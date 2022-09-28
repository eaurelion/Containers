#ifndef PAIR_COMPARE_HPP
#define PAIR_COMPARE_HPP

#include "less.hpp"
#include "pair.hpp"

namespace ft
{
    template <class Key, class T, class Compare = ft::less<Key> >
    class pair_compare
    {
    public:
        typedef ft::pair<const Key, T>      pair_value;
        typedef Compare                     key_compare;

        pair_compare(const key_compare &comp = key_compare()) : _comp(comp) {}

        bool    operator()(const pair_value &pair1, const pair_value &pair2) const
        {
            return _comp(pair1.first, pair2.first);
        }

    private:
        key_compare _comp;
    };
}

#endif
