set(CMAKE_CXX_STANDARD 20)

enable_testing()

add_executable(test-with-simple-stub
    AffairsTest.cxx
    GoodAffairTest.cxx
    DecoyToolkit.h)

target_include_directories(test-with-simple-stub PRIVATE wed3pm)

target_link_libraries(test-with-simple-stub wed3pm GTest::gtest_main)

if(CMAKE_COMPILER_IS_GNUCXX)
    target_link_libraries(test-with-simple-stub gcov)
endif()

include(GoogleTest)

gtest_discover_tests(test-with-simple-stub)
