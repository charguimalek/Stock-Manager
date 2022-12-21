#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct date
{
    int j, m, a;
} date;
typedef struct produit
{
    int code, prix;
    char nom[30], desc[50];
    struct date de, ds;

} produit;
int c, y;
void application()
{

    printf("1-gestion des produit \n%n");
    printf("2-affichage du stock \n");
    printf("3-l'historique des entrees et des sorties\n");
    printf("4-quitter\n ");
    printf("merci du choisir la commande \n");
    scanf("%d", &c);
    commande(c);
}
void commande(int x)
{
    switch (x)
    {
    case 1:
        g_produit();
        break;
    case 2:
        stock();
        break;
    case 3:
        hestorique();
        break;
    case 4:
        return 0;
    default:
        printf("erreur");
        return 0;
    }
}
void g_produit()
{
    printf("1/Ajouter un produit\n");
    printf("2/Afficher la description d\'un produit\n");
    printf("3/Modifier un produit\n");
    printf("4/Supprimer un produit\n");
    printf("5/Recherche d\'un produit dans le stock\n");
    printf("6/retour\n");
    printf("merci du choisir la commande \n");
    scanf("%d", &c);
    pro(c);
}

void pro(int x)
{
    if (x == 1)
    {
        ajouter() ;
    }
    else if (x == 2)
    {

        printf("donner le code du produit \n");
        scanf("%d", &y);
        produit prd;
        FILE *file;
        file = fopen("produit.txt", "r");
        int nbr = 0, i = 0;
        while (fread(&prd, sizeof(struct produit), 1, file))
            if (prd.code == y)
                puts(prd.desc);

        fclose(file);
    }
    else if (x == 3)
    {
        Modifier();
    }
    else if (x == 4)
    {
        supprimer();
    }
    else if (x == 5)
    {

        printf("donner le code du produit \n");
        scanf("%d", &y);
        Recherche(y);
    }
    else if (x == 6)
    {
        application();
    }
}
void ajouter()
{
        produit prd;
        produit prd0 ;
        FILE *file;
        FILE *fl;
        printf("code du produit\n");
        scanf("%d", &prd.code);
        fl=fopen("produit.txt","r");
        int found =0 ;
        while (fread(&prd0, sizeof(struct produit), 1, fl)){
            if(prd0.code==prd.code)
                found=1 ;
        }
         if  (found == 1){
            printf("ce code est deja utiliser  \n");
            ajouter() ;
            }
        printf("prix de produit\n");
        scanf("%d", &prd.prix);

        do
        {
            printf("date d\'entree j/m/a\n");
            scanf("%d%d%d", &prd.de.j, &prd.de.m, &prd.de.a);
        } while (((prd.de.j > 31) && (0 > prd.de.j)) || ((prd.de.m > 13) && (prd.de.m < 0)) || (prd.de.a < 1999));
        do
        {
            printf("date de sortie j/m/a\n");
            scanf("%d%d%d", &prd.ds.j, &prd.ds.m, &prd.ds.a);
        } while (((prd.ds.j < 31) && (0 > prd.ds.j)) || ((prd.ds.m > 13) && (prd.ds.m < 0)) || (prd.ds.a < 1999));
        fflush(stdin);
        printf("nom du produit\n");
        fgets(prd.nom, 20, stdin);
        printf("description du produit\n");
        fgets(prd.desc, 50, stdin);
        file = fopen("produit.txt", "a");
        fwrite(&prd, sizeof(struct produit), 1, file);

        if (fwrite != 0)
            printf("produit ajoute avec succee");
        else
            printf("erreur");
        fclose(file);
}
void Modifier()
{
    produit prd1;
    produit prd;
    FILE *file;
    printf("code du produit\n");
    scanf("%d", &prd1.code);
    printf("prix de produit\n");
    scanf("%d", &prd1.prix);

    do
    {
        printf("date d\'entree j/m/a\n");
        scanf("%d%d%d", &prd1.de.j, &prd1.de.m, &prd1.de.a);
    } while (((prd1.de.j > 31) && (0 > prd1.de.j)) || ((prd1.de.m > 13) && (prd1.de.m < 0)) || (prd1.de.a < 1999));
    do
    {
        printf("date de sortie j/m/a\n");
        scanf("%d%d%d", &prd1.ds.j, &prd1.ds.m, &prd1.ds.a);
    } while (((prd1.ds.j < 31) && (0 > prd1.ds.j)) || ((prd1.ds.m > 13) && (prd1.ds.m < 0)) || (prd1.ds.a < 1999));
    fflush(stdin);
    printf("nom du produit\n");
    fgets(prd1.nom, 20, stdin);
    printf("description du produit\n");
    fgets(prd1.desc, 50, stdin);
    file = fopen("produit.txt", "r");
    int nbr = 0, i;
    produit p[100];
    while (fread(&prd, sizeof(struct produit), 1, file))
    {
        p[nbr] = prd;
        nbr++;
    }
    fclose(file);
    remove("produit.txt");
    FILE *nvfile;
    nvfile = fopen("nvproduit", "a");
    for (i = 0; i < nbr; i++)
    {
        if (p[i].code == prd1.code)
            fwrite(&prd1, sizeof(struct produit), 1, nvfile);
        else
            fwrite(&p[i], sizeof(struct produit), 1, nvfile);
    }
    fclose(nvfile);
    rename("nvproduit", "produit.txt");
}
void Recherche(int x)
{
    struct produit prd1;
    FILE *file;
    produit p[30];
    file = fopen("produit.txt", "r");
    int nbrp = 0, i;
    while (fread(&prd1, sizeof(struct produit), 1, file))
        p[nbrp] = prd1;
    nbrp++;
    fclose(file);
    for (i = 0; i < nbrp; i++)
    {
        if (p[i].code == x)
        {
            printf("le nom de produit est ");
            puts(p[i].nom);
            printf("le prix est %d\n", p[i].prix);
            printf("date d\'entree %d/%d/%d\n", p[i].de.j, p[i].de.m, p[i].de.a);
            printf("date de sortie %d/%d/%d\n", p[i].ds.j, p[i].ds.m, p[i].ds.a);
            printf("description est ");
            puts(p[i].desc);
        }
        else
            printf("n'existe pas  ");
    }
}
void supprimer()
{
    int code;
    produit prd;
    FILE *file;
    printf("code du produit\n");
    scanf("%d", &code);
    file = fopen("produit.txt", "r");
    int nbr = 0, i;
    produit p[100];
    while (fread(&prd, sizeof(struct produit), 1, file))
    {
        p[nbr] = prd;
        nbr++;
    }
    fclose(file);
    remove("produit.txt");
    FILE *nvfile;
    nvfile = fopen("nvproduit", "a");
    for (i = 0; i < nbr; i++)
    {
        if (p[i].code != code)
            fwrite(&p[i], sizeof(struct produit), 1, nvfile);
    }
    fclose(nvfile);
    rename("nvproduit", "produit.txt");
    printf("produit est supprime");
}
void stock()
{
    produit prd1, p[30];
    FILE *file;
    int nbrp = 0, i;
    file = fopen("produit.txt", "r");
    while (fread(&prd1, sizeof(struct produit), 1, file))
    {
        p[nbrp] = prd1;
        nbrp++;
    }
    fclose(file);
    for (i = 0; i < nbrp; i++)
    {
        printf("produit numero %d\n", i + 1);
        printf("code de produit %d\n", p[i].code);
        printf("le nom de produit est ");
        puts(p[i].nom);
        printf(" prix est %d\n", p[i].prix);
        printf(" date d\'entree %d/%d/%d\n", p[i].de.j, p[i].de.m, p[i].de.a);
        printf(" date de sortie %d/%d/%d\n", p[i].ds.j, p[i].ds.m, p[i].ds.a);
        printf(" description est ");
        puts(p[i].desc);
    }
}
void hestorique()
{
    int jour, mois;
    produit prd1, p[30];
    FILE *file;
    int nbrp = 0, i;
    file = fopen("produit.txt", "r");
    while (fread(&prd1, sizeof(struct produit), 1, file))
    {
        p[nbrp] = prd1;
        nbrp++;
    }
    fclose(file);
    printf("donner le jour ");
    scanf("%d", &jour);
    for (i = 0; i < nbrp; i++)
    {
        if (p[i].de.j == jour)
        {
            printf("c'est l\'entree du produit \n%s", p[i].nom);
        }
        else if (p[i].ds.j == jour)
            printf("cest la sortie du produit\n %s", p[i].nom);
    }
    printf("donner le mois ");
    scanf("%d", &mois);
    printf("dans le mois num \n");
    for (i = 0; i < nbrp; i++)
    {
        if (p[i].de.j == jour)
        {
            printf("c'est l\'entree du produit%s\n", p[i].nom);
        }
        else if (p[i].ds.j == jour)
            printf("cest la sortie du produit %s\n", p[i].nom);
    }
}
int main()
{
    application();

    return 0;
}
