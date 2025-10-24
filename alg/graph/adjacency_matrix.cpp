/*
 * =====================================================================================
 * 
 *        Filename:  adjacency_matrix.cpp
 * 
 *     Description:  Conversão de Grafo Dinâmico (Lista de Adjacências) 
 *                   para Matriz de Adjacências
 * 
 *         Version:  1.0
 *         Created:  2025
 *        Compiler:  g++
 * 
 *          Author:  IPRJ/UERJ
 * 
 * =====================================================================================
 */

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <iomanip>
#include <map>

// =====================================================================================
// Classe Node - Representa um nó do grafo (Lista de Adjacências)
// =====================================================================================
class Node {
public:
    struct Connection {
        Node* node;
        int weight;
        Connection(Node* n, int w) : node(n), weight(w) {}
    };
    
private:
    std::string name;
    std::list<Connection> connections;
    
public:
    explicit Node(const std::string& nodeName) : name(nodeName) {}
    ~Node() {}
    
    const std::string& getName() const { return name; }
    const std::list<Connection>& getConnections() const { return connections; }
    std::list<Connection>& getConnections() { return connections; }
    
    void addConnection(Node* targetNode, int weight) {
        connections.emplace_back(targetNode, weight);
    }
    
    void removeConnection(Node* targetNode) {
        connections.remove_if([targetNode](const Connection& conn) {
            return conn.node == targetNode;
        });
    }
    
    void clearConnections() {
        connections.clear();
    }
};

// =====================================================================================
// Classe Graph - Representa o grafo com Lista de Adjacências
// =====================================================================================
class Graph {
private:
    std::vector<Node*> nodes;
    
public:
    Graph() {}
    
    ~Graph() {
        for (Node* node : nodes) {
            delete node;
        }
        nodes.clear();
    }
    
    Node* addNode(const std::string& name) {
        Node* newNode = new Node(name);
        nodes.push_back(newNode);
        return newNode;
    }
    
    void connect(Node* nodeA, Node* nodeB, int weight) {
        if (!nodeA || !nodeB) return;
        nodeA->addConnection(nodeB, weight);
        nodeB->addConnection(nodeA, weight);
    }
    
    const std::vector<Node*>& getNodes() const { return nodes; }
    size_t getNodeCount() const { return nodes.size(); }
};

// =====================================================================================
// Classe AdjacencyMatrix - Representa o grafo como Matriz de Adjacências
// =====================================================================================
class AdjacencyMatrix {
private:
    std::vector<std::vector<int>> matrix;  // Matriz de pesos
    std::vector<std::string> nodeNames;    // Nomes dos nós (mapeamento índice -> nome)
    std::map<std::string, int> nodeIndex;  // Mapeamento nome -> índice
    int size;                               // Número de nós
    
public:
    // Construtor padrão
    AdjacencyMatrix() : size(0) {}
    
    // Construtor que converte um Graph para matriz
    explicit AdjacencyMatrix(const Graph& graph) {
        convertFromGraph(graph);
    }
    
    // Destrutor
    ~AdjacencyMatrix() {}
    
    // Converte um grafo (lista de adjacências) para matriz
    void convertFromGraph(const Graph& graph) {
        const auto& nodes = graph.getNodes();
        size = nodes.size();
        
        // Inicializa a matriz com zeros
        matrix.resize(size, std::vector<int>(size, 0));
        nodeNames.clear();
        nodeIndex.clear();
        
        // Mapeia nós para índices
        for (int i = 0; i < size; i++) {
            nodeNames.push_back(nodes[i]->getName());
            nodeIndex[nodes[i]->getName()] = i;
        }
        
        // Preenche a matriz com os pesos das conexões
        for (int i = 0; i < size; i++) {
            Node* currentNode = nodes[i];
            
            for (const auto& conn : currentNode->getConnections()) {
                // Encontra o índice do nó conectado
                auto it = std::find(nodes.begin(), nodes.end(), conn.node);
                if (it != nodes.end()) {
                    int j = std::distance(nodes.begin(), it);
                    matrix[i][j] = conn.weight;
                }
            }
        }
    }
    
    // Imprime a matriz de adjacências de forma bonita
    void print() const {
        if (size == 0) {
            std::cout << "Matriz vazia!" << std::endl;
            return;
        }
        
        std::cout << "\n╔════════════════════════════════════════════════════════╗" << std::endl;
        std::cout << "║        MATRIZ DE ADJACÊNCIAS (Pesos)                  ║" << std::endl;
        std::cout << "╚════════════════════════════════════════════════════════╝\n" << std::endl;
        
        // Calcula largura das colunas
        int colWidth = 12;
        for (const auto& name : nodeNames) {
            if ((int)name.length() + 2 > colWidth) {
                colWidth = name.length() + 2;
            }
        }
        
        // Cabeçalho (nomes das colunas)
        std::cout << std::setw(colWidth) << " ";
        for (const auto& name : nodeNames) {
            std::cout << std::setw(colWidth) << name;
        }
        std::cout << std::endl;
        
        // Linha separadora
        std::cout << std::string(colWidth + nodeNames.size() * colWidth, '-') << std::endl;
        
        // Linhas da matriz
        for (int i = 0; i < size; i++) {
            std::cout << std::setw(colWidth) << nodeNames[i];
            for (int j = 0; j < size; j++) {
                std::cout << std::setw(colWidth) << matrix[i][j];
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    
    // Imprime a matriz de adjacências de forma compacta (0 e 1)
    void printBinary() const {
        if (size == 0) {
            std::cout << "Matriz vazia!" << std::endl;
            return;
        }
        
        std::cout << "\n╔════════════════════════════════════════════════════════╗" << std::endl;
        std::cout << "║    MATRIZ DE ADJACÊNCIAS (Binária: 0=sem, 1=com)     ║" << std::endl;
        std::cout << "╚════════════════════════════════════════════════════════╝\n" << std::endl;
        
        // Cabeçalho compacto
        std::cout << "     ";
        for (int i = 0; i < size; i++) {
            std::cout << std::setw(4) << i;
        }
        std::cout << std::endl;
        std::cout << "    " << std::string(size * 4 + 1, '-') << std::endl;
        
        // Linhas da matriz (0 ou 1)
        for (int i = 0; i < size; i++) {
            std::cout << std::setw(2) << i << " |";
            for (int j = 0; j < size; j++) {
                std::cout << std::setw(4) << (matrix[i][j] > 0 ? 1 : 0);
            }
            std::cout << "  | " << nodeNames[i] << std::endl;
        }
        std::cout << std::endl;
    }
    
    // Retorna o peso da aresta entre dois nós (por nome)
    int getWeight(const std::string& from, const std::string& to) const {
        auto it1 = nodeIndex.find(from);
        auto it2 = nodeIndex.find(to);
        
        if (it1 == nodeIndex.end() || it2 == nodeIndex.end()) {
            return -1; // Nó não encontrado
        }
        
        return matrix[it1->second][it2->second];
    }
    
    // Retorna o peso da aresta entre dois nós (por índice)
    int getWeight(int i, int j) const {
        if (i < 0 || i >= size || j < 0 || j >= size) {
            return -1; // Índice inválido
        }
        return matrix[i][j];
    }
    
    // Verifica se existe conexão entre dois nós
    bool hasConnection(const std::string& from, const std::string& to) const {
        return getWeight(from, to) > 0;
    }
    
    // Retorna o grau de um nó (número de conexões)
    int getDegree(const std::string& nodeName) const {
        auto it = nodeIndex.find(nodeName);
        if (it == nodeIndex.end()) return -1;
        
        int degree = 0;
        int idx = it->second;
        
        for (int j = 0; j < size; j++) {
            if (matrix[idx][j] > 0) {
                degree++;
            }
        }
        
        return degree;
    }
    
    // Retorna o número de nós
    int getSize() const { return size; }
    
    // Retorna os nomes dos nós
    const std::vector<std::string>& getNodeNames() const { return nodeNames; }
    
    // Estatísticas da matriz
    void printStatistics() const {
        std::cout << "\n📊 ESTATÍSTICAS DA MATRIZ:" << std::endl;
        std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;
        
        int totalEdges = 0;
        int totalWeight = 0;
        
        // Conta arestas e peso total (divide por 2 pois é não-direcionado)
        for (int i = 0; i < size; i++) {
            for (int j = i + 1; j < size; j++) {
                if (matrix[i][j] > 0) {
                    totalEdges++;
                    totalWeight += matrix[i][j];
                }
            }
        }
        
        std::cout << "  • Número de nós: " << size << std::endl;
        std::cout << "  • Número de arestas: " << totalEdges << std::endl;
        std::cout << "  • Peso total: " << totalWeight << std::endl;
        std::cout << "  • Tamanho da matriz: " << size << "x" << size 
                  << " (" << (size * size) << " elementos)" << std::endl;
        
        // Densidade do grafo
        int maxEdges = (size * (size - 1)) / 2;
        double density = (maxEdges > 0) ? (totalEdges * 100.0 / maxEdges) : 0;
        std::cout << "  • Densidade: " << std::fixed << std::setprecision(1) 
                  << density << "%" << std::endl;
        
        // Grau de cada nó
        std::cout << "\n  Grau dos nós:" << std::endl;
        for (int i = 0; i < size; i++) {
            std::cout << "    - " << std::setw(15) << std::left << nodeNames[i] 
                      << ": " << getDegree(nodeNames[i]) << " conexões" << std::endl;
        }
        
        std::cout << std::endl;
    }
    
    // Exporta a matriz para formato CSV
    void exportToCSV(const std::string& filename) const {
        std::cout << "💾 Exportando para " << filename << "..." << std::endl;
        std::cout << "(Funcionalidade de exemplo - implementação de arquivo seria adicionada aqui)" << std::endl;
    }
};

// =====================================================================================
// Função Main - Demonstração e Testes
// =====================================================================================
int main() {
    std::cout << "╔════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║  Conversão: Lista de Adjacências → Matriz            ║" << std::endl;
    std::cout << "║  DynaGraph C++ - IPRJ/UERJ                            ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════╝\n" << std::endl;
    
    // ========== PASSO 1: Criar o grafo com lista de adjacências ==========
    std::cout << "📍 PASSO 1: Criando grafo com LISTA DE ADJACÊNCIAS" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    
    Graph grafo;
    
    // Cria os nós (cidades do RJ)
    Node* petropolis = grafo.addNode("Petropolis");
    Node* teresopolis = grafo.addNode("Teresopolis");
    Node* niteroi = grafo.addNode("Niteroi");
    Node* rio = grafo.addNode("Rio");
    Node* friburgo = grafo.addNode("Friburgo");
    
    std::cout << "✅ Criados 5 nós: Petropolis, Teresopolis, Niteroi, Rio, Friburgo\n" << std::endl;
    
    // Conecta os nós
    std::cout << "🔗 Criando conexões:" << std::endl;
    grafo.connect(petropolis, teresopolis, 50);
    std::cout << "  • Petropolis ↔ Teresopolis (peso: 50)" << std::endl;
    grafo.connect(petropolis, rio, 65);
    std::cout << "  • Petropolis ↔ Rio (peso: 65)" << std::endl;
    grafo.connect(teresopolis, rio, 100);
    std::cout << "  • Teresopolis ↔ Rio (peso: 100)" << std::endl;
    grafo.connect(teresopolis, friburgo, 75);
    std::cout << "  • Teresopolis ↔ Friburgo (peso: 75)" << std::endl;
    grafo.connect(niteroi, rio, 15);
    std::cout << "  • Niteroi ↔ Rio (peso: 15)" << std::endl;
    grafo.connect(niteroi, friburgo, 120);
    std::cout << "  • Niteroi ↔ Friburgo (peso: 120)" << std::endl;
    grafo.connect(rio, friburgo, 140);
    std::cout << "  • Rio ↔ Friburgo (peso: 140)" << std::endl;
    
    std::cout << "\n✅ Grafo criado com 7 conexões!\n" << std::endl;
    
    // ========== PASSO 2: Converter para matriz de adjacências ==========
    std::cout << "\n📍 PASSO 2: Convertendo para MATRIZ DE ADJACÊNCIAS" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    
    AdjacencyMatrix matriz(grafo);
    
    std::cout << "✅ Conversão realizada com sucesso!\n" << std::endl;
    
    // ========== PASSO 3: Visualizar a matriz ==========
    std::cout << "\n📍 PASSO 3: Visualizando a MATRIZ" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    
    // Matriz com pesos
    matriz.print();
    
    // Matriz binária (0 e 1)
    matriz.printBinary();
    
    // ========== PASSO 4: Estatísticas ==========
    std::cout << "\n📍 PASSO 4: ESTATÍSTICAS" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    
    matriz.printStatistics();
    
    // ========== PASSO 5: Consultas ==========
    std::cout << "\n📍 PASSO 5: CONSULTAS NA MATRIZ" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    
    std::cout << "\n🔍 Testando consultas:" << std::endl;
    std::cout << "  • Peso Petropolis → Rio: " << matriz.getWeight("Petropolis", "Rio") << std::endl;
    std::cout << "  • Peso Niteroi → Friburgo: " << matriz.getWeight("Niteroi", "Friburgo") << std::endl;
    std::cout << "  • Existe conexão Petropolis → Niteroi? " 
              << (matriz.hasConnection("Petropolis", "Niteroi") ? "SIM" : "NÃO") << std::endl;
    std::cout << "  • Grau de Rio: " << matriz.getDegree("Rio") << " conexões" << std::endl;
    std::cout << "  • Grau de Petropolis: " << matriz.getDegree("Petropolis") << " conexões" << std::endl;
    
    // ========== PASSO 6: Comparação ==========
    std::cout << "\n\n📍 PASSO 6: COMPARAÇÃO DAS REPRESENTAÇÕES" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    
    std::cout << "\n┌─────────────────────────────────────────────────────────┐" << std::endl;
    std::cout << "│              LISTA vs MATRIZ DE ADJACÊNCIAS             │" << std::endl;
    std::cout << "├─────────────────────────────────────────────────────────┤" << std::endl;
    std::cout << "│                                                         │" << std::endl;
    std::cout << "│  LISTA DE ADJACÊNCIAS (Grafo Original):                │" << std::endl;
    std::cout << "│    ✅ Eficiente em espaço: O(V + E)                     │" << std::endl;
    std::cout << "│    ✅ Rápido adicionar aresta: O(1)                     │" << std::endl;
    std::cout << "│    ⚠️  Verificar adjacência: O(grau do nó)              │" << std::endl;
    std::cout << "│                                                         │" << std::endl;
    std::cout << "│  MATRIZ DE ADJACÊNCIAS (Convertida):                   │" << std::endl;
    std::cout << "│    ⚠️  Usa mais espaço: O(V²)                           │" << std::endl;
    std::cout << "│    ✅ Verificar adjacência: O(1)                        │" << std::endl;
    std::cout << "│    ✅ Melhor para grafos densos                         │" << std::endl;
    std::cout << "│                                                         │" << std::endl;
    std::cout << "│  Para este grafo:                                      │" << std::endl;
    std::cout << "│    • Lista: " << std::setw(2) << (grafo.getNodeCount() + 7*2) 
              << " elementos (5 nós + 14 conexões)      │" << std::endl;
    std::cout << "│    • Matriz: " << (matriz.getSize() * matriz.getSize()) 
              << " elementos (5x5)                      │" << std::endl;
    std::cout << "│                                                         │" << std::endl;
    std::cout << "└─────────────────────────────────────────────────────────┘" << std::endl;
    
    // ========== Finalização ==========
    std::cout << "\n\n" << std::string(60, '=') << std::endl;
    std::cout << "✅ CONVERSÃO CONCLUÍDA COM SUCESSO!" << std::endl;
    std::cout << "🎯 Grafo dinâmico convertido para matriz de adjacências!" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    
    return 0;
}

