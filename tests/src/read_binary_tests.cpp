// Instructor tests. Do not modify files in tests/ or vcpkg.json.
#include "test_files.h"

// Purpose: Decode known instructor bytes, independently of the student's writer.
// Debugging hint: The count is also a big-endian field that must be converted.
TEST_F(EventLogFiles, ReadBinaryDecodesKnownBytesAndReplacesExistingEvents) {
    writeBytes("input.bin", exampleBytes);
    std::vector<Event> events {{99, 99}};

    ASSERT_TRUE(readBinaryLog(filename("input.bin"), events));
    expectEvents(events, exampleEvents);
}

TEST_F(EventLogFiles, ReadBinaryPreservesAllBitsInUnsignedFields) {
    writeBytes("input.bin", boundaryBytes);
    std::vector<Event> events {};

    ASSERT_TRUE(readBinaryLog(filename("input.bin"), events));
    expectEvents(events, boundaryEvents);
}

TEST_F(EventLogFiles, ReadBinaryAcceptsZeroRecordCount) {
    writeBytes("input.bin", {0x00, 0x00, 0x00, 0x00});
    std::vector<Event> events {{99, 99}};

    ASSERT_TRUE(readBinaryLog(filename("input.bin"), events));
    EXPECT_TRUE(events.empty());
}

// Purpose: Every required byte matters, including a missing count and a short
// final field. EOF is an error when a declared field is incomplete.
TEST_F(EventLogFiles, ReadBinaryRejectsEveryTruncatedPrefix) {
    for (std::size_t length {0}; length < exampleBytes.size(); ++length) {
        SCOPED_TRACE("available bytes: " + std::to_string(length));
        const std::vector<unsigned char> prefix {
            exampleBytes.begin(), exampleBytes.begin() + length
        };
        writeBytes("input.bin", prefix);
        std::vector<Event> events {};

        EXPECT_FALSE(readBinaryLog(filename("input.bin"), events));
    }
}

TEST_F(EventLogFiles, ReadBinaryRejectsMissingFile) {
    std::vector<Event> events {};
    EXPECT_FALSE(readBinaryLog(filename("missing.bin"), events));
}
