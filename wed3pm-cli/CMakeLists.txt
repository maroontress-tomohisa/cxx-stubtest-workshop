set(CMAKE_CXX_STANDARD 20)

add_executable(wed3pm-cli main.cxx)

target_include_directories(wed3pm-cli PRIVATE wed3pm)

target_link_libraries(wed3pm-cli wed3pm)
