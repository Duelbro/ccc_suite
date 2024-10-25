#include <cmath>
#include <cassert>
#include <vector>
#include "ccc_suite.h"

vector<vector<int>> make_map(int n_full, int m_full, int desk_count) {
    vector<vector<int>> map;
    map.resize(n_full);
    for (auto &line : map) {
        line.resize(m_full);
    }

    int horizontal_tables = floor(((m_full+1)/4.0));

    int id = 0;
    for (int i = 0; i < n_full; i += 2) {
        int j = 0;
        for (int th = 0; th < horizontal_tables; th++) {
            map[i][j++] = ++id;
            map[i][j++] = id;
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

    int vertical_tables = floor(((n_full + 1) / 4.0));
    int i = 0;
    for (int tv = 0; tv < vertical_tables; tv++) {
        for (int j = 4 * horizontal_tables; j < m_full; j += 2) {
            map[i++][j] = ++id;
            map[i++][j] = id;
            map[i++][j] = id;
            i++;
            desk_count--;

            if (desk_count <= 0) {
                break;
            }
        }
    }

    assert(desk_count == 0 && ("Could not place all desks!"));

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

void solution(istream &in, ostream &out) {
    int x = 0;
    int y = 0;
    int dc = 0;
    in >> y;
    while(!in.eof()){
        in >> x;
        in >> y;
        in >> dc;

        if (in.eof()) {
            break;
        }

        print_map(make_map(y, x, dc), y, x, out);
    }
}
