#ifndef QUICK
#define QUICK

template <typename T>
class QuickSort
{
public:
    QuickSort(){
        divides[0] = &QuickSort::divideI;
        divides[1] = &QuickSort::divideII;
        divides[2] = &QuickSort::divideIII;
    }
    void sort(T*, int len, int pattern = 0);

private:
    void sort(T*, int left, int right, int pattern);
    int divideI(T*, int left, int right);
    int divideII(T*, int left, int right);
    int divideIII(T*, int left, int right);
    void swap(T&, T&);

    typedef int (QuickSort::*fp)(T*, int, int);
    fp divides[3];
};

template <typename T>
void QuickSort<T>::sort(T* array, int len, int pattern)
{
    sort(array, 0, len-1, pattern);
}

template <typename T>
void QuickSort<T>::sort(T* array, int left, int right, int pattern)
{
    if (left >= right)
        return;
    int m = (this->*divides[pattern])(array, left, right);
    sort(array, left, m-1, pattern);
    sort(array, m+1, right, pattern);
}

template <typename T>
int QuickSort<T>::divideI(T* array, int left, int right)
{
    T pivot = array[left];
    int i = left, j = right;
    while (i != j)
    {
        while (j != i && array[j] >= pivot)
            --j;
        if (j != i)
            array[i++] = array[j];
        while (j != i && array[i] <= pivot)
            ++i;
        if (j != i)
            array[j--] = array[i];
    }
    array[i] = pivot;
    return i;
}

template <typename T>
int QuickSort<T>::divideII(T* array, int left, int right)
{
    T pivot = array[left];
    int i = left, j = right;
    while (i != j)
    {
        while (i != j && array[j] >= pivot)
            --j;
        while (i != j && array[i] <= pivot)
            ++i;
        if (i != j)
            swap(array[i], array[j]);
    }
    array[left] = array[i];
    array[i] = pivot;
    return i;
}

template <typename T>
int QuickSort<T>::divideIII(T* a, int left, int right)
{
    T pivot = a[left];
    int i = left, j = left + 1;
    while (j <= right)
    {
        if (a[j] < pivot)
            swap(a[i++], a[j]);
        ++j;
    }
    a[i] = pivot;
    return i;
}

template <typename T>
void QuickSort<T>::swap(T& a, T& b)
{
    T tmp = a;
    a = b;
    b = tmp;
}

#endif