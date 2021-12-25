#include "util.h"
using std::string;

string read_file(const char* filename)
{
    // open file
    std::ifstream file{ filename };
    std::stringstream stream;
    // allow ifstream to throw errors
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        // store file buffer content in stream
        stream << file.rdbuf();

        file.close();
    }
    catch (const std::ifstream::failure& error)
    {
        std::cerr << "Error reading from file \"" << filename << "\":\n"
                  << error.what();
    }

    return stream.str();
}

