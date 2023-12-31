// #include <iostream>
// #include <vector>

#include "include/CSVParser.hpp"

// #include <condition_variable>
// #include <functional>
#include <thread>
// #include <queue>
// #include <mutex>
// #include <chrono>

void threadedFunc(CSV::CSVParser& parser){
    std::cout << parser.lineTextFormat(45 - 1) << std::endl;
    std::cout << parser.lineCSVFormat(45 - 1) << std::endl;
}

int main(int argc, char **argv)
{
    CSV::CSVParser parser("../allStock5Year.csv");

    std::thread thread(threadedFunc, std::ref(parser));

    thread.join();

    // std::cout << parser.lineTextFormat(45 - 1) << std::endl;

    return 0;
}

//Ex:
/*
2013-02-08,15.07,15.12,14.63,14.75,8407500,AAL
2013-02-11,14.89,15.01,14.26,14.46,8882000,AAL
2013-02-12,14.45,14.51,14.1,14.27,8126000,AAL
2013-02-13,14.3,14.94,14.25,14.66,10259500,AAL
2013-02-14,14.94,14.96,13.16,13.99,31879900,AAL
2013-02-15,13.93,14.61,13.93,14.5,15628000,AAL
2013-02-19,14.33,14.56,14.08,14.26,11354400,AAL
2013-02-20,14.17,14.26,13.15,13.33,14725200,AAL
2013-02-21,13.62,13.95,12.9,13.37,11922100,AAL
2013-02-22,13.57,13.6,13.21,13.57,6071400,AAL
2013-02-25,13.6,13.76,13.0,13.02,7186400,AAL
2013-02-26,13.14,13.42,12.7,13.26,9419000,AAL
2013-02-27,13.28,13.62,13.18,13.41,7390500,AAL
2013-02-28,13.49,13.63,13.39,13.43,6143600,AAL
2013-03-01,13.37,13.95,13.32,13.61,7376800,AAL
2013-03-04,13.5,14.07,13.47,13.9,8174800,AAL
2013-03-05,14.01,14.05,13.71,14.05,7676100,AAL
2013-03-06,14.52,14.68,14.25,14.57,13243200,AAL
2013-03-07,14.7,14.93,14.5,14.82,9125300,AAL
*/
