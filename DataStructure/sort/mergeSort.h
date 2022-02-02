#ifndef Merge
#define Merge

template <typename T>
class MergeSort
{
public:
    void sort(T*, int len);

private:
    void sort(T*, int left, int right);
    void merge(T*, int left, int mid, int right);
};

template <typename T>
void MergeSort<T>::sort(T* array, int len)
{
    sort(array, 0, len-1);
}

template <typename T>
void MergeSort<T>::sort(T* array, int left, int right)
{
    if (left == right)
        return;
    int mid = (left + right + 1) >> 1;
    sort(array, left, mid-1);
    sort(array, mid, right);
    merge(array, left, mid, right);
}

template <typename T>
void MergeSort<T>::merge(T* array, int left, int mid, int right)
{
    T *tmp = new T[right - left + 1];
    int i = left, j = mid, t = 0;
    while (i <= mid-1 && j <= right)
    {
        if (array[i] < array[j])
            tmp[t++] = array[i++];
        else
            tmp[t++] = array[j++];
    }
    while (i <= mid-1)
        tmp[t++] = array[i++];
    while (j <= right)
        tmp[t++] = array[j++];

    for (int k = 0; k < right - left + 1; ++k)
        array[left + k] = tmp[k];
    delete []tmp;
}

#endif