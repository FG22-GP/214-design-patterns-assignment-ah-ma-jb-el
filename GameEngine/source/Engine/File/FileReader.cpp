#include "Core.hpp"
#include "FileReader.hpp"

std::vector<std::string> FileReader::ReadCSVFile(const std::string& filePath)
{
    try
    {
        if(!FileExists(filePath))
        {
            throw std::runtime_error("Error : Input file not found or not accessible");
        }
    
        std::ifstream file; // Open the filestream
        file.open(filePath); // Open the file
        
        if(!file.is_open()) { // If the file failed to open
            throw std::runtime_error("Error : Failed to open file");
        }
        
        std::string line; // String to hold each line
        std::vector<std::string> lines; // Vector to hold all lines and return
        while (std::getline(file, line)) {
            std::stringstream lineStream(line);
            std::string cell;
            while (std::getline(lineStream, cell, ',')) {
                lines.push_back(cell);
            }
        }
        file.close(); // Close the filestream
    
        return lines;
    } catch(const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return {};
    }
}
