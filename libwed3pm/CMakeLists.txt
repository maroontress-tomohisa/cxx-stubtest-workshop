set(CMAKE_CXX_STANDARD 20)

if(CMAKE_COMPILER_IS_GNUCXX)
    include(CodeCoverage)
endif()

add_library(wed3pm STATIC
    src/wed3pm/Affairs.cxx
    include/wed3pm/Affairs.h
    include/wed3pm/DefaultToolkit.h
    include/wed3pm/Toolkit.h
    include/wed3pm/GoodAffair.h)

if(CMAKE_COMPILER_IS_GNUCXX)
    append_coverage_compiler_flags_to_target(wed3pm)
endif()

target_include_directories(wed3pm PUBLIC include)

if(CMAKE_COMPILER_IS_GNUCXX)
    setup_target_for_coverage_gcovr_html(
        NAME coverage
        EXECUTABLE bash -c "ctest --test-dir test-with-simple-stub || exit 0")
endif()
