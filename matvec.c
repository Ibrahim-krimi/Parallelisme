#include "matvec.h"

/**********
 * matvec *
 **********/

void
matvec(const float A[], const float x[], float b[], const unsigned size) {

  // Accumulateur permettant de calculer la composante b[i].
  float acc;

  // Boucle sur les lignes de la matrice.
  for (unsigned i = 0; i < size; i ++) {

    // Initialisation de l'accumulateur.
    acc = 0.0;

    // Boucle sur les colonnes de la matrice.
    for (unsigned k = 0; k < size; k ++) { 
      acc += A[i * size + k] * x[k];  
    }

    // C'est terminé pour b[i].
    b[i] = acc;
 
  }
  
}
