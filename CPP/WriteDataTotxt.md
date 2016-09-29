
### Question

I currently write a set of doubles from a vector to a text file like this:

```cpp
std::ofstream fout;
fout.open("vector.txt");

for (l = 0; l < vector.size(); l++)
    fout << std::setprecision(10) << vector.at(l) << std::endl;

fout.close();
```

But this is taking a lot of time to finish. Is there a faster or more efficient way to do this?

### Answer 1

```cpp
std::ofstream fout("vector.txt");
fout << std::setprecision(10);

for(auto const& x : vector)
    fout << x << '\n';
```

Everything I changed had theoretically worse performance in your version of the code, but the `std::endl` was the real killer.
`std::vector::at` (with bounds checking, which you don't need) would be the second, then the fact that you did not use iterators.

Why default-construct a `std::ofstream` and then call open, when you can do it in one step? Why call close when RAII (the destructor)
takes care of it for you? You can also call

```cpp
fout << std::setprecision(10)
```

just once, before the loop.

As noted in the comment below, if your vector is of elements of fundamental type, you might get a better performance with 
`for(auto x : vector)`. Measure the running time / inspect the assembly output.

### Answer 2

You can also use a rather neat form of outputting contents of any vector into the file with a help of iterators and copy function.

```cpp
std::ofstream fout("vector.txt");
fout.precision(10);

std::copy(numbers.begin(), numbers.end(), std::ostream_iterator<double>(fout, "\n"));
```

### Answer 3

There are two main bottlenecks in your program: output and formatting text.

To increase performance, you will want to increase the amount of data output per call. For example, 1 output transfer of 500 characters
is faster than 500 transfers of 1 character.

My recommendation is you format the data to a big buffer, then block write the buffer.

Here's an example:

```cpp
char buffer[1024 * 1024];
unsigned int buffer_index = 0;
const unsigned int size = my_vector.size();
for (unsigned int i = 0; i < size; ++i)
{
  signed int characters_formatted = snprintf(&buffer[buffer_index],
                                             (1024 * 1024) - buffer_index,
                                             "%.10f", my_vector[i]);
  if (characters_formatted > 0)
  {
      buffer_index += (unsigned int) characters_formatted;
  }
}
cout.write(&buffer[0], buffer_index);
```
