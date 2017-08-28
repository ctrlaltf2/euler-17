#pragma once

#include <cmath>            // std::pow
#include <cstddef>          // std::ptrdiff_t, std::size_t
#include <initializer_list> // std::initializer_list
#include <iostream>         // std::cout, std::endl
#include <iterator>         // std::random_access_iterator_tag
#include <limits>           // std::numeric_limits::max()
#include <stdexcept>        // std::runtime_error
#include <type_traits>      // std::is_arithmetic
#include <utility>          // std::move
#include <vector>           // std::vector

/*
 * This 'container' was created to aid with Project Euler problems. The author saw that the use of a
 * lazy evaluated array would prove very useful for some problems.
 * Implements an 'array' that is similar to Haskell's lazy array implementation where just a range
 * or equation is stored for the array, and numbers are generated on the fly when accessed.
 * Currently only polynomials to the nth degree are supported, but this should cover all reasonable
 * applications.
 * Support as an STL compatible container is planned
 */

template<class T>
class LazyArray {
    std::vector<T> m_coefficients;

    /*
     * Even though this container is theoretically infinite in size, there does need to be a max value
     * to stop at for iterators. If this isn't explicitly set through .setEnd(T), things that use .end() for traversing the container will keep going for a very, very long time (with some overflows thrown in the mix).
     */
    T m_end{std::numeric_limits<T>::max()};
    // By default, this container will begin at zero and count up by 1 to m_end
    T m_begin{0};
public:
    LazyArray() {
        static_assert(std::is_arithmetic<T>::value, "Arithmetic value required for this container");
    }

    /*
     * Constructed from an initializer list of arithmetic value T. Each value in the initalizer list
     * corresponds to a coefficient of a polynomial. If LazyArray LZ{1, 6, 4, -3, 7} is constructed,
     * the 'equation' of the container would be 1x^4 + 6x^3 + 4x^2 - 3x + 7.
     */
    LazyArray(std::initializer_list<T> l) {
        LazyArray();
        m_coefficients = l;
    }

    LazyArray(const LazyArray& lz) { m_coefficients = lz.m_coefficients; }

    LazyArray(LazyArray&& lz) noexcept { m_coefficients = std::move(lz.m_coefficients); }

    // Assignment Operators
    LazyArray& operator= (LazyArray& other) {
       m_coefficients = other.m_coefficients;
       return *this;
    }

    LazyArray& operator= (std::initializer_list<T>&& l) {
       m_coefficients = l;
       return *this;
    }

    // Access functions

    // No bounds checking
    T operator[] (const std::size_t I) {
        return this->valueAt(I);
    }

    T at (const std::size_t I) {
        if((I >= m_end) || (I < m_begin))
            throw std::out_of_range("");

        return this->valueAt(I);
    }

    T valueAt(const std::size_t I) {
        auto ritr = m_coefficients.rbegin();

        std::size_t xpow = 0;
        T finalVal{0};

        for(;ritr != m_coefficients.rend();++ritr, ++xpow)
            finalVal += *ritr * pow(I, xpow);

        return finalVal;
    }


    std::size_t size() const noexcept { return m_end - m_begin; }

    void swap(LazyArray& other) { std::swap(this->m_coefficients, other.m_coefficients); }

    void print_coefficients() const noexcept {
        for(const auto& i : m_coefficients) {
            std::cout << i << ' ';
        }
        std::cout << std::endl;
    }

    T getEnd() const noexcept { return m_end; }

    // Reset max to default maximum
    void setEnd() noexcept { m_end = std::numeric_limits<T>::max(); }
    void setEnd(T num) noexcept { m_end = num; }
    void setBegin(T num) noexcept { m_begin = num; }

    std::vector<T> toVector() {
        std::vector<T> V;
        for(auto i : *this)
            V.push_back(i);

        return V;
    }

    class iterator {
        typedef std::random_access_iterator_tag iterator_category;
        typedef T               value_type;
        typedef T*              pointer;
        typedef T&              reference;
        typedef std::size_t     size_type;
        typedef std::ptrdiff_t  difference_type;

        size_type m_position;
        LazyArray* m_parent{nullptr};

        friend class LazyArray;
    public:

        // http://www.cplusplus.com/reference/iterator/RandomAccessIterator/
        // Is default-constructible, copy-constructible, copy-assignable and destructible
        // default constructible
        iterator() : m_position{0} { }

        // Copy constructible
        iterator(const iterator& itr) {
            m_position = itr.m_position;
            m_parent = itr.m_parent;
        }

        // Copy assignable
        iterator& operator= (const iterator& itr) {
            m_position = itr.m_position;
            m_parent = itr.m_parent;
            return *this;
        }

        // Can be compared for equivalence using the equality/inequality operators
        // equality
        bool operator== (const iterator& rhs) {
            return ((m_position == rhs.m_position) && (m_parent == rhs.m_parent));
        }

        // inequality
        bool operator!= (const iterator& rhs) { return !(*this == rhs); }

        // Can be dereferenced as an rvalue (if in a dereferenceable state).
        T operator* () { return m_parent->at(m_position); }

        // ???: operator -> is required so that iterator->member is valid but is this ever used?

        // Can be incremented (if in a dereferenceable state).
        // prefix increment
        iterator& operator++() {
            ++m_position;
            return *this;
        }

        // postfix increment
        iterator operator++ (int) {
            iterator t = *this;
            ++*this;
            return t;
        }

        // Can be decremented (if a dereferenceable iterator value precedes it).
        // prefix decrement
        iterator& operator--() {
            --m_position;
            return *this;
        }

        // postfix decrement
        iterator operator--(int) {
            iterator t = *this;
            --*this;
            return t;
        }

        // Supports the arithmetic operators + and - between an iterator and an integer value, or subtracting an iterator from another.
        // add integer
        iterator operator+ (const difference_type n) {
            m_position += n;
            return *this;
        }

        // subtract integer
        iterator operator- (const difference_type n) {
            m_position -= n;
            return *this;
        }

        // subtract iterators
        difference_type operator- (const iterator& other) { return m_position - other.m_position; }

        // Can be compared with inequality relational operators (<, >, <= and >=).
        bool operator< (const iterator& rhs) { return m_position < rhs.m_position; }
        bool operator> (const iterator& rhs) { return rhs.m_position < m_position; }
        bool operator<=(const iterator& rhs) { return !(*this > rhs); }
        bool operator>=(const iterator& rhs) { return !(*this < rhs); }

        // Supports compound assignment operations += and -=
        iterator& operator+= (const size_type n) {
            m_position += n;
            return *this;
        }

        iterator& operator-= (const size_type n) {
            m_position -= n;
            return *this;
        }

        // Supports the offset dereference operator ([])
        T operator[] (const difference_type t) { return *((*this) + t); }

        // Lvalues are swappable.
        void swap(iterator& lhs, iterator& rhs) {
            std::swap(lhs.m_position, rhs.m_position);
            std::swap(lhs.m_parent, rhs.m_parent);
        }


    }; // class iterator

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

}; // class LazyArray

// Specialization for iterator_traits because somehow typedefs inside the iterator just isn't enough

namespace std {
    // generated using the python file included in lib/
    template<>
    struct iterator_traits<LazyArray<bool>::iterator> {
        typedef std::random_access_iterator_tag iterator_category;
        typedef bool               value_type;
        typedef bool*              pointer;
        typedef bool&              reference;
        typedef std::size_t     size_type;
        typedef std::ptrdiff_t  difference_type;
    };
    template<>
    struct iterator_traits<LazyArray<char>::iterator> {
        typedef std::random_access_iterator_tag iterator_category;
        typedef char               value_type;
        typedef char*              pointer;
        typedef char&              reference;
        typedef std::size_t     size_type;
        typedef std::ptrdiff_t  difference_type;
    };
    template<>
    struct iterator_traits<LazyArray<char16_t>::iterator> {
        typedef std::random_access_iterator_tag iterator_category;
        typedef char16_t               value_type;
        typedef char16_t*              pointer;
        typedef char16_t&              reference;
        typedef std::size_t     size_type;
        typedef std::ptrdiff_t  difference_type;
    };
    template<>
    struct iterator_traits<LazyArray<char32_t>::iterator> {
        typedef std::random_access_iterator_tag iterator_category;
        typedef char32_t               value_type;
        typedef char32_t*              pointer;
        typedef char32_t&              reference;
        typedef std::size_t     size_type;
        typedef std::ptrdiff_t  difference_type;
    };
    template<>
    struct iterator_traits<LazyArray<wchar_t>::iterator> {
        typedef std::random_access_iterator_tag iterator_category;
        typedef wchar_t               value_type;
        typedef wchar_t*              pointer;
        typedef wchar_t&              reference;
        typedef std::size_t     size_type;
        typedef std::ptrdiff_t  difference_type;
    };
    template<>
    struct iterator_traits<LazyArray<signed char>::iterator> {
        typedef std::random_access_iterator_tag iterator_category;
        typedef signed char               value_type;
        typedef signed char*              pointer;
        typedef signed char&              reference;
        typedef std::size_t     size_type;
        typedef std::ptrdiff_t  difference_type;
    };
    template<>
    struct iterator_traits<LazyArray<short int>::iterator> {
        typedef std::random_access_iterator_tag iterator_category;
        typedef short int               value_type;
        typedef short int*              pointer;
        typedef short int&              reference;
        typedef std::size_t     size_type;
        typedef std::ptrdiff_t  difference_type;
    };
    template<>
    struct iterator_traits<LazyArray<int>::iterator> {
        typedef std::random_access_iterator_tag iterator_category;
        typedef int               value_type;
        typedef int*              pointer;
        typedef int&              reference;
        typedef std::size_t     size_type;
        typedef std::ptrdiff_t  difference_type;
    };
    template<>
    struct iterator_traits<LazyArray<long int>::iterator> {
        typedef std::random_access_iterator_tag iterator_category;
        typedef long int               value_type;
        typedef long int*              pointer;
        typedef long int&              reference;
        typedef std::size_t     size_type;
        typedef std::ptrdiff_t  difference_type;
    };
    template<>
    struct iterator_traits<LazyArray<long long int>::iterator> {
        typedef std::random_access_iterator_tag iterator_category;
        typedef long long int               value_type;
        typedef long long int*              pointer;
        typedef long long int&              reference;
        typedef std::size_t     size_type;
        typedef std::ptrdiff_t  difference_type;
    };
    template<>
    struct iterator_traits<LazyArray<unsigned char>::iterator> {
        typedef std::random_access_iterator_tag iterator_category;
        typedef unsigned char               value_type;
        typedef unsigned char*              pointer;
        typedef unsigned char&              reference;
        typedef std::size_t     size_type;
        typedef std::ptrdiff_t  difference_type;
    };
    template<>
    struct iterator_traits<LazyArray<unsigned short int>::iterator> {
        typedef std::random_access_iterator_tag iterator_category;
        typedef unsigned short int               value_type;
        typedef unsigned short int*              pointer;
        typedef unsigned short int&              reference;
        typedef std::size_t     size_type;
        typedef std::ptrdiff_t  difference_type;
    };
    template<>
    struct iterator_traits<LazyArray<unsigned int>::iterator> {
        typedef std::random_access_iterator_tag iterator_category;
        typedef unsigned int               value_type;
        typedef unsigned int*              pointer;
        typedef unsigned int&              reference;
        typedef std::size_t     size_type;
        typedef std::ptrdiff_t  difference_type;
    };
    template<>
    struct iterator_traits<LazyArray<unsigned long int>::iterator> {
        typedef std::random_access_iterator_tag iterator_category;
        typedef unsigned long int               value_type;
        typedef unsigned long int*              pointer;
        typedef unsigned long int&              reference;
        typedef std::size_t     size_type;
        typedef std::ptrdiff_t  difference_type;
    };
    template<>
    struct iterator_traits<LazyArray<unsigned long long int>::iterator> {
        typedef std::random_access_iterator_tag iterator_category;
        typedef unsigned long long int               value_type;
        typedef unsigned long long int*              pointer;
        typedef unsigned long long int&              reference;
        typedef std::size_t     size_type;
        typedef std::ptrdiff_t  difference_type;
    };
    template<>
    struct iterator_traits<LazyArray<float>::iterator> {
        typedef std::random_access_iterator_tag iterator_category;
        typedef float               value_type;
        typedef float*              pointer;
        typedef float&              reference;
        typedef std::size_t     size_type;
        typedef std::ptrdiff_t  difference_type;
    };
    template<>
    struct iterator_traits<LazyArray<double>::iterator> {
        typedef std::random_access_iterator_tag iterator_category;
        typedef double               value_type;
        typedef double*              pointer;
        typedef double&              reference;
        typedef std::size_t     size_type;
        typedef std::ptrdiff_t  difference_type;
    };
    template<>
    struct iterator_traits<LazyArray<long double>::iterator> {
        typedef std::random_access_iterator_tag iterator_category;
        typedef long double               value_type;
        typedef long double*              pointer;
        typedef long double&              reference;
        typedef std::size_t     size_type;
        typedef std::ptrdiff_t  difference_type;
    };
}
