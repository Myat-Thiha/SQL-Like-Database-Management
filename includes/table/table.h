#ifndef TABLE_H
#define TABLE_H

#include "typedefs.h"
#include "../shunting_yard/shunting_yard.h"
using namespace std;

class Table{
    public:
    Table();
    Table(const string& name);
    Table(const string& name,const vectorstr fields);

    void insert_into(vectorstr info);

    void select_all() const;
    Table select_all();
    Table select(vectorstr fields);
    Table select(vectorstr fields, string field, string condition, const string& entry);
    Table select(vectorstr fields, const Queue<Token*>& post);
    Table select(vectorstr fields, const vectorstr& condition);
    vector<long> get_recno(string field,string condition,const string& entry);
    vector<long> get_recno_rpn();

    friend ostream& operator<<(ostream& outs, const Table& t);
    void set_fields(vectorstr fields);
    vector<string> get_fields();
    void reindex(vectorstr v, int recno);
    vector<long> select_recnos() const;


    private:
    bool empty();
    long serial;
    string table_name;
    FileRecord r;
    int size;
    vector<string> field_names;
    vector<long> indices;
    Map<string,long>field_map;
    vector<MMap<string,long>> data;

    Queue<Token*>queue_rpn;
};


#endif //TABLE_H