#include "stokenize.h"

using namespace std;

int STokenizer::_table[MAX_ROWS][MAX_COLUMNS];

STokenizer::STokenizer()
{
    _pos=0;
    make_table(_table);
    //_table[MAX_ROWS][MAX_COLUMNS];
}

STokenizer::STokenizer(char str[])
{
    set_string(str);
    _pos=0;
    make_table(_table);
    //_table[MAX_ROWS][MAX_COLUMNS];
}

//true: there are no more tokens
bool STokenizer::done()
{
    //cout<<"pos is "<<_pos<<endl;
    if(_pos>=strlen(_buffer))
        return true;
    return false;
}

//true: there are more tokens
bool STokenizer::more()
{
    //cout<<"pos is "<<_pos<<endl;
    if(done())
        return false;
    return true;
}

//extract one token (very similar to the way cin >> works)
STokenizer& operator >> (STokenizer& s, Token1& t)
{
    int end_state=0;
    string token="";
    bool flag;
    flag=s.get_token(end_state,token);
    //cout<<"I am here "<<endl;
    t=Token1(token,end_state);
    //cout<<"t is "<<t<<endl;
    return s;
}

//set a new string as the input string
void STokenizer::set_string(char str[])
{
    strcpy(_buffer, str);
    //cout<<"_buffer is "<<_buffer<<endl;
    _pos=0;
}

//create table for all the tokens we will recognize
//                      (e.g. doubles, words, etc.)
void STokenizer::make_table(int _table[][MAX_COLUMNS])
{
    init_table(_table);
        mark_fail(_table,0);
        mark_fail(_table,6);
        mark_success(_table,10);
        mark_success(_table,1);
        mark_success(_table,2);
        mark_success(_table,3);
        mark_success(_table,4);
        mark_success(_table,5);
        mark_success(_table,7);
        mark_success(_table,8);
        mark_success(_table,9);
        mark_cells(0,_table,ALFA,1);
        mark_cells(1,_table,ALFA,1);
        mark_cells(0,_table,DIGITS,2);
        mark_cells(2,_table,DIGITS,2);
        mark_cells(0,_table,OPERATORS,3);
        mark_cells(3,_table,OPERATORS,3);
        mark_cells(0,_table,SPACES,4);
        mark_cells(4,_table,SPACES,4);
        mark_cells(0,_table,PUNC,5);
        mark_cells(5,_table,PUNC,5);
        mark_cell(2,_table,'.',6);
        mark_cells(6,_table,DIGITS,7);
        mark_cells(7,_table,DIGITS,7);
        mark_cell(0,_table,STRING,8); 
        mark_cells(8,_table,ALFA,9);
        mark_cells(9,_table,ALFA,9);
        mark_cells(9,_table,SPACES,9);
        mark_cells(9,_table,PUNC,9);
        mark_cells(9,_table,DIGITS,9);
        mark_cells(9,_table,OPERATORS,9);
        mark_cell(9,_table,STRING,10);
}

//extract the longest string that match
//     one of the acceptable token types
bool STokenizer::get_token(int& end_state, string& token)
{
    //print_table(_table);
    //cout<<"The string length is "<<strlen(_buffer)<<endl;
    int next_row=0;
    int last_pos=_pos;
    int count=0;
    int current_row=0;
    int ascii=0;
    //show_string(_buffer,_pos);
    for(int i=_pos; i< strlen(_buffer);i++)
    {
        ascii=_buffer[i];
        current_row=next_row;
        next_row=_table[current_row][_buffer[i]];
        //cout<<"ascii is "<<ascii<<endl;
        //cout<<"current state "<<next_row<<endl;
        if((next_row==-1)||(ascii<=0)||(ascii>MAX_COLUMNS))
        {
            if(_table[current_row][0]==1)
            {
                last_pos=last_pos+count;
            }
            else
            {
                //cout<<"SKIPPING"<<endl;
                last_pos++;
            }
            //cout<<"The last pos is "<<last_pos<<endl;
            for(int i=_pos; i< last_pos; i++)
            {
                token+=_buffer[i];
            }
            _pos=last_pos;
            return false;
        }
        else
            if(_table[next_row][0]==1)
            {
                end_state=next_row;
                last_pos++;
            }
            else
            {
                count++;
            }
    }
    if(_table[next_row][0]==1)
    {
        last_pos=last_pos+count;
    }
    for(int i=_pos; i< last_pos; i++)
    {
        token+=_buffer[i];
    }
    
    // if(strlen(_buffer)==last_pos)
    // {
        _pos=last_pos;
    // }
    // else
    // {
    //     _pos=last_pos+1;
    // }
    //cout<<"pos is "<<_pos<<endl;
    //cout<<"end state is "<<end_state<<endl;
    return true;
}