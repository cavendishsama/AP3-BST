#include "bst.h"


BST::Node::Node(int m_value, Node* m_left, Node* m_right){
    this->value = m_value;
    this->left = m_left;
    this->right = m_right;        
}

// BST::Node::Node() = default;

BST::Node::Node(const Node& node){
    value = node.value;
    left = node.left;
    right = node.right;
}

BST::Node*& BST::get_root() {
    return root;
}

// void BST::bfs(std::function<void(Node*& node)> func){
//     if (root = nullptr)
//         return;
    
//     std::queue<Node*> q;
//     q.push(root);

//     while(!q.empty()){
//         Node* node = q.front();
//         q.pop();

//         /*Enqueue right child */
//         if (node->left != NULL)
//             q.push(node->left); 
//         /*Enqueue right child */
//         if (node->right != NULL)
//             q.push(node->right);

//         func(node);
//     }

}




std::ostream& operator<<(std::ostream& os, const BST::Node& v)
{
    os << &v << v.value << v.left << v.right;
    return os;
}