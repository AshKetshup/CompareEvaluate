#ifndef TEST_H
#define TEST_H

#include <filesystem>
#include <string>

using namespace std;

class Test {
public:
    Test(filesystem::path, filesystem::path);
    Test(filesystem::path, filesystem::path, string);
    void setResult(int result);
    string toString();


private:
    string name;
    pair<filesystem::path, filesystem::path> images;
    int result;
};

#endif // TEST_H
