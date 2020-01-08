package com.dataflow.samples;

import java.util.Arrays;
import org.apache.beam.sdk.Pipeline;
import org.apache.beam.sdk.options.Description;
import org.apache.beam.sdk.options.PipelineOptions;
import org.apache.beam.sdk.options.PipelineOptionsFactory;
import org.apache.beam.sdk.options.Validation.Required;
import org.apache.beam.sdk.transforms.Create;
import org.apache.beam.sdk.transforms.DoFn;
import org.apache.beam.sdk.transforms.GroupByKey;
import org.apache.beam.sdk.transforms.ParDo;
import org.apache.beam.sdk.transforms.Sum;
import org.apache.beam.sdk.transforms.windowing.AfterWatermark;
import org.apache.beam.sdk.transforms.windowing.StopSessions; // custom one
import org.apache.beam.sdk.transforms.windowing.BoundedWindow;
import org.apache.beam.sdk.transforms.windowing.Window;
import org.apache.beam.sdk.values.KV;
import org.apache.beam.sdk.values.TimestampedValue;
import org.joda.time.Duration;
import org.joda.time.Instant;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;


public class StopSessionsExample {

  private static final Logger LOG = LoggerFactory.getLogger(StopSessionsExample.class);

  public static void main(String[] args) {
    PipelineOptions options = PipelineOptionsFactory.fromArgs(args).withValidation().as(PipelineOptions.class);

    Pipeline p = Pipeline.create(options);

    p
      .apply("Create data", Create.timestamped(
            TimestampedValue.of(KV.of("k1", 0), new Instant()), // <t0, k1, 0>
            TimestampedValue.of(KV.of("k1",98), new Instant().plus(1000)), // <t1, k1, 98>
            TimestampedValue.of(KV.of("k1",145), new Instant().plus(2000)), // <t2, k1, 145>
            TimestampedValue.of(KV.of("k1",0), new Instant().plus(4000)), // <t4, k1, 0>
            TimestampedValue.of(KV.of("k1",350), new Instant().plus(3000)), // <t3, k1, 350>
            TimestampedValue.of(KV.of("k1",40), new Instant().plus(5000)), //  <t5, k1, 40>
            TimestampedValue.of(KV.of("k1",65), new Instant().plus(6000)), //  <t6, k1, 65>
            TimestampedValue.of(KV.of("k1",120), new Instant().plus(7000)), //  <t7, k1, 120>
            TimestampedValue.of(KV.of("k1",240), new Instant().plus(8000)), //  <t8, k1, 240>
            TimestampedValue.of(KV.of("k1",352), new Instant().plus(9000)))) //  <t9, k1, 352>
      .apply("Window into StopSessions", Window.<KV<String, Integer>>into(StopSessions
        .withGapDuration(Duration.standardSeconds(10))
        .withStopValue(0))
          .triggering(AfterWatermark.pastEndOfWindow())
          .withAllowedLateness(Duration.ZERO)
          .discardingFiredPanes())
      .apply("Group By Key", GroupByKey.<String, Integer>create())
      .apply("Log results", ParDo.of(new DoFn<KV<String, Iterable<Integer>>, Void>() {
        @ProcessElement
        public void processElement(ProcessContext c, BoundedWindow window) {
          String user = c.element().getKey();
          Iterable<Integer> scores = c.element().getValue();
          StringBuilder values = new StringBuilder(); 

          scores.forEach(value->values.append(value + ","));
          LOG.info(String.format("user=%s, scores=%s, window=%s", user, "[" + values.substring(0, values.length() - 1) + "]", window.toString()));
        }
      }));

    p.run();
  }
}
