#ifndef Shell
#define Shell

template <typename T>
class ShellSort
{
public:
    void sort(T*, int len, int gap = 0);
    void insertionsort(T*, int len, int gap = 1);
};

template <typename T>
void ShellSort<T>::sort(T* array, int len, int gap)
{
    if (len == 1)
        return;
    if (gap <= 0)
        gap = len >> 1;
    while (gap > 0)
    {
        insertionsort(array, len, gap);
        gap /= 2;
    }
}

template <typename T>
void ShellSort<T>::insertionsort(T* array, int len, int gap)
{
    T tmp;
    for (int i = gap; i < len; i += gap)
    {
        tmp = array[i];
        while (i >= gap && array[i-gap] > tmp)
        {
            array[i] = array[i-gap];
            i -= gap;
        }
        array[i] = tmp;
    }
}

#endif