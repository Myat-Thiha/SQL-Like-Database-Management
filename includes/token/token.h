#ifndef TOKEN1_H
#define TOKEN1_H

#include <iostream>
#include "constant.h"
using namespace std;

class Token
{
public:
    Token();
    friend ostream& operator <<(ostream& outs, const Token& token);
    friend ostream& operator <<(ostream& outs, const Token* token);
    virtual void Print(ostream& outs=cout) const;
    virtual TOKEN_TYPES TypeOf(){return TOKEN;}
};




#endif 