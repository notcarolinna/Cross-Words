#include "dictionary.h"

#include <fstream>
#include <algorithm>


Dictionary::Dictionary() {}

void Dictionary::leftTrim(std::string &str) {
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

void Dictionary::rightTrim(std::string &str) {
    str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), str.end());
}

void Dictionary::trim(std::string &str) {
    rightTrim(str);
    leftTrim(str);
}

void Dictionary::parseFile(std::string fileName, std::unordered_set<int> sizes) {
    std::ifstream file;
    file.open(fileName);
    while (file.is_open() && !file.eof()) {
        std::string line;
        std::getline(file, line);
        if (!line.empty()) {
            trim(line);
            int length = line.length();
            if (line[length-1] == '\r') {
                line = line.substr(0, length-1);
            }
            length = line.length();
            if(std::all_of(line.begin(), line.end(), [] (char c) {return std::isalpha(c);} )) {
                if (std::find(sizes.begin(), sizes.end(), length) != sizes.end()) {
                    _wordMap[length].push_back(line);
                }
            }
        }
    }

    for (const auto& pair : _wordMap) {
        std::cout << "SIZE " << pair.first << ": ";

        for(const auto& word : pair.second) {
            std::cout << word << " ";
        }
        std::cout << std::endl;
    }
}
