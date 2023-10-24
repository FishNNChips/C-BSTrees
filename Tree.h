#ifndef TREE_H
#define TREE_H
template <typename T>
class Tree
{
    static_assert(std::integral<T> || std::floating_point<T>, "Template Parameter must be Numeric!!!\n");

public:
    using Tree_iterator = NODE<T> *;
    Tree_iterator root;
};

#endif