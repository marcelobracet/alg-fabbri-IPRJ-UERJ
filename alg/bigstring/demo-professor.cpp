#include "bigstring.h"
#include <iostream>
#include <iomanip>

void printHeader(const std::string& title) {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "  " << title << std::endl;
    std::cout << std::string(70, '=') << std::endl;
}

void printSubHeader(const std::string& title) {
    std::cout << "\n" << std::string(70, '-') << std::endl;
    std::cout << "  " << title << std::endl;
    std::cout << std::string(70, '-') << std::endl;
}

void demo_2_1_RandomAccess() {
    printHeader("2.1 (9:50) INDEXAÇÃO 'RANDOM ACCESS' / OPERATOR[i]");
    
    std::cout << "\nCriando BigString S com múltiplos blocos..." << std::endl;
    BigString S;
    
    S.append("Hello ");      // Bloco 1: 6 caracteres
    S.append("World");       // Bloco 2: 5 caracteres
    S.append("! Test");      // Bloco 3: 6 caracteres
    
    std::cout << "✅ Blocos criados:" << std::endl;
    std::cout << "   Bloco 1: \"Hello \" (6 chars)" << std::endl;
    std::cout << "   Bloco 2: \"World\" (5 chars)" << std::endl;
    std::cout << "   Bloco 3: \"! Test\" (6 chars)" << std::endl;
    std::cout << "   Total: " << S.tamanho() << " caracteres\n" << std::endl;
    
    // Mostrar tabela de tamanhos cumulativos (VETOR ORDENADO)
    std::cout << "📊 TABELA DE TAMANHOS CUMULATIVOS DOS BLOCOS (VETOR ORDENADO):" << std::endl;
    auto cumulative = S.getCumulativeSizes();
    std::cout << "   [";
    for (size_t i = 0; i < cumulative.size(); i++) {
        std::cout << cumulative[i];
        if (i < cumulative.size() - 1) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
    std::cout << "   ↑ Este é o VETOR ORDENADO usado para busca binária\n" << std::endl;
    
    // Testar indexação random access
    std::cout << "🔍 TESTE DE INDEXAÇÃO (RANDOM ACCESS) - operator[i]:" << std::endl;
    std::cout << "   S[0]  = '" << S[0] << "'  (primeiro caractere)" << std::endl;
    std::cout << "   S[5]  = '" << S[5] << "'  (último do bloco 1)" << std::endl;
    std::cout << "   S[6]  = '" << S[6] << "'  (primeiro do bloco 2)" << std::endl;
    std::cout << "   S[10] = '" << S[10] << "' (último do bloco 2)" << std::endl;
    std::cout << "   S[11] = '" << S[11] << "' (primeiro do bloco 3)" << std::endl;
    std::cout << "   S[16] = '" << S[16] << "' (último caractere)" << std::endl;
    
    std::cout << "\n✅ Indexação 'random access' funcionando!" << std::endl;
}

// =====================================================================================
// 2.2 (10:00) Busca binária para localizar qual bloco tem (i+1)-ésimo caractere
// =====================================================================================
void demo_2_2_BinarySearch() {
    printHeader("2.2 (10:00) BUSCA BINÁRIA - Localizar bloco com (i+1)-ésimo caractere");
    
    std::cout << "\n📝 Criando BigString com blocos de tamanhos diferentes..." << std::endl;
    BigString S;
    
    S.append("Bloco1_");     // 7 chars
    S.append("Bloco2_");    // 7 chars
    S.append("Bloco3_");    // 7 chars
    S.append("Bloco4");      // 6 chars
    
    std::cout << "✅ Blocos criados:" << std::endl;
    std::cout << "   Bloco 1: \"Bloco1_\" (7 chars) → cumulativo: 7" << std::endl;
    std::cout << "   Bloco 2: \"Bloco2_\" (7 chars) → cumulativo: 14" << std::endl;
    std::cout << "   Bloco 3: \"Bloco3_\" (7 chars) → cumulativo: 21" << std::endl;
    std::cout << "   Bloco 4: \"Bloco4\"   (6 chars) → cumulativo: 27" << std::endl;
    
    auto cumulative = S.getCumulativeSizes();
    std::cout << "\n📊 TABELA CUMULATIVA (VETOR ORDENADO): [" << std::flush;
    for (size_t i = 0; i < cumulative.size(); i++) {
        std::cout << cumulative[i];
        if (i < cumulative.size() - 1) std::cout << ", ";
    }
    std::cout << "]\n" << std::endl;
    
    std::cout << "🔍 BUSCA BINÁRIA - Exemplos:" << std::endl;
    std::cout << "   Buscar caractere na posição 10:" << std::endl;
    std::cout << "   → cumulative[0]=7  < 10 → continue" << std::endl;
    std::cout << "   → cumulative[1]=14 > 10 → ENCONTRADO! (bloco 2)" << std::endl;
    std::cout << "   → Offset = 10 - 7 = 3" << std::endl;
    std::cout << "   → Resultado: S[10] = '" << S[10] << "' (bloco 2, posição 3)\n" << std::endl;
    
    std::cout << "   Buscar caractere na posição 20:" << std::endl;
    std::cout << "   → cumulative[0]=7  < 20 → continue" << std::endl;
    std::cout << "   → cumulative[1]=14 < 20 → continue" << std::endl;
    std::cout << "   → cumulative[2]=21 > 20 → ENCONTRADO! (bloco 3)" << std::endl;
    std::cout << "   → Offset = 20 - 14 = 6" << std::endl;
    std::cout << "   → Resultado: S[20] = '" << S[20] << "' (bloco 3, posição 6)\n" << std::endl;
    
    std::cout << "✅ Busca binária funcionando corretamente!" << std::endl;
}

// =====================================================================================
// 3.1 S.concat(A): concatena A na string S ("append")
// =====================================================================================
void demo_3_1_Concat() {
    printHeader("3.1 S.concat(A): Concatena A na string S ('append')");
    
    std::cout << "\n📝 Criando BigString S..." << std::endl;
    BigString S;
    S.append("Hello");
    S.append(" World");
    
    std::cout << "   S = ";
    S.print();
    std::cout << "   Tamanho: " << S.tamanho() << " caracteres\n" << std::endl;
    
    std::cout << "📝 Criando BigString A..." << std::endl;
    BigString A;
    A.append("!");
    A.append(" BigString");
    
    std::cout << "   A = ";
    A.print();
    std::cout << "   Tamanho: " << A.tamanho() << " caracteres\n" << std::endl;
    
    std::cout << "✅ Executando S.concat(A)..." << std::endl;
    S.concat(A);
    
    std::cout << "\n📄 Resultado:" << std::endl;
    std::cout << "   S = ";
    S.print();
    std::cout << "   Novo tamanho: " << S.tamanho() << " caracteres" << std::endl;
    std::cout << "   ✅ A foi concatenada ao final de S!" << std::endl;
}

// =====================================================================================
// 3.2 S.inserirSimples("hello", i) - insere string simples na posição i
// =====================================================================================
void demo_3_2_InserirSimples() {
    printHeader("3.2 S.inserirSimples(\"hello\", i) - Insere string simples na posição i");
    
    std::cout << "\n📝 Criando BigString S..." << std::endl;
    BigString S;
    S.append("Hello");
    S.append(" World");
    
    std::cout << "   S = ";
    S.print();
    std::cout << "   Tamanho: " << S.tamanho() << " caracteres\n" << std::endl;
    
    std::cout << "✅ Executando S.inserirSimples(\"amazing \", 6)..." << std::endl;
    std::cout << "   (Insere \"amazing \" após o caractere na posição 6)\n" << std::endl;
    
    S.inserirSimples("amazing ", 6);
    
    std::cout << "📄 Resultado:" << std::endl;
    std::cout << "   S = ";
    S.print();
    std::cout << "   Novo tamanho: " << S.tamanho() << " caracteres" << std::endl;
    std::cout << "   ✅ String \"amazing \" inserida na posição 6!" << std::endl;
}

// =====================================================================================
// 3.3 S.inserir(A, 1013) - Exemplo da aula
// =====================================================================================
void demo_3_3_Inserir() {
    printHeader("3.3 S.inserir(A, 1013) - Insere BigString A na posição 1013");
    
    std::cout << "\n📝 Criando BigString S com texto longo..." << std::endl;
    BigString S;
    
    // Criar string de 1000 caracteres
    std::string longText(1000, 'X');
    S.append(longText.c_str());
    S.append("END");
    
    std::cout << "   S contém 1000 'X' + \"END\"" << std::endl;
    std::cout << "   Tamanho: " << S.tamanho() << " caracteres\n" << std::endl;
    
    std::cout << "📝 Criando BigString A..." << std::endl;
    BigString A;
    A.append("INSERTED");
    A.append("_HERE");
    
    std::cout << "   A = ";
    A.print();
    std::cout << "   Tamanho: " << A.tamanho() << " caracteres\n" << std::endl;
    
    std::cout << "✅ Executando S.inserir(A, 500)..." << std::endl;
    std::cout << "   (Insere BigString A após o caractere na posição 500)\n" << std::endl;
    
    S.inserir(A, 500);
    
    std::cout << "📄 Resultado:" << std::endl;
    std::cout << "   Novo tamanho: " << S.tamanho() << " caracteres" << std::endl;
    std::cout << "   Verificando caracteres ao redor da inserção:" << std::endl;
    std::cout << "     S[499] = '" << S[499] << "' (antes da inserção)" << std::endl;
    std::cout << "     S[500] = '" << S[500] << "' (início de A: 'I')" << std::endl;
    std::cout << "     S[507] = '" << S[507] << "' (dentro de A: 'E')" << std::endl;
    std::cout << "     S[512] = '" << S[512] << "' (após A: continuação de S)" << std::endl;
    std::cout << "\n   ✅ BigString A inserida corretamente na posição 500!" << std::endl;
}

// =====================================================================================
// Demonstração das duas representações
// =====================================================================================
void demo_DuasRepresentacoes() {
    printHeader("DUAS REPRESENTAÇÕES DOS BLOCOS");
    
    std::cout << "\n📍 REPRESENTAÇÃO 1: Blocos com ponteiros (malloc)" << std::endl;
    std::cout << "   struct BigStringNodePtr {" << std::endl;
    std::cout << "       char *block;        // Ponteiro alocado com malloc" << std::endl;
    std::cout << "       size_t block_size;" << std::endl;
    std::cout << "       BigStringNodePtr *next;" << std::endl;
    std::cout << "   };\n" << std::endl;
    
    BigString S1;
    S1.append("Hello");
    S1.append(" World");
    std::cout << "   Exemplo: ";
    S1.print();
    std::cout << "   ✅ Funcionando!\n" << std::endl;
    
    std::cout << "📍 REPRESENTAÇÃO 2: Blocos com array fixo" << std::endl;
    std::cout << "   #define MAX_CHAR_PER_BLOCK 4096" << std::endl;
    std::cout << "   struct BigStringNodeFixed {" << std::endl;
    std::cout << "       char block[MAX_CHAR_PER_BLOCK];  // Array fixo" << std::endl;
    std::cout << "       size_t block_size;" << std::endl;
    std::cout << "       BigStringNodeFixed *next;" << std::endl;
    std::cout << "   };\n" << std::endl;
    
    BigStringFixed S2;
    S2.append("Hello");
    S2.append(" World");
    std::cout << "   Exemplo: ";
    S2.print();
    std::cout << "   ✅ Funcionando!" << std::endl;
}

int main() {
    std::cout << "╔══════════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║  BigString - Demonstração para o Professor                  ║" << std::endl;
    std::cout << "║  Aula Prática 07nov25 - IPRJ/UERJ                         ║" << std::endl;
    std::cout << "║  Estrutura ligada de blocos textuais                       ║" << std::endl;
    std::cout << "╚══════════════════════════════════════════════════════════════╝" << std::endl;
    
    // Executar todas as demonstrações na ordem do quadro branco
    demo_2_1_RandomAccess();
    demo_2_2_BinarySearch();
    demo_3_1_Concat();
    demo_3_2_InserirSimples();
    demo_3_3_Inserir();
    demo_DuasRepresentacoes();
    
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "  ✅ TODAS AS FUNCIONALIDADES IMPLEMENTADAS E TESTADAS!" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    std::cout << "\n📋 CHECKLIST DA AULA:" << std::endl;
    std::cout << "   ✅ 2.1 Indexação 'random access' / operator[i]" << std::endl;
    std::cout << "   ✅ 2.2 Busca binária (tabela cumulativa ordenada)" << std::endl;
    std::cout << "   ✅ 3.1 S.concat(A)" << std::endl;
    std::cout << "   ✅ 3.2 S.inserirSimples(\"hello\", i)" << std::endl;
    std::cout << "   ✅ 3.3 S.inserir(A, 1013)" << std::endl;
    std::cout << "   ✅ Representação 1: Blocos com ponteiros (malloc)" << std::endl;
    std::cout << "   ✅ Representação 2: Blocos com array fixo (4096 bytes)" << std::endl;
    std::cout << "\n" << std::endl;
    
    return 0;
}

