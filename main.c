#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aluno.h"

int main() {
    Serie serie[3]; // primeira série, segunda série e terceira série. ambas com turmas A e B.
    Pilha_historico historico;
    int total_id = 0;
    inicializar_sistema(serie, &historico);

    return 0;
}