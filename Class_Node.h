#ifndef CLASS_NODE_H
#define CLASS_NODE_H
#include "Tree.h"
#include "Rb_Tree.h"

template <typename T>
class NODE
{
    friend class Tree<T>;

public:
    T value;

private:
    NODE<T> *left, *right;
    NODE() : value(0), left(nullptr), right(nullptr) {}
    NODE(T val) : value(val), left(nullptr), right(nullptr) {}
};

template <typename T>
class Rb_Tree_NODE
{
    friend class Rb_Tree<T>;

public:
    T value;
    unsigned short int color : 2;

private:
    Rb_Tree_NODE(T num, Rb_Tree_NODE *p) : value(num), left(nullptr), right(nullptr), color(Rb_Tree<T>::RED), parent(p){};
    Rb_Tree_NODE(Rb_Tree_NODE *obj) : value(obj->value), left(obj->left), right(obj->right), parent(obj->parent), color(obj->color){};
    Rb_Tree_NODE<T> *left, *right, *parent;
};

#endif