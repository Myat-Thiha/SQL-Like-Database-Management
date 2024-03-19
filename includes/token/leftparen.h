#ifndef LEFT_PAREN_H
#define LEFT_PAREN_H
#include<iostream>
#include<cmath>
#include"token.h"
#include "constant.h"
using namespace std;

class LeftParen: public Token
{
    public:
        LeftParen();
        void Print(ostream& outs=cout) const;
        TOKEN_TYPES TypeOf(){return LPAREN;}
    private:
        string paren;
};


#endif //LEFT_PAREN_H