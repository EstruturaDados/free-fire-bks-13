#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10 // Capacidade maxima que cabe na mochila

//Struct onde representa um item dentro da mochila
typedef struct {
    char nome[30]; // Nome do item
    char tipo[20]; // Tipo do item
    int quantidade; // Quantidade que contem o item
} Item;
//Vetor da mochila
Item mochila[MAX_ITENS];
int totalItens = 0; //Quantidade atual dos itens
int vetorOrdenado = 0; //Flag indica se o vetor ta ordenado


// Função que aguarda ate o usuario apertar enter
void pausar() {
    printf("\nPressione ENTER para continuar...");
    getchar();
    getchar();
}


// Função que exibe a tabela
void exibirTabelaCabecalho() {
    printf("---------------------------------------------------------\n");
    printf("NOME               | TIPO         | QUANTIDADE\n");
    printf("---------------------------------------------------------\n");
}

void exibirItem(Item item) {
    printf("%-18s | %-12s | %d\n", item.nome, item.tipo, item.quantidade);
}


// Insere novo item no vetor lista sequencial
void inserirItem() {

    if (totalItens >= MAX_ITENS) {
        printf("\nA mochila está cheia!\n");
        pausar();
        return;
    }

    Item novo;

    printf("\n--- Adicionar Novo Item ---\n");
    printf("Nome do item: ");
    scanf(" %[^\n]", novo.nome);

    printf("Tipo do item (arma, municao, cura...): ");
    scanf(" %[^\n]", novo.tipo);

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    mochila[totalItens] = novo;
    totalItens++;
    vetorOrdenado = 0;

    printf("\nItem '%s' adicionado com sucesso!\n", novo.nome);
    pausar();
}


// Lista os itens do vetor
void listarItens() {

    if (totalItens == 0) {
        printf("\nA mochila está vazia.\n");
        pausar();
        return;
    }

    printf("\n--- ITENS NA MOCHILA (%d/%d) ---\n", totalItens, MAX_ITENS);
    exibirTabelaCabecalho();

    for (int i = 0; i < totalItens; i++) {
        exibirItem(mochila[i]);
    }

    printf("---------------------------------------------------------\n");
    pausar();
}


// Remove o item pelo nome no vetor
void removerItem() {

    char nome[30];
    printf("Digite o nome do item que deseja remover: ");
    scanf(" %[^\n]", nome);

    for (int i = 0; i < totalItens; i++) {

        if (strcmp(mochila[i].nome, nome) == 0) {

            for (int j = i; j < totalItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }

            totalItens--;
            printf("\nItem '%s' removido com sucesso!\n", nome);
            pausar();
            return;
        }
    }

    printf("\nItem não encontrado.\n");
    pausar();
}


// Busca sequencial no vetor/ Conta as comparações feitas
void buscarSequencial() {

    char nome[30];
    printf("Digite o nome do item que deseja buscar (sequencial): ");
    scanf(" %[^\n]", nome);

    int comparacoes = 0;

    for (int i = 0; i < totalItens; i++) {

        comparacoes++;

        if (strcmp(mochila[i].nome, nome) == 0) {

            printf("\nItem encontrado!\n");
            printf("Comparações realizadas: %d\n", comparacoes);

            exibirTabelaCabecalho();
            exibirItem(mochila[i]);
            printf("---------------------------------------------------------\n");

            pausar();
            return;
        }
    }

    printf("\nItem não encontrado.\nComparações: %d\n", comparacoes);
    pausar();
}


// Faz a ordenação bubble sort
void ordenarVetor() {

    if (totalItens < 2) {
        printf("\nPoucos itens para ordenar.\n");
        pausar();
        return;
    }

    for (int i = 0; i < totalItens - 1; i++) {
        for (int j = 0; j < totalItens - i - 1; j++) {
            if (strcmp(mochila[j].nome, mochila[j + 1].nome) > 0) {

                Item temp = mochila[j];
                mochila[j] = mochila[j + 1];
                mochila[j + 1] = temp;
            }
        }
    }

    vetorOrdenado = 1;

    printf("\nItens ordenados pelo nome!\n");
    listarItens();
}


// Faz a busca binaria, somente se o vetor tiver ordenado
void buscarBinaria() {

    if (!vetorOrdenado) {
        printf("\nO vetor precisa estar ordenado antes da busca binária!\n");
        pausar();
        return;
    }

    char nome[30];
    printf("Digite o nome do item para busca binária: ");
    scanf(" %[^\n]", nome);

    int inicio = 0;
    int fim = totalItens - 1;
    int comparacoes = 0;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoes++;

        int cmp = strcmp(nome, mochila[meio].nome);

        if (cmp == 0) {
            printf("\nItem encontrado!\nComparações: %d\n", comparacoes);

            exibirTabelaCabecalho();
            exibirItem(mochila[meio]);
            printf("---------------------------------------------------------\n");

            pausar();
            return;
        }
        else if (cmp > 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }

    printf("\nItem não encontrado.\nComparações: %d\n", comparacoes);
    pausar();
}


// Menu da mochila, com tratamento para erros caso o usuario digite letras
int main() {

    int opcao;
    char entrada[10];

    do {
        system("clear || cls");

        printf("===========================================\n");
        printf("  MOCHILA DE SOBREVIVENCIA - CODIGO DA ILHA\n");
        printf("===========================================\n");
        printf("Itens na Mochila: %d/%d\n\n", totalItens, MAX_ITENS);

        printf("1. Adicionar Item (Loot)\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens\n");
        printf("4. Buscar Item\n");
        printf("5. Ordenar Itens\n");
        printf("6. Buscar Item (Binária)\n");
        printf("0. Sair\n");
        printf("-------------------------------------------\n");
        printf("Escolha uma opção: ");

        scanf("%s", entrada);

        // valida número
        if (strlen(entrada) == 1 && entrada[0] >= '0' && entrada[0] <= '6')
            opcao = entrada[0] - '0';
        else
            opcao = -1;

        switch (opcao) {
            case 1: inserirItem(); break;
            case 2: removerItem(); break;
            case 3: listarItens(); break;
            case 4: buscarSequencial(); break;
            case 5: ordenarVetor(); break;
            case 6: buscarBinaria(); break;
            case 0: printf("\nSaindo...\n"); break;
            default: printf("\nOpção inválida!\n"); pausar();
        }

    } while (opcao != 0);

    return 0;
}
