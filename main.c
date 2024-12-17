#include<stdio.h>
#include"polynome.h"

#define QUITTER 10

int main()
{
    int choix;

    while ((choix = choixMenu()) != QUITTER)
    {
        switch (choix)
        {
        case 1:
            EntrerPolynome();
            break;
        case 2:
            AfficherPolynome();
            break;
        case 3:
            OrdonnerPolynome();
            break;
        case 4:
            SommerPolynome();
            break;
        case 5:
            SoustrairePolynome();
            break;
        case 6:
            MultiplicationPolynome();
            break;
        case 7:
            RacinePolynome();
            break;
        case 8:
            MultiplierPolynomeParConstante();
            break;
        case 9:
            EditerPolynome();
            break;
        default:
            printf("Le choix entre est invalide");
            break;
        }
    }

    return 0;
}