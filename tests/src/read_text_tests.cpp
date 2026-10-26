// Instructor tests. Do not modify files in tests/ or vcpkg.json.
#include "test_files.h"

// Purpose: Load complete numeric pairs and replace previous vector contents.
// Debugging hint: Read into an Event, then append it after both fields succeed.
TEST_F(EventLogFiles, ReadTextLoadsPairsAndReplacesExistingEvents) {
    writeTextFile("input.txt", "12 1000\n25 2000\n");
    std::vector<Event> events {{99, 99}};

    ASSERT_TRUE(readTextLog(filename("input.txt"), events));
    expectEvents(events, exampleEvents);
}

// Purpose: Read one complete event per line, including the full unsigned range.
TEST_F(EventLogFiles, ReadTextAcceptsOneEventPerLineAndFullUnsignedRange) {
    writeTextFile("input.txt", "0 4294967295\n16909060 2695938256\n");
    std::vector<Event> events {};

    ASSERT_TRUE(readTextLog(filename("input.txt"), events));
    expectEvents(events, boundaryEvents);
}

// Purpose: An empty file is a successful log containing zero events.
TEST_F(EventLogFiles, ReadTextAcceptsEmptyFile) {
    writeTextFile("input.txt", "");
    std::vector<Event> events {{99, 99}};

    ASSERT_TRUE(readTextLog(filename("input.txt"), events));
    EXPECT_TRUE(events.empty());
}

TEST_F(EventLogFiles, ReadTextRejectsMissingFile) {
    std::vector<Event> events {};
    EXPECT_FALSE(readTextLog(filename("missing.txt"), events));
}
