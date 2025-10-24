#include "sort_char.h"
#include <iostream>
#include <cstring>

bool test_basic_sorting() {
    char test[] = "hello";
    sort_char(test);
    return strcmp(test, "ehllo") == 0;
}

bool test_empty_string() {
    char test[] = "";
    sort_char(test);
    return strlen(test) == 0;
}

bool test_single_char() {
    char test[] = "a";
    sort_char(test);
    return strcmp(test, "a") == 0;
}

bool test_already_sorted() {
    char test[] = "abc";
    sort_char(test);
    return strcmp(test, "abc") == 0;
}

bool test_reverse_sorted() {
    char test[] = "cba";
    sort_char(test);
    return strcmp(test, "abc") == 0;
}

bool test_duplicates() {
    char test[] = "aabbcc";
    sort_char(test);
    return strcmp(test, "aabbcc") == 0;
}

bool test_mixed_case() {
    char test[] = "BaC";
    sort_char(test);
    return strcmp(test, "BCa") == 0;
}

bool test_null_pointer() {
    sort_char(nullptr);
    return true;
}

int main() {
    struct {
        const char* name;
        bool (*test)();
    } tests[] = {
        {"Basic sorting", test_basic_sorting},
        {"Empty string", test_empty_string},
        {"Single character", test_single_char},
        {"Already sorted", test_already_sorted},
        {"Reverse sorted", test_reverse_sorted},
        {"Duplicates", test_duplicates},
        {"Mixed case", test_mixed_case},
        {"Null pointer", test_null_pointer}
    };
    
    int passed = 0;
    int total = sizeof(tests) / sizeof(tests[0]);
    
    std::cout << "=== Character Sort Tests (Bubble Sort) ===" << std::endl;
    
    for (int i = 0; i < total; i++) {
        std::cout << "Running: " << tests[i].name << "... ";
        if (tests[i].test()) {
            std::cout << "PASS" << std::endl;
            passed++;
        } else {
            std::cout << "FAIL" << std::endl;
        }
    }
    
    std::cout << "\nResults: " << passed << "/" << total << " tests passed" << std::endl;
    
    return (passed == total) ? 0 : 1;
}
