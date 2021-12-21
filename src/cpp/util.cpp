#include "util.h"
using std::string;

string read_file(const char* filename)
{
    // open file
    std::ifstream file{ filename };
    std::stringstream stream;
    // store file buffer content in stream
    stream << file.rdbuf();

    file.close();

    return stream.str();
}

