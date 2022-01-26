#ifndef STACK
#define STACK

template <class elemType>
class Stack
{
public:
    virtual bool isEmpty() const = 0;
    virtual void push(const elemType &) = 0;
    virtual elemType pop() = 0;
    virtual elemType top() const = 0;
    virtual ~Stack(){}
};

template <class elemType>
class seqStack: public Stack<elemType>
{
public:
    seqStack (int initSize = 10);
    ~seqStack();
    bool isEmpty() const {return (top_p == 0);}
    bool isFull() const {return (top_p == maxsize);}
    void push(const elemType &);
    elemType pop();
    elemType top() const;
private:
    elemType* array;
    int maxsize;
    int top_p;
    void doubleSpace();
};

template <class elemType>
class linkStack: public Stack<elemType>
{
    struct Node
    {
        elemType data;
        Node *next;
        Node (const elemType &x, Node *N = nullptr): data(x), next(N){}
        Node (Node *N = nullptr): next(N){}
    };
public:
    linkStack();
    ~linkStack();
    bool isEmpty() const {return (top_p == nullptr);}
    void push(const elemType &);
    elemType pop();
    elemType top() const {return top_p->data;}
private:
    Node *top_p;
};


template <class elemType>
seqStack<elemType>::seqStack(int initSize): maxsize(initSize), top_p(0)
{
    array = new elemType[maxsize];
}

template <class elemType>
void seqStack<elemType>::doubleSpace()
{
    maxsize *= 2;
    elemType* temp = new elemType[maxsize];
    for (int i = 0; i < maxsize/2; i++)
        temp[i] = array[i];
    delete []array;
    array = temp;
}

template <class elemType>
void seqStack<elemType>::push(const elemType& obj)
{
    if (isFull())
        doubleSpace();
    array[top_p++] = obj;
}

template <class elemType>
seqStack<elemType>::~seqStack()
{
    delete []array;
}

template <class elemType>
elemType seqStack<elemType>::pop()
{
    return array[--top_p];
}

template <class elemType>
elemType seqStack<elemType>::top() const
{
    return array[top_p-1];
}

template <class elemType>
linkStack<elemType>::linkStack(): top_p(nullptr){}

template <class elemType>
linkStack<elemType>::~linkStack()
{
    Node* t;
    while (top_p)
    {
        t = top_p;
        top_p = top_p->next;
        delete t;
    }
}

template <class elemType>
void linkStack<elemType>::push(const elemType &obj)
{
    Node *tmp = new Node(obj, top_p);
    top_p = tmp;
}

template <class elemType>
elemType linkStack<elemType>::pop()
{
    elemType res = top();
    Node *tmp = top_p;
    top_p = top_p->next;
    delete tmp;
    return res;
}

#endif