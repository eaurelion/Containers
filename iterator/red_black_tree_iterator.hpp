#ifndef RED_BLACK_TREE_ITERATOR_HPP
#define RED_BLACK_TREE_ITERATOR_HPP


#include "iterator_traits.hpp"
#include "../utilities/switch_const.hpp"

namespace ft
{
    template <class T>
    struct node
    {
        T       value;
        node*   left;
        node*   right;
        node*   parent;
        bool    isBlack;

        node() : value(T()), left(0), right(0), parent(0), isBlack(false) {}

        node(const T &copyValue) : value(copyValue), left(0), right(0), parent(0), isBlack(false) {}

        node    &operator=(const node   &n)
        {
            if (this != &n)
            {
                value = n.value;
                left = n.left;
                right = n.right;
                parent = n.parent;
                isBlack = n.isBlack;
            }
            return *this;
        }
    };


    template <typename T>
    class   red_black_tree_iterator
    {
    public:
        typedef typename ft::iterator<std::bidirectional_iterator_tag, T>	rbt_iterator;
        typedef typename rbt_iterator::iterator_category 					iterator_category;
        typedef typename rbt_iterator::value_type 							value_type;
        typedef typename rbt_iterator::difference_type 						difference_type;
        typedef T 															*pointer;
        typedef T 															&reference;
        typedef pointer														iterator_type;
        typedef ft::node<typename ft::switch_const<T>::type> 		        *node_pointer;

        red_black_tree_iterator(): _root(nullptr), _node(nullptr) {}

        explicit red_black_tree_iterator(const node_pointer &root, const node_pointer &node)
                : _root(root), _node(node) {}

        red_black_tree_iterator(const red_black_tree_iterator &it)
        {
            *this = it;
        }

        ~red_black_tree_iterator(){}

        red_black_tree_iterator &operator=(const red_black_tree_iterator &it)
        {
            if (this != &it)
            {
                _root = it._root;
                _node = it._node;
            }
            return *this;
        }

        reference   &operator*()
        {
            return _node->value;
        }

        reference   &operator*() const
        {
            return _node->value;
        }

        pointer     operator->() const
        {
            return &(_node->value);
        }

        red_black_tree_iterator    &operator++()
        {
            if (!_node)
                return *this;
            else if (_node->right)
                _node = min_node(_node->right);
            else if (_node == max_node(_root->parent))
                _node = 0;
            else
            {
                while (_node->parent->right == _node)
                    _node = _node->parent;
                _node = _node->parent;
            }
            return *this;
        }

        red_black_tree_iterator     operator++(int)
        {
            red_black_tree_iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        red_black_tree_iterator &operator--()
        {
            if (!_node)
                _node = max_node(_root->parent);
            else if (_node->left)
                _node = max_node(_node->left);
            else
            {
                while (_node->parent->left == _node)
                    _node = _node->parent;
                _node = _node->parent;
            }
            return *this;
        }

        red_black_tree_iterator operator--(int)
        {
            red_black_tree_iterator tmp = *this;
            --(*this);
            return tmp;
        }

        bool    operator==(const red_black_tree_iterator &it) const
        {
            return it._node == _node;
        }

        bool    operator!=(const red_black_tree_iterator &it) const
        {
            return it._node != _node;
        }

        operator    red_black_tree_iterator<const T>() const
        {
            return red_black_tree_iterator<const T>(_root, _node);
        }

    private:
        node_pointer _root;
        node_pointer _node;

        node_pointer  min_node(node_pointer node) const
        {
            if (node)
                while (node->left)
                    node = node->left;
            return node;
        }

        node_pointer  max_node(node_pointer node) const
        {
            if (node)
                while (node->right)
                    node = node->right;
            return node;
        }
    };
}

#endif