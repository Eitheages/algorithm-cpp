#include "base.h"
#include <queue>

template <typename T>
void swap(T &a, T &b)
{
    T tmp = a;
    a = b;
    b = tmp;
}

inline int log(int n)
{
    int res = -1;
    while (n)
    {
        n = n >> 1;
        ++res;
    }
    return res;
}

//base on the binomial heap
template <typename T>
class priorityQueue: public Queue<T>
{
    struct TreeNode;
    typedef struct TreeNode Node;
    struct DumpRoot;
    typedef struct DumpRoot DRoot;
    struct copyNode;
    typedef struct copyNode CNode;

public:
    priorityQueue();
    ~priorityQueue() = default;
    priorityQueue(const priorityQueue &) = delete;
    priorityQueue(priorityQueue &&) = delete;
    bool isEmpty()const;
    void enQueue(const T&);
    void meld(const priorityQueue &other);
    T deQueue();
    T getHead()const;

private:
    DRoot *head;
    int length;
    int size;
    void meld(Node**, int);
    Node* copy(Node*);
};

template <typename T>
struct priorityQueue<T>::TreeNode
{
    TreeNode *child, *sib;
    T val;
    TreeNode(TreeNode *p1 = nullptr, TreeNode *p2 = nullptr): child(p1), sib(p2){}
    TreeNode(T x, TreeNode *p1 = nullptr, TreeNode *p2 = nullptr): val(x), child(p1), sib(p2){}
    ~TreeNode() = default;
    TreeNode(const TreeNode&) = default;
    TreeNode(TreeNode &&) = default;
    void addchild(TreeNode* &p);
};

template <typename T>
struct priorityQueue<T>::copyNode
{
    Node *self, *source;
    copyNode(Node *p1 = nullptr, Node *p2 = nullptr): self(p1), source(p2){}
    ~copyNode() = default;
};

template <typename T>
void priorityQueue<T>::TreeNode::addchild(TreeNode* &p)
{
    Node *tmp = child;
    if (!tmp)
        child = p;
    else
    {
        while (tmp->sib)
            tmp = tmp->sib;
        tmp->sib = p;
    }
}

template <typename T>
struct priorityQueue<T>::DumpRoot
{
    Node *root;
    DumpRoot *next;
    DumpRoot(Node *p1 = nullptr, DumpRoot *p2 = nullptr): root(p1), next(p2){}
    ~DumpRoot() = default;
};

template <typename T>
priorityQueue<T>::priorityQueue(): head(new DRoot()){}

template <typename T>
bool priorityQueue<T>::isEmpty() const {return size == 0;}

template <typename T>
void priorityQueue<T>::enQueue(const T &ele)
{
    Node *tmp = new Node(ele), *p;
    DRoot *t = head;
    while (t->next && t->next->root)
    {
        t = t->next;
        p = t->root;
        t->root = nullptr;
        if (p->val < tmp->val)
            swap<Node*>(p, tmp);
        tmp->addchild(p);
    }
    if (!t->next)
        t->next = new DRoot(tmp), ++length;
    else
        t->next->root = tmp;
    ++size;
}

template <typename T>
void priorityQueue<T>::meld(Node **nodes, int n)
{
    // given an array of Node* (long enough), meld it with the binomial heap
    DRoot *t = head;
    Node *tmp;
    int k = 0;
    while (k < n)
    {
        t = t->next;
        tmp = t->root;
        if (tmp)
        {
            // carry
            int m = k;
            while (nodes[m])
            {
                // ensure tmp->val is bigger
                if (nodes[m]->val < tmp->val)
                    swap<Node*>(tmp, nodes[m]);
                tmp->addchild(nodes[m]);
                nodes[m] = nullptr;
                ++m;
            };
            nodes[m] = tmp;
        }
        ++k;
    }

    t = head;
    k = 0;
    while (k < n)
    {
        if (t->next)
            t->next->root = nodes[k++];
        else
            t->next = new DRoot(nodes[k++]);
        t = t->next;
    }
}

template <typename T>
T priorityQueue<T>::deQueue()
{
    // find the DumpRoot which has the root with greatest value
    DRoot *t = head->next, *target = t;
    while (t->next)
    {
        t = t->next;
        if (!t->root)
            continue;
        if (!target->root || target->root->val > t->root->val)
            target = t;
    }
    T res = target->root->val;


    // depart the childs, add them into the pointers' array
    --size;
    int n = log(size) + 1;
    Node **nodes = new Node*[n];
    Node *p = target->root->child, *tmp;
    int k = 0;
    for (int i = 0; i < n; ++i)
        nodes[i] = nullptr;
    while (p)
    {
        nodes[k++] = p;
        tmp = p;
        p = p->sib;
        tmp->sib = nullptr; // remove the sibling relation
    }
    delete target->root;
    target->root = nullptr;

    // meld every new node
    this->meld(nodes, n);

    delete []nodes;
    return res;
}

template <typename T>
struct priorityQueue<T>::TreeNode* priorityQueue<T>::copy(Node* root)
{
    if (root == nullptr)
        return nullptr;
    std::queue<CNode*> q;
    Node *res = new Node(root->val);
    Node *self, *source, *t1, *t2;
    q.emplace(new CNode(res, root));
    CNode *tmp;

    while (!q.empty())
    {
        tmp = q.front(), q.pop();
        self = tmp->self, source = tmp->source;
        delete tmp;
        t1 = source->child;
        if (t1)
        {
            t2 = self->child = new Node(t1->val);
            q.emplace(new CNode(t2, t1));

            while (t1->sib)
            {
                t1 = t1->sib;
                t2->sib = new Node(t1->val);
                t2 = t2->sib;
                q.emplace(new CNode(t2, t1));
            }
        }
    }

    return res;
}

template <typename T>
T priorityQueue<T>::getHead() const
{
    DRoot *t = head->next;
    Node *target = t->root;
    while (t->next)
    {
        t = t->next;
        if (!target || target->val > t->root->val)
            target = t->root;
    }
    return target->val;
}

template <typename T>
void priorityQueue<T>::meld(const priorityQueue<T>& other)
{
    int cnt = this->size + other.size;
    int n = log(cnt) + 1;
    Node **nodes = new Node*[n];
    for (int i = 0; i < n; ++i)
        nodes[i] = nullptr;
    int k = -1;
    DRoot *t = other.head;
    while (t->next)
    {
        t = t->next;
        ++k;
        // copy the whole subtree
        nodes[k] = copy(t->root);
    }
    this->meld(nodes, n);
    this->size = cnt;
    delete []nodes;
}