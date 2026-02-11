# ✅ Checklist de Desenvolvimento

## 🏗️ Estruturas de Base
- [x] Definição do TAD Aluno (.h)
- [x] Implementação da Lista Estática (Turma)
- [x] Implementação da Fila Dinâmica (Espera)
- [x] Implementação da Pilha Dinâmica (Histórico)

## ⚙️ Funções de Manipulação
- [x] Criar/Inicializar estruturas
- [x] Push/Pop da Fila de Espera
- [x] Push/Pop da Pilha de Histórico
- [x] Inserção/Remoção da Lista da Turma
- [x] Mover aluno da espera para a turma

## 🔍 Consultas e Exibição
- [x] Buscar aluno por ID
- [x] Buscar aluno por Nome
- [x] Imprimir dados de um aluno
- [x] Imprimir lista da turma
- [x] Imprimir fila de espera
- [x] Imprimir histórico (pilha)

## ⏳ Pendências (O que falta fazer)
- [x] **Criação de aluno:** Quando criar um aluno, colocar a validez dele como VALIDA. ex: ```aluno.valido = VALIDO;```. Ordenar a turma sempre que adicionar um aluno novo nela.
- [x] **Menu Principal (main.c):** Interface via terminal para o usuário escolher as opções.
- [x] **Ordenação Alfabética:** Implementar um `Bubble Sort` ou `Quick Sort` na Lista Estática antes de imprimir a turma.
- [ ] **Persistência de Dados :** Salvar e ler os dados em arquivo `.txt` ou `.dat`. Salvar os dados antes de encerrar o programa.
- [x] **Validações:** Usar recursividade nas funções de validação. Idade mínima e máxima (idade mínima de 15 e máxima de 23), impedir números e caractéres especiais no nome, letras e caractéres especiais no ID, letras e caractéres especiais na idade.
- [x] **Cálculo de Médias:** Função para calcular a média global da turma.
- [x] **Mudança na Estrutura da Fila de Espera:** Cada série (conjunto de turmas) vai ter sua fila de espera. Ex: 1º ano, com turmas A e B, vai ter uma fila de espera. O preenchimento será na turma A e depois na turma B.
- [x] **Sistema de ID:** O ID não será digitado pelo usuário mais. O ID será criado sendo a vez que o aluno foi cadastrado na escola. Ex: primeiro aluno -> ID: 00001. décimo segundo aluno -> 00012.