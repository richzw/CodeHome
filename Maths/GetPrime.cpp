// Get primes between 2~100

#include <algorithm>
#include <iostream>
#include <iterator>

using namespace std;

template <typename T>
class range_type {
public:
    class range_iterator {
    public:
        typedef T value_type;
        typedef T* pointer;
        typedef T& reference;
        typedef T difference_type;
        typedef forward_iterator_tag iterator_category;

        range_iterator(T v) : v_(v) {}
        T operator*() const { return v_; }
        range_iterator operator++() { ++v_; return *this; }
        range_iterator operator++(int) { range_iterator copy(*this); ++v_; return copy; }
        bool operator==(const range_iterator &other) const { return v_ == other.v_; }
        bool operator!=(const range_iterator &other) const { return v_ != other.v_; }
    private:
        T v_;
    };

    range_type(T lower, T upper) : lower_(lower), upper_(upper) {}
    range_iterator begin() const { return range_iterator(lower_); }
    range_iterator end() const { return range_iterator(upper_); }

private:
    T lower_, upper_;
};

template <typename T>
range_type<T> range(T lower, T upper) { return range_type<T>(lower, upper); }

template <typename Container, typename UnaryPredicate>
bool none_of(const Container& c, UnaryPredicate pred) { return none_of(c.begin(), c.end(), pred); }

template <typename Container, typename DestIterator, typename UnaryPredicate>
void copy_if(const Container& c, DestIterator d, UnaryPredicate pred) { copy_if(c.begin(), c.end(), d, pred); }

int main() {
    copy_if(range(2, 101), ostream_iterator<int>(cout, " "), [](int x){ return none_of(range(2, x), [x](int y) { return x % y == 0; }); });
    return 0;
}
