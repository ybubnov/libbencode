find_package(Boost COMPONENTS unit_test_framework REQUIRED)

# Define the c++ standard.
add_definitions(-std=c++11)


file(GLOB bencode_TEST_SOURCES *.cpp)

foreach(bencode_TEST_SOURCE ${bencode_TEST_SOURCES})
    # Extract extension fomr file name.
    get_filename_component(bencode_TEST ${bencode_TEST_SOURCE} NAME_WE)

    add_executable(${bencode_TEST} ${bencode_TEST_SOURCE})
    target_link_libraries(${bencode_TEST} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

    # Define a new test from the source file.
    add_test(NAME ${bencode_TEST} COMMAND ${bencode_TEST})
endforeach(bencode_TEST_SOURCE)
