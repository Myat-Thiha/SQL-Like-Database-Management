#ifndef RELATIONAL_H
#define RELATIONAL_H

#include<iostream>
#include"token.h"
#include "constant.h"
using namespace std;

class Relational: public Token
{
    public:
        Relational();
        Relational(string r);
        void Print(ostream& outs=cout) const;
        TOKEN_TYPES TypeOf(){return RELATIONAL;}
        string string_only(){return _r;}
    private:
        string _r;
};




#endif //RELATIONAL_H