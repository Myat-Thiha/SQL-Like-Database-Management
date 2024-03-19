#include "logical.h"

Logical::Logical()
{
    _l=string();
}

Logical::Logical(string l)
{
    _l=l;
}

void Logical::Print(ostream& outs) const
{
    outs<<"Printing Logical :";
    outs<<"["<<_l<<"]";
}