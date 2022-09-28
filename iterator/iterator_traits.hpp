#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

#include <iostream>

namespace ft {
    template<class Category, class T, class Distance = std::ptrdiff_t,
            class Pointer = T*, class Reference = T&>
    struct iterator
    {
      typedef Category  iterator_category;
      typedef T         value_type;
      typedef Distance  difference_type;
      typedef Pointer   pointer;
      typedef Reference reference;
    };

    template<class Iter>
    struct iterator_traits
     {
        typedef typename Iter::iterator_category    iterator_category;
        typedef typename Iter::value_type           value_type;
        typedef typename Iter::difference_type      difference_type;
        typedef typename Iter::pointer              pointer;
        typedef typename Iter::reference            reference;
     };

    template<class T>
    struct iterator_traits<T*>
    {
        typedef std::random_access_iterator_tag iterator_category;
        typedef T                               value_type;
        typedef ptrdiff_t                       difference_type;
        typedef T                               *pointer;
        typedef T                               &reference;
    };

    template<class InputIterator>
    typename ft::iterator_traits<InputIterator>::difference_type
                distance(InputIterator first, InputIterator last)
    {
        typename ft::iterator_traits<InputIterator>::difference_type distance = 0;
        while (first != last)
        {
            ++distance;
            ++first;
        }
        return distance;
    }
}

#endif
