#ifndef FT_CONTAINERS_EQUAL_HPP
#define FT_CONTAINERS_EQUAL_HPP

namespace ft
{
    template<class Iter1, class Iter2>
    bool equal(Iter1 first1, Iter1 last1, Iter2 first2)
    {
        for (; first1 != last1; first1++, first2++)
            if (*first1 != *first2)
                return false;
        return true;
    }

    template<class Iter1, class Iter2, class Predicate>
    bool equal(Iter1 first1, Iter1 last1, Iter2 first2, Predicate pred)
    {
        for (; first1 != last1; first1++, first2++)
            if (!pred(*first1, *first2))
                return false;
        return true;
    }
}

#endif
