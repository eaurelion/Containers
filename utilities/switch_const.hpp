#ifndef SWITCH_CONST_HPP
#define SWITCH_CONST_HPP

namespace ft
{
    template<class T>
    struct switch_const
    {
        typedef T   type;
    };

    template<class T>
    struct switch_const<const T>
    {
        typedef T   type;
    };
}

#endif
