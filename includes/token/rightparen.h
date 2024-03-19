#ifndef RIGHT_PAREN_H
#define RIGHT_PAREN_H
#include<iostream>
#include"token.h"
#include "constant.h"
using namespace std;

class RightParen : public Token
{
    public:
        RightParen();
        void Print(ostream& outs=cout) const;
        TOKEN_TYPES TypeOf(){return RPAREN;}
    private:
        string paren;
};

#endif //RIGHT_PAREN_H