#include <stdio.h>
#include <stdlib.h>
#include "include/raylib.h"

typedef struct liste liste;
struct liste {
    int v;
    liste* suiv;
};

liste* creer_noeud() {
    liste* nouveau_noeud = (liste*)malloc(sizeof(liste));
    return nouveau_noeud;
}

void CreerListe_Tete(liste** Tete, int n) {
    liste* nouv;
    int v;

    for (int i = 0; i < n; i++) {
        printf("Entrez la valeur du noeud %d : ", i + 1);
        scanf("%d", &v);

        nouv = creer_noeud();

        if (nouv != NULL) {
            nouv->v = v;
            nouv->suiv = *Tete;
            *Tete = nouv;
        }
    }
}

// Fonction pour supprimer un nœud après une position donnée
liste* supprimer(liste* tete, int position) {
    if (tete == NULL) {
        printf("La liste est vide.\n");
        return NULL;
    }

    if (position == 1) {
        // Supprimer la tête de la liste
        liste* new_debut = tete->suiv;
        free(tete);
        return new_debut;
    }

    liste* courant = tete;
    int i;

    // Parcourir la liste jusqu'à la position précédant le nœud à supprimer
    for (i = 1; i < position - 1 && courant != NULL; ++i) {
        courant = courant->suiv;
    }

    // Vérifier si la position est valide
    if (courant == NULL || courant->suiv == NULL) {
        printf("Position invalide.\n");
        return tete;
    }

    // Supprimer le nœud après la position donnée
    liste* element_a_supprimer = courant->suiv;
    courant->suiv = courant->suiv->suiv;
    free(element_a_supprimer);

    return tete;
}

liste* tri_par_selection(liste* tete) {
    liste *i, *j, *min;

    for (i = tete; i != NULL; i = i->suiv) {
        min = i;
        for (j = i->suiv; j != NULL; j = j->suiv) {
            if (j->v < min->v) {
                min = j;
            }
        }
        // Échanger les données des nœuds i et min
        int temp = i->v;
        i->v = min->v;
        min->v = temp;
    }

    return tete;
}

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Liste avec Raylib");

    liste* tete = NULL;

    CreerListe_Tete(&tete, 5);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Dessinez ici votre liste en utilisant DrawText ou d'autres fonctions de dessin Raylib

        EndDrawing();
    }

    CloseWindow();

    return 0;
}


