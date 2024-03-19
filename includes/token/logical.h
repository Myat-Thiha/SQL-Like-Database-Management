#ifndef LOGICAL_H
#define LOGICAL_H

#include <iostream>
#include "token.h"
#include "constant.h"
using namespace std;

class Logical: public Token
{
    public:
        Logical();
        Logical(string l);
        void Print(ostream& outs=cout) const;
        TOKEN_TYPES TypeOf(){return LOGICAL;}
        string string_only(){return _l;}
    private:
        string _l;
};


#endif //LOGICAL_H