public class PerElementFixedWindows<T extends HasWindowSize>
    extends WindowFn<T, IntervalWindow> {
  private final Duration offset;
  public Collection<IntervalWindow> assignWindow(AssignContext c) {
    long perElementSize = c.element().getWindowSize();
    long start = perKeyShift + c.timestamp().getMillis()
                   - c.timestamp()
                      .plus(size)
                      .minus(offset)
                      .getMillis() % size.getMillis();
    return Arrays.asList(IntervalWindow(
        new Instant(start), perElementSize));
  }
}

PCollection<KV<Team, Integer>> totals = input
  .apply(Window.into(new PerElementFixedWindows())
               .triggering(AfterWatermark()))
  .apply(Sum.integersPerKey());
