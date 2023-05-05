public class CustomFieldTimePolicy extends TimestampPolicy<String, Foo> {
    protected Instant currentWatermark;

    public CustomFieldTimePolicy(Optional<Instant> previousWatermark) {
        currentWatermark = previousWatermark.orElse(BoundedWindow.TIMESTAMP_MIN_VALUE);
    }


    @Override
    public Instant getTimestampForRecord(PartitionContext ctx, KafkaRecord<String, Foo> record) {
        currentWatermark = new Instant(record.getKV().getValue().getTimestamp());
        return currentWatermark;
    }

    @Override
    public Instant getWatermark(PartitionContext ctx) {
        return currentWatermark;
    }
}

   KafkaIO.<String, Foo>read().withBootstrapServers("http://localhost:9092")
                    .withTopic("foo")
                    .withKeyDeserializer(StringDeserializer.class)
                    .withValueDeserializerAndCoder(KafkaAvroDeserializer.class, AvroCoder.of(Foo.class)) 
                    .withTimestampPolicyFactory((tp, previousWatermark) -> new CustomFieldTimePolicy(previousWatermark))
                    .updateConsumerProperties(kafkaProperties))
