#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <ios>
#include <iostream>
#include <map>
#include <ostream>
#include <queue>
#include <set>
#include <string>
#include <vector>

// #include "ccc_suite.h"

enum Style { R, P, S };

char fight(char a, char b) {
    switch (a) {
        case 'R':
            return b != 'P' && b != 'Y' ? a : b;
        case 'Y':
            return b != 'P' && b != 'L' ? a : b;
        case 'P':
            return b != 'S' && b != 'L' ? a : b;
        case 'L':
            return b != 'R' && b != 'S' ? a : b;
        case 'S':
            return b != 'R' && b != 'Y' ? a : b;
        case 'X':
            return 'X';
    }
    return '?';
}

string round(const string &result_copy) {
    string winners(result_copy.size() / 2, ' ');

    for (int i = 0; i < winners.size(); i++) {
        winners[i] = fight(result_copy[2 * i], result_copy[2 * i + 1]);
    }
    return winners;
}

void fix(string &result_copy, int n, int &r, int &y, int &p, int &l, int &s) {
    printf("%i %i %i %i %i %s\n", r, y, p, l, s, result_copy.c_str());
    if (n <= 0) {
        return;
    }

    if (y > 0) {
        result_copy[n / 2] = 'Y';
        y--;
    } else if (p > 0) {
        result_copy[n / 2] = 'P';
        p--;
    } else if (l > 0) {
        result_copy[n / 2] = 'L';
        l--;
    } else if (s > 0) {
        result_copy[n / 2] = 'S';
        s--;
    } else if (r > 0) {
        result_copy[n / 2] = 'R';
        r--;
    }

    for (int i = n / 2 + 1; i < n - 1; i++) {
        if (i == 0) {
            if (s > 0) {
                result_copy[i] = 'S';
                s--;
            }
            return;
        }

        if (r > 0) {
            result_copy[i] = 'R';
            r--;
        } else if (y > 0) {
            result_copy[i] = 'Y';
            y--;
        } else if (p > 0) {
            result_copy[i] = 'P';
            p--;
        } else if (l > 0) {
            result_copy[i] = 'L';
            l--;
        } else if (s > 0) {
            result_copy[i] = 'S';
            s--;
        }
    }

    if (n > 2) {
        if (result_copy[n / 2] == 'Y') {
            if (p > 0) {
                result_copy[n - 1] = 'P';
                p--;
            } else if (l > 0) {
                result_copy[n - 1] = 'L';
                l--;
            } else if (s > 0) {
                result_copy[n - 1] = 'S';
                s--;
            } else if (r > 0) {
                result_copy[n - 1] = 'R';
                r--;
            } else if (y > 0) {
                result_copy[n - 1] = 'Y';
                y--;
            }
        } else {
            if (r > 0) {
                result_copy[n - 1] = 'R';
                r--;
            } else if (l > 0) {
                result_copy[n - 1] = 'L';
                l--;
            } else if (s > 0) {
                result_copy[n - 1] = 'S';
                s--;
            }
        }
    }

    fix(result_copy, n / 2, r, y, p, l, s);
}

void fix(int r, int y, int p, int l, int s) {
    int n = r + y + p + l + s;
    string result;
    while (r > 0) {
        if (r < n / 2) {
            result.append(r, 'R');
            r = 0;
        } else {
            result.append(n / 2 - 1, 'R');
            r -= n / 2 - 1;
            result.append('Y')
        }
    }
}

struct tourney_node {
    set<char> options;
    tourney_node *left = nullptr;
    tourney_node *right = nullptr;

    void make_children(int rounds) {
        // left child always wins
        if(rounds == 0) return;
        left = new tourney_node;
        right = new tourney_node;
        left->make_children(rounds - 1);
        right->make_children(rounds - 1);
    }

    void update_options() {
        if (left == nullptr) return;
        left->update_options(options);
        right->update_options(options);
    }
    void update_options(const set<char> &parent_options) {
        if(left == nullptr) return;
        left->options.clear();
        right->options.clear();
        for (auto c : parent_options) {
            left->options.add(c);
            for (auto c_ : get_opponents(c)) {
                right->options.add(c);
            }
        }
        left->update_options();
        right->update_options();
    }

    tourney_node *most_determined_node() {
        if (options.size() == 0) {
            if (left == nullptr) return nullptr;
            return right->options.size() < left->options.size()
                       ? right->most_determined_node()
                       : left->most_determined_node();
        } else {
            return this;
        }
        return nullptr;
    }

    static set<char> get_opponents(char winner) {
        switch (winner) {
            case 'R':
                return {'R', 'L', 'S'};
            case 'Y':
                return {'R', 'Y', 'S'};
            case 'P':
                return {'R', 'Y', 'P'};
            case 'L':
                return {'Y', 'P', 'L'};
            case 'S':
                return {'P', 'L', 'S'};
        }
        return {};
    }

    string tostring() {
        if left()
    }
}
}

tourney_node *generate_tree()

    vector<char> get_losing_against(char winner) {
    switch (winner) {
        case 'R':
            return {'R', 'L', 'S'};
        case 'Y':
            return {'R', 'Y', 'S'};
        case 'P':
            return {'R', 'Y', 'P'};
        case 'L':
            return {'Y', 'P', 'L'};
        case 'S':
            return {'P', 'L', 'S'};
    }
    return {};
}

int main(int, char**) {
  tourney_node *root = new tourney_node;
    root->make_children(2);

    
    root->options = {'S'};
    root->update_options();
    
    auto node = root->most_determined_node();

    while(node != nullptr) {
    }

}

bool expand(string &result, char winner, int depth, map<char, int> &budget) {
    printf("entered expand with '%s' and depth %i and pref. winner %c\n",
           result.c_str(), depth, winner);

    if (depth > 0) {
        map<char, int> budget_copy{budget};
        string result_copy{result};
        if (expand(result_copy, winner, depth - 1, budget_copy)) {
            budget = budget_copy;
            result = result_copy;
        } else {
            printf("failed because winner cant be placed\n");
            return false;
        }
        vector<char> opponents = get_losing_against(winner);

        bool succ = false;

        cout << result << ", " << opponents.size() << " opponents\n";

        for (char opponent : opponents) {
            auto budget_copy = budget;
            string result_copy{result};
            if (expand(result_copy, opponent, depth - 1, budget_copy)) {
                budget = budget_copy;
                result = result_copy;
                succ = true;
                break;
            }
        }
        if (!succ) printf("failed because opponent could not be placed\n");
        return succ;

    } else {
        if (budget[winner] > 0) {
            budget[winner]--;
            result.push_back(winner);
            cout << "adding " << winner << '\n';
            return true;
        } else {
            return false;
        }
    }
}

void fix_five_tournament() {
    struct comp {
        bool operator()(const string &a, const string &b) {
            return a.size() < b.size();
        }
    };
    priority_queue<string, vector<string>, comp> expansions;
    expansions.push("S");
    while (!expansions.empty()) {
        string expansion = expansions.top();
        expansions.pop();
        for (char c : expansion) {
        }
    }
}

void verify(string result) {
    while (result.length() > 1) {
        cout << result << '\n';
        result = round(result);
    }
    cout << result << '\n';
    assert(result == "S" && "not scissor winner");
}

void solution(istream &in, ostream &out) {
    string str;
    getline(in, str);
    while (!getline(in, str).eof()) {
        char *parse_ptr;
        map<char, int> budget;
        // int r = budget['R'] = strtol(str.c_str(), &parse_ptr, 10);
        // int p = budget['P'] = strtol(parse_ptr + 2, &parse_ptr, 10);
        // int s = budget['S'] = strtol(parse_ptr + 2, &parse_ptr, 10);
        // int y = budget['Y'] = strtol(parse_ptr + 2, &parse_ptr, 10);
        // int l = budget['L'] = strtol(parse_ptr + 2, &parse_ptr, 10);
        int r = budget['R'] = 1;
        int p = budget['P'] = 1;
        int s = budget['S'] = 1;
        int y = budget['Y'] = 1;
        int l = budget['L'] = 0;
        int n = r + y + p + l + s;
        string nstr;
        // fix(nstr, n, r, y, p, l, s);
        expand(nstr, 'S', 2, budget);
        verify(nstr);
        cout << "---------------\n";
        out << nstr << "\r\n";
    }
    out.flush();
}
