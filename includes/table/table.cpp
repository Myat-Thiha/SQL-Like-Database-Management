#include "table.h"

Table::Table()
{
    r=FileRecord();
    size=0;
    table_name="empty";
}

Table::Table(const string& name)
{
   fstream f;
   table_name=name;
   size=0;
   string field_name=name+".bin";
    open_fileRW(f,field_name.c_str()); //open field file
    int i = 0;
    long bytes = r.read(f, i); 
    set_fields(r.vectorstr());
   f.close();
//now time for value file
   open_fileRW(f,table_name.c_str());
   i=0;
   bytes=r.read(f,i);
   while(bytes>0){
       reindex(r.vectorstr(),i);
       i++;
       bytes = r.read(f,i);
       size++;
   }
  f.close(); 
}

Table::Table(const string& name,const vectorstr fields)
{
    fstream f;
    table_name=name;
    size=0;

    open_fileW(f,table_name.c_str());
    f.close();

    string field_name=name+".bin";
    open_fileW(f,field_name.c_str());
    FileRecord r(fields);
    r.write(f);
    f.close();
    set_fields(fields);
}

void Table::set_fields(vectorstr fields)
{
    field_names = fields;
    for(int i=0; i<fields.size(); i++){
        field_map.insert(fields[i],i);
        data.push_back(MMap<string,long>());
    }
}

void Table::reindex(vectorstr v, int recno)
{
    for(int i=0; i< v.size(); i++)
    {
        data[i].insert(v[i],recno);
    }
}

void Table::insert_into(vectorstr info)
{
    fstream f;
    long recno;
    open_fileRW(f,table_name.c_str());
    r=FileRecord(info);
    recno=r.write(f);
    reindex(info,recno);
    f.close();
    size++;
}

void Table::select_all() const
{
    FileRecord r2;
    fstream f;
    string field_name=table_name+".bin";
    if(file_exists(field_name.c_str()))
    {
    open_fileRW(f, field_name.c_str());
    int i = 0;
    long bytes = r2.read(f, i); //empty envelop to be filled by the FileRecord object
    while (bytes>0){
      cout<<r2<<endl;
      i++;
      bytes = r2.read(f, i);
    }
    f.close();
    open_fileRW(f,table_name.c_str()); 
    i = 0;
    bytes = r2.read(f, i); //empty envelop to be filled by the FileRecord object
    while (bytes>0){
      cout<<i<<r2<<endl;
      i++;
      bytes = r2.read(f, i);
    }
    f.close();
    }
}

ostream& operator<<(ostream& outs, const Table& t)
{
    outs<<"table_name: "<<t.table_name<<" records: "<<t.size<<endl;
    t.select_all();
    return outs;
}

vector<long> Table::select_recnos() const
{
    return indices;
}

vector<long> Table::get_recno(string field,string condition,const string& entry)
{
    vector <long> recno;
        if(condition == "=")
    {
        recno=data[field_map[field]][entry];
    }
    else if(condition == ">")
    { 
        MMap<string,long>::Iterator it=(data[field_map[field]].upper_bound(entry));
        while(it != data[field_map[field]].end())
        {
            recno+=(*it).value_list;
            it++;
        }
    }
    else if(condition == "<")
    {
        MMap<string,long>::Iterator begin=data[field_map[field]].begin();
        MMap<string,long>::Iterator end=(data[field_map[field]].lower_bound(entry));
        for(MMap<string,long>::Iterator it=begin; it!=end; it++)
        {
            //cout<<"Here"<<endl;
            recno+=(*it).value_list;
        }
    }
    else if(condition == ">=")
    {
        MMap<string,long>::Iterator it=(data[field_map[field]].lower_bound(entry));
        while(it != data[field_map[field]].end())
        {
            recno+=(*it).value_list;
            it++;
        }
    }
    else if(condition == "<=")
    {
        MMap<string,long>::Iterator begin=data[field_map[field]].begin();
        MMap<string,long>::Iterator end=(data[field_map[field]].upper_bound(entry));
        for(MMap<string,long>::Iterator it=begin; it!=end; it++)
        {
            //cout<<"Here"<<endl;
            recno+=(*it).value_list;
        }
    }
    else
    {
    }
    return recno;
}

Table Table::select_all()
{
    return select(field_names);
}

Table Table::select(vectorstr fields, string field, string condition, const string& entry)
{
    indices.clear();
    FileRecord r;
    fstream f1;
    string name ="select";
    Table t(name,fields);
    vector <long> recno;
    recno=get_recno(field,condition,entry);
    vectorstr record;
    open_fileRW(f1,table_name.c_str());
    for(int i=0; i<recno.size(); i++)
    {
        r.read(f1,recno[i]);
        record=r.vectorstr();
        vectorstr read;
        for(int j=0; j<fields.size(); j++)
        {
            read+=record[field_map[fields[j]]];
        }
        t.insert_into(read);
        indices.push_back(recno[i]);
    }
    return t;
}

vector<long> Table::get_recno_rpn()
{
    Stack<Token*>stack_rpn;
    Token * walker=queue_rpn.pop();
    string str1,str2;
    vector<long> recno, hold1,hold2;
    Stack<vectorl> results;
    while(walker!=nullptr)
    {
        switch(walker->TypeOf())
        {
            case TOKENSTRING:
            {
                stack_rpn.push(walker);
                break;
            }
            case RELATIONAL:
            {
                if(stack_rpn.size()>=2)
                {
                str1=static_cast<TokenStr*>(stack_rpn.pop())->string_only();
                str2=static_cast<TokenStr*>(stack_rpn.pop())->string_only();
                recno=get_recno(str2,static_cast<Relational*>(walker)->string_only(),str1);
                results.push(recno);
                //cout<<results<<endl;
                }
                break;
            }
            case LOGICAL:
            {
                if(static_cast<Logical*>(walker)->string_only()=="and")
                {
                    if(results.size()>=2)
                    {
                    //cout<<"before intersection"<<results<<endl;
                    hold1=results.pop();
                    hold2=results.pop();
                    recno=vector_intersection(hold1,hold2);
                    results.push(recno);
                    //cout<<results<<endl;
                    }
                    break;
                }
                else if(static_cast<Logical*>(walker)->string_only()=="or")
                {
                    if(results.size()>=2)
                    {
                    //cout<<"before union"<<results<<endl;
                    hold1=results.pop();
                    hold2=results.pop();
                    recno=vector_union(hold1,hold2);
                    results.push(recno);
                    //cout<<results<<endl;
                    }
                    break;
                }
            }
            default:
            {
                break;
            }
        }
        walker=queue_rpn.pop();
    }
    return results.pop();
}

Table Table::select(vectorstr fields, const Queue<Token*>& post)
{
    indices.clear();
    fstream f1;
    string name ="select";
    Table t;
    if(fields[0]=="*")
    {
        t= Table(name,field_names);
        queue_rpn=post;
    vector <long> recno;
    recno=get_recno_rpn();
    vectorstr record;
    open_fileRW(f1,table_name.c_str());
    for(int i=0; i<recno.size(); i++)
    {
        r.read(f1,recno[i]);
        record=r.vectorstr();
        vectorstr read;
        for(int j=0; j<field_names.size(); j++)
        {
            read+=record[field_map[field_names[j]]];
        }
        t.insert_into(read);
        indices.push_back(recno[i]);
    }
    return t;
    }
    else
    {
        t= Table(name,fields);
        queue_rpn=post;
    vector <long> recno;
    recno=get_recno_rpn();
    vectorstr record;
    open_fileRW(f1,table_name.c_str());
    for(int i=0; i<recno.size(); i++)
    {
        r.read(f1,recno[i]);
        record=r.vectorstr();
        vectorstr read;
        for(int j=0; j<fields.size(); j++)
        {
            read+=record[field_map[fields[j]]];
        }
        t.insert_into(read);
        indices.push_back(recno[i]);
    }
    return t;
    }
}

Table Table::select(vectorstr fields, const vectorstr& condition)
{
    Queue<Token*> cond;
    for(int i=0; i<condition.size(); i++)
    {
        if(condition[i]=="<" || condition[i]==">" || condition[i]=="<=" ||condition[i]==">="||condition[i]=="=")
        {
            cond.push(new Relational(condition[i]));
        }
        else if(condition[i]=="and"||condition[i]=="or")
        {
            cond.push(new Logical(condition[i]));
        }
        else if(condition[i]=="(")
        {
            cond.push(new LeftParen());
        }
        else if(condition[i]==")")
        {
            cond.push(new RightParen());
        }
        else
        {
            cond.push(new TokenStr(condition[i]));
        }
    }
    ShuntingYard sy(cond);
    cond=sy.postfix();
    //cout<<"cond is "<<cond<<endl;
    return select(fields,cond);
}

Table Table::select(vectorstr fields)
{
    indices.clear();
    fstream f;
    FileRecord r;
    string name ="select";
    Table t(name,fields);
    open_fileRW(f,table_name.c_str());
    int i = 0;
    vectorstr record;
    long bytes = r.read(f, i); //empty envelop to be filled by the FileRecord object
    while (bytes>0){
      record=r.vectorstr();
        vectorstr read;
        for(int j=0; j<fields.size(); j++)
        {
            read+=record[field_map[fields[j]]];
        }
        t.insert_into(read);
        indices.push_back(i);
      i++;
      bytes = r.read(f, i);
    }
    f.close();
    return t;
}