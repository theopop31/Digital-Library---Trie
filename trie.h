/* POPESCU Ioan Emanuel Theodor - 315CB */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>

#define MAX_ALF 68
#define MAX_TITLE 50
#define MAX_AUTH 40

#ifndef _ARBORE_PREFIXE_
#define _ARBORE_PREFIXE_

typedef struct carte
{
    char titlu[MAX_TITLE], autor[MAX_AUTH];
    int rating, nr_pag;
}Info;

typedef struct nod1
{
    struct nod1 *fii[MAX_ALF]; /* vectorul de fii pentru nod */
    int sf_cuv; /* va avea val. 1 daca am ajuns la sfarsitul unui cuvant */
    Info* carte; /* structura in care retinem info despre carte */
}TNod1, *T1;

typedef struct nod2
{
    struct nod2 *fii[MAX_ALF]; /* vectorul de fii pentru nod */
    int sf_cuv; /* va avea val. 1 daca am ajuns la sfarsitul unui cuvant */
    T1 info; /* arbore de tip T1 */
}TNod2, *T2;

int indx(char c);
T1 alocNod1();
T2 alocNod2();
void InserT2(T2 a, Info* carte);
void InserT1(T1 a, Info* carte);
int cautaT1(T1 a, char* titlu, FILE* g);
void afisTrieT1(T1 a, char s[], int niv, FILE* g);
int cautaT2(T2 a, char* autor, FILE* g);
int search_author(T2 a, char* autor, char* titlu, FILE* g);
#endif