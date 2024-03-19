#include "tokenstr.h"

TokenStr::TokenStr()
{
    _str=string();
}

TokenStr::TokenStr(string str)
{
    _str=str;
}

void TokenStr::Print(ostream& outs) const
{
    outs<<"Printing TokenStr :";
    outs<<"["<<_str<<"]";
}