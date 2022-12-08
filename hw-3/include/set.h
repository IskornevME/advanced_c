#pragma once // NOLINT

#include <memory>
#include <initializer_list>
#include <stdio.h>
#include <iostream>


template <class T>
class Set {
    class BaseNode;
    public:
        class iterator {
            public:
                friend class Set;

                iterator();
                iterator(const iterator &);
                iterator(iterator &&);

                iterator &operator=(const iterator &);
                iterator &operator=(iterator &&);

                bool operator==(const iterator &) const;
                bool operator!=(const iterator &) const;

                iterator &operator++();
                iterator operator++(int);

                iterator &operator--();
                iterator operator--(int);

                const T &operator*() const;
                const T *operator->() const;

            private:
                const BaseNode *_cur = nullptr;

                iterator(const BaseNode *n);
        };

        friend class iterator;

        Set();

        template <class InputIt>
        Set(InputIt first, InputIt last);
        Set(std::initializer_list<T> l);
        Set(const Set &rhs);
        ~Set();

        Set &operator=(const Set &rhs);

        iterator begin() const;
        iterator end() const;

        void insert(const T &key);
        void erase(const T &key);

        size_t size() const;
        bool empty() const;

        iterator find(const T &key) const;
        iterator lower_bound(const T &key) const;

        void print_tree() const;

    private:
        struct BaseNode {
            BaseNode *left = nullptr;
            BaseNode *right = nullptr;
            BaseNode *next = nullptr;
            BaseNode *prev = nullptr;
            int length = 1;
        };

        struct Node : BaseNode {
            T data;

            Node(const T &key) : data(key) {}
        };

        BaseNode *_root;
        size_t _size;

        BaseNode _quasi_last;

        void _delete(BaseNode *n);
        void _insert(BaseNode *&n, const T &key);
        void _set_length(BaseNode *n);
        int _get_balance(BaseNode *n) const;
        void _balance(BaseNode *&n);
        void _erase(BaseNode *&n, const T &key, BaseNode *p);
        void _swap(BaseNode *n1, BaseNode *p1, BaseNode *n2, BaseNode *p2);
        void _print_tree(BaseNode *n, int offset) const;
};


template <class T>
Set<T>::iterator::iterator() = default;


template <class T>
Set<T>::iterator::iterator(const iterator &) = default;


template <class T>
Set<T>::iterator::iterator(iterator &&) = default;


template <class T>
typename Set<T>::iterator &Set<T>::iterator::operator=(const iterator &) = default;


template <class T>
typename Set<T>::iterator &Set<T>::iterator::operator=(iterator &&) = default;


template <class T>
bool Set<T>::iterator::operator==(const iterator &rhs) const {
    return _cur == rhs._cur;
}


template <class T>
bool Set<T>::iterator::operator!=(const iterator &rhs) const {
    return _cur != rhs._cur;
}

template <class T>
typename Set<T>::iterator &Set<T>::iterator::operator++() {
    _cur = _cur->next;
    return *this;
}


template <class T>
typename Set<T>::iterator Set<T>::iterator::operator++(int) {
    iterator tmp = *this;
    ++(*this);
    return tmp;
}


template <class T>
typename Set<T>::iterator &Set<T>::iterator::operator--() {
    _cur = _cur->prev;
    return *this;
}


template <class T>
typename Set<T>::iterator Set<T>::iterator::operator--(int) {
    iterator tmp = *this;
    --(*this);
    return tmp;
}


template <class T>
const T &Set<T>::iterator::operator*() const {
    return static_cast<const Node *>(_cur)->data;
}


template <class T>
const T *Set<T>::iterator::operator->() const {
    return &**this;
}


template <class T>
Set<T>::iterator::iterator(const BaseNode *n)
    : _cur(n)
{}


template <class T>
Set<T>::Set()
    : _root(nullptr)
    , _size(0) {

    _quasi_last.next = _quasi_last.prev = &_quasi_last;
}


template <class T>
template <class InputIt>
Set<T>::Set(InputIt first, InputIt last)
    : _root(nullptr)
    , _size(0) {

    _quasi_last.next = _quasi_last.prev = &_quasi_last;

    for (InputIt it = first; it != last; ++it) {
        insert(*it);
    }
}


template <class T>
Set<T>::Set(std::initializer_list<T> l)
    : _root(nullptr)
    , _size(0) {

    _quasi_last.next = _quasi_last.prev = &_quasi_last;

    for (const T &x : l) {
        insert(x);
    }
}


template <class T>
Set<T>::Set(const Set &rhs)
    : _root(nullptr)
    , _size(0) {

    _quasi_last.next = _quasi_last.prev = &_quasi_last;

    for (const T &x : rhs) {
        insert(x);
    }
}


template <class T>
Set<T>::~Set() {
    _delete(_root);
}


template <class T>
void Set<T>::_delete(BaseNode *n) {
    if (n == nullptr) {
        return;
    }

    _delete(n->left);
    _delete(n->right);

    delete static_cast<Node *>(n);
}


template <class T>
Set<T> &Set<T>::operator=(const Set &rhs) {
    if (this == &rhs) {
        return *this;
    }

    if (rhs.empty()) {
        _delete(_root);
        _root = nullptr;
        _size = 0;
        _quasi_last.next = _quasi_last.prev = &_quasi_last;
        return *this;
    }

    Set tmp{ rhs };

    _delete(_root);

    _root = tmp._root;
    _size = tmp._size;

    BaseNode *a = tmp._quasi_last.next;
    BaseNode *b = tmp._quasi_last.prev;

    _quasi_last.next = a;
    _quasi_last.prev = b;
    a->prev = b->next = &_quasi_last;

    tmp._root = nullptr;

    return *this;
}


template <class T>
typename Set<T>::iterator Set<T>::begin() const {
    return iterator(_quasi_last.next);
}


template <class T>
typename Set<T>::iterator Set<T>::end() const {
    return iterator(&_quasi_last);
}


template <class T>
void Set<T>::insert(const T &key) {
    if (_root == nullptr) {
        _root = new Node(key);
        _root->next = &_quasi_last;
        _root->prev = &_quasi_last;
        _quasi_last.next = _quasi_last.prev = _root;
        _size++;
    } else {
        _insert(_root, key);
    }
}


template <class T>
void Set<T>::_insert(BaseNode *&n, const T &key) {
    // Node *cur = n;

    // if (cur == nullptr) {
    //     n = create_node(key);
    //     return;
    // }
    // if (cur->data == key) {
    //     return;
    // } else if (cur->data < key) {
    //     _insert(cur->right, key);
    // } else {
    //     _insert(cur->left, key);
    // }

    T &data = static_cast<Node *>(n)->data;

    // if (data == key) {
    //     return;
    // }

    if (data < key) {
        if (n->right != nullptr) {
            _insert(n->right, key);
        } else {
            BaseNode *a = new Node(key);
            BaseNode *x = n;
            BaseNode *y = n->next;

            n->right = a;

            x->next = a;
            a->prev = x;
            a->next = y;
            y->prev = a;

            _size++;
        }
        // _set_length(n);
        // _balance(n->right);
    } else if (key < data) {
        if (n->left != nullptr) {
            _insert(n->left, key);
        } else {
            BaseNode *a = new Node(key);
            BaseNode *x = n->prev;
            BaseNode *y = n;

            n->left = a;

            x->next = a;
            a->prev = x;
            a->next = y;
            y->prev = a;

            _size++;
        }
        // _set_length(n);
        // _balance(n->left);
    } else {
        return;
    }

    _set_length(n);
    _balance(n);
}


template <class T>
void Set<T>::_set_length(BaseNode *n) {
    if (n == nullptr)
        return;

    if (n->right != nullptr && n->left != nullptr) {
        n->length = std::max(n->left->length, n->right->length) + 1;
    } else if (n->right != nullptr) {
        n->length = n->right->length + 1;
    } else if (n->left != nullptr) {
        n->length = n->left->length + 1;
    } else {
        n->length = 1;
    }
}


template <class T>
int Set<T>::_get_balance(BaseNode *n) const {
    if (n == nullptr)
        return 0;

    if (n->right != nullptr && n->left != nullptr) {
        return n->right->length - n->left->length;
    } else if (n->right != nullptr) {
        return n->right->length;
    } else if (n->left != nullptr) {
        return -n->left->length;
    } else {
        return 0;
    }
}


template <class T>
void Set<T>::_balance(BaseNode *&n) {
    if (n == nullptr)
        return;

    BaseNode *cur = n;

    if (_get_balance(cur) == -2) {
        BaseNode *b = cur->left;
        if (_get_balance(b) <= 0) {
            n = b;
            BaseNode *o = b->right;
            b->right = cur;
            cur->left = o;

            _set_length(cur);
            _set_length(b);
        } else {
            BaseNode *c = b->right;
            n = c;
            cur->left = c->right;
            b->right = c->left;
            c->left = b;
            c->right = cur;

            _set_length(b);
            _set_length(cur);
            _set_length(c);
        }
    } else if (_get_balance(cur) == 2) {
        BaseNode *b = cur->right;

        if (_get_balance(b) >= 0) {
            n = b;
            BaseNode *o = b->left;
            b->left = cur;
            cur->right = o;
            _set_length(cur);
            _set_length(b);
        } else {
            BaseNode *c = b->left;
            n = c;
            cur->right = c->left;
            b->left = c->right;
            c->right = b;
            c->left = cur;

            _set_length(b);
            _set_length(cur);
            _set_length(c);
        }
    }
}


template <class T>
void Set<T>::erase(const T &key) {
    _erase(_root, key, nullptr);
}


template <class T>
void Set<T>::_swap(BaseNode *n1, BaseNode *p1, BaseNode *n2, BaseNode *p2) {
    if (p2 == nullptr || p1 == n2) {
        _swap(n2, p2, n1, p1);
        return;
    }

    if (p2 == n1) {
        bool b = (p1 != nullptr) && (p1->left == n1);
        if (n1->right == n2) {
            BaseNode *a = n1->left;
            BaseNode *b = n2->left;
            BaseNode *c = n2->right;

            n2->left = a;
            n2->right = n1;
            n1->left = b;
            n1->right = c;
        } else {
            BaseNode *a = n2->left;
            BaseNode *b = n2->right;
            BaseNode *c = n1->right;

            n1->left = a;
            n1->right = b;
            n2->left = n1;
            n2->right = c;
        }
        if (p1 == nullptr) {
            _root = n2;
        } else {
            (b ? p1->left : p1->right) = n2;
        }
    } else {
        BaseNode *l1 = n1->left;
        BaseNode *r1 = n1->right;

        BaseNode *l2 = n2->left;
        BaseNode *r2 = n2->right;

        bool b1 = (p1 != nullptr) && (p1->left == n1);
        bool b2 = (p2->left == n2);

        // if (p1 && p1->left != n1 && p1->right != n1) {
        //     printf("NOT parent of n1\n");
        // }

        // if (p2 && p2->left != n2 && p2->right != n2) {
        //     printf("NOT parent of n2\n");
        // }

        if (p1 == nullptr) {
            _root = n2;
        } else {
            (b1 ? p1->left : p1->right) = n2;
        }

        (b2 ? p2->left : p2->right) = n1;

        n2->left = l1;
        n2->right = r1;

        n1->left = l2;
        n1->right = r2;
    }
}


template <class T>
void Set<T>::_erase(BaseNode *&n, const T &key, BaseNode *p) {
    BaseNode *cur = n;

    if (cur == nullptr) {
        return;
    }

    T &data = static_cast<Node *>(n)->data;

    if (key < data) {
        _erase(cur->left, key, cur);
        _set_length(cur);
    } else if (data < key) {
        _erase(cur->right, key, cur);
        _set_length(cur);
    } else {
        if (cur->left == nullptr) {
            n = cur->right;

            _set_length(n);

            BaseNode *x = cur->prev;
            BaseNode *y = cur->next;
            x->next = y;
            y->prev = x;

            _size--;
            delete cur;
            return;
        }

        if (cur->right == nullptr) {
            n = cur->left;

            _set_length(n);

            BaseNode *x = cur->prev;
            BaseNode *y = cur->next;
            x->next = y;
            y->prev = x;

            _size--;
            delete cur;
            return;
        }
        if (_get_balance(cur) > 0) {
            BaseNode *closest_parent = cur;
            BaseNode *&closest = cur->right;
            while (closest->left != nullptr) {
                closest_parent = closest;
                closest = closest->left;
            }
            _swap(cur, p, closest, closest_parent);
            _erase(n->right, key, n);
            _set_length(n);
            return;
        } else {
            BaseNode *closest_parent = cur;
            BaseNode *&closest = cur->left;
            while (closest->right != nullptr) {
                closest_parent = closest;
                closest = closest->right;
            }
            _swap(cur, p, closest, closest_parent);
            _erase(n->left, key, n);
            _set_length(n);
            return;
        }
        // if (_get_balance(cur) > 0) {
            // BaseNode *closest_parent = cur;
            // BaseNode *&closest = cur->right;
            // // BaseNode *&closest = cur->next->next->left;
            // while (closest->left != nullptr) {
            //     closest_parent = closest;
            //     closest = closest->left;
            // }
            // // BaseNode *tmp = closest;
            // print_tree();
            // _swap(cur, p, closest, closest_parent);
            // print_tree();
            // // static_cast<Node *>(cur)->data = static_cast<Node *>(closest)->data;

            // // printf("..%d\n", data);
            // // printf("..%d\n", static_cast<Node *>(closest_parent)->data);
            // // printf("parent..%d\n", static_cast<Node *>(p)->data);
            // _erase(n->right, key, n);
            // // _erase(cur, key, p);
            // _set_length(n);
            // return;
        //
        // else {
        //     BaseNode *closest_parent = cur;
        //     BaseNode *&closest = cur->left;
        //     while ()
        //     for (; (*closest)->right; closest = &((*closest)->right))
        //         ;
        //     cur->key = (*closest)->key;
        //     cur->data = (*closest)->data;
        //     removeFromTree(&(cur->left), (*closest)->key);
        //     _set_length(cur);
        //     return cur->length;
        // }
    }
    // if (key < data) {
    //     _erase(cur->left, key, cur);
    //     _set_length(cur);
    // } else {
    //     _erase(cur->right, key, cur);
    //     _set_length(cur);
    // }
    _balance(n);
}


template <class T>
void Set<T>::print_tree() const {
    _print_tree(_root, 0);
    std::cout << "\n\n";
}


template <class T>
void Set<T>::_print_tree(BaseNode *n, int offset) const {
    if (n == nullptr) {
        return;
    }

    _print_tree(n->right, offset + 1);

    for (int i = 0; i < offset; i++) {
        std::cout << "    ";
    }
    std::cout << static_cast<Node *>(n)->data << '\n';

    _print_tree(n->left, offset + 1);
}


template <class T>
size_t Set<T>::size() const {
    return _size;
}


template <class T>
bool Set<T>::empty() const {
    return (_size == 0);
}


template <class T>
typename Set<T>::iterator Set<T>::find(const T &key) const {
    BaseNode *n = _root;

    while (n != nullptr) {
        const T &data = static_cast<Node *>(n)->data;

        if (key < data) {
            n = n->left;
        } else if (data < key) {
            n = n->right;
        } else {
            return iterator(n);
        }
    }

    return end();
}


template <class T>
typename Set<T>::iterator Set<T>::lower_bound(const T &key) const {
    BaseNode *n = _root;
    BaseNode *candidate = nullptr;

    while (n != nullptr) {
        const T &data = static_cast<Node *>(n)->data;

        if (key < data) {
            candidate = n;
            n = n->left;
        } else if (data < key) {
            n = n->right;
        } else {
            return iterator(n);
        }
    }

    return (candidate == nullptr) ? end() : iterator(candidate);
}
