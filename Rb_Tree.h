#ifndef RB_TREE_H // include guard
#define RB_TREE_H

#include <bits/stdc++.h>
#include "Tree.h"
template <typename T>
class Rb_Tree;

template <typename T>
decltype(Rb_Tree<T>::root) inorder_successor(Rb_Tree<T> &t, T value)
{
    decltype(t.root) pt = (t.searchNode(value));
    if (pt->right)
        pt = pt->right;
    while (pt->left)
        pt = pt->left;
    return pt;
}
template <typename T>
decltype(Rb_Tree<T>::root) inorder_successor(Rb_Tree<T> &&t, T value) { return inorder_successor<T>(t, value); }

template <typename T = int>
decltype(Rb_Tree<T>::root) inorder_predecessor(Rb_Tree<T> &t, T value)
{
    decltype(t.root) pt = (t.searchNode(value));
    if (pt->left)
        pt = pt->left;
    while (pt->right)
        pt = pt->right;
    return pt;
}
template <typename T>
decltype(Rb_Tree<T>::root) inorder_predecessor(Rb_Tree<T> &&t, T value) { return inorder_predecessor<T>(t, value); }

template <typename T>
class Rb_Tree:public Tree<T>
{
    static_assert(std::integral<T> || std::floating_point<T>, "Template Parameter must be Numeric!!!\n");

private:
    class NODE
    {
    public:
        NODE(T num, NODE *p) : value(num), left(nullptr), right(nullptr), color(Rb_Tree<T>::RED), parent(p){};
        NODE(NODE *obj) : value(obj->value), left(obj->left), right(obj->right), parent(obj->parent), color(obj->color){};
        T value;
        unsigned short int color : 1;
        NODE *left, *right, *parent;
    };
    // std::stack<bool> prefix_code;

public:
    // Members.
    static constexpr short RED = 0;
    static constexpr short BLACK = 1;
    static constexpr short DOUBLE_BLACK = 2;

    using Rb_Tree_iterator = NODE *;
    using Node = NODE;

    Rb_Tree_iterator root;

    // Constructors.
    Rb_Tree() : root(nullptr){}; // Create an empty RB Tree.
    Rb_Tree(T value)
    {
        root = new Node(value, nullptr);
        root->color = BLACK;
    }
    Rb_Tree(const std::vector<T> &vec) : root(nullptr) { insert(vec); }
    Rb_Tree(std::vector<T> &&vec) : root(nullptr)
    {
        for (auto &i : vec)
            insert(i);
    }
    // Create RB Tree with root node.

    void clearTree() { delete_all(root); }
    // Searching inside RB Tree.
    bool search(T &value)
    {
        return search_impl(value, root);
    }

    Rb_Tree_iterator searchNode(T value)
    {
        return search_impl(value);
    }

    bool checkColour(T &value)
    {
        Rb_Tree_iterator node = search_impl(value);
        if (node)
            return node->color;
    }

    // insertion and deletion.
    void insert(T &value)
    {
        // 1.) If tree is empty create a newnode as root node with color black.
        if (!root)
        {
            root = new Node(value, nullptr);
            root->color = BLACK;
            return;
        }
        Rb_Tree_iterator newnode, it = root;

        // 2.) If tree is not empty then, create newnode as leaf node with color RED.
        do
        {
            if (value < it->value)
            {
                if (!it->left)
                {
                    it->left = new NODE(value, it);
                    newnode = it->left;
                    break;
                }
                it = it->left;
                // prefix_code.push(0);
            }
            else if (value > it->value)
            {
                if (!it->right)
                {
                    it->right = new NODE(value, it);
                    newnode = it->right;
                    break;
                }
                it = it->right;
                // prefix_code.push(1);
            }
        } while (1);
        insertfixup(newnode);
    }
    void insert(T &&value) { insert(value); };
    void insert(std::vector<T> &vec)
    {
        for (auto &i : vec)
            insert(i);
    }
    void insert(std::vector<T> &&vec) { insert(vec); }

    void deleteNode(T &value)
    {
        Rb_Tree_iterator r = search_impl(value);
        if (!r)
        {
            std::cout << "Node with value = " << value << " not found!";
            return;
        }
        deletefixup(r);
    }
    void deleteNode(T &&value) { deleteNode(value); }
    void deleteNode(std::vector<T> &vec)
    {
        for (const auto &i : vec)
            deleteNode(i);
    }
    void deleteNode(std::vector<T> &&vec) { deleteNode(vec); }

    // Traversal methods.
    // Root , Left , Right
    void preorder_traversal(Rb_Tree_iterator it)
    {
        if (!it)
            return;

        std::cout << it->value << '(' << (it->color == BLACK ? "B" : "R") << ")\t";
        preorder_traversal(it->left);
        preorder_traversal(it->right);
    }

    // Left , Root , Right
    void inorder_traversal(Rb_Tree_iterator it)
    {
        if (!it)
            return;

        inorder_traversal(it->left);
        std::cout << it->value << '(' << (it->color == BLACK ? "B" : "R") << ")\t";
        inorder_traversal(it->right);
    }

    // Left , Right , Root
    void postorder_traversal(Rb_Tree_iterator it)
    {
        if (!it)
            return;

        postorder_traversal(it->left);
        postorder_traversal(it->right);
        std::cout << it->value << '(' << (it->color == BLACK ? "B" : "R") << ")\t";
    }

    void display_Node(Rb_Tree_iterator it)
    {
        if (!it)
        {
            std::cout << "NULL NODE\n";
            return;
        }
        std::cout << (it == root ? "Root Node details:-\n" : "Node details:-\n") << "Value = " << it->value
                  << "\nCOLOR = " << (it->color == RED ? "RED\n" : "BLACK\n")
                  << "Left = " << (it->left == nullptr ? "NULL" : std::to_string(it->left->value))
                  << "\nRight = " << (it->right == nullptr ? "NULL\n" : std::to_string(it->right->value)) << '\n';
    }

    void printHelper(Rb_Tree_iterator root, std::string indent, bool last)
    {
        if (root)
        {
            std::cout << indent;
            if (last)
            {
                std::cout << "R----";
                indent += "   ";
            }
            else
            {
                std::cout << "L----";
                indent += "|  ";
            }

            std::string c = !root->color ? "RED" : "BLACK";
            std::cout << root->value << "(" << c << ")" << '\n';
            printHelper(root->left, indent, false);
            printHelper(root->right, indent, true);
        }
    }
    void printTree()
    {
        if (root)
        {
            printHelper(this->root, "", true);
        }
    }
    // Destructor.
    // delete all nodes to avoid memory leaks.
    ~Rb_Tree()
    {
        if (root)
            printTree(), delete_all(root);
    }

private: // implementation methods.
    void delete_all(Rb_Tree_iterator root)
    {
        if (!root || !root->left && !root->right)
            return;
        delete_all(root->left);
        delete_all(root->right);
        delete root;
    };

    Rb_Tree_iterator search_impl(T &value)
    {
        // // stopping conditions.
        // if (!root)
        // {
        //     return;
        // }
        // if (root->value == value)
        //     return;

        // value < root->value ? search_impl(value, root->left) : search_impl(value, root->right); // ;)
        Rb_Tree_iterator root = this->root;
        do
        {
            if (root->value > value)
                if (root->left)
                    root = root->left;
                else
                    break;
            else if (root->value < value)
                if (root->right)
                    root = root->right;
                else
                    break;
            else
                break;
        } while (1);
        if (root->value != value)
            root = nullptr;
        return root;
    }
    void insertfixup(Rb_Tree_iterator &newnode);
    void deletefixup(Rb_Tree_iterator &p);
    void L_rotation(Rb_Tree_iterator p);
    void R_rotation(Rb_Tree_iterator p);
    inline void in_predecessor(Rb_Tree_iterator &node)
    {
        if (node->left)
            node = node->left;
        while (node && node->right)
            node = node->right;
    }
    inline void in_successor(Rb_Tree_iterator &node)
    {
        if (node->right)
            node = node->right;
        while (node && node->left)
            node = node->left;
    }
};

template <typename T>
void Rb_Tree<T>::insertfixup(Rb_Tree_iterator &t)
{
    while (t->parent->color == RED)
    {
        Rb_Tree_iterator g = t->parent->parent, u;
        if (g->left == t->parent)
        {
            if (g->right && g->right->color == RED)
            {
                u = g->right;
                t->parent->color = BLACK;
                u->color = BLACK;
                g->color = RED;
                t = g;
            }
            else
            {
                if (t->parent->right == t)
                {
                    // t->color ^= 1;
                    t = t->parent;
                    // t->color ^= 1;
                    L_rotation(t);
                }
                t->parent->color = BLACK;
                g->color = RED;
                R_rotation(g);
            }
        }
        else
        {
            if (g->left && g->left->color == RED)
            {
                u = g->left;
                if (u->color == RED)
                {
                    t->parent->color = BLACK;
                    u->color = BLACK;
                    g->color = RED;
                    t = g;
                }
            }
            else
            {
                if (t->parent->left == t)
                {
                    // t->color ^= 1;
                    t = t->parent;
                    // t->color ^= 1;
                    R_rotation(t);
                }
                t->parent->color = BLACK;
                g->color = RED;
                L_rotation(g);
            }
            if (t == root)
                break;
        }
        root->color = BLACK;
    }
}

template <typename T>
void Rb_Tree<T>::deletefixup(Rb_Tree_iterator &p) {}

template <typename T>
void Rb_Tree<T>::L_rotation(Rb_Tree_iterator p) // p is grandparent of newnode.
{
    if (!p->right)
        return;
    else
    {
        Rb_Tree_iterator y = p->right;
        if (y->left)
        {
            p->right = y->left;
            y->left->parent = p;
        }
        else
            p->right = nullptr;
        if (p != root)
        {
            y->parent = p->parent;
            if (p == p->parent->right)
                p->parent->right = y;
            else
                p->parent->left = y;
        }
        else
            root = y;
        y->left = p;
        p->parent = y;
        // p->color ^= 1;
        // y->color ^= 1;
    }
}

template <typename T>
void Rb_Tree<T>::R_rotation(Rb_Tree_iterator p)
{
    if (!p->left)
        return;
    else
    {
        Rb_Tree_iterator y = p->left;
        if (y->right)
        {
            p->left = y->right;
            y->right->parent = p;
        }
        else
            p->left = nullptr;
        if (p != root)
        {
            y->parent = p->parent;
            if (p == p->parent->left)
                p->parent->left = y;
            else
                p->parent->right = y;
        }
        else
            root = y;
        y->right = p;
        p->parent = y;
        // p->color ^= 1;
        // y->color ^= 1;
    }
}

#endif // RB_TREE_H