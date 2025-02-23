set(TEST_SOURCES
    attractor/attractor.c
    test.c
    version.c
)

add_executable(json-128-test ${TEST_SOURCES})
target_link_libraries(json-128-test PRIVATE json_128_lib)
