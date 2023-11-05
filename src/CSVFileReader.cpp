#include "CSVFileReader.hpp"

using namespace CSV;

CSVFileReader::CSVFileReader(std::string absfilename)
{
    if (! absfilename.empty()){
        filename = absfilename;

        openFile(filename);

        init();
    }
}

void CSV::CSVFileReader::init()
{
    std::string line;

    if (file.is_open())
    {
        while (std::getline(file, line))
            content.push_back(line);
    }
}

void CSV::CSVFileReader::openFile(const std::string &fil)
{
    file.open(fil, std::ios::in);
}

void CSV::CSVFileReader::setFile(const std::string &absfilename)
{
    if (! absfilename.empty() && filename != absfilename){
        filename = absfilename;

        openFile(filename);

        init();
    }
}

std::string CSVFileReader::absoluteFile() const
{
    return filename;
}

const std::size_t CSVFileReader::linesCount() const
{
    return content.size();
}

const std::string &CSVFileReader::lineAt(std::size_t idx) const
{
    return content.at(idx);
}

CSVFileReader::~CSVFileReader()
{
    content.clear();
    file.close();
}