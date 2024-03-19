#ifndef TOKENSTR_H
#define TOKENSTR_H

#include<iostream>
#include"token.h"
#include "constant.h"
using namespace std;

class TokenStr: public Token
{
    public:
        TokenStr();
        TokenStr(string str);
        void Print(ostream& outs=cout) const;
        TOKEN_TYPES TypeOf(){return TOKENSTRING;}
        string string_only(){return _str;}
    private:
        string _str;
};




#endif //TOKENSTR