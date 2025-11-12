/*
 * =====================================================================================
 * 
 *        Filename:  bigstring.h
 * 
 *     Description:  BigString - estrutura ligada de blocos textuais
 *                   Duas representações: ponteiros e array fixo
 * 
 *         Version:  1.0
 *         Created:  2025
 *        Compiler:  g++
 * 
 *          Author:  IPRJ/UERJ
 * 
 * =====================================================================================
 */

#ifndef BIGSTRING_H
#define BIGSTRING_H

#include <cstddef>
#include <cstring>
#include <vector>
#include <iostream>

// =====================================================================================
// REPRESENTAÇÃO 1: Bloco com ponteiro (malloc)
// =====================================================================================
struct BigStringNodePtr {
    char *block;                    // Ponteiro para bloco alocado com malloc
    size_t block_size;              // Tamanho real do bloco usado
    BigStringNodePtr *next;         // Próximo nó
    
    BigStringNodePtr() : block(nullptr), block_size(0), next(nullptr) {}
    ~BigStringNodePtr() {
        if (block) {
            free(block);
            block = nullptr;
        }
    }
};

// =====================================================================================
// REPRESENTAÇÃO 2: Bloco com array fixo
// =====================================================================================
#define MAX_CHAR_PER_BLOCK 4096  // 4096 bytes = 1 página = ~64 cache lines

struct BigStringNodeFixed {
    char block[MAX_CHAR_PER_BLOCK];  // Array fixo
    size_t block_size;                // Quantos caracteres estão sendo usados
    BigStringNodeFixed *next;         // Próximo nó
    
    BigStringNodeFixed() : block_size(0), next(nullptr) {
        block[0] = '\0';
    }
};

// =====================================================================================
// CLASSE BigString - Representação com ponteiros
// =====================================================================================
class BigString {
public:
    // Construtor
    BigString();
    
    // Destrutor
    ~BigString();
    
    // Construtor de cópia (desabilitado por simplicidade)
    BigString(const BigString&) = delete;
    BigString& operator=(const BigString&) = delete;
    
    // Adiciona texto ao final
    void append(const char* text);
    
    // Concatena outra BigString
    void concat(BigString& other);
    
    // Insere string simples na posição i
    void inserirSimples(const char* text, size_t i);
    
    // Insere BigString A na posição i
    void inserir(BigString& A, size_t i);
    
    // Acesso aleatório (random access) - operator[]
    char operator[](size_t i) const;
    
    // Retorna tamanho total
    size_t tamanho() const { return total_size; }
    
    // Imprime a string completa
    void print() const;
    
    // Retorna como string C++ (para debug)
    std::string toString() const;
    
    // Retorna tabela de tamanhos cumulativos (para busca binária)
    std::vector<size_t> getCumulativeSizes() const;

private:
    BigStringNodePtr* head;      // Primeiro nó
    BigStringNodePtr* tail;       // Último nó (para append rápido)
    size_t total_size;            // Tamanho total da string
    
    // Busca binária: encontra o bloco que contém o caractere na posição i
    // Retorna: (nó, offset dentro do bloco)
    std::pair<BigStringNodePtr*, size_t> findBlock(size_t i) const;
    
    // Cria um novo nó com texto
    BigStringNodePtr* createNode(const char* text, size_t len);
    
    // Insere nó após um nó específico
    void insertNodeAfter(BigStringNodePtr* after, BigStringNodePtr* newNode);
};

// =====================================================================================
// CLASSE BigStringFixed - Representação com array fixo
// =====================================================================================
class BigStringFixed {
public:
    // Construtor
    BigStringFixed();
    
    // Destrutor
    ~BigStringFixed();
    
    // Construtor de cópia (desabilitado)
    BigStringFixed(const BigStringFixed&) = delete;
    BigStringFixed& operator=(const BigStringFixed&) = delete;
    
    // Adiciona texto ao final
    void append(const char* text);
    
    // Concatena outra BigStringFixed
    void concat(BigStringFixed& other);
    
    // Insere string simples na posição i
    void inserirSimples(const char* text, size_t i);
    
    // Insere BigStringFixed A na posição i
    void inserir(BigStringFixed& A, size_t i);
    
    // Acesso aleatório (random access) - operator[]
    char operator[](size_t i) const;
    
    // Retorna tamanho total
    size_t tamanho() const { return total_size; }
    
    // Imprime a string completa
    void print() const;
    
    // Retorna como string C++ (para debug)
    std::string toString() const;
    
    // Retorna tabela de tamanhos cumulativos
    std::vector<size_t> getCumulativeSizes() const;

private:
    BigStringNodeFixed* head;     // Primeiro nó
    BigStringNodeFixed* tail;     // Último nó
    size_t total_size;            // Tamanho total
    
    // Busca binária: encontra o bloco que contém o caractere na posição i
    std::pair<BigStringNodeFixed*, size_t> findBlock(size_t i) const;
    
    // Cria um novo nó com texto (pode dividir se necessário)
    void createNodesForText(const char* text, size_t len);
    
    // Insere nó após um nó específico
    void insertNodeAfter(BigStringNodeFixed* after, BigStringNodeFixed* newNode);
    
    // Retorna tamanho usado de um bloco (até '\0' ou MAX_CHAR_PER_BLOCK)
    size_t getBlockUsedSize(BigStringNodeFixed* node) const;
};

#endif // BIGSTRING_H

