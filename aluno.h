#ifndef ALUNO_H
#define ALUNO_H

#define MAX_ALUNOS 2 // normal: 50 alunos por turma. deixando 2 por turma para teste.
#define MAX_NOME 128
#define TAM_NOME_TURMA 5

#define INVALIDO -1
#define VALIDO 1

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
} Serie; // duas turmas (A e B) e uma fila de espera

// salvar dados
void salvar_sistema(Serie *serie, Pilha_historico *historico, int total_id, const char *nomeArquivo);
int carregar_sistema(Serie *serie, Pilha_historico *historico, const char *nomeArquivo);

// funções auxiliares
void limpar_buffer_entrada();
void escolher_turma(char *opcao);
int escolher_serie(Serie *serie);
void arrumar_nome(char *nome);
char *descobrir_nome_turma(char *nome_turma, int i, int j);
Lista_turma *descobrir_turma_por_nome(Serie *serie, char *nome_turma);
Fila_espera *descobrir_fila_por_numero(Serie *serie, int num);

// funções de inicializar/criar
void inicializar_sistema(Serie *serie, Pilha_historico *turma_historico);
void criar_lista_turma(Lista_turma *turma);
void criar_fila_espera(Fila_espera *turma_espera);
void criar_pilha_historico(Pilha_historico *turma_historico);
Nof *criar_aluno_fila_espera(Fila_espera *turma_espera, Aluno aluno);

// função do menu
int exibir_menu(); 

// funções de verificar/comparar
int verificar_id(Lista_turma turma, int id);
int verificar_idade(int idade);

// funções de ler
void ler_nome(char *nome);
void ler_idade(int *idade);
void ler_nota(double *nota);

// funções de buscar/ordenar
Aluno buscar_aluno_id(Lista_turma turma, int id);
Aluno buscar_aluno_series_id(Serie *serie, int id);
void buscar_aluno_nome(Serie *serie, char *nome_busca);
void ordenar_turma_alfabetica(Lista_turma *turma);

// lista, fila e pilha: inserir (push) e remover (pop)
int push_lista_turma(Serie *serie, char *nome_turma, Aluno aluno);
Aluno pop_lista_turma(Serie *serie, char *nome_turma, int id_aluno);
Aluno pop_aluno_por_id(Serie *serie, int id);

int push_fila_espera(Serie *serie, int num_serie, Aluno aluno);
Aluno pop_fila_espera(Serie *serie, int num_turma);

int push_pilha_historico(Pilha_historico *turma_historico, Aluno aluno);
Aluno pop_pilha_historico(Pilha_historico *turma_historico);

// colocar o primeiro aluno da fila de espera para dentro da turma
int sair_espera_aluno(Serie *serie, char *nome_turma);

// funções de imprimir
void print_aluno(Aluno aluno);
void print_lista_turma(Serie *serie, char *nome_turma);
void print_fila_espera(Serie *serie, int num_serie);
void print_pilha_historico(Pilha_historico turma_historico);

// função de limpar memoria
void limpar_tudo(Serie *serie, Pilha_historico *historico);

#endif