#include "eventlog.h"

#include <bit>
#include <fstream>

// TODO: Read exactly four bytes into value, check the read, and convert the
// big-endian representation to the native byte order. Return false if a
// complete field could not be read. Use this helper for every binary field.
bool readBigEndian32(std::ifstream& input, std::uint32_t& value) {
    return false;
}

// TODO: Convert the local copy of value to big-endian order and write its
// four bytes. Return whether writing succeeded. Use this helper for every
// binary field.
bool writeBigEndian32(std::ofstream& output, std::uint32_t value) {
    return false;
}

bool readTextLog(const std::string& filename, std::vector<Event>& events) {
    // TODO: Open the text file, clear events, and load complete numeric pairs.
    // Check the file stream and follow the contract in eventlog.h.
    // HINT: construct a std::ifstream to open the file.
    // Use >> to read one uint32_t from the file, and then a second.
    // Use those to construct an Event object to push into the vector.
    // Repeat that until the >> operator fails where you expect it to. (After reading
    // the last pair of two consecutive integers.)
    return false;
}

bool writeTextLog(const std::string& filename,
                  const std::vector<Event>& events) {
    // TODO: Open the text file and write each event in the specified format.
    // Open the std::ofstream, and then loop over the events, using <<
    // to write each event's elapsedSeconds and eventCount to the file,
    // followed by an endline.
    return false;
}

bool readBinaryLog(const std::string& filename, std::vector<Event>& events) {
    // TODO: Open in binary mode and clear events. Read the record count,
    // then read that many events using readBigEndian32 for each field.
    // Append an event only after both of its fields have been read.

    // HINT: start by calling readBigEndian32 to read "numberOfEvents", and if that succeeds,
    // call it two more times to read "elapsedSeconds" and "eventCount".
    // Use those to construct an Event object to push into the events vector.
    // Then decide how to loop that "numberOfEvents" times total. You also need to handle numberOfEvents being 0.
    return false;
}

bool writeBinaryLog(const std::string& filename,
                    const std::vector<Event>& events) {
    // TODO: Open in binary mode. Write the vector's size as the record count,
    // then each event's fields using writeBigEndian32.
    // Flush the stream and check whether output succeeded.

    // HINT: call writeBigEndian32 to write events.size() to the file first.
    // Then loop over the elements of events, and for each one, call writeBigEndian32
    // on both its elapsedSeconds and its eventCount.

    return false;
}
