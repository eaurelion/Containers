#ifndef SWAP_HPP
#define SWAP_HPP

namespace ft
{
    template<class T>
    void    swap(T &lhs, T &rhs)
    {
        T   tmp = lhs;
        lhs = rhs;
        rhs = tmp;
    }
}

#endif
