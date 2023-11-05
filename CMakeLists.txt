cmake_minimum_required(VERSION 3.26.4)
project("CSV Parser")

set(CMAKE_CXX_STANDARD 20)

add_library(csvparser STATIC src/CSVParser.cpp)
add_library(csvfilereader STATIC src/CSVFileReader.cpp)

# include_directories(src)
include_directories(include)

add_executable(app app.cpp)
target_link_libraries(csvparser csvfilereader) #linking CSVFileReader lib to CSVParser
target_link_libraries(app csvparser) #linking CSVParser to executable App

