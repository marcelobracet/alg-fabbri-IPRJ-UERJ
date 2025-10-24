add_executable(test-sort_char test_sort_char.cpp)
target_link_libraries(test-sort_char libsort_char)

enable_testing()
add_test(NAME CharSortTest COMMAND test-sort_char)
