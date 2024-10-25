#include <algorithm>
#include <cmath>
#include <cassert>
#include <set>
#include <map>
#include <unordered_map>
#include <utility>
#include <vector>
#include "ccc_suite.h"

set<pair<int, int>> all_tables(int n, int m) {
    set<pair<int, int>> at;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if(i < n - 1) {at.insert(make_pair(i*n+j, i*n+j + 1));}
            if(j < m - 1) {at.insert(make_pair(i*n+j, i*n+j + n));}
        }
    }
    return at;
}

int table_to_key(pair<int, int> table, int n, int m) {
    if (table.first > table.second) {
        swap(table.first, table.second);
    }
    int key;
    if (table.second == table.first + 1) {
        key = 2 * (table.first);
    } else {
        key = 2 * (table.first) + 1;
    }
    return key;
}

pair<int, int> key_to_table(int key, int n, int m) {
    if (key % 2 == 0) {
        return make_pair(key / 2, key / 2 + 1);

    } else {
        return make_pair((key)/2, (key)/2 + n);
    }
}

void prohibit_field(std::unordered_map<int, bool> &p, int field, int n, int m) {
    if (2 * field >= 0 && 2 * field < (n-1) * m + (m-1) * n) {
        p[2 * field] = false;
    }

    if (2 * field + 1 >= 0 && 2 * field + 1 < (n-1) * m + (m-1) * n) {
        p[2 * field + 1] = false;
    }

    if (2 * (field - 1) >= 0 && 2 * (field - 1) < (n-1) * m + (m-1) * n) {
        p[2 * (field-1)] = false;
    }

    if (2*(field-n)+1 >= 0 && 2*(field-n)+1 < (n-1) * m + (m-1) * n) {
        p[2*(field-n)+1] = false;
    }

}

void prohibits(std::unordered_map<int, bool> &p, int key, int n, int m) {
    if (key % 2 == 0) {
        prohibit_field(p, (key / 2) - 1 - n, n, m);
        prohibit_field(p, (key / 2)     - n, n, m);
        prohibit_field(p, (key / 2) + 1 - n, n, m);
        prohibit_field(p, (key / 2) + 2 - n, n, m);

        prohibit_field(p, (key / 2) - 1, n, m);
        prohibit_field(p, (key / 2)    , n, m);
        prohibit_field(p, (key / 2) + 1, n, m);
        prohibit_field(p, (key / 2) + 2, n, m);

        prohibit_field(p, (key / 2) - 1 + n, n, m);
        prohibit_field(p, (key / 2)     + n, n, m);
        prohibit_field(p, (key / 2) + 1 + n, n, m);
        prohibit_field(p, (key / 2) + 2 + n, n, m);
    }

    if (key % 2 == 0) {
        prohibit_field(p, (key / 2) - 1 - n, n, m);
        prohibit_field(p, (key / 2)     - n, n, m);
        prohibit_field(p, (key / 2) + 1 - n, n, m);

        prohibit_field(p, (key / 2) - 1, n, m);
        prohibit_field(p, (key / 2)    , n, m);
        prohibit_field(p, (key / 2) + 1, n, m);

        prohibit_field(p, (key / 2) - 1 + n, n, m);
        prohibit_field(p, (key / 2)     + n, n, m);
        prohibit_field(p, (key / 2) + 1 + n, n, m);

        prohibit_field(p, (key / 2) - 1 + 2*n, n, m);
        prohibit_field(p, (key / 2)     + 2*n, n, m);
        prohibit_field(p, (key / 2) + 1 + 2*n, n, m);
    }
}

vector<vector<int>> make_map(int n_full, int m_full, int desk_count) {
    vector<vector<int>> map;
    map.resize(n_full);
    for (auto &line : map) {
        line.resize(m_full);
    }

    int horizontal_tables = floor(((m_full+1)/3.0));

    int id = 0;
    for (int i = 0; i < n_full; i += 2) {
        int j = 0;
        for (int th = 0; th < horizontal_tables; th++) {
            map[i][j++] = ++id;
            map[i][j++] = id;
            j++;
            desk_count--;
            if (desk_count <= 0) {
                break;
            }
        }
    }

    if (desk_count <= 0) {
        return map;
    }

    int vertical_tables = floor(((n_full + 1) / 3.0));
    int i = 0;
    for (int tv = 0; tv < vertical_tables; tv++) {
        for (int j = 3 * horizontal_tables; j < m_full; j += 2) {
            map[i++][j] = ++id;
            map[i++][j] = id;
            i++;
            desk_count--;

            if (desk_count <= 0) {
                break;
            }
        }
    }

    //assert(desk_count == 0 && ("Could not place all desks!"));

    return map;
}

vector<vector<int>> make_map(vector<int> selection, int n, int m) {
    vector<vector<int>> map;
    map.resize(n);
    for (auto &line : map) {
        line.resize(m);
    }

    for (int key = 0; key < selection.size(); key++) {
        if(selection[key]) {
            auto t = key_to_table(key, n, m);
            cout << key << " " << t.first << " " << t.second << "\n";
            cout << t.first % n << " " << t.first / n << "\n" << t.second%n << " " << t.second/n << "\n\n";
            map[t.first % n][t.first / n] = 1;
            map[t.second % n][t.second / n] = 1;
        }
    }

    return map;
}

void print_map(vector<vector<int>> map, int n, int m, ostream &out) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            out << (map[i][j] == 0 ? '.' : 'X');
        }
        out << '\n';
    }
    out << '\n';
}

vector<int> fuck;

vector<int> search(std::vector<int> selection,  std::unordered_map<int, bool> possibilites, int desk_count, int n, int m) {
    if (desk_count == 0) {
        for (int i = 0; i < selection.size(); i++) {
            if (selection[i]) {
                cout << i << " ";

            }
        }
        cout << "\n";
        fuck = selection;
        return selection;
    }

    else {
        for (auto kv: possibilites) {
            if (kv.second == true && selection[kv.first] == false) {
                auto v = selection;
                v[kv.first] = true;
                auto p = possibilites;
                prohibits(p, kv.first, n, m);

                auto res = search(v, p, desk_count - 1, n, m);

                if (res.size() != 0) {
                    return res;
                }
            }
        }
        return vector<int>();
    }


}

void solution(istream &in, ostream &out) {
    int x = 0;
    int y = 0;
    int dc = 0;
    in >> y;

    in >> x;
    in >> y;
    in >> dc;

    cout << "x " << x <<  " y " << y << '\n';

    auto at = all_tables(y, x);

    cout << at.size();

    map<int, pair<int, int>> check1;
    map<pair<int, int>, int> check2;
    for (auto t : at) {
        check1[table_to_key(t, y, x)] = t;
        check2[t] = table_to_key(t, y, x);
    }

    cout << "<->" << check1.size() << "<->" << check2.size() << "<->"
         << (x - 1) * y + x * (y - 1) << "\n";

    std::vector<int> sel, poss;

    sel.resize((x - 1) * y + x * (y - 1));
    poss.resize((x - 1) * y + x * (y - 1));

    for (int i = 0; i < (x - 1) * y + x * (y - 1); i++) {
        sel[i] = false;
        poss[i] = true;
    }

    auto ret = search(sel, poss, dc, y, x);

    print_map(make_map(fuck, y, x), y, x, cout);

    // while(!in.eof()){
    //     // in >> x;
    //     // in >> y;
    //     // in >> dc;

    //     // if (in.eof()) {
    //     //     break;
    //     // }

    //     // print_map(make_map(y, x, dc), y, x, out);
    // }
}
