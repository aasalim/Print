add_library(Print STATIC Print.c)
target_include_directories(Print PUBLIC ${Print_SOURCE_DIR}/include)