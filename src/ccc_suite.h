#include <filesystem>
#include <fstream>
#include <iostream>
#include <istream>
#include <ostream>
#include <string>
using namespace std;

void do_things(istream &in, ostream &out) {
    printf("new file\n");
    out << in.rdbuf();
}

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
    string LVL_NUMBER = "1";
    filesystem::path base_path;
    base_path /= "level" + LVL_NUMBER + "/";
    ifstream test_in{base_path.replace_filename("level" + LVL_NUMBER + "_example.in") };
    cout << "Opened " << base_path << " for reading\n";
    ofstream test_out{base_path.replace_filename("level" + LVL_NUMBER + "_test.out") };
    cout << "Opened " << base_path << " for writing\n";

    do_things(test_in, test_out);

    test_out.close();
    ifstream test_result{base_path.replace_filename("level" + LVL_NUMBER + "_test.out") };
    cout << "Opened " << base_path << " for reading\n";
    ifstream example_result{base_path.replace_filename("level" + LVL_NUMBER + "_example.out") };
    cout << "Opened " << base_path << " for reading\n";
    if (compare_files(test_result, example_result)) {
        cout << "Test successful\n";
    } else {
        cout << "Test unsuccessful\n";
    }

    for (const auto &file : filesystem::directory_iterator{base_path.remove_filename()}) {
        filesystem::path filepath = file.path();
        if ((filepath.extension() == ".in") && (filepath.stem() != "level" + LVL_NUMBER + "_example")) {
            ifstream in{filepath};
            cout << "Opened " << filepath << " for reading\n";
            ofstream out{filepath.replace_extension("out")};
            cout << "Opened " << filepath << " for writing\n";
            do_things(in, out);
        }
    }
}
