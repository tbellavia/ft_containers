#ifndef TRAITS_HPP
#define TRAITS_HPP

namespace ft {
    template<bool B, class T = void>
    struct enable_if { };

    template<class T>
    struct enable_if<true, T> {
        typedef T type;
    };

    template<class T, T v>
    struct integral_constant {
        static const T                  value = v;
        typedef T                       value_type;
        typedef integral_constant<T, v> type;
    };

    /**
     * True type
     *
     * Define the value true within the true_type struct.
     *
     */
    struct true_type : ft::integral_constant<bool, true> {};

    /**
     * False type
     *
     * Define the value false within the false_type struct.
     *
     */
    struct false_type : ft::integral_constant<bool, false> {};

    /**
     * Iterator traits
     *
     * Define a traits for iterators.
     *
     */
    template<typename Iterator>
    struct iterator_traits {
        typedef typename Iterator::iterator_category iterator_category;
        typedef typename Iterator::value_type value_type;
        typedef typename Iterator::difference_type difference_type;
        typedef typename Iterator::pointer pointer;
        typedef typename Iterator::reference reference;
    };

    template<typename T>
    struct iterator_traits<T *> {
        typedef std::random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef T *pointer;
        typedef T &reference;
    };

    template<typename T>
    struct iterator_traits<const T *> {
        typedef std::random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef const T *pointer;
        typedef const T &reference;
    };

    /**
     * Is iterator
     *
     * Define a way to check if it is iterator
     */
    template<typename T>
    struct is_iterator : public ft::false_type {};

    template<typename T>
    struct remove_cv
    { typedef T type; };

    template<typename T>
    struct remove_cv<const T>
    { typedef T type; };

    template<typename T>
    struct remove_cv<volatile T>
    { typedef T type; };

    template<typename T>
    struct remove_cv<const volatile T>
    { typedef T type; };

    /**
     * Is integral
     *
     * Checks whether T is an integral type.
     *
     * Provides the member constant value which is equal to true, if T is the type
     * bool, char, char8_t (since C++20), char16_t, char32_t, wchar_t, short, int, long, long long,
     * or any implementation-defined extended integer types, including any signed, unsigned,
     * and cv-qualified variants. Otherwise, value is equal to false.
     */
    template<typename>
    struct _is_integral_helper : public ft::false_type {};

    template<>
    struct _is_integral_helper<bool> : public ft::true_type {};

    template<>
    struct _is_integral_helper<char> : public ft::true_type {};

    template<>
    struct _is_integral_helper<wchar_t> : public ft::true_type {};

    template<>
    struct _is_integral_helper<signed char> : public ft::true_type {};

    template<>
    struct _is_integral_helper<short int> : public ft::true_type {};

    template<>
    struct _is_integral_helper<int> : public ft::true_type {};

    template<>
    struct _is_integral_helper<long int> : public ft::true_type {};

    template<>
    struct _is_integral_helper<long long int> : public ft::true_type {};

    template<>
    struct _is_integral_helper<unsigned char> : public ft::true_type {};

    template<>
    struct _is_integral_helper<unsigned short int> : public ft::true_type {};

    template<>
    struct _is_integral_helper<unsigned int> : public ft::true_type {};

    template<>
    struct _is_integral_helper<unsigned long int> : public ft::true_type {};

    template<>
    struct _is_integral_helper<unsigned long long int> : public ft::true_type {};

    template<typename T>
    struct is_integral : public ft::_is_integral_helper<typename ft::remove_cv<T>::type>::type {};


}

#endif /* TRAITS_HPP */
