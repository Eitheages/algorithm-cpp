#ifndef BINARYHEAP
#define BINARYHEAP

#include "base.h"
#include <iostream>

// based on binary heap
template <typename T>
class priorityQueue: public Queue<T>
{
    template <typename U>
    friend std::ostream &operator<<(std::ostream &os, const priorityQueue<U> &obj);
public:
    priorityQueue(int size = 5);
    priorityQueue(T* data, int size);
    bool isEmpty()const;
    void enQueue(const T&);
    T deQueue();
    T getHead()const;
    ~priorityQueue(){delete []array;}

private:
    T *array;
    int maxsize;
    int cur;
    void doubleSpace();
    void buildHeap();
    void percolateDown(int);
};

template <typename T>
priorityQueue<T>::priorityQueue(int size): maxsize(size), cur(0)
{
    array = new T[maxsize + 1];
}

template <typename T>
priorityQueue<T>::priorityQueue(T* data, int size): maxsize(size), cur(size)
{
    array = new T[maxsize + 1];
    for (int i = 0; i < size; ++i)
        array[1 + i] = data[i];
    buildHeap();
}

template <typename T>
bool priorityQueue<T>::isEmpty() const {return cur == 0;}

template <typename T>
void priorityQueue<T>::enQueue(const T& ele)
{
    if (cur == maxsize)
        doubleSpace();

    int i = ++cur;

    while (i >= 2 && array[i >> 1] > ele)
    {
        array[i] = array[i >> 1];
        i = i >> 1;
    }
    array[i] = ele;
}

template <typename T>
void priorityQueue<T>::doubleSpace()
{
    maxsize = maxsize << 1;
    T *tmp = array;
    array = new T[maxsize + 1];
    for (int i = 1; i <= cur; ++i)
        array[i] = tmp[i];
    delete []tmp;
}

template <typename T>
T priorityQueue<T>::deQueue()
{
    array[0] = array[1];
    array[1] = array[cur--];
    percolateDown(1);
    return array[0];
}

template <typename T>
void priorityQueue<T>::percolateDown(int i)
{
    int child;
    T tmp = array[i];

    while ((i << 1) < cur)
    {
        child = i << 1;

        if (array[child] > array[child + 1])
            ++child;
        if (array[child] >= tmp)
            break;
        else
            array[i] = array[child], i = child;
    }
    if ((i << 1) == cur && array[i << 1] < array[i])
        array[i] = array[i << 1], i = i << 1;

    array[i] = tmp;
}

template <typename T>
void priorityQueue<T>::buildHeap()
{
    int i = cur >> 1;

    while (i >= 1)
        percolateDown(i--);
}

template <typename U>
std::ostream &operator<<(std::ostream &os, const priorityQueue<U> &obj)
{
    for (int i = 1; i <= obj.cur; ++i)
        os << obj.array[i] << ' ';
    return os;
}

template <typename T>
T priorityQueue<T>::getHead() const
{
    return array[1];
}

#endif