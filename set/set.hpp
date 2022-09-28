#ifndef SET_HPP
#define SET_HPP

#include <memory>
#include "../utilities/utilities.hpp"
#include "../iterator/red_black_tree_iterator.hpp"
#include "../iterator/reverse_iterator.hpp"
#include "../RBTree/red_black_tree.hpp"

namespace ft
{
    template<class Key, class Compare = ft::less<Key>, class Allocator = std::allocator <Key> >
    class set
    {
    public:
        typedef Key                                                     key_type;
        typedef key_type                                                value_type;
        typedef Compare                                                 key_compare;
        typedef key_compare                                             value_compare;
        typedef Allocator                                               allocator_type;
        typedef typename allocator_type::reference                      reference;
        typedef typename allocator_type::const_reference                const_reference;
        typedef typename allocator_type::pointer                        pointer;
        typedef typename allocator_type::const_pointer                  const_pointer;
        typedef ft::red_black_tree_iterator<value_type>                 iterator;
        typedef ft::red_black_tree_iterator<const value_type>           const_iterator;
        typedef ft::reverse_iterator<iterator>                          reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>                    const_reverse_iterator;
        typedef typename ft::iterator_traits<iterator>::difference_type difference_type;
        typedef difference_type                                         size_type;

        typedef typename Allocator::template rebind<node<value_type> >::other   node_allocator_type;
        typedef red_black_tree<value_type, value_compare, node_allocator_type>  tree_type;
        typedef typename ft::node<value_type>                                   *node_pointer;

        explicit set(const key_compare &comparator = key_compare(), const allocator_type &allocator = allocator_type())
        {
            _allocator = allocator;
            _root_child = _tree.create_node(value_type());
            _key_compare = comparator;
            _size = 0;
        }

        template <class Iter>
        set(Iter first, Iter last, const key_compare &comparator = key_compare(),
                const allocator_type &allocator = allocator_type())
        {
            _allocator = allocator;
            _root_child = _tree.create_node(value_type());
            _key_compare = comparator;
            _size = 0;
            insert(first, last);
        }

        ~set()
        {
            _tree.clear(&_root_child->parent);
            _tree.clear(&_root_child);
        }

        set(const set &other_set)
        {
            _allocator = other_set._allocator;
            _root_child = _tree.create_node(value_type());
            _key_compare = other_set._key_compare;
            _size = other_set._size;
            *this = other_set;
        }

        set     &operator=(const set &other_set)
        {
            if (this != &other_set)
            {
                clear();
                _allocator = other_set._allocator;
                _key_compare = other_set._key_compare;
                insert(other_set.begin(), other_set.end());
            }
            return *this;
        }

        iterator    begin()
        {
            return iterator(_root_child, _tree.min_node(_root_child->parent));
        }

        const_iterator  begin() const
        {
            return const_iterator(_root_child, _tree.min_node(_root_child->parent));
        }

        iterator    end()
        {
            return iterator(_root_child, nullptr);
        }

        const_iterator  end() const
        {
            return const_iterator(_root_child, nullptr);
        }

        reverse_iterator    rbegin()
        {
            return reverse_iterator(end());
        }

        const_reverse_iterator  rbegin() const
        {
            return const_reverse_iterator(end());
        }

        reverse_iterator    rend()
        {
            return reverse_iterator(begin());
        }

        const_reverse_iterator  rend() const
        {
            return const_reverse_iterator(begin());
        }

        bool    empty() const
        {
            return !_size;
        }

        size_type   size() const
        {
            return _size;
        }

        size_type   max_size() const
        {
            return _tree.max_size();
        }

        ft::pair<iterator, bool>    insert(const value_type &value)
        {
            bool    result = _tree.insert(&_root_child->parent, _tree.create_node(value));
            _size += result;
            return ft::pair<iterator, bool>(iterator(_root_child, _tree.find_node(_root_child->parent, value)), result);
        }

        iterator    insert(iterator, const value_type &value)
        {
            _size += _tree.insert(&_root_child->parent, _tree.create_node(value));
            return iterator(_root_child, _tree.find_node(_root_child->parent, value));
        }

        template <class Iter>
        void    insert(Iter first, Iter last)
        {
            for (; first != last; ++first)
                insert(*first);
        }

        void        erase(iterator position)
        {
            _size -= _tree.erase(&_root_child->parent, *position);
        }

        size_type   erase(const key_type &key)
        {
            bool    result = (bool)_tree.erase(&_root_child->parent, key);
            _size -= result;
            return result;
        }

        void        erase(iterator first, iterator last)
        {
            while (first != last)
                erase(first++);
        }


        void    swap(set &other_set)
        {
            ft::swap(other_set._tree, _tree);
            ft::swap(other_set._allocator, _allocator);
            ft::swap(other_set._root_child, _root_child);
            ft::swap(other_set._key_compare, _key_compare);
            ft::swap(other_set._size, _size);
        }

        void    clear()
        {
            _tree.clear(&_root_child->parent);
            _root_child->parent = nullptr;
            _size = 0;
        }

        key_compare     key_comp() const
        {
            return _key_compare;
        }

        value_compare   value_comp() const
        {
            return _key_compare;
        }

        iterator        find(const key_type &key)
        {
            return iterator(_root_child, _tree.find_node(_root_child->parent, key));
        }

        const_iterator  find(const key_type &key) const
        {
            return const_iterator(_root_child, _tree.find_node(_root_child->parent, key));
        }

        size_type       count(const key_type &key) const
        {
            return _tree.find_node(_root_child->parent, key) ? 1 : 0;
        }

        iterator        lower_bound(const key_type &key)
        {
            return iterator(_root_child, _tree.lower(_root_child->parent, key));
        }

        const_iterator  lower_bound(const key_type &key) const
        {
            return const_iterator(_root_child, _tree.lower(_root_child->parent, key));
        }

        iterator        upper_bound(const key_type &key)
        {
            node_pointer tmp = _tree.lower(_root_child->parent, key);
            iterator it(_root_child, tmp);
            if (tmp && tmp->value == key)
                ++it;
            return it;
        }

        const_iterator  upper_bound(const key_type &key) const
        {
            node_pointer tmp = _tree.lower(_root_child->parent, key);
            const_iterator it(_root_child, tmp);
            if (tmp && tmp->value == key)
                ++it;
            return it;
        }

        ft::pair<iterator, iterator>    equal_range(const key_type &key)
        {
            return ft::make_pair(lower_bound(key), upper_bound(key));
        }

        ft::pair<const_iterator, const_iterator>    equal_range(const key_type &key) const
        {
            return ft::make_pair(lower_bound(key), upper_bound(key));
        }

        allocator_type  get_allocator() const
        {
            return _allocator;
        }

    private:
        tree_type           _tree;
        allocator_type      _allocator;
        key_compare         _key_compare;
        size_type           _size;
        node_pointer        _root_child;
    };

    template <class Key, class Compare, class Allocator>
    bool    operator==(const set<Key, Compare, Allocator> &set1, const set<Key, Compare, Allocator> &set2)
    {
        return set1.size() == set2.size() && ft::equal(set1.begin(), set1.end(), set2.begin())
               && ft::equal(set2.begin(), set2.end(), set1.begin());
    }

    template <class Key, class Compare, class Allocator>
    bool    operator!=(const set<Key, Compare, Allocator> &set1, const set<Key, Compare, Allocator> &set2)
    {
        return !(set1 == set2);
    }

    template <class Key, class Compare, class Allocator>
    bool    operator<(const set<Key, Compare, Allocator> &set1, const set<Key, Compare, Allocator> &set2)
    {
        return ft::lexicographical_compare(set1.begin(), set1.end(), set2.begin(), set2.end()) && set1 != set2;
    }

    template <class Key, class Compare, class Allocator>
    bool    operator<=(const set<Key, Compare, Allocator> &set1, const set<Key, Compare, Allocator> &set2)
    {
        return set1 < set2 || set1 == set2;
    }

    template <class Key, class Compare, class Allocator>
    bool    operator>(const set<Key, Compare, Allocator> &set1, const set<Key, Compare, Allocator> &set2)
    {
        return set2 < set1;
    }

    template <class Key, class Compare, class Allocator>
    bool    operator>=(const set<Key, Compare, Allocator> &set1, const set<Key, Compare, Allocator> &set2)
    {
        return set1 > set2 || set1 == set2;
    }

    template <class Key, class Compare, class Allocator>
    void    swap(set<Key, Compare, Allocator> &set1, set<Key, Compare, Allocator> &set2)
    {
        set1.swap(set2);
    }
}

#endif