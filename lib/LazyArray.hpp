#pragma once

#include <cstddef>           // std::ptrdiff_t, std::size_t
#include <functional>        // std::function
#include <initializer_list>  // std::initializer_list
#include <iostream>          // std::cout, std::endl
#include <iterator>          // std::random_access_iterator_tag
#include <limits>            // std::numeric_limits::max()
#include <stdexcept>         // std::runtime_error
#include <type_traits>       // std::is_arithmetic
#include <utility>           // std::move
#include <vector>            // std::vector

/*
 * This 'container' was created to aid with Project Euler problems. The author
 * saw that the use of a lazy evaluated array would prove very useful for some
 * problems. Implements an 'array' that is similar to Haskell's lazy array
 * implementation where just a range or equation is stored for the array, and
 * numbers are generated on the fly when accessed. Currently only polynomials to
 * the nth degree are supported, but this should cover all reasonable
 * applications.
 * Support as an STL compatible container is planned
 */

template <class T>
class LazyArray {
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    std::function<T(T)> m_func;
    /*
     * Even though this container is theoretically infinite in size, there does
     * need to be a max value to stop at for iterators. If this isn't explicitly
     * set through .setEnd(T), things that use .end() for traversing the
     * container will keep going for a very, very long time (with some overflows
     * thrown in the mix).
     */
    T m_end{std::numeric_limits<T>::max()};
    // By default, this container will begin at zero and count up by 1 to m_end
    T m_begin{0};

    T m_increment{1};

   public:
    LazyArray() {
        static_assert(std::is_arithmetic<T>::value,
                      "Arithmetic value required for this container");
    }

    /*
     * Constructor from a function that returns type T and accepts T as
     * a parameter.
     */
    LazyArray(std::function<T(T)> func) { m_func = func; }

    /*
     * Copy constructor
     */
    LazyArray(const LazyArray& lz) : m_func{lz.m_func} {}

    /*
     * Move constructor
     */
    LazyArray(LazyArray&& lz) noexcept : m_func{std::move(lz.m_func)} {}

    /*
     * Copy assignment
     */
    LazyArray& operator=(const LazyArray& other) {
        m_func = other.m_func;
        return *this;
    }

    /*
     * Move assignment
     */
    LazyArray& operator=(LazyArray&& other) {
        m_func = std::move(other.m_func);
        return *this;
    }

    /*
     * Function assignment
     */
    LazyArray& operator=(std::function<T(T)>&& func) {
        m_func = func;
        return *this;
    }

    // Access functions

    // No bounds checking
    T operator[](const T I) const { return this->valueAt(I); }

    // Bounds checking
    T at(const T I) const {
        if ((I >= m_end) || (I < m_begin)) throw std::out_of_range("");

        return this->valueAt(I);
    }

    T valueAt(const T I) const { return m_func(I); }

    size_type size() const noexcept { return m_end - m_begin; }

    void swap(LazyArray<T>& other) {
        std::swap(this->m_func, other.m_func);
        std::swap(this->m_begin, other.m_begin);
        std::swap(this->m_end, other.m_end);
    }

    T getEnd() const noexcept { return m_end; }

    // Reset max to default maximum
    void setEnd() noexcept { m_end = std::numeric_limits<T>::max(); }
    void setEnd(T num) noexcept { m_end = num; }
    void setBegin(T num) noexcept { m_begin = num; }
    void setIncrement(T num) noexcept { m_increment = num; };

    std::vector<T> toVector() {
        std::vector<T> V;
        for (const auto i : *this) V.push_back(i);

        return V;
    }

    class iterator : public std::iterator<std::random_access_iterator_tag, T> {
        T m_position;
        LazyArray* m_parent{nullptr};

        friend class LazyArray;

       public:
        // http://www.cplusplus.com/reference/iterator/RandomAccessIterator/
        // Is default-constructible, copy-constructible, copy-assignable and
        // destructible default constructible
        iterator() : m_position{0} {}

        // Copy constructible
        iterator(const iterator& itr) {
            m_position = itr.m_position;
            m_parent = itr.m_parent;
        }

        // Copy assignable
        iterator& operator=(const iterator& itr) {
            m_position = itr.m_position;
            m_parent = itr.m_parent;
            return *this;
        }

        // Can be compared for equivalence using the equality/inequality
        // operators equality
        bool operator==(const iterator& rhs) {
            return ((m_position == rhs.m_position) &&
                    (m_parent == rhs.m_parent));
        }

        // inequality
        bool operator!=(const iterator& rhs) { return !(*this == rhs); }

        // Can be dereferenced as an rvalue (if in a dereferenceable state).
        T operator*() { return m_parent->at(m_position); }

        // ???: operator -> is required so that iterator->member is valid
        // but is this ever used?

        // Can be incremented (if in a dereferenceable state).
        // prefix increment
        iterator& operator++() {
            //++m_position;
            m_position += m_parent->m_increment;
            return *this;
        }

        // postfix increment
        iterator operator++(int) {
            iterator t = *this;
            ++*this;
            return t;
        }

        // Can be decremented (if a dereferenceable iterator value precedes
        // it). prefix decrement
        iterator& operator--() {
            m_position -= m_parent->m_increment;
            return *this;
        }

        // postfix decrement
        iterator operator--(int) {
            iterator t = *this;
            --*this;
            return t;
        }

        // Supports the arithmetic operators + and - between an iterator and
        // an integer value, or subtracting an iterator from another. add
        // integer
        iterator operator+(const difference_type n) {
            m_position += n;
            return *this;
        }

        // subtract integer
        iterator operator-(const difference_type n) {
            m_position -= n;
            return *this;
        }

        // subtract iterators
        difference_type operator-(const iterator& other) {
            return m_position - other.m_position;
        }

        // Can be compared with inequality relational operators (<, >, <=
        // and
        // >=).
        bool operator<(const iterator& rhs) {
            return m_position < rhs.m_position;
        }
        bool operator>(const iterator& rhs) {
            return rhs.m_position < m_position;
        }
        bool operator<=(const iterator& rhs) { return !(*this > rhs); }
        bool operator>=(const iterator& rhs) { return !(*this < rhs); }

        // Supports compound assignment operations += and -=
        iterator& operator+=(const size_type n) {
            m_position += n;
            return *this;
        }

        iterator& operator-=(const size_type n) {
            m_position -= n;
            return *this;
        }

        // Supports the offset dereference operator ([])
        T operator[](const difference_type t) { return *((*this) + t); }

        // Lvalues are swappable.
        void swap(iterator& lhs, iterator& rhs) {
            std::swap(lhs.m_position, rhs.m_position);
            std::swap(lhs.m_parent, rhs.m_parent);
        }

    };  // class iterator

    iterator begin() {
        LazyArray<T>::iterator itr;
        itr.m_parent = this;
        itr.m_position = m_begin;
        return itr;
    }

    iterator end() {
        LazyArray<T>::iterator itr;
        itr.m_parent = this;
        itr.m_position = m_end;
        return itr;
    }

};  // class LazyArray
