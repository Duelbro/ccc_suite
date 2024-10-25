#include <vector>
#include "ccc_suite.h"

vector<vector<int>> make_map(int n_full, int m_full, int desk_count) {
    vector<vector<int>> map;
    map.resize(n_full);
    for (auto &line : map) {
        line.resize(m_full);
    }

    int m_nice = m_full - (m_full % 3);

    int id = 0;
    for (int i = 0; i < n_full; i++) {
        for (int j = 0; j < m_nice; j += 3) {
            map[i][j] = ++id;
            map[i][j + 1] = id;
            map[i][j + 2] = id;
            desk_count--;

            if (desk_count <= 0) {
                break;
            }
        }
    }

    if (desk_count <= 0) {
        return map;
    }

    int n_nice = n_full - (n_full % 3);
    for (int i = 0; i < n_nice; i += 3) {
        for (int j = m_nice; j < m_full; j++) {
            map[i][j] = ++id;
            map[i + 1][j] = id;
            map[i + 2][j] = id;
            desk_count--;

            if (desk_count <= 0) {
                break;
            }
        }
    }


    return map;
}

void print_map(vector<vector<int>> map, int n, int m, ostream &out) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            out << map[i][j] << ' ';
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
