#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
//Definiçoes de tamanho e limite
#define MAX_COMPONENTES 20
#define TAM_NOME 30
#define TAM_TIPO 20
//Estrutura que representa os componentes da mochila
typedef struct {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int quantidade;
    int prioridade; 
} Componente;

Componente mochila[MAX_COMPONENTES];
int numComponentes = 0; //Conta os componentes da mochila
int comparacoes = 0; //// Conta  as comparações nos algoritmos de ordenação
int trocas = 0;
bool ordenadaPorNome = false; // Flag para informar se esta ordenado ou nao
// Função que aguarda o usuario apertar enter
void pausar() {
    printf("\nPressione Enter para continuar...");
    while (getchar() != '\n'); 
    getchar();
}
// Exibe cabeçalho da tabela de inventário
void exibirTabelaCabecalho() {
    printf("--------------------------------------------------------------\n");
    printf("NOME           | TIPO        | QUANTIDADE | PRIORIDADE\n");
    printf("--------------------------------------------------------------\n");
}

// Exibe um componente formatado na tabela
void exibirComponente(Componente c) {
    printf("%-14s | %-11s | %10d | %10d\n", c.nome, c.tipo, c.quantidade, c.prioridade);
}

// Adiciona o componente
void adicionarComponente() {
    if (numComponentes >= MAX_COMPONENTES) {
        printf("Capacidade maxima atingida!\n");
        pausar();
        return;
    }

    Componente novo;
    printf("\n--- Coletando Novo Componente ---\n");
    printf("Nome: ");
    scanf(" %[^\n]", novo.nome);
    printf("Tipo (Estrutural, Eletronico, Energia): ");
    scanf(" %[^\n]", novo.tipo);
    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    printf("Prioridade de Montagem (1–5): ");
    scanf("%d", &novo.prioridade);

    mochila[numComponentes++] = novo;
    ordenadaPorNome = false;

    printf("\nComponente '%s' adicionado!\n", novo.nome);

    // Mostrar inventário atualizado
    printf("\n--- INVENTARIO ATUAL (%d/%d) ---\n", numComponentes, MAX_COMPONENTES);
    exibirTabelaCabecalho();
    for (int i = 0; i < numComponentes; i++)
        exibirComponente(mochila[i]);
    printf("--------------------------------------------------------------\n");

    pausar();
}

// Função auxiliar para trocar dois componentes
void trocarComponentes(int i, int j) {
    Componente temp = mochila[i];
    mochila[i] = mochila[j];
    mochila[j] = temp;
    trocas++;
}

// Ordena a mochila por NOME usando Bubble Sort
void bubbleSort() {
    comparacoes = 0;
    trocas = 0;

    for (int i = 0; i < numComponentes - 1; i++) {
        for (int j = 0; j < numComponentes - 1 - i; j++) {
            comparacoes++;
            if (strcmp(mochila[j].nome, mochila[j+1].nome) > 0)
                trocarComponentes(j, j+1);
        }
    }

    ordenadaPorNome = true;

    printf("\nMochila organizada por NOME.\n");
    printf("Analise de Desempenho: Foram necessarias %d comparacoes.\n", comparacoes);

    // Mostrar inventário atualizado
    printf("\n--- INVENTARIO ATUAL (%d/%d) ---\n", numComponentes, MAX_COMPONENTES);
    exibirTabelaCabecalho();
    for (int i = 0; i < numComponentes; i++)
        exibirComponente(mochila[i]);
    printf("--------------------------------------------------------------\n");

    pausar();
}

// Ordena a mochila por TIPO usando Insertion Sort
void insertionSort() {
    comparacoes = 0;
    trocas = 0;

    for (int i = 1; i < numComponentes; i++) {
        Componente chave = mochila[i];
        int j = i - 1;
        while (j >= 0) {
            comparacoes++;
            if (strcmp(mochila[j].tipo, chave.tipo) > 0) {
                mochila[j+1] = mochila[j];
                trocas++;
                j--;
            } else break;
        }
        mochila[j+1] = chave;
    }

    printf("\nMochila organizada por TIPO.\n");
    printf("Analise de Desempenho: Foram necessarias %d comparacoes.\n", comparacoes);

    // Mostrar inventário atualizado
    printf("\n--- INVENTARIO ATUAL (%d/%d) ---\n", numComponentes, MAX_COMPONENTES);
    exibirTabelaCabecalho();
    for (int i = 0; i < numComponentes; i++)
        exibirComponente(mochila[i]);
    printf("--------------------------------------------------------------\n");

    pausar();
}

// Ordena a mochila por PRIORIDADE usando Selection Sort
void selectionSort() {
    comparacoes = 0;
    trocas = 0;

    for (int i = 0; i < numComponentes - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < numComponentes; j++) {
            comparacoes++;
            if (mochila[j].prioridade < mochila[min_idx].prioridade)
                min_idx = j;
        }
        if (min_idx != i)
            trocarComponentes(i, min_idx);
    }

    printf("\nMochila organizada por PRIORIDADE.\n");
    printf("Analise de Desempenho: Foram necessarias %d comparacoes.\n", comparacoes);

    // Mostrar inventário atualizado
    printf("\n--- INVENTARIO ATUAL (%d/%d) ---\n", numComponentes, MAX_COMPONENTES);
    exibirTabelaCabecalho();
    for (int i = 0; i < numComponentes; i++)
        exibirComponente(mochila[i]);
    printf("--------------------------------------------------------------\n");

    pausar();
}

// Organizar mochila
void organizarMochila() {
    if (numComponentes < 2) {
        printf("\nE necessario pelo menos 2 componentes para ordenar.\n");
        pausar();
        return;
    }

    printf("\n---\n");
    printf("Estrategia de Organizacao ---\n");
    printf("Como deseja ordenar os componentes?\n");
    printf("1. Por Nome (Ordem Alfabetica)\n");
    printf("2. Por Tipo\n");
    printf("3. Por Prioridade de Montagem\n");
    printf("0. Cancelar\n");
    printf("Escolha o criterio: ");

    int op;
    scanf("%d", &op);

    if (op == 0) return;

    switch(op) {
        case 1: bubbleSort(); break;
        case 2: insertionSort(); break;
        case 3: selectionSort(); break;
        default:
            printf("\nOpcao invalida!\n");
            pausar();
    }
}

// Busca binária por nome (necessita que esteja ordenada por nome)
void buscaBinaria() {
    if (!ordenadaPorNome) {
        printf("\nALERTA: A busca binaria requer que a mochila esteja ordenada por NOME.\n");
        printf("Use a Opcao 4 para organizar a mochila primeiro.\n");
        pausar();
        return;
    }

    char chave[TAM_NOME];
    printf("\n--- Busca Binaria por Componente-Chave ---\n");
    printf("Nome do componente a buscar: ");
    scanf(" %[^\n]", chave);

    int inicio = 0, fim = numComponentes - 1;
    bool encontrado = false;
    int pos = -1;
    comparacoes = 0;

    while (inicio <= fim) {
        int meio = (inicio + fim)/2;
        comparacoes++;
        int cmp = strcmp(mochila[meio].nome, chave);
        if (cmp == 0) {
            pos = meio;
            encontrado = true;
            break;
        } else if (cmp < 0) inicio = meio + 1;
        else fim = meio - 1;
    }

    if (encontrado) {
        printf("\n --- Componente-Chave Encontrado!  --- \n");
        printf("Nome: %s, Tipo: %s, Qtd: %d, Prio: %d \n",
               mochila[pos].nome,
               mochila[pos].tipo,
               mochila[pos].quantidade,
               mochila[pos].prioridade);
    } else {
        printf("\n --- Componente-Chave '%s' nao encontrado. --- \n", chave);
    }

    pausar();
}

// Lista todos os componentes da mochila
void listarComponentes() {
    if (numComponentes == 0) {
        printf("\nA mochila esta vazia.\n");
        pausar();
        return;
    }

    printf("\n--- INVENTARIO ATUAL (%d/%d) ---\n", numComponentes, MAX_COMPONENTES);
    exibirTabelaCabecalho();
    for (int i = 0; i < numComponentes; i++)
        exibirComponente(mochila[i]);
    printf("--------------------------------------------------------------\n");
    pausar();
}

// Remover componente
void descartarComponente() {
    if (numComponentes == 0) {
        printf("\nA mochila esta vazia.\n");
        pausar();
        return;
    }

    char nome[TAM_NOME];
    printf("Digite o nome do componente a descartar: ");
    scanf(" %[^\n]", nome);

    int i, encontrado = 0;
    for (i = 0; i < numComponentes; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("\nComponente nao encontrado.\n");
        pausar();
        return;
    }

    for (int j = i; j < numComponentes - 1; j++)
        mochila[j] = mochila[j+1];
    numComponentes--;

    printf("\nComponente '%s' removido com sucesso!\n", nome);
    pausar();
}

// Menu principal
int main() {
    int opcao;

    do {
        system("clear || cls");
        printf("==========================================================\n");
        printf("        PLANO DE FUGA - CODIGO DA ILHA (NIVEL MESTRE)\n");
        printf("==========================================================\n\n");
        printf("Itens na Mochila: %d/%d\n", numComponentes, MAX_COMPONENTES);
        printf("Status da Ordenacao por Nome: %s\n\n", ordenadaPorNome ? "ORDENADO" : "NAO ORDENADO");
        printf("1. Adicionar Componente\n");
        printf("2. Descartar Componente\n");
        printf("3. Listar Componentes (Inventario)\n");
        printf("4. Organizar Mochila (Ordenar Componentes)\n");
        printf("5. Busca Binaria por Componente-Chave (por nome)\n");
        printf("0. ATIVAR TORRE DE FUGA (Sair)\n");
        printf("----------------------------------------------------------\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);

        switch(opcao) {
            case 1: adicionarComponente(); break;
            case 2: descartarComponente(); break;
            case 3: listarComponentes(); break;
            case 4: organizarMochila(); break;
            case 5: buscaBinaria(); break;
            case 0: printf("\nSaindo e ativando torre de fuga...\n"); break;
            default:
                printf("\nOpcao invalida!\n");
                pausar();
        }

    } while(opcao != 0);

    return 0;
}
