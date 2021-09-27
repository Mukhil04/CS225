/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

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
    Node* t1 = t-> right;
    t->right = t1->left;
    t1->left = t;
    t->height = std::max(heightOrNeg1(t->left)+ 1, heightOrNeg1(t->right) +1);
    t = t1;
    t->height = std::max(heightOrNeg1(t),heightOrNeg1(t->left) +1 );
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
    Node* t1 = t -> left;
    t->left = t1->right;
    t1->right = t;
    t->height = std::max(heightOrNeg1(t->right)+ 1, heightOrNeg1(t->left) +1);
    t = t1;
    t->height = std::max(heightOrNeg1(t),heightOrNeg1(t->right) +1 );
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
    int balance = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);
    if (balance <= -2){
        if (heightOrNeg1(subtree->left->left) > heightOrNeg1(subtree->left->right)){
            rotateRight(subtree);
        }
        else{
            rotateLeftRight(subtree);
        }
    }
    else if (balance >= 2){
        if (heightOrNeg1(subtree->right->right) > heightOrNeg1(subtree->right->left)){
            rotateLeft(subtree);
        }
        else{
            rotateRightLeft(subtree);
        }
    }
    else {
        if (subtree->left == NULL && subtree->right == NULL){
            subtree->height = 0;
            return;
        }
        else {
            subtree->height = std::max(heightOrNeg1(subtree->left) + 1, heightOrNeg1(subtree->right) + 1);
        }
    }
    return;
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
    if (subtree == NULL){
        subtree = new Node(key,value);
    }
    else if (key < subtree->key){
        insert(subtree->left, key, value);
    }
    else if (key > subtree->key){
        insert(subtree->right, key, value);
    }
    rebalance(subtree);
    return;
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
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        remove(subtree->left, key);
        // your code here
    } 
    else if (key > subtree->key) {
        remove(subtree->right, key);
        // your code here
    } 
    else {
        if (subtree->left == NULL && subtree->right == NULL) {
            delete subtree;
            subtree = NULL;
            return;
            /* no-child remove */
            // your code here
        } 
        else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node* iterator = subtree;
            Node* parent = NULL;
            iterator = iterator->left;
            while(iterator->right->right != NULL){
                iterator = iterator->right;
            }
            parent = iterator;
            iterator = iterator->right;
            swap(iterator,subtree);
            delete iterator;
            parent->right = NULL;
            rebalance(parent);
            if (subtree->left != NULL){
                rebalance(subtree->left);
            }
            rebalance(subtree);
        } 
        else {
            Node* iterator = NULL;
            if (subtree->left != NULL){
                iterator = subtree->left;
            }
            else if (subtree->right != NULL){
                iterator = subtree->right;
            }
            swap(iterator,subtree);
            if (subtree->left != NULL){
                delete iterator;
                subtree->left = NULL;
            }
            else if(subtree->right != NULL){
                delete iterator;
                subtree->right = NULL;
            }
            rebalance(subtree);
        }
            
        return;
            /* one-child remove */
            // your code here
    }
        
        // your code here
    rebalance(subtree);
    return;
}
