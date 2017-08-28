    template<>
    struct iterator_traits<LazyArray<bool>::iterator> {
        typedef bool               value_type;
        typedef bool*              pointer;
        typedef bool&              reference;
        typedef std::size_t     size_type;
        typedef std::ptrdiff_t  difference_type;
    };
    template<>
    struct iterator_traits<LazyArray<char>::iterator> {
        typedef char               value_type;
        typedef char*              pointer;
        typedef char&              reference;
        typedef std::size_t     size_type;
        typedef std::ptrdiff_t  difference_type;
    };
    template<>
    struct iterator_traits<LazyArray<char16_t>::iterator> {
        typedef char16_t               value_type;
        typedef char16_t*              pointer;
        typedef char16_t&              reference;
        typedef std::size_t     size_type;
        typedef std::ptrdiff_t  difference_type;
    };
    template<>
    struct iterator_traits<LazyArray<char32_t>::iterator> {
        typedef char32_t               value_type;
        typedef char32_t*              pointer;
        typedef char32_t&              reference;
        typedef std::size_t     size_type;
        typedef std::ptrdiff_t  difference_type;
    };
    template<>
    struct iterator_traits<LazyArray<wchar_t>::iterator> {
        typedef wchar_t               value_type;
        typedef wchar_t*              pointer;
        typedef wchar_t&              reference;
        typedef std::size_t     size_type;
        typedef std::ptrdiff_t  difference_type;
    };
    template<>
    struct iterator_traits<LazyArray<signed char>::iterator> {
        typedef signed char               value_type;
        typedef signed char*              pointer;
        typedef signed char&              reference;
        typedef std::size_t     size_type;
        typedef std::ptrdiff_t  difference_type;
    };
    template<>
    struct iterator_traits<LazyArray<short int>::iterator> {
        typedef short int               value_type;
        typedef short int*              pointer;
        typedef short int&              reference;
        typedef std::size_t     size_type;
        typedef std::ptrdiff_t  difference_type;
    };
    template<>
    struct iterator_traits<LazyArray<int>::iterator> {
        typedef int               value_type;
        typedef int*              pointer;
        typedef int&              reference;
        typedef std::size_t     size_type;
        typedef std::ptrdiff_t  difference_type;
    };
    template<>
    struct iterator_traits<LazyArray<long int>::iterator> {
        typedef long int               value_type;
        typedef long int*              pointer;
        typedef long int&              reference;
        typedef std::size_t     size_type;
        typedef std::ptrdiff_t  difference_type;
    };
    template<>
    struct iterator_traits<LazyArray<long long int>::iterator> {
        typedef long long int               value_type;
        typedef long long int*              pointer;
        typedef long long int&              reference;
        typedef std::size_t     size_type;
        typedef std::ptrdiff_t  difference_type;
    };
    template<>
    struct iterator_traits<LazyArray<unsigned char>::iterator> {
        typedef unsigned char               value_type;
        typedef unsigned char*              pointer;
        typedef unsigned char&              reference;
        typedef std::size_t     size_type;
        typedef std::ptrdiff_t  difference_type;
    };
    template<>
    struct iterator_traits<LazyArray<unsigned short int>::iterator> {
        typedef unsigned short int               value_type;
        typedef unsigned short int*              pointer;
        typedef unsigned short int&              reference;
        typedef std::size_t     size_type;
        typedef std::ptrdiff_t  difference_type;
    };
    template<>
    struct iterator_traits<LazyArray<unsigned int>::iterator> {
        typedef unsigned int               value_type;
        typedef unsigned int*              pointer;
        typedef unsigned int&              reference;
        typedef std::size_t     size_type;
        typedef std::ptrdiff_t  difference_type;
    };
    template<>
    struct iterator_traits<LazyArray<unsigned long int>::iterator> {
        typedef unsigned long int               value_type;
        typedef unsigned long int*              pointer;
        typedef unsigned long int&              reference;
        typedef std::size_t     size_type;
        typedef std::ptrdiff_t  difference_type;
    };
    template<>
    struct iterator_traits<LazyArray<unsigned long long int>::iterator> {
        typedef unsigned long long int               value_type;
        typedef unsigned long long int*              pointer;
        typedef unsigned long long int&              reference;
        typedef std::size_t     size_type;
        typedef std::ptrdiff_t  difference_type;
    };
    template<>
    struct iterator_traits<LazyArray<float>::iterator> {
        typedef float               value_type;
        typedef float*              pointer;
        typedef float&              reference;
        typedef std::size_t     size_type;
        typedef std::ptrdiff_t  difference_type;
    };
    template<>
    struct iterator_traits<LazyArray<double>::iterator> {
        typedef double               value_type;
        typedef double*              pointer;
        typedef double&              reference;
        typedef std::size_t     size_type;
        typedef std::ptrdiff_t  difference_type;
    };
    template<>
    struct iterator_traits<LazyArray<long double>::iterator> {
        typedef long double               value_type;
        typedef long double*              pointer;
        typedef long double&              reference;
        typedef std::size_t     size_type;
        typedef std::ptrdiff_t  difference_type;
    };
