#ifndef TREE_H
#define TREE_H

template <typename T>
class Tree
{
public:
    class NODE
    {
        NODE *left, *right;
        T value;
        NODE() : left(nullptr), right(nullptr), value(0){};
    };
};

#endif