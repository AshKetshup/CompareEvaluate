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
    int getResult();
    filesystem::path getFirst();
    filesystem::path getSecond();
    string toString();

private:
    string name = "";
    pair<filesystem::path, filesystem::path> images;
    int result = 0;
};

#endif // TEST_H
