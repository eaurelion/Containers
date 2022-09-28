#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include "../iterator/random_access_iterator.hpp"
#include "../iterator/reverse_iterator.hpp"
#include "../utilities/utilities.hpp"

namespace ft
{
    template <class T, class Allocator = std::allocator<T> >
    class vector {
    public:
        typedef T                                                       value_type;
        typedef Allocator                                               allocator_type;
        typedef typename allocator_type::size_type                      size_type;
        typedef typename allocator_type::reference                      reference;
        typedef typename allocator_type::const_reference                const_reference;
        typedef typename allocator_type::pointer                        pointer;
        typedef typename allocator_type::const_pointer                  const_pointer;
        typedef ft::random_access_iterator<value_type>                  iterator;
        typedef ft::random_access_iterator<const value_type>            const_iterator;
        typedef ft::reverse_iterator<iterator>                          reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>                    const_reverse_iterator;
        typedef typename ft::iterator_traits<iterator>::difference_type difference_type;

        explicit    vector(const allocator_type &alloc = allocator_type())
        {
            _allocator = alloc;
            _data = nullptr;
            _capacity = 0;
            _size = 0;
        }

        explicit    vector(size_type size, const value_type &value = value_type(),
                           const allocator_type &alloc = allocator_type())
        {
            if (size < 0)
                throw std::bad_alloc();
            else
            {
                _allocator = alloc;
                _capacity = size;
                _size = size;

                if (size == 0)
                    _data = nullptr;
                else
                {
                    _data = _allocator.allocate(_capacity);
                    for (size_type i = 0; i < size; ++i)
                        _allocator.construct(_data + i, value);
                }
            }
        }

        template <class InputIterator>
        vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
                typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = nullptr)
        {
            _allocator = alloc;
            _size = ft::distance(first, last);
            _capacity = _size;
            _data = _allocator.allocate(_capacity);
            value_type  *data_value = _data;
            for (InputIterator it = first; it != last; it++, data_value++)
                _allocator.construct(data_value, *it);
        }

        ~vector()
        {
            for (size_type i = 0; i < _size; ++i)
                _allocator.destroy(_data + i);
            _allocator.deallocate(_data, _capacity);
        }

        vector(const vector &vec)
        {
            _allocator = vec._allocator;
            _capacity = vec._capacity;
            _size = vec._size;
            _data = _allocator.allocate(_capacity);
            for (size_type i = 0; i < _size; ++i)
                _allocator.construct(_data + i, vec[i]);
        }

        vector &operator=(const vector &vec)
        {
            if (this != &vec)
            {
                _allocator.deallocate(_data, _capacity);
                _capacity = vec._capacity;
                _size = vec._size;
                _data = _allocator.allocate(_capacity);
                for (size_type i = 0; i < _size; i++)
                    _allocator.construct(_data + i, vec[i]);
            }
            return *this;
        }

        iterator        begin()
        {
            return &_data[0];
        }

        const_iterator  begin() const
        {
            return &_data[0];
        }

        iterator        end()
        {
            return &_data[_size];
        }

        const_iterator  end() const
        {
            return &_data[_size];
        }

        reverse_iterator       rbegin()
        {
            return reverse_iterator(end());
        }

        const_reverse_iterator  rbegin() const
        {
            return reverse_iterator(end());
        }

        reverse_iterator       rend()
        {
            return reverse_iterator(begin());
        }

        const_reverse_iterator  rend() const
        {
            return reverse_iterator(begin());
        }

        size_type   size() const
        {
            return size_type(end() - begin());
        }

        size_type   max_size() const
        {
            return _allocator.max_size();
        }

        size_type   capacity() const
        {
            return _capacity;
        }

        bool    empty() const
        {
            return begin() == end();
        }

        void    resize(size_type new_size, value_type value = value_type())
        {
            if (new_size < size())
                erase(begin() + new_size, end());
            else
                insert(end(), new_size - size(), value);
        }

        void reserve(size_type size)
        {
            if (size > _capacity && size < max_size())
            {
                pointer tmp = _allocator.allocate(size);
                try
                {
                    std::uninitialized_copy(_data, _data + _size, tmp);
                }
                catch (...)
                {
                    _allocator.deallocate(tmp, size);
                    throw;
                }
                _allocator.deallocate(_data, _capacity);
                _data = tmp;
                _capacity = size;
            }
        }

        reference   operator[](size_type size)
        {
            return *(begin() + size);
        }

        const_reference operator[](size_type size) const
        {
            return *(begin() + size);
        }

        allocator_type  get_allocator() const
        {
            return _allocator;
        }

        reference       at(size_type size)
        {
            if (size < _size)
                return _data[size];
            throw std::out_of_range("ERROR: position out of range");
        }

        const_reference at(size_type size) const
        {
            if (size < _size)
                return _data[size];
            throw std::out_of_range("ERROR: position out of range");
        }

        reference   front()
        {
            return *begin();
        }

        const_reference front() const
        {
            return *begin();
        }

        reference   back()
        {
            return *(end() - 1);
        }

        const_reference back() const
        {
            return *(end() - 1);
        }

        void    assign(size_type size, const value_type &value)
        {
            clear();
            if (_capacity < size)
            {
                if (_capacity * 2 >= size)
                    reserve(_capacity * 2);
                else
                    reserve(size);
            }
            for (; _size < size; _size++)
                    _allocator.construct(_data + _size, value);
        }

        template<class InputIterator>
        void assign(InputIterator first, InputIterator last,
                    typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = nullptr)
        {
            clear();
            size_type   dist = ft::distance(first, last);

            if (_capacity < dist)
            {
                if (_capacity * 2 >= dist)
                    reserve(_capacity * 2);
                else
                    reserve(dist);
            }
            for (; first < last; first++, _size++)
                _allocator.construct(_data + _size, *first);
        }

        void    clear()
        {
            while (_size > 0)
                _allocator.destroy(_data + (--_size));
        }

        iterator    insert(iterator pos, const value_type& value)
        {
            size_type   distance = ft::distance(begin(), pos);
            if (_size < _capacity)
            {
                for (iterator it = end(); it != pos - 1; --it)
                    _allocator.construct(&(*it), *(it - 1));
                _allocator.construct(&(*pos), value);
                _size++;
            }
            else
            {
                value_type *tmp_data = (_capacity ? _allocator.allocate(_capacity * 2) : _allocator.allocate(1));
                size_type i = 0;
                for (iterator it = begin(); it != end(); ++it)
                {
                    if (it == pos)
                        _allocator.construct(tmp_data + i++, value);
                    _allocator.construct(tmp_data + i++, *it);
                    _allocator.destroy(&(*it));
                }
                size_type tmp_capacity = (_capacity ? _capacity * 2 : 1);
                _allocator.deallocate(_data,_capacity);
                _data = tmp_data;
                _size++;
                _capacity = tmp_capacity;
            }
            return begin() + distance;
        }

        void    insert(iterator pos, size_type count, const value_type& value)
        {
            if (_size + count > _capacity)
            {
                if (_size + count >= _capacity * 2)
                    _capacity = _size + count;
                else
                    _capacity *= 2;
            }
            value_type  *tmp_data = _allocator.allocate(_capacity);
            value_type  *p_tmp_data = tmp_data;
            for (int i = 0; begin() + i < pos; ++i)
            {
                _allocator.construct(p_tmp_data++, *(begin() + i));
                _allocator.destroy(&(*(begin() + i)));
            }
            for (size_type i = 0; i < count; ++i)
                _allocator.construct(p_tmp_data++, value);
            for (int i = 0; pos + i < end(); ++i)
            {
                _allocator.construct(p_tmp_data++, *(pos + i));
                _allocator.destroy(&(*(pos + i)));
            }
            _allocator.deallocate(&(*begin()), _size);
            _data = tmp_data;
            _size += count;
        }

        template< class InputIterator>
        void    insert(iterator pos, InputIterator first, InputIterator last,
                       typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = nullptr)
        {
            size_type   count = ft::distance(first, last);
            size_type   distance = ft::distance(begin(), pos);
            if (pos > end() || pos < begin())
                throw std::range_error("Error by inserting");
            value_type  *tmp_data = _allocator.allocate(count);
            try
            {
                for (size_type i = 0; i < count; ++i)
                    _allocator.construct(tmp_data + i, *first++);
            }
            catch (...)
            {
                for (size_type i = 0; tmp_data + i != 0 && i < count; ++i)
                    _allocator.destroy(tmp_data + i);
                _allocator.deallocate(tmp_data, count);
                throw std::runtime_error("Error by inserting");
            }
            if (_capacity == _size && _capacity)
                reserve(_capacity * 2);
            if (_capacity < _size + count)
                reserve(_size + count);
            for (size_type i = 0; distance + i != _size;  ++i)
            {
                _allocator.construct(_data + _size - 1 - i + count, _data[_size - 1 - i]);
                _allocator.destroy(_data + _size - i - 1);
            }
            for (size_type i = 0; i < count; ++i)
            {
                _allocator.construct(_data + distance + i, tmp_data[i]);
                _allocator.destroy(tmp_data + i);
                _size++;
            }
            _allocator.deallocate(tmp_data, count);
        }

        iterator    erase(iterator position)
        {
            size_type   count = 0;
            for (iterator it = this->begin(); it != position; ++it)
            {
                count++;
            }
            for (size_type i = 0; i < _size; ++i)
            {
                if (i == count)
                    _allocator.destroy(_data + count);
                if (i > count)
                    _allocator.construct(_data + i - 1, _data[i]);
            }
            --_size;
            return (iterator(_data + count));
        }

        iterator    erase(iterator first, iterator last)
        {
            iterator tmp = first;
            size_type distance = ft::distance(first, last);
            for ( ;tmp < end() - distance; ++tmp)
            {
                _allocator.destroy(&(*tmp));
                _allocator.construct(&(*tmp), *(tmp +  distance));
                _allocator.destroy(&(*(tmp + distance)));
            }
            _size -= distance;
            return first;
        }

        void    swap(vector &vec)
        {
            ft::swap(_data, vec._data);
            ft::swap(_size, vec._size);
            ft::swap(_capacity, vec._capacity);
        }

        void    push_back(const value_type &value)
        {
            if (!_size || _size == _capacity)
                reserve(!_size ? 1 : _capacity * 2);
            _allocator.construct(&(*end()), value);
            _size++;
        }

        void    pop_back()
        {
            if (_size)
            {
                _allocator.destroy(&(*(end() - 1)));
                _size--;
            }
        }

    private:
        allocator_type  _allocator;
        value_type      *_data;
        size_type       _capacity;
        size_type       _size;
    };

    template<class T, class Allocator>
    bool    operator==(const ft::vector<T, Allocator> &lhs, const ft::vector<T, Allocator> &rhs)
    {
        if (lhs.size() != rhs.size())
            return false;
        if (ft::equal(lhs.begin(), lhs.end(), rhs.begin()))
            return true;
        return false;
    }

    template<class T, class Allocator>
    bool    operator!=(const ft::vector<T, Allocator> &lhs, const ft::vector<T, Allocator> &rhs)
    {
        if (lhs.size() != rhs.size() || !ft::equal(lhs.begin(), lhs.end(), rhs.begin()))
            return true;
        return false;
    }

    template<class T, class Allocator>
    bool    operator<(const ft::vector<T, Allocator> &lhs, const ft::vector<T, Allocator> &rhs)
    {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template<class T, class Allocator>
    bool    operator<=(const ft::vector<T, Allocator> &lhs, const ft::vector<T, Allocator> &rhs)
    {
        return !(lhs > rhs);
    }

    template<class T, class Allocator>
    bool    operator>(const ft::vector<T, Allocator> &lhs, const ft::vector<T, Allocator> &rhs)
    {
        return ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
    }

    template<class T, class Allocator>
    bool    operator>=(const ft::vector<T, Allocator> &lhs, const ft::vector<T, Allocator> &rhs)
    {
        return !(lhs < rhs);
    }
}

#endif
