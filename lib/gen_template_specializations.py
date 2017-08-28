"""    template<>
    struct iterator_traits<LazyArray<long>::iterator> {
        typedef std::random_access_iterator_tag iterator_category;
        typedef long               value_type;
        typedef long*              pointer;
        typedef long&              reference;
        typedef std::size_t     size_type;
        typedef std::ptrdiff_t  difference_type;
    };"""


primTypes = ["bool", "char", "char16_t", "char32_t", "wchar_t", "signed char", "short int", "int", "long int", "long long int", "unsigned char", "unsigned short int", "unsigned int", "unsigned long int", "unsigned long long int", "float", "double", "long double"]

for i in primTypes:
	print("    template<>\n    struct iterator_traits<LazyArray<" + i + ">::iterator> {\n        typedef " + i + "               value_type;\n        typedef " + i + "*              pointer;\n        typedef " + i + "&              reference;\n        typedef std::size_t     size_type;\n        typedef std::ptrdiff_t  difference_type;\n    };")
