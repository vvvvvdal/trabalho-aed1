#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "aluno.h"

int main() {
    Serie serie[3]; // primeira série, segunda série e terceira série. ambas com turmas A e B.
    Pilha_historico historico;
    Aluno novo;
    int total_id = 0, opcao = -1, num_serie, id_busca;
    char nome_turma[NOME_TURMA];
    inicializar_sistema(serie, &historico);

    while(1){
        opcao = exibir_menu();

        switch(opcao) {
            case 1: {
                escolher_turma(nome_turma);
                num_serie = nome_turma[0] - '0';  

                novo.id = ++total_id;
                novo.valido = VALIDO;
                
                ler_nome(novo.nome);
                ler_idade(&novo.idade); 
                ler_nota(&novo.nota);

                if(push_lista_turma(serie, nome_turma, novo) == 1) {
                    printf("\nTem vaga na turma %s. Aluno de ID %04d inserido com sucesso.\n\n", nome_turma, total_id);
                } else {
                    nome_turma[1] = 'B';
                    nome_turma[2] = '\0';

                    if(push_lista_turma(serie, nome_turma, novo) == 1) printf("\nA turma %dA esta cheia. Aluno de ID %04d inserido na turma %s.\n\n", num_serie, total_id, nome_turma);
                    else {
                        printf("\nAs turmas %dA e %dB estao cheias. Tentando colocar na fila de espera...\n", num_serie, num_serie);
                        if(push_fila_espera(serie, num_serie, novo) == 1) printf("\nAluno de ID %04d inserido na fila de espera da serie %d.\n\n", total_id, num_serie);
                        else printf("\nErro ao alocar memoria\n\n");
                    }
                } 

                break;
            }
            case 2: {
                escolher_turma(nome_turma);
                print_turma_escolhida(serie, nome_turma);

                break;
            }
            case 3: {
                num_serie = escolher_serie(serie);
                novo.id = ++total_id;
                novo.valido = VALIDO;
                
                ler_nome(novo.nome);
                ler_idade(&novo.idade);
                ler_nota(&novo.nota);

                nome_turma[0] = num_serie + '0';
                nome_turma[1] = 'A';
                nome_turma[2] = '\0';

                if(push_lista_turma(serie, nome_turma, novo) == 1) {
                    printf("\nTem vaga na turma %s. Aluno de ID %04d inserido com sucesso.\n\n", nome_turma, total_id);
                } else {
                    nome_turma[0] = num_serie + '0';
                    nome_turma[1] = 'B';
                    nome_turma[2] = '\0';

                    if(push_lista_turma(serie, nome_turma, novo) == 1) printf("\nA turma %dA esta cheia. Aluno de ID %04d inserido na turma %s.\n\n", num_serie, total_id, nome_turma);
                    else {
                        printf("\nAs turmas %dA e %dB estao cheias. Tentando colocar na fila de espera...\n", num_serie, num_serie);
                        if(push_fila_espera(serie, num_serie, novo) == 1) printf("\nAluno de ID %04d inserido na fila de espera da serie %d.\n\n", total_id, num_serie);
                        else printf("\nErro ao alocar memoria\n\n");
                    }
                }

                break;
            }
            case 4: {
                num_serie = escolher_serie(serie);
                print_fila_espera(serie, num_serie);
                
                break;
            }
            case 5: {
                printf("Digite o ID do aluno para buscar: ");
                scanf("%d", &id_busca);
                limpar_buffer_entrada();

                Aluno buscar = buscar_aluno_series(serie, id_busca);
                if(buscar.valido == INVALIDO) printf("\nAluno não encontrado nas series.\n\n");
                else print_aluno(buscar);

                break;
            }
            case 6: {
                char nome_busca[MAX_NOME];
                printf("Digite o nome do aluno para buscar: ");
                scanf(" %127[^\n]%*c", nome_busca);
                buscar_aluno_nome(serie, nome_busca);

                break;
            }
            case 7: {
                printf("Digite o ID do aluno para remover: ");
                scanf("%d", &id_busca);
                limpar_buffer_entrada();

                Aluno removido = pop_series(serie, id_busca);
                if(removido.valido == INVALIDO) printf("\nAluno nao encontrado nas series.\n\n");
                else {
                    push_pilha_historico(&historico, removido);
                    printf("\n");
                    print_aluno(removido);
                    printf("\nAluno de ID %d movido para o historico de alunos apagados.\n\n", removido.id);
                }

                break;
            }
            case 8: {
                print_pilha_historico(historico);
                break;
            }
            case 0: {
                limpar_tudo(serie, &historico);
                printf("Encerrando programa...\n\n");
                exit(0);
                break;
            }
            default: {
                printf("Opcao nao encontrada. Digite novamente.\n\n");
                limpar_buffer_entrada();
                break;
            }
        }
    }
    return 0;
}