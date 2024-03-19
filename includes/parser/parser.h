#ifndef PARSER_H
#define PARSER_H
#include "../tokenizer/stokenize.h"
#include "../table/table.h"
#include "../table/typedefs.h"
class Parser
{
    public:
    Parser();
    Parser(char str[]);
    void set_string(char str[]);
    long get_column(string str);
    bool get_parser_tree(int start_state);
    void build_keyword_list();
    void make_table();
    mmap_ss parse_tree();
    bool success();

    private:
    char _buffer[MAX_BUFFER];       //input string
    // int _pos;                       //current position in the string
    static int _table[MAX_ROWS][MAX_COLUMNS];   

    vectorstr input_queue;
    mmap_ss _ptree;
    map_sl _keywords;
    bool flag;
    enum KEYS{ZERO, SELECT, FROM, STAR, SYM, WHERE, INTO, INSERT, MAKE ,
     TABLE, VALUES, FIELDS,RELATIONAL,LOGICAL,PAREN,UNKNOWN};
};


#endif //PARSER