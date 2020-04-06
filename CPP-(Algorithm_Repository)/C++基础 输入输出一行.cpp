#include <iostream>
#include <sstream>

    string line;
    if (getline(cin,line)) {
        stringstream s(line);
        string x;
        while (s>>x) {
            a.push_back(x);
            ++n;
        }
    }