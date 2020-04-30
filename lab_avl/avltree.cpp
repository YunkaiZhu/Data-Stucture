/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
using namespace std;

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    Node* temp = t -> right;
    t -> right = temp -> left;
    temp -> left = t;
    t -> height = 1 + max(heightOrNeg1(t -> left), heightOrNeg1(t -> right));
    temp -> height = t -> height + 1;
    t = temp;
    
    // your code here
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    Node* temp = t -> left;
    t -> left = temp -> right;
    temp -> right = t;
    t -> height = 1 + max(heightOrNeg1(t->left),heightOrNeg1(t->right));
    temp -> height = 1 + t -> height;
    t = temp;
    // your code here
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    rotateRight(t->right);
    rotateLeft(t);
    // your code here
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    if(subtree == NULL){
        return;
    }
    int balance = heightOrNeg1(subtree->left) - heightOrNeg1(subtree->right);
    if(balance == -2){
        if(heightOrNeg1(subtree->right->left) > heightOrNeg1(subtree->right->right)){
            rotateRightLeft(subtree);
            subtree->left->height = subtree->height - 1;
        }
        else if(heightOrNeg1(subtree->right->left) < heightOrNeg1(subtree->right->right)){
            rotateLeft(subtree);
            subtree->left->height = subtree->height - 1;
        }
        else{
            
            rotateLeft(subtree);
            subtree->left->height = subtree->left->right->height + 1;
        }
    }
    else if(balance == 2){
        if(heightOrNeg1(subtree->left->left) < heightOrNeg1(subtree->left->right)){
            rotateLeftRight(subtree);
            subtree->right->height = subtree->height - 1;
        }
        else if(heightOrNeg1(subtree->left->left) > heightOrNeg1(subtree->left->right)){
            rotateRight(subtree);
            subtree->right->height = subtree->height - 1;
        }
        else{
            rotateRight(subtree);
            subtree->right->height = subtree->right->left->height + 1;
        }
    }

    subtree->height = max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right)) + 1;
    // your code here
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    
    if(subtree == NULL){
        subtree = new Node(key, value);
    }
    if(key > subtree->key) {
        if (subtree->right == NULL) {
            subtree->right = new Node(key, value);
        } else {
            insert(subtree->right, key, value);
        }
    }
    if(key < subtree->key) {
        if (subtree->left == NULL) {
            subtree->left = new Node(key, value);
        } else {
            insert(subtree->left, key, value);
        }
    }
    // if(key < subtree->key && subtree->left == NULL){
    //     subtree->left = new Node(key, value);
    // }
    // if(key < subtree->key){
    //     insert(subtree->left, key, value);
    // }
    rebalance(subtree);
    // your code here
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL){
        return;
    }
    if (key < subtree->key) {
        remove(subtree->left, key);
        // your code here
    } else if (key > subtree->key) {
        remove(subtree->right, key);
        // your code here
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            
            Node* todelete = subtree;
            subtree = NULL;
            delete todelete;
            return;
            /* no-child remove */
            // your code here
        } else if (subtree->left != NULL && subtree->right != NULL) {
            
            Node* temp = subtree->left;
            while(temp->right->right != NULL){
                temp = temp->right;
            }
            Node* todelete = temp;
            if(temp->right == NULL){
                subtree->left = temp->left;
                swap(subtree, temp);
                delete todelete;
            }
            else{
                todelete = todelete->right;
                swap(subtree, todelete);
                temp->right = NULL;
                delete todelete;
            }
            // while (temp -> right != NULL) {
            //     temp = temp -> right;
            // }
            // swap(subtree, temp);
            // delete temp;
            return;
            }
            /* two-child remove */
            // your code here
            else {
            if(subtree->right == NULL){
                Node* todelete = subtree;
                subtree = subtree->left;
                delete todelete;
            }
            else{
                Node* todelete = subtree;
                subtree = subtree->right;
                delete todelete;
            }
            return;
            /* one-child remove */
            // your code here
        }
        // your code here
    }
    rebalance(subtree);
}
