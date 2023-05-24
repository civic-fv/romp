/**
 * @proj romp
 * @author Andrew Osterhout
 * @author Ajantha Varadharaaj
 * @org University of Utah (UofU) School of Computing (SoC)
 * @org Center for Parallel compute at Utah (CPU)
 * @org <a href="https://civic-fv.github.io">Civic-fv NSF Grant</a>
 * @org Ganesh Gopalakrishnan's Research Group
 * @file IntRangeSet.hpp
 * 
 * @brief A data object that holds a set representation of integer ranges,
 *        where overlap-ing ranges are union-ed into single ranges.
 *        (used in romp to handle the merged scalar enum value space)
 * 
 * @date 2022/10/16
 * @version 0.3
 */

namespace romp {

template<long long MIN, long long MAX>
class SubRangeSet {
  typedef long long int_t;
  struct _Range {
    _Range* prev;
    int_t min;
    int_t max;
    _Range* next;
  };
  _Range* range_head = nullptr;
  size_t _size = 0u;
public:
  const int_t MIN;
  const int_t MAX;
  SubRangeSet(int_t MIN_, int_t MAX_) 
    : MIN(MIN_), MAX(MAX_), range_head(nullptr), _size(0u) {}
  void insert(int_t min, int_t max) {
    min = ((min <= MIN) ? MIN : min);
    max = ((max >= MAX) ? MAX : max);
    if (range_head == nullptr) {  // base case: empty
      range_head = new _Range{nullptr, min, max, nullptr};
      _size = 1u;
      return;
    }
    _Range* range = _insert(range_head, min,max);
    _span(range->next, min,max, range);  // never call with a node you don't want to loose!!
  }

  iterator begin() const { return iterator{range_head}; }
  iterator end() const { return iterator{nullptr}; }
  size_t size() const { return _size; } 

protected:
  struct iterator {
    _Range* iter;
    _Range& operator*() const { return *iter; }
    _Range* operator->() const { return iter; }
    friend iterator& operator ++ (iterator& i) { i.iter = i.iter->next; return i; }
    friend iterator operator ++ (iterator& i, int v) { iterator cpy{i.iter}; ++i; return cpy; }
    friend bool operator == (const iterator& l, const iterator& r) { return l.iter == r.iter; }
    friend bool operator != (const iterator& l, const iterator& r) { return l.iter != r.iter; }
  };

  _Range* _insert(_Range* r, int_t& min, int_t& max) { // forward (r never null)
    if (min > r->max) { // case: r comes before range
      auto _r = new _Range{r,min,max,r->next};
      r->next = _r;
      return _r;
    }
    if (min >= r->min) {  // case: r overlaps with range // also case: r->max == min
      if (r->max >= max) // sub-case: r contains all of our range
        max = r->max;   // update max
      return r;
    }
    if (r->next == nullptr) {
      ++_size; // add new range to the count
      return new _Range{r,min,max,nullptr};
    }
    return _insert(r->next, min,max);
  }
  void _span(_Range* r, int_t& min, int_t& max, _Range* range) { // forward (r can be null); !! trims ALL nodes it explores !!
    if (r == nullptr) // base case: END OF RANGE LIST
      return;
    if (max < r->min) // base case: NO OVERLAP
      return;  // do not trim r
    if (max >= r->min) { // case: r overlaps with range
      range->max = r->max; // update with current range with values from this overlapping range
      range->next = r->next;
    }
    if (max > r->max) // case: range completely overlaps with r
      _span(r->next, min,max, range);  // check next range for overlap
    delete r; // trim r
    --_size; // remove it from the count
  }
};

} // namespace romp