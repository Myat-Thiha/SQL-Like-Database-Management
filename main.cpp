#include <iostream>
#include <iomanip>

#include "includes/sql/sql.h"
using namespace std;

int main(int argv, char** argc) {
    cout << "\n\n"
         << endl;
    SQL sql;
    sql.Batch("_!select-1.txt");
    cout << "\n\n\n=====================" << endl;
    sql.run();
    return 0;
}
