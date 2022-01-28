#ifndef BT
#define BT

#include <iostream>
#include <queue>

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
};

template <typename T>
class BinaryTree: public bTree<T>
{
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
    void preOrder () const
    {
        if (this->isEmpty())
            return;
        std::cout << "Pre-Order Traversal:\n";
        preOrder(root);
        std::cout << std::endl;
    }
    void inOrder () const
    {
        if (this->isEmpty())
            return;
        std::cout << "In-Order Traversal:\n";
        inOrder(root);
        std::cout << std::endl;
    }
    void postOrder () const
    {
        if (this->isEmpty())
            return;
        std::cout << "Post-Order Traversal:\n";
        postOrder(root);
        std::cout << std::endl;
    }
    void levelOrder () const
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

private:
    Node *root;
    void clear(Node *p);
    Node *find(T x, Node *p) const;
    void preOrder(Node *p) const;
    void inOrder(Node *p) const;
    void postOrder(Node *p) const;
};

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


#endif