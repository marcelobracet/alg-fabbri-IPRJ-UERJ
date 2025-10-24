/*
 * =====================================================================================
 * 
 *        Filename:  dynagraph.cpp
 * 
 *     Description:  C++ implementation of completely dynamic graph representation
 *                   Using OOP with classes, constructors, and destructors
 * 
 *         Version:  2.0
 *         Created:  2025
 *        Compiler:  g++
 * 
 *          Author:  Based on Ricardo Fabbri's dynagraph.c
 *                   Converted to C++ with OOP
 *         Company:  IPRJ/UERJ
 * 
 * =====================================================================================
 */

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <memory>

// =====================================================================================
// Classe Node - Representa um nó do grafo
// =====================================================================================
class Node {
public:
    // Estrutura para representar uma conexão (aresta)
    struct Connection {
        Node* node;      // Ponteiro para o nó conectado
        int weight;      // Peso da conexão
        
        Connection(Node* n, int w) : node(n), weight(w) {}
    };
    
private:
    std::string name;                    // Nome do nó
    std::list<Connection> connections;   // Lista de conexões (adjacências)
    
public:
    // Construtor
    explicit Node(const std::string& nodeName) : name(nodeName) {
        std::cout << "[Constructor] Nó '" << name << "' criado" << std::endl;
    }
    
    // Destrutor
    ~Node() {
        std::cout << "[Destructor] Nó '" << name << "' destruído" << std::endl;
        // A lista de conexões é automaticamente limpa (RAII)
    }
    
    // Getters
    const std::string& getName() const { return name; }
    const std::list<Connection>& getConnections() const { return connections; }
    std::list<Connection>& getConnections() { return connections; }
    
    // Setter
    void setName(const std::string& newName) { name = newName; }
    
    // Adiciona uma conexão a este nó
    void addConnection(Node* targetNode, int weight) {
        connections.emplace_back(targetNode, weight);
    }
    
    // Remove uma conexão específica para um nó
    void removeConnection(Node* targetNode) {
        connections.remove_if([targetNode](const Connection& conn) {
            return conn.node == targetNode;
        });
    }
    
    // Remove todas as conexões
    void clearConnections() {
        connections.clear();
    }
    
    // Imprime as conexões deste nó
    void printConnections() const {
        std::cout << "Conexões de " << name << ":" << std::endl;
        for (const auto& conn : connections) {
            std::cout << "  -> " << conn.node->getName() 
                      << " (peso " << conn.weight << ")" << std::endl;
        }
    }
};

// =====================================================================================
// Classe Graph - Representa o grafo completo
// =====================================================================================
class Graph {
private:
    std::vector<Node*> nodes;  // Lista de nós do grafo
    
    // Método auxiliar para verificar se um nó já foi visitado
    bool isVisited(const std::vector<Node*>& visited, Node* node) const {
        return std::find(visited.begin(), visited.end(), node) != visited.end();
    }
    
    // Método recursivo para calcular componente conexo
    int componenteConexoRecursive(Node* node, int maxWeight, 
                                  std::vector<Node*>& visited) {
        if (!node) return 0;
        
        visited.push_back(node);
        int totalWeight = 0;
        
        for (auto& conn : node->getConnections()) {
            // Filtro por peso máximo
            if (conn.weight >= maxWeight)
                continue;
                
            // Se o nó ainda não foi visitado
            if (!isVisited(visited, conn.node)) {
                totalWeight += conn.weight + 
                              componenteConexoRecursive(conn.node, maxWeight, visited);
            }
        }
        
        return totalWeight;
    }
    
public:
    // Construtor
    Graph() {
        std::cout << "[Constructor] Grafo criado" << std::endl;
    }
    
    // Destrutor - libera todos os nós
    ~Graph() {
        std::cout << "[Destructor] Grafo sendo destruído..." << std::endl;
        for (Node* node : nodes) {
            delete node;
        }
        nodes.clear();
    }
    
    // Adiciona um nó ao grafo
    Node* addNode(const std::string& name) {
        Node* newNode = new Node(name);
        nodes.push_back(newNode);
        return newNode;
    }
    
    // Liga dois nós (grafo não-direcionado)
    void connect(Node* nodeA, Node* nodeB, int weight) {
        if (!nodeA || !nodeB) {
            std::cerr << "Erro: Tentando conectar nós nulos!" << std::endl;
            return;
        }
        
        nodeA->addConnection(nodeB, weight);
        nodeB->addConnection(nodeA, weight);  // Grafo não-direcionado
    }
    
    // Deleta um nó do grafo (remove todas as conexões)
    void deleteNode(Node* node) {
        if (!node) return;
        
        std::cout << "\n🗑️  Deletando nó: " << node->getName() << std::endl;
        
        // Remove conexões dos vizinhos para este nó
        for (auto& conn : node->getConnections()) {
            conn.node->removeConnection(node);
        }
        
        // Limpa as conexões do próprio nó
        node->clearConnections();
        
        // Remove o nó da lista do grafo
        auto it = std::find(nodes.begin(), nodes.end(), node);
        if (it != nodes.end()) {
            nodes.erase(it);
        }
        
        // Libera a memória do nó
        delete node;
    }
    
    // Calcula o componente conexo a partir de um nó
    int calculateConnectedComponent(Node* startNode, int maxWeight,
                                   std::vector<Node*>& componentNodes) {
        if (!startNode) return -1;
        
        componentNodes.clear();
        return componenteConexoRecursive(startNode, maxWeight, componentNodes);
    }
    
    // Renomeia Friburgo para Nova Friburgo (exemplo específico do exercício)
    // Dado um ponteiro para Petropolis, navega pelas conexões
    void renomearFriburgo(Node* petropolis) {
        if (!petropolis || petropolis->getConnections().empty())
            return;
            
        // Navega: Petropolis -> primeira conexão -> primeira conexão da segunda conexão
        auto& firstConn = petropolis->getConnections().front();
        if (firstConn.node && !firstConn.node->getConnections().empty()) {
            auto it = firstConn.node->getConnections().begin();
            std::advance(it, 1); // Pula para a segunda conexão
            if (it != firstConn.node->getConnections().end() && it->node) {
                it->node->setName("Nova Friburgo");
            }
        }
    }
    
    // Imprime todos os nós do grafo
    void printGraph() const {
        std::cout << "\n📊 Grafo completo:" << std::endl;
        std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;
        for (const Node* node : nodes) {
            node->printConnections();
            std::cout << std::endl;
        }
    }
    
    // Busca um nó pelo nome
    Node* findNode(const std::string& name) const {
        auto it = std::find_if(nodes.begin(), nodes.end(),
            [&name](const Node* node) {
                return node->getName() == name;
            });
        return (it != nodes.end()) ? *it : nullptr;
    }
    
    // Retorna o número de nós
    size_t getNodeCount() const { return nodes.size(); }
};

// =====================================================================================
// Função Main - Testa o grafo
// =====================================================================================
int main() {
    std::cout << "╔════════════════════════════════════════════╗" << std::endl;
    std::cout << "║  DynaGraph C++ - Grafos com OOP           ║" << std::endl;
    std::cout << "║  Versão 2.0 - IPRJ/UERJ                   ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════╝\n" << std::endl;
    
    // Cria o grafo
    Graph grafo;
    
    // Adiciona os nós (cidades do RJ)
    Node* petropolis  = grafo.addNode("Petropolis");
    Node* teresopolis = grafo.addNode("Teresopolis");
    Node* niteroi     = grafo.addNode("Niteroi");
    Node* rio         = grafo.addNode("Rio");
    Node* friburgo    = grafo.addNode("Friburgo");
    
    std::cout << std::endl;
    
    // Conecta os nós (cria as arestas)
    std::cout << "🔗 Criando conexões..." << std::endl;
    grafo.connect(petropolis, teresopolis, 50);
    grafo.connect(petropolis, rio, 65);
    grafo.connect(teresopolis, rio, 100);
    grafo.connect(teresopolis, friburgo, 75);
    grafo.connect(niteroi, rio, 15);
    grafo.connect(niteroi, friburgo, 120);
    grafo.connect(rio, friburgo, 140);
    
    // Mostra o estado antes de deletar
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "📍 ANTES DE DELETAR O NÓ RIO" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    petropolis->printConnections();
    std::cout << std::endl;
    niteroi->printConnections();
    
    // Deleta o nó Rio
    grafo.deleteNode(rio);
    rio = nullptr; // Importante: evita dangling pointer
    
    // Mostra o estado após deletar
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "📍 APÓS DELETAR O NÓ RIO" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    petropolis->printConnections();
    std::cout << std::endl;
    niteroi->printConnections();
    std::cout << std::endl;
    
    // Renomeia Friburgo
    grafo.renomearFriburgo(petropolis);
    
    // Calcula componente conexo
    std::vector<Node*> componenteNos;
    int pesoTotal = grafo.calculateConnectedComponent(friburgo, 100, componenteNos);
    
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "📊 COMPONENTE CONEXO A PARTIR DE FRIBURGO" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    std::cout << "Componente de " << friburgo->getName() 
              << " tem " << componenteNos.size() 
              << " nós e peso total " << pesoTotal << std::endl;
    
    std::cout << "\nNós no componente:" << std::endl;
    for (const Node* node : componenteNos) {
        std::cout << "  • " << node->getName() << std::endl;
    }
    
    // Imprime o grafo completo
    grafo.printGraph();
    
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "✅ Programa finalizado com sucesso!" << std::endl;
    std::cout << "⚙️  Destrutores serão chamados automaticamente...\n" << std::endl;
    
    // O destrutor do Graph será chamado automaticamente
    // e limpará todos os nós restantes (RAII)
    return 0;
}

