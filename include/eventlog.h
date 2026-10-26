#ifndef EVENTLOG_H
#define EVENTLOG_H

#include <cstdint>
#include <string>
#include <vector>

// An Event is a simple description of *something* that happened *somewhere*.
// It's irrelevant to us what the "thing" or the "where" actually is.
// An Event records two integer values, "elapsedSeconds" and "eventCount".
struct Event {
    std::uint32_t elapsedSeconds {};
    std::uint32_t eventCount {};
};

// Events are stored in two different file formats.
// In text format, the file contains one line of text for each event.
// On each line, an event's elapsedSeconds is written first, then a space,
// then its eventCount.
// An empty event log in text format represents 0 total events.

// In binary format, all integers are stored as big-endian 4-byte values. A binary file
// of Events always starts with a 4-byte uint32_t that specifies the count
// of Event objects in the file. Following that count, we store each of the
// events: a 4-byte uint32_t for the elapsedSeconds, then another uint32_t
// for the event's eventCount.
// There are no separators or newline characters between binary fields.
// Thus, a valid binary file with N events occupies 4 + 8*N bytes.
// An empty binary log still contains the four-byte count of zero.

// Attempt to read the given text-format event log, and fill in the
// given vector with each Event that is read. Return true only if all
// reads succeeded and eof was reached as expected, and false if any of them failed unexpectedly.
bool readTextLog(const std::string& filename, std::vector<Event>& events);

// Write the given vector of Event objects to a text file with the given name.
// Return true only if all the writes succeeded, and the file was flushed.
bool writeTextLog(const std::string& filename,
                  const std::vector<Event>& events);

// Attempt to read the given binary-format event log, and fill in the
// given vector with each Event that is read. Return true only if all
// reads succeeded, which means that the expected number of Event objects
// were all read successfully.
bool readBinaryLog(const std::string& filename, std::vector<Event>& events);

// Write the given vector of Event objects to a binary file with the given name.
// Return true only if all the writes succeeded, and the file was flushed.
bool writeBinaryLog(const std::string& filename,
                    const std::vector<Event>& events);

#endif  // EVENTLOG_H
