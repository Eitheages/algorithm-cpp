#ifndef BST
#define BST

#include "base.h"

template <typename K, typename V>
class BinarySearchTree : public dynamicalSearchTable<K, V> {

    typedef const struct searchSet<K, V> SET;
    struct TreeNode;
    typedef struct TreeNode Node;

public:
    BinarySearchTree();
    ~BinarySearchTree();
    BinarySearchTree(const BinarySearchTree&) = delete;
    BinarySearchTree(BinarySearchTree&&) = delete;
    SET* find(const K& x) const;
    void insert(const SET&);
    void remove(const K&);

private:
    Node* root;

    Node* find(const K&, Node* const&) const;
    void insert(const SET&, Node*&);
    void remove(const K&, Node*&);
    void clear(Node*);
};

template <typename K, typename V>
struct BinarySearchTree<K, V>::TreeNode {
    SET* data;  // unchangeable
    TreeNode *left, *right;

    TreeNode() = default;
    TreeNode(const SET& thedata, TreeNode* p1 = nullptr, TreeNode* p2 = nullptr)
        : data(new SET(thedata.key, thedata.value)), left(p1), right(p2) {}
    TreeNode(K x, V y, TreeNode* p1 = nullptr, TreeNode* p2 = nullptr)
        : data(new SET(x, y)), left(p1), right(p2) {}

    TreeNode(const TreeNode&) = delete;
    ~TreeNode() { delete data; }
};

template <typename K, typename V>
BinarySearchTree<K, V>::BinarySearchTree() : root(nullptr) {}

template <typename K, typename V>
BinarySearchTree<K, V>::~BinarySearchTree() {
    clear(root);
}

template <typename K, typename V>
void BinarySearchTree<K, V>::clear(Node* p) {
    if (!p)
        return;
    clear(p->left);
    clear(p->right);
    delete p;
}

template <typename K, typename V>
const struct searchSet<K, V>* BinarySearchTree<K, V>::find(const K& key) const {
    Node* finded = find(key, root);
    if (!finded)
        return nullptr;
    return finded->data;
}

template <typename K, typename V>
struct BinarySearchTree<K, V>::TreeNode* BinarySearchTree<K, V>::find(
    const K& key, Node* const& p) const {
    if (!p || p->data->key == key)
        return p;
    if (p->data->key > key)
        return find(key, p->left);
    else
        return find(key, p->right);
}

template <typename K, typename V>
void BinarySearchTree<K, V>::insert(const SET& x) {
    insert(x, root);
}

template <typename K, typename V>
void BinarySearchTree<K, V>::insert(const SET& ele, Node*& p) {
    if (!p) {
        p = new Node(ele);
        return;
    }
    if (p->data->key == ele.key) {
        std::cout << "inserted failure!" << std::endl;
        return;
    }
    if (p->data->key > ele.key)
        insert(ele, p->left);
    else
        insert(ele, p->right);
}

template <typename K, typename V>
void BinarySearchTree<K, V>::remove(const K& key) {
    remove(key, root);
}

template <typename K, typename V>
void BinarySearchTree<K, V>::remove(const K& key, Node*& p) {
    if (!p) {
        std::cout << "deleted failure!" << std::endl;
        return;
    }
    if (p->data->key < key)
        remove(key, p->right);
    else if (p->data->key > key)
        remove(key, p->left);
    else if (p->left && p->right) {
        Node* tmp = p->left;
        while (tmp->right)
            tmp = tmp->right;
        delete p->data;
        p->data = new SET(tmp->data->key, tmp->data->value);
        remove(p->data->key, p->left);
    } else {
        Node* tmp = p;
        p = p->left ? p->left : p->right;
        delete tmp;
    }
}

#endif