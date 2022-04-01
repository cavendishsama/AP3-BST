#ifndef BST_H
#define BST_H

#include <iostream>
#include <functional>
#include <compare>
#include <queue>
#include <vector>
#include <initializer_list>

class BST
{
public:
    class Node
    {
    public:
        Node(int value, Node* left = nullptr, Node* right = nullptr);
        Node() = default;
        Node(const Node& node);

        int value;
        Node* left;
        Node* right;

        std::partial_ordering operator<=>(const int& _N) const { return value <=> _N; }
        bool operator==(const int& _N) { return value == _N; }
        friend std::ostream& operator<<(std::ostream& os, const BST::Node& v) ;

    };


    Node*& get_root() ;
    void bfs(std::function<void(Node*& node)> func) ;
    size_t length();
    bool add_node(int value);
    Node** find_node(int value);
    Node** find_parrent(int value);
    Node** find_successor(int value);
    bool delete_node(int value);

    friend std::ostream& operator<<(std::ostream& os,  BST& v);
    BST& operator++();
    BST operator++(int);
    BST& operator=(BST& bst);
    BST& operator=(BST&& bst);

    BST() = default;
    BST( BST& bst);
    BST(BST&& bst);
    BST(std::initializer_list<int> );
    ~BST();
private:
    Node* root;
};

#endif //BST_H