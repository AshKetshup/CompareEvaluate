#include "testmanager.h"

#include <iostream>
#include <random>

#include "toml.hpp"

TestManager::TestManager(string name, fs::path configPath) :
    testName(name), testConfigFile(configPath) {

    if (!loadConfigFile())
        throw TestManagerException("TOML parser, wasn't able to parse given file");
}

bool TestManager::loadConfigFile() {
    try {
        toml::table config = toml::parse_file(testConfigFile.c_str());
        auto arrPaths = config["directories"].as_array();

        for (size_t i = 0; i < arrPaths->max_size(); i++) {
            const char* x = arrPaths->get(i)->value<string>()->c_str();

            loadDirectory(fs::path(x));
        }

    } catch (const toml::parse_error& err) {
        cerr << "Error parsing file '" << *err.source().path << "':\n"
             << err.description() << "\n (" << err.source().begin << ")\n";

        return false;
    }

    return true;
}



void TestManager::loadDirectory(fs::path dirPath) {
    cout << "Childs of directory '" << dirPath << "'\n";
    for (fs::directory_entry child : fs::directory_iterator(dirPath)) {
        if (!fs::is_regular_file(child))
            continue;

        string fileName = child.path().filename().string();
        cout << "\t" << fileName << "\n";

        // Inserts pair {fileName, root_path} to tableFiles:
        // 1. Certificates that there is at least an empty vector
        tableFiles.try_emplace( fileName, vector<fs::path>() );

        // 2. Gets the vector by reference and pushes back the root_path
        vector<fs::path>& paths = tableFiles.at(fileName);
        paths.push_back(child.path().root_path());
    }
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
    for ( const auto& myPair : tableFiles )
        combinations( myPair.second, pair<fs::path, fs::path>(), 0, myPair.second.size()-1, 0);

    shuffle(queue.begin(), queue.end(), random_device());
}


/**
 * RECURSIVE 2-Combination
 * arr[]        : Input Array
 * aux          : Temporary pair to store current combination
 * start & end : Starting and Ending indexes in arr[]
 * index        : Current index in aux pair
 */
void TestManager::combinations(vector<fs::path> arr, pair<fs::path, fs::path> aux, int start, int end, int index) {

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
    for (int i = start; i <= end && end - i + 1 >= 2 - index; i++) {
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

char *TestManagerException::what() { return message; }
