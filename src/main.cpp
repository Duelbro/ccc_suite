#include <ostream>
#include <string>
#include "ccc_suite.h"

enum Style {R,P,S};

char fight(char a, char b) {
    switch (a) {
        case 'R': return b != 'P' ? a : b;
        case 'P': return b != 'S' ? a : b;
        case 'S': return b != 'R' ? a : b;
    }
    return '?';
} 

void solution(istream &in, ostream &out) {
    string s;
    getline(in, s);
    while(!getline(in, s).eof()){
        out << fight(s[0], s[1]) << '\n';
    }
    out.flush();
}


