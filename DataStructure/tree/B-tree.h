#ifndef BT
#define BT

#include <iostream>
#include <queue>
#include <stack>

#define max(a, b) ((a > b)? (a): (b))
template <typename T>
class bTree
{
public:
    virtual void clear() = 0;
    virtual bool isEmpty() const = 0;
    virtual T getRoot (const T &flag) const = 0;
    virtual T parent (T x, const T &flag) const = 0;
    virtual T lchild (T x, const T &flag) const = 0;
    virtual T rchild (T x, const T &flag) const = 0;
    virtual void delleft (T x) = 0;
    virtual void delright (T x) = 0;
    virtual void preOrder () const = 0;
    virtual void inOrder () const = 0;
    virtual void postOrder () const = 0;
    virtual void levelOrder () const = 0;
    virtual int findtwodegree() const = 0;
    virtual bool isFull() const = 0;
    virtual int getHeight() const = 0;
};

template <typename T>
class BinaryTree: public bTree<T>
{
    template <typename U>
    friend bool operator==(const BinaryTree<U>&, const BinaryTree<U>&);
    template <typename U>
    friend int getHeight(const BinaryTree<U>&);
    struct Node
    {
        Node *left, *right;
        T val;

        Node (Node *p = nullptr, Node *q = nullptr): left(p), right(q){}
        Node (T x, Node *p = nullptr, Node *q = nullptr): val(x), left(p), right(q){}
        ~Node (){}
    };

public:
    BinaryTree(): root(nullptr){}
    BinaryTree(T x): root(new Node(x)){}
    ~BinaryTree() {clear();}

    void clear() {clear(root);}
    bool isEmpty() const {return root == nullptr;}
    T getRoot (const T &flag) const;
    T parent (T x, const T &flag) const {return flag;}
    T lchild (T x, const T &flag) const;
    T rchild (T x, const T &flag) const;
    void createTree(T flag);
    void delleft (T x);
    void delright (T x);
    void preOrder () const;
    void inOrder () const;
    void postOrder () const;
    void levelOrder () const;
    int findtwodegree() const;
    bool isFull() const;
    bool isComplete() const;
    int getHeight() const;

private:
    struct Node *root;
    void clear(Node *p);
    struct Node *find(T x, Node *p) const;
    void preOrder(Node *p) const;
    void inOrder(Node *p) const;
    void postOrder(Node *p) const;
    bool isSameTree(Node* p, Node* q) const;
    int getHeight(Node* p) const;
};

template <typename T>
void BinaryTree<T>::preOrder() const
{
    if (this->isEmpty())
        return;
    std::cout << "Pre-Order Traversal:\n";
    preOrder(root);
    std::cout << std::endl;
}

template <typename T>
void BinaryTree<T>::inOrder() const
{
    if (this->isEmpty())
        return;
    std::cout << "In-Order Traversal:\n";
    inOrder(root);
    std::cout << std::endl;
}

template <typename T>
void BinaryTree<T>::postOrder() const
{
    if (this->isEmpty())
        return;
    std::cout << "Post-Order Traversal:\n";
    postOrder(root);
    std::cout << std::endl;
}

template <typename T>
void BinaryTree<T>::levelOrder() const
{
    if (this->isEmpty())
        return;
    std::cout << "Level-Order Traversal:\n";
    std::queue<Node*> q;
    q.push(root);

    while (!q.empty())
    {
        Node *tmp = q.front();
        q.pop();
        std::cout << tmp->val << ' ';
        if (tmp->left)
            q.push(tmp->left);
        if (tmp->right)
            q.push(tmp->right);
    }
    std::cout << std::endl;
}

template <typename T>
void BinaryTree<T>::clear(Node *p)
{
    if (p == nullptr)
        return;
    clear(p->left);
    clear(p->right);
    delete p;
    p = nullptr;
}

template <typename T>
T BinaryTree<T>::getRoot(const T &flag) const
{
    return root == nullptr? flag: root->val;
}

template <typename T>
void BinaryTree<T>::preOrder(Node *p) const
{
    if (p == nullptr)
        return;
    std::cout << p->val << ' ';
    preOrder(p->left);
    preOrder(p->right);
}

template <typename T>
bool BinaryTree<T>::isFull() const
{
    struct Node *tmp;
    std::queue<Node *> q;
    int height = 0, cnt = 0;
    if (root)
        q.push(root), ++cnt;

    while (!q.empty())
    {
        ++height;
        int times = q.size();
        while (times--)
        {
            tmp = q.front(), q.pop();
            if (tmp->left)
                q.push(tmp->left), ++cnt;
            if (tmp->right)
                q.push(tmp->right), ++cnt;
        }
    }
    return cnt == (1 << height) - 1;
}

template <typename T>
void BinaryTree<T>::inOrder(Node *p) const
{
    if (p == nullptr)
        return;
    inOrder(p->left);
    std::cout << p->val << ' ';
    inOrder(p->right);
}

template <typename T>
void BinaryTree<T>::postOrder(Node *p) const
{
    if (p == nullptr)
        return;
    postOrder(p->left);
    postOrder(p->right);
    std::cout << p->val << ' ';
}

template <typename T>
struct BinaryTree<T>::Node *BinaryTree<T>::find(T x, Node *p) const
{
    if (p == nullptr)
        return nullptr;
    if (p->val == x)
        return p;
    Node *tmp = find(x, p->left);
    if (tmp)
        return tmp;
    tmp = find(x, p->right);
    return tmp;
}

template <typename T>
T BinaryTree<T>::lchild(T x, const T &flag) const
{
    Node *tmp = find(x, root);
    if (tmp && tmp->left)
        return tmp->left->val;
    return flag;
}

template <typename T>
T BinaryTree<T>::rchild(T x, const T &flag) const
{
    Node *tmp = find(x, root);
    if (tmp && tmp->right)
        return tmp->right->val;
    return flag;
}

template <typename T>
void BinaryTree<T>::delleft(T x)
{
    Node *tmp = find(x, root);
    if (tmp == nullptr)
        return;
    clear(tmp->left);
}

template <typename T>
void BinaryTree<T>::delright(T x)
{
    Node *tmp = find(x, root);
    if (tmp == nullptr)
        return;
    clear(tmp->right);
}

template <typename T>
void BinaryTree<T>::createTree(T flag)
{
    T x, l, r;
    Node *tmp;
    std::queue<Node*> q;
    std::cout << "Input the root node: ";
    std::cin >> x;
    q.push(root = new Node(x));

    while (!q.empty())
    {
        tmp = q.front();
        q.pop();
        std::cout << "Input the left and right childs of " << tmp->val << ": ";
        std::cin >> l >> r;
        if (l != flag)
            q.push(tmp->left = new Node(l));
        if (r != flag)
            q.push(tmp->right = new Node(r));
    }
    std::cout << "Create completed!\n";
}

template <typename T>
bool operator==(const BinaryTree<T> &tree1, const BinaryTree<T> &tree2)
{
    return tree1.isSameTree(tree1.root, tree2.root);
}

template <typename T>
bool BinaryTree<T>::isSameTree(Node* p, Node* q) const
{
    if (p && q && p->val == q->val)
        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    else if (!p && !q)
        return true;
    else
        return false;
}

template <typename T>
int BinaryTree<T>::findtwodegree() const
{
    int res = 0;
    struct Node *tmp;
    std::stack<Node*> stk;
    if (root)
        stk.push(root);

    while (!stk.empty())
    {
        tmp = stk.top(), stk.pop();
        if (tmp->left && tmp->right)
            ++res;
        if (tmp->left)
            stk.push(tmp->left);
        if (tmp->right)
            stk.push(tmp->right);
    }
    return res;
}

template <typename T>
bool BinaryTree<T>::isComplete() const
{
    std::queue<struct Node*> q;
    struct Node *tmp;
    q.push(root);

    while (tmp = q.front())
    {
        q.pop();
        q.push(tmp->left);
        q.push(tmp->right);
    }

    while (!q.empty())
    {
        tmp = q.front();
        q.pop();
        if (tmp)
            return false;
    }
    return true;
}

template <typename T>
int BinaryTree<T>::getHeight() const
{
    return getHeight(root);
}

template <typename T>
int BinaryTree<T>::getHeight(Node *p) const
{
    if (p)
        return max(getHeight(p->left), getHeight(p->right)) + 1;
    return 0;
}

template <typename T>
int getHeight(const BinaryTree<T> &tree)
{
    struct BinaryTree<T>::Node *tmp, *r = tree.root;
    std::queue<struct BinaryTree<T>::Node*> q;
    int height = 0;
    q.push(r);

    while (1)
    {
        int cnt = q.size();
        while (cnt--)
        {
            tmp = q.front(), q.pop();
            if (tmp)
                q.push(tmp->left), q.push(tmp->right);
        }
        if (!q.empty())
            ++height;
        else
            break;
    }
    return height;
}

#endif