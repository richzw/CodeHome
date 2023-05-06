class CombiningEmittingFn extends DoFn<KV<Integer, Integer>, Integer> {

  @TimerId("emitter")
  private final TimerSpec emitterSpec = TimerSpecs.timer(TimeDomain.PROCESSING_TIME);

  @StateId("done")
  private final StateSpec<ValueState<Boolean>> doneState = StateSpecs.value();

  @StateId("agg")
  private final StateSpec<CombiningState<Integer, int[], Integer>>
      aggSpec = StateSpecs.combining(
          Sum.ofIntegers().getAccumulatorCoder(null, VarIntCoder.of()), Sum.ofIntegers());

  @ProcessElement
  public void processElement(ProcessContext c,
      @StateId("agg") CombiningState<Integer, int[], Integer> aggState,
      @StateId("done") ValueState<Boolean> doneState,
      @TimerId("emitter") Timer emitterTimer) throws Exception {
        if (SOME CONDITION) {
          countValueState.clear();
          doneState.write(true);
        } else {
          countValueState.addAccum(c.element().getValue());
          emitterTimer.align(Duration.standardMinutes(5)).setRelative();
        }
      }
    }

  @OnTimer("emitter")
  public void onEmit(
      OnTimerContext context,
      @StateId("agg") CombiningState<Integer, int[], Integer> aggState,
      @StateId("done") ValueState<Boolean> doneState,
      @TimerId("emitter") Timer emitterTimer) {
      Boolean isDone = doneState.read();
      if (isDone != null && isDone) {
        return;
      } else {
        context.output(aggState.getAccum());
        // Set the timer to emit again
        emitterTimer.align(Duration.standardMinutes(5)).setRelative();
      }
    }
  }
  }
