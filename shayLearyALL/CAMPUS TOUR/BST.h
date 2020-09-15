#ifndef BST_H
#define BST_H
#include<iostream>
#include<functional>


template <class T>
class BST
{
    struct BSTnode {
        T data; /// The data within the node
        BSTnode* left; /// The node to the downward left of this node
        BSTnode* right; /// The node to the downward right of this node
        int height =0;
        BSTnode(T dat){
            data = dat;
            left = nullptr;
            right = nullptr;
        }
    };
    public:
        BST(){
            root = NULL;
        }
        virtual ~BST(){
            deleteTree(root);
        }
        /**
        * @brief Inserts Data
        * @param data - data of type T
        * @return void
        */
        void Insert(T data);
        /**
        * @brief Traveres the BST in order
        * @param *f(T) - a function pointer for data to be sent to
        * @return void
        */
        void InOrderTraversal(std::function<void(T&)> fun);
        /**
        * @brief Traveres the BST in post order
        * @param *f(T) - a function pointer for data to be sent to
        * @return void
        */
        void PostOrderTraversal(void(*f)(T));
        /**
        * @brief Traveres the BST in pre order
        * @param *f(T) - a function pointer for data to be sent to
        * @return void
        */
        void PreOrderTraversal(void(*f)(T));
        /**
        * @brief Searches the BST for data
        * @param data - data of type T to search for
        * @param *f(T) - a function pointer for data to be sent to
        * @return bool
        */
        bool Search(T data, void(*f)(T));

        BST<T>& operator = (const BST<T> &node){
            deleteTree(root);
            root = Copy(node.root);
        };

    protected:

    private:
        BSTnode *root; /// The root node of the Binary Search Tree
        /**
        * @brief Inserts Data
        * @param data - data of type T
        * @param *parent - the parent node of where the insert is happening
        * @return void
        */
        BSTnode* Insert(T data, BSTnode *parent);
        /**
        * @brief Traveres the BST in order
        * @param *f(T) - a function pointer for data to be sent to
        * @param *node - the current node that is being searched
        * @return void
        */
        void InOrderTraversal(BSTnode *node,std::function<void(T&)> fun);
        /**
        * @brief Traveres the BST in pre order
        * @param *f(T) - a function pointer for data to be sent to
        * @param *node - the current node that is being searched
        * @return void
        */
        void PreOrderTraversal(BSTnode *node,void(*f)(T));
        /**
        * @brief Traveres the BST in post order
        * @param *f(T) - a function pointer for data to be sent to
        * @param *node - the current node that is being searched
        * @return void
        */
        void PostOrderTraversal(BSTnode *node,void(*f)(T));
        /**
        * @brief Searches the BST for data
        * @param *start - the node that is currently being searched
        * @param data - data of type T to search for
        * @param *f(T) - a function pointer for data to be sent to
        * @return bool
        */
        bool Search(BSTnode *start,T data, void(*f)(T));
        /**
        * @brief Deletes the entire BST
        * @param *node - node that is currently being deleted
        * @return void
        */
        void deleteTree(BSTnode *node);
        /**
        * @brief Copys the BST
        * @param *node - node that is currently being copied
        * @return BSTnode*
        */
        BSTnode* Copy(BSTnode *toCopy);
        /**
        * @brief Gets the balance between 2 nodes
        * @param *node - parent node of the nodes being checked for balance
        * @return int
        */
        int getBalance(BSTnode *node);
        /**
        * @brief Returns the bigger int between the 2
        * @param int a - first number
        * @param int b - second number
        * @return int
        */
        int getBigger(int a,int b);
        /**
        * @brief returns the height of the BSTnode
        * @param *node - node that is returning height
        * @return int
        */
        int getHeight(BSTnode *node);
        /**
        * @brief rotates the tree right based on a provided pivot point
        * @param *node - node that is the pivot point
        * @return BSTnode*
        */
        BSTnode* rotateRight(BSTnode *node);
        /**
        * @brief rotates the tree left based on a provided pivot point
        * @param *node - node that is the pivot point
        * @return BSTnode*
        */
        BSTnode* rotateLeft(BSTnode *node);
};
template <class T>
typename BST<T>::BSTnode* BST<T>::rotateRight(BSTnode *node){
    BSTnode *temp = node->left;
    BSTnode *temp2 = temp->right;

    temp->right = node; //temp becomes the new root node
    node->left = temp2;

    node->height = getBigger(getHeight(node->left),getHeight(node->right)) +1;
    temp->height = getBigger(getHeight(temp->left),getHeight(temp->right)) +1;

    return temp;
}
template <class T>
typename BST<T>::BSTnode* BST<T>::rotateLeft(BSTnode *node){
    BSTnode *temp = node->right;
    BSTnode *temp2 = temp->left;

    temp->left = node;
    node->right = temp2;

    node->height = getBigger(getHeight(node->left),getHeight(node->right)) +1;
    temp->height = getBigger(getHeight(temp->left),getHeight(temp->right)) +1;


    return temp;
}
template <class T>
int BST<T>::getHeight(BSTnode *node){
    if (node == NULL)
        return 0;
    return node->height;
}

template <class T>
int BST<T>::getBigger(int a, int b){
    return (a > b)? a : b;
}

template <class T>
int BST<T>::getBalance(BSTnode *node){
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

template <class T>
typename BST<T>::BSTnode* BST<T>::Insert(T data, BSTnode *parent){
    if (parent == NULL)
        return(new BSTnode(data));

    if (data < parent->data)
        parent->left = Insert(data,parent->left);

    else if (data > parent->data)
        parent->right = Insert(data,parent->right);

    else
        return parent;
    parent->height = getBigger(getHeight(parent->left),getHeight(parent->right)) +1;

    int balance = getBalance(parent);

    // Left Left Roatation
    if (balance > 1 && data < parent->left->data)
        return rotateRight(parent);

    // Right Right Rotation
    if (balance < -1 && data > parent->right->data)
        return rotateLeft(parent);

    // Left Right Rotation
    if (balance > 1 && data > parent->left->data){
        parent->left = rotateLeft(parent->left);
        return rotateRight(parent);
    }

    // Right Left Rotation
    if (balance < -1 && data < parent->right->data){
        parent->right = rotateRight(parent->right);
        return rotateLeft(parent);
    }
    return parent;
}

template <class T>
void BST<T>::Insert(T data){
     if(root == NULL)
        root = new BSTnode(data);
     else
        root = Insert(data, root);
}

template <class T>
void BST<T>::InOrderTraversal(std::function<void(T&)> fun){
    InOrderTraversal(root,fun);
}
template <class T>
void BST<T>::InOrderTraversal(BSTnode *node,std::function<void(T&)> fun){
    if(!node)
        return;
    InOrderTraversal(node->left,fun);
    fun(node-> data);
    InOrderTraversal(node->right,fun);
}

template <class T>
void BST<T>::PostOrderTraversal(void(*f)(T)){
    PostOrderTraversal(root,(*f));
}
template <class T>
void BST<T>::PostOrderTraversal(BSTnode *node,void(*f)(T)){
    if(!node)
        return;
    PostOrderTraversal(node->left,(*f));
    PostOrderTraversal(node->right,(*f));
    (*f)(node-> data);
}

template <class T>
void BST<T>::PreOrderTraversal(void(*f)(T)){
    PreOrderTraversal(root,(*f));
}
template <class T>
void BST<T>::PreOrderTraversal(BSTnode *node,void(*f)(T)){
    if(!node)
        return;
    (*f)(node-> data);
    PreOrderTraversal(node->left,(*f));
    PreOrderTraversal(node->right,(*f));
}

template <class T>
bool BST<T>::Search(T data, void(*f)(T)){
    return Search(root,data,(*f));
}

template <class T>
bool BST<T>::Search(BSTnode *start,T data, void(*f)(T)){
    bool res = false;
    if(start == NULL)
        return false;
    if(start->data == data){
        (*f)(start-> data);
        return(true);
    }
    res = Search(start->left,data,(*f));
    if(!res){
        res = Search(start->right,data,(*f));
    }
    return res;
}

template <class T>
void BST<T>::deleteTree(BSTnode *node){
    if (node == NULL) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}
template <class T>

typename BST<T>::BSTnode* BST<T>::Copy(BSTnode *toCopy){
    if(!toCopy){
        return 0;
    }
    BSTnode* newNode = new BSTnode(toCopy->data);
    newNode->left = Copy(toCopy->left);
    newNode->right = Copy(toCopy->right);
    return newNode;
}
#endif // BST_H
