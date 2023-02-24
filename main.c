/* POPESCU Ioan Emanuel Theodor - 315CB */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "trie.h"

int main(int argc, char *argv[])
{
    FILE* f, *g;
    char* line = NULL;
    size_t len = 0;
    /* initializare arbori */
    T1 Trie1 = alocNod1();
    T2 Trie2 = alocNod2();

    f = fopen(argv[1], "rt");
    if (f == NULL)
    {
        printf("Eroare la deschiderea fisierului de input!\n");
        return 0;
    }
    g = fopen(argv[2], "wt");
    if (g == NULL)
    {
        printf("Eroare la deschiderea fisierului de output!\n");
        return 0;
    }

    while (getline(&line, &len, f) != -1)
    {
        char* func = strtok(line, " ");
        // verificam sa nu existe caractere nedorite
        while (line[strlen(line) - 1] == '\n')
        {
            line[strlen(line) - 1] = 0;
        }
        if (strcmp(func, "add_book") == 0)
        {
            /* extragem datele pentru carte */
            char* name = strtok(NULL, ":\n\r");
            char* auth = strtok(NULL, ":\n\r");
            int rating = atoi(strtok(NULL, ":\n\r"));
            int nr_pag = atoi(strtok(NULL, ":\n\r"));
            /* alocam memorie pentru carte */
            Info* carte = (Info* )malloc(sizeof(Info));
            if (carte == NULL)
                return 0;
            strcpy(carte->autor, auth);
            strcpy(carte->titlu, name);
            carte->rating = rating;
            carte->nr_pag = nr_pag;
            /* inseram cartea in T1 si in T2 */
            InserT1(Trie1, carte);
            InserT2(Trie2, carte);
            continue;
        }
        if (strcmp(func, "search_book") == 0)
        {
            char* titlu = strtok(NULL, ":\n\r");
            if (titlu[strlen(titlu) - 1] == '~')
            {
                continue;
            }
            else
            {
                int ok = cautaT1(Trie1, titlu, g);
                if (ok == 0)
                    fprintf(g, "Cartea %s nu exista in recomandarile tale.\n", 
                            titlu);
            }
            continue;
        }
        if (strcmp(func, "list_author") == 0)
        {
            char* autor = strtok(NULL, ":\n\r");
            int ok = cautaT2(Trie2, autor, g);
            if (ok == 0)
                fprintf(g, "Autorul %s nu face parte din recomandarile tale.\n",
                        autor);
            continue;
        }
        if (strcmp(func, "search_by_author") == 0)
        {
            char* autor = strtok(NULL, ":\n\r");
            char* titlu = strtok(NULL, ":\n\r");
            int ok = search_author(Trie2, autor, titlu, g);
            if (ok == 0)
                fprintf(g, "Autorul %s nu face parte din recomandarile tale.\n",
                        autor);
            if (ok == -1)
                 fprintf(g, "Cartea %s nu exista in recomandarile tale.\n", 
                            titlu);
            continue;
        }
    }
    return 0;
}