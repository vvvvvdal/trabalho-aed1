#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aluno.h"

void limpar_buffer_entrada() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

// funções de verificar/buscar/ordenar
int verificar_id(Lista_turma turma, int id) {
    for (int i = 0; i < turma.tam_lista; i++) {
        if (turma.alunos[i].id == id) {
            return 1;
        }
    }
    return 0;
}
int verificar_idade(int idade){

}

int verificar_nome(char *nome) {

}

Aluno buscar_aluno_id(Lista_turma turma, int id) {
    Aluno aluno;
    aluno.valido = INVALIDO;
    int i;

    for(i=0;i<turma.tam_lista;i++){
        if(turma.alunos[i].id == id) {
            aluno = turma.alunos[i];
            aluno.valido = VALIDO;
            return aluno;
        }
    }
    
    return aluno;
}

int buscar_aluno_nome(Lista_turma turma, char *nome) {
    Aluno alunos[MAX_ALUNOS];
    int i, qtd = 0;

    for(i=0;i<turma.tam_lista;i++){
        if(strcmp(turma.alunos[i].nome, nome) == 0) {
            alunos[qtd++] = turma.alunos[i];
        }
    }

    if(qtd == 0) return 0;

    if(qtd == 1) {
        printf("foi encontrado um aluno:\n");
        print_aluno(alunos[0]);
    } else {
        printf("foram encontrados %d alunos:\n", qtd);
        for(i=0;i<qtd;i++){
            print_aluno(alunos[i]);
        }
    }

    return 1;
}

void ordenar_turma_alfabetica(Lista_turma *turma) {
    int i, j;
    Aluno aux;

    for (i = 0; i < turma->tam_lista - 1; i++) {
        for (j = 0; j < turma->tam_lista - i - 1; j++) {
            if (strcmp(turma->alunos[j].nome, turma->alunos[j + 1].nome) > 0) {
                aux = turma->alunos[j];
                turma->alunos[j] = turma->alunos[j + 1];
                turma->alunos[j + 1] = aux;
            }
        }
    }
}

// funções de criar/inicializar
void criar_lista_turma(Lista_turma *turma) {
    turma->tam_lista = 0;
}

void criar_fila_espera(Fila_espera *turma_espera) {
    turma_espera->inicio = NULL;
    turma_espera->fim = NULL;
    turma_espera->tam_fila = 0;
}

void criar_pilha_historico(Pilha_historico *turma_historico){
    turma_historico->topo = NULL;
    turma_historico->tam_pilha = 0;
}

Nof *criar_aluno_fila_espera(Fila_espera *turma_espera, Aluno aluno) {
    Nof *nof = (Nof*)malloc(1*sizeof(Nof));

    if(nof == NULL) return NULL;

    nof->aluno = aluno;
    nof->proximo = NULL;

    return nof;
}

void inicializar_sistema(Serie *serie, Pilha_historico *turma_historico) {
    int i;
    strcpy(serie[0].turma_a.nome_turma, "1A");
    strcpy(serie[0].turma_b.nome_turma, "1B");

    strcpy(serie[1].turma_a.nome_turma, "2A");
    strcpy(serie[1].turma_b.nome_turma, "2B");

    strcpy(serie[2].turma_a.nome_turma, "3A");
    strcpy(serie[2].turma_b.nome_turma, "3B");

    criar_pilha_historico(turma_historico);

    for(i=0;i<3;i++){
        criar_fila_espera(&(serie[i].serie_espera));
    }

    for(i=0;i<3;i++){
        criar_lista_turma(&(serie[i].turma_a));
        criar_lista_turma(&(serie[i].turma_b));
    }
}

// lista, fila, pilha: inserir (push) e remover (pop)
int push_lista_turma(Lista_turma *turma, Aluno aluno) {

    if (turma->tam_lista == MAX_ALUNOS) return 0;

    turma->alunos[turma->tam_lista] = aluno;
    turma->tam_lista++;
    ordenar_turma_alfabetica(turma);

    return 1; 
}

Aluno pop_lista_turma(Lista_turma *turma, int id_aluno) { //conferir essa

    Aluno removido;
    removido.valido = INVALIDO;

    if (turma->tam_lista == 0) return removido;

    for (int i = 0; i < turma->tam_lista; i++) {

        if (turma->alunos[i].id == id_aluno) {

            removido = turma->alunos[i];

            for (int j = i; j < turma->tam_lista - 1; j++) turma->alunos[j] = turma->alunos[j + 1];

            turma->tam_lista--;

            return removido;
        }
    }

    return removido;
}

int push_fila_espera(Fila_espera *turma_espera, Aluno aluno) {
    Nof *nof = criar_aluno_fila_espera(turma_espera, aluno);

    if(nof == NULL) return 0;

    if(turma_espera->inicio == NULL) {
        turma_espera->inicio = nof;
        turma_espera->fim = nof;
    } else {
        turma_espera->fim->proximo = nof;
        turma_espera->fim = nof;
    }

    turma_espera->tam_fila++;

    return 1;
}

Aluno pop_fila_espera(Fila_espera *turma_espera) {
    Aluno res;
    Nof *aux;
    if(turma_espera->tam_fila == 0) {
        res.valido = INVALIDO;
        return res;
    }

    aux = turma_espera->inicio;
    turma_espera->inicio = aux->proximo;
    res = aux->aluno;

    turma_espera->tam_fila--;
    free(aux);

    return res;
}

int push_pilha_historico(Pilha_historico *turma_historico, Aluno aluno) {

    Nop *novo = (Nop*) malloc(sizeof(Nop));

    if (novo == NULL) return 0;

    novo->aluno = aluno;
    novo->proximo = turma_historico->topo;
    turma_historico->topo = novo;

    turma_historico->tam_pilha++;

    return 1;
}

Aluno pop_pilha_historico(Pilha_historico *turma_historico) {
    Aluno pop_aluno;

    if(turma_historico->topo == NULL) {
        pop_aluno.valido = INVALIDO;

        return pop_aluno;
    }

    Nop *pop_historico = turma_historico->topo;
    pop_aluno = pop_historico->aluno;

    turma_historico->topo = turma_historico->topo->proximo;

    free(pop_historico);

    return pop_aluno;
}

// recuperar o ultimo aluno que foi apagado
int recuperar_historico_aluno(Lista_turma *turma, Pilha_historico *historico) { //conferir

    if (historico->tam_pilha == 0) return 0;
    if (turma->tam_lista == MAX_ALUNOS) return 2;

    Aluno aluno = pop_pilha_historico(historico);

    turma->alunos[turma->tam_lista] = aluno;
    turma->tam_lista++;

    return 1;
}

// colocar o primeiro aluno da fila de espera para dentro da turma
int sair_espera_aluno(Lista_turma *turma, Fila_espera *espera) { //conferir
    if (espera->tam_fila == 0) return 0;
    if (turma->tam_lista == MAX_ALUNOS) return 2;

    Aluno aluno = pop_fila_espera(espera);

    turma->alunos[turma->tam_lista] = aluno;
    turma->tam_lista++;

    return 1; 
}

// funções de imprimir
void print_aluno(Aluno aluno) {
    printf("nome: %s\n", aluno.nome);
    printf("matricula: %d\n", aluno.id);
    printf("idade: %d\n", aluno.idade);
    printf("nota: %.2lf\n", aluno.nota);
}

void print_lista_turma(Lista_turma turma) {
    printf("\n=====| LISTA DA TURMA %s |=====\n", turma.nome_turma);

    if (turma.tam_lista == 0) {
        printf("A turma está vazia.\n");
        return;
    }

    printf("\nTotal de alunos na turma: %d\n", turma.tam_lista);

    for (int i = 0; i < turma.tam_lista; i++) {
        printf("\nAluno %d:\n", i + 1);
        print_aluno(turma.alunos[i]);
    }

}

void print_fila_espera(Fila_espera turma_espera) {
    printf("\n=====| FILA DE ESPERA |=====\n");

    if (turma_espera.tam_fila == 0) {
        printf("Fila de espera vazia.\n");
        return;
    }

    Nof *aux = turma_espera.inicio;
    int pos = 1;

    printf("\nTotal de alunos na fila: %d\n", turma_espera.tam_fila);
    while (aux != NULL) {
        printf("\nAluno na posição %d da fila:\n", pos);
        print_aluno(aux->aluno);

        aux = aux->proximo;
        pos++;
    }

}

void print_pilha_historico(Pilha_historico turma_historico) {

    //tbm n tem que ordenar
    printf("\n=====| HISTÓRICO DE ALUNOS |=====\n");

    if (turma_historico.tam_pilha == 0) {
        printf("Histórico vazio.\n");
        return;
    }

    Nop *aux = turma_historico.topo;
    int pos = 1;

    printf("\nTotal de alunos no histórico: %d\n", turma_historico.tam_pilha);
    while (aux != NULL) {
        printf("\nAluno no topo %d:\n", pos);
        print_aluno(aux->aluno);

        aux = aux->proximo;
        pos++;
    }

}
