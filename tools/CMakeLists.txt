set(LEMON_SOURCES
    lemon.c
)

add_executable(lemon ${LEMON_SOURCES})
target_compile_options(lemon PRIVATE -Wno-strict-prototypes)
