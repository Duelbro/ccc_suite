#include "ccc_suite.h"

void do_things(istream &in, ostream &out) {
    cout << "Hello World!\n";

    string s;
    while(!in.eof()){
        in >> s;
        out << s;
    }
}
