/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package org.apache.beam.sdk.transforms.windowing;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.Collections;
import java.util.List;
import java.util.Objects;
import javax.annotation.Nullable;
import org.apache.beam.sdk.coders.Coder;
import org.apache.beam.sdk.transforms.display.DisplayData;
import org.apache.beam.sdk.values.KV;
import org.joda.time.Duration;

/**
 * A {@link WindowFn} that windows values into sessions separated by periods with no input for at
 * least the duration specified by {@link #getGapDuration()} or until it fins a stopValue given by
 * {@link #withStopValue()}.
 *
 * <p>For example, in order to window data into session with at least 10 minute gaps in between
 * them and use 0 as the value where we want to close the window:
 *
 * <pre>{@code
 * PCollection<Integer> pc = ...;
 * PCollection<Integer> windowed_pc = pc.apply(
 *   Window.<Integer>into(StopSessions.withGapDuration(Duration.standardMinutes(10).withStopValue(0))));
 * }</pre>
 */
public class StopSessions extends WindowFn<KV<String,Integer>, IntervalWindow> {
  /** Duration of the gaps between sessions. */
  private final Duration gapDuration;

  /** Value that closes the session. */
  private final Integer stopValue;

  /** Creates a {@code StopSessions} {@link WindowFn} with the specified gap duration. */
  public static StopSessions withGapDuration(Duration gapDuration) {
    return new StopSessions(gapDuration, 0);
  }

  /** Creates a {@code StopSessions} {@link WindowFn} with the specified stop value. */
  public StopSessions withStopValue(Integer stopValue) {
    return new StopSessions(gapDuration, stopValue);
  }

  /** Creates a {@code StopSessions} {@link WindowFn} with the specified gap duration and stop value. */
  private StopSessions(Duration gapDuration, Integer stopValue) {
    this.gapDuration = gapDuration;
    this.stopValue = stopValue;
  }

  @Override
  public Collection<IntervalWindow> assignWindows(AssignContext c) {
    // Assign each element into a window from its timestamp until gapDuration in the
    // future.  Overlapping windows (representing elements within gapDuration of
    // each other) will be merged. If a stop signal is encountered the element will
    // be windowed into a minimum window of 1 ms
    Duration newGap = c.element().getValue().equals(this.stopValue) ? new Duration(1) : gapDuration;
    return Arrays.asList(new IntervalWindow(c.timestamp(), newGap));
  }

  @Override
  public Coder<IntervalWindow> windowCoder() {
    return IntervalWindow.getCoder();
  }

  @Override
  public boolean isCompatible(WindowFn<?, ?> other) {
    return other instanceof StopSessions;
  }

  @Override
  public void verifyCompatibility(WindowFn<?, ?> other) throws IncompatibleWindowException {
    if (!this.isCompatible(other)) {
      throw new IncompatibleWindowException(
          other,
          String.format(
              "%s is only compatible with %s.",
              StopSessions.class.getSimpleName(), StopSessions.class.getSimpleName()));
    }
  }

  @Override
  public WindowMappingFn<IntervalWindow> getDefaultWindowMappingFn() {
    throw new UnsupportedOperationException("StopSessions is not allowed in side inputs");
  }

  public Duration getGapDuration() {
    return gapDuration;
  }

  public Integer getStopValue() {
    return stopValue;
  }

  @Override
  public void populateDisplayData(DisplayData.Builder builder) {
    super.populateDisplayData(builder);
    builder.add(DisplayData.item("gapDuration", gapDuration).withLabel("Session Gap Duration"));
    builder.add(DisplayData.item("stopValue", stopValue).withLabel("Stop Value that closes Session"));
  }

  @Override
  public boolean equals(Object object) {
    if (!(object instanceof StopSessions)) {
      return false;
    }
    StopSessions other = (StopSessions) object;
    return getGapDuration().equals(other.getGapDuration());
  }

  @Override
  public int hashCode() {
    return Objects.hash(gapDuration);
  }

    /** Merge overlapping {@link IntervalWindow}s. */
  @Override
  public void mergeWindows(MergeContext c) throws Exception {
    // Merge any overlapping windows into a single window.
    // Sort the list of existing windows so we only have to
    // traverse the list once rather than considering all
    // O(n^2) window pairs.
    List<IntervalWindow> sortedWindows = new ArrayList<>();
    for (IntervalWindow window : c.windows()) {
      sortedWindows.add(window);
    }
    Collections.sort(sortedWindows);
    List<MergeCandidate> merges = new ArrayList<>();
    MergeCandidate current = new MergeCandidate();
    for (IntervalWindow window : sortedWindows) {
      // get window duration and check if it's a stop session request
      Long windowDuration = new Duration(window.start(), window.end()).getMillis();

      if (current.intersects(window) && !windowDuration.equals(1L)) {
        current.add(window);
      } else {
        merges.add(current);
        current = new MergeCandidate(window);
      }
    }
    merges.add(current);
    for (MergeCandidate merge : merges) {
      merge.apply(c);
    }
  }

  private static class MergeCandidate {
    @Nullable private IntervalWindow union;
    private final List<IntervalWindow> parts;

    public MergeCandidate() {
      union = null;
      parts = new ArrayList<>();
    }

    public MergeCandidate(IntervalWindow window) {
      union = window;
      parts = new ArrayList<>(Arrays.asList(window));
    }

    public boolean intersects(IntervalWindow window) {
      return union == null || union.intersects(window);
    }

    public void add(IntervalWindow window) {
      union = union == null ? window : union.span(window);
      parts.add(window);
    }

    public void apply(WindowFn<?, IntervalWindow>.MergeContext c) throws Exception {
      if (parts.size() > 1) {
        c.merge(parts, union);
      }
    }

    @Override
    public String toString() {
      return "MergeCandidate[union=" + union + ", parts=" + parts + "]";
    }
  }
}
