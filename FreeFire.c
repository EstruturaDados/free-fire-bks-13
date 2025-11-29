#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//Define o maximo de itens que pode conter na mochila
#define MAX_ITENS 10 

//Representa os itens no inventario
typedef struct {
    char nome[30];    // Array com o nome do item e limite de caracteres
    char tipo[20];    // Array com o tipo do item e limite de caracteres
    int quantidade;   // Quantidade de itens
} Item;

//Funções para inserir,remover,listar,buscar e aguardar o enter para continuar
void inserirItem(Item mochila[], int *total);
void removerItem(Item mochila[], int *total);
void listarItens(Item mochila[], int total);
void buscarItem(Item mochila[], int total);
void esperarEnter();


int main() {
    Item mochila[MAX_ITENS]; // Vetor que armazena os itens
    int total = 0;           // Quantidade de itens atualmente na mochila
    int opcao;

    do {
        printf("\n===========================================\n");
        printf("  MOCHILA DE SOBREVIVENCIA - CODIGO DA ILHA\n");
        printf("===========================================\n");
        printf("Itens na Mochila: %d/%d\n\n", total, MAX_ITENS);
        printf("1. Adicionar Item (Loot)\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens na Mochila\n");
        printf("4. Buscar Item na Mochila\n");
        printf("0. Sair\n");
        printf("-------------------------------------------\n");
        printf("Escolha uma opcao: ");

        // Valida a entrada digitada no menu
        if (scanf("%d", &opcao) != 1) {
            printf("\nEntrada invalida! Digite um numero.\n");
            while (getchar() != '\n');
            opcao = -1; 
        }
        getchar(); 

        switch (opcao) {
            case 1:
                inserirItem(mochila, &total);
                break;
            case 2:
                removerItem(mochila, &total);
                break;
            case 3:
                listarItens(mochila, total);
                break;
            case 4:
                buscarItem(mochila, total);
                break;
            case 0:
                printf("\nSaindo...\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
                esperarEnter();
        }

    } while (opcao != 0);

    return 0;
}

//Insere o item na mochila
void inserirItem(Item mochila[], int *total) {
    if (*total >= MAX_ITENS) {
        printf("\nA mochila esta cheia! Capacidade maxima: %d itens.\n", MAX_ITENS);
        esperarEnter();
        return;
    }

    Item novo;
    printf("\n---Adicionar Novo Item---\n");

    printf("Nome do item: ");
    fgets(novo.nome, 30, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    printf("Tipo do item (arma, municao, cura, etc.): ");
    fgets(novo.tipo, 20, stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    // Valida quantidade
    do {
        printf("Quantidade: ");
        if(scanf("%d", &novo.quantidade) != 1) {
            printf("Entrada invalida! Digite um numero positivo.\n");
            while(getchar() != '\n'); 
            novo.quantidade = 0;
        } else if (novo.quantidade <= 0) {
            printf("Quantidade invalida! Deve ser maior que zero.\n");
        }
    } while (novo.quantidade <= 0);
    getchar(); 

    mochila[*total] = novo;
    (*total)++;

    printf("\nItem '%s' adicionado com sucesso!\n", novo.nome);

    // Exibi os itens na mochila
    listarItens(mochila, *total);

    esperarEnter();
}

// Remove o item da mochila pelo nome digitado
void removerItem(Item mochila[], int *total) {
    if (*total == 0) {
        printf("\nNao ha itens para remover.\n");
        esperarEnter();
        return;
    }

    char nomeRemover[30];
    printf("\n---Remover Item---\n");
    printf("Digite o nome do item a ser removido: ");
    fgets(nomeRemover, 30, stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

    int encontrado = -1;
    for (int i = 0; i < *total; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("\nItem nao encontrado.\n");
        esperarEnter();
        return;
    }

    for (int i = encontrado; i < *total - 1; i++) {
        mochila[i] = mochila[i + 1];
    }
    (*total)--;

    printf("\nItem '%s' removido com sucesso!\n", nomeRemover);

    //Exibe os itens que estao na mochila apos serem removidos
    listarItens(mochila, *total);

    esperarEnter();
}

// Lista todos os itens da mochila
void listarItens(Item mochila[], int total) {
    printf("\n--- ITENS NA MOCHILA (%d/%d) ---\n", total, MAX_ITENS);
    if (total == 0) {
        printf("A mochila esta vazia.\n");
    } else {
        printf("---------------------------------------------------------\n");
        printf("%-18s | %-10s | %-9s\n", "NOME", "TIPO", "QUANTIDADE");
        printf("---------------------------------------------------------\n");
        for (int i = 0; i < total; i++) {
            printf("%-18s | %-10s | %-9d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
        }
        printf("---------------------------------------------------------\n");
    }
}

// Busca sequencial, busca o item na mochila pelo nome
void buscarItem(Item mochila[], int total) {
    if (total == 0) {
        printf("\nA mochila esta vazia.\n");
        esperarEnter();
        return;
    }

    char nomeBuscar[30];
    printf("\n---Buscar Item---\n");
    printf("Digite o nome do item que deseja buscar: ");
    fgets(nomeBuscar, 30, stdin);
    nomeBuscar[strcspn(nomeBuscar, "\n")] = '\0';

    int encontrado = 0;
    for (int i = 0; i < total; i++) {
        if (strcmp(mochila[i].nome, nomeBuscar) == 0) {
            printf("\nItem encontrado:\n");
            printf("-------------------------------------------------\n");
            printf("%-18s | %-10s | %-9s\n", "NOME", "TIPO", "QUANTIDADE");
            printf("-------------------------------------------------\n");
            printf("%-18s | %-10s | %-9d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            printf("-------------------------------------------------\n");
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("\nItem '%s' nao encontrado na mochila.\n", nomeBuscar);
    }

    esperarEnter();
}

// Aguarda o usuario pressionar o enter para continuar
void esperarEnter() {
    printf("\nPressione Enter para continuar...");
    getchar();
}
