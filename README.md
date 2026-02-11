# Sistema de Gerenciamento de Alunos

Sistema desenvolvido em **C** para a disciplina de Algoritmos e Estruturas de Dados 1. O objetivo é gerenciar alunos de uma escola utilizando diferentes estruturas de dados para otimizar o fluxo de matrículas.

## 🛠️ Estruturas Utilizadas

O projeto utiliza todos os conceitos fundamentais de AED1:

1. **Métodos de Ordenação:** Bubble sort para ordenar os alunos na turma em ordem alfabética.
2. **Funções Recursivas:** funções de ler nome/idade/nota dos alunos.
3. **Lista Estática (Turma de alunos):** Com capacidade máxima de 50 alunos.
4. **Fila Dinâmica (Lista de espera):** Gerencia alunos aguardando vaga por ordem de chegada, em cada série (FIFO).
5. **Pilha Dinâmica (Histórico de exclusão):** Armazena alunos removidos.

## 🚀 Funcionalidades

- Cadastro de alunos (ID, Nome, Idade, Média Global).
- Arquivo binario com as informações dos alunos.
- Busca de alunos por ID ou Nome.
- Ordenação dos alunos por ordem alfabética
- Cálculo da média geral da turma (média aritmética da nota de todos os alunos da turma);
- Movimentação automática da fila de espera para a turma ativa.
- Histórico de alunos excluídos.

## 💻 Como Compilar e Executar

```bash
git clone https://github.com/vvvvvdal/trabalho-aed1
gcc *.c -o main
./main
