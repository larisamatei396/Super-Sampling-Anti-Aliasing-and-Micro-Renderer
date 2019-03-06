#include "homework1.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

int num_threads;
int resolution;

/* Functie care imi aloca o matrice in care retin pixelii pentru imaginea 
    grayscale */
unsigned char **allocation_bw(int height, int width) {
    int i, j;
    unsigned char **img;
    
    img = malloc (height * sizeof(unsigned char *));
    if (img == NULL) 
        return NULL;

    for (i = 0; i < height; i++) {
        img[i] = malloc (width * sizeof(unsigned char));
        if (img[i] == NULL) {
            for (j = 0; j < i; j++)
                free (img[j]);
            free(img);
            return NULL;
        }
    }
    return img;
}

/* Functie folosita pentru eliberarea memoriei */
void free_bw (unsigned char ***img, int height) {
    int i;
    for (i = 0; i < height; i++) 
        free((*img)[i]);
    free(*img);
    *img = NULL;
}

/* Functie pentru initializarea imaginii */
void initialize(image *img) {
    img -> P = '5';
    img -> height = resolution;
    img -> width = resolution;
    img -> maxVal = 255;

    img -> bw = allocation_bw (img -> height, img -> width);
}

void *threadFunction (void *var) {
    thread_struct thread = *(thread_struct*) var;
    int i, j, low, high, intervalSize;
    float x, y;

    /* Creez capetele intervalului pentru fiecare thread */
    intervalSize = ceil ((float) (thread.img -> height) / num_threads);
    low = thread.thread_id * intervalSize;
    high = MIN ((thread.thread_id + 1) * intervalSize, thread.img -> height);

    for (i = low; i < high; i++) {
        for (j = 0; j < thread.img -> width; j++) {
            /* Creez coordonatele pixelului in cm */
            x = (thread.img -> height - 1 - i + 0.5) * 100 / resolution;
            y = (j + 0.5) * 100 / resolution;
            if (abs(-y + 2 * x) / sqrt(5) <= 3)
                thread.img -> bw[i][j] = 0;
            else 
                thread.img -> bw[i][j] = 255;
        }
    }
    return NULL;
}

void render(image *img) {
    int i;
    pthread_t tid[num_threads];
    thread_struct *thread = malloc (num_threads * sizeof(thread_struct));    

    for (i = 0; i < num_threads; i++) {
        thread[i].img = img;
        thread[i].thread_id = i;
    }    

    for (i = 0; i < num_threads; i++) {
        pthread_create(&(tid[i]), NULL, threadFunction, &(thread[i]));
    }

    for (i = 0; i < num_threads; i++) {
        pthread_join(tid[i], NULL);
    }    

    free(thread);
}

/* Functie folosita pentru a crea imaginea */
void writeData(const char *fileName, image *img) {
    int i;
    /* Deschid fisierul */
    FILE *file_out = fopen(fileName, "wb");

    /* Scriu header-ul */
    fprintf(file_out, "P%c\n", img -> P);
    fprintf(file_out, "%d %d\n", img -> width, img -> height);
    fprintf(file_out, "%hhu\n", img -> maxVal);
    
    /* Scriu matricea de pixeli */
    for (i = 0; i < img -> height; i++)
        fwrite(img -> bw[i], sizeof(unsigned char), img -> width, file_out);
    
    /* Eliberez memoria */
    free_bw(&img -> bw, img -> height);
    /* Inchid fisierul */
    fclose(file_out);
}

