#ifndef STACK_HPP
#define STACK_HPP

#include "../vector/vector.hpp"

namespace ft
{
    template<class T, class Container = ft::vector<T> >
    class stack
    {
    public:
        typedef T           value_type;
        typedef Container   container_type;
        typedef size_t      size_type;

    protected:
        container_type      _container;

    public:
        explicit    stack(const container_type &c = container_type())
        {
            _container = c;
        }

        ~stack() {}

        value_type  &top()
        {
            return _container.back();
        }

        const value_type    &top() const
        {
            return _container.back();
        }

        bool    empty() const
        {
            return _container.empty();
        }

        size_type   size() const
        {
            return _container.size();
        }

        void    push(const value_type &value)
        {
            _container.push_back(value);
        }

        void    pop()
        {
            _container.pop_back();
        }

        template <class TF, class ContainerF>
        friend bool operator==(const ft::stack<TF, ContainerF> &lhs, const ft::stack<TF, ContainerF> &rhs);

        template <class TF, class ContainerF>
        friend bool operator!=(const ft::stack<TF, ContainerF> &lhs, const ft::stack<TF, ContainerF> &rhs);

        template <class TF, class ContainerF>
        friend bool operator>(const ft::stack<TF, ContainerF> &lhs, const ft::stack<TF, ContainerF> &rhs);

        template <class TF, class ContainerF>
        friend bool operator>=(const ft::stack<TF, ContainerF> &lhs, const ft::stack<TF, ContainerF> &rhs);

        template <class TF, class ContainerF>
        friend bool operator<(const ft::stack<TF, ContainerF> &lhs, const ft::stack<TF, ContainerF> &rhs);

        template <class TF, class ContainerF>
        friend bool operator<=(const ft::stack<TF, ContainerF> &lhs, const ft::stack<TF, ContainerF> &rhs);
    };

    template <class TF, class ContainerF>
    bool operator==(const ft::stack<TF, ContainerF> &lhs, const ft::stack<TF, ContainerF> &rhs)
    {
        return (lhs._container == rhs._container);
    }

    template <class TF, class ContainerF>
    bool operator!=(const ft::stack<TF, ContainerF> &lhs, const ft::stack<TF, ContainerF> &rhs)
    {
        return lhs._container != rhs._container;
    }

    template <class TF, class ContainerF>
    bool operator>(const ft::stack<TF, ContainerF> &lhs, const ft::stack<TF, ContainerF> &rhs)
    {
        return lhs._container > rhs._container;
    }

    template <class TF, class ContainerF>
    bool operator>=(const ft::stack<TF, ContainerF> &lhs, const ft::stack<TF, ContainerF> &rhs)
    {
        return lhs._container >= rhs._container;
    }

    template <class TF, class ContainerF>
    bool operator<(const ft::stack<TF, ContainerF> &lhs, const ft::stack<TF, ContainerF> &rhs)
    {
        return lhs._container < rhs._container;
    }

    template <class TF, class ContainerF>
    bool operator<=(const ft::stack<TF, ContainerF> &lhs, const ft::stack<TF, ContainerF> &rhs)
    {
        return lhs._container <= rhs._container;
    }
}

#endif