#ifndef __CSV__

#define __CSV__

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

#include "NonCopyable.hpp"
#include "CSVFileReader.hpp"

namespace CSV
{
    class CSVParser: public NonCopyable //inheriting from noncopyable to avoid move semantics
    {
        public:
            CSVParser()                     = default;

            CSVParser(const std::string file); //parametized ctor

            ~CSVParser();

            void                            setFile(const std::string &);

            std::size_t                     columnCount(); //column count

            std::size_t                     rowCount() const; //row count

            std::vector<std::string>        headers(); //return headers

            std::vector<std::string>        contentByColumn(const std::string &, const std::size_t fromRow = 0,
                                                            const std::size_t toRow = 0); //return content by column
                                                            
            std::vector<std::string>        contentByColumn(const std::size_t, const std::size_t fromRow = 0,
                                                            const std::size_t toRow = 0); //return content by column index

            std::vector<std::string>        contentCSVFormat(const std::size_t rows = 0); //return CSV format content

            std::vector<std::string>        contentTextFormat(const std::size_t rows = 0); //return CSV format content

            std::string                     lineCSVFormat(const std::size_t row = 0); //return CSV format line

            std::string                     lineTextFormat(const std::size_t row = 0); //return Text format line

            std::size_t                     getColumnIndex(const std::string &); //return a index by a specified name

            std::string                     getColumnName(const std::size_t); //return a name by a specified index

            std::string                     cell(const std::size_t, const std::size_t); //return content at row and column

        private:

            std::vector<std::string>        split(std::string& line, char delimiter); //internal use for spliting

            bool                            parse_fields(); //method it will be called just after constructor

        private:
            CSV::CSVFileReader              reader; //to read CSV files
            std::vector<std::string>        cells; //to storage csv format in a std::vector
    };
}

#endif