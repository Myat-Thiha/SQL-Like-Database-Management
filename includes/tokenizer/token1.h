#ifndef TOKEN_H
#define TOKEN_H
#include <iostream>
#include <string>
using namespace std;

class Token1
{
public:
    Token1();
    Token1(string str, int type);
    friend ostream& operator <<(ostream& outs, const Token1& t);
    int type() const;
    string type_string() const;
    string token_str() const;
private:
    string _token;
    int _type;
};

#endif //TOKEN_H