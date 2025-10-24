#include "sort_char.h"
#include <cstddef>

void sort_char(char* v) {
    if (!v) return;
    
    size_t length = 0;
    while (v[length] != '\0') {
        length++;
    }
    
    if (length <= 1) return;
    
    for (size_t i = 0; i < length - 1; i++) {
        for (size_t j = 0; j < length - 1 - i; j++) {
            if (v[j] > v[j + 1]) {
                char temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
}
