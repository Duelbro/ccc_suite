#include <filesystem>
#include <fstream>
#include <iostream>
#include <istream>
#include <ostream>
#include <string>
using namespace std;

void solution(istream &in, ostream &out);

bool compare_files(istream &inA, istream &inB) {
    string a;
    string b;
    while (!inA.eof() && !inB.eof()) {
        getline(inA, a);
        getline(inB, b);
        if (a != b) {
            return false;
        }
    }
    return (!inA.eof() || !inB.eof());
}

int main() {
    string level = "level9";
    while (!filesystem::exists(level)) {
        level[level.length() - 1]--;
        if (level == "level0") {
            return 1;
        }
    }
    filesystem::path base_path;
    base_path /= level + "/";
    ifstream test_in{base_path.replace_filename(level + "_example.in") };
    cout << "Opened " << base_path << " for reading\n";
    ofstream test_out{base_path.replace_filename(level + "_test.out") };
    cout << "Opened " << base_path << " for writing\n";

    solution(test_in, test_out);

    test_out.close();
    ifstream test_result{base_path.replace_filename(level + "_test.out") };
    cout << "Opened " << base_path << " for reading\n";
    ifstream example_result{base_path.replace_filename(level + "_example.out") };
    cout << "Opened " << base_path << " for reading\n";
    if (compare_files(test_result, example_result)) {
        cout << "Test successful\n";
    } else {
        cout << "Test unsuccessful\n";
    }

    for (const auto &file : filesystem::directory_iterator{base_path.remove_filename()}) {
        filesystem::path filepath = file.path();
        if ((filepath.extension() == ".in") && (filepath.stem() != level + "_example")) {
            ifstream in{filepath};
            cout << "Opened " << filepath << " for reading\n";
            ofstream out{filepath.replace_extension("out")};
            cout << "Opened " << filepath << " for writing\n";
            solution(in, out);
        }
    }
}
