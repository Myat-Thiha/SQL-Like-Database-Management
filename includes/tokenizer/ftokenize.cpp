#include "ftokenize.h"

FTokenizer::FTokenizer(char* fname)
{
    _f.open(fname);
    if(_f.fail())
    {
        cout<<"Cannot open file"<<endl;
        exit(1);
    }
    cout<<"End"<<endl;
    _more=get_new_block();
    _pos=0;
    _blockPos=0;
}

Token1 FTokenizer::next_token()
{
    Token1 t;
    //cout<<"next_token"<<endl;
    if(_stk.done())
    //for(int i=0; i< 5; i++)
    {
        //cout<<"loop ... "<<endl;
        _more = get_new_block(); 
    }
    _stk>>t;
    return t;
}
bool FTokenizer::more()
{
    return _more;
}

int FTokenizer::pos()
{
    return _pos;
}

int FTokenizer::block_pos()
{
    return _blockPos;
}

FTokenizer& operator >> (FTokenizer& f, Token1& t)
{
    //cout<<"this is >> "<<endl;
    t=f.next_token();
    return f;
}

bool FTokenizer::get_new_block()
{
    //cout<<"Getting into get_new_block"<<endl;
    char input[MAX_BUFFER];
    if(_f.eof())
    {
        //cout<<"eofffff"<<endl;
        _f.close();
        return false;
    }
    else
    {
        //cout<<"elseeeee"<<endl;
        _f.read(input,MAX_BUFFER-1);
        input[_f.gcount()]='\0';
        //cout<<"input is "<<input<<endl;
        _stk.set_string(input);
        return true;
    }
}