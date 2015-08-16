// Sort the array but keep some value fixed following predicate

template <typename Container, typename Comparator, typename Predicate>
void sortButKeepSomeFixed(Container& c, const Comparator& comp, const Predicate& pred) {
  vector<typename Container::value_type> toSort;
  vector<typename Container::iterator> iterators;
  for (typename Container::iterator it = c.begin(); it != c.end(); ++it) {
    if (!pred(*it)) {
      toSort.emplace_back(*it);
      iterators.emplace_back(it);
    }
  }
  
  toSort.sort(toSort.begin(), toSort.end(), comp);
  for (size_t i = 0; i < toSort.size(); ++i) {
    *iterators[i] = toSort[i];
  }
}
