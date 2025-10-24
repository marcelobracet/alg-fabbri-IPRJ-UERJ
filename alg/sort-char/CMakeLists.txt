add_library(libsort_char sort_char.cpp)
# export public header path for other components
target_include_directories(libsort_char PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(cmd)
add_subdirectory(tests)
add_subdirectory(benchmark)

# Custom target to run benchmarks
add_custom_target(eval-sort-char
  COMMAND bm-sort_char-cmd
  DEPENDS bm-sort_char-cmd
  COMMENT "Running char sort benchmark"
)
