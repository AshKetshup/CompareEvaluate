#include "test.h"

Test::Test(std::filesystem::path imgLeft, std::filesystem::path imgRight) {
    images = {imgLeft, imgRight};
}

Test::Test(std::filesystem::path imgLeft, std::filesystem::path imgRight, string testName) {
    images = {imgLeft, imgRight};
    name = testName;
}

void Test::setResult(int result) { this->result = result; }

int Test::getResult() { return this->result; }

filesystem::path Test::getFirst()  { return this->images.first;  }

filesystem::path Test::getSecond() { return this->images.second; }

string Test::toString() {
    string first = images.first.string();
    string second = images.second.string();
    string r = to_string(this->result);

    return "<" + first + ", " + second + "> = " + r;
}
