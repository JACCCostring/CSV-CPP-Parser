#include "CSVParser.hpp"

using namespace CSV;

CSVParser::CSVParser(const std::string file): reader(file){
    //calling method to parse all necesaty fields with rows/columns
    if (! file.empty()) parse_fields();
}

void CSV::CSVParser::setFile(const std::string &filename)
{
    if (! filename.empty()){
        reader.setFile(filename);

        parse_fields();
    }
}

std::size_t CSVParser::columnCount()
{
    return headers().size();
}

std::size_t CSV::CSVParser::rowCount() const
{
    return reader.linesCount();
}

std::vector<std::string> CSV::CSVParser::headers()
{
    std::string target = reader.lineAt(0);

    std::vector<std::string> temp = split(target, ',');

    return temp;
}

std::vector<std::string> CSVParser::contentByColumn(const std::string &column, const std::size_t from,
                                                    const std::size_t to)
{
    std::vector<std::string> temp;

    std::size_t startAt{};
    std::size_t stopAt{};

    if (from < 0|| to > rowCount()) return {}; //if bound is out of range then return empty
    if (from > rowCount() || to < 0) return {}; //if bounds are not valid tne return empty

    if (from > 0 && to == 0) { startAt = from; stopAt = rowCount(); } //if 1 param is valid and 2 param neutral
    if (from == 0 && to > 0) { startAt = 0; stopAt = to; } //if 1 param is neutral and 2 param valid number
    if (from > 0 && to > 0) { startAt = from; stopAt = to; } //if 1 and 2 param is are valid numbers

    auto col = getColumnIndex(column); //getting col idx by name
    
    if (startAt >= 1) //if from idx < or equal 0 then not decrement
    {
        startAt -= 1;
        stopAt -= 1;
    }

    for (auto idx = startAt; idx < stopAt; idx++)
    {
        auto content = cell(idx, getColumnIndex(column));

        temp.push_back(content);
    }

    return temp;
}

std::vector<std::string> CSVParser::contentByColumn(const std::size_t col, const std::size_t from,
                                                    const std::size_t to)
{
    auto column = getColumnName(col);

    auto temp = contentByColumn(column, from, to);

    return temp;
}

std::vector<std::string> CSVParser::contentCSVFormat(const std::size_t rows)
{
    std::vector<std::string> temp;

    std::size_t howManyRows = rows;

    if (rows < 0 || rows > rowCount()) return {};

    if (howManyRows == 0) howManyRows = rowCount();

    for (auto idx = 0; idx < howManyRows - 1; idx++)
    {
        //substr need it, to avoid last character of string 
        //that is a ',' in this case
        temp.push_back(cells.at(idx).substr(0, cells.at(idx).size() - 1));
    }

    return temp;
}

std::vector<std::string> CSVParser::contentTextFormat(const std::size_t rows)
{
    std::vector<std::string> temp;
    
    std::string substr{};

    if (rows < 0 || rows > rowCount()) return {};

    std::size_t howManyRows = rows;
    std::size_t col = 0;

    if (howManyRows == 0) howManyRows = rowCount();

    for (auto idx = 0; idx < howManyRows; idx++)
    {
        auto splited = split(cells[idx], ',');

        for (auto cont: splited)
        {
            if (col == columnCount())
            {
                temp.push_back(substr);

                substr.clear();
                col = 0;
            }

            substr += cont + ' ';

            col++;
        }
    }

    return temp;
}

std::string CSV::CSVParser::lineCSVFormat(const std::size_t row)
{
    return cells.at(row - 1).substr(0, cells.at(row - 1).size());
}

std::string CSV::CSVParser::lineTextFormat(const std::size_t row)
{    
    std::string substr{};

    if (row < 0 || row > rowCount()) return {};

    std::size_t howManyRows = row;
    std::size_t col = 0;

    if (howManyRows == 0) howManyRows = rowCount();

    auto splited = split(cells[row - 1], ',');

    for (auto cont: splited)
    {
        if (col == columnCount())
        {
            substr.clear();
            col = 0;
        }

        substr += cont + ' ';

        col++;
    }

    return substr;
}

std::vector<std::string> CSV::CSVParser::split(std::string &line, char delimiter)
{
    std::string substr{};
    std::stringstream stream{};
    std::vector<std::string> temp{};

    line = line + delimiter; //adding delimeter at the end, to parse last word
    
    for (int idx = 0; idx < line.size(); idx++)
    {
        if (line[idx] != delimiter) substr += line[idx];
        if (line[idx] == delimiter) { temp.push_back(substr); substr.clear(); }
    }

    return temp;
}

bool CSVParser::parse_fields()
{
    if (rowCount() > 0) //if reader contains buffer
    {
        // starting from 1 to ignore headers
        for (int idx = 1; idx < rowCount(); idx++)
        {
            std::string line = reader.lineAt(idx); //get line at indx in a CVS format

            cells.push_back(line);
        }
 
        return true;
    }

    return false;
}

std::size_t CSVParser::getColumnIndex(const std::string &name)
{
    std::size_t count = 0;

    for (auto c: headers())
    {
        if (c == name) return count;

        count++;
    }

    return -1;
}

std::string CSVParser::getColumnName(const std::size_t idx)
{
    return headers()[idx];
}

std::string CSVParser::cell(const std::size_t row, const std::size_t column)
{
    //first it checks the bound
    if (row < 0 && row > rowCount() && column < 0 && column > columnCount()) return {};

    auto c = cells[row - 1];

    auto splited = split(c, ',');

    for (auto cursor = 0; cursor < columnCount(); cursor++)
        if (cursor == column) return splited[column];

    return {};
}

CSVParser::~CSVParser(){/*to implement*/}