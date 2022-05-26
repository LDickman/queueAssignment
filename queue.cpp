// queue.cpp for CS 223 Lab 5
//
// Student Name: Lauren Dickman
// Date: 3/13/2020
//
// CLASS IMPLEMENTED: queue (see queue.h for documentation)
//
// INVARIANTS for the queue class:
//
//   1. The current number of items in the queue is maintained in the instance
//      variable `count`.
//
//   2. The instance variable `data` is an array in dynamic (heap) memory of
//      length `capacity`, used to store the items in the queue. The items are
//      stored from data[first] through data[last].
//
//   3. The data array is indexed in a "circular" fashion: if the queue is not
//      full and if the most recently added item is at index capacity-1 (the
//      largest valid index in `data`), then the next added item will be stored
//      at index 0.  That is, `next_index(capacity-1)` is 0.
//
//   4. For an empty queue, `last` is any valid index, and `first` is
//      equal to `next_index(last)`. 
//
//   5. The queue is out of capacity when next_index(next_index(last)) is equal 
//      to first. That is, there will always be an unused "space" in the circular 
//      queue between last and first. 
//
//   6.	Before trying to add an item, we always call ensure_capacity, which will 
//      copy the data over to a new array twice the capacity of the current array
//      ONLY IF the queue is out of capacity.
//
// INSTANCE VARIABLES:
//      queue::size_type capacity
//      queue::value_type data[capacity]
//      queue::size_type first      // Index of item at front of the queue
//      queue::size_type last       // Index of item at rear of the queue
//      queue::size_type count      // Current number of items in the queue

#include "queue.h"

using namespace std;

namespace cs223_lab5
{
typedef queue::size_type size_type;
typedef queue::value_type value_type;
// CONSTRUCTOR
// Basic constructor
// Precondition:  cap >= 2
// Postcondition: queue has been initialized as an empty queue
//    with capacity equal to `cap`.
// Note:  If cap < 2, the queue capacity defaults to 8.
queue::queue(size_type cap)
{
   if (cap < 2)
   {
    cap = (2*4);
    capacity = cap;
   }
   else
   {
    capacity = cap;
   }
   count = 0;
   last = cap-1;
   first = next_index(last);
   data = new value_type [cap];

}
// Copy constructor
// Postcondition: queue is initialized as an independent copy of `other`;
//    subsequent changes to either of the queues will NOT affect the other.
queue::queue(const queue& other)
{
    //STUB
}
// DESTRUCTOR
queue::~queue()
{
    //STUB
}

// ACCESSOR MEMBER FUNCTIONS

// size
// Postcondition: Return value is the current number of items in the queue.
size_type queue::size() const
{
    return count;
}

// is_empty()
// Postcondition: Returns true if this is an empty queue; otherwise
//    returns false.
bool queue::is_empty() const
{
    size_type ans = 0;
    if (ans == count)
    {
        return true;
    }
    return false;
}

// front
// Precondition:  size > 0
// Postcondition: Return value is the front item of the queue.
value_type queue::front() const
{
    return data[first];
}

// PRIVATE FUNCTIONS

// next_index
// private function for helping to move a circular array index forward
// Precondition: 0 <= i < capacity
// Postcondition: Returns the next index, possibly looping around to the
//    beginning of the array.
// Note: complete code is provided
queue::size_type queue::next_index(size_type i) const
{
    i = (i + 1) % capacity;
    return i;
}

// copy_values
// private function for copying the values from the queue into a provided array
// Precondition: The array has enough space for count + 1 values.
// Postcondition: The first 0 through count - 1 entries in the array contain
//     copies of the queue elements, in same correct order.
void queue::copy_values(value_type arr[]) const
{
    for (size_type i = first; i <= last; i = next_index(i))
    {
        arr[i] = data[i];
    }
}

// ensure_capacity
// private function for increasing the capacity of the queue as needed
// Postcondition:
//    - If capacity == count - 1 (queue is "full") when this function is called,
//      then after it returns, capacity == old capacity * 2
//    - The items in the queue, and their ordering, is unchanged.
// NOTE: If capacity > count - 1 when this function is called, then it has no
//    effect.
// NOTE: While technically the array can fit one more item, we will NEVER
//    fully fill the array. This makes other parts of the class easier to code.
void queue::ensure_capacity()
{
    if (capacity == (count - 1))
    {
        value_type* new_capacity = new value_type [capacity];
        capacity = capacity * 2;
        copy_values(new_capacity);
    }
}

// getIteratorAt
// private function that creates an iterator for the queue at a particular index.
// Precondition: index is a valid location into the queue's elements, or it is the
//      location immediately preceding the last valid location.
// NOTE: Implementation is provided
queue::iterator queue::getIteratorAt(size_type index) const
{
    return queue::iterator(*this, index);
}

// MODIFICATION MEMBER FUNCTIONS (PUBLIC)

// push
// Postcondition: A new item, `entry`, has been inserted at the rear
//    of the queue.
// Postcondition: size has increased by 1.
void queue::push(const value_type& entry)
{
    ensure_capacity();
    last = next_index(last);
    data[last] = entry;
    count = count + 1;
}

// pop
// Precondition:  size > 0
// Postcondition: The front item of the queue has been removed.
// Postcondition: size has decreased by 1.
void queue::pop()
{
    first = next_index(first);
    count = count - 1;
}

// assignment operator
// Postcondition: This queue becomes an identical -- but indepedent --
//    copy of `other` queue.
// Postcondition: Returns this queue to allow for "chained assignment".
queue& queue::operator=(const queue& other)
{
    return *this;
}

// NON-MEMBER FUNCTIONS (FRIENDS)

// equivalence operator, checks for logical equivalence of q1 and q2
// Postcondition: Returns true if
//       a) q1 and q2 are equal in length, and
//       b) q1 and q2 have equivalent values and the same ordering;
//    otherwise, returns false.
//  Example 1. The queues <a, b, c> and <a, b, c> are equivalent.
//  Example 2. The queues <a, b, c> and <c, a, b> are not equivalent.
//  Example 3. The queues <a, b> and <a, b, c> are not equivalent.
bool operator==(const queue& q1, const queue& q2)
{
    return false;
}

// inequivalence operator
// Postcondition: Returns false if q1 == q2; otherwise, returns true.
bool operator!=(const queue& q1, const queue& q2)
{
    return false;
}

// output stream operator
// Printed queue should have this general format:
//    queue of size <num>:
//    first_item
//       .
//       .
//       .
//    last_item
//
// For example, if the queue contains 3 strings: "German shepherd",
//    "French bulldog", and "Boston terrier", pushed into the queue in
//    that order, then the printed queue will look as follows:
//       queue of size 3:
//       German shepherd
//       French bulldog
//       Boston terrier
//
// Postcondition: Returns the ostream to allow for chaining.
// Note: complete code is provided
std::ostream& operator<<(std::ostream& out, const queue& q)
{
    out << "queue of size " << q.size() << ":\n";

    for (queue::size_type i = 0; i < q.size(); i++)
    {
        out << q.data[(q.first + i) % q.capacity] << "\n";
    }

    return out;
}

// ITERATOR FUNCTIONS

// begin
// Returns an iterator pointing to the location of the first element
// in the queue.
// NOTE: Use getIteratorAt
queue::iterator queue::begin() const
{
    return getIteratorAt(0);
}

// end
// Returns an iterator pointing to the location immediately following
// the last element in the queue.
// NOTE: Use getIteratorAt
// NOTE: You must never try to access this iterator's location. You must
//    only use this iterator in comparison to another iterator, to determine
//    if that other iterator has reached the end of the queue.
queue::iterator queue::end() const
{
    return getIteratorAt(0);
}

// operator++
// Moves the iterator to point to the next location
// Precondition: The next location in the queue is
//      a valid index into the queue's data.
// Postcondition: The iterator now points to the next location in the
//      queue (this may no longer be a valid location.)
value_type& queue::iterator::operator*() const
{
    return q.data[0];
}

// operator*
// Dereferences the iterator pointer
// Precondition: The iterator points to a valid location in the queue's
//      data.
// Postcondition: Returns a reference to the value stored at
//      the location pointed to by the iterator.
queue::iterator& queue::iterator::operator++()
{
    return *this;
}

// operator*=
// Assigns to iterator location
// Precondition: The iterator points to a valid location in the queue's
//      data.
// Postconditions:
//    - The location pointed to by the iterator now contains
//      the provided value.
//    - Returns the provided value.
value_type& queue::iterator::operator*=(const value_type& value) const
{
    return q.data[0];
}

// operator==
// Compares two iterators. Two iterators are considered equal when they
// refer to the same queue (so the ADDRESSES of the two queue references
// are equal) and they have the same index.
// NOTE: It is important that you compare the queue references for ADDRESS
//       equality, and not normal equality.
// Postcondition: Returns true if the iterators are equal, false otherwise
bool queue::iterator::operator==(const queue::iterator& other) const
{
    return false;
}

// operator!=
// Compares two iterators. See note above.
// Postcondition: Returns false if the iterators are equal, true otherwise.
// NOTE: You should not implement both operator== and operator!= independent
//     of each other. Implement only one of them and make the other call it
//     appropriately.
bool queue::iterator::operator!=(const queue::iterator& other) const
{
    return false;
}

}  // end namespace cs223_lab5
