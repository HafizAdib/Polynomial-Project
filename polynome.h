// Inclusion des bibliotheques
#include<stdio.h>
#include<math.h>
#include<stdlib.h>


// Structures d'un Monome (un coef "coef" et un degre)
typedef struct Monome
{
    int coef, deg;
}Monome;

// Structures d'un Polynome (Une suite des monomes)
typedef struct Polynome 
{
    int coef, deg;
    struct Polynome *suivant;
}Polynome;

// Les variables GLOBALES
Polynome *P, *Q, *R;

// La fonction choixMenu
int choixMenu()
{
    int choix;
    system("cls");
    printf("\n Le Programme permet de manipuler les POLYNOMES \n\t1:  Enregistrer un polynome\n\t2:  Afficher un polynome\n\t3:  Ordonner un polynome\n\t4:  Sommer deux un polynome\n\t5:  Soutraire des un polynome\n\t6:  Multiplier des  polynome\n\t7:  Trouver les racines d'un polynome\n\t8:  Multiplier un polynome par une constante\n\t9:  Modifier un polynome\n\t10: Quitter le programme\nEntrez votre choix: ");
    scanf("%d", &choix);
    return choix;
}

// les fontions internes

// La fonction insert un monome a la queue d'un polynome
Polynome * InsertQueue(Polynome *P, Monome M)
{
    Polynome *newPoly = (Polynome *)malloc(sizeof(Polynome));
    if (newPoly == NULL) {
        printf("Erreur d'allocation memoire\n");
        return NULL;
    }

    newPoly->coef = M.coef;
    newPoly->deg = M.deg;
    newPoly->suivant = NULL;

    if (P == NULL) {
        P = newPoly; // Premier monome
    } else {
        Polynome *current = P;
        while (current->suivant != NULL) {
            current = current->suivant;
        }
        current->suivant = newPoly; // Ajout a la fin
    }
    return P;
}

// La fonction prend un polynome en entre et insert les elements
Polynome * LirePolynome(Polynome *P)
{
    Monome M;
    printf("\nEntrez les monomes du polynome (les coefficients et les degres. \nEntrez un degre negatif pour arreter");

    printf("\nDegre du monome : ");
    scanf("%d", &M.deg);

    while (M.deg >= 0)    
    {
        printf("\ncoef du monome : ");
        scanf("%d", &M.coef);
        
        P = InsertQueue(P, M);

        printf("\nDegre du monome : ");
        scanf("%d", &M.deg);
    }
    return P;    
}

// La procedure prend en entre un polynome et l'affiche a l'ecran
void AfficherPolynomeEntre(Polynome *P)
{
    if (P == NULL) {
        printf("Le polynome est vide.\n");
        return;
    }

    Polynome* temp = P;
    while (temp != NULL) {
        // Afficher le signe si c'est pas la tete
        if (temp->coef > 0 && temp != P) {
            printf(" + ");
        } else  if (temp->coef < 0) {
            printf(" - ");
        }

        // Gerer le coef absolu (sans le signe dans certains cas)
        if (temp->coef != 1 && temp->coef != -1 || temp->deg == 0) {
            printf("%d", abs(temp->coef));
        }

        // Afficher l'exposant
        if (temp->deg != 0) {
            printf("x");
            if (temp->deg > 1) {
                printf("^%d", temp->deg);
            }
        }

        temp = temp->suivant;
    }
    printf("\n");
}

// La procedure prend en entre un monome et l'affiche a l'ecran
void afficherMonome(Monome M) {
    
    // Cas ou le coefficient est nul
    if (M.coef == 0) {
        printf("0\n");
        return;
    }

    // Cas ou le degre = 0
    if (M.deg == 0) {
        // Monôme constant : affichage de "a"
        printf("%d\n", M.coef);
    }
    // Cas ou le deg = 1
    else if (M.deg == 1) {
        // Monôme de degre 1 : affichage de "ax"
        if (M.coef == 1) {
            printf("x\n");
        } else if (M.coef == -1) {
            printf("-x\n");
        } else {
            printf("%dx\n", M.coef);
        }
    } 
    // Monôme de degre superieur a 1 : affichage de "ax^n"
    else {
        if (M.coef == 1) {
            printf("x^%d\n", M.deg);
        } else if (M.coef == -1) {
            printf("-x^%d\n", M.deg);
        } else {
            printf("%dx^%d\n", M.coef, M.deg);
        }
    }
}

// La fonction prend en entre un monome et l'affiche a l'ecran
/* void AfficherMonome(Monome M)
{
        if(M.coef != 0 && M.deg == 0)
            printf("%d",M.coef);
        else
            if(M.deg == 1)
                if(M.coef == 1 )
                    printf("x ");
                else
                    if(M.coef == -1)
                        printf("-x ");
                    else
                        if(M.coef != 0)
                            printf("%d x",M.coef);
            else
                if(M.coef == 1)
                    printf("x^%d",M.deg);
                else
                    if(M.coef == -1)
                        printf("-x^%d",M.deg);
                    else
                        if(M.coef != 0)
                            printf("%dx^%d",M.coef,M.deg);
}

 */// La fonction prend en entre un monome et l'insert dans un polynome et le retourner

Polynome *InsertPolyOrd(Polynome *P, Monome M)
{
    Polynome *q; // Nouveau nœud temporaire

    // Cas où la liste est vide, creation du premier polynome
    if (P == NULL)
    {
        P = (Polynome *)malloc(sizeof(Polynome));
        if (P == NULL)
        {
            printf("Erreur d'allocation memoire.\n");
            exit(EXIT_FAILURE);
        }
        P->coef = M.coef;
        P->deg = M.deg;
        P->suivant = NULL;
        return P;
    }
    
    // Cas où le monome M a un degre plus grand, insertion au debut
    if (M.deg > P->deg)
    {
        q = (Polynome *)malloc(sizeof(Polynome));
        if (q == NULL)
        {
            printf("Erreur d'allocation memoire.\n");
            exit(EXIT_FAILURE);
        }
        q->coef = M.coef;
        q->deg = M.deg;
        q->suivant = P;
        return q; // Le nouveau nœud devient la nouvelle tete
    }
    
    // Cas où les degres sont egaux, addition des coefficients
    if (M.deg == P->deg)
    {
        P->coef += M.coef;
        return P;
    }
    
    // Cas où le degre de M est plus petit, insertion recursive
    P->suivant = InsertPolyOrd(P->suivant, M);
    return P; // Retour de la tete mise a jour
}

// La fonction prend en entre un polynome et le retourne ordonne
Polynome *OrdPolynome(Polynome *P)
{

    Polynome* temp = P, *p = NULL;
    Monome M;
    while (temp != NULL) {
        M.coef = temp->coef;
        M.deg = temp->deg;
        p = InsertPolyOrd(p, M);
        temp = temp->suivant;
    }

    return p;
}

// La fonction prend deux polynomes P et Q et les sommes tout en retournant le R dans R
void AddPolynome(Polynome *P, Polynome *Q, Polynome *R)
{
    Polynome *current;
    Monome M;

    // Verifier si l'un ou les deux polynomes est NULL
    if (P == NULL && Q == NULL)
    {
        printf("\nVous n'avez pas enregistre les deux polynomes.");
    }
    else if (P == NULL || Q == NULL)
    {
        printf("\nVous n'avez pas enregistre l'un des polynomes.");
    }
    else
    {
        // Initialiser R comme une liste vide (si R est NULL au debut)
        R = NULL;

        // Ajouter les monomes de P dans R
        current = P;
        while (current != NULL)
        {
            M.coef = current->coef;
            M.deg = current->deg;
            R = InsertPolyOrd(R, M);
            current = current->suivant;
        }

        // Ajouter les monomes de Q dans R
        current = Q;
        while (current != NULL)
        {
            M.coef = current->coef;
            M.deg = current->deg;
            R = InsertPolyOrd(R, M); 
            current = current->suivant;
        }
    }

    // Affichage des polynomes
    printf("\nP(x) = ");
    AfficherPolynomeEntre(P);
    printf("\nQ(x) = ");
    AfficherPolynomeEntre(Q);
    printf("\nP(x) + Q(x) = ");
    AfficherPolynomeEntre(R);

    // Pause et nettoyage de l'ecran
    system("Pause");
    system("cls");
}

// La fonctiion prend trois polynomes P, Q et R et renvoie R qui est la difference de P et Q 
Polynome * SoustractionPolynome(Polynome* P, Polynome* Q, Polynome* R)
{
    // Polynome courant
    Polynome* temp;     
    // Monome temporaire
    Monome M;           
    
    // Verifier si l'un ou les deux polynomes est NULL
    if (P == NULL && Q == NULL)
    {
        printf("\nVous n'avez pas enregistre les deux polynomes.");
        return NULL;
    }
    else if (P == NULL || Q == NULL)
    {
        printf("\nVous n'avez pas enregistre l'un des polynomes.");
        return NULL;
    } 
    else
    {
        // Initialiser R a NULL
        R = NULL;
        
        while (P != NULL || Q != NULL) 
        {
            // Cas où P n'est pas NULL et Q est NULL ou le degre de P est inferieur a celui de Q
            if (P != NULL && (Q == NULL || P->deg < Q->deg)) 
            {
                // On copie directement le monome de P
                M.coef = P->coef;
                M.deg = P->deg;
                P = P->suivant;
            }

            // Cas où Q n'est pas NULL et P est NULL ou le degre de Q est inferieur a celui de P
            else if (Q != NULL && (P == NULL || Q->deg < P->deg)) 
            {
                // On copie directement le monome de Q avec changement de signe du coef
                M.coef = -Q->coef;
                M.deg = Q->deg;
                Q = Q->suivant;
            }

            // Cas où P et Q ne sont pas NULL et leurs monomes on le meme degre
            else 
            {
                // Les deux monomes ont le meme degre on fait la difference entre P->coef et Q->coef
                M.coef = P->coef - Q->coef;
                M.deg = P->deg;
                P = P->suivant;
                Q = Q->suivant;
            }

            // On ajoute le monome(M) au R(R) si son coefficient n'est pas NULL
            if (M.coef != 0) 
            {
                R = InsertPolyOrd(R, M);
            }
        }

        // Renvoi du polynome resultante
        return R;

        // Pause et nettoyage de l'ecran
        system("Pause");
        system("cls");
    } 
}

// La fonction retourne un polynmone resultant de P*Q
Polynome* Multiplication2Polynome()
{
    Polynome *C1, *C2;
    Monome M1, M2;
    
    // On verifie si l'un des polynomes est NULL
    if (P == NULL || Q == NULL) 
    {
        printf("\nMultiplication impossible car l'un des polynomes est vide.\n");
        return NULL;
    }

    C1 = P;
    // On s'assure que R est initialise a NULL avant de commencer
    R = NULL; 

    while (C1 != NULL)
    {
        M1.coef = C1->coef;
        M1.deg = C1->deg;

        // On reinitialise C2 a Q pour chaque iteration de monome de C1
        C2 = Q; 
        while (C2 != NULL)
        {
            M2.coef = M1.coef * C2->coef;
            M2.deg = M1.deg + C2->deg;
            // On insere M2 dans le polynome R dans l'ordre croissant des degres
            R = InsertPolyOrd(R, M2); 
            C2 = C2->suivant;
        }
        C1 = C1->suivant;            
    }
    //On retourne le resultat de la multiplication
    return R;
}

// La fonction prend en parametre un polynome P et et une constante k et retourne k*P
Polynome* MultiplieParConstante(Polynome* poly, int constante)
{
    if (poly == NULL) 
    {
        printf("Le polynome est vide.\n");
        return NULL;
    }

    Polynome* resultat = NULL;
    Polynome* temp = poly;
    Polynome* courant = NULL;

    while (temp != NULL) 
    {
        // Creation d'un nouveau nœud
        Polynome* nouveau = (Polynome*)malloc(sizeof(Polynome));
        nouveau->coef = temp->coef * constante;
        nouveau->deg = temp->deg;
        nouveau->suivant = NULL;

        // Ajout au resultat
        if (resultat == NULL) 
        {
            resultat = nouveau;
            courant = resultat;
        } 
        else 
        {
            courant->suivant = nouveau;
            courant = courant->suivant;
        }

        temp = temp->suivant;
    }

    return resultat;
}

// La procedure prend en entre une constante qu'elle multiplie P ou Q ou les deux en fonction du choix
void MultiplieurPolynomeParConstante(int constante, Polynome* R )
{
    int choix;
    printf("\nQuel polynome doit etre multiplie par une constante ? \n\t1 : P(x) \n\t2 : Q(x) \n\t3 : P(x) et Q(x)\nEntrez votre choix : ");
    scanf("%d", &choix);
    printf("\n");

    R = NULL;

    if (choix == 1) 
    {
        if (P == NULL) 
        {
            printf("Le polynome P(x) n'est pas defini.\n");
        } 
        else 
        {
            R = MultiplieParConstante(P, constante);
            printf("%d * P(x) = ", constante);
            AfficherPolynomeEntre(R);
            
            // Pause et nettoyage de l'ecran
            system("Pause");
        }
    } 
    else if (choix == 2) 
    {
        if (Q == NULL) 
        {
            printf("Le polynome Q(x) n'est pas defini.\n");
        } 
        else 
        {
            R = MultiplieParConstante(Q, constante);
            printf("%d * Q(x) = ", constante);
            AfficherPolynomeEntre(R);
            
            // Pause et nettoyage de l'ecran
            system("Pause");
        }
    } 
    else if (choix == 3)
    {
        // P(x)*k
        if (P == NULL) 
        {
            printf("Le polynome P(x) n'est pas defini.\n");
        } 
        else 
        {
            R = MultiplieParConstante(P, constante);
            printf("%d * P(x) = ", constante);
            AfficherPolynomeEntre(R);
        }

        // Q(x)*k
        if (Q == NULL) 
        {
            printf("Le polynome Q(x) n'est pas defini.\n");
        } 
        else 
        {
            R = MultiplieParConstante(Q, constante);
            printf("%d * Q(x) = ", constante);
            AfficherPolynomeEntre(R); 
        }
    }
    
    else 
    {
        printf("Choix invalide.\n");
    }
    
}

// La procedure prend les coefficients en entre d'un polynome et calcule la racine
void Racine(int a, int b, int c)
{
    int  D; 
    double x, x1, x2;

    // a = 0 => equation devient bx + c = 0
    if (a == 0) {
        // b = 0
        if (b == 0) {
            // c = 0 : infinite de solutions, sinon pas de solution
            if (c == 0) {
                // Infinite de solutions
                printf("Infinite de solutions\n");
            } 
            // c != 0
            else {
                // Pas de solution
                printf("Pas de solution\n");
            }
        } 
        // b != 0
        else {
            // bx + c = 0 => x = -c / b
            x = -(c / b); // Forcage de type en flottant
            printf("Solution unique : S = {%d}\n", x); // Affichage avec 2 chiffres apres la virgule
        }
    } 
    // a != 0 => ax^2 + bx + c
    else {
        // Calcul du discriminant : D = b^2 - 4*a*c
        D = b * b - 4 * a * c;

        // Delta > 0
        if (D > 0) {
            // Deux solutions
            x1 = (-b - sqrt(D)) / (2.0 * a);
            x2 = (-b + sqrt(D)) / (2.0 * a);
            printf("Deux solutions : S = {%d; %d}\n", x1, x2);
        } 
        // Delta = 0
        else if (D == 0) {
            // Solution unique
            x = -b / (2.0 * a);
            printf("Solution unique : S = {%d}\n", x);
        } 
        // Delta < 0 => Pas de solution dans R 
        else {
            printf("Pas de solution\n");
        }
    }
}

// La procedure prend les polynomes P et Q en entre et calcule leurs racines
void RacineP_Q(Polynome *P, Polynome *Q)
{
    int a, b, c;

    // Calcul de racine de P(x)
    if (P != NULL)
    {
        a = P->coef;
        b = P->suivant->coef;
        c = P->suivant->suivant->coef;
        // Affichage l'equation sous forme ax^2 + bx + c = 0
        printf("\n\nResolution de l'equation :\nP(x) = %dx^2 + %dx + %d = 0\n", a, b, c);

        Racine(a, b, c);
    }
    else
    {
        printf("Polynome P(x) vide\n");
    }
    
    // Calcul de racine de Q(x)
    if (Q != NULL)
    {
        // Recuperation des coefficients
        a = Q->coef;
        b = Q->suivant != NULL ?Q->suivant->coef : 0;
        c = Q->suivant->suivant != NULL ? Q->suivant->suivant->coef : 0;
        // Affichage l'equation sous forme ax^2 + bx + c = 0
        printf("\n\nResolution de l'equation :\nQ(x) = %dx^2 + %dx + %d = 0\n", a, b, c);

        Racine(a, b, c);
    }
    else
    {
        printf("Polynome Q(x) vide\n");
    }
}


// La fonction prend un polynome en entre pour le modifier puis le retourne
Polynome * Editer(Polynome *P)
{
    // Reenregistrement de P si NUL
    if (P == NULL)
    {
        printf("Le polynome est vide. \nVoulez vous modifier ? (Tapez 1 pour Oui ou 0 pour Non) : ");
        int c;
        scanf("%d",&c);

        if (c == 1)
        {
            P = LirePolynome(P);
        }
    }
    
    // Modification de P si non NUL
    else
    {
        Polynome *tmp = P;
        
        printf("Les modifications se fait Monome par Monome :\nSi vous ne modifiez pas un monome reecrivez les encienne valeurs du coefficient et du degre \n");
        while (tmp != NULL)
        {
            Monome M = {tmp->coef, tmp->deg};
            printf("\n M = ");
            afficherMonome(M);

            printf("\nVoulez vous modifier ? (Tapez 1 pour Oui ou 0 pour Non)");
            
            int c;
            scanf("%d",&c);

            if (c == 1)
            {
                int coef, deg;
                printf("\nEntrez le nouveau coefficient : ");
                scanf("%d", &coef);
                tmp->coef = coef;

                printf("\nEntrez le nouveau degre : ");
                scanf("%d", &deg);

                while (deg < 0)
                {
                    printf("le degre doit etre positif");
                    printf("\nEntrez le nouveau degre : ");
                    scanf("%d", &deg);
                }
                tmp->deg = deg;                
            }
            tmp = tmp->suivant;            
        }       
    }  

    return P;
}

// La procedure modifie les polynomes P ou Q ou les deux
void EditeurPolynome()
{
    int choix;
    printf("\nQuel polynome doit etre Modifie ? \n\t1 : P(x) \n\t2 : Q(x) \n\t3 : P(x) et Q(x)\nEntrez votre choix : ");
    scanf("%d", &choix);

    if (choix == 1) 
    {
        // Modifier P(x)        
        printf("P(x) = ");
        AfficherPolynomeEntre(P); 
        P = Editer(P);
    } 
    
    else if (choix == 2) 
    {
        // Modifier Q(x)
        printf("Q(x) = ");
        AfficherPolynomeEntre(Q); 
        Q = Editer(Q);
    } 
    
    else if (choix == 3)
    {
        // Modifier P(x)        
        printf("P(x) = ");
        AfficherPolynomeEntre(P); 
        P = Editer(P);
        
        // Modifier Q(x)
        printf("Q(x) = ");
        AfficherPolynomeEntre(Q); 
        Q = Editer(Q);
    } 
    
    else 
    {
        printf("Choix invalide.\n");
    }
    
}


// Les Macros (Modules)

void EntrerPolynome()
{
    system("cls");
    printf("Enregistrement des polynomes P(x) et Q(x) :\n\n");
    printf("Vous devez enregistrer 02 polynomes P et Q pour faire les operations affichees dans le Menu\n\n");
    P = Q = NULL;
    
    printf("\nLe polynome P(x) :\n");
    P = LirePolynome(P);

    printf("\nLe polynome Q(x) :\n");
    Q = LirePolynome(Q);

}

void AfficherPolynome()
{
    system("cls");    
    printf("\nAffichages des polynomes P et Q :\n");
    printf("\nP(x) = ");
    AfficherPolynomeEntre(P);
    printf("\nQ(x) = ");
    AfficherPolynomeEntre(Q);
    system("pause");
}

void ReduirePolynome()
{
    system("cls");
    AfficherPolynome();
}

void OrdonnerPolynome()
{
    system("cls");
    printf("\nAffichages des polynomes P et Q ordonnees :\n\n");
    
    printf("\nP(x) = ");
    P = OrdPolynome(P);
    AfficherPolynomeEntre(P);
    
    printf("\nQ(x) = ");
    Q = OrdPolynome(Q);
    AfficherPolynomeEntre(Q);
    
    system("pause");
}

void SommerPolynome()
{
    system("cls");

    printf("La somme des polynomes P et Q :\n\n");

    R = NULL;
    AddPolynome(P, Q, R);
}

void SoustrairePolynome()
{
    system("cls");
    printf("La difference des polynomes P et Q :\n\n");
    R = NULL;
    R = SoustractionPolynome(P, Q, R);

    printf("\nP(x) = ");
    AfficherPolynomeEntre(P);
    printf("\nQ(x) = ");
    AfficherPolynomeEntre(Q);
    
    if (R != NULL && P != NULL && Q != NULL)
    {
        printf("\nP(x) - Q(x) = ");
        AfficherPolynomeEntre(R);
    }
    system("pause");
}

void MultiplicationPolynome()
{
    system("cls");

    printf("Multiplication des polynomes P(x) et Q(x) :\n\n");

    printf("\nP(x) = ");
    AfficherPolynomeEntre(P);
    printf("\nQ(x) = ");
    AfficherPolynomeEntre(Q);

    R = Multiplication2Polynome();

    if((P != NULL && Q != NULL ) && R != NULL)
    {
        printf("\nP(x) * Q(x) = ");
        AfficherPolynomeEntre(R);
    }
    printf("\n");
    system("pause");
}

void RacinePolynome()
{
    system("cls");
    
    printf("Calcul des racines de P(x) et de Q(x) :\n\n");

    RacineP_Q(P, Q);

    system("pause");
}

void MultiplierPolynomeParConstante()
{
    system("cls");
    printf("Multiplication des polynomes par une constante : \n\n");
    
    int k;
    printf("Entrer la constante : ");
    scanf("%d", &k);
    
    MultiplieurPolynomeParConstante(k, R); 

    printf("\n");
    system("Pause");
    system("cls");
}

void EditerPolynome()
{
    system("cls");
    printf("Modification des polynomes :\n\n");
    EditeurPolynome();
    
    printf("/n");
    AfficherPolynome();
}