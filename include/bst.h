#ifndef BST_H
#define BST_H

#include <iostream>
#include <functional>
#include <compare>
#include <queue>
#include <vector>

class BST
{
public:
    class Node
    {
    public:
        Node(int value, Node* left = nullptr, Node* right = nullptr);
        Node() = default;
        Node(const Node& node);

        std::partial_ordering operator<=>(const int& _N) const { return value <=> _N; }
        bool operator==(const int& _N) { return value == _N; }

        int value;
        Node* left;
        Node* right;
    };


    Node*& get_root() ;
    void bfs(std::function<void(Node*& node)> func);
    size_t length();
    bool add_node(int value);
    Node** find_node(int value);
    Node** find_parrent(int value);
    Node** find_successor(int value);
    bool delete_node(int value);

private:
    Node* root;
};

std::ostream& operator<<(std::ostream& os, const BST::Node& v) ;

#endif //BST_H