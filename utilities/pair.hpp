#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft
{
    template <class Key, class Value>
    struct pair
    {
    public:
        Key         first;
        Value       second;

        pair(): first(), second() {}

        pair(const Key &_first, const Value &_second) : first(_first), second(_second) {}

        template <typename new_key, typename new_value>
        pair(const pair<new_key, new_value> &new_pair) : first(new_pair.first), second(new_pair.second) {}

        ~pair() {}

        pair    &operator=(const pair &new_pair)
        {
            if (this != &new_pair)
            {
                first = new_pair.first;
                second = new_pair.second;
            }
            return *this;
        }
    };

    template <class T_key, class T_value>
    bool    operator==(const pair<T_key, T_value> &lhs, const pair<T_key, T_value> &rhs)
    {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    }

    template <class T_key, class T_value>
    bool    operator!=(const pair<T_key, T_value> &lhs, const pair<T_key, T_value> &rhs)
    {
        return !(lhs == rhs);
    }

    template <class T_key, class T_value>
    bool    operator<(const pair<T_key, T_value> &lhs, const pair<T_key, T_value> &rhs)
    {
        return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
    }

    template <class T_key, class T_value>
    bool    operator>=(const pair<T_key, T_value> &lhs, const pair<T_key, T_value> &rhs)
    {
        return !(lhs < rhs);
    }

    template <class T_key, class T_value>
    bool    operator>(const pair<T_key, T_value> &lhs, const pair<T_key, T_value> &rhs)
    {
        return rhs < lhs;
    }

    template <class T_key, class T_value>
    bool    operator<=(const pair<T_key, T_value> &lhs, const pair<T_key, T_value> &rhs)
    {
        return !(rhs < lhs);
    }

    template <class T_key, class T_value>
    pair<T_key, T_value>    make_pair(T_key key, T_value value)
    {
        return ft::pair<T_key, T_value>(key, value);
    }
}

#endif
