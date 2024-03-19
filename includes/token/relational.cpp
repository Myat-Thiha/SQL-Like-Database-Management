#include "relational.h"

Relational::Relational()
{
    _r=string();
}

Relational::Relational(string r)
{
    _r=r;
}

void Relational::Print(ostream& outs) const
{
    outs<<"Printing Relational :";
    outs<<"["<<_r<<"]";
}