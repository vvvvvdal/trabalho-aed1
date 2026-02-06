#ifndef ALUNO_H
#define ALUNO_H

#define MAX_ALUNOS 50

#define INVALIDO -1
#define VALIDO 1
#define TAM_NULO -1

typedef struct {
    int id;
    int idade;
    int valido;
    double nota;
    char nome[128];
} Aluno; // elemento

typedef struct {
    Aluno alunos[MAX_ALUNOS];
    char nome_turma[3];
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
    Lista_turma turma_a;
    Lista_turma turma_b;
    Fila_espera serie_espera;
} Serie; // duas turmas e uma fila de espera. ex: 1°A, 1°B, e fila de espera para o 1°ano.

void limpar_buffer_entrada(); //feito

// funções de verificar/buscar/ordenar
int verificar_id(Lista_turma turma, int id); // feito. verifica se há mais de um ID identico.
int verificar_idade(int idade);
int verificar_nome(char *nome);
Aluno buscar_aluno_id(Lista_turma turma, int id); //feito
int buscar_aluno_nome(Lista_turma turma, char *nome); //feito
void ordenar_turma_alfabetica(Lista_turma *turma); // feito. ordenar o nome dos alunos alfabeticamente.

// funções de criar/inicializar
void criar_lista_turma(Lista_turma *turma); //feito
void criar_fila_espera(Fila_espera *turma_espera); //feito
void criar_pilha_historico(Pilha_historico *turma_historico); //feito
void inicializar_sistema(Serie *serie, Pilha_historico *turma_historico);

Nof *criar_aluno_fila_espera(Fila_espera *turma_espera, Aluno aluno); //feito

// funções de imprimir
void print_aluno(Aluno aluno); //feito
void print_lista_turma(Lista_turma turma); //feito
void print_fila_espera(Fila_espera turma_espera); //feito
void print_pilha_historico(Pilha_historico turma_historico); //feito

// lista: inserir (push) e remover (pop)
int push_lista_turma(Lista_turma *turma, Aluno aluno); //feito
Aluno pop_lista_turma(Lista_turma *turma, int id_aluno); //feito

// fila: inserir (push) e remover (pop)
int push_fila_espera(Fila_espera *turma_espera, Aluno aluno); //feito
Aluno pop_fila_espera(Fila_espera *turma_espera); //feito

// pilha: inserir (push) e remover (pop)
int push_pilha_historico(Pilha_historico *turma_historico, Aluno aluno); //feito
Aluno pop_pilha_historico(Pilha_historico *turma_historico); //feito

// recuperar o ultimo aluno que foi apagado
int recuperar_historico_aluno(Lista_turma *turma, Pilha_historico *historico); //feito

// colocar o primeiro aluno da fila de espera para dentro da turma
int sair_espera_aluno(Lista_turma *turma, Fila_espera *espera); //feito

#endif