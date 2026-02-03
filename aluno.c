#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aluno.h"

void limpar_buffer_entrada() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

Aluno buscar_aluno(Lista_turma turma, int id) {
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

int tam_lista_turma(Lista_turma turma) {
    return turma.tam_lista;
}

int tam_fila_espera(Fila_espera turma_espera) {
    return turma_espera.tam_fila;
}

int tam_pilha_historico(Pilha_historico turma_historico) {
    return turma_historico.tam_pilha;
}

int push_lista_turma(Lista_turma *turma, int id_aluno, int idade_aluno, char *nome_aluno) {
    Aluno aluno;
    aluno.id = id_aluno, aluno.idade = idade_aluno, strcpy(aluno.nome, nome_aluno);

    // (turma->tam_lista == MAX) verificar o tamanho da lista antes de executar o push

    turma->alunos[turma->tam_lista++] = aluno;

    return 1;
}

Aluno pop_lista_turma(Lista_turma *turma, int id_aluno) {
    Aluno aluno;
    int i, achou = 0, pos = 0;

    // (turma->tam_lista == 0) verificar o tamanho da lista antes de executar o pop
    for(i=0;i<turma->tam_lista;i++){
        if(turma->alunos[i].id == id_aluno) {
            aluno = turma->alunos[i];
            achou = 1;
            pos = i;
        }
    }

    if(achou == 1) {
        for(i=pos;i<turma->tam_lista-1;i++){
            turma->alunos[i] = turma->alunos[i+1];
        }
        turma->tam_lista--;
    } else aluno.id = ID_NULO;
    
    return aluno;
}

Aluno pop_pilha_historico(Pilha_historico *turma_historico);

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
