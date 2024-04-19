#include <map>

#include "ccc_suite.h"

void solution(istream &in, ostream &out) {
    string s;
    getline(in, s);
    while (!getline(in, s).eof()) {
        int max_x = 0, max_y = 0, min_x = 0, min_y = 0, x = 0, y = 0;

        for (char c : s) {
            switch (c) {
                case 'W':
                    y--;
                    break;
                case 'D':
                    x++;
                    break;
                case 'S':
                    y++;
                    break;
                case 'A':
                    x--;
                    break;
            }
            max_x = max(max_x, x);
            max_y = max(max_y, y);
            min_x = min(min_x, x);
            min_y = min(min_y, y);

        }

        out << max_x - min_x + 1 << " " << max_y - min_y + 1 << "\r\n";
    }
}
