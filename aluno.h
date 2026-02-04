#ifndef ALUNO_H
#define ALUNO_H

#define MAX_ALUNOS 50
#define MAX_ESPERA 50
#define MAX_HISTORICO 50

#define ID_NULO -1
#define TAM_NULO -1

typedef struct {
    int id;
    int idade;
    char nome[128];
} Aluno; // elemento

typedef struct {
    Aluno alunos[MAX_ALUNOS];
    int tam_lista;
} Lista_turma; // lista estática

typedef struct {
    Aluno alunos[MAX_ESPERA];
    int tam_fila;
    int inicio_fila;
    int fim_fila;
} Fila_espera; // fila estática

typedef struct Aluno_historico {
    Aluno dados;
    struct Aluno_historico *proximo;
} Aluno_historico; // elemento pra pilha dinamica

typedef struct Aluno{
    Aluno_historico *topo;
    int tam_pilha;
} Pilha_historico; // pilha dinamica

void limpar_buffer_entrada();
int verificar_id(int id);
int verificar_idade(int idade);
int verificar_nome(char *nome);
Aluno buscar_aluno_id(Lista_turma turma, int id);
int buscar_aluno_nome(Lista_turma turma, char *nome);

// funções de criar
int criar_lista_turma(Lista_turma *turma);
int criar_fila_espera(Fila_espera *turma_espera);
int criar_pilha_historico(Pilha_historico *turma_historico);

// funções de imprimir
void print_aluno(Aluno aluno);
void print_lista_turma(Lista_turma turma);
void print_fila_espera(Fila_espera turma_espera);
void print_pilha_historico(Pilha_historico turma_historico);

// lista: inserir (push) e remover (pop)
int push_lista_turma(Lista_turma *turma, int id_aluno, int idade_aluno, char *nome_aluno);
Aluno pop_lista_turma(Lista_turma *turma, int id_aluno);

// fila: inserir (push) e remover (pop)
int push_fila_espera(Fila_espera *turma_espera, Aluno aluno);
Aluno pop_fila_espera(Fila_espera *turma_espera);

// pilha: inserir (push) e remover (pop)
int push_pilha_historico(Pilha_historico *turma_historico, Aluno aluno);
Aluno pop_pilha_historico(Pilha_historico *turma_historico);

// recuperar o ultimo aluno que foi apagado
int recuperar_historico_aluno(Lista_turma *turma, Pilha_historico *historico);

// colocar o primeiro aluno da fila de espera para dentro da turma
int sair_espera_aluno(Lista_turma *turma, Fila_espera *espera);

#endif