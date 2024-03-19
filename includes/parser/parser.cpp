#include "parser.h"
#include "string"
int Parser::_table[MAX_ROWS][MAX_COLUMNS];

Parser::Parser()
{
    build_keyword_list();
    flag=false;
}

Parser::Parser(char str[])
{
    set_string(str);
    // get_parser_tree(0);
}

bool Parser::success()
{
    return flag;
} 

void Parser::set_string(char str[])
{
    _ptree.clear();
    _keywords.clear();
    input_queue.clear();
    strcpy(_buffer,str);
    STokenizer stk(_buffer);
    Token1 t;
    string hold;
    stk>>t;
    if(t.type_string()=="STRING")
    {
        hold=t.token_str();
        hold.erase(hold.begin());
        hold.erase(hold.end());
        input_queue.push_back(hold);
        //cout<<setw(10)<<t.type_string()<<setw(10)<<t<<endl;
    }
    else if(t.type_string()!="SPACE" && t.type_string()!="PUNC")
    {
        input_queue.push_back(t.token_str());
        //cout<<setw(10)<<t.type_string()<<setw(10)<<t<<endl;
    } 
    while(stk.more())
    {
        t=Token1();
        stk>>t;
        if(t.type_string()=="STRING")
    {
        hold=t.token_str();
        hold.erase(hold.begin());
        hold.pop_back();
        input_queue.push_back(hold);
        //cout<<setw(10)<<t.type_string()<<setw(10)<<t<<endl;
    }
        else if(t.type_string()!="SPACE" && t.type_string()!="PUNC")
        {
            input_queue.push_back(t.token_str());
            //cout<<setw(10)<<t.type_string()<<setw(10)<<t<<endl;
        }
    }
    //cout<<"size of input_queue is "<<input_queue.size()<<endl;
    //cout<<"size is "<<input_queue.size()<<endl;
    flag=get_parser_tree(0);
    // if(!flag)
    // {
    //     cout<<"wrong input!!!"<<endl;
    // }
}

long Parser::get_column(string str)
{
    bool flag;
    flag=_keywords.contains(str);
    if(flag)
        {
            return _keywords[str];
        }
    else
        return SYM;
}

bool Parser::get_parser_tree(int start_state)
{
    build_keyword_list();
    int state=start_state;
    int column;
    string yes="YES";
    //cout<<"input queue is "<<input_queue<<endl;
    for(int i=0; i<input_queue.size(); i++)
    {
        column=get_column(input_queue[i]);
        if(_table[state][column]!=-1 || _table[state][column]!=1)
        {
            switch(state){
            case 0:
            {
                _ptree["command"]+=input_queue[i];
                state=_table[state][column];
                break;
            }
            case 1:
            {
                if(column==FROM || column==TABLE || column==INTO)
                {
                    state=_table[state][column];
                    break;
                }
                _ptree["fields"]+=input_queue[i];
                state=_table[state][column];
                break;
            }
            case 2:
            {
                _ptree["cols"]+=input_queue[i];
                state=_table[state][column];
                break;
            }
            case 3:
            {
                _ptree["table_name"]+=input_queue[i];
                state=_table[state][column];
                break;
            }
            case 4:
            {
                if(column==WHERE)
                {
                    _ptree["where"]+=yes;
                    state=_table[state][column];
                    break;
                }
                else if(column==FIELDS)
                {
                    _ptree["cols"];
                    state=_table[state][column];
                    break;
                }
                else if(column==VALUES)
                {
                    _ptree["values"];
                    state=_table[state][column];
                    break;
                }
                else
                {
                    _ptree["condition"];
                    state=_table[state][column];
                    break;
                }
            }
            case 5:
            {
                _ptree["condition"]+=input_queue[i];
                state=_table[state][column];
                break;
            }
            case 6:
            {
                _ptree["values"]+=input_queue[i];
                state=_table[state][column];
                break;
            }
            default:
            {
                state=_table[state][column];
                break;
            }  
        }
        }
    }
    if(_table[state][column]!=-1 && _table[state][column]!=0){
    return true;}
    else
    {
    //_ptree.clear();
    return false;
    }
}

void Parser::build_keyword_list()
{
    _keywords.insert("select",SELECT);
    _keywords.insert("from",FROM);
    _keywords.insert("*",STAR);
    _keywords.insert("where",WHERE);
    _keywords.insert("make",MAKE);
    _keywords.insert("into",INTO);
    _keywords.insert("insert",INSERT);
    _keywords.insert("table",TABLE);
    _keywords.insert("values",VALUES);
    _keywords.insert("fields",FIELDS);
    make_table();
}

void Parser::make_table()
{
    init_table(_table);
    mark_fail(_table,0);
    mark_fail(_table,1);
    mark_fail(_table,3);
    mark_success(_table,4);
    mark_success(_table,2);
    mark_success(_table,6);
    mark_success(_table,5);

    mark_cell(0,_table,SELECT,1);
    mark_cell(0,_table,MAKE,1);
    mark_cell(0,_table,INSERT,1);
    mark_cell(1,_table,TABLE,3);
    mark_cell(1,_table,INTO,3);
    mark_cell(1,_table,SYM,1);
    mark_cell(1,_table,STAR,1);
    mark_cell(1,_table,FROM,3);
    mark_cell(3,_table,SYM,4);
    mark_cell(4,_table,SYM,4);
    mark_cell(4,_table,WHERE,5);
    mark_cell(4,_table,VALUES,6);
    mark_cell(4,_table,FIELDS,2);
    mark_cell(2,_table,SYM,2);
    mark_cell(6,_table,SYM,6);
    mark_cell(5,_table,SYM,5);
}

mmap_ss Parser::parse_tree()
{
    return _ptree;
}