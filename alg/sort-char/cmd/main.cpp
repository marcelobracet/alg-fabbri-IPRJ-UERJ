#include "sort_char.h"
#include <iostream>
#include <cstring>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <string>" << std::endl;
        std::cout << "Example: " << argv[0] << " \"hello world\"" << std::endl;
        return 1;
    }
    
    size_t len = strlen(argv[1]);
    char* input = new char[len + 1];
    strcpy(input, argv[1]);
    
    std::cout << "Original: \"" << input << "\"" << std::endl;
    
    sort_char(input);
    
    std::cout << "Sorted:   \"" << input << "\"" << std::endl;
    
    delete[] input;
    return 0;
}
