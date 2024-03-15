#ifndef TESTMANAGER_H
#define TESTMANAGER_H

#include <filesystem>
#include <string>
#include <vector>
#include <unordered_map>

#include "test.h"

using namespace std;
using namespace std::string_view_literals;
namespace fs = filesystem;

class TestManagerException : public exception {
    public:
        TestManagerException(const string &msg) : message(msg) {}
        virtual const char* what() const;

        static constexpr const char* TOML_EXCEPTION_ERROR = "TOML parser, wasn't able to parse given file";
    private:
        const string message;
};

class ReadException : public exception {
    public:
        ReadException(const string &msg) : message(msg) {}
        virtual const char* what() const;

        static constexpr const char* READ_EXCEPTION_ERROR = "TOML was read, although we couldn't retrieve the proper values";
    private:
        const string message;
};

class TestManager {
    public:
        static void initTestManager(string name, fs::path configPath);
        static void initTestManager(fs::path configPath);

        static string getName();
        static filesystem::path getTestConfigFile();
        static unordered_map<string, vector<fs::path>>& getTableFiles();
        static Test& getTest(size_t i);
        static Test& getCurrentTest();

        static vector<Test>& getQueue();
        static size_t queueSize();
        static void pushQueue(Test t);

        static void next();
        static void previous();
        static void reset();

    private:
        inline static size_t testIndex = 0;
        inline static string testName = string("");
        inline static filesystem::path testConfigFile  = filesystem::current_path();
        inline static unordered_map<string, vector<fs::path>> tableFiles = {};
        inline static vector<Test> queue = {};

        static bool loadConfigFile();
        static void loadDirectory(fs::path dirPath);
        static void generateQueue();
        static void combinations(
            vector<fs::path> arr,
            pair<fs::path, fs::path> aux,
            size_t start,
            size_t end,
            size_t index
        );
};

#endif // TESTMANAGER_H
