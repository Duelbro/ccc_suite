#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <memory>
#include <ostream>
#include <string>

#include "ccc_suite.h"

enum Style { R, P, S };

char fight(char a, char b) {
    switch (a) {
        case 'R':
            return b != 'P' ? a : b;
        case 'P':
            return b != 'S' ? a : b;
        case 'S':
            return b != 'R' ? a : b;
    }
    return '?';
}

string round(const string &contestants) {
    string winners(contestants.size() / 2, ' ');

    for (int i = 0; i < winners.size(); i++) {
        winners[i] = fight(contestants[2 * i], contestants[2 * i + 1]);
    }
    return winners;
}

string generate_pairing(int r, int p, int s) {
    int n = r + p + s;
    string pairing(n, ' ');
    pairing[0] = 'S';
    s--;
    while (n >= 2) {
        if (p > 0) {
            pairing[n / 2] = 'P';
            p--;
        } else {
            pairing[n / 2] = 'S';
            s--;
        }
        for (int i = n / 2 + 1; i < n; i++) {
            if (r > 0) {
                pairing[i] = 'R';
                r--;
            } else if (p > 0) {
                pairing[i] = 'P';
                p--;
            } else {
                pairing[i] = 'S';
                s--;
            }
        }
        cout << pairing << '\n';
        n /= 2;
    }
    return pairing;
}
void fix(string &contestants, int n, int &r, int &s, int &p) {
    if (n <= 0) {
        return;
    }

    if (p > 0) {
        contestants[n - 4] = 'P';
        p--;
    } else if (s > 0) {
        contestants[n - 4] = 'S';
        s--;
    }

    for (int i = n - 3; i < n; i++) {
        if (i == 0) {
            if (s > 0) {
                contestants[i] = 'S';
                s--;
            }
            return;
        }

        if (r > 0) {
            contestants[i] = 'R';
            r--;
        } else if (p > 0) {
            contestants[i] = 'P';
            p--;
        } else if (s > 0) {
            contestants[i] = 'S';
            s--;
        }
    }

    fix(contestants, n - 4, r, s, p);
}

void verify(const string &result, int r, int p, int s) {
    int cr = 0, cs = 0, cp = 0;
    for (char c : result) {
        switch (c) {
            case 'R':
                cr++;
                break;
            case 'S':
                cs++;
                break;
            case 'P':
                cp++;
                break;
        }
    }

    assert(cr == r && "budget error");
    assert(cs == s && "budget error");
    assert(cp == p && "budget error");

    string third = round(round(result));

    bool s_present = false;
    for (char c : third) {
        assert(c != 'R' && "rock in third stage");
        s_present |= c == 'S';
    }

    assert(s_present && "no scissors in third stage");
}

void solution(istream &in, ostream &out) {
    string str;
    getline(in, str);
    while (!getline(in, str).eof()) {
        char *parse_ptr;
        int r = strtol(str.c_str(), &parse_ptr, 10);
        cout << r;
        int p = strtol(parse_ptr + 2, &parse_ptr, 10);
        cout << p;
        int s = strtol(parse_ptr + 2, &parse_ptr, 10);
        string nstr(r + s + p, ' ');
        int cr = r, cs = s, cp = p;
        fix(nstr, r + s + p, r, s, p);
        verify(nstr, cr, cp, cs);
        out << nstr << "\r\n";
    }
    out.flush();
}
