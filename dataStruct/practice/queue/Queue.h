#ifndef QUEUE
#define QUEUE

#include <iostream>

template <typename T>
class Queue
{
public:
    virtual bool isEmpty()const = 0;
    virtual void enQueue(const T&) = 0;
    virtual T deQueue() = 0;
    virtual T getHead()const = 0;
    virtual ~Queue(){}
};

template <typename T>
class seqQueue: public Queue<T>
{
public:
    seqQueue(int size = 10);
    ~seqQueue(){delete []elem;}

    bool isEmpty()const {return (front == rear);}
    void enQueue(const T&);
    T deQueue();
    T getHead()const;

private:
    T *elem;
    int maxSize;
    int front, rear;
    void doubleSpace();
};

template <typename T>
class linkQueue: public Queue<T>
{
    struct Node
    {
        T val;
        Node *next;
        Node (Node *p = nullptr): next(p){}
        Node (const T &obj, Node *p = nullptr): val(obj), next(p){}
        ~Node () = default;
    };
public:
    linkQueue();
    ~linkQueue();

    bool isEmpty()const {return (front == nullptr);}
    void enQueue(const T&);
    T deQueue();
    T getHead()const;

private:
    Node *front, *rear;
};

template <typename T>
seqQueue<T>::seqQueue(int size): maxSize(size), front(0), rear(0)
{
    elem = new T[maxSize + 1];
}

template <typename T>
void seqQueue<T>::doubleSpace()
{
    maxSize *= 2;
    T *tmp = new T[maxSize + 1];
    for (int i = 1; i <= maxSize/2; ++i)
        tmp[i] = elem[i];
    delete []elem;
    elem = tmp;
    front = 0, rear = maxSize/2;
}

template <typename T>
void seqQueue<T>::enQueue(const T &obj)
{
    if ((rear + 1) % (maxSize + 1) == front)
        this->doubleSpace(), std::cout << "double space!\n";
    rear = (rear + 1) % (maxSize + 1);
    elem[rear] = obj;
}

template <typename T>
T seqQueue<T>::deQueue()
{
    front = (front + 1) % (maxSize + 1);
    return elem[front];
}

template <typename T>
T seqQueue<T>::getHead() const
{
    return elem[(front + 1) % (maxSize + 1)];
}

template <typename T>
linkQueue<T>::linkQueue(): front(nullptr), rear(nullptr){}

template <typename T>
linkQueue<T>::~linkQueue()
{
    Node *pre;
    while (front != nullptr)
    {
        pre = front;
        front = front->next;
        delete pre;
    }
}

template <typename T>
void linkQueue<T>::enQueue(const T& obj)
{
    if (rear == nullptr)
        front = rear = new Node(obj);
    else
        rear = rear->next = new Node(obj);
}

template <typename T>
T linkQueue<T>::deQueue()
{
    T res;
    if (front == rear)
    {
        res = front->val;
        delete front;
        front = rear = nullptr;
    }
    else{
        Node *tmp = front;
        front = front->next;
        res = tmp->val;
        delete tmp;
    }
    return res;
}

template <typename T>
T linkQueue<T>::getHead() const
{
    return front->val;
}

#endif