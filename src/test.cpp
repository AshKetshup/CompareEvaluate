#include "test.h"

Test::Test(std::filesystem::path imgLeft, std::filesystem::path imgRight) {
    images = {imgLeft, imgRight};
}

Test::Test(std::filesystem::path imgLeft, std::filesystem::path imgRight, string testName) {
    images = {imgLeft, imgRight};
    name = testName;
}
