#include "eventlog.h"

#include <iostream>
#include <string>
#include <vector>

// YOU DO NOT NEED TO TOUCH THIS FILE.

// After implementing the TODOs, try these from the project or build directory:
//   eventlog encode data/events.txt encoded.bin
//   eventlog decode data/events.bin decoded.txt
// data/empty.* are valid empty logs. data/truncated.bin must fail to decode.

void printUsage(const char* programName) {
    std::cerr << "Usage:\n"
              << "  " << programName << " encode INPUT_TEXT OUTPUT_BINARY\n"
              << "  " << programName << " decode INPUT_BINARY OUTPUT_TEXT\n";
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        printUsage(argv[0]);
        return 2;
    }

    const std::string operation {argv[1]};
    if (operation != "encode" && operation != "decode") {
        std::cerr << "Unknown operation: " << operation << '\n';
        printUsage(argv[0]);
        return 2;
    }

    const std::string inputFilename {argv[2]};
    const std::string outputFilename {argv[3]};
    std::vector<Event> events {};

    // Read the complete input before opening the output through a writer.
    if (operation == "encode") {
        if (!readTextLog(inputFilename, events)) {
            std::cerr << "Could not read text log: " << inputFilename << '\n';
            return 1;
        }
        if (!writeBinaryLog(outputFilename, events)) {
            std::cerr << "Could not write binary log: " << outputFilename << '\n';
            return 1;
        }
    }
    else {
        if (!readBinaryLog(inputFilename, events)) {
            std::cerr << "Could not read binary log: " << inputFilename << '\n';
            return 1;
        }
        if (!writeTextLog(outputFilename, events)) {
            std::cerr << "Could not write text log: " << outputFilename << '\n';
            return 1;
        }
    }

    return 0;
}
