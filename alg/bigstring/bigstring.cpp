#include "bigstring.h"
#include <cstdlib>
#include <algorithm>
#include <stdexcept>

BigString::BigString() : head(nullptr), tail(nullptr), total_size(0) {}

BigString::~BigString() {
    BigStringNodePtr* current = head;
    while (current) {
        BigStringNodePtr* next = current->next;
        delete current;
        current = next;
    }
}

BigStringNodePtr* BigString::createNode(const char* text, size_t len) {
    if (len == 0) return nullptr;
    
    BigStringNodePtr* node = new BigStringNodePtr();
    node->block = (char*)malloc(len + 1);  // +1 para '\0'
    if (!node->block) {
        delete node;
        return nullptr;
    }
    
    memcpy(node->block, text, len);
    node->block[len] = '\0';
    node->block_size = len;
    node->next = nullptr;
    
    return node;
}

void BigString::append(const char* text) {
    if (!text || strlen(text) == 0) return;
    
    size_t len = strlen(text);
    BigStringNodePtr* newNode = createNode(text, len);
    if (!newNode) return;
    
    if (!head) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    
    total_size += len;
}

void BigString::concat(BigString& other) {
    BigStringNodePtr* current = other.head;
    while (current) {
        append(current->block);
        current = current->next;
    }
}

std::vector<size_t> BigString::getCumulativeSizes() const {
    std::vector<size_t> cumulative;
    size_t sum = 0;
    
    BigStringNodePtr* current = head;
    while (current) {
        sum += current->block_size;
        cumulative.push_back(sum);
        current = current->next;
    }
    
    return cumulative;
}

std::pair<BigStringNodePtr*, size_t> BigString::findBlock(size_t i) const {
    if (i >= total_size || !head) {
        return {nullptr, 0};
    }
    
    std::vector<size_t> cumulative = getCumulativeSizes();
    
    if (cumulative.empty()) {
        return {nullptr, 0};
    }
    
    size_t left = 0;
    size_t right = cumulative.size();
    size_t block_index = 0;
    
    while (left < right) {
        size_t mid = left + (right - left) / 2;
        
        if (cumulative[mid] > i) {
            block_index = mid;
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    
    if (block_index >= cumulative.size()) {
        block_index = cumulative.size() - 1;
    }
    
    BigStringNodePtr* current = head;
    size_t offset = i;
    
    for (size_t j = 0; j < block_index && current; j++) {
        offset -= current->block_size;
        current = current->next;
    }
    
    if (!current) {
        return {nullptr, 0};
    }
    
    return {current, offset};
}

char BigString::operator[](size_t i) const {
    auto [node, offset] = findBlock(i);
    if (!node || offset >= node->block_size) {
        return '\0';
    }
    return node->block[offset];
}

void BigString::insertNodeAfter(BigStringNodePtr* after, BigStringNodePtr* newNode) {
    if (!after) {
        // Inserir no início
        newNode->next = head;
        head = newNode;
        if (!tail) tail = newNode;
    } else {
        newNode->next = after->next;
        after->next = newNode;
        if (after == tail) {
            tail = newNode;
        }
    }
}

void BigString::inserirSimples(const char* text, size_t i) {
    if (!text || strlen(text) == 0) return;
    if (i > total_size) i = total_size;  // Ajusta para o final se necessário
    
    size_t len = strlen(text);
    BigStringNodePtr* newNode = createNode(text, len);
    if (!newNode) return;
    
    if (i == 0) {
        // Inserir no início
        insertNodeAfter(nullptr, newNode);
    } else if (i == total_size) {
        // Inserir no final
        append(text);
        delete newNode;  // append já criou o nó
        return;
    } else {
        // Inserir no meio
        auto [targetNode, offset] = findBlock(i - 1);
        
        if (offset == targetNode->block_size - 1) {
            // Inserir após o bloco completo
            insertNodeAfter(targetNode, newNode);
        } else {
            // Dividir o bloco: parte antes + novo + parte depois
            size_t before_len = offset + 1;
            size_t after_len = targetNode->block_size - before_len;
            
            // Criar nó com parte depois
            BigStringNodePtr* afterNode = nullptr;
            if (after_len > 0) {
                afterNode = createNode(targetNode->block + before_len, after_len);
            }
            
            // Redimensionar bloco atual
            targetNode->block = (char*)realloc(targetNode->block, before_len + 1);
            targetNode->block[before_len] = '\0';
            targetNode->block_size = before_len;
            
            // Inserir novo nó
            insertNodeAfter(targetNode, newNode);
            
            // Inserir parte depois
            if (afterNode) {
                insertNodeAfter(newNode, afterNode);
            }
        }
    }
    
    total_size += len;
}

void BigString::inserir(BigString& A, size_t i) {
    if (A.total_size == 0) return;
    if (i > total_size) i = total_size;
    
    if (i == total_size) {
        // Inserir no final = concat
        concat(A);
        return;
    }
    
    BigStringNodePtr* currentA = A.head;
    BigStringNodePtr* firstNew = nullptr;
    BigStringNodePtr* lastNew = nullptr;
    
    while (currentA) {
        BigStringNodePtr* newNode = createNode(currentA->block, currentA->block_size);
        if (!newNode) break;
        
        if (!firstNew) {
            firstNew = lastNew = newNode;
        } else {
            lastNew->next = newNode;
            lastNew = newNode;
        }
        
        currentA = currentA->next;
    }
    
    if (!firstNew) return;
    
    if (i == 0) {
        lastNew->next = head;
        head = firstNew;
        if (!tail) tail = lastNew;
    } else {
        auto [targetNode, offset] = findBlock(i - 1);
        
        if (offset == targetNode->block_size - 1) {
            // Inserir após o bloco completo
            lastNew->next = targetNode->next;
            targetNode->next = firstNew;
            if (targetNode == tail) tail = lastNew;
        } else {
            // Dividir bloco e inserir no meio
            size_t before_len = offset + 1;
            size_t after_len = targetNode->block_size - before_len;
            
            BigStringNodePtr* afterNode = nullptr;
            if (after_len > 0) {
                afterNode = createNode(targetNode->block + before_len, after_len);
            }
            
            targetNode->block = (char*)realloc(targetNode->block, before_len + 1);
            targetNode->block[before_len] = '\0';
            targetNode->block_size = before_len;
            
            lastNew->next = afterNode ? afterNode : targetNode->next;
            targetNode->next = firstNew;
            
            if (afterNode) {
                if (targetNode == tail) tail = afterNode;
            } else if (targetNode == tail) {
                tail = lastNew;
            }
        }
    }
    
    total_size += A.total_size;
}

void BigString::print() const {
    BigStringNodePtr* current = head;
    while (current) {
        std::cout << current->block;
        current = current->next;
    }
    std::cout << std::endl;
}

std::string BigString::toString() const {
    std::string result;
    BigStringNodePtr* current = head;
    while (current) {
        result += std::string(current->block, current->block_size);
        current = current->next;
    }
    return result;
}

// =====================================================================================
// IMPLEMENTAÇÃO: BigStringFixed (Representação com array fixo)
// =====================================================================================

BigStringFixed::BigStringFixed() : head(nullptr), tail(nullptr), total_size(0) {}

BigStringFixed::~BigStringFixed() {
    BigStringNodeFixed* current = head;
    while (current) {
        BigStringNodeFixed* next = current->next;
        delete current;
        current = next;
    }
}

size_t BigStringFixed::getBlockUsedSize(BigStringNodeFixed* node) const {
    if (!node) return 0;
    
    // Procura '\0' ou usa block_size
    size_t used = 0;
    while (used < MAX_CHAR_PER_BLOCK && node->block[used] != '\0') {
        used++;
    }
    
    return (used < node->block_size) ? used : node->block_size;
}

void BigStringFixed::createNodesForText(const char* text, size_t len) {
    size_t pos = 0;
    
    while (pos < len) {
        BigStringNodeFixed* newNode = new BigStringNodeFixed();
        size_t copy_len = std::min(len - pos, (size_t)MAX_CHAR_PER_BLOCK - 1);
        
        memcpy(newNode->block, text + pos, copy_len);
        newNode->block[copy_len] = '\0';
        newNode->block_size = copy_len;
        newNode->next = nullptr;
        
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        
        pos += copy_len;
        total_size += copy_len;
    }
}

void BigStringFixed::append(const char* text) {
    if (!text || strlen(text) == 0) return;
    createNodesForText(text, strlen(text));
}

void BigStringFixed::concat(BigStringFixed& other) {
    BigStringNodeFixed* current = other.head;
    while (current) {
        size_t used = getBlockUsedSize(current);
        if (used > 0) {
            createNodesForText(current->block, used);
        }
        current = current->next;
    }
}

std::vector<size_t> BigStringFixed::getCumulativeSizes() const {
    std::vector<size_t> cumulative;
    size_t sum = 0;
    
    BigStringNodeFixed* current = head;
    while (current) {
        sum += getBlockUsedSize(current);
        cumulative.push_back(sum);
        current = current->next;
    }
    
    return cumulative;
}

std::pair<BigStringNodeFixed*, size_t> BigStringFixed::findBlock(size_t i) const {
    if (i >= total_size || !head) {
        return {nullptr, 0};
    }
    
    // Busca binária na tabela de tamanhos cumulativos
    std::vector<size_t> cumulative = getCumulativeSizes();
    
    if (cumulative.empty()) {
        return {nullptr, 0};
    }
    
    // Busca binária: encontrar o menor índice onde cumulative[j] > i
    size_t left = 0;
    size_t right = cumulative.size();
    size_t block_index = 0;
    
    while (left < right) {
        size_t mid = left + (right - left) / 2;
        
        if (cumulative[mid] > i) {
            block_index = mid;
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    
    // Se não encontrou, está no último bloco
    if (block_index >= cumulative.size()) {
        block_index = cumulative.size() - 1;
    }
    
    // Encontra o bloco e offset
    BigStringNodeFixed* current = head;
    size_t offset = i;
    
    for (size_t j = 0; j < block_index && current; j++) {
        offset -= getBlockUsedSize(current);
        current = current->next;
    }
    
    if (!current) {
        return {nullptr, 0};
    }
    
    return {current, offset};
}

char BigStringFixed::operator[](size_t i) const {
    auto [node, offset] = findBlock(i);
    if (!node) return '\0';
    
    size_t used = getBlockUsedSize(node);
    if (offset >= used) return '\0';
    
    return node->block[offset];
}

void BigStringFixed::insertNodeAfter(BigStringNodeFixed* after, BigStringNodeFixed* newNode) {
    if (!after) {
        newNode->next = head;
        head = newNode;
        if (!tail) tail = newNode;
    } else {
        newNode->next = after->next;
        after->next = newNode;
        if (after == tail) tail = newNode;
    }
}

void BigStringFixed::inserirSimples(const char* text, size_t i) {
    if (!text || strlen(text) == 0) return;
    if (i > total_size) i = total_size;
    
    size_t len = strlen(text);
    
    if (i == total_size) {
        // Inserir no final
        append(text);
        return;
    }
    
    auto [targetNode, offset] = findBlock(i);
    
    if (offset == 0 && targetNode->block_size < MAX_CHAR_PER_BLOCK) {
        // Pode inserir no início do bloco se houver espaço
        size_t space = MAX_CHAR_PER_BLOCK - targetNode->block_size - 1;
        size_t insert_len = std::min(len, space);
        
        // Move conteúdo existente
        memmove(targetNode->block + insert_len, targetNode->block, targetNode->block_size);
        memcpy(targetNode->block, text, insert_len);
        targetNode->block_size += insert_len;
        targetNode->block[targetNode->block_size] = '\0';
        
        if (insert_len < len) {
            // Criar novos blocos para o resto
            createNodesForText(text + insert_len, len - insert_len);
        }
    } else {
        // Dividir bloco e inserir
        size_t before_len = offset;
        size_t after_len = getBlockUsedSize(targetNode) - before_len;
        
        // Criar novo bloco com parte depois
        BigStringNodeFixed* afterNode = nullptr;
        if (after_len > 0) {
            afterNode = new BigStringNodeFixed();
            memcpy(afterNode->block, targetNode->block + before_len, after_len);
            afterNode->block[after_len] = '\0';
            afterNode->block_size = after_len;
        }
        
        // Ajustar bloco atual
        targetNode->block[before_len] = '\0';
        targetNode->block_size = before_len;
        
        // Criar blocos para o texto a inserir
        BigStringNodeFixed* firstNew = nullptr;
        BigStringNodeFixed* lastNew = nullptr;
        size_t pos = 0;
        
        while (pos < len) {
            BigStringNodeFixed* newNode = new BigStringNodeFixed();
            size_t copy_len = std::min(len - pos, (size_t)MAX_CHAR_PER_BLOCK - 1);
            
            memcpy(newNode->block, text + pos, copy_len);
            newNode->block[copy_len] = '\0';
            newNode->block_size = copy_len;
            
            if (!firstNew) {
                firstNew = lastNew = newNode;
            } else {
                lastNew->next = newNode;
                lastNew = newNode;
            }
            
            pos += copy_len;
        }
        
        // Conectar: targetNode -> firstNew -> ... -> lastNew -> afterNode
        if (firstNew) {
            targetNode->next = firstNew;
            lastNew->next = afterNode;
            if (afterNode) {
                if (targetNode == tail) tail = afterNode;
            } else {
                if (targetNode == tail) tail = lastNew;
            }
        } else {
            targetNode->next = afterNode;
            if (targetNode == tail && afterNode) tail = afterNode;
        }
    }
    
    total_size += len;
}

void BigStringFixed::inserir(BigStringFixed& A, size_t i) {
    if (A.total_size == 0) return;
    if (i > total_size) i = total_size;
    
    if (i == total_size) {
        concat(A);
        return;
    }
    
    // Copiar todos os nós de A
    BigStringNodeFixed* currentA = A.head;
    BigStringNodeFixed* firstNew = nullptr;
    BigStringNodeFixed* lastNew = nullptr;
    
    while (currentA) {
        size_t used = getBlockUsedSize(currentA);
        if (used > 0) {
            size_t pos = 0;
            while (pos < used) {
                BigStringNodeFixed* newNode = new BigStringNodeFixed();
                size_t copy_len = std::min(used - pos, (size_t)MAX_CHAR_PER_BLOCK - 1);
                
                memcpy(newNode->block, currentA->block + pos, copy_len);
                newNode->block[copy_len] = '\0';
                newNode->block_size = copy_len;
                
                if (!firstNew) {
                    firstNew = lastNew = newNode;
                } else {
                    lastNew->next = newNode;
                    lastNew = newNode;
                }
                
                pos += copy_len;
            }
        }
        currentA = currentA->next;
    }
    
    if (!firstNew) return;
    
    // Inserir na posição i
    auto [targetNode, offset] = findBlock(i);
    
    if (offset == 0 && targetNode->block_size < MAX_CHAR_PER_BLOCK) {
        // Tentar inserir no início do bloco
        // (implementação similar ao inserirSimples)
        inserirSimples(A.toString().c_str(), i);
        return;
    }
    
    // Dividir e inserir
    size_t before_len = offset;
    size_t after_len = getBlockUsedSize(targetNode) - before_len;
    
    BigStringNodeFixed* afterNode = nullptr;
    if (after_len > 0) {
        afterNode = new BigStringNodeFixed();
        memcpy(afterNode->block, targetNode->block + before_len, after_len);
        afterNode->block[after_len] = '\0';
        afterNode->block_size = after_len;
    }
    
    targetNode->block[before_len] = '\0';
    targetNode->block_size = before_len;
    
    lastNew->next = afterNode ? afterNode : targetNode->next;
    targetNode->next = firstNew;
    
    if (afterNode) {
        if (targetNode == tail) tail = afterNode;
    } else if (targetNode == tail) {
        tail = lastNew;
    }
    
    total_size += A.total_size;
}

void BigStringFixed::print() const {
    BigStringNodeFixed* current = head;
    while (current) {
        size_t used = getBlockUsedSize(current);
        std::cout.write(current->block, used);
        current = current->next;
    }
    std::cout << std::endl;
}

std::string BigStringFixed::toString() const {
    std::string result;
    BigStringNodeFixed* current = head;
    while (current) {
        size_t used = getBlockUsedSize(current);
        result += std::string(current->block, used);
        current = current->next;
    }
    return result;
}

