#include "LongLongInt.h"
#include <cstring>
// #include <string>
#include <algorithm>
using namespace std;

LongLongInt::LongLongInt(const char *n)
{
    const char *tmp;

    switch (n[0])
    {
    case '+':
        tmp = n + 1;
        sign = 1;
        break;
    
    case '-':
        tmp = n + 1;
        sign = -1;
        break;

    default:
        tmp = n;
        sign = 1;
        break;
    }

    if ((strcmp(tmp, "0") == 0))
    {
        tmp = "";
        sign = 1; //规定：0的符号为1，字符串为空""
    }
    int len = strlen(tmp);
    
    num = new char[len + 1];
    for (int i = 0; i < len; i++)
        num[i] = tmp[len - i - 1];
    num[len] = '\0';
}

LongLongInt::LongLongInt(const LongLongInt &source)
{
    sign = source.sign;
    num = new char[strlen(source.num) + 1];
    strcpy(num, source.num);
}

LongLongInt &LongLongInt::operator=(const LongLongInt &other)
{
    if (&other == this)
        return *this;
    delete num;
    sign = other.sign;
    num = new char[strlen(other.num) + 1];
    strcpy(num, other.num);
    return *this;
}

LongLongInt::LongLongInt(LongLongInt &&source): num{source.num}
{
    sign = source.sign;
    source.num = nullptr;
}

//比较两个数(字符串)的绝对值，前者大于等于后者，返回true
bool compare(const char *num1, const char *num2)
{
    int len1 = strlen(num1), len2 = strlen(num2);
    if (len1 != len2)
        return len1 > len2;
    for (int i = len1 - 1; i >= 0; i--)
    {
        if (num1[i] != num2[i])
            return num1[i] > num2[i];
    }
    return true;
}

char *sub(const char *num1, const char *num2)
{
    if (strcmp(num1, num2) == 0)
    {
        char *res = new char[1];
        res[0] = 0;
        return res;
    }
    int len1 = strlen(num1), len2 = strlen(num2);
    char *tmp = new char[len1];
    int minus = 0, i = 0;
    for (; i < len2; i++)
    {
        int number = num1[i] - num2[i] - minus;
        if (number < 0)
        {
            minus = 1;
            number += 10;
        }
        else
        {
            minus = 0;
        }
        tmp[i] = number + '0';
    }
    while (i < len1)
    {
        int number = num1[i] - minus - '0';
        if (number < 0)
        {
            minus = 1;
            number += 10;
        }
        tmp[i++] = number + '0';
    }
    do
    {
        i--;
    } while (i >= 0 && tmp[i] == '0');
    tmp[i+1] = '\0';
    char *res = new char[strlen(tmp) + 1];
    strcpy(res, tmp);
    delete tmp;
    return res;
}

char *add(const char *num1, const char *num2)
{
    int len1 = strlen(num1), len2 = strlen(num2);
    int minlen = min(len1, len2);
    int len = max(len1, len2) + 1; //加和后的长整数可能最长的位数
    char *tmp = new char[len + 1];
    int carry{0};
    int i = 0;
    for (; i < minlen; i++)
    {
        int temp = num1[i] + num2[i] - 2*'0' + carry;
        tmp[i] = temp % 10 + '0';
        carry = temp / 10;
    }
    while (i < len1)
    {
        int temp = num1[i] + carry - '0';
        tmp[i] = temp % 10 + '0';
        carry = temp / 10;
        i++;
    }
    while (i < len2)
    {
        int temp = num2[i] + carry - '0';
        tmp[i] = temp % 10 + '0';
        carry = temp / 10;
        i++;
    }
    if (carry > 0)
        tmp[i++] = carry + '0';
    tmp[i] = '\0';
    char *res = new char[strlen(tmp) + 1];
    strcpy(res, tmp);
    return res;
}

LongLongInt operator+(const LongLongInt &a, const LongLongInt &b)
{
    LongLongInt res = LongLongInt();
    delete res.num;
    if (a.sign == b.sign)
    {
        res.num = add(a.num, b.num);
        res.sign = a.sign;
    }
    else if (compare(a.num, b.num))
    {
        if (a.num == b.num)
            return LongLongInt();
        res.sign = a.sign;
        res.num = sub(a.num, b.num);
    }
    else
    {
        res.sign = b.sign;
        res.num = sub(b.num, a.num);
    }
    return res;
}

LongLongInt operator-(const LongLongInt &a, const LongLongInt &b)
{
    LongLongInt tmp = b;
    tmp.sign *= -1;
    return a + tmp;
}

ostream &operator<<(ostream &os, const LongLongInt &obj)
{
    if (strlen(obj.num) == 0)
        os << 0;
    else if (obj.sign == 1)
        for (int i = strlen(obj.num)-1; i >= 0; i--)
            os << obj.num[i];
    else
    {
        os << '-';
        for (int i = strlen(obj.num)-1; i >= 0; i--)
            os << obj.num[i];
    }
    return os;
}

istream &operator>>(istream &is, LongLongInt &obj)
{
    char *n = new char[100];
    is >> n;
    obj = LongLongInt(n);
    delete n;
    return is;
}