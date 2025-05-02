#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define NB_BUS_X 5
#define NB_BUS_Y 4
#define NB_TRAJETS 10

sem_t mutex;
sem_t tunnel;

int nb_buses_in_tunnel = 0;
int current_direction = -1; // -1: libre, 0: X->Y, 1: Y->X

void sleep_random() {
    usleep((rand() % 500 + 1000) * 1000); // entre 1s et 1.5s
}

void entrer_tunnel(int direction) {
    int opposite_direction = 1 - direction;

    while (1) {
        sem_wait(&mutex);

        if (nb_buses_in_tunnel == 0 || current_direction == direction) {
            nb_buses_in_tunnel++;
            current_direction = direction;
            sem_post(&mutex);
            break;
        }

        sem_post(&mutex);
        usleep(100000); // attendre un peu avant de réessayer
    }
}

void sortir_tunnel() {
    sem_wait(&mutex);
    nb_buses_in_tunnel--;
    if (nb_buses_in_tunnel == 0) {
        current_direction = -1; // libre
    }
    sem_post(&mutex);
}

void* bus_thread(void* arg) {
    int id = ((int*)arg)[0];
    int ville = ((int*)arg)[1]; // 0: X, 1: Y
    const char* noms_villes[] = {"X", "Y"};

    for (int i = 1; i <= NB_TRAJETS; i++) {
        // Aller
        entrer_tunnel(ville);
        printf("Bus %d de %s : %s -> %s (Trajet %d)\n",
               id, noms_villes[ville], noms_villes[ville], noms_villes[1 - ville], i);
        sleep_random();
        sortir_tunnel();

        // Retour
        entrer_tunnel(1 - ville);
        printf("Bus %d de %s : %s -> %s (Trajet %d)\n",
               id, noms_villes[ville], noms_villes[1 - ville], noms_villes[ville], i);
        sleep_random();
        sortir_tunnel();
    }

    free(arg); // libérer les arguments
    return NULL;
}

int main() {
    srand(time(NULL));
    pthread_t threads[NB_BUS_X + NB_BUS_Y];

    sem_init(&mutex, 0, 1);
    sem_init(&tunnel, 0, 1);

    int index = 0;

    // Créer les bus de la ville X
    for (int i = 0; i < NB_BUS_X; i++) {
        int* args = malloc(2 * sizeof(int));
        args[0] = i + 1; // ID du bus
        args[1] = 0;     // Ville X
        pthread_create(&threads[index++], NULL, bus_thread, args);
    }

    // Créer les bus de la ville Y
    for (int i = 0; i < NB_BUS_Y; i++) {
        int* args = malloc(2 * sizeof(int));
        args[0] = i + 1 + NB_BUS_X;
        args[1] = 1;     // Ville Y
        pthread_create(&threads[index++], NULL, bus_thread, args);
    }

    // Attendre tous les threads
    for (int i = 0; i < NB_BUS_X + NB_BUS_Y; i++) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&tunnel);

    return 0;
}
