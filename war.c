#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 5

typedef struct {
    char nome[50];
    char cor[20];
    int tropas;
} Territorio;

void mostrarMapa(const Territorio *t) {
    printf("\n=== MAPA ===\n");
    for (int i = 0; i < MAX; i++) {
        printf("%d - %s (%s) Tropas: %d\n",
            i + 1, t[i].nome, t[i].cor, t[i].tropas);
    }
}

void atacar(Territorio *atk, Territorio *def) {
    int dAtk = rand() % 6 + 1;
    int dDef = rand() % 6 + 1;

    printf("\nDados: Atk=%d | Def=%d\n", dAtk, dDef);

    if (dAtk >= dDef) {
        printf("Atacante venceu! -1 tropa no defensor\n");
        def->tropas--;
        if (def->tropas <= 0) {
            printf(">>> TERRITÓRIO CONQUISTADO!\n");
            strcpy(def->cor, atk->cor);
            def->tropas = 1;
        }
    } else {
        printf("Defensor segurou!\n");
    }
}

int missaoConcluida(const Territorio *t, int tipoMissao, const char *alvoCor) {
    if (tipoMissao == 1) {  
        for (int i = 0; i < MAX; i++) {
            if (strcmp(t[i].cor, alvoCor) == 0) return 0;
        }
        return 1;
    }

    if (tipoMissao == 2) {  
        int count = 0;
        for (int i = 0; i < MAX; i++) {
            if (t[i].tropas > 0) count++;
        }
        return (count >= 3);
    }

    return 0;
}

int main() {
    srand(time(NULL));

    Territorio t[MAX] = {
        {"Norte", "Vermelho", 3},
        {"Sul", "Verde", 2},
        {"Leste", "Azul", 4},
        {"Oeste", "Amarelo", 2},
        {"Centro", "Roxo", 5}
    };

    int missao = rand() % 2 + 1;
    const char alvo[] = "Verde";

    printf("=== Missão ===\n");
    if (missao == 1)
        printf("Destruir o exército %s\n", alvo);
    else
        printf("Conquistar 3 territórios\n");

    int opc, atk, def;
    while (1) {
        printf("\nMENU\n1 - Atacar\n2 - Verificar Missão\n0 - Sair\n> ");
        scanf("%d", &opc);

        if (opc == 0) break;

        if (opc == 1) {
            mostrarMapa(t);

            printf("Atacante: ");
            scanf("%d", &atk);
            printf("Defensor: ");
            scanf("%d", &def);

            atacar(&t[atk - 1], &t[def - 1]);
        }

        else if (opc == 2) {
            if (missaoConcluida(t, missao, alvo)) {
                printf("\n🎉 MISSÃO CUMPRIDA! PARABÉNS!\n");
                break;
            } else {
                printf("Missão ainda não concluída...\n");
            }
        }
    }

    return 0;
}