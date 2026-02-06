# Sistema de Gerenciamento de Turmas (AED 1)

Sistema desenvolvido em **C** para a disciplina de Algoritmos e Estruturas de Dados 1. O objetivo é gerenciar alunos de uma escola utilizando diferentes estruturas de dados para otimizar o fluxo de matrículas.

## 🛠️ Estruturas Utilizadas

O projeto utiliza três conceitos fundamentais de AED:

1. **Lista Estática (Turma Ativa):** Com capacidade máxima de 50 alunos (conforme o limite de vagas físicas).
2. **Fila Dinâmica (Lista de Espera):** Gerencia alunos aguardando vaga por ordem de chegada (FIFO).
3. **Pilha Dinâmica (Histórico de Exclusão):** Armazena alunos removidos, permitindo a recuperação rápida do último excluído (LIFO).

## 🚀 Funcionalidades
- Cadastro de alunos (ID, Nome, Idade, Média Global).
- Busca de alunos por ID ou Nome.
- Movimentação automática da fila de espera para a turma ativa.
- Histórico de exclusão com sistema de "desfazer".

## 💻 Como Compilar e Executar
```bash
gcc main.c aluno.c -o sistema
./sistema
