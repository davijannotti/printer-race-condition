#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define NUM_THREADS 3
#define PAGINAS_POR_USUARIO 5

struct {
    char usuario_atual[50]; 
    int pagina_atual;     
} impressora;

pthread_mutex_t mutex;

void* enviar_para_impressora(void* nome_usuario) {
    char* usuario = (char*)nome_usuario;

    for (int i = 1; i <= PAGINAS_POR_USUARIO; i++) {
        pthread_mutex_lock(&mutex); // Bloqueia o acesso à impressora

        strcpy(impressora.usuario_atual, usuario);
        impressora.pagina_atual = i;

        // Simula o tempo de impressão
        usleep(1000 * (rand() % 10));

        printf("Usuário: %s está imprimindo página %d\n", impressora.usuario_atual, impressora.pagina_atual);

        pthread_mutex_unlock(&mutex); // Libera o acesso à impressora
    }

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    char* usuarios[NUM_THREADS] = {"Joao", "Pedro", "Dani"};

    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, enviar_para_impressora, (void*)usuarios[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);

    return 0;
}
