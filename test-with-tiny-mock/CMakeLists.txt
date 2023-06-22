set(CMAKE_CXX_STANDARD 20)

enable_testing()

add_executable(test-with-tiny-mock
    AffairsTest.cxx
    GoodAffairTest.cxx
    DecoyBuilderToolkit.h
    DecoyToolkit.h
    extension.cxx
    tinymock/Call.h
    tinymock/Parameters.h
    tinymock/Scenario.h
    tinymock/ScenarioBuilder.h
    tinymock/namespace.h)

target_include_directories(test-with-tiny-mock PRIVATE wed3pm)

target_link_libraries(test-with-tiny-mock wed3pm GTest::gtest_main)

if(CMAKE_COMPILER_IS_GNUCXX)
    target_link_libraries(test-with-tiny-mock gcov)
endif()

include(GoogleTest)

gtest_discover_tests(test-with-tiny-mock)
