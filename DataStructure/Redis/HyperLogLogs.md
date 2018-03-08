To get started, let’s look at something more familiar than HyperLogLogs.

Imagine someone flipping a coin multiple times, while recording the maximum number of heads they get in a row. If they told you this number — would you be able to estimate how many times they’d flipped the coin?

Not with great accuracy, but since a longer run of heads is more probable when flipping the coin many times, the number of consecutive heads or tails in a series of coin flips can indicate how many times the coin was flipped: if the number of heads in a row is low, the number of coin flips is most probably also low. Conversely, if the number of heads in a row is high the number of coin flips is most probably high.

If the same number of coin flips were done and recorded separately, a much more precise estimate could be made by combining these numbers. This can be observed using the following methods:

```python
def coin_flips(n)
  Array.new(n) { [:heads, :tails].sample }
end

def heads_in_a_row(flips)
  run = max = 0

  flips.each do |flip|
    if flip == :heads
      run += 1
    else
      max = [run, max].max
      run = 0
    end
  end

  max
end

class Array
  def average
    reduce(:+).to_f / size
  end
end
```

The bigger the number of coin flips, the bigger the number of heads in a row.

```
heads_in_a_row coin_flips(10)    #=> 3
heads_in_a_row coin_flips(100)   #=> 5
heads_in_a_row coin_flips(1000)  #=> 9
heads_in_a_row coin_flips(10000) #=> 15
```

The bigger the number of series, the better the stability of the output. With a more stable output, a better estimate can be made:

```
heads_in_a_row coin_flips(10) #=> 3
heads_in_a_row coin_flips(10) #=> 7
heads_in_a_row coin_flips(10) #=> 4

Array.new(1000) { heads_in_a_row coin_flips(10) }.average #=> 2.449
Array.new(1000) { heads_in_a_row coin_flips(10) }.average #=> 2.442
Array.new(1000) { heads_in_a_row coin_flips(10) }.average #=> 2.469
```

Similarly to how the number of coin flips can be estimated by observing the number of heads in a row, the calculations of a HyperLogLog are based on the observation that the cardinality of a set of uniformly distributed random numbers can be estimated by counting the maximum number of leading zeros in the binary representation of the numbers.

For there to be leading zeros, the numbers must be represented as integers with the same number of bits, for instance as 64-bit unsigned integers.

If the maximum number of leading zeros is n, the estimated number of unique values in the set is 2^n.

To make sure values are uniformly distributed and represented as same-size integers, the HyperLogLog algorithm applies a hash function to all values. This transforms the values into a set of uniformly distributed random numbers with the same cardinality as the original set.

The first few bits of the hashed values are used to divide them into different subsets, much like the separate series of coin flips in the example above. For each subset the maximum number of leading zeros within its values are stored in a register.

To calculate the approximate cardinality of the whole set, the estimates for all the subsets are combined using a harmonic mean.