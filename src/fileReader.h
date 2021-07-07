#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <memory>
#include <string>

class FileReader {
public:
    FileReader(const std::string& fileName, std::streamsize bufferSize, char delimeter = ' ')
        : delimeter(delimeter)
        , bufferSize(bufferSize)
        , buffer(new char[bufferSize])
        , file(fileName)
    {
    }

    std::string read() {
        // read at least bufferSize characters
        // than append characters one by one until it is not equal to delimeter
        // this is to prevent cutting words in the middle
        // returns string to process (empty if there is no data to read)
        if (!good())
            return std::string();
        file.read(buffer.get(), bufferSize);
        auto extracted = file.gcount();
        auto result = std::string(buffer.get());
        if (extracted != bufferSize) {
            result.resize(extracted);
            if (result.back() == '\n') {
                result.pop_back();
            }
        }
        char ch{0};
        while (ch!=delimeter and good()) {
            file.get(ch);
            result+=ch;
        }
        return result;
    }

    bool good() const {
        return file.good();
    }

private:
    const char delimeter {' '};
    const std::streamsize bufferSize {0};
    std::unique_ptr<char[]> buffer;
    std::ifstream file;
};
