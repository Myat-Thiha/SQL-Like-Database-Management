#ifndef SQL_H
#define SQL_H

#include "../table/typedefs.h"
#include "../table/table.h"
#include "../parser/parser.h"
#include <iostream>
#include <iomanip>
using namespace std;

class SQL
{
    public:
    SQL();
    SQL(string file_name);
    void Batch(string file_name);
    Table command(const string& command);
    vectorl select_recnos() const;
    void run();
    // void insert();
    // void select();
    // void create_table();
    // bool get_sql_command();


    private:
    vectorstr _table_names;
    Parser _parser;
    Table _table;
};


#endif //SQL_H