//https://www.oreilly.com/library/view/streaming-systems/9781491983867/ch04.html

public class BoundedSessions extends WindowFn<Object, IntervalWindow> {
  private final Duration gapDuration;
  private final Duration maxSize;
  public Collection<IntervalWindow> assignWindows(AssignContext c) {
    return Arrays.asList(
      new IntervalWindow(c.timestamp(), gapDuration));
  }
  private Duration windowSize(IntervalWindow window) {
    return window == null
      ? new Duration(0)
      : new Duration(window.start(), window.end());
  }
  public void mergeWindows(MergeContext c) throws Exception {
    List<IntervalWindow> sortedWindows = new ArrayList<>();
    for (IntervalWindow window : c.windows()) {
      sortedWindows.add(window);
    }
    Collections.sort(sortedWindows);
    List<MergeCandidate> merges = new ArrayList<>();
    MergeCandidate current = new MergeCandidate();
    for (IntervalWindow window : sortedWindows) {
      MergeCandidate next = new MergeCandidate(window);
      if (current.intersects(window)) {
        current.add(window);
        if (windowSize(current.union) <= (maxSize - gapDuration))
          continue;
        // Current window exceeds bounds, so flush and move to next
        next = new MergeCandidate();
      }
      merges.add(current);
      current = next;
    }
    merges.add(current);
    for (MergeCandidate merge : merges) {
      merge.apply(c);
    }
  }
}

PCollection<KV<Team, Integer>> totals = input
  .apply(Window.into(BoundedSessions
                       .withGapDuration(ONE_MINUTE)
                       .withMaxSize(THREE_MINUTES))
               .triggering(
                 AfterWatermark()
                   .withEarlyFirings(AlignedDelay(ONE_MINUTE))
                   .withLateFirings(AfterCount(1)))
               .accumulatingAndRetractingFiredPanes())
  .apply(Sum.integersPerKey());
