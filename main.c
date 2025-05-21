#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TARGET "HELLO C LANGUAGE AND AI"
#define POP_SIZE 100
#define CHARS "ABCDEFGHIJKLMNOPQRSTUVWXYZ "
#define MUTATION_RATE 0.1

int calc_fitness(const char *genes) {
    int score = 0;
    for (int i = 0; TARGET[i] != '\0'; ++i) {
        if (genes[i] == TARGET[i]) {
            ++score;
        }
    }
    return score;
}

void random_genes(char *genes, int length) {
    for (int i = 0; i < length; ++i) {
        genes[i] = CHARS[rand() % strlen(CHARS)];
    }
    genes[length] = '\0';
}

void mutate(char *genes, int length) {
    if ((double)rand() / RAND_MAX < MUTATION_RATE) {
        int pos = rand() % length;
        genes[pos] = CHARS[rand() % strlen(CHARS)];
    }
}

int main() {
    srand((unsigned int)time(NULL));
    int len = strlen(TARGET);
    char best[len + 1];
    random_genes(best, len);
    int best_fitness = calc_fitness(best);

    while (best_fitness < len) {
        char new_gen[len + 1];
        char candidate[len + 1];
        int max_fitness = -1;

        for (int i = 0; i < POP_SIZE; ++i) {
            strcpy(candidate, best);
            mutate(candidate, len);
            int f = calc_fitness(candidate);
            if (f > max_fitness) {
                max_fitness = f;
                strcpy(new_gen, candidate);
            }
        }

        strcpy(best, new_gen);
        best_fitness = max_fitness;
        printf("%s (fitness: %d)\n", best, best_fitness);
    }

    printf("Completed: %s\n", best);
    return 0;
}
