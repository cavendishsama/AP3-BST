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

void BST::bfs(std::function<void(Node*& node)> func){

    // std::cout << "check point1 ................" << std::endl;
    if (root == nullptr)
        return;
    
    std::queue<Node*> q;
    q.push(root);

    while(!q.empty()){
        Node* node = q.front();
        q.pop();
        
        /*Enqueue right child */
        if (node->left != NULL)
            q.push(node->left);
             
        /*Enqueue right child */
        if (node->right != NULL)
            q.push(node->right);

        func(node);
    }

}

 size_t BST::length(){
/*                          //with code copy::
     if(root == NULL)
        return 0;

    size_t counter {1};
    std::queue<Node* > q;
    q.push(root);

    while(!q.empty()){
        Node* temp_node = q.front();

        if(temp_node->left){
            q.push(temp_node->left);
            counter++;
        }
            
        if(temp_node->right){
            q.push(temp_node->right);
            counter++;
        }
        q.pop();
    }
*/
    //via using lambda function
    size_t counter{ 0 };
    this->bfs([&counter](BST::Node*& node) { counter++; });
    return counter;
 }

bool BST::add_node(int m_value){

    BST::Node* node { new BST::Node(m_value, nullptr, nullptr) }; 
    if(root == nullptr){
        // std::cout << "check point1 ................" << std::endl;
        root = node;
        return true;
    }

    BST::Node* prev = nullptr;
    BST::Node* temp_node { root };
    while(temp_node != nullptr){
        if(temp_node->value > m_value){
            prev = temp_node;
            if(temp_node->left == nullptr){
                temp_node = nullptr;
                break;
            }
            temp_node = temp_node->left ;
            
        }
        if(temp_node->value < m_value){
            prev = temp_node;
            if(temp_node->right == nullptr){
                temp_node = nullptr;
                break;
            }
            temp_node =  temp_node->right;
        }
        if(temp_node->value == m_value)
            return false;
    }
    
    if(prev->value < m_value)
        prev->right = node; 
    else
        prev->left = node;
        
    // std::cout << "check point0 ................" << std::endl;
    return true;
    
}

BST::Node** BST::find_node(int m_value){
    BST::Node** temp { new BST::Node*};
    *temp = root;
    
    if(*temp == nullptr){
        std::cout << "Tree doesn't exist" << std::endl;   
        return nullptr;
        }

    while(true){

        if(*temp == nullptr){
            std::cout << "This value doesn't exist in tree" << std::endl;        
            return nullptr;
        }

        //added these != nullptr to fix segmentation fault.

        if(*temp != nullptr && (*temp)->value > m_value)
            *temp = (*temp)->left;
        
        if(*temp != nullptr && (*temp)->value < m_value)
            *temp = (*temp)->right;
        
        if(*temp != nullptr && (*temp)->value == m_value)
            return temp;          
    
    }
}

BST::Node** BST::find_parrent(int m_value){

    BST::Node** temp { new BST::Node*};
    *temp = root;
    
    if(*temp == nullptr){
        std::cout << "Tree doesn't exist" << std::endl;   
        return nullptr;
        }

    while(true){
        
        if(*temp == nullptr){
            std::cout << "This value doesn't exist in tree" << std::endl;        
            return nullptr;
        }

        if(*temp != nullptr && (*temp)->value > m_value){
            if(*temp != nullptr && (*temp)->left->value == m_value)
                return temp;
            else    
                *temp = (*temp)->left;
        }

        if(*temp != nullptr && (*temp)->value < m_value){
            if(*temp != nullptr && (*temp)->right->value == m_value)
                return temp;
            else
                *temp = (*temp)->right;
        }
    }
    
}

BST::Node** BST::find_successor(int m_value){

    BST::Node** temp { new BST::Node*};
    *temp = *this->find_node(m_value);
    
    if(*temp == nullptr)
        return nullptr;
    
    if((*temp)->left == nullptr)
        return temp;
    
    else if ((*temp)->left->right == nullptr){
        *temp =  (*temp)->left;
        return temp;
    }

    else{
        *temp = (*temp)->left;
        while((*temp)->right != nullptr)
            (*temp) = (*temp)->right;
        
        return temp;
    }
}

bool BST::delete_node(int m_value){

    BST::Node** delete_node { this->find_node(m_value) };

    if( delete_node == nullptr )
        return false;

    //leaf :
    if((*delete_node)->left == nullptr && (*delete_node)->right == nullptr){
        auto delete_node_parent { this->find_parrent(m_value) };
        
        //again added !=nullptr for seg fault
        if((*delete_node_parent)->left != nullptr && (*delete_node_parent)->left->value == m_value ){
            delete *delete_node;
            (*delete_node_parent)->left = nullptr;
            return true;
        }
        if((*delete_node_parent)->right != nullptr && (*delete_node_parent)->right->value == m_value){
            delete *delete_node;
            (*delete_node_parent)->right = nullptr;
            return true;
        }
    }
    //right child
    else if((*delete_node)->left == nullptr && (*delete_node)->right != nullptr){
        auto delete_node_parent { this->find_parrent(m_value) };
        if((*delete_node_parent)->right != nullptr && (*delete_node_parent)->right->value == m_value){
            BST::Node** temp {  new BST::Node* }; 
            *temp = (*delete_node)->right;
            delete (*delete_node);
            (*delete_node_parent)->right = (*temp);
            return true;
        }  
    }
    //left child
    else if((*delete_node)->left != nullptr && (*delete_node)->right == nullptr){
        auto delete_node_parent { this->find_parrent(m_value) };
        if((*delete_node_parent)->left != nullptr && (*delete_node_parent)->left->value == m_value){
            BST::Node** temp {  new BST::Node* }; 
            *temp = (*delete_node)->left;
            delete (*delete_node);
            (*delete_node_parent)->left = (*temp);
            return true;
        }

    }
    //both children
    else{
        auto delete_node_successor { this->find_successor(m_value) };
        auto delete_node_successor_parent { this->find_parrent((*delete_node_successor)->value) };

        (*delete_node)->value = (*delete_node_successor)->value;
        delete (*delete_node_successor);
        if ((*delete_node_successor_parent)->right != nullptr && (*delete_node_successor_parent)->right->value == (*delete_node_successor)->value) {
            (*delete_node_successor_parent)->right = nullptr;
            return true;
        } else if ((*delete_node_successor_parent)->left != nullptr && (*delete_node_successor_parent)->left->value == (*delete_node_successor)->value) {
            (*delete_node_successor_parent)->left = nullptr;
            return true;
        }    
    }    
    return false;
}



std::ostream& operator<<(std::ostream& os,  BST& v){

    std::queue<BST::Node*> nodes;
    v.bfs([&nodes](BST::Node*& node) { nodes.push(node); });
    os << std::string(85, '*') << std::endl;
   
    while(!nodes.empty()){
        os << *nodes.front() << std::endl;
        nodes.pop();
    }
    os << "Binary Search tree size: " << v.length() << std::endl;
    os << std::string(85, '*') << std::endl;
    return os;

}

std::ostream& operator<<(std::ostream& os, const BST::Node& v)
{
    os << &v << "\t => value: " << v.value << "\t\t";
    std::cout << "left: " << std::left;
    os.width(15);
    std::cout << v.left << std::right;
    os.width(10);
    std::cout << "right: " << std::left;
    std::cout << v.right;
    //  "\t left: " << v.left << "\t right: " << v.right << std::endl;
    
    return os;
}

BST& BST::operator++(){

    std::queue<BST::Node*> q;
    this->bfs([&q](BST::Node*& node) { q.push(node); });
    while(!q.empty()){
        q.front()->value++;
        q.pop();
    }
    return *this;
}

BST BST::operator++(int){
    BST tree { *this };
    ++(*this);
    return *this;
}

BST& BST::operator=(BST& bst){
    std::queue<BST::Node*> q;
    bst.bfs([&q](BST::Node*& node) { q.push(node); });
    
    while (!q.empty())
    {
        this->add_node(q.front()->value);
        q.pop();
    }  
    return *this;
}

BST& BST::operator=(BST&& bst){
    root = bst.get_root();
    bst.root = nullptr;
    return *this;
}

 BST::BST(BST& bst) : root { nullptr }{
    std::queue<BST::Node*> q;
    bst.bfs([&q](BST::Node*& node) { q.push(node); });
    
    while (!q.empty())
    {
        this->add_node(q.front()->value);
        q.pop();
    }  
 }

 BST::BST(BST&& bst){
    root = bst.get_root();
    bst.root = nullptr;
 }

  BST::~BST(){
 	std::vector<Node*> nodes;
 	bfs([&nodes](BST::Node*& node){nodes.push_back(node);});
 	for(auto& node: nodes)
 		delete node;
 }