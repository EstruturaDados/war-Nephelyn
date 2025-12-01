#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

void atacar(struct Territorio* atacante, struct Territorio* defensor) {
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\n%s (%s) atacou %s (%s)!\n", atacante->nome, atacante->cor, defensor->nome, defensor->cor);
    printf("Dado do atacante: %d | Dado do defensor: %d\n", dadoAtacante, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("O atacante venceu!\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = (defensor->tropas / 2) + (atacante->tropas / 2);
        if (atacante->tropas > 0)
            atacante->tropas -= 1;
    } else {
        printf("O defensor resistiu!\n");
        if (atacante->tropas > 0)
            atacante->tropas -= 1;
    }
}


void exibir(struct Territorio* t, int n) {
    printf("\nSituação Atual dos Territórios\n");
    for (int i = 0; i < n; i++) {
        printf("%d. %s | Cor: %s | Tropas: %d\n", i + 1, t[i].nome, t[i].cor, t[i].tropas);
    }
}

int main() {
    srand(time(NULL)); 

    int n;
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &n);

   
    struct Territorio* t = (struct Territorio*) malloc(n * sizeof(struct Territorio));
    if (t == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

   
    for (int i = 0; i < n; i++) {
        printf("\n--- Território %d ---\n", i + 1);
        printf("Nome: ");
        scanf(" %29[^\n]", t[i].nome);
        printf("Cor do exército: ");
        scanf(" %9s", t[i].cor);
        printf("Número de tropas: ");
        scanf("%d", &t[i].tropas);
    }

    exibir(t, n);

    char continuar;
    do {
        int a, d;
        printf("\nEscolha o número do território que ira atacar (1 a %d): ", n);
        scanf("%d", &a);
        printf("Escolha o número do território que ira defender (1 a %d): ", n);
        scanf("%d", &d);

        if (a < 1 || a > n || d < 1 || d > n || a == d) {
            printf("Escolha inválida\n");
        } else {
            atacar(&t[a - 1], &t[d - 1]);
            exibir(t, n);
        }

        printf("\nDeseja realizar outro ataque? (s/n): ");
        scanf(" %c", &continuar);
    } while (continuar == 's' || continuar == 'S');

    free(t); // libera memória
    printf("\nMemória liberada. Programa encerrado.\n");

    return 0;
}