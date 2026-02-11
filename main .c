#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "aluno.h"

int main() {
    Serie serie[3]; 
    Pilha_historico historico;
    Aluno aluno_novo, aluno_buscar, aluno_remover;
    int total_id = 0, opcao = -1, num_serie, id_busca;
    char nome_turma[TAM_NOME_TURMA];
    
    const char *NOME_ARQUIVO = "dados_escola.bin";

    inicializar_sistema(serie, &historico);

    //total_id receberá o valor salvo ou continua 0.
    total_id = carregar_sistema(serie, &historico, NOME_ARQUIVO);

    while(1){
        opcao = exibir_menu();

        switch(opcao) {
            case 1: { 
                escolher_turma(nome_turma);
                num_serie = nome_turma[0] - '0';  

                aluno_novo.id = ++total_id; 
                aluno_novo.valido = VALIDO;
                
                ler_nome(aluno_novo.nome); 
                ler_idade(&aluno_novo.idade); 
                ler_nota(&aluno_novo.nota);

                if(push_lista_turma(serie, nome_turma, aluno_novo) == 1) {
                    printf("\nTem vaga na turma %s. Aluno de ID %04d inserido com sucesso.\n\n", nome_turma, total_id);
                } else {
                    char turma_lotada = nome_turma[1];
                    if(nome_turma[1] == 'A') nome_turma[1] = 'B';
                    else nome_turma[1] = 'A';
                    nome_turma[2] = '\0';

                    if(push_lista_turma(serie, nome_turma, aluno_novo) == 1) 
                        printf("\nA turma %d%c esta cheia. Aluno de ID %04d inserido na turma %s.\n\n", num_serie, turma_lotada, total_id, nome_turma);
                    else {
                        printf("\nAs turmas %dA e %dB estao cheias. Tentando colocar na fila de espera...\n", num_serie, num_serie);
                        if(push_fila_espera(serie, num_serie, aluno_novo) == 1) 
                            printf("\nAluno de ID %04d inserido na fila de espera da serie %d.\n\n", total_id, num_serie);
                        else printf("\nErro ao alocar memoria\n\n");
                    }
                }
                break;
            }
            case 2: { 
                escolher_turma(nome_turma);
                print_lista_turma(serie, nome_turma);
                break;
            }
            case 3: { 
                num_serie = escolher_serie(serie);
                aluno_novo.id = ++total_id; 
                aluno_novo.valido = VALIDO;
                
                ler_nome(aluno_novo.nome); 
                ler_idade(&aluno_novo.idade); 
                ler_nota(&aluno_novo.nota);

                if(push_fila_espera(serie, num_serie, aluno_novo) == 1) 
                    printf("\nAluno de ID %04d inserido na fila de espera da serie %d.\n\n", total_id, num_serie);
                else printf("\nErro ao alocar memoria\n\n");
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

                aluno_buscar = buscar_aluno_series_id(serie, id_busca);
                if(aluno_buscar.valido == INVALIDO) printf("\n\nAluno não encontrado nas series.\n\n");
                else print_aluno(aluno_buscar);
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

                aluno_remover = pop_aluno_por_id(serie, id_busca);
                if(aluno_remover.valido == INVALIDO) printf("\nAluno nao encontrado nas series.\n\n");
                else {
                    push_pilha_historico(&historico, aluno_remover);
                    printf("\n");
                    print_aluno(aluno_remover);
                    printf("Aluno de ID %d movido para o historico de alunos apagados.\n\n", aluno_remover.id);
                }
                break;
            }
            case 8: { 
                print_pilha_historico(historico);
                break;
            }
            case 0: { 
                salvar_sistema(serie, &historico, total_id, NOME_ARQUIVO);
                limpar_tudo(serie, &historico);
                printf("Dados salvos. Encerrando programa...\n\n");
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