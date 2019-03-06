#ifndef HOMEWORK_H1
#define HOMEWORK_H1

/* Macrodefinitie pentru elementul minim */
#define MIN(a, b) (a < b? a : b)

/* Structura pentru imagine de tip pnm */
typedef struct {
    char P;
    int height, width;
    unsigned char maxVal;
    unsigned char **bw;
}image;

/* Structura pentru thread (o dau ca parametru in threadFunction) */
typedef struct {
    image *img;
    int thread_id;
} thread_struct;

/* Antet functii */
void initialize(image *im);

void render(image *im);

void writeData(const char * fileName, image *img);

#endif /* HOMEWORK_H1 */