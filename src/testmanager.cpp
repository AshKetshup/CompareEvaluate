#include "testmanager.h"

#include <iostream>
#include <random>
#include <chrono>
#include <QDebug>

#include "toml.hpp"

// TestManager class

/**
 * Initializes TestManager staticly
 */
void TestManager::initTestManager(string name, fs::path configPath) {
    // No Tab
    qDebug() << "Initializes TestManager";

    TestManager::testName = name;
    TestManager::testConfigFile = configPath;


    bool successLoading = loadConfigFile();
    qDebug() << "Success Loading TOML: " << successLoading;
    if ( !successLoading )
        throw TestManagerException(TestManagerException::TOML_EXCEPTION_ERROR);

    TestManager::generateQueue();
}

void TestManager::initTestManager(fs::path configPath) { initTestManager("", configPath); }

bool TestManager::loadConfigFile() {
    // 1 Tab

    qDebug() << "\n\tLoads Config File:";

    bool returnValue = true;

    try {
        toml::table config = toml::parse_file(testConfigFile.c_str());

        auto arrPaths = config["CONFIG"]["directories"].as_array();
        if (!arrPaths)
            throw ReadException(ReadException::READ_EXCEPTION_ERROR);

        for (size_t i = 0; i < arrPaths->size(); i++) {
            fs::path readDirectory(arrPaths->get(i)->value<string>()->c_str());

            qDebug() << "Read directory" << readDirectory.string();

            fs::path fullDir = (readDirectory.is_relative())
                ? testConfigFile.parent_path()/readDirectory
                : readDirectory;

            qDebug() << "Complete Directory: " << fullDir.string() << "\n";

            loadDirectory(fullDir);
        }

    } catch (const toml::parse_error& err) {
        qCritical() << "\tTomlParseError: Error parsing file '" << err.source().path->c_str() << "':\n\t\t"
             << err.description() << "\n(" << err.source().begin.column << " cl " << err.source().begin.line << " ln )\n";

        returnValue = false;
    } catch (const ReadException& err) {
        qCritical() << "\tReadException: " << err.what() << "\n";

        returnValue = false;
    } catch (const exception& err) {
        qCritical() << "\tEXCEPTION NOT COVERED: " << err.what() << "\n";

        returnValue = false;
    }


    qDebug() << "\t[DONE]";
    return returnValue;
}

void TestManager::loadDirectory(fs::path dirPath) {
    // 2 Tabs
    qDebug() << "\n\t\tLoading Directory Files from: '" << dirPath.string();

    fs::directory_iterator iterator(dirPath);

    for (auto& child : iterator) {
        if (!fs::is_regular_file(child))
            continue;

        string fileName = child.path().filename().string();
        qDebug() << "\t\t - " << fileName;

        // Inserts pair {fileName, root_path} to tableFiles:
        // 1. Certificates that there is at least an empty vector
        tableFiles.try_emplace( fileName, vector<fs::path>() );

        // 2. Gets the vector by reference and pushes back the root_path
        vector<fs::path>& paths = tableFiles.at(fileName);
        paths.push_back(child.path());
    }

    qDebug() << "\t\t[DONE]";
}


/** GENERATE QUEUE
 *  1. from each key:
 *       1.1. Get vector of paths from the key X
 *       1.2. Generate all possible non-repeating pairs X
 *       1.3. Convert into Test X
 *       1.4. Append to queue vector X
 *  2. randomize queue
*/
void TestManager::generateQueue() {
    qDebug() << "\n\tGenerates Queue from Table ... ";

    qDebug() << "\tCreates all possible combos ...";
    for ( const auto& myPair : tableFiles )
        combinations( myPair.second, pair<fs::path, fs::path>(), 0, myPair.second.size() - 1, 0 );

    qDebug() << "\tShuffles queue order";

    std::random_device rDevice;
    std::mt19937 generator(rDevice());
    generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
    shuffle(queue.begin(), queue.end(), generator);

    qDebug() << "\t[DONE]";
}


/**
 * RECURSIVE 2-Combination
 * arr[]        : Input Array
 * aux          : Temporary pair to store current combination
 * start & end : Starting and Ending indexes in arr[]
 * index        : Current index in aux pair
 */
void TestManager::combinations(vector<fs::path> arr, pair<fs::path, fs::path> aux, size_t start, size_t end, size_t index) {

    // Current combination is ready to be printed, print it
    if (index == 2) {
        queue.push_back( Test(aux.first, aux.second) );
        return;
    }

    /*
     * Replace index with all possible elements.
     * The condition "end-i+1 >= 2-index" makes sure that including one element at
     * index will make a combination with remaining elements at remaining positions
     */
    for (size_t i = start; i <= end && end - i + 1 >= 2 - index; i++) {
        switch (index) {
        case 0:
            aux.first = arr[i];
            break;
        case 1:
            aux.second = arr[i];
            break;
        }

        combinations(arr, aux, i + 1, end, index + 1);
    }
}

string TestManager::getName(){ return TestManager::testName; }

filesystem::path TestManager::getTestConfigFile(){ return TestManager::testConfigFile; }

unordered_map<string, vector<fs::path>>& TestManager::getTableFiles() { return TestManager::tableFiles; }

vector<Test>& TestManager::getQueue() { return TestManager::queue; }

Test& TestManager::getTest(size_t i) { return TestManager::queue.at(i); }

Test& TestManager::getCurrentTest() { return TestManager::queue.at(TestManager::testIndex); }

void TestManager::pushQueue(Test t) { TestManager::queue.push_back(t); }

void TestManager::next() { TestManager::testIndex++; }

void TestManager::previous() { TestManager::testIndex--; }

void TestManager::reset() { TestManager::testIndex = 0; }

size_t TestManager::queueSize() { return TestManager::queue.size(); }

// TestManagerException class
const char* TestManagerException::what() const { return message.c_str(); }

// ReadException class
const char* ReadException::what() const { return message.c_str(); }
