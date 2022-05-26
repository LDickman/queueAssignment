// FILE: queue.h
// Header file for Lab 5, CS 223, Winter 2020
//
// Modified version of the queue.h file provided by Main/Savitch, Chap. 8
//
// Haris Skiadas, Barb Wahl, and Theresa Wilson
//
// ********** DO NOT CHANGE THIS FILE **********
//
// CLASS PROVIDED: queue
//
// TYPEDEFS and MEMBER CONSTANTS for the queue class:
//   typedef ____ value_type
//     queue::value_type is the data type of the items in the queue. It
//     may be any of the C++ built-in types (int, char, etc.), or any class with
//     a default constructor, assignment operator, equivalence operator, and
//     copy constructor.
//
//   typedef ____ size_type
//     queue::size_type is the data type of any variable that keeps track
//     of how many items are in a queue.
//
// VALUE SEMANTICS for the queue class:
//   Assignment and copy constructor may be used with queue objects.
//
// FRIENDS OF THE CLASS
//    friend bool operator==(const queue& q1, const queue& q2);
//    friend bool operator!=(const queue& q1, const queue& q2);
//    friend std::ostream& operator<<(std::ostream& out, const queue& q);

#ifndef CS223_LAB5
#define CS223_LAB5

#include <iostream>

namespace cs223_lab5
{
class queue
{
  public:
    // TYPEDEFS and MEMBER CONSTANTS
    typedef std::size_t size_type;
    typedef std::string value_type;

    // CONSTRUCTORS

    // Basic constructor
    // Precondition:  cap >= 2
    // Postcondition: queue has been initialized as an empty queue
    //    with capacity equal to `cap`.
    // Note:  If cap < 2, the queue capacity defaults to 8.
    queue(size_type cap = 8);

    // Copy constructor
    // Postcondition: queue is initialized as an independent copy of `other`;
    //    subsequent changes to either of the queues will NOT affect the other.
    queue(const queue& other);

    // DESTRUCTOR
    ~queue();

    // ACCESSOR MEMBER FUNCTIONS

    // size
    // Postcondition: Return value is the current number of items in the queue.
    size_type size() const;

    // is_empty()
    // Postcondition: Returns true if this is an empty queue; otherwise,
    //    returns false.
    bool is_empty() const;

    // front
    // Precondition:  size > 0
    // Postcondition: Return value is the front item of the queue.
    value_type front() const;

    // MODIFICATION MEMBER FUNCTIONS

    // push
    // Postcondition: A new item, `entry`, has been inserted at the rear
    //    of the queue.
    // Postcondition: size has increased by 1.
    void push(const value_type& entry);

    // pop
    // Precondition:  size > 0
    // Postcondition: The front item of the queue has been removed.
    // Postcondition: size has decreased by 1.
    void pop();

    // assignment operator
    // Postcondition: This queue becomes an identical -- but indepedent --
    //    copy of `other` queue.
    // Postcondition: Returns this queue to allow for "chained assignment".
    queue& operator=(const queue& other);

    // Class that provides iterators for a queue. It must be declared as a
    // friend class in order to access the private storage details of a
    // queue
    friend class iterator;

    // Inner class iterator
    // An iterator represents a pointer to a specific location in the queue.
    // Invariant: index is either an index into the queue's data corresponding to
    //      a valid location, or it immediately follows the last valid index,
    //      i.e. is equal to next_index(last). This is only the case for the end
    //      iterator.
    // NOTE: Iterators are only valid as long as the queue has not changed. Any
    //      change to the queue's contents will invalidate any active iterator.
    //      You must take care not to rely on the behavior of any such iterators.
    class iterator
    {
      public:
        // operator++
        // Moves the iterator to point to the next location
        // Precondition: The next location in the queue is
        //      a valid index into the queue's data.
        // Postcondition: The iterator now points to the next location in the
        //      queue (this may no longer be a valid location.)
        iterator& operator++();

        // operator*
        // Dereferences the iterator pointer
        // Precondition: The iterator points to a valid location in the queue's
        //      data.
        // Postcondition: Returns a reference to the value stored at
        //      the location pointed to by the iterator.
        value_type& operator*() const;

        // operator*=
        // Assigns to iterator location
        // Precondition: The iterator points to a valid location in the queue's
        //      data.
        // Postconditions:
        //    - The location pointed to by the iterator now contains
        //      the provided value.
        //    - Returns the provided value.
        value_type& operator*=(const value_type& value) const;

        // operator==
        // Compares two iterators. Two iterators are considered equal when they
        // refer to the same queue (so the ADDRESSES of the two queue references
        // are equal) and they have the same index.
        // NOTE: It is important that you compare the queue references for address
        //       equality, and not normal equality.
        // Postcondition: Returns true if the iterators are equal, false otherwise
        bool operator==(const iterator& iter) const;
        
        // operator!=
        // Compares two iterators. See note above.
        // Postcondition: Returns false if the iterators are equal, true otherwise.
        // NOTE: You should not implement both operator== and operator!= independent
        //     of each other. Implement only one of them and make the other call it
        //     appropriately.
        bool operator!=(const iterator& iter) const;

      private:
        friend class queue;
        // Constructor for iterators (provided). You must NOT call it
        // directly. Use `getIteratorAt` instead.
        iterator(const queue& q, size_t index) : q(q), index(index)
        {
        }
        const queue& q;  // A reference to the iterator's queue
        size_t index;    // The index into the queue data
    };

    // begin
    // Returns an iterator pointing to the location of the first element
    // in the queue.
    iterator begin() const;

    // end
    // Returns an iterator pointing to the location immediately following
    // the last element in the queue.
    // NOTE: You must never try to access this location. You must only use
    //    this iterator in comparison to another iterator, to determine if
    //    that other iterator has reached the end of the queue.
    iterator end() const;

    // FRIENDS
    friend bool operator==(const queue& q1, const queue& q2);
    friend bool operator!=(const queue& q1, const queue& q2);
    friend std::ostream& operator<<(std::ostream& out, const queue& q);

  private:
    size_type capacity;  // Current queue capacity (array length)
    value_type* data;    // Circular array in the heap
    size_type first;     // Index of item at front of the queue
    size_type last;      // Index of item at rear of the queue
    size_type count;     // Number of items currently in the queue

    // next_index
    // private function for helping to move a circular array index forward
    // Precondition: 0 <= i < capacity
    // Postcondition: Returns the next index, possibly looping around to the
    //    beginning of the array.
    size_type next_index(size_type i) const;

    // copy_values
    // private function for copying the values from the queue into a provided array
    // Precondition: The array has enough space for count + 1 values.
    // Postcondition: The first 0 through count - 1 entries in the array contain
    //     copies of the queue elements, in same correct order.
    void copy_values(value_type arr[]) const;

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
    void ensure_capacity();

    // getIteratorAt (provided)
    // private function that creates an iterator for the queue at a particular index.
    // Precondition: index is a valid location into the queue's elements, or it is the
    //      location immediately preceding the last valid location.
    iterator getIteratorAt(size_type index) const;

};  // end of class definition

// NON-MEMBER FUNCTIONS (FRIENDS)

// equivalence operator, checks for logical equivalence of q1 and q2
// Postcondition: Returns true if
//       a) q1 and q2 are equal in length, and
//       b) q1 and q2 have equivalent values and the same ordering;
//    otherwise, returns false.
//  Example 1. The queues <a, b, c> and <a, b, c> are equivalent.
//  Example 2. The queues <a, b, c> and <c, a, b> are not equivalent.
//  Example 3. The queues <a, b> and <a, b, c> are not equivalent.
bool operator==(const queue& q1, const queue& q2);

// inequivalence operator
// Postcondition: Returns false if q1 == q2; otherwise, returns true.
bool operator!=(const queue& q1, const queue& q2);

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
std::ostream& operator<<(std::ostream& out, const queue& q);

}  // namespace cs223_lab5

#endif
