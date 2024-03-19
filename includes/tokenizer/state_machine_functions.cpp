#include "state_machine_functions.h"
#include "constants.h"
#include <cstring>
using namespace std;

//Fill all cells of the array with -1
void init_table(int _table[][MAX_COLUMNS])
{
    for(int row=0; row < MAX_ROWS; row++)
    {
        for(int column=1; column < MAX_COLUMNS; column++)
        {
            _table[row][column]=-1;
        }
    }
}

//Mark this state (row) with a 1 (success)
void mark_success(int _table[][MAX_COLUMNS], int state)
{
    _table[state][0]=1;
}

//Mark this state (row) with a 0 (fail)
void mark_fail(int _table[][MAX_COLUMNS], int state)
{
    _table[state][0]=0;
}

//true if state is a success state
bool is_success(int _table[][MAX_COLUMNS], int state)
{
    if(_table[state][0]==1)
    {
        return true;
    }
    return false;
}

//Mark a range of cells in the array. 
void mark_cells(int row, int _table[][MAX_COLUMNS], int from, int to, int state)
{
    for(int i=from; i< to+1; i++)
    {
        _table[row][i]=state;
    }
}

//Mark columns represented by the string columns[] for this row
void mark_cells(int row, int _table[][MAX_COLUMNS], const char columns[], int state)
{
    for(int i=0; i<strlen(columns); i++)     //using strlen includes null
    {
        _table[row][columns[i]]=state;
    }
}

//Mark this row and column
void mark_cell(int row, int table[][MAX_COLUMNS], int column, int state)
{
    table[row][column]=state;
}

//This can realistically be used on a small table
void print_table(int _table[][MAX_COLUMNS])
{
    for(int row=0; row < MAX_ROWS; row++)
    {
        for(int column=0; column < MAX_COLUMNS; column++)
        {
            cout<<" "<<_table[row][column];
        }
        cout<<endl;
        cout<<endl;
    }
}

//show string s and mark this position on the string:
//hello world   pos: 7
//       ^
void show_string(char s[], int _pos)
{
    for(int i=0; i< strlen(s); i++)
    {
        cout<<s[i];
    }
    cout<<endl;
    cout<<"marked postion is " <<s[_pos]<<endl;
}