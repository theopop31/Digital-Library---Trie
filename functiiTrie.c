/* POPESCU Ioan Emanuel Theodor - 315CB */
#include "trie.h"

int indx(char c)
/* intoarce pozitia caracterului c in alfabet */
{
    char alf[69] = 
    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.-'?! ";
    int i;
    for (i = 0; i < 69; ++i)
        if (c == alf[i])
            return i;
    return 0;
}

T1 alocNod1()
/* aloca memorie pentru un nod te tip T1 */
{
    T1 aux = NULL;
    aux = (T1)malloc(sizeof(TNod1));
    if (aux == NULL)
    {
        printf("Eroare la alocare!\n");
        return NULL;
    }
    int i;
    aux->sf_cuv = 0;
    aux->carte = NULL;
    for (i = 0; i < MAX_ALF; ++i)
        aux->fii[i] = NULL;
    return aux;
}

T2 alocNod2()
/* aloca memorie pentru un nod te tip T2 */
{
    T2 aux = NULL;
    aux = (T2)malloc(sizeof(TNod2));
    if (aux == NULL)
    {
        printf("Eroare la alocare!\n");
        return NULL;
    }
    aux->info = NULL;
    aux->sf_cuv = 0;
    int i;
    for (i = 0; i < MAX_ALF; ++i)
        aux->fii[i] = NULL;
    return aux;
}

void InserT2(T2 a, Info* carte)
/* insereaza in arborele de tip T2 informatiile din carte */
{
    int l = strlen(carte->autor), i;
    T2 aux = a;
    /* inseram numele autorului in arborele de tip T2 */
    for (i = 0; i < l; ++i)
    {
        int j = indx(carte->autor[i]);
        /* litera i din numele autorlui nu exista in arbore asa ca o adaugam */
        if (aux->fii[j] == NULL)
            aux->fii[j] = alocNod2();
        aux = aux->fii[j];
    }
    /* marcam ultimul nod ca fiind sfarsitul numelui */
    aux->sf_cuv = 1;
    /* daca frunza corespunzatoare numelui autorului nu pointeaza catre un
        arbore de tip T1, il alocam */
    if (aux->info == NULL)
        aux->info = alocNod1();
    l = strlen(carte->titlu);
    T1 p = aux->info;
    /* inseram titlul cartii in arborele de tip T1 corespunzator autorului */
    for (i = 0; i < l; ++i)
    {
        int j = indx(carte->titlu[i]);
        /* litera i din titlu nu exista in arbore asa ca o adaugam */
        if (p->fii[j] == NULL)
            p->fii[j] = alocNod1();
        p = p->fii[j];
    }
    /* marcam ultimul nod ca fiind sfarsitul titlului */
    p->sf_cuv = 1;
    /* adaugam la ultimul nod informatiile legate de carte */
    p->carte = carte;

}

void InserT1(T1 a, Info* carte)
/* insereaza informatiile din carte in arborele de tip T1
    asemanator functiei de mai sus */
{
    int l = strlen(carte->titlu), i;
    T1 aux = a;
    for (i = 0; i < l; ++i)
    {
        int j = indx(carte->titlu[i]);
        if (aux->fii[j] == NULL)
            aux->fii[j] = alocNod1();
        aux = aux->fii[j];
    }
    aux->sf_cuv = 1;
    aux->carte = carte;
}

int cautaT1(T1 a, char* titlu, FILE* g)
/* returneaza 1 daca am gasit titlui in arbore si 0 in caz contrar */
{
    /* arborele este vid */
    if (a == NULL)
        return 0;
    int l = strlen(titlu), i;
    T1 aux = a;
    /* parcurgem arborele prin nodurile corespunzatoare literelor din titlu */
    for (i = 0; i < l; ++i)
    {
        int j = indx(titlu[i]);
        /* daca nu am gasit una din litere ne oprim */
        if (aux->fii[j] == NULL)
            return 0;
        aux = aux->fii[j];
    }
    /* daca am ajuns la sfarsitul unui cuvant valid afisam si returnam 1 */
    if (aux != NULL && aux->sf_cuv == 1)
    {
        char titlu[MAX_TITLE], autor[MAX_AUTH];
        int rat = aux->carte->rating;
        int nrp = aux->carte->nr_pag;
        strcpy(titlu, aux->carte->titlu);
        strcpy(autor, aux->carte->autor);
        fprintf(g, "Informatii recomandare: %s, %s, %d, %d\n", titlu, autor,
        rat, nrp);
        return 1;
    }
    return 0;
}

void afisTrieT1(T1 a, char s[], int niv, FILE* g)
/* afiseaza recursiv continutul unui arbore de tip T1 */
{
    /* arborele este vid */
    if (a == NULL)
        return;
    /* daca am ajuns la finalului unui cuvant afisam ce am parcurs */
    if (a->sf_cuv == 1)
    {
        s[niv] = 0;
        fprintf(g, "%s\n", s);
    }
    int i;
    char alf[69] = 
    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.-'?! ";
    /* parcurgem arborele */
    for (i = 0; i < MAX_ALF; ++i)
    {
        /* daca exista fiul i, adaugam litera corespunzatoare lui din alfabet
            si parcurgem recursiv mai departe la fii acestui nod */
        if (a->fii[i] != NULL)
        {
            s[niv] = alf[i];
            afisTrieT1(a->fii[i], s, niv + 1, g);
        }
    }
}

int cautaT2(T2 a, char* autor, FILE* g)
/* returneaza 1 daca autorul a fost gasit in arbore sau 0 in caz contrar */
{
    int l = strlen(autor), i;
    T2 aux = a;
    for (i = 0; i < l; ++i)
    {
        int j = indx(autor[i]);
        if (aux->fii[j] == NULL)
            return 0;
        aux = aux->fii[j];
    }
    /* am gasit autorul asa ca apelam afisarea arborelui corespunzator
        frunzei sale */
    if (aux != NULL && aux->sf_cuv == 1)
    {
        char s[MAX_ALF + 2];
        int niv = 0;
        afisTrieT1(aux->info, s, niv, g);
        return 1;
    }
    return 0;
}

int search_author(T2 a, char* autor, char* titlu, FILE* g)
/* returneaza 0 daca nu am gasit autorul in T2, -1 daca nu am gasit titlul
    in T1, sau 1 daca am gasit autorul si titlul cautati */
{
    int l = strlen(autor), i;
    T2 aux = a;
    for (i = 0; i < l; ++i)
    {
        int j = indx(autor[i]);
        if (aux->fii[j] == NULL)
            return 0;
        aux = aux->fii[j];
    }
    
    if (aux != NULL && aux->sf_cuv == 1) /* am gasit numele autorului */
    {
        l = strlen(titlu);
        T1 p = aux->info;
        for (i = 0; i < l; ++i)
        {
            int j = indx(titlu[i]);
            if (p->fii[j] == NULL)
                return -1;
            p = p->fii[j];
        }
        if (p != NULL && p->sf_cuv == 1) /* am gasit titlul */
        {
            int rat = p->carte->rating;
            int nrp = p->carte->nr_pag;
            fprintf(g, "Informatii recomandare: %s, %s, %d, %d\n",
                    titlu, autor, rat, nrp);
            return 1;
        }
        return -1;
    }
    return 0;
}

