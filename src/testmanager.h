#ifndef TESTMANAGER_H
#define TESTMANAGER_H

#include <filesystem>
#include <string>
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


class TestManager {
    public:
        TestManager(string name, fs::path configPath);
        TestManager(fs::path configPath);

        string getTestName();
        filesystem::path getTestConfigFile();
        unordered_map<string, vector<fs::path>> getTableFiles();
        vector<Test> getQueue();
        void appendQueue(Test);


    private:
        string testName;
        filesystem::path testConfigFile;
        unordered_map<string, vector<fs::path>> tableFiles;
        vector<Test> queue;

        bool loadConfigFile();
        void loadDirectory(fs::path dirPath);
        void generateQueue();
        void combinations(vector<fs::path> arr, pair<fs::path, fs::path> aux, int start, int end, int index);

};

#endif // TESTMANAGER_H
