#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aluno.h"

void limpar_buffer_entrada() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

void print_aluno(Aluno aluno) {
    printf("nome: %s\n", aluno.nome);
    printf("matricula: %d\n", aluno.id);
    printf("idade: %d\n", aluno.idade);
}

Aluno buscar_aluno_id(Lista_turma turma, int id) {
    Aluno aluno;
    int i;

    for(i=0;i<turma.tam_lista;i++){
        if(turma.alunos[i].id == id) {
            aluno = turma.alunos[i];
            return aluno;
        }
    }

    aluno.id = ID_NULO;
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

int criar_lista_turma(Lista_turma *turma) {
    turma->tam_lista = 0;
    return 1;
}

int criar_fila_espera(Fila_espera *turma_espera) {
    turma_espera->inicio_fila = 0;
    turma_espera->tam_fila = 0;
    turma_espera->fim_fila = 0;
    return 1;
}

int criar_pilha_historico(Pilha_historico *turma_historico){
    turma_historico->tam_pilha = 0;
    return 1;
}

Aluno pop_pilha_historico(Pilha_historico *turma_historico) {
    Aluno pop_aluno;

    if(turma_historico->topo == NULL) {
        pop_aluno.id = ID_NULO;

        return pop_aluno;
    }

    Aluno_historico *pop_historico = turma_historico->topo;
    pop_aluno = pop_historico->dados;

    turma_historico->topo = turma_historico->topo->proximo;

    free(pop_historico);

    return pop_aluno;
}

int recuperar_historico_aluno(Lista_turma *turma, Pilha_historico *historico) {
    Aluno aluno = pop_pilha_historico(historico);
    turma->alunos[turma->tam_lista++] = aluno;

    // if(historico->tam_pilha == 0) return 0; // historico vazio. deixando de comentário para lembrar de fazer a verificação do tamanho
    //                                                             antes de executar essa função de recuperar

    // if(turma->tam_lista == MAX_ALUNOS) return 2; // turma cheia. deixando de comentário para lembrar de fazer a verificação do tamanho
    //                                                              antes de executar essa função de recuperar


    return 1; // aluno recuperado
}

int sair_espera_aluno(Lista_turma *turma, Fila_espera *espera) {
    Aluno aluno = pop_fila_espera(espera);
    turma->alunos[turma->tam_lista++] = aluno;

        // if(espera->tam_fila == 0) return 0; // lista de espera vazia. deixando de comentário para lembrar de fazer a verificação do tamanho
    //                                                             antes de executar essa função de espera

    // if(turma->tam_lista == MAX_ALUNOS) return 2; // turma cheia. deixando de comentário para lembrar de fazer a verificação do tamanho
    //                                                              antes de executar essa função de espera

    return 1; // aluno enviado para a turma
}
