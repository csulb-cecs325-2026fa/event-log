// Instructor tests. Do not modify files in tests/ or vcpkg.json.
#include "test_files.h"

// Purpose: Verify exact field order, count, byte order, and lack of separators.
// Debugging hint: Write numeric fields individually, not formatted text or a struct.
TEST_F(EventLogFiles, WriteBinaryMatchesKnownBigEndianBytes) {
    ASSERT_TRUE(writeBinaryLog(filename("output.bin"), exampleEvents));
    EXPECT_EQ(readBytes("output.bin"), exampleBytes);
}

TEST_F(EventLogFiles, WriteBinaryPreservesAllBitsAndInputEvents) {
    auto events = boundaryEvents;
    ASSERT_TRUE(writeBinaryLog(filename("output.bin"), events));

    EXPECT_EQ(readBytes("output.bin"), boundaryBytes);
    expectEvents(events, boundaryEvents);
}

// Purpose: An empty binary log contains a count, even with no event fields.
TEST_F(EventLogFiles, WriteBinaryReplacesExistingFileWithZeroRecordCount) {
    writeBytes("output.bin", exampleBytes);

    ASSERT_TRUE(writeBinaryLog(filename("output.bin"), {}));
    const std::vector<unsigned char> expected {0x00, 0x00, 0x00, 0x00};
    EXPECT_EQ(readBytes("output.bin"), expected);
}

TEST_F(EventLogFiles, WriteBinaryRejectsUnopenableOutput) {
    EXPECT_FALSE(writeBinaryLog(filename("missing-directory/output.bin"), exampleEvents));
}
