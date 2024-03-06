#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_LENGTH 10
#define MAX_LENGTH8PASS 8

int autoIdEtudiant = 10;
int autoIdAdmin = 0;
//------------------------------ Structure ------------------------------
typedef struct
{
    int j, m, a;

} DATE;

struct Utilisateur {
    char nom[MAX_LENGTH];
    char role[MAX_LENGTH];
};


typedef struct {
    char nomFichier[100];
    FILE *fichier;
} File;

typedef struct {
    int id;
    char nom[50];
    char prenom[50];
    char matricule[10];
    DATE dateNaissance;
    char presence[31]; //présent / abscent
    char messages[1000]; // 
    int nbMessages;
    int etat;
    char classe[5];
    int cumulretard; // quota maximal d'absences avant renvoi, paramétrable
    int nbAbsences;
} Etudiant;


//------------------------------------------------------ Prototype ---------------------------------------------------------
void genererMatricule  (char matricule[10], Etudiant etudiant);

//--------------------------------------------------------- Main -----------------------------------------------------------
int main () {

    char nom[MAX_LENGTH8PASS];
    char motdepasse[MAX_LENGTH8PASS];
    int taille = 0;

    printf("Nom d'utilisateur : ");
    scanf("%s", nom);
    printf("Mot de passe : ");
    scanf("%s", motdepasse);




    FILE *fichier;
    char texte[100];

    // Ouvrir le fichier en écriture
    fichier = fopen("apprenant.txt", "w");

    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier.");
        return 1;
    }

    // Demander à l'utilisateur d'entrer du texte
    printf("Entrez du texte (max 100 caracteres) : ");
    scanf("%s", texte);

    // Écrire le texte dans le fichier
    fprintf(fichier, "%s", texte);

    // Fermer le fichier
    fclose(fichier);

    printf("Le texte a ete ecrit dans le fichier.\n");

    return 0;
}


//--------------------------------------------------------- Functions -------------------------------------------------------
DATE saisiedate(void)
{
    DATE d;
    printf("Entrez votre date de naissance: \n");
    printf("Jour : ");
    scanf("%d", &d.j);
    printf("Mois : ");
    scanf("%d", &d.m);
    printf("Annee : ");
    scanf("%d", &d.a);
    return d;
}

int verifierConnexion(char *nom, char *motdepasse, struct Utilisateur *utilisateurs, int taille) {
    for (int i = 0; i < taille; i++) {
        if (strcmp(nom, utilisateurs[i].nom) == 0 && strcmp(motdepasse, utilisateurs[i].role) == 0) {
            return 1; // Connexion réussie
        }
    }
    return 0; // Connexion échouée
}

Etudiant saisirEtudiant(){
    Etudiant e;
    int taille = 10;
    e.id = ++ autoIdEtudiant;
    genererMatricule(e.matricule, e);
    puts("Donnez le nom :");
    scanf("%s", e.nom);
    puts("Donnez le prénom :");
    scanf("%s", e.prenom);
    e.dateNaissance = saisiedate();
    return e;
}

void genererMatricule  (char matricule[10], Etudiant etudiant) {
    //matricule ex: MAT-PM0001 (MAT-1èrelettre prénom+1èrelettre nom + id)
    sprintf(matricule,"MAT-%c%c%04d", toupper(etudiant.prenom[0]), toupper(etudiant.nom[0]), etudiant.id);
}

// Création des fichiers pour stocker les identifiants
    