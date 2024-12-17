#  Projet polynômes

Ce projet est une application console en langage C permettant de manipuler des polynômes. Vous pouvez effectuer différentes opérations telles que l'affichage, l'addition, la soustraction, la multiplication, et bien d'autres.

## Fonctionnalités

- **Enregistrer des polynômes** : Permet de saisir deux polynômes P(x) et Q(x).
- **Afficher des polynômes** : Affiche les polynômes enregistrés.
- **Ordonner les polynômes** : Trie les termes d'un polynôme par ordre croissant de degré.
- **Addition et soustraction** : Calcule la somme et la différence de deux polynômes.
- **Multiplication** : Multiplie deux polynômes ou un polynôme par une constante.
- **Calcul des racines** : Trouve les racines des polynômes de degré ≤ 2.
- **Édition** : Permet de modifier les termes d'un polynôme.

## Prérequis

Avant d'exécuter ce projet, vous devez avoir installé un compilateur C (comme GCC).

### Installer les dépendances

1. Clonez ce repository sur votre machine locale :
   ```bash
   git clone https://github.com/votre-nom-d'utilisateur/manipulation-polynomes.git
   ```

2. Accédez au dossier du projet :
   ```bash
   cd manipulation-polynomes
   ```

3. Compilez le projet avec **GCC** :
   ```bash
   gcc main.c -o polynome
   ```

## Utilisation

1. Une fois l'installation terminée, vous pouvez exécuter le programme en lançant le fichier compilé :
   ```bash
   ./polynome
   ```

2. Un menu interactif s'affichera avec les options suivantes :
   - Enregistrer un polynôme.
   - Afficher les polynômes.
   - Ordonner les polynômes.
   - Effectuer une somme.
   - Effectuer une soustraction.
   - Multiplier des polynômes.
   - Calculer les racines d'un polynôme.
   - Multiplier un polynôme par une constante.
   - Modifier un polynôme.
   - Quitter le programme.

3. Vous pouvez interagir avec le programme en sélectionnant l'une des options et en suivant les instructions à l'écran.

## Exemple de code pour additionner deux polynômes

Voici un extrait de code qui montre comment la fonction d'addition de polynômes est implémentée :

```c
void AddPolynome(Polynome *P, Polynome *Q, Polynome *R) {
    Polynome *current;
    Monome M;
    // Ajouter les monomes de P dans R
    current = P;
    while (current != NULL) {
        M.coef = current->coef;
        M.deg = current->deg;
        R = InsertPolyOrd(R, M);
        current = current->suivant;
    }

    // Ajouter les monomes de Q dans R
    current = Q;
    while (current != NULL) {
        M.coef = current->coef;
        M.deg = current->deg;
        R = InsertPolyOrd(R, M);
        current = current->suivant;
    }
}
```

### Explication :
- Cette fonction prend deux polynômes **P** et **Q** et les additionne terme par terme, en insérant les résultats dans un troisième polynôme **R**.

## Exemple d'interface

Le programme fonctionne en ligne de commande et affiche les polynômes sous la forme suivante :
```
P(x) = 2x^3 + 3x^2 - 4x + 5
Q(x) = x^2 - 3x + 2
```

Ensuite, l'utilisateur peut effectuer des opérations comme l'addition ou la multiplication sur ces polynômes.

## Contribuer

Si vous souhaitez contribuer à ce projet, vous pouvez le forker et soumettre une pull request. Voici les étapes pour contribuer :

1. Forkez ce projet en cliquant sur le bouton "Fork" en haut à droite de la page GitHub.
2. Créez une branche pour vos modifications :
   ```bash
   git checkout -b feature-nouvelle-fonctionnalité
   ```
3. Committez vos changements :
   ```bash
   git commit -am 'Ajout d\'une nouvelle fonctionnalité'
   ```
4. Poussez vos modifications :
   ```bash
   git push origin feature-nouvelle-fonctionnalité
   ```
5. Ouvrez une pull request pour que vos changements soient examinés.

---

## Aide et Support

Je suis toujours present pour les conseils d'ameliorationde ce mini projet, n'hésitez pas à ouvrir une **issue** sur GitHub ou à me contacter directement.
