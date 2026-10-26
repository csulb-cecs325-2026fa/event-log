// Instructor tests. Do not modify files in tests/ or vcpkg.json.
#include "test_files.h"

// Purpose: Test text output independently of the student's text reader.
TEST_F(EventLogFiles, WriteTextWritesOneDecimalPairPerLine) {
    ASSERT_TRUE(writeTextLog(filename("output.txt"), exampleEvents));
    EXPECT_EQ(readTextFile("output.txt"), "12 1000\n25 2000\n");
}

TEST_F(EventLogFiles, WriteTextPreservesFullUnsignedRangeAndInputEvents) {
    auto events = boundaryEvents;
    ASSERT_TRUE(writeTextLog(filename("output.txt"), events));

    EXPECT_EQ(readTextFile("output.txt"), "0 4294967295\n16909060 2695938256\n");
    expectEvents(events, boundaryEvents);
}

// Purpose: Writers replace old contents, including when the new log is empty.
TEST_F(EventLogFiles, WriteTextReplacesExistingFileWithEmptyLog) {
    writeTextFile("output.txt", "old file contents\n");

    ASSERT_TRUE(writeTextLog(filename("output.txt"), {}));
    EXPECT_TRUE(readTextFile("output.txt").empty());
}

TEST_F(EventLogFiles, WriteTextRejectsUnopenableOutput) {
    // The parent directory deliberately does not exist.
    EXPECT_FALSE(writeTextLog(filename("missing-directory/output.txt"), exampleEvents));
}
