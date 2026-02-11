#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "aluno.h"

// funções auxiliares
void limpar_buffer_entrada() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

void arrumar_nome(char *nome) {
    nome[0] = toupper(nome[0]);

    for(int i = 1; nome[i] != '\0'; i++){
        if(nome[i-1] == ' ') nome[i] = toupper(nome[i]); 
        else nome[i] = tolower(nome[i]);
    }
}

// função do menu
int exibir_menu(int opcao) {
    printf("\n*** SISTEMA DE GERENCIAMENTO ESCOLAR ***\n");
    printf("1. Cadastrar aluno na turma\n");
    printf("2. Ver turma\n");
    printf("3. Cadastrar aluno na fila de espera\n");
    printf("4. Ver fila de Espera\n");
    printf("5. Buscar aluno por ID\n");
    printf("6. Buscar aluno por nome\n");
    printf("7. Remover aluno por ID\n");
    printf("8. Ver historico de alunos removidos\n");
    printf("0. Sair\n");
    printf("Digite sua opcao: ");
    scanf("%d", &opcao);
    limpar_buffer_entrada();
    return opcao;
}

// funções de ler
void ler_nome(char *nome) {
    int i;
    printf("Nome do aluno: ");

    scanf(" %127[^\n]%*c", nome);

    for (i = 0; nome[i] != '\0'; i++) {
        if (!isalpha(nome[i]) && nome[i] != ' ') {
            printf("Nome com caractere invalido. Digite novamente.\n\n");
            ler_nome(nome);
            return;
        }
    }

    arrumar_nome(nome);
}

void ler_idade(int *idade) {
    printf("Idade (entre 15 e 23 anos): ");
    scanf("%d", idade);
    limpar_buffer_entrada();

    if(verificar_idade(*idade) == 0) {
        printf("Idade invalida. Digite novamente.\n\n");
        ler_idade(idade);
        return;
    }
}

void ler_nota(double *nota) {
    printf("Nota (ex: 8.5): ");
    scanf("%lf", nota);
    limpar_buffer_entrada();

    if(*nota < 0 || *nota > 10) {
        printf("A nota deve ser um valor entre 0 e 10. Digite novamente.\n\n");
        ler_nota(nota);
    }
}

void escolher_turma(char *nome_turma) {
    printf("\nAs turmas sao 1A/B, 2A/B e 3A/B\n");

    while(1) {
        printf("Digite qual turma voce quer (ex: 1B): ");
        scanf(" %9[^\n]%*c", nome_turma);

        nome_turma[1] = toupper(nome_turma[1]);

        int ano_valido = (nome_turma[0] >= '1' && nome_turma[0] <= '3');
        int turma_valida = (nome_turma[1] == 'A' || nome_turma[1] == 'B');

        if (ano_valido && turma_valida) break;
        else printf("Turma inexistente. Digite novamente\n\n");
    }
}

int escolher_serie(Serie *serie){
    int opcao;
    printf("\nAs series sao 1, 2 e 3\n");

    while(1) {
        printf("Digite qual serie voce quer (ex: 2): ");
        scanf("%d", &opcao);
        limpar_buffer_entrada();
        
        int opcao_valida = (opcao == 1 || opcao == 2 || opcao == 3);

        if(opcao_valida) return opcao;
        else printf("\nSerie inexistente. Digite novamente\n\n");
    }

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
    return (15 <= idade && idade <= 23);
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

Aluno buscar_aluno_series(Serie *serie, int id) {
    Aluno aluno;
    char letra_turma;

    for(int i=0;i<3;i++) {
        for(int j=0;j<2;j++) {
            aluno = buscar_aluno_id(serie[i].turmas[j], id);

            if(j==0) letra_turma = 'A';
            else letra_turma = 'B';

            if(aluno.valido == VALIDO) {
                printf("Aluno encontrado na turma %d%c\n\n", i+1, letra_turma);
                return aluno;
            }
        }
    }

    aluno.valido = INVALIDO;
    return aluno;
}

void buscar_aluno_nome(Serie *serie, char *nome_busca) {
    int total_encontrados = 0;
    char letra_turma;
    arrumar_nome(nome_busca);

    printf("\n*** RESULTADOS DA BUSCA POR: %s ***\n\n", nome_busca);

    for(int i=0;i<3;i++) {
        for(int j=0;j<2;j++) {
            if(j==0) letra_turma = 'A';
            else letra_turma = 'B';

            for(int k=0;k<serie[i].turmas[j].tam_lista;k++) {
                if(strstr(serie[i].turmas[j].alunos[k].nome, nome_busca) != NULL) {
                    printf("Alunos na turma %d%c:\n\n", i+1, letra_turma);
                    print_aluno(serie[i].turmas[j].alunos[k]);

                    total_encontrados++;
                }
            }
        }
    }

    if(total_encontrados == 0) printf("Nenhum aluno encontrado com esse nome em nenhuma turma.\n\n");
    else {
        if(total_encontrados == 1) printf("Total: %d aluno\n\n", total_encontrados);
        else printf("Total: %d alunos\n\n", total_encontrados);
    }
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
    turma->nota_total = 0.0;
    turma->media = 0.0;
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
    criar_pilha_historico(turma_historico);

    for(i=0;i<3;i++){
        criar_fila_espera(&(serie[i].serie_espera));
    }

    for(i=0;i<3;i++){
        criar_lista_turma(&(serie[i].turmas[0]));
        criar_lista_turma(&(serie[i].turmas[1]));
    }
}

// lista, fila, pilha: inserir (push) e remover (pop)
int push_lista_turma(Serie *serie, char *nome_turma, Aluno aluno) {
    int id_turma = comparar_nome_turma(serie, nome_turma);
    
    Lista_turma *turma = NULL;

    switch(id_turma) {
        case 0: turma = &(serie[0].turmas[0]); break;
        case 1: turma = &(serie[0].turmas[1]); break;
        case 2: turma = &(serie[1].turmas[0]); break;
        case 3: turma = &(serie[1].turmas[1]); break;
        case 4: turma = &(serie[2].turmas[0]); break;
        case 5: turma = &(serie[2].turmas[1]); break;
    }

    if (turma == NULL) return 0;

    if (turma->tam_lista >= MAX_ALUNOS) {
        return 0;
    }

    turma->alunos[turma->tam_lista] = aluno;
    
    turma->tam_lista++;
    turma->nota_total += aluno.nota;
    turma->media = turma->nota_total / turma->tam_lista;
    ordenar_turma_alfabetica(turma);

    return 1;
}

Aluno pop_lista_turma(Lista_turma *turma, int id_aluno) {
    Aluno removido;
    removido.valido = INVALIDO;

    if (turma->tam_lista == 0) return removido;

    for (int i = 0; i < turma->tam_lista; i++) {
        if (turma->alunos[i].id == id_aluno) {
            removido = turma->alunos[i];
            
            turma->nota_total -= removido.nota;
            turma->tam_lista--;
            
            if (turma->tam_lista > 0)
                turma->media = turma->nota_total / turma->tam_lista;
            else
                turma->media = 0.0;

            for (int j = i; j < turma->tam_lista; j++) turma->alunos[j] = turma->alunos[j + 1];
            
            return removido;
        }
    }

    return removido;
}

Aluno pop_series(Serie *serie, int id) {
    Aluno removido;
    removido.valido = INVALIDO;

    for (int i=0;i<3;i++) {
        
        removido = pop_lista_turma(&serie[i].turmas[0], id);
        if (removido.valido == VALIDO) {
            if(serie[i].serie_espera.tam_fila > 0) {
                Aluno aluno_espera = pop_fila_espera(&serie[i].serie_espera);
                char nome_turma_dest[3];
                
                nome_turma_dest[0] = (i+1) + '0';
                nome_turma_dest[1] = 'A';
                nome_turma_dest[2] = '\0';
                
                if(push_lista_turma(serie, nome_turma_dest, aluno_espera)) {
                    printf("\nVaga aberta na turma %s. Aluno de ID %04d movido da fila de espera.\n", nome_turma_dest, aluno_espera.nome, aluno_espera.id);
                } else {
                    nome_turma_dest[1] = 'B';
                    if(push_lista_turma(serie, nome_turma_dest, aluno_espera)) {
                        printf("\nVaga aberta na turma %s. Aluno de ID %04d movido da fila de espera.\n", nome_turma_dest, aluno_espera.nome, aluno_espera.id);
                    }
                }
            }
            return removido;
        }

        removido = pop_lista_turma(&serie[i].turmas[1], id);
        if (removido.valido == VALIDO) {
            if(serie[i].serie_espera.tam_fila > 0) {
                Aluno aluno_espera = pop_fila_espera(&serie[i].serie_espera);
                char nome_turma_dest[3];
                
                nome_turma_dest[0] = (i+1) + '0';
                nome_turma_dest[1] = 'A';
                nome_turma_dest[2] = '\0';
                
                if(push_lista_turma(serie, nome_turma_dest, aluno_espera)) {
                    printf("\nVaga aberta na turma %s. Aluno %s (ID %d) movido da fila de espera.\n", nome_turma_dest, aluno_espera.nome, aluno_espera.id);
                } else {
                    nome_turma_dest[1] = 'B';
                    if(push_lista_turma(serie, nome_turma_dest, aluno_espera)) {
                        printf("\nVaga aberta na turma %s. Aluno %s (ID %d) movido da fila de espera.\n", nome_turma_dest, aluno_espera.nome, aluno_espera.id);
                    }
                }
             }
            return removido;
        }
    }

    return removido;
}

int push_fila_espera(Serie *serie, int num_serie, Aluno aluno) {
    Fila_espera *fila = &(serie[num_serie-1].serie_espera);
    
    Nof *nof = criar_aluno_fila_espera(fila, aluno);
    if(nof == NULL) return 0;

    if(fila->inicio == NULL) {
        fila->inicio = nof;
        fila->fim = nof;
    } else {
        fila->fim->proximo = nof;
        fila->fim = nof;
    }

    fila->tam_fila++;

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

// colocar o primeiro aluno da fila de espera para dentro da turma
int sair_espera_aluno(Lista_turma *turma, Fila_espera *espera) {
    if (espera->tam_fila == 0) return 0;
    if (turma->tam_lista == MAX_ALUNOS) return 2;

    Aluno aluno = pop_fila_espera(espera);

    turma->alunos[turma->tam_lista] = aluno;
    turma->tam_lista++;

    return 1; 
}

// funções de imprimir
void print_aluno(Aluno aluno) {
    printf("Matricula: %04d\n", aluno.id);
    printf("Nome: %s\n", aluno.nome);
    printf("Idade: %d\n", aluno.idade);
    printf("Nota: %.2lf\n\n", aluno.nota);
}

void print_lista_turma(Lista_turma turma, char *nome_turma) {
    printf("\n*** TURMA %s ***\n\n", nome_turma);

    if (turma.tam_lista == 0) {
        printf("A turma %s esta vazia.\n\n", nome_turma);
        return;
    }

    for (int i = 0; i < turma.tam_lista; i++) {
        printf("Aluno %d:\n", i + 1);
        print_aluno(turma.alunos[i]);
    }

    printf("Media da turma: %.2lf\n", turma.media);

    if(turma.tam_lista == 1) printf("Total: %d aluno\n\n", turma.tam_lista);
    else printf("Total: %d alunos\n\n", turma.tam_lista);
}

int comparar_nome_turma(Serie *serie, char *nome_turma) {
    int ano_num = nome_turma[0] - '0';
    char turma_letra = nome_turma[1];

    if (ano_num >= 1 && ano_num <= 3 && (turma_letra == 'A' || turma_letra == 'B')) {
        return (ano_num - 1) * 2 + (turma_letra == 'B' ? 1 : 0);
    }
    
    return -1;
}

void print_turma_escolhida(Serie *serie, char *nome_turma) {
    comparar_nome_turma(serie, nome_turma);
    if(id_turma == -1) return;

    for(int i=0;i<3;i++){
        for(int j=0;j<2;j++){
            if(serie[i].turmas[j].id == id_turma){
                print_lista_turma(serie[i].turmas[j], nome_turma);
                return;
            }
        }
    }
}

void print_fila_espera(Serie *serie, int num_serie) {
    Fila_espera *f = &(serie[num_serie - 1].serie_espera);

    printf("\n*** FILA DE ESPERA: SERIE %d ***\n\n", num_serie);

    if (f->tam_fila == 0) {
        printf("Fila de espera vazia.\n\n");
        return;
    }

    Nof *aux = f->inicio;
    int pos = 1;
    
    while (aux != NULL) {
        printf("Aluno %d:\n", pos);
        print_aluno(aux->aluno);

        aux = aux->proximo;
        pos++;
    }

    if(f->tam_fila == 1) printf("Total: %d aluno\n\n", f->tam_fila);
    else printf("Total: %d alunos\n\n", f->tam_fila);
}

void print_pilha_historico(Pilha_historico turma_historico) {

    printf("\n*** HISTORICO DE ALUNOS APAGADOS ***\n\n");

    if (turma_historico.tam_pilha == 0) {
        printf("Historico vazio.\n\n");
        return;
    }

    Nop *aux = turma_historico.topo;
    int pos = 1;

    while (aux != NULL) {
        printf("Aluno %d:\n", pos);
        print_aluno(aux->aluno);

        aux = aux->proximo;
        pos++;
    }

    if(turma_historico.tam_pilha == 1) printf("Total: %d aluno\n\n", turma_historico.tam_pilha);
    else printf("Total: %d alunos\n\n", turma_historico.tam_pilha);
}

void limpar_tudo(Serie *serie, Pilha_historico *historico) {
    int i; 

    for(i=0;i<3;i++) {
        while(serie[i].serie_espera.tam_fila > 0) {
            pop_fila_espera(&(serie[i].serie_espera));
        }
    }

    while(historico->tam_pilha > 0) {
        pop_pilha_historico(historico);
    }

    printf("Memoria limpa com sucesso.\n");
}