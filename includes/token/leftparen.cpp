#include"leftparen.h"

LeftParen::LeftParen()
{
    paren= "(";
}
void LeftParen::Print(ostream& outs) const
{
    outs<<"Printing LeftParen: ";
    outs<<"["<<paren<<"]";
}