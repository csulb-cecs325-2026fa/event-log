#ifndef EVENTLOG_TEST_FILES_H
#define EVENTLOG_TEST_FILES_H

// Instructor test support. Do not modify files in tests/ or vcpkg.json.
#include <gtest/gtest.h>

#include <chrono>
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <string>
#include <system_error>
#include <vector>

#include "eventlog.h"

class EventLogFiles : public ::testing::Test {
protected:
    std::filesystem::path directory {};

    void SetUp() override {
        const auto stamp = std::chrono::steady_clock::now().time_since_epoch().count();
        for (int attempt {0}; attempt < 100; ++attempt) {
            const auto candidate = std::filesystem::temp_directory_path()
                / ("cecs325-event-log-" + std::to_string(stamp)
                   + "-" + std::to_string(attempt));
            std::error_code error {};
            if (std::filesystem::create_directory(candidate, error)) {
                directory = candidate;
                return;
            }
            ASSERT_FALSE(error) << "Could not create test directory: " << error.message();
        }
        FAIL() << "Could not create a unique test directory.";
    }

    void TearDown() override {
        if (!directory.empty()) {
            std::error_code error {};
            std::filesystem::remove_all(directory, error);
            EXPECT_FALSE(error) << "Could not clean test directory: " << error.message();
        }
    }

    std::string filename(const std::string& name) const {
        return (directory / name).string();
    }

    void writeTextFile(const std::string& name, const std::string& text) {
        std::ofstream output {filename(name)};
        ASSERT_TRUE(output) << "Could not create text fixture.";
        output << text;
        output.flush();
        ASSERT_TRUE(output) << "Could not write text fixture.";
    }

    void writeBytes(const std::string& name,
                    const std::vector<unsigned char>& bytes) {
        std::ofstream output {filename(name), std::ios::binary};
        ASSERT_TRUE(output) << "Could not create binary fixture.";
        for (unsigned char byte : bytes) {
            output.put(static_cast<char>(byte));
        }
        output.flush();
        ASSERT_TRUE(output) << "Could not write binary fixture.";
    }

    std::string readTextFile(const std::string& name) const {
        // Text mode normalizes the platform's line endings for comparison.
        std::ifstream input {filename(name)};
        EXPECT_TRUE(input) << "Could not open text output.";
        return {std::istreambuf_iterator<char> {input},
                std::istreambuf_iterator<char> {}};
    }

    std::vector<unsigned char> readBytes(const std::string& name) const {
        std::ifstream input {filename(name), std::ios::binary};
        EXPECT_TRUE(input) << "Could not open binary output.";
        return {std::istreambuf_iterator<char> {input},
                std::istreambuf_iterator<char> {}};
    }

    void expectEvents(const std::vector<Event>& actual,
                      const std::vector<Event>& expected) const {
        ASSERT_EQ(actual.size(), expected.size());
        for (std::size_t index {0}; index < expected.size(); ++index) {
            EXPECT_EQ(actual[index].elapsedSeconds, expected[index].elapsedSeconds)
                << "event " << index;
            EXPECT_EQ(actual[index].eventCount, expected[index].eventCount)
                << "event " << index;
        }
    }

    const std::vector<Event> exampleEvents {{12, 1000}, {25, 2000}};
    const std::vector<unsigned char> exampleBytes {
        0x00, 0x00, 0x00, 0x02,
        0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x03, 0xE8,
        0x00, 0x00, 0x00, 0x19, 0x00, 0x00, 0x07, 0xD0
    };
    const std::vector<Event> boundaryEvents {
        {0, 0xFFFFFFFFu}, {0x01020304u, 0xA0B0C0D0u}
    };
    const std::vector<unsigned char> boundaryBytes {
        0x00, 0x00, 0x00, 0x02,
        0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,
        0x01, 0x02, 0x03, 0x04, 0xA0, 0xB0, 0xC0, 0xD0
    };
};

#endif  // EVENTLOG_TEST_FILES_H
