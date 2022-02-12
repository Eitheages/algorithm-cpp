#ifndef LEFTISTHEAP
#define LEFTISTHEAP

#include "base.h"
#define min(a, b) ((a)>(b))? (b): (a)

// based on the leftist heap
template <typename T>
class priorityQueue: public Queue<T>
{
    struct TreeNode;
    typedef struct TreeNode Node;
public:
    priorityQueue();
    ~priorityQueue();
    bool isEmpty() const;
    void enQueue(const T&);
    T deQueue();
    T getHead() const;
    void merge(const priorityQueue &other);

private:
    TreeNode *root;
    void clear(Node*);
    Node* merge(Node*, Node*);
};

template <typename T>
struct priorityQueue<T>::TreeNode
{
    T val;
    int npl;
    TreeNode *left, *right;
    TreeNode(int y = 0, TreeNode *l = nullptr, TreeNode *r = nullptr)
            : left(l), right(r), npl(y){}
    TreeNode(T x, int y = 0, TreeNode *l = nullptr, TreeNode *r = nullptr)
            : val(x), left(l), right(r), npl(y){}
    ~TreeNode() = default;
    TreeNode(const TreeNode&) = delete;
};

template <typename T>
priorityQueue<T>::priorityQueue(): root(nullptr){}

template <typename T>
priorityQueue<T>::~priorityQueue(){clear(root);}

template <typename T>
void priorityQueue<T>::clear(TreeNode *p)
{
    if (p == nullptr)
        return;
    clear(p->left);
    clear(p->right);
    delete p;
}

template <typename T>
bool priorityQueue<T>::isEmpty() const {return root == nullptr;}

template <typename T>
void priorityQueue<T>::merge(const priorityQueue &other)
{
    root = merge(this->root, other.root);
}

template <typename T>
struct priorityQueue<T>::TreeNode* priorityQueue<T>::merge(Node *p1, Node *p2)
{
    if (!p1)
        return p2;
    if (!p2)
        return p1;
    Node *tmp;
    if (p1->val > p2->val)
    {
        tmp = p1;
        p1 = p2;
        p2 = tmp;
    }
    p1->right = merge(p1->right, p2);
    if (!p1->left || p1->left->npl < p1->right->npl)
    {
        tmp = p1->left;
        p1->left = p1->right;
        p1->right = tmp;
    }
    if (!p1->right)
        p1->npl = 0;
    else
        p1->npl = 1 + p1->right->npl;
    return p1;
}

template <typename T>
void priorityQueue<T>::enQueue(const T &ele)
{
    root = merge(this->root, new Node(ele, 0));
}

template <typename T>
T priorityQueue<T>::deQueue()
{
    Node *tmp = root;
    root = merge(tmp->left, tmp->right);
    T res = tmp->val;
    delete tmp;
    return res;
}

template <typename T>
T priorityQueue<T>::getHead() const {return root->val;}

#endif