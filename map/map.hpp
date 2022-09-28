#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include "../utilities/utilities.hpp"
#include "../iterator/red_black_tree_iterator.hpp"
#include "../iterator/reverse_iterator.hpp"
#include "../RBTree/red_black_tree.hpp"

namespace ft
{
    template<class Key, class T, class Compare = ft::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
    class map
    {
    public:
        typedef Key                                                             key_type;
        typedef T                                                               mapped_type;
        typedef ft::pair<const Key, T>                                          value_type;
        typedef Compare                                                         key_compare;
        typedef Allocator                                                       allocator_type;
        typedef typename allocator_type::reference                              reference;
        typedef typename allocator_type::const_reference                        const_reference;
        typedef typename allocator_type::pointer                                pointer;
        typedef typename allocator_type::const_pointer                          const_pointer;
        typedef ft::red_black_tree_iterator<value_type>                         iterator;
        typedef ft::red_black_tree_iterator<const value_type>                   const_iterator;
        typedef ft::reverse_iterator<iterator>                                  reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>                            const_reverse_iterator;
        typedef typename ft::iterator_traits<iterator>::difference_type         difference_type;
        typedef difference_type                                                 size_type;

        typedef typename ft::pair_compare<key_type, mapped_type, key_compare>   value_compare;
        typedef typename Allocator::template rebind<node<value_type> >::other   node_allocator_type;
        typedef red_black_tree<value_type, value_compare, node_allocator_type>  tree_type;
        typedef typename ft::node<value_type>                                   *node_pointer;

        explicit    map(const key_compare &comparator = key_compare(),
                        const allocator_type &allocator = allocator_type())
        {
            _allocator = allocator;
            _root_child = _tree.create_node(value_type());
            _key_compare = comparator;
        }

        template<class Iter>
        map(Iter first, Iter last, const key_compare &comparator = key_compare(),
            const allocator_type &allocator = allocator_type())
        {
            _allocator = allocator;
            _root_child = _tree.create_node(value_type());
            _key_compare = comparator;
            insert(first, last);
        }

        ~map()
        {
            _tree.clear(&_root_child->parent);
            _tree.clear(&_root_child);
        }

        map(const map &other_map)
        {
            _allocator = other_map._allocator;
            _root_child = _tree.create_node(value_type());
            _key_compare = other_map._key_compare;
            *this = other_map;
        }

        map     &operator=(const map &other_map)
        {
            if (this != &other_map)
            {
                clear();
                _allocator = other_map._allocator;
                _key_compare = other_map._key_compare;
                _value_compare = other_map._value_compare;
                insert(other_map.begin(), other_map.end());
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


        mapped_type &operator[](const key_type &key)
        {
            _size += _tree.insert(&_root_child->parent,_tree.create_node(bind_pair(key)));
            node_pointer  p = _tree.find_node(_root_child->parent, bind_pair(key));
            return p->value.second;
        }

        ft::pair<iterator, bool>    insert(const value_type &value)
        {
            bool    result = _tree.insert(&_root_child->parent, _tree.create_node(value));
            _size += result;
            return ft::pair<iterator, bool>(iterator(_root_child, _tree.find_node(_root_child->parent, value)), result);
        }

        iterator  insert(iterator, const value_type &value)
        {
            _size += _tree.insert(&_root_child->parent, _tree.create_node(value));
            return iterator(_root_child, _tree.find_node(_root_child->parent, value));
        }

        template<class Iter>
        void      insert(Iter first, Iter last)
        {
            for (; first != last; ++first)
                insert(*first);
        }


        void    erase(iterator position)
        {
            _size -= _tree.erase(&_root_child->parent, *position);
        }

        size_type   erase(const key_type &key)
        {
            bool result = _tree.erase(&_root_child->parent, bind_pair(key));
            _size -= result;
            return result;
        }

        void    erase(iterator first, iterator last)
        {
            while (first != last)
                erase(first++);
        }

        void    swap(map &other_map)
        {
            ft::swap(other_map._tree, _tree);
            ft::swap(other_map._allocator, _allocator);
            ft::swap(other_map._root_child, _root_child);
            ft::swap(other_map._key_compare, _key_compare);
            ft::swap(other_map._value_compare, _value_compare);
            ft::swap(other_map._size, _size);
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
            return _value_compare;
        }

        iterator        find(const key_type &key)
        {
            return iterator(_root_child, _tree.find_node(_root_child->parent, bind_pair(key)));
        }

        const_iterator  find(const key_type &key) const
        {
            return const_iterator(_root_child, _tree.find_node(_root_child->parent, bind_pair(key)));
        }

        size_type       count(const key_type &key) const
        {
            return _tree.find_node(_root_child->parent, bind_pair(key)) ? 1 : 0;
        }

        mapped_type         &at(const key_type& key)
        {
            iterator    it = find(key);
            if ((*it).second)
                return (*it).second;
            throw std::out_of_range("ERROR: container does not have an element with the specified key");
        }

        const mapped_type   &at(const key_type& key) const
        {
            const_iterator    it = find(key);
            if ((*it).second)
                return (*it).second;
            throw std::out_of_range("ERROR: container does not have an element with the specified key");
        }

        iterator        lower_bound(const key_type &key)
        {
            return iterator(_root_child, _tree.lower(_root_child->parent, bind_pair(key)));
        }

        const_iterator  lower_bound(const key_type &key) const
        {
            return const_iterator(_root_child, _tree.lower(_root_child->parent, bind_pair(key)));
        }

        iterator        upper_bound(const key_type &key)
        {
            node_pointer tmp = _tree.lower(_root_child->parent, bind_pair(key));
            iterator it(_root_child, tmp);
            if (tmp && tmp->value.first == key)
                ++it;
            return it;
        }

        const_iterator  upper_bound(const key_type &key) const
        {
            node_pointer tmp = _tree.lower(_root_child->parent, bind_pair(key));
            const_iterator it(_root_child, tmp);
            if (tmp && tmp->value.first == key)
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
        size_type 			_size;
        allocator_type 		_allocator;
        key_compare 		_key_compare;
        value_compare 		_value_compare;
        tree_type 			_tree;
        node_pointer 		_root_child;


        value_type  bind_pair(const Key &key)
        {
            return ft::make_pair(key, mapped_type());
        }

        value_type  bind_pair(const Key &key) const
        {
            return ft::make_pair(key, mapped_type());
        }
    };

    template <class Key, class T, class Compare, class Allocator>
    bool    operator==(const map<Key, T, Compare, Allocator> &map1, const map<Key, T, Compare, Allocator> &map2)
    {
        return map1.size() == map2.size() && ft::equal(map1.begin(), map1.end(), map2.begin()) &&
            ft::equal(map2.begin(), map2.end(), map1.begin());
    }

    template <class Key, class T, class Compare, class Allocator>
    bool    operator!=(const map<Key, T, Compare, Allocator> &map1, const map<Key, T, Compare, Allocator> &map2)
    {
        return !(map1 == map2);
    }

    template <class Key, class T, class Compare, class Allocator>
    bool    operator<(const map<Key, T, Compare, Allocator> &map1, const map<Key, T, Compare, Allocator> &map2)
    {
        return ft::lexicographical_compare(map1.begin(), map1.end(), map2.begin(), map2.end()) && map1 != map2;
    }

    template <class Key, class T, class Compare, class Allocator>
    bool    operator>(const map<Key, T, Compare, Allocator> &map1, const map<Key, T, Compare, Allocator> &map2)
    {
        return map2 < map1;
    }

    template <class Key, class T, class Compare, class Allocator>
    bool    operator<=(const map<Key, T, Compare, Allocator> &map1, const map<Key, T, Compare, Allocator> &map2)
    {
        return map1 < map2 || map1 == map2;
    }

    template <class Key, class T, class Compare, class Allocator>
    bool    operator>=(const map<Key, T, Compare, Allocator> &map1, const map<Key, T, Compare, Allocator> &map2)
    {
        return map1 > map2 || map1 == map2;
    }

    template <class Key, class T, class Compare, class Allocator>
    void    swap(map<Key, T, Compare, Allocator> &map1, map<Key, T, Compare, Allocator> &map2)
    {
        map1.swap(map2);
    }
}

#endif