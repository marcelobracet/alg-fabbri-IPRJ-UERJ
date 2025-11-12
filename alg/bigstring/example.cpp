/*
 * =====================================================================================
 * 
 *        Filename:  example.cpp
 * 
 *     Description:  Exemplo simples de uso do BigString
 * 
 * =====================================================================================
 */

#include "bigstring.h"
#include <iostream>

int main() {
    std::cout << "╔════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║  BigString - Exemplo Simples de Uso                  ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════╝\n" << std::endl;
    
    // ========== REPRESENTAÇÃO 1: Ponteiros ==========
    std::cout << "📍 REPRESENTAÇÃO 1: Blocos com Ponteiros (malloc)\n" << std::endl;
    
    BigString S;
    S.append("Hello ");
    S.append("World");
    S.append("!");
    
    std::cout << "String S: ";
    S.print();
    std::cout << "Tamanho: " << S.tamanho() << std::endl;
    
    // Indexação
    std::cout << "\nAcesso aleatório:" << std::endl;
    std::cout << "  S[0] = '" << S[0] << "'" << std::endl;
    std::cout << "  S[5] = '" << S[5] << "'" << std::endl;
    std::cout << "  S[10] = '" << S[10] << "'" << std::endl;
    
    // Concat
    BigString A;
    A.append(" BigString");
    S.concat(A);
    
    std::cout << "\nApós concat: ";
    S.print();
    
    // Inserir
    S.inserirSimples("amazing ", 6);
    std::cout << "Após inserirSimples('amazing ', 6): ";
    S.print();
    
    // ========== REPRESENTAÇÃO 2: Array Fixo ==========
    std::cout << "\n\n📍 REPRESENTAÇÃO 2: Blocos com Array Fixo (4096 bytes)\n" << std::endl;
    
    BigStringFixed S2;
    S2.append("Hello ");
    S2.append("World");
    S2.append("!");
    
    std::cout << "String S2: ";
    S2.print();
    std::cout << "Tamanho: " << S2.tamanho() << std::endl;
    
    // Mesmas operações
    std::cout << "\nAcesso aleatório:" << std::endl;
    std::cout << "  S2[0] = '" << S2[0] << "'" << std::endl;
    std::cout << "  S2[5] = '" << S2[5] << "'" << std::endl;
    
    BigStringFixed A2;
    A2.append(" BigStringFixed");
    S2.concat(A2);
    
    std::cout << "\nApós concat: ";
    S2.print();
    
    std::cout << "\n✅ Exemplo concluído!" << std::endl;
    
    return 0;
}

