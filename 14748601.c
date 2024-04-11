/*********************************************************************/
/**   ACH2024 - Algoritmos e Estruturas de Dados II                 **/
/**   EACH-USP - Primeiro Semestre de 2024                          **/
/**   Turma 04 - Prof. Luciano Digiampietri                         **/
/**                                                                 **/
/**   Primeiro Exercicio-Programa                                   **/
/**                                                                 **/
/**   <Otávio Alves Rosa>                   <14748601>              **/
/**                                                                 **/
/*********************************************************************/

// gcc 14748601.c -lm

/*  Este programa fornece funções que calculam 8 métricas de grafos, 
    bem como alguns testes executados na main(), algumas funções de suporte
    já foram fornecidas no código do arquivo "completeERenomeie.c".
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define true 1
#define false 0

typedef int bool;

/* Estrutura para representar nosso grafo usando matriz binaria de adjacencias */
typedef struct {
  int numVertices;
  int numArestas;
  bool** matriz;
} Grafo;


/* Funcao auxiliar para o sistema de correcao automatica (nao mexer) */
void printf123(){
    // Funcao usada pelo sistema de correcao automatica (nao mexer)
}


/* Funcao que inicializa o grafo cujo endereco foi passado como parametro.
   Isto e, cria a matriz de adjacencias (preenchida com false),
   e atribui valor para numVertices (recebendo o valor passado por parametro)
   e numArestas igual a zero.
*/
bool inicializaGrafo(Grafo* g, int vertices){
  if (g==NULL || vertices<1) return false;
  g->numVertices = vertices;
  g->numArestas = 0;
  int x, y;
  g->matriz = (bool**) malloc(sizeof(bool*)*vertices);
  for (x=0; x<vertices; x++){
    g->matriz[x] = (bool*) malloc(sizeof(bool)*vertices);
    for (y=0; y<vertices; y++){
      g->matriz[x][y] = false;
    }
  }
  return true;
}


/* Funcao que libera a memoria da matriz de adjacencia do grafo cujo endereco
   foi passado como parametro.
*/
bool liberaGrafo(Grafo* g){
  if (g==NULL) return false;
  int x;
  for (x=0; x<g->numVertices; x++)
    free(g->matriz[x]);
  free(g->matriz);
  g->numVertices = 0;
  g->numArestas = 0;
  g->matriz = NULL;
  return true;
}

/* Funcao que retorna o numero de vertices do grafo apontado por g, caso o 
   endereco armazenado em g seja diferente de NULL. Caso contrario, retorna -1.
*/
int numeroDeVertices(Grafo* g){
  if (g != NULL) return g->numVertices;
  else return -1;
}


/* Funcao que retorna o numero de arestas do grafo apontado por g, caso o 
   endereco armazenado em g seja diferente de NULL. Caso contrario, retorna -1.
*/
int numeroDeArestas(Grafo* g){
  if (g != NULL) return g->numArestas;
  else return -1;
}


/* Funcao que retorna o grau do vertice v, caso ele exista.
   Caso contrario, retorna -1.
*/
int retornaGrauDoVertice(Grafo* g, int v){
  if (!g || v < 0 || v >= g->numVertices) return -1;
  int x, grau = 0;
  for (x=0;x<g->numVertices;x++){
    if (g->matriz[v][x]) grau++;
  }
  return grau;
}


/* Funcao que retorna true se o vertice v possui um ou mais
   vertices adjacentes (vizinhos).
*/
bool possuiVizinhos(Grafo* g, int v){
  if (!g || v < 0 || v >= g->numVertices) return false;
  int x;
  for (x=0;x<g->numVertices;x++)
    if (g->matriz[v][x]) return true;
  return false;
}


/* Funcao que insere uma nova aresta no grafo.
   Se os vertices passados como parametro forem validos, ha duas possibilidades:
   - a aresta nao existia;
   - a aresta existia. 
*/
bool insereAresta(Grafo* g, int v1, int v2){
  if (!g || v1 < 0 || v2 < 0 || v1 >= g->numVertices || v2 >= g->numVertices || v1 == v2) return false;
  if (g->matriz[v1][v2] == false){
      g->matriz[v1][v2] = true;
      g->matriz[v2][v1] = true;
      g->numArestas++;
  }
  return true;
}


/* Funcao que exclui a aresta entre v1 e v2 (caso exista uma aresta valida
   entre v1 e v2) e retorna true; ou retorna false, caso contrario.
*/
bool removeAresta(Grafo* g, int v1, int v2){
  if (!g || v1 < 0 || v2 < 0 || v1 >= g->numVertices || v2 >= g->numVertices || g->matriz[v1][v2] == false) return false;
  g->matriz[v1][v2] = false;
  g->matriz[v2][v1] = false;
  g->numArestas--;
  return true;
}


/* Funcao que retorna true se existe uma aresta valida entre v1 e v2 
   e false caso contrario.
*/
bool arestaExiste(Grafo* g, int v1, int v2){
  if (!g || v1 < 0 || v2 < 0 || v1 >= g->numVertices || v2 >= g->numVertices || g->matriz[v1][v2] == false) return false;
  return true;
}


/* Funcao que cria um grafo com o numero de vertices e
   numero de arestas passados como parametro e retorna seu endereco.
*/
Grafo* criaGrafoAleatorio(int numVertices, int numArestas){
  printf("################# Criando grafo com %i vertice(s) e com %i aresta(s). #################\n",numVertices, numArestas);
  int x, y, a = 0;
  if (numVertices < 1 || numArestas >= numVertices*(numVertices-1)/2) {
    printf("Parametros invalidos, o grafo nao sera gerado.\n");
    return NULL;  
  }
  Grafo* g = (Grafo*)malloc(sizeof(Grafo));
  inicializaGrafo(g,numVertices);
  while(a<numArestas){
    x = rand()%numVertices;
    y = rand()%numVertices;
    if (x!=y && g->matriz[x][y] == false){
      g->matriz[x][y] = true;
      g->matriz[y][x] = true;
      a++;
    }
  }
  g->numArestas = numArestas;
  return g;
}


/* Funcao desenvolvida para exibir um grafo, no formato de uma matriz
   de adjacencia.
*/
void exibeGrafo(Grafo* g){
  if(!g) return;
  int x, y;
  printf("\nImprimindo grafo (vertices: %i; arestas: %i).\n   ", g->numVertices, g->numArestas);
  for (x=0;x<g->numVertices;x++) printf(" %3i",x);
  printf("\n");
  for (x=0;x<g->numVertices;x++){
    printf("%3i",x);
    for (y=0;y<g->numVertices;y++)
      printf(" %3i",g->matriz[x][y]);  
    printf("\n");
  }
  printf("\n");
}


/* Funcao que exibe os valores de um arranjo de numeros reais */
void exibeArranjoReais(float* arranjo, int n){
  int x;
  for (x=0; x<n; x++) printf("  v%i\t", x);
  printf("\n");
  for (x=0; x<n; x++){
    printf("%3.2f\t",arranjo[x]);
  }
  printf("\n\n");
}


/* Funcao que exibe os valores de um arranjo de numeros inteiros */
void exibeArranjoInteiros(int* arranjo, int n){
  int x;
  for (x=0; x<n; x++) printf(" v%i\t", x);
  printf("\n");
  for (x=0; x<n; x++){
    printf("%3i\t",arranjo[x]);
  }
  printf("\n\n");
}



/* FUNCOES QUE DEVEM SER COMPLETADAS PARA RESOLVER O EP.
   A DESCRICAO DE CADA FUNCAO ESTA NO ENUNCIADO DO EP.
   www.each.usp.br/digiampietri/ACH2024/ep1/ep1.pdf        */

/* Vizinhos em Comum */
/* Função que verifica quantos vizinhos em comum v tem com cada um dos vértices do grafo*/
void vizinhosEmComum(Grafo* g, int v, int* vizinhos){
  int atual, i, vizinhosEmComum;
  for(atual = 0; atual<g->numVertices; atual++) { // loop que percorre todo vértice do grafo "linha" por "linha"
    vizinhosEmComum = 0;
    for(i = 0; i<g->numVertices; i++) { // loop que percorre a "linha" de vizinhos (1) ou não vizinhos (0) do vértice atual
        if (g->matriz[atual][i] && g->matriz[v][i] == 1) { // verifica se o vizinho do vértice atual também é vizinho de v
            vizinhosEmComum++; // soma todos os vizinhos em comum entre o atual e v
        }
    }
    vizinhos[atual] = vizinhosEmComum; // preenche o array fornecido através do parâmetro da função com os respectivos numeros de vizinhos em comum
  }
}



/* Coeficiente de Jaccard */
/* Função que calcula o Coeficiente de Jaccard do vértice v em relação a cada um dos vértices do grafo*/
void coeficienteDeJaccard(Grafo* g, int v, float* coeficientes){
  int atual, i, andCounter, orCounter;
  for(atual = 0; atual<g->numVertices; atual++) { // loop que percorre todo vértice do grafo "linha" por "linha"
    andCounter = 0;
    orCounter = 0;
    for(i = 0; i<g->numVertices; i++) { // loop que percorre a "linha" de vizinhos (1) ou não vizinhos (0) do vértice atual
        if (g->matriz[atual][i] || g->matriz[v][i] == 1) { // verifica se pelo menos um dos vértices (atual ou v) é vizinho de i
          orCounter++;
          if (g->matriz[atual][i] && g->matriz[v][i] == 1) { // verifica se o vértice atual e v são vizinhos de i
            andCounter++;
          }
        }
    }
    if (orCounter == 0) coeficientes[atual] = -1; // cobre o caso em que o denominador (orCounter) é igual a zero
    else coeficientes[atual] = (float) andCounter/orCounter; // preenche o array fornecido através do parâmetro da função com os respectivos coeficientes de cada vértice
  }
}


/* Medida Adamic Adar */
/* Função que calcula a métrica Adamic Adar do vértice v em relação a cada um dos vértices do grafo*/
void AdamicAdar(Grafo* g, int v, float* coeficientes){
  int atual, i, x, vizinhosI;
  for(atual = 0; atual<g->numVertices; atual++) { // loop que percorre todo vértice do grafo "linha" por "linha"
    float somatorio = 0;
    for(i = 0; i<g->numVertices; i++) { // loop que percorre a "linha" de vizinhos (1) ou não vizinhos (0) do vértice atual
      if (g->matriz[atual][i] && g->matriz[v][i] == 1) {  // verifica se i é um vizinho em comum entre o v e o atual
        vizinhosI = 0;
        vizinhosI = retornaGrauDoVertice(g, i); // calcula o número de vizinhos de i
        somatorio = somatorio + 1/logf(vizinhosI); // calcula o valor de um elemento do somatório de Adamic Adar e acumula o valor na variável somatório
      }
    }
    coeficientes[atual] = somatorio; // preenche o array fornecido através do parâmetro da função com os respectivos coeficientes de cada vértice
  }
}


/* Alocacao de Recursos */
/* Função que calcula a medida Alocação de Recursos do vértice v em relação a cada um dos vértices do grafo*/
void alocacaoDeRecursos(Grafo* g, int v, float* coeficientes){
  int atual, i, x, vizinhosI;
  for(atual = 0; atual<g->numVertices; atual++) { // loop que percorre todo vértice do grafo "linha" por "linha"
    float somatorio = 0;
    for(i = 0; i<g->numVertices; i++) { // loop que percorre a "linha" de vizinhos (1) ou não vizinhos (0) do vértice atual
      if (g->matriz[atual][i] && g->matriz[v][i] == 1) { // verifica se i é um vizinho em comum entre o v e o atual
        vizinhosI = 0;
        vizinhosI = retornaGrauDoVertice(g, i); // calcula o número de vizinhos de i
        somatorio = somatorio + (1/(float)vizinhosI); // calcula o valor de um elemento do somatório da fórmula de alocação de Recursos e acumula o valor na variável somatório
      }
    }
    coeficientes[atual] = somatorio; // preenche o array fornecido através do parâmetro da função com os respectivos coeficientes de cada vértice
  }

}


/* Similaridade Cosseno */
/* Função que calcula a Similaridade Cosseno do vértice v em relação a cada um dos vértices do grafo*/
void similaridadeCosseno(Grafo* g, int v, float* coeficientes){
  int atual,grauV,grauAtual;
  int* vizinhosEmComumV = (int*)malloc(g->numVertices*(sizeof(int))); // aloca memória para um array que guardará os vizinhos em comum de v com cada vértice do grafo
  float raiz;
  grauV = retornaGrauDoVertice(g,v); // guarda o número de vizinhos de v
  vizinhosEmComum(g,v,vizinhosEmComumV); // usa a função vizinhosEmComum já programada para preencher o array vizinhosEmComumV com o número de vizinhos de v com cada vértice do grafo
  for(atual = 0; atual<g->numVertices; atual++) { // loop que percorre todo vértice do grafo "linha" por "linha"
    grauAtual = retornaGrauDoVertice(g,atual); // guarda o número de vizinhos do vértice atual
    raiz = sqrt((float)grauV*grauAtual); // guarda o valor do denominador da fórmula "Similaridade Cosseno"
    if (raiz==0) coeficientes[atual] = -1; // cobre o caso em que o denominador (raiz) é igual a zero
    else coeficientes[atual] = ((float)vizinhosEmComumV[atual])/raiz; // preenche o array passado como parâmetro da função com os coeficientes de cada vértice do grafo
  }
  free(vizinhosEmComumV); // libera memória do array "vizinhosEmComumV" anteriormente alocado
}


/* Coeficiente de Dice */
/* Função que calcula o Coeficiente de Dice do vértice v em realção a cada um dos vértices do grafo*/
void coeficienteDeDice(Grafo* g, int v, float* coeficientes){
  int atual,grauV,grauAtual;
  int* vizinhosEmComumV = (int*)malloc(g->numVertices*(sizeof(int))); // aloca memória para um array que guardará os vizinhos em comum de v com cada vértice do grafo
  float soma;
  grauV = retornaGrauDoVertice(g,v); // guarda o número de vizinhos de v
  vizinhosEmComum(g,v,vizinhosEmComumV); // usa a função vizinhosEmComum já programada para preencher o array vizinhosEmComumV com o número de vizinhos de v com cada vértice do grafo
  for(atual = 0; atual<g->numVertices; atual++) { // loop que percorre todo vértice do grafo "linha" por "linha"
    grauAtual = retornaGrauDoVertice(g,atual); // guarda o número de vizinhos do vértice atual
    soma = (float)(grauAtual + grauV); // guarda o valor do denominador da fórmula "Coeficiente de Dice"
    if (soma==0) coeficientes[atual] = -1; // cobre o caso em que o denominador (soma) é igual a zero
    else coeficientes[atual] = ((float)2*vizinhosEmComumV[atual])/soma; // preenche o array passado como parâmetro da função com os coeficientes de cada vértice do grafo
  }
  free(vizinhosEmComumV); // libera memória do array "vizinhosEmComumV" anteriormente alocado
}


/* Função auxiliar que retorna o valor mínimo entre dois inteiros*/
int min(int a, int b) {
  return (a<b) ? a : b;
}



/* Função auxiliar que retorna o valor máximo entre dois inteiros*/
int max(int a, int b) {
  return (a>b) ? a : b;
}


/* Hub Promoted Index */
/* Função que calcula a medida HPI do vértice v em relação a cada um dos vértices do grafo*/
void HPI(Grafo* g, int v, float* coeficientes){
  int atual,grauV,grauAtual;
  int* vizinhosEmComumV = (int*)malloc(g->numVertices*(sizeof(int))); // aloca memória para um array que guardará os vizinhos em comum de v com cada vértice do grafo
  float minimo;
  grauV = retornaGrauDoVertice(g,v); // guarda o número de vizinhos de v
  vizinhosEmComum(g,v,vizinhosEmComumV); // usa a função vizinhosEmComum já programada para preencher o array vizinhosEmComumV com o número de vizinhos de v com cada vértice do grafo
  for(atual = 0; atual<g->numVertices; atual++) { // loop que percorre todo vértice do grafo "linha" por "linha"
    grauAtual = retornaGrauDoVertice(g,atual); // guarda o número de vizinhos do vértice atual
    minimo = (float)min(grauAtual,grauV); // guarda o valor do denominador da fórmula "HPI"
    if (minimo==0) coeficientes[atual] = -1; // cobre o caso em que o denominador (minimo) é igual a zero
    else coeficientes[atual] = ((float)vizinhosEmComumV[atual])/minimo; // preenche o array passado como parâmetro da função com os coeficientes de cada vértice do grafo
  }
  free(vizinhosEmComumV); // libera memória do array "vizinhosEmComumV" anteriormente alocado
}


/* Hub Depressed Index */
/* Função que calcula a medida HDI do vértice v em relação a cada um dos vértices do grafo*/
void HDI(Grafo* g, int v, float* coeficientes){
  int atual,grauV,grauAtual;
  int* vizinhosEmComumV = (int*)malloc(g->numVertices*(sizeof(int))); // aloca memória para um array que guardará os vizinhos em comum de v com cada vértice do grafo
  float maximo;
  grauV = retornaGrauDoVertice(g,v); // guarda o número de vizinhos de v
  vizinhosEmComum(g,v,vizinhosEmComumV); // usa a função vizinhosEmComum já programada para preencher o array vizinhosEmComumV com o número de vizinhos de v com cada vértice do grafo
  for(atual = 0; atual<g->numVertices; atual++) { // loop que percorre todo vértice do grafo "linha" por "linha"
    grauAtual = retornaGrauDoVertice(g,atual);  // guarda o número de vizinhos do vértice atual
    maximo = (float)max(grauAtual,grauV); // guarda o valor do denominador da fórmula "HPI"
    if (maximo==0) coeficientes[atual] = -1; // cobre o caso em que o denominador (maximo) é igual a zero
    else coeficientes[atual] = ((float)vizinhosEmComumV[atual])/maximo; // preenche o array passado como parâmetro da função com os coeficientes de cada vértice do grafo
  }
  free(vizinhosEmComumV); // libera memória do array "vizinhosEmComumV" anteriormente alocado
}


/* Funcao main para testar as funcoes implementadas neste EP.
   Esta parte do codigo nao sera usada na correcao do EP e nao contempla
   todos os testes possiveis.
   Fique a vontade para realizar testes adicionais.
*/
int main() {

  int n = 5;
  int* vComum = (int*)malloc(sizeof(int)*n);
  float* coeficientes = (float*)malloc(sizeof(float)*n);
  
  Grafo g1;

  printf("PRIMEIRO EXEMPLO\n");

  inicializaGrafo(&g1, n);
  insereAresta(&g1,0,1);
  insereAresta(&g1,0,2);
  insereAresta(&g1,1,4);
  insereAresta(&g1,1,3);
  insereAresta(&g1,2,3);

  exibeGrafo(&g1);

  printf("Vizinhos em Comum de v0:\n");
  vizinhosEmComum(&g1, 0, vComum);
  exibeArranjoInteiros(vComum, n);
  printf("Coeficientes de Jaccard de v0:\n");
  coeficienteDeJaccard(&g1, 0, coeficientes);
  exibeArranjoReais(coeficientes, n);


  printf("Medida de Adamic-Adar de v0:\n");
  AdamicAdar(&g1, 0, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Medida de Alocacao de Recursos de v0:\n");
  alocacaoDeRecursos(&g1, 0, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Similaridade Cosseno de v0:\n");
  similaridadeCosseno(&g1, 0, coeficientes);
  exibeArranjoReais(coeficientes, n);

  coeficienteDeDice(&g1, 0, coeficientes);
  printf("Coeficiente de Dice de v0:\n");
  exibeArranjoReais(coeficientes, n);

  HPI(&g1, 0, coeficientes);
  printf("Indice HPI de v0:\n");
  exibeArranjoReais(coeficientes, n);

  HDI(&g1, 0, coeficientes);
  printf("Indice HDI de v0:\n");
  exibeArranjoReais(coeficientes, n);

  printf("\n\nSEGUNDO EXEMPLO\n");

  // Excluindo duas arestas do grafo
  removeAresta(&g1,0,2);
  removeAresta(&g1,2,3);


  exibeGrafo(&g1);

  printf("Vizinhos em Comum de v0:\n");
  vizinhosEmComum(&g1, 0, vComum);
  exibeArranjoInteiros(vComum, n);

  printf("Coeficientes de Jaccard de v0:\n");
  coeficienteDeJaccard(&g1, 0, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Medida de Adamic-Adar de v0:\n");
  AdamicAdar(&g1, 0, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Medida de Alocacao de Recursos de v0:\n");
  alocacaoDeRecursos(&g1, 0, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Similaridade Cosseno de v0:\n");
  similaridadeCosseno(&g1, 0, coeficientes);
  exibeArranjoReais(coeficientes, n);

  coeficienteDeDice(&g1, 0, coeficientes);
  printf("Coeficiente de Dice de v0:\n");
  exibeArranjoReais(coeficientes, n);

  HPI(&g1, 0, coeficientes);
  printf("Indice HPI de v0:\n");
  exibeArranjoReais(coeficientes, n);

  HDI(&g1, 0, coeficientes);
  printf("Indice HDI de v0:\n");
  exibeArranjoReais(coeficientes, n);

  /* Grafo gerado aleatoriamente - pode ficar diferente
    de acordo com o compilador usado.                 */
  printf("\nTERCEIRO EXEMPLO\n");
  n = 6;
  int arestas = 8;
  
  free(vComum);
  free(coeficientes);
  vComum = (int*)malloc(sizeof(int)*n);
  coeficientes = (float*)malloc(sizeof(float)*n);
  
  Grafo* g2 = criaGrafoAleatorio(n,arestas);
  exibeGrafo(g2);
  
  printf("Vizinhos em Comum de v0:\n");
  vizinhosEmComum(g2, 0, vComum);
  exibeArranjoInteiros(vComum, n);

  printf("Vizinhos em Comum de v1:\n");
  vizinhosEmComum(g2, 1, vComum);
  exibeArranjoInteiros(vComum, n);

  printf("Vizinhos em Comum de v5:\n");
  vizinhosEmComum(g2, 5, vComum);
  exibeArranjoInteiros(vComum, n);


  printf("Coeficientes de Jaccard de v0:\n");
  coeficienteDeJaccard(g2, 0, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Coeficientes de Jaccard de v1:\n");
  coeficienteDeJaccard(g2, 1, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Coeficientes de Jaccard de v5:\n");
  coeficienteDeJaccard(g2, 5, coeficientes);
  exibeArranjoReais(coeficientes, n);


  printf("Medida de Adamic-Adar de v0:\n");
  AdamicAdar(g2, 0, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Medida de Adamic-Adar de v1:\n");
  AdamicAdar(g2, 1, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Medida de Adamic-Adar de v5:\n");
  AdamicAdar(g2, 5, coeficientes);
  exibeArranjoReais(coeficientes, n);


  printf("Medida de Alocacao de Recursos de v0:\n");
  alocacaoDeRecursos(g2, 0, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Medida de Alocacao de Recursos de v1:\n");
  alocacaoDeRecursos(g2, 1, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Medida de Alocacao de Recursos de v5:\n");
  alocacaoDeRecursos(g2, 5, coeficientes);
  exibeArranjoReais(coeficientes, n);


  printf("Similaridade Cosseno de v0:\n");
  similaridadeCosseno(g2, 0, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Similaridade Cosseno de v1:\n");
  similaridadeCosseno(g2, 1, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Similaridade Cosseno de v5:\n");
  similaridadeCosseno(g2, 5, coeficientes);
  exibeArranjoReais(coeficientes, n);


  coeficienteDeDice(g2, 0, coeficientes);
  printf("Coeficiente de Dice de v0:\n");
  exibeArranjoReais(coeficientes, n);

  printf("Coeficiente de Dice de v1:\n");
  coeficienteDeDice(g2, 1, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Coeficiente de Dice de v5:\n");
  coeficienteDeDice(g2, 5, coeficientes);
  exibeArranjoReais(coeficientes, n);


  HPI(g2, 0, coeficientes);
  printf("Indice HPI de v0:\n");
  exibeArranjoReais(coeficientes, n);

  printf("Indice HPI de v1:\n");
  HPI(g2, 1, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Indice HPI de v5:\n");
  HPI(g2, 5, coeficientes);
  exibeArranjoReais(coeficientes, n);
  
  
  HDI(g2, 0, coeficientes);
  printf("Indice HDI de v0:\n");
  exibeArranjoReais(coeficientes, n);

  printf("Indice HDI de v1:\n");
  HDI(g2, 1, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Indice HDI de v5:\n");
  HDI(g2, 5, coeficientes);
  exibeArranjoReais(coeficientes, n);
  return 0;  
}