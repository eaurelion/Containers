#ifndef LESS_HPP
#define LESS_HPP

namespace ft
{
    template <class lhs_type, class rhs_type, class res_type>
    struct less_function
    {
        typedef lhs_type     left_argument_type;
        typedef rhs_type     right_argument_type;
        typedef res_type     result_type;
    };

    template <class T>
    struct less : less_function<T, T, bool>
    {
        bool    operator()(const T &lhs, const T &rhs) const
        {
            return lhs < rhs;
        }
    };
}

#endif
