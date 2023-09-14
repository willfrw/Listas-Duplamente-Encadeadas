#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char nome[20];
  float nota;
  int turma;
} Aluno;

typedef struct Nodo Nodo;
struct Nodo {
  Aluno dado;
  Nodo *proximo;
  Nodo *anterior;
};

// Definindo variáveis globais.
Nodo *inicio;
Nodo *fim;
int tamanho;

// Criando prototipos de função
void criaLista();
Nodo *aloca();
void insereInicio();
void insereFim();
void inserePosicao();
void removeDado();
void apagaLista();
void imprimeLista();
void instancia(Aluno *aluno, char *nome, float nota, int turma);
void lineMsg();

int main() {
  lineMsg();
  printf("Lista Duplamente Encadeada");
  lineMsg();

  Aluno aluno;
  
  criaLista();

  int opt = 1;
  char * nome;
  int nota, turma, pos;

  while (opt != 0) {
    printf("Digite a opção desejada:\n[1] - Inserir no inicio da Lista\n[2] - Inserir no fim da Lista\n[3] - Inserir na posição desejada da Lista\n[4] - Mostrar a Lista\n[5] Mostrar a Lista ao contrário\n[6] - Excluir item da lista\n[0] - Encerrar o programa");
    switch (opt) {
      case 1:
        printf("Digite o nome, nota e turma: \n");
        scanf("%c %.2f %d", &nome, &nota, &turma);
        instancia(&aluno, nome, nota, turma);
        insereInicio(aluno);
        break;
      
      case 2:
        printf("Digite o nome, nota e turma: \n");
        scanf("%c %.2f %d", &nome, &nota, &turma);
        instancia(&aluno, nome, nota, turma);
        insereFim(aluno);
        break;
      
      case 3:
        printf("Digite a posição que deseja inserir: ");
        scanf("%d", pos);
        printf("Digite o nome, nota e turma: \n");
        scanf("%c %.2f %d", &nome, &nota, &turma);
        instancia(&aluno, nome, nota, turma);
        inserePosicao(aluno, pos);
        break;

      case 4:
        imprimeLista(0);
        break;
      
      case 5:
        imprimeLista(1);
        break;

      case 6:
        
    }
  
  }

  apagaLista();

  
  lineMsg();
  printf("Fim do programa.\n");
  lineMsg();
  return 0;
}

// Criar 2 elementos nulos na lista.
void criaLista() {
  inicio = NULL;
  fim = NULL;
  tamanho = 0;
}
// Alocar um dado, e como funciona o esquema do lista duplamente encadeada:
Nodo *aloca(Aluno dado) {
  Nodo *novo = (Nodo *)malloc(sizeof(Nodo));
  // inclui os dados na estrutura Aluno
  strcpy(novo->dado.nome, dado.nome);
  novo->dado.turma = dado.turma;
  novo->dado.nota = dado.nota;

  novo->anterior = NULL;
  novo->proximo = NULL;
  return novo;
}

void removeDado(char *nome) {
  Nodo *atual = inicio;
  printf("Removendo %s da lista.\n", nome);
  while (atual != NULL) { // enquanto atual for diferente de NULL o loop roda
    if (strcmp(atual->dado.nome, nome) == 0) {
      if (atual == inicio) {
        inicio = atual->proximo;
        if (inicio != NULL)
          inicio->anterior = NULL;
        else
          fim = NULL;
      } else if (atual == fim) {
        fim = atual->anterior;
        fim->proximo = NULL;
      } else {
        atual->anterior->proximo = atual->proximo;
        atual->proximo->anterior = atual->anterior;
      }
      free(atual);
      tamanho--;
      return;
    }
    atual = atual->proximo;
  }
  
}

void apagaLista() { // percorre a lista e exclui os dados e libera a memória alocada
  Nodo *atual = inicio;
  while (atual != NULL) {
    Nodo *prox = atual->proximo;
    free(atual);
    atual = prox;
  }
  inicio = NULL;
  fim = NULL;
  tamanho = 0;
}


// Inserir no inicio da lista:
void insereInicio(Aluno dado) {
  Nodo *novo = aloca(dado); // criar novo Nodo
  // verificar se o inicio for nulo, se sim, inicio recebe novo e o fim vai ser
  // novo também, pois se os dois são nulos o inico e fim recebe o novo.
  if (inicio == NULL) {
    inicio = novo;
    fim = novo;

    // Se a lista já tiver dado se cria outro Nodo e aponta o ant para o dado 2
    // e prox do dado 2 para o 1.
  } else {
    Nodo *atual; // criar novo Nodo caso tenha dado no inicio da lista.
    atual = inicio;
    novo->proximo = atual;
    atual->anterior = novo;
    inicio = novo;
  }
  printf("Inserindo %s no inicio da lista.\n", dado.nome);
  tamanho++;
}

// Inserir no fim da lista:
void insereFim(Aluno dado) {
  Nodo *novo = aloca(dado); // criar novo Nodo
  // verificar se o inicio for nulo, se sim, inicio recebe novo e o fim vai ser
  // novo também, pois se os dois são nulos o inico e fim recebe o novo.
  if (inicio == NULL) {
    inicio = novo;
    fim = novo;
    // Se a lista já tiver dado se cria outro Nodo e aponta o ant para o dado 2
    // e prox do dado 2 para o 1.
  } else {
    Nodo *atual; // criar novo Nodo caso tenha dado no inicio da lista.
    atual = fim;
    novo->anterior = atual;
    atual->proximo = novo;
    fim = novo;
  }
  printf("Inserindo %s no fim da lista.\n", dado.nome);
  tamanho++;
}

// Inserir no inicio da lista:
void inserePosicao(Aluno dado, int pos) {
  Nodo *novo = aloca(dado); // cria novo nodo
  if (inicio == NULL) {    // se a lista estiver vazia novo o primeiro nodo
    inicio = novo;
    fim = novo;
    tamanho++;
  } else if (pos == 1) {   // se a posição é 1, insere no começo
    insereInicio(dado);
  } else {                 // se não, encontra o nó na posiçãosition pos - 1
    Nodo *atual = inicio;
    int i = 1;
    while (i < pos - 1 && atual->proximo != NULL) {
      atual = atual->proximo;
      i++;
    }
    if (i == pos - 1) {    // se nodo for encontrado insre novo
      novo->anterior = atual;
      novo->proximo = atual->proximo;
      if (atual->proximo == NULL) {  // se atual for o último faz do novo o último
        fim = novo;
      } else {                      // se não atualiaza o nodo anterior
        atual->proximo->anterior = novo;
      }
      atual->proximo = novo;
      tamanho++;
      printf("Inserindo %s na posicao %d da lista.\n", dado.nome, pos);
    } else {                // se não houve nodo insere no final da lista
      insereFim(dado);
    }
  }
}


// Função para imprimir a lista:
void imprimeLista(int sentido) {
  lineMsg();
  if (inicio == NULL && fim == NULL) {
    printf("Lista está vazia.\n");
    lineMsg();
    return;
  }
  if (sentido == 0) { // se parâmetro for 0 imprime a lista normalmente
    Nodo *atual;
    atual = inicio;    
    printf("Imprimindo Lista:\n");
    printf("%-10s %-6s %-5s \n", "Nome", "Nota", "Turma");
    while (atual) {
      printf("%-10s %-6.1f %-4d \n", atual->dado.nome, atual->dado.nota,
             atual->dado.turma);

      atual = atual->proximo;
    }
  } else if (sentido == 1) { // se parâmetro for 1 imprime ao contrário
    Nodo *atual;
    atual = fim;
    printf("Imprimindo Lista ao Contrário:\n");
    printf("%-10s %-6s %-5s \n", "Nome", "Nota", "Turma");
    while (atual) {
      printf("%-10s %-6.1f %-4d \n", atual->dado.nome, atual->dado.nota,
             atual->dado.turma);
      atual = atual->anterior;
    }

  }
  lineMsg();
}

void instancia(Aluno *aluno, char *nome, float nota, int turma) { // serve para instanciar o parâmetro aluno com os dados
  strcpy(aluno->nome, nome);
  aluno->nota = nota;
  aluno->turma = turma;
}

void lineMsg(void) { // imprime uma linha
  printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
}