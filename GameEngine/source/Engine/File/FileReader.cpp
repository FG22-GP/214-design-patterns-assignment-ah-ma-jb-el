#include "Core.hpp"
#include "FileReader.hpp"


// Filepath is relative to the working directory

std::vector<std::string> FileReader::ReadCSVFile(const std::string& filePath, bool bSanitize /*= true*/)
{
    try
    {
        if (!FileExists(filePath))
        {
            throw std::runtime_error("Error: Input file not found or not accessible");
        }

        std::ifstream file(filePath); // Open the filestream directly with the file path

        if (!file.is_open()) { // If the file failed to open
            throw std::runtime_error("Error: Failed to open file");
        }

        std::string fileContent((std::istreambuf_iterator(file)), std::istreambuf_iterator<char>());
        if (bSanitize) {
            SanitizeString(fileContent); // If sanitization is enabled, remove unwanted characters
        }

        std::stringstream lineStream(fileContent);
        std::vector<std::string> lines; // Vector to hold all cells and return

        std::string cell;
        while (std::getline(lineStream, cell, ',')) {
            lines.push_back(cell); // Splitting cells based on commas and adding to the vector
        }

        file.close(); // Close the filestream

        return lines;
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return {};
    }
}


