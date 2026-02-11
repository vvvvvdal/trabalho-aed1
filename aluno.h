#ifndef ALUNO_H
#define ALUNO_H

#define MAX_ALUNOS 2 // normal: 50 alunos por turma. deixando 2 por turma para teste.
#define MAX_NOME 128
#define NOME_TURMA 10

#define INVALIDO -1
#define VALIDO 1
#define TAM_NULO -1

typedef struct {
    int id;
    int idade;
    int valido;
    double nota;
    char nome[MAX_NOME];
} Aluno; // elemento

typedef struct {
    Aluno alunos[MAX_ALUNOS];
    double nota_total;
    double media;
    int tam_lista;
} Lista_turma; // lista estática

typedef struct Nof {
    Aluno aluno;
    struct Nof *proximo;
} Nof; // elemento pra fila dinamica

typedef struct {
    Nof *inicio;
    Nof *fim;
    int tam_fila;
} Fila_espera; // fila dinamica

typedef struct Nop {
    Aluno aluno;
    struct Nop *proximo;
} Nop; // elemento pra pilha dinamica

typedef struct {
    Nop *topo;
    int tam_pilha;
} Pilha_historico; // pilha dinamica

typedef struct {
    Lista_turma turmas[2];
    Fila_espera serie_espera;
} Serie; // duas turmas e uma fila de espera. ex: 1°A, 1°B, e fila de espera para o 1°ano.

// funções auxiliares
void limpar_buffer_entrada(); //feito
void arrumar_nome(char *nome);

// função do menu
int exibir_menu();

void escolher_turma(char *opcao);
int escolher_serie(Serie *serie);

// funções de ler
void ler_nome(char *nome);
void ler_idade(int *idade);
void ler_nota(double *nota);

int verificar_idade(int idade);
Aluno buscar_aluno_id(Lista_turma turma, int id); //feito
Aluno buscar_aluno_series(Serie *serie, int id);
void buscar_aluno_nome(Serie *serie, char *nome_busca); //feito
void ordenar_turma_alfabetica(Lista_turma *turma); // feito. ordenar o nome dos alunos alfabeticamente.
int comparar_nome_turma(Serie *serie, char *nome_turma);

// funções de criar/inicializar
void criar_lista_turma(Lista_turma *turma); //feito
void criar_fila_espera(Fila_espera *turma_espera); //feito
void criar_pilha_historico(Pilha_historico *turma_historico); //feito
void inicializar_sistema(Serie *serie, Pilha_historico *turma_historico);
Nof *criar_aluno_fila_espera(Fila_espera *turma_espera, Aluno aluno); //feito

// tamanho de lista, fila, pilha
int tam_turma(Lista_turma *turma, char *nome_turma);
int tam_espera(Fila_espera *turma_espera, int turma_num);
int tam_historico(Pilha_historico *turma_historico);

// lista, fila, pilha: inserir (push) e remover (pop)
int push_lista_turma(Serie *serie, char *nome_turma, Aluno aluno); //feito
Aluno pop_lista_turma(Lista_turma *turma, int id_aluno); //feito
Aluno pop_series(Serie *serie, int id); //feito
int push_fila_espera(Serie *serie, int num_serie, Aluno aluno);
Aluno pop_fila_espera(Fila_espera *turma_espera); //feito
int push_pilha_historico(Pilha_historico *turma_historico, Aluno aluno); //feito
Aluno pop_pilha_historico(Pilha_historico *turma_historico); //feito

// colocar o primeiro aluno da fila de espera para dentro da turma
int sair_espera_aluno(Lista_turma *turma, Fila_espera *espera); //feito

// função de limpar memoria
void limpar_tudo(Serie *serie, Pilha_historico *historico);

// funções de imprimir
void print_aluno(Aluno aluno); //feito
void print_lista_turma(Lista_turma turma, char *nome_turma); //feito
void print_fila_espera(Serie *serie, int num_serie); //feito
void print_pilha_historico(Pilha_historico turma_historico); //feito
void print_turma_escolhida(Serie *serie, char *nome_turma);

#endif