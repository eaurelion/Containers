#ifndef IS_INTEGRAL_HPP
#define IS_INTEGRAL_HPP

namespace ft
{
    template<typename T, bool is_integral>
    struct integral
    {
        typedef T value_type;

        static const bool value = is_integral;

        operator value_type() const
        {
            return value;
        }
    };

    template<typename T>
    struct is_integral_type: public ft::integral<T, false> {};

    template<>
    struct is_integral_type<bool>: public ft::integral<bool, true> {};

    template<>
    struct is_integral_type<char>: public ft::integral<char, true> {};

    template<>
    struct is_integral_type<char16_t>: public ft::integral<char16_t, true> {};

    template<>
    struct is_integral_type<char32_t>: public ft::integral<char32_t, true> {};

    template<>
    struct is_integral_type<wchar_t>: public ft::integral<wchar_t, true> {};

    template<>
    struct is_integral_type<signed char>: public ft::integral<signed char, true> {};

    template<>
    struct is_integral_type<unsigned char>: public ft::integral<unsigned char, true> {};

    template<>
    struct is_integral_type<int>: public ft::integral<int, true> {};

    template<>
    struct is_integral_type<short int>: public ft::integral<short int, true> {};

    template<>
    struct is_integral_type<long int>: public ft::integral<long int, true> {};

    template<>
    struct is_integral_type<long long int>: public ft::integral<long long int, true> {};

    template<>
    struct is_integral_type<unsigned int>: public ft::integral<unsigned int, true> {};

    template<>
    struct is_integral_type<unsigned short int>: public ft::integral<unsigned short int, true> {};

    template<>
    struct is_integral_type<unsigned long int>: public ft::integral<unsigned long int, true> {};

    template<>
    struct is_integral_type<unsigned long long int>: public ft::integral<unsigned long long int, true> {};

    template<typename T>
    struct is_integral: public is_integral_type<T> {};
}

#endif