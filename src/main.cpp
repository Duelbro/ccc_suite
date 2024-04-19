#include <map>
#include "ccc_suite.h"

void solution(istream &in, ostream &out) {

    string s;
    getline(in, s);
    while (!getline(in, s).eof()) {
        map<char, int> totals;

        for (char c : s) {
            totals[c]++;
        }

        out << totals['W'] << " " << totals['D'] << " " << totals['S'] << " "
            << totals['A'] << '\n';
    }
}
