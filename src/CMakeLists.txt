set(SOURCES
    json-128.c
    tokenizer.c
    version.c
)

add_library(json_128_lib STATIC ${SOURCES})
