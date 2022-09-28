#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft {
    template<typename Iter>
    class reverse_iterator
    {
    public:
        typedef Iter                                                    iterator_type;
        typedef typename ft::iterator_traits<Iter>::iterator_category   iterator_category;
        typedef typename ft::iterator_traits<Iter>::value_type          value_type;
        typedef typename ft::iterator_traits<Iter>::difference_type     difference_type;
        typedef typename ft::iterator_traits<Iter>::pointer             pointer;
        typedef typename ft::iterator_traits<Iter>::reference           reference;

        reverse_iterator() {}

        ~reverse_iterator() {}

        explicit    reverse_iterator(iterator_type elem) : _elem(elem) {}

        reverse_iterator(const reverse_iterator<Iter> &src) : _elem(src.base()) {}

        reference operator*() const
        {
            iterator_type tmp = _elem;
            return *(--tmp);
        }

        pointer operator->() const
        {
            return &(operator*());
        }

        reverse_iterator operator+(difference_type t) const
        {
            return (reverse_iterator(_elem - t));
        }

        reverse_iterator &operator++()
        {
            _elem--;
            return *this;
        }

        reverse_iterator operator++(int)
        {
            reverse_iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        reverse_iterator operator+=(difference_type t)
                {
            _elem -= t;
            return *this;
        }

        reverse_iterator operator-(difference_type t) const
        {
            return (reverse_iterator(_elem + t));
        }

        reverse_iterator &operator--()
        {
            _elem++;
            return *this;
        }

        reverse_iterator operator--(int)
        {
            reverse_iterator tmp = *this;
            --(*this);
            return tmp;
        }

        reverse_iterator operator-=(difference_type t)
        {
            _elem += t;
            return *this;
        }

        reference operator[](difference_type t) const
        {
            return *(operator+ (t));
        }

        iterator_type   base() const
        {
            return _elem;
        }

    private:
        Iter _elem;
    };

    template<class Iter>
    bool    operator==(const reverse_iterator<Iter> &lhs, const reverse_iterator<Iter> &rhs)
    {
        return lhs.base() == rhs.base();
    }

    template<class Iter>
    bool    operator!=(const reverse_iterator<Iter> &lhs, const reverse_iterator<Iter> &rhs)
    {
        return lhs.base() != rhs.base();
    }

    template<class Iter>
    bool    operator<(const reverse_iterator<Iter> &lhs, const reverse_iterator<Iter> &rhs)
    {
        return lhs.base() > rhs.base();
    }

    template<class Iter>
    bool    operator<=(const reverse_iterator<Iter> &lhs, const reverse_iterator<Iter> &rhs)
    {
        return lhs.base() >= rhs.base();
    }

    template<class Iter>
    bool    operator>(const reverse_iterator<Iter> &lhs, const reverse_iterator<Iter> &rhs)
    {
        return lhs.base() < rhs.base();
    }

    template<class Iter>
    bool    operator>=(const reverse_iterator<Iter> &lhs, const reverse_iterator<Iter> &rhs)
    {
        return lhs.base() <= rhs.base();
    }

    template<class Iter>
    reverse_iterator<Iter>  operator+(typename reverse_iterator<Iter>::difference_type t,
            const reverse_iterator<Iter> &r_it)
    {
        return r_it + t;
    }

    template<class Iter>
    typename reverse_iterator<Iter>::difference_type    operator-(const reverse_iterator<Iter> &lhs,
            const reverse_iterator<Iter> &rhs)
    {
        return lhs.base() - rhs.base();
    }
    
}

#endif
