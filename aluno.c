#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "aluno.h"

// funçoes de salvar/carregar
void salvar_sistema(Serie *serie, Pilha_historico *historico, int total_id, const char *nomeArquivo) {
    int i, j;
    FILE *arquivo = fopen(nomeArquivo, "wb"); 
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar.\n");
        return;
    }

    //n repetir id
    fwrite(&total_id, sizeof(int), 1, arquivo);

    //turmas
    for (i=0;i<3;i++) {
        for (j=0;j<2;j++) {
            fwrite(&serie[i].turmas[j], sizeof(Lista_turma), 1, arquivo);
        }
    }

    //fila de espera
    for (i=0;i<3;i++) {
        //quantos alunos tem na fila
        fwrite(&serie[i].serie_espera.tam_fila, sizeof(int), 1, arquivo);
        
        Nof *aux = serie[i].serie_espera.inicio;
        while (aux != NULL) {
            fwrite(&aux->aluno, sizeof(Aluno), 1, arquivo);
            aux = aux->proximo;
        }
    }

    //historico
    fwrite(&historico->tam_pilha, sizeof(int), 1, arquivo);
    Nop *auxP = historico->topo;
    while (auxP != NULL) {
        fwrite(&auxP->aluno, sizeof(Aluno), 1, arquivo);
        auxP = auxP->proximo;
    }

    fclose(arquivo);
    printf("Dados salvos com sucesso em '%s'.\n\n", nomeArquivo);
}

int carregar_sistema(Serie *serie, Pilha_historico *historico, const char *nomeArquivo) {
    int i, j, k, total_id, tam_espera, tam_historico;

    FILE *arquivo = fopen(nomeArquivo, "rb"); 
    if (arquivo == NULL) {
        printf("Arquivo '%s' nao encontrado. Iniciando novo sistema...\n", nomeArquivo);
        return 0; 
    }

    if (fread(&total_id, sizeof(int), 1, arquivo) != 1) total_id = 0;

    //turmas
    for (i=0;i<3;i++) {
        for (j=0;j<2;j++) fread(&serie[i].turmas[j], sizeof(Lista_turma), 1, arquivo);
    }

    //fila de espera
    for (i=0;i<3;i++) {
        fread(&tam_espera, sizeof(int), 1, arquivo);
        for (k=0;k<tam_espera;k++) {
            Aluno temp;
            fread(&temp, sizeof(Aluno), 1, arquivo);
            push_fila_espera(serie, i + 1, temp);
        }
    }

    //historico
    fread(&tam_historico, sizeof(int), 1, arquivo);
    
    if (tam_historico > 0) {
        Aluno *aluno_aux = (Aluno*)malloc(sizeof(Aluno) * tam_historico);

        for (k=0;k<tam_historico;k++) fread(&aluno_aux[k], sizeof(Aluno), 1, arquivo);
        for (k=tam_historico-1;k>=0;k--) push_pilha_historico(historico, aluno_aux[k]);

        free(aluno_aux);
    }

    fclose(arquivo);
    printf("Dados carregados com sucesso de '%s'.\n", nomeArquivo);
    return total_id;
}

// funções auxiliares
void limpar_buffer_entrada() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

void escolher_turma(char *nome_turma) {
    printf("\nAs turmas sao 1A/B, 2A/B e 3A/B\n");

    while(1) {
        printf("Digite qual turma voce quer (ex: 1B): ");
        scanf(" %4[^\n]%*c", nome_turma);

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

void arrumar_nome(char *nome) {
    nome[0] = toupper(nome[0]);

    for(int i = 1; nome[i] != '\0'; i++){
        if(nome[i-1] == ' ') nome[i] = toupper(nome[i]); 
        else nome[i] = tolower(nome[i]);
    }
}

char *descobrir_nome_turma(char *nome_turma, int i, int j) {
    nome_turma[0] = (i+1) + '0';
    
    if(j == 0) nome_turma[1] = 'A';
    else nome_turma[1] = 'B';

    nome_turma[2] = '\0';

    return nome_turma;
}

Lista_turma *descobrir_turma_por_nome(Serie *serie, char *nome_turma) {
    int num_serie = (nome_turma[0] - '0') - 1;
    int num_turma;

    if(nome_turma[1] == 'A') num_turma = 0;
    else num_turma = 1;

    return &(serie[num_serie].turmas[num_turma]);
}

Fila_espera *descobrir_fila_por_numero(Serie *serie, int num) {
    return &(serie[num - 1].serie_espera);
}

// funções de inicializar/criar
void inicializar_sistema(Serie *serie, Pilha_historico *turma_historico) {
    criar_pilha_historico(turma_historico);

    for(int i=0;i<3;i++){
        for(int j=0;j<2;j++) criar_lista_turma(&(serie[i].turmas[j]));
        criar_fila_espera(&(serie[i].serie_espera));
    }
}

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

// função do menu
int exibir_menu(int opcao) {
    printf("\n*** SISTEMA DE GERENCIAMENTO DE ALUNOS ***\n");
    printf("1. Cadastrar aluno na turma\n");
    printf("2. Ver turma\n");
    printf("3. Cadastrar aluno na fila de espera\n");
    printf("4. Ver fila de Espera\n");
    printf("5. Buscar aluno por ID\n");
    printf("6. Buscar aluno por nome\n");
    printf("7. Remover aluno por ID\n");
    printf("8. Ver historico de alunos removidos\n");
    printf("0. Salvar dados no arquivo e Sair\n");
    printf("Digite sua opcao: ");
    scanf("%d", &opcao);
    limpar_buffer_entrada();
    return opcao;
}

// funções de ler
void ler_nome(char *nome) {
    printf("Nome do aluno: ");
    scanf(" %127[^\n]%*c", nome);

    for (int i=0;nome[i]!='\0';i++) {
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

    if(*idade < 15 || *idade > 23) {
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
        return;
    }
}

// funções de buscar/ordenar
Aluno buscar_aluno_id(Lista_turma turma, int id) {
    Aluno aluno;

    for(int i=0;i<turma.tam_lista;i++){
        if(turma.alunos[i].id == id) {
            aluno = turma.alunos[i];
            aluno.valido = VALIDO;
            return aluno;
        }
    }
    return aluno;
}

Aluno buscar_aluno_series_id(Serie *serie, int id) {
    Aluno aluno;
    aluno.valido = INVALIDO;

    char nome_turma[TAM_NOME_TURMA];

    for(int i=0;i<3;i++) {
        for(int j=0;j<2;j++) {
            aluno = buscar_aluno_id(serie[i].turmas[j], id);
            descobrir_nome_turma(nome_turma, i, j);

            if(aluno.valido == VALIDO) {
                printf("Aluno encontrado na turma %c%c\n\n", nome_turma[0], nome_turma[1]);
                return aluno;
            }
        }
    }
    return aluno;
}

void buscar_aluno_nome(Serie *serie, char *nome_busca) {
    int total_encontrados = 0;
    char nome_turma[TAM_NOME_TURMA], ja_imprimiu;

    arrumar_nome(nome_busca);

    printf("\n*** RESULTADOS DA BUSCA POR: %s ***\n\n", nome_busca);

    for(int i=0;i<3;i++) {
        for(int j=0;j<2;j++) {
            ja_imprimiu = 'z';
            descobrir_nome_turma(nome_turma, i, j);

            for(int k=0;k<serie[i].turmas[j].tam_lista;k++) {
                if(strstr(serie[i].turmas[j].alunos[k].nome, nome_busca) != NULL) {
                    if(ja_imprimiu != nome_turma[0]) printf("Alunos na turma %c%c:\n\n", nome_turma[0], nome_turma[1]);
                    print_aluno(serie[i].turmas[j].alunos[k]);

                    ja_imprimiu = nome_turma[0];
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
    Aluno aux;

    for(int i=0;i<turma->tam_lista-1;i++) {
        for(int j=0;j<turma->tam_lista-i-1;j++) {
            if(strcmp(turma->alunos[j].nome, turma->alunos[j + 1].nome)>0) {
                aux = turma->alunos[j];
                turma->alunos[j] = turma->alunos[j + 1];
                turma->alunos[j + 1] = aux;
            }
        }
    }
}

// lista, fila e pilha: inserir (push) e remover (pop)
int push_lista_turma(Serie *serie, char *nome_turma, Aluno aluno) {
    Lista_turma *turma = descobrir_turma_por_nome(serie, nome_turma);

    if (turma->tam_lista >= MAX_ALUNOS) return 0;

    turma->alunos[turma->tam_lista] = aluno;
    
    turma->tam_lista++;
    turma->nota_total += aluno.nota;
    turma->media = turma->nota_total / turma->tam_lista * 1.0;
    ordenar_turma_alfabetica(turma);

    return 1;
}

Aluno pop_lista_turma(Serie *serie, char *nome_turma, int id_aluno) {
    Lista_turma *turma = descobrir_turma_por_nome(serie, nome_turma);

    Aluno aluno_remover;
    aluno_remover.valido = INVALIDO;

    if (turma->tam_lista == 0) return aluno_remover;

    for (int i = 0; i < turma->tam_lista; i++) {
        if (turma->alunos[i].id == id_aluno) {
            aluno_remover = turma->alunos[i];
            
            turma->nota_total -= aluno_remover.nota;
            turma->tam_lista--;
            
            if (turma->tam_lista > 0)
                turma->media = turma->nota_total / turma->tam_lista;
            else
                turma->media = 0.0;

            for (int j = i; j < turma->tam_lista; j++) turma->alunos[j] = turma->alunos[j + 1];
            
            return aluno_remover;
        }
    }

    return aluno_remover;
}

Aluno pop_aluno_por_id(Serie *serie, int id) {
    Aluno aluno_remover;
    aluno_remover.valido = INVALIDO;
    char nome_turma[TAM_NOME_TURMA];

    for (int i=0;i<3;i++) {
        for (int j=0;j<2;j++) {
            
            descobrir_nome_turma(nome_turma, i, j);

            aluno_remover = pop_lista_turma(serie, nome_turma, id);
            
            if (aluno_remover.valido == VALIDO) {
                if (serie[i].serie_espera.tam_fila > 0) {
                    Aluno aluno_espera = pop_fila_espera(serie, (nome_turma[0]-'0'));
                    
                    if (push_lista_turma(serie, nome_turma, aluno_espera))
                        printf("\nVaga aberta na turma %s. Aluno de ID %d movido da fila de espera para a turma.\n",
                        nome_turma, aluno_espera.id);
                }
                return aluno_remover; 
            }
        }
    }
    
    return aluno_remover;
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

Aluno pop_fila_espera(Serie *serie, int num_turma) {
    Fila_espera *turma_espera = descobrir_fila_por_numero(serie, num_turma);

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
    Nop *aluno_novo = (Nop*) malloc(sizeof(Nop));

    if (aluno_novo == NULL) return 0;

    aluno_novo->aluno = aluno;
    aluno_novo->proximo = turma_historico->topo;
    turma_historico->topo = aluno_novo;

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
    turma_historico->tam_pilha--;

    return pop_aluno;
}

// funções de imprimir
void print_aluno(Aluno aluno) {
    printf("Matricula: %04d\n", aluno.id);
    printf("Nome: %s\n", aluno.nome);
    printf("Idade: %d\n", aluno.idade);
    printf("Nota: %.2lf\n\n", aluno.nota);
}

void print_lista_turma(Serie *serie, char *nome_turma) {
    Lista_turma *turma = descobrir_turma_por_nome(serie, nome_turma);

    printf("\n*** TURMA %s ***\n\n", nome_turma);

    if (turma->tam_lista == 0) {
        printf("A turma %s esta vazia.\n\n", nome_turma);
        return;
    }

    for (int i=0;i<turma->tam_lista;i++) {
        printf("Aluno %d:\n", i + 1);
        print_aluno(turma->alunos[i]);
    }

    printf("Media da turma: %.2lf\n", turma->media);

    if(turma->tam_lista == 1) printf("Total: %d aluno\n\n", turma->tam_lista);
    else printf("Total: %d alunos\n\n", turma->tam_lista);
}

void print_fila_espera(Serie *serie, int num_serie) {
    Fila_espera *fila = descobrir_fila_por_numero(serie, num_serie);

    printf("\n*** FILA DE ESPERA: SERIE %d ***\n\n", num_serie);

    if (fila->tam_fila == 0) {
        printf("Fila de espera vazia.\n\n");
        return;
    }

    Nof *aux = fila->inicio;
    int pos = 1;
    
    while (aux != NULL) {
        printf("Aluno %d:\n", pos);
        print_aluno(aux->aluno);

        aux = aux->proximo;
        pos++;
    }

    char *palavra_alunos = (fila->tam_fila == 1) ? "aluno":"alunos";
    printf("Total: %d %s\n\n", fila->tam_fila, palavra_alunos);
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

    char *palavra_alunos = (turma_historico.tam_pilha == 1) ? "aluno":"alunos";
    printf("Total: %d %s\n\n", turma_historico.tam_pilha, palavra_alunos);
}

// função de limpar memoria
void limpar_tudo(Serie *serie, Pilha_historico *historico) {
    for(int i=0;i<3;i++) while(serie[i].serie_espera.tam_fila > 0) pop_fila_espera(serie, (i+1));

    while(historico->tam_pilha > 0) pop_pilha_historico(historico);

    printf("Memoria limpa com sucesso. Encerrando sistema...\n");
}