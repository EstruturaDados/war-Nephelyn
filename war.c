#include <stdio.h>
#include <string.h>

struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

int main() {
  
    struct Territorio territorios[5];

    printf("Cadastro de Territórios \n\n");

   
    for (int i = 0; i < 5; i++) {
        printf("Cadastro do Território %d:\n", i + 1);

     
        printf("Digite o nome do território: ");
        scanf(" %29[^\n]", territorios[i].nome);
        printf("Digite a cor do exército: ");
        scanf(" %9s", territorios[i].cor);

       
        printf("Digite o número de tropas: ");
        scanf("%d", &territorios[i].tropas);

        printf("\n"); 
    }

   
    printf("\nDados dos Territórios Cadastrados\n\n");
    for (int i = 0; i < 5; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do Exército: %s\n", territorios[i].cor);
        printf("Tropas: %d\n", territorios[i].tropas);
        printf("-----------------------------\n");
    }

    printf("Cadastro concluido.\n");

    return 0;
}    