#ifndef BASEQUEUE
#define BASEQUEUE

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

#endif