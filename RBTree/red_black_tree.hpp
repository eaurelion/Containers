#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include <memory>
#include "../utilities/less.hpp"
#include "../iterator/red_black_tree_iterator.hpp"

namespace ft
{
    template<class T, class Compare = ft::less<T>, class Allocator = std::allocator<T> >
    class red_black_tree
    {
    public:
        typedef T                                   value_type;
        typedef Compare                             key_compare;
        typedef Allocator                           allocator_type;
        typedef typename allocator_type::size_type  size_type;
        typedef typename allocator_type::pointer    node_pointer;
        
        node_pointer  create_node(value_type node)
        {
            node_pointer  new_node = _allocator.allocate(1);

            _allocator.construct(new_node, node);
            return new_node;
        }
        
        void    delete_node(node_pointer node)
        {
            if (node)
            {
                _allocator.destroy(node);
                _allocator.deallocate(node, 1);
            }
        }
        
        void    swap_color(node_pointer node)
        {
            bool    color = node->isBlack;

            node->isBlack = node->right->isBlack;
            node->right->isBlack = color;
            node->left->isBlack = color;
        }
        
        node_pointer min_node(node_pointer node) const
        {
            if (node)
                while (node->left)
                    node = node->left;
            return node;
        }
        
        node_pointer max_node(node_pointer node) const
        {
            if (node)
                while (node->right)
                    node = node->right;
            return node;
        }
        
        node_pointer  find_node(node_pointer node, value_type key) const
        {
            if (node)
            {
                if (_compare(node->value, key))
                    return find_node(node->right, key);
                else if (_compare(key, node->value))
                    return find_node(node->left, key);
            }
            return node;
        }
        
        node_pointer  lower(node_pointer root, value_type key) const
        {
            node_pointer node = 0;

            while (root)
            {
                if (_compare(root->value, key))
                    root = root->right;
                else
                {
                    if (root->left)
                    {
                        node = lower(root->left, key);
                        if (node)
                            root = node;
                        break ;
                    }
                    else
                        break ;
                }
            }
            return root;
        }
        
        void    clear(node_pointer *root)
        {
            if (!(*root))
                return;
            if (*root)
            {
                if ((*root)->left)
                    clear(&((*root)->left));
                if ((*root)->right)
                    clear(&((*root)->right));
                delete_node(*root);
            }
            *root = 0;
        }
        
        size_type   max_size() const
        {
            return _allocator.max_size();
        }
        
        void        insert_balance(node_pointer *root, node_pointer node)
        {
            node_pointer  parent;
            node_pointer  grand;
            node_pointer  tmp;

            while (node)
            {
                parent = node->parent;
                grand = 0;
                tmp = parent;
                if (parent)
                {
                    grand = parent->parent;
                    if (node->isBlack == false)
                    {
                        if (parent->isBlack == true)
                            node = parent;
                        else if (grand)
                        {
                            if (grand->left && grand->left->isBlack == false &&
                                grand->right && grand->right->isBlack == false)
                            {
                                swap_color(grand);
                                node = grand;
                            }
                            else if (grand->right == parent)
                            {
                                if (parent->left == node)
                                {
                                    rotate_right(parent, root);
                                    parent = node;
                                }
                                if (parent->right == node)
                                    rotate_left(grand, root);
                                node = parent->parent;
                            }
                            else
                            {
                                if (parent->right == node)
                                {
                                    rotate_left(parent, root);
                                    parent = node;
                                }
                                if (parent->left == node)
                                    rotate_right(grand, root);
                                node = parent->parent;
                            }
                        }
                    }
                    else
                        node = parent;
                }
                else
                {
                    node->isBlack = true;
                    node = node->parent;
                }
            }
        }
        
        bool        insert(node_pointer *root, node_pointer new_node)
        {
            if (!(*root))
             {
                *root = new_node;
                new_node->isBlack = true;
            }
            else
            {
                node_pointer tmp = *root;
                while (tmp)
                {
                    if (!_compare(tmp->value, new_node->value) && !_compare(new_node->value, tmp->value))
                    {
                        if (tmp != new_node)
                            delete_node(new_node);
                        return false;
                    }
                    else if (_compare(new_node->value, tmp->value))
                    {
                        if (tmp->left)
                            tmp = tmp->left;
                        else
                        {
                            tmp->left = new_node;
                            new_node->parent = tmp;
                            break;
                        }
                    }
                    else
                    {
                        if (tmp->right)
                            tmp = tmp->right;
                        else
                        {
                            tmp->right = new_node;
                            new_node->parent = tmp;
                            break;
                        }
                    }
                }
            }
            insert_balance(root, new_node);
            return true;
        }
        
        void        pointers_swap(node_pointer remove, node_pointer replace)
        {
            if (remove->parent)
            {
                if (remove->parent->left == remove)
                    remove->parent->left = replace;
                else
                    remove->parent->right = replace;
            }
            replace->parent = remove->parent;
            if (remove->left)
            {
                remove->left->parent = replace;
            }
            replace->left = remove->left;
            if (remove->right)
            {
                remove->right->parent = replace;
            }
            replace->right = remove->right;
            replace->isBlack = remove->isBlack;
        }
        
        bool        erase(node_pointer *root, value_type key)
        {
            node_pointer remove = find_node(*root, key);

            if (remove)
            {
                node_pointer replace = 0;
                if (remove->left)
                    replace = erase_left(remove, root);
                else if (remove->right)
                    replace = erase_right(remove, root);
                else
                    erase_not_child(remove, root);
                if (replace)
                    pointers_swap(remove, replace);
                if (remove == *root)
                {
                    if (replace)
                        *root = replace;
                    else
                        *root = 0;
                }
                delete_node(remove);
                return true;
            }
            return false;
        }

        node_pointer    erase_left(node_pointer node, node_pointer *root)
        {
            node_pointer replace = max_node(node->left);

            if (replace)
            {
                if (replace == node->left)
                {
                    node->left = replace->left;
                    if (replace->left)
                        replace->left->parent = node;
                }
                else
                {
                    replace->parent->right = replace->left;
                    if (replace->left)
                        replace->left->parent = replace->parent;
                }
                if (replace->isBlack == true)
                {
                    if (replace->left && replace->left->isBlack == false)
                        replace->left->isBlack = true;
                    erase_balance(root, replace->parent);
                }
            }
            return replace;
        }

        node_pointer    erase_right(node_pointer node, node_pointer *root)
        {
            node_pointer replace = min_node(node->right);

            if (replace)
            {
                if (replace == node->right)
                {
                    node->right = replace->right;
                    if (replace->right)
                        replace->right->parent = node;
                }
                else
                {
                    replace->parent->left = replace->right;
                    if (replace->right)
                        replace->right->parent = replace->parent;
                }
                if (replace->isBlack == true)
                {
                    if (replace->right && replace->right->isBlack == false)
                        replace->right->isBlack = true;
                    erase_balance(root, replace->parent);
                }
            }
            return replace;
        }

        node_pointer    erase_not_child(node_pointer node, node_pointer *root)
        {
            node_pointer replace = node;

            if (replace && replace->parent)
            {
                if (replace->parent->right == replace)
                    replace->parent->right = 0;
                else
                    replace->parent->left = 0;
                if (replace->isBlack == true)
                {
                    if (replace->right && replace->right->isBlack == false)
                        replace->right->isBlack = true;
                    erase_balance(root, replace->parent);
                }
            }
            return replace;
        }

        void            erase_balance(node_pointer *root, node_pointer node)
        {
            node_pointer right;
            node_pointer left;
            node_pointer brother;

            while (node != *root && node->isBlack)
            {
                brother = node->right;
                if (brother)
                {
                    right = brother->right;
                    left = brother->left;
                    if ((right || left) && (!right || right->isBlack == true) &&
                        (!left || left->isBlack == true))
                    {
                        if (brother->isBlack == true)
                        {
                            brother->isBlack = false;
                            node->isBlack = true;
                            rotate_left(node, root);
                        }
                        else
                            node = node->parent;
                    }
                    else if (right && brother->isBlack == true)
                    {
                        if (left && left->isBlack == false &&
                            right->isBlack == true)
                        {
                            rotate_right(brother, root);
                            right = brother;
                            brother = left;
                        }
                        if (right->isBlack == false &&
                            (!left || left->isBlack == true || !node->left))
                            rotate_left(node, root);
                        else
                            node = node->parent;
                    }
                    else if (brother->isBlack == true &&
                             node->isBlack == false)
                    {
                        node->isBlack = true;
                        brother->isBlack = false;
                        node = node->parent;
                    }
                    else
                        node = node->parent;
                }
                else
                    break;
            }
        }

        void        rotate_left(node_pointer node, node_pointer *root)
        {
            node_pointer right = node->right;
            right->parent = node->parent;

            if (right->parent)
            {
                if (right->parent->right == node)
                    right->parent->right = right;
                else
                    right->parent->left = right;
            }
            node->parent = right;
            node->right = right->left;
            if (node->right)
            {
                if (node->right->parent == right)
                    node->right->parent = node;
                else
                    node->right->parent = node;
            }
            right->left = node;
            bool color = node->isBlack;
            node->isBlack = right->isBlack;
            right->isBlack = color;
            if (!right->parent)
                *root = right;
        }

        void        rotate_right(node_pointer node, node_pointer *root)
        {
            node_pointer left = node->left;
            left->parent = node->parent;

            if (left->parent)
            {
                if (left->parent->left == node)
                    left->parent->left = left;
                else
                    left->parent->right = left;
            }
            node->parent = left;
            node->left = left->right;
            if (node->left)
            {
                if (node->left->parent == left)
                    node->left->parent = node;
                else
                    node->left->parent = node;
            }
            left->right = node;
            node->isBlack = false;
            left->isBlack = true;
            if (!left->parent)
                *root = left;
        }

    private:
        allocator_type  _allocator;
        key_compare     _compare;
    };
}

#endif