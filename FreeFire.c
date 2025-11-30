#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct que representa os itens
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Nó da lista encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

No* inicio = NULL;   // início da lista ligada
int totalItens = 0;  


// Pausa onde fica aguardando o usuario apertar enter
void pausar() {
    printf("\nPressione ENTER para continuar...");
    getchar();
    getchar();
}


// Exibi o cabecalho de itens
void exibirTabelaCabecalho() {
    printf("---------------------------------------------------------\n");
    printf("NOME               | TIPO         | QUANTIDADE\n");
    printf("---------------------------------------------------------\n");
}

void exibirItem(Item item) {
    printf("%-18s | %-12s | %d\n", item.nome, item.tipo, item.quantidade);
}


// Adiciona um item na mochila
void inserirItemLista() {

    Item novo;

    printf("\n--- Adicionar Novo Item ---\n");
    printf("Nome do item: ");
    scanf(" %[^\n]", novo.nome);

    printf("Tipo do item (arma, municao, cura...): ");
    scanf(" %[^\n]", novo.tipo);

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->dados = novo;
    novoNo->proximo = NULL;

    if (inicio == NULL) {
        inicio = novoNo;
    } else {
        No* temp = inicio;
        while (temp->proximo != NULL)
            temp = temp->proximo;
        temp->proximo = novoNo;
    }

    totalItens++;

    printf("\nItem '%s' adicionado com sucesso!\n", novo.nome);
    pausar();
}


// Lista os itens da mochila
void listarItensLista() {

    if (inicio == NULL) {
        printf("\nA mochila está vazia.\n");
        pausar();
        return;
    }

    printf("\n--- ITENS NA MOCHILA (%d itens) ---\n", totalItens);
    exibirTabelaCabecalho();

    No* temp = inicio;

    while (temp != NULL) {
        exibirItem(temp->dados);
        temp = temp->proximo;
    }

    printf("---------------------------------------------------------\n");
    pausar();
}


// Remove um item da lista
void removerItemLista() {

    if (inicio == NULL) {
        printf("\nA mochila está vazia.\n");
        pausar();
        return;
    }

    char nome[30];
    printf("Digite o nome do item que deseja remover: ");
    scanf(" %[^\n]", nome);

    No* temp = inicio;
    No* anterior = NULL;

    while (temp != NULL) {

        if (strcmp(temp->dados.nome, nome) == 0) {

            if (anterior == NULL)
                inicio = temp->proximo;
            else
                anterior->proximo = temp->proximo;

            free(temp);
            totalItens--;

            printf("\nItem '%s' removido com sucesso!\n", nome);
            pausar();
            return;
        }

        anterior = temp;
        temp = temp->proximo;
    }

    printf("\nItem não encontrado.\n");
    pausar();
}


// Faz a busca sequencial dos itens na mochila
void buscarSequencialLista() {

    char nome[30];
    printf("Digite o nome do item que deseja buscar: ");
    scanf(" %[^\n]", nome);

    int comparacoes = 0;
    No* temp = inicio;

    while (temp != NULL) {
        comparacoes++;

        if (strcmp(temp->dados.nome, nome) == 0) {

            printf("\nItem encontrado!\n");
            printf("Comparações realizadas: %d\n", comparacoes);

            exibirTabelaCabecalho();
            exibirItem(temp->dados);
            printf("---------------------------------------------------------\n");

            pausar();
            return;
        }

        temp = temp->proximo;
    }

    printf("\nItem não encontrado.\nComparações: %d\n", comparacoes);
    pausar();
}



// Exibe o menu de opções da mochila
int main() {

    int opcao;
    char entrada[10];

    do {
        system("clear || cls");

        printf("===========================================\n");
        printf("  MOCHILA DE SOBREVIVENCIA - CODIGO DA ILHA\n");
        printf("===========================================\n");
        printf("Itens na Mochila: %d\n\n", totalItens);

        printf("1. Adicionar Item (Loot)\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens na Mochila\n");
        printf("4. Buscar Item por Nome\n");
        printf("0. Sair\n");
        printf("-------------------------------------------\n");
        printf("Escolha uma opção: ");

        scanf("%s", entrada);

        if (strlen(entrada) == 1 && entrada[0] >= '0' && entrada[0] <= '4')
            opcao = entrada[0] - '0';
        else
            opcao = -1;

        switch (opcao) {
            case 1: inserirItemLista(); break;
            case 2: removerItemLista(); break;
            case 3: listarItensLista(); break;
            case 4: buscarSequencialLista(); break;
            case 0: printf("\nSaindo...\n"); break;
            default: printf("\nOpção inválida!\n"); pausar();
        }

    } while (opcao != 0);

    return 0;
}
