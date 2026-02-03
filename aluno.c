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
