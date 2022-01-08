#ifndef LLI
#define LLI

#include <iostream>

class LongLongInt
{
    friend LongLongInt operator+(const LongLongInt&, const LongLongInt&);
    friend LongLongInt operator-(const LongLongInt&, const LongLongInt&);
    friend std::ostream &operator<<(std::ostream&, const LongLongInt&);
    friend std::istream &operator>>(std::istream&, LongLongInt&);
public:
    LongLongInt (const char *n = "");
    LongLongInt (const LongLongInt &);
    ~LongLongInt (){
        delete num;
    }
    LongLongInt (LongLongInt &&);
    LongLongInt &operator=(const LongLongInt&);

private:
    char *num;
    int sign; //1 or -1
};  

#endif