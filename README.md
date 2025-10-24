# Algoritmos e Estrutura de Dados 2025
## Informações
- Professor [Ricardo Fabbri, Ph.D](http://rfabbri.github.io)
- Datas das avaliações teóricas
    - P1: qua1Out25
    - P2: qua2Dez25

## Criterio de Avaliacao

M = 0.3*P + 0.7*T
P = (P1 + P2)/2
T = nota de trabalhos e tarefas

## Trabalhos

- Semanais
    - Praticos
        - Lista de exercicios em casa
        - Nao entrega lista, mas programa na hora da aula pratica
        - Testes passando -> nota
    - Teoricos
- Trabalho final da disciplina: consistem em trabalhos maiores
- IA sera permitida em alguns trabalhos
- Toda correção terá acompanhamento individual do professor para garantir
  conhecimento

### Enviar para

rfabbri@iprj...

subject tem que conter: [alg-iprj]

### Tarefa 0: questionario e contas, até 17h de 14ago25

A tarefa 0.1) consiste em responder ao questionário (enviado por email).

Solicito outras tarefas:

0.2) criar uma conta github até a mesma data, caso ainda não tenha, 

0.3) assinatura do plano de estudante do Gemni gratuito por 1 ano, que foi eleito para algumas atividades do curso.

Recomendo já instalar o gemni-cli na sua máquina pessoal, que foi o assistente
de programação eleito/justificado em aula.


### Tarefa  1

#### Mini-tarefa: jogo centipede
O jogo centipede esta em scripts/
Pratique o jogo em casa consistentemente.

Voce tera 5min em aula para mostrar que consegue atingir um score de 80

#### Mini-tarefa: vimtutor
Rode vimtutor e faca todas as atividades. Em aula havera perguntas.

#### Tarefa principal

Fazer lista de exercicios e praticar por conta.
Lista de exercicios (explicada em aula)
1) Programar e testar a operacao merge_ordenado de dois vetores ordenados sem IA
    - Entrada: dois vetores ordenados v e w
    - Saída: um vetor ordenado vw contendo os elementos de v e w
2) Programar e testar a operacao básica partition do quicksort: dado um elemento x de um
  vetor v, particionar o vetor v em elementos menores que x, x, seguidos dos
  maiores que x.
    - Entrada: um vetor v, e um índice ix  (de um elemento x tq v[ix] == x)
    - Saída: v  da seguinte forma [ elementos < x | x | elementos > x ]
  Nao utilizar nenhum vetor auxiliar.
3) Repetir para listas encadeadas
- Tipo de dado: int
- IMPORTANTE: Seguir recomendacoes do GEMINI.md sobre boas praticas de código e
  testes. Em especial, usar arrays em C [] e nao STL vector, pois se trata de
  codigo de alta performance.
- Casa tarefa acima devera ter um comando correspondente cuja entrada no stdin
  sao um conjunto de numeros inteiros positivos separados por espaco, e cuja
  saida sera o vetor ordenado no stdout. O nome exato dos executaveis sao
  'merge-ordenado' e 'partition'. 

Na aula prática você tera 30 min para programar um algoritmo similar solicitado
pelo professor.

## Aulas Teoricas

- Exemplos em codigo fonte de videogames
- Apenas os melhores algoritmos e as melhores implementacoes!
    - IA nao consegue (?)
    
## Aulas Praticas
- O objetivo das aulas praticas sera trazer o aluno para um estado de
  proficiencia que tambem se utiliza no ambito profissional, nao apenas o
  minimo suficiente para realizar as tarefas

- Iremos usar o gemni-cli, mas tendo o claude-code como referencia de sistema
  production-grade em diferentes niveis durante o curso
  

    
## Linguagem
C/C++ com CMake
### Revisao de C, ponteiros, etc.
https://youtu.be/Gru0DnXWr0g
https://youtu.be/k0KfKildD-U

## IDE/Ambiente
- VSCode eh padrao atualmente para explorarr codigo como IA, porém não é avançado
- Usaremos o Vim, em especial explorando o Neovim (NVim) (motivacao nos slides).
  A IDE mais respeitada por desenvolvedores de acordo com o Stack Overflow
  Developer Survey 2025.

### IA/LLMs
- Uso de IA será explorado em alguns projetos
- Na primeira aula foi adotado o Gemni e o Gemni-CLI (13ago25)
- Video sobre Gemni-CLI https://www.youtube.com/watch?v=KrnyAJyjVG4
- No entanto, o foco do curso será na qualificação de programação profissional sem IA.


## Livros
- A melhor referencia para cada algoritmo
- Programming Pearls

## Bonus Topcoder
- O aluno que comprovar participação em competições de programação do Topcoder
  (ou outras) poderá ter bonus de nota atribuido pelo professor. As atividades
  devem ser restritas à programação algoritmica em si, e não sobre design de software.

## See also
- Dijkstra On the foolishness of "natural language programming" https://news.ycombinator.com/item?id=43564386 
- [Projeto e Analise de Algoritmos - wiki](http://wiki.nosdigitais.teia.org.br/PAA) (em fase de upgrade)

