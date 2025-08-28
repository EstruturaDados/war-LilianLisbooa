#include <stdio.h>
#include <string.h>

// Definição da struct territorio
// A struct permite agrupar diferentes tipos de dados relacionados
typedef struct {
    char nome[30];  // Nome do território
    char cor[10];   // Cor do Exército
    int tropas;     // Quantidade de tropas
}Territorio;

int main(){
    // Vetor de struct: armazenará ate 5 territórios
    Territorio territorios[5];

    //Cadastro dos territórios
    printf("=== Cadastro de Territórios ===\n\n");

    for (int i = 0; i < 5; i++) {
        printf("Cadastro de território %d:\n", i + 1);

        // Leitura do nome
        printf("Digite o nome do trritório: ");
        scanf(" %[^\n]", territorios[i].nome);  // Lê até espaço

         // Leitura da cor do exército
        printf("Digite a cor do exército: ");
        scanf(" %[^\n]", territorios[i].cor);

        // Leitura do número de tropas
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);

        printf("\n");
    }

    // Exibição dos dados cadastrados
    printf("\n=== Territórios Cadastrados ===\n\n");
    for (int i = 0; i < 5; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do Exército: %s\n", territorios[i].cor);
        printf("Quantidade de Tropas: %d\n", territorios[i].tropas);
        printf("-----------------------------\n");
    }

    return 0;
}