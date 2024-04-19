#include <cstdio>

#include "ccc_suite.h"

void move_mower(int &x, int &y, char c) {
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
}

void print_lawn(int x, int y, int width, int height, char *lawn) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i != y || j != x) {
                printf("%c", lawn[i * width + j]);
            } else {
                printf("o");
            }
        }
        printf("\n");
    }
    printf("\n");
}

void solution(istream &in, ostream &out) {
    string s;
    getline(in, s);
    while (!getline(in, s).eof()) {
        int x = 0, y = 0;
        int width = 0, height = 0;
        sscanf(s.c_str(), "%i %i", &width, &height);
        char lawn[height][width];

        for (int y = 0; y < height; y++) {
            getline(in, s);
            for (int x = 0; x < width; x++) {
                lawn[y][x] = s[x];
            }
        }
        getline(in, s);
        if (s.length() != width * height - 1) {
            out << "INVALID\n";
            cout << "path too short\n";
            continue;
        }

        int minx = 0, maxx = 0, miny = 0, maxy = 0;

        for (char c : s) {
            move_mower(x, y, c);
            minx = min(x, minx);
            maxx = max(x, maxx);
            miny = min(y, miny);
            maxy = max(y, maxy);
        }
        if(width != maxx-minx+1 || height != maxy-miny+1) {
            out << "INVALID\n";
            continue;
        }
        x = -minx;
        y = -miny;

        if (x < 0 || x >= width || y < 0 || y >= height || lawn[y][x] != '.') {
            out << "INVALID\n";
            continue;
        }

        lawn[y][x] = '*';
        int visited = 1;
        for (char c : s) {
            if (c != 'W' && c != 'D' && c != 'S' && c != 'A') {
                break;
            }
            move_mower(x, y, c);
            if (x < 0 || x >= width || y < 0 || y >= height ||
                lawn[y][x] != '.') {
                break;
            }
            lawn[y][x] = '*';
            visited++;
        }
        if (visited == width * height - 1) {
            out << "VALID\n";
        } else {
            out << "INVALID\n";
        }
    }
}
