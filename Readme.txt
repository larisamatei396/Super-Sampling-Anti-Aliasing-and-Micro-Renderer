===============================================================================
    MATEI Bianca-Larisa -> 332CB -- TEMA 1 APD --
===============================================================================


*******************************************************************************
    Part 1. Super Sampling Anti Aliasing
*******************************************************************************
    Pentru prima parte a temei, am declarat in fisierul homework.h urmatoarele
structuri: 
->  pixel (structura ajutatoare pentru a retine un pixel pentru imaginile 
    color); 
->  image (structura in care retin imaginea de tip pnm). In variabilele P, 
    height, width si maxVal retin header-ul imaginii, iar in matricea color 
    retin pixelii in cazul in care imaginea este color. In bw retin pixelii 
    (dati ca o valoare intre 0 si 255) pentru imaginea grayscale;
->  thread_struct (structura pentru thread-uri pe care o dau ca parametru in 
    threadFunction).

    homework.c:

    Pentru inceput, am declarat global si am initializat matricea ce contine 
valorile Kernel-ului Gaussian. Am creat urmatoarele functii:
->  allocation_color - functie care imi aloca o matrice cu elemente de tip 
    pixel;
->  free_color - functie pentru eliberarea memoriei folosite pentru o matrice 
    cu elemente de tip pixel;
->  allocation_bw - functie care imi aloca o matrice cu elemente de tip 
    unsigned char (retin pixelii pentru imaginea de tip grayscale);
->  free_bw - functie pentru eliberarea memoriei folosite pentru o matrice 
    cu elemente de tip unsigned char (imagine de tip grayscale);

->  readInput - functie folosita pentru a retine datele din imaginea de input.
    Dupa ce am deschis fisierul, am sarit peste primul byte ('P') folosind 
    functia fseek, dupa care am retinut tipul imaginii (color sau grayscale).
    Dupa ce am retinut header-ul imaginii de tip pnm, am citit matricea care 
    contine pixelii imaginii (in functie de tipul acesteia). La final, am 
    inchis fisierul.

->  writeData - dupa ce am deschis fisierul si am creat header-ul imaginii de 
    output, am scris in fisier matricea rezultata in functie de tipul imaginii 
    (color sau grayscale) si am eliberat memoria. La final, am inchis fisierul.

->  threadFunction - functie folosita pentru resize_factor par si care primeste
    ca parametru un argument de tip thread_struct (contine imaginea de input,
    imaginea de output si id-ul threadului). Pentru inceput, am creat capetele
    de interval pentru fiecare thread in functie de id-ul acestuia (am impartit
    height-ul matricii in num_threads threaduri). In functie de tipul imaginii,
    am impartit matricea in submatrici de dimensiune resize_factor * 
    resize_factor, am calculat media aritmetica a pixelilor si am salvat 
    rezultatul in output.

->  threadFunction_odd - functie folosita pentru resize_factor impar (==3) si 
    care primeste ca parametru un argument de tip thread_struct, la fel ca mai 
    devreme. Diferenta este ca de data aceasta, am inmultit fiecare valoare din 
    submatricea de dimensiune 3 * 3 cu valorile corespunzatoare din matricea 
    gaussianKernel si am impartit suma elementelor din matricea rezultata la 
    suma elementelor din matricea gaussianKernel. In final, retin valorile in 
    output.

->  resize - dupa ce am retinut header-ul in output (cu dimensiunile micsorate)
    si am alocat memorie, am completat structura pe care urmeaza sa o dau ca 
    parametru functiei threadFunction pentru fiecare thread. In functie de 
    resize_factor (par sau impar), redimensionez imaginea in cazul in care nu 
    se imparte exact la resize_factor (pierd informatia din partea dreapta sau
    de jos a imaginii) si creez threadurile. La final, eliberez memoria.
-------------------------------------------------------------------------------


*******************************************************************************
    Part 2. Micro renderer
*******************************************************************************
    Pentru cea de-a doua parte a temei, am declarat in fisierul homework1.h 
urmatoarele structuri: 
->  image (structura in care retin imaginea de tip pnm). In variabilele P, 
    height, width si maxVal retin header-ul imaginii, iar in bw retin pixelii 
    (valori de 0 sau 255) pentru imaginea grayscale;
->  thread_struct (structura pentru thread-uri pe care o dau ca parametru in 
    threadFunction).

    homework1.c:

    Am creat urmatoarele functii:
->  allocation_bw - functie care imi aloca o matrice cu elemente de tip 
    unsigned char (retin pixelii pentru imaginea de tip grayscale);
->  free_bw - functie pentru eliberarea memoriei folosite pentru o matrice 
    cu elemente de tip unsigned char (imagine de tip grayscale);

->  initialize - functie pentru initializarea imaginii (setez header-ul si 
    aloc memorie pentru matricea de pixeli).

->  threadFunction - am creat capetele intervalului pentru fiecare thread 
    si am creat imaginea alba (255) cu o linie neagra (0). Pentru aceasta, 
    am luat centrul fiecarui pixel si am calculat distanta de la acesta la 
    linie dupa formula |ax + by + c| / sqrt(a^2 + b^2). Daca aceasta distanta 
    este <= 3, atunci pixelul va fi negru, altfel va fi alb.

->  render - am creat vrectorul ce contine elemente de tip thread_struct 
    (in care retin imaginea si id-ul threadului) si am creat num_threads 
    threaduri.

->  writeData - dupa ce am deschis fisierul si am creat header-ul imaginii de 
    output, am scris in fisier matricea creata si am eliberat memoria. 
    La final, am inchis fisierul.
-------------------------------------------------------------------------------
    