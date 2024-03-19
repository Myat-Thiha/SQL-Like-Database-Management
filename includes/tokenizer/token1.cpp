#include "token1.h"

Token1::Token1()
{
    _token=" ";
    _type=0;
}

Token1::Token1(string str, int type)
{
    _token=str;
    _type=type;
}

ostream& operator <<(ostream& outs, const Token1& t)
{
    outs<< "   |"<<t.token_str()<<"|"<<endl;
    return outs;
}

int Token1::type() const
{
    return _type;
}

string Token1::type_string() const
{
    if(_type==1)
    {
        return "ALPHA";
    }
    else if((_type==2)||(_type==7))
    {
        return "DOUBLE";
    }
    else if(_type==3)
    {
        return "OPERATOR";
    }
    else if(_type==4)
    {
        return "SPACE";
    }
    else if(_type==5)
    {
        return "PUNC";
    }
    else if(_type==10)
    {
        return "STRING";
    }
    else
        return "UNKNOWN";
}

string Token1::token_str() const
{
    return _token;
}