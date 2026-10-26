cmake_minimum_required(VERSION 3.21)

project("EventLog" LANGUAGES CXX)

option(BUILD_TESTING "Build the unit tests" ON)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Release,MinSizeRel>:ProgramDatabase>>")
endif()

add_library(eventlog_core src/eventlog.cpp)

target_include_directories(eventlog_core PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_compile_features(eventlog_core PUBLIC cxx_std_23)
set_target_properties(eventlog_core PROPERTIES CXX_EXTENSIONS OFF)

add_executable(eventlog src/main.cpp)
target_link_libraries(eventlog PRIVATE eventlog_core)
set_target_properties(eventlog PROPERTIES CXX_EXTENSIONS OFF)

# Keep the supplied examples available when running from the build directory.
foreach(sample_file IN ITEMS events.txt events.bin empty.txt empty.bin truncated.bin)
  configure_file("data/${sample_file}" "data/${sample_file}" COPYONLY)
endforeach()

include(CTest)
if (BUILD_TESTING)
  add_subdirectory("tests")
endif()
