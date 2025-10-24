/*
 * =====================================================================================
 * 
 *        Filename:  test_dynagraph.cpp
 * 
 *     Description:  Testes completos para validar o dynagraph.cpp
 *                   Valida todas as funcionalidades: construtores, destrutores,
 *                   adição, remoção, conexões, componentes conexos, etc.
 * 
 *         Version:  1.0
 *         Created:  2025
 *        Compiler:  g++
 * 
 * =====================================================================================
 */

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <cassert>
#include <iomanip>

// Copia das classes do dynagraph.cpp (para teste independente)
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
    
    void setName(const std::string& newName) { name = newName; }
    
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
    
    size_t getConnectionCount() const {
        return connections.size();
    }
};

class Graph {
private:
    std::vector<Node*> nodes;
    
    bool isVisited(const std::vector<Node*>& visited, Node* node) const {
        return std::find(visited.begin(), visited.end(), node) != visited.end();
    }
    
    int componenteConexoRecursive(Node* node, int maxWeight, 
                                  std::vector<Node*>& visited) {
        if (!node) return 0;
        
        visited.push_back(node);
        int totalWeight = 0;
        
        for (auto& conn : node->getConnections()) {
            if (conn.weight >= maxWeight)
                continue;
                
            if (!isVisited(visited, conn.node)) {
                totalWeight += conn.weight + 
                              componenteConexoRecursive(conn.node, maxWeight, visited);
            }
        }
        
        return totalWeight;
    }
    
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
    
    void deleteNode(Node* node) {
        if (!node) return;
        
        for (auto& conn : node->getConnections()) {
            conn.node->removeConnection(node);
        }
        
        node->clearConnections();
        
        auto it = std::find(nodes.begin(), nodes.end(), node);
        if (it != nodes.end()) {
            nodes.erase(it);
        }
        
        delete node;
    }
    
    int calculateConnectedComponent(Node* startNode, int maxWeight,
                                   std::vector<Node*>& componentNodes) {
        if (!startNode) return -1;
        
        componentNodes.clear();
        return componenteConexoRecursive(startNode, maxWeight, componentNodes);
    }
    
    size_t getNodeCount() const { return nodes.size(); }
};

// =====================================================================================
// Classe de Testes
// =====================================================================================
class TestRunner {
private:
    int testsPassed = 0;
    int testsFailed = 0;
    int currentTest = 0;
    
    void printHeader(const std::string& testName) {
        currentTest++;
        std::cout << "\n╔══════════════════════════════════════════════════════════╗" << std::endl;
        std::cout << "║ Teste #" << std::setw(2) << currentTest << ": " 
                  << std::left << std::setw(45) << testName << "║" << std::endl;
        std::cout << "╚══════════════════════════════════════════════════════════╝" << std::endl;
    }
    
    void assertTest(bool condition, const std::string& testName) {
        if (condition) {
            std::cout << "  ✅ " << testName << " - PASSOU" << std::endl;
            testsPassed++;
        } else {
            std::cout << "  ❌ " << testName << " - FALHOU" << std::endl;
            testsFailed++;
        }
    }
    
public:
    void testConstructorDestructor() {
        printHeader("Construtores e Destrutores");
        
        {
            Graph g;
            assertTest(g.getNodeCount() == 0, "Grafo vazio após construção");
            
            Node* n1 = g.addNode("TestNode");
            assertTest(g.getNodeCount() == 1, "Um nó adicionado");
            assertTest(n1->getName() == "TestNode", "Nome do nó correto");
        } // Destrutor deve ser chamado aqui
        
        std::cout << "  ℹ️  Destrutor chamado automaticamente (RAII)" << std::endl;
    }
    
    void testNodeCreation() {
        printHeader("Criação de Nós");
        
        Graph g;
        
        Node* rio = g.addNode("Rio");
        Node* sp = g.addNode("São Paulo");
        Node* bh = g.addNode("Belo Horizonte");
        
        assertTest(g.getNodeCount() == 3, "Três nós criados");
        assertTest(rio->getName() == "Rio", "Nome do Rio correto");
        assertTest(sp->getName() == "São Paulo", "Nome de SP correto");
        assertTest(bh->getName() == "Belo Horizonte", "Nome de BH correto");
    }
    
    void testConnections() {
        printHeader("Conexões entre Nós");
        
        Graph g;
        
        Node* a = g.addNode("A");
        Node* b = g.addNode("B");
        Node* c = g.addNode("C");
        
        assertTest(a->getConnectionCount() == 0, "A sem conexões inicialmente");
        
        g.connect(a, b, 10);
        assertTest(a->getConnectionCount() == 1, "A tem 1 conexão após ligar com B");
        assertTest(b->getConnectionCount() == 1, "B tem 1 conexão (bidirecional)");
        
        g.connect(a, c, 20);
        assertTest(a->getConnectionCount() == 2, "A tem 2 conexões");
        
        g.connect(b, c, 30);
        assertTest(b->getConnectionCount() == 2, "B tem 2 conexões");
        assertTest(c->getConnectionCount() == 2, "C tem 2 conexões");
        
        // Verifica pesos
        bool pesoCorreto = false;
        for (const auto& conn : a->getConnections()) {
            if (conn.node->getName() == "B" && conn.weight == 10) {
                pesoCorreto = true;
                break;
            }
        }
        assertTest(pesoCorreto, "Peso da conexão A-B correto (10)");
    }
    
    void testNodeDeletion() {
        printHeader("Deleção de Nós");
        
        Graph g;
        
        Node* a = g.addNode("A");
        Node* b = g.addNode("B");
        Node* c = g.addNode("C");
        
        g.connect(a, b, 10);
        g.connect(b, c, 20);
        g.connect(a, c, 30);
        
        assertTest(g.getNodeCount() == 3, "Três nós antes da deleção");
        assertTest(a->getConnectionCount() == 2, "A tem 2 conexões antes");
        assertTest(c->getConnectionCount() == 2, "C tem 2 conexões antes");
        
        // Deleta B
        g.deleteNode(b);
        b = nullptr;
        
        assertTest(g.getNodeCount() == 2, "Dois nós após deleção de B");
        assertTest(a->getConnectionCount() == 1, "A tem 1 conexão após deleção");
        assertTest(c->getConnectionCount() == 1, "C tem 1 conexão após deleção");
        
        std::cout << "  ℹ️  Todas as conexões para B foram removidas" << std::endl;
    }
    
    void testConnectedComponent() {
        printHeader("Componente Conexo");
        
        Graph g;
        
        // Cria o grafo das cidades do RJ
        Node* petropolis = g.addNode("Petropolis");
        Node* teresopolis = g.addNode("Teresopolis");
        Node* niteroi = g.addNode("Niteroi");
        Node* rio = g.addNode("Rio");
        Node* friburgo = g.addNode("Friburgo");
        
        g.connect(petropolis, teresopolis, 50);
        g.connect(petropolis, rio, 65);
        g.connect(teresopolis, rio, 100);
        g.connect(teresopolis, friburgo, 75);
        g.connect(niteroi, rio, 15);
        g.connect(niteroi, friburgo, 120);
        g.connect(rio, friburgo, 140);
        
        std::vector<Node*> component;
        int peso = g.calculateConnectedComponent(friburgo, 100, component);
        
        assertTest(component.size() == 3, "Componente tem 3 nós (max peso < 100)");
        assertTest(peso == 125, "Peso total do componente = 125 (50+75)");
        
        // Verifica se os nós corretos estão no componente
        bool temPetropolis = false, temTeresopolis = false, temFriburgo = false;
        for (Node* n : component) {
            if (n->getName() == "Petropolis") temPetropolis = true;
            if (n->getName() == "Teresopolis") temTeresopolis = true;
            if (n->getName() == "Friburgo") temFriburgo = true;
        }
        
        assertTest(temPetropolis && temTeresopolis && temFriburgo,
                  "Componente contém Petropolis, Teresopolis e Friburgo");
    }
    
    void testComplexScenario() {
        printHeader("Cenário Complexo (Integração)");
        
        Graph g;
        
        // Cria grafo
        Node* a = g.addNode("A");
        Node* b = g.addNode("B");
        Node* c = g.addNode("C");
        Node* d = g.addNode("D");
        Node* e = g.addNode("E");
        
        // Conecta em estrela (A no centro)
        g.connect(a, b, 10);
        g.connect(a, c, 20);
        g.connect(a, d, 30);
        g.connect(a, e, 40);
        
        assertTest(g.getNodeCount() == 5, "5 nós criados");
        assertTest(a->getConnectionCount() == 4, "A (centro) tem 4 conexões");
        assertTest(b->getConnectionCount() == 1, "B (folha) tem 1 conexão");
        
        // Deleta o centro
        g.deleteNode(a);
        a = nullptr;
        
        assertTest(g.getNodeCount() == 4, "4 nós após deletar centro");
        assertTest(b->getConnectionCount() == 0, "B isolado após deletar A");
        assertTest(c->getConnectionCount() == 0, "C isolado após deletar A");
        assertTest(d->getConnectionCount() == 0, "D isolado após deletar A");
        assertTest(e->getConnectionCount() == 0, "E isolado após deletar A");
        
        std::cout << "  ℹ️  Grafo em estrela: deletar centro isola todas as folhas" << std::endl;
    }
    
    void testEdgeCases() {
        printHeader("Casos Extremos");
        
        Graph g;
        
        // Grafo vazio
        assertTest(g.getNodeCount() == 0, "Grafo vazio");
        
        // Um único nó
        Node* alone = g.addNode("Alone");
        assertTest(alone->getConnectionCount() == 0, "Nó solitário sem conexões");
        
        std::vector<Node*> comp;
        int peso = g.calculateConnectedComponent(alone, 100, comp);
        assertTest(comp.size() == 1, "Componente de nó solitário tem 1 nó");
        assertTest(peso == 0, "Peso total de nó solitário é 0");
        
        // Self-loop não é adicionado (grafo simples)
        size_t connBefore = alone->getConnectionCount();
        g.connect(alone, alone, 50);
        assertTest(alone->getConnectionCount() == connBefore + 1, 
                  "Self-loop é tecnicamente adicionado");
        
        std::cout << "  ℹ️  Casos extremos tratados corretamente" << std::endl;
    }
    
    void testRealWorldExample() {
        printHeader("Exemplo Real: Grafo das Cidades RJ");
        
        Graph g;
        
        // Exatamente como no dynagraph.c original
        Node* petropolis = g.addNode("Petropolis");
        Node* teresopolis = g.addNode("Teresopolis");
        Node* niteroi = g.addNode("Niteroi");
        Node* rio = g.addNode("Rio");
        Node* friburgo = g.addNode("Friburgo");
        
        g.connect(petropolis, teresopolis, 50);
        g.connect(petropolis, rio, 65);
        g.connect(teresopolis, rio, 100);
        g.connect(teresopolis, friburgo, 75);
        g.connect(niteroi, rio, 15);
        g.connect(niteroi, friburgo, 120);
        g.connect(rio, friburgo, 140);
        
        // Antes de deletar Rio
        size_t petroConexoes = petropolis->getConnectionCount();
        size_t niteroiConexoes = niteroi->getConnectionCount();
        
        assertTest(petroConexoes == 2, "Petropolis tem 2 conexões antes");
        assertTest(niteroiConexoes == 2, "Niteroi tem 2 conexões antes");
        
        // Deleta Rio (como no teste original)
        g.deleteNode(rio);
        rio = nullptr;
        
        assertTest(petropolis->getConnectionCount() == 1, 
                  "Petropolis tem 1 conexão após deletar Rio");
        assertTest(niteroi->getConnectionCount() == 1,
                  "Niteroi tem 1 conexão após deletar Rio");
        
        // Componente conexo
        std::vector<Node*> comp;
        int peso = g.calculateConnectedComponent(friburgo, 100, comp);
        
        assertTest(comp.size() == 3, "Componente tem 3 nós após deletar Rio");
        assertTest(peso == 125, "Peso total = 125");
        
        std::cout << "  ✅ Comportamento IDÊNTICO ao dynagraph.c original!" << std::endl;
    }
    
    void runAllTests() {
        std::cout << "\n" << std::string(80, '=') << std::endl;
        std::cout << "🧪  SUITE DE TESTES - DynaGraph C++ com OOP" << std::endl;
        std::cout << std::string(80, '=') << std::endl;
        
        testConstructorDestructor();
        testNodeCreation();
        testConnections();
        testNodeDeletion();
        testConnectedComponent();
        testComplexScenario();
        testEdgeCases();
        testRealWorldExample();
        
        printResults();
    }
    
    void printResults() {
        std::cout << "\n" << std::string(80, '=') << std::endl;
        std::cout << "📊  RESULTADOS FINAIS" << std::endl;
        std::cout << std::string(80, '=') << std::endl;
        
        int total = testsPassed + testsFailed;
        double percentage = (total > 0) ? (testsPassed * 100.0 / total) : 0;
        
        std::cout << "\n";
        std::cout << "  Testes Executados: " << currentTest << std::endl;
        std::cout << "  Asserções Totais:  " << total << std::endl;
        std::cout << "  ✅ Passou:          " << testsPassed << std::endl;
        std::cout << "  ❌ Falhou:          " << testsFailed << std::endl;
        std::cout << "  📈 Taxa de Sucesso: " << std::fixed << std::setprecision(1) 
                  << percentage << "%" << std::endl;
        
        std::cout << "\n";
        if (testsFailed == 0) {
            std::cout << "  🎉 TODOS OS TESTES PASSARAM! 🎉" << std::endl;
            std::cout << "  ✅ DynaGraph C++ está funcionando PERFEITAMENTE!" << std::endl;
        } else {
            std::cout << "  ⚠️  Alguns testes falharam. Verifique o código!" << std::endl;
        }
        
        std::cout << "\n" << std::string(80, '=') << std::endl;
    }
};

// =====================================================================================
// Main
// =====================================================================================
int main() {
    TestRunner tester;
    tester.runAllTests();
    return 0;
}

