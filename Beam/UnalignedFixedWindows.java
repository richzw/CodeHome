public class UnalignedFixedWindows
    extends WindowFn<KV<K, V>, IntervalWindow> {
  private final Duration size;
  private final Duration offset;
  public Collection<IntervalWindow> assignWindow(AssignContext c) {
    long perKeyShift = hash(c.element().key()) % size.getMillis();
    long start = perKeyShift + c.timestamp().getMillis()
                   - c.timestamp()
                      .plus(size)
                      .minus(offset)
                      .getMillis() % size.getMillis();
    return Arrays.asList(IntervalWindow(new Instant(start), size));
  }
}

PCollection<KV<Team, Integer>> totals = input
  .apply(Window.into(UnalignedFixedWindows.of(TWO_MINUTES))
               .triggering(AfterWatermark()))
  .apply(Sum.integersPerKey());
