#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft
{
    template<typename T>
    class random_access_iterator : ft::iterator<std::random_access_iterator_tag, T>
    {
    public:
        typedef typename ft::iterator<std::random_access_iterator_tag, T>   rait;
        typedef typename rait::iterator_category                            iterator_category;
        typedef typename rait::value_type                                   value_type;
        typedef typename rait::difference_type                              difference_type;
        typedef T                                                           *pointer;
        typedef T                                                           &reference;
        typedef pointer                                                     iterator_type;

        random_access_iterator() {}

        ~random_access_iterator() {}

        random_access_iterator(pointer elem) : _elem(elem) {}

        random_access_iterator(const random_access_iterator &src)
        {
            *this = src;
        }

        random_access_iterator  &operator=(const random_access_iterator &src)
        {
            if (this != &src)
                _elem = src._elem;
            return *this;
        }

        reference   &operator*()
        {
            return *_elem;
        }

        pointer     operator->()
        {
            return _elem;
        }

        random_access_iterator  operator+(difference_type t) const
        {
            return _elem + t;
        }

        random_access_iterator  &operator++()
        {
            ++_elem;
            return *this;
        }

        random_access_iterator  operator++(int)
        {
            random_access_iterator  tmp = *this;
            ++(*this);
            return tmp;
        }

        random_access_iterator  operator+=(difference_type t)
        {
            _elem += t;
            return *this;
        }

        random_access_iterator  operator-(difference_type t) const
        {
            return _elem - t;
        }

        random_access_iterator      &operator--()
        {
            --_elem;
            return *this;
        }

        random_access_iterator      operator--(int)
        {
            random_access_iterator  tmp = *this;
            --(*this);
            return tmp;
        }

        random_access_iterator  operator-=(difference_type t)
        {
            _elem -= t;
            return *this;
        }

        reference   operator[](difference_type t) const
        {
            return *this + t;
        }

        operator    random_access_iterator<const T>() const
        {
            return (random_access_iterator<T>(_elem));
        }

        pointer     base() const
        {
            return _elem;
        }

    private:
        pointer _elem;
    };

    template<class Iter>
    bool    operator==(const random_access_iterator<Iter> &lhs, const random_access_iterator<Iter> &rhs)
    {
        return (lhs.base() == rhs.base());
    }

    template<class Iter>
    bool    operator!=(const random_access_iterator<Iter> &lhs, const random_access_iterator<Iter> &rhs)
    {
        return (lhs.base() != rhs.base());
    }

    template<class Iter>
    bool    operator>(const random_access_iterator<Iter> &lhs, const random_access_iterator<Iter> &rhs)
    {
        return (lhs.base() > rhs.base());
    }

    template<class Iter>
    bool    operator>=(const random_access_iterator<Iter> &lhs, const random_access_iterator<Iter> &rhs)
    {
        return (lhs.base() >= rhs.base());
    }

    template<class Iter>
    bool    operator<(const random_access_iterator<Iter> &lhs, const random_access_iterator<Iter> &rhs)
    {
        return (lhs.base() < rhs.base());
    }

    template<class Iter>
    bool    operator<=(const random_access_iterator<Iter> &lhs, const random_access_iterator<Iter> &rhs)
    {
        return (lhs.base() <= rhs.base());
    }

    template<class Iter>
    random_access_iterator<Iter>    operator+(typename random_access_iterator<Iter>::difference_type t,
            const random_access_iterator<Iter> &it)
    {
        return (it + t);
    }

    template<class Iter>
    typename random_access_iterator<Iter>::difference_type  operator-(const random_access_iterator<Iter> &lhs,
            const random_access_iterator<Iter> &rhs)
    {
        return lhs.base() - rhs.base();
    }
}

#endif
