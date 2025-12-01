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


void exibirMapa(struct Territorio* t, int n) {
    printf("\n--- Situação Atual dos Territórios ---\n");
    for (int i = 0; i < n; i++) {
        printf("%d. %s | Cor: %s | Tropas: %d\n", i + 1, t[i].nome, t[i].cor, t[i].tropas);
    }
}

void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int sorteio = rand() % totalMissoes;
    strcpy(destino, missoes[sorteio]);
}


void exibirMissao(char* missao) {
    printf("\n--- Sua Missão ---\n");
    printf("%s\n", missao);
}

int verificarMissao(char* missao, struct Territorio* mapa, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        if (mapa[i].tropas < 2) {
            return 1; 
        }
    }
    return 0;
}


void liberarMemoria(struct Territorio* mapa, char* missao) {
    free(mapa);
    free(missao);
    printf("\nMemória liberada. Programa encerrado.\n");
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
        printf("\n Território %d \n", i + 1);
        printf("Nome: ");
        scanf(" %29[^\n]", t[i].nome);
        printf("Cor do exército: ");
        scanf(" %9s", t[i].cor);
        printf("Número de tropas: ");
        scanf("%d", &t[i].tropas);
    }

  
    char* missoes[] = {
        "Conquistar 3 territórios seguidos.",
        "Controlar todos os territórios com mais de 10 tropas.",
        "Ter pelo menos 2 territórios com mais de 20 tropas.",
        "Reduzir as tropas inimigas a menos de 2 unidades."
    };

    int totalMissoes = 5;

    char* missaoJogador = (char*) malloc(100 * sizeof(char));
    if (missaoJogador == NULL) {
        printf("Erro ao alocar memória para a missão!\n");
        free(t);
        return 1;
    }

    atribuirMissao(missaoJogador, missoes, totalMissoes);
    exibirMissao(missaoJogador);

    exibirMapa(t, n);

   
    char continuar;
    do {
        int a, d;
        printf("\nEscolha o território que irá atacar (1 a %d): ", n);
        scanf("%d", &a);
        printf("Escolha o território que irá defender (1 a %d): ", n);
        scanf("%d", &d);

        if (a < 1 || a > n || d < 1 || d > n || a == d) {
            printf("Escolha inválida!\n");
        } else {
            atacar(&t[a - 1], &t[d - 1]);
            exibirMapa(t, n);
        }

        // Verifica se missão foi cumprida
        if (verificarMissao(missaoJogador, t, n)) {
            printf("\n🎯 Missão cumprida! Você venceu o jogo!\n");
            break;
        }

        printf("\nDeseja realizar outro ataque? (s/n): ");
        scanf(" %c", &continuar);
    } while (continuar == 's' || continuar == 'S');

    liberarMemoria(t, missaoJogador);
    return 0;
}