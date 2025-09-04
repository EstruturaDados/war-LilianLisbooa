#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// ========================== FUNÇÕES =============================

// Função para cadastrar territórios
void cadastrarTerritorios(Territorio* mapa, int tamanho) {
    printf("\n===== Cadastro de Territórios =====\n");
    for (int i = 0; i < tamanho; i++) {
        printf("\n--- Território %d ---\n", i + 1);
        printf("Nome: ");
        scanf(" %[^\n]", mapa[i].nome);
        printf("Cor do exército: ");
        scanf(" %[^\n]", mapa[i].cor);
        printf("Tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

// Função para exibir os territórios
void exibirMapa(Territorio* mapa, int tamanho) {
    printf("\n===== Mapa Atual =====\n");
    for (int i = 0; i < tamanho; i++) {
        printf("[%d] %s | Cor: %s | Tropas: %d\n", i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// Atribui uma missão aleatória ao jogador
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;
    strcpy(destino, missoes[indice]);
}

// Simula um ataque entre dois territórios
void atacar(Territorio* atacante, Territorio* defensor) {
    int dadoA = rand() % 6 + 1;
    int dadoD = rand() % 6 + 1;

    printf("\nRolagem de dados - %s (A): %d | %s (D): %d\n", atacante->nome, dadoA, defensor->nome, dadoD);

    if (dadoA > dadoD) {
        printf("Vitória de %s! Conquistou %s.\n", atacante->nome, defensor->nome);
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
    } else {
        printf("Defesa bem-sucedida! %s perde 1 tropa.\n", atacante->nome);
        if (atacante->tropas > 1)
            atacante->tropas -= 1;
    }
}

// Exibe a missão do jogador no início
void exibirMissao(const char* missao) {
    printf("\n🎯 Sua missão estratégica: %s\n", missao);
}

// Verifica se a missão foi cumprida (lógica simples de exemplo)
int verificarMissao(char* missao, Territorio* mapa, int tamanho) {
    if (strcmp(missao, "Controlar pelo menos 3 territórios") == 0) {
        // Conta quantos territórios têm a mesma cor (exemplo: "azul")
        int cont = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "azul") == 0)
                cont++;
        }
        return cont >= 3;
    }
    if (strcmp(missao, "Conquistar um território com mais de 5 tropas") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "azul") == 0 && mapa[i].tropas > 5)
                return 1;
        }
    }
    if (strcmp(missao, "Eliminar todas as tropas da cor vermelha") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelho") == 0)
                return 0;
        }
        return 1;
    }

    // Outras missões podem ser adicionadas aqui...

    return 0;
}

// Libera toda a memória alocada
void liberarMemoria(Territorio* mapa, char* missao) {
    free(mapa);
    free(missao);
}

// ========================== MAIN =============================

int main() {
    srand(time(NULL));

    int total;
    printf("Digite o número total de territórios: ");
    scanf("%d", &total);

    // Alocação dinâmica do mapa
    Territorio* mapa = (Territorio*) malloc(total * sizeof(Territorio));
    if (!mapa) {
        printf("Erro de alocação de memória.\n");
        return 1;
    }

    // Vetor de missões possíveis
    char* missoes[] = {
        "Conquistar 2 territórios inimigos",
        "Eliminar todas as tropas da cor vermelha",
        "Controlar pelo menos 3 territórios",
        "Conquistar um território com mais de 5 tropas",
        "Perder apenas 1 tropa durante o jogo"
    };
    int totalMissoes = sizeof(missoes) / sizeof(missoes[0]);

    // Alocação dinâmica para missão do jogador
    char* missaoJogador = (char*) malloc(100 * sizeof(char));
    if (!missaoJogador) {
        printf("Erro ao alocar memória para a missão.\n");
        free(mapa);
        return 1;
    }

    // Cadastro do mapa e sorteio da missão
    cadastrarTerritorios(mapa, total);
    atribuirMissao(missaoJogador, missoes, totalMissoes);
    exibirMissao(missaoJogador);

    // Loop do jogo
    char continuar;
    do {
        int iA, iD;

        exibirMapa(mapa, total);
        printf("\nDigite o número do território ATACANTE: ");
        scanf("%d", &iA);

        printf("Digite o número do território DEFENSOR: ");
        scanf("%d", &iD);

        if (iA < 0 || iA >= total || iD < 0 || iD >= total) {
            printf("Índices inválidos. Tente novamente.\n");
        } else if (strcmp(mapa[iA].cor, mapa[iD].cor) == 0) {
            printf("Não é possível atacar território da mesma cor.\n");
        } else {
            atacar(&mapa[iA], &mapa[iD]);
        }

        // Verificação silenciosa da missão
        if (verificarMissao(missaoJogador, mapa, total)) {
            printf("\n🎉 Parabéns! Você cumpriu sua missão: %s\n", missaoJogador);
            break;
        }

        printf("\nDeseja realizar outro ataque? (s/n): ");
        scanf(" %c", &continuar);

    } while (continuar == 's' || continuar == 'S');

    liberarMemoria(mapa, missaoJogador);
    printf("\nJogo encerrado. Memória liberada.\n");

    return 0;
}
