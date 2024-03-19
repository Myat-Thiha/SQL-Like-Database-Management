#include "sql.h"

SQL::SQL()
{

}

SQL::SQL(string file_name)
{

}

Table SQL::command(const string& command)
{
    char s[300];
    vectorstr table_name;
    vectorstr fields;
    strcpy(s,command.c_str());
    Parser parser(s);
    mmap_ss ptree;
    ptree=parser.parse_tree();
    if(parser.success())
    {
    table_name =ptree["table_name"];
    if(ptree["command"][0]=="make")
    {
        fields=ptree["cols"];
        _table=Table(table_name[0],fields);
        return _table;
    }
    else if(ptree["command"][0]=="insert")
    {
        fields=ptree["values"];
        _table=Table(table_name[0]);
        _table.insert_into(fields);
        return _table;
    }
    else if(ptree["command"][0]=="select")
    {
        _table=Table(table_name[0]);
        fields=ptree["fields"];
        bool flag=ptree.contains("condition");
        if(fields[0]=="*" && !flag)
        {
            //cout<<_table.select_all();
            return _table.select_all();
        }
        else if(!flag)
        {
            return _table.select(fields);
        }
        else
        {
            return _table.select(fields,ptree["condition"]);
        }
    }
    else
    {
        //cout<<"wrong input"<<endl;
        return Table();
    }
    }
    else
    {
        cout<<"wrong input"<<endl;
        _table=Table();
        return _table;
    }
}

vectorl SQL::select_recnos()const
{
    return _table.select_recnos();
}

void SQL::Batch(string file_name)
{
    SQL sql;
    ifstream f;
    f.open(file_name);
    string str = "";
    if (!f.is_open())
    {
        cout << "input file cannot opened."<<endl;
    }
    else
    {
        while (getline(f, str))
        {
            cout<<str<<endl;
            if (str.find("make")==0 || str.find("insert")==0 || str.find("select")==0)
            {
                cout << sql.command(str) << endl;
                cout <<sql.select_recnos()<<endl;
            }
        }
        f.close();
    }
}

void SQL::run()
{
    SQL sql;
    string str = "";
    string str2 = "";
    while (str2 != "exit")
    {
        int i = 0;
        cout << "command > ";
        do
        {
            cin >> str2;
            str += str2;
            i = cin.get();
            if (i == ' ')
                str += " ";
        } while (i != '\n');
        if (str == "exit")
            break;
        cout << sql.command(str) << endl;
        str = "";
    }
}