#ifndef __CSVFileReader__

#define __CSVFileReader__

// #include <sstream>
#include <fstream>
#include <string>

#include "NonCopyable.hpp"

namespace CSV
{
    class CSVFileReader: public NonCopyable
    {
        public:

            CSVFileReader()                 = default;
            
            CSVFileReader(std::string absolutFile);

            void                            setFile(const std::string &);

            std::string                     absoluteFile() const;

            const std::size_t               linesCount() const;

            const std::string&              lineAt(std::size_t idx) const;

            ~CSVFileReader();

        private:

            void                            init();

            void                            openFile(const std::string &);

        private:
            std::ifstream                   file;
            std::string                     filename;
            std::vector<std::string>        content;
    };
}

#endif