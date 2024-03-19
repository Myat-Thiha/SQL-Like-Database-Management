#include"rightparen.h"

RightParen::RightParen()
{
    paren=")";
}

void RightParen::Print(ostream& outs) const
{
    outs<<"Printing Rightparen: ";
    outs<<"["<<paren<<"]";
}