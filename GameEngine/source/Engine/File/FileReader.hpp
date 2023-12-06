#pragma once

#include "Core.hpp"

class FileReader
{
public:
    
    GAME_API static std::vector<std::string> ReadCSVFile(const std::string& filePath);
    
private:
    static bool FileExists(const std::string& filePath)
    {
        const std::ifstream file(filePath);
        return file.good();
    }
};
