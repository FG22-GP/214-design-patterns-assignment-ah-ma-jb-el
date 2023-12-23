#pragma once

#include "Core.hpp"

class FileReader
{
public:
    
    GAME_API static std::vector<std::string> ReadCSVFile(const std::string& filePath, bool bSanitize = true);
    
private:
    static bool FileExists(const std::string& filePath)
    {
        const std::ifstream file(filePath);
        return file.good();
    }

    static void SanitizeString(std::string& input)
    {
        std::erase(input, '\n');
        std::erase(input, '\r');
        std::erase(input, '\t');
        std::erase(input, ' ');
    }
};
