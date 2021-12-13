#include "matvec_omp_for_j2.h"

/*********************
 * matvec_omp_for_j2 *
 *********************/

void
matvec_omp_for_j2(const float A[],
                  const float x[],
                  float b[],
                  const unsigned size) {

  // Accumulateur permettant de calculer la composante b[i].
  float acc;

#pragma omp parallel
  {
    
    // Boucle sur les lignes de la matrice.
    for (unsigned i = 0; i < size; i ++) {

      // Initialisation de l'accumulateur par le premier thread arrivé.
#pragma omp single
      acc = 0.0;

      // Boucle sur les colonnes de la matrice.
#pragma omp for schedule (static) reduction (+:acc)
      for (unsigned k = 0; k < size; k ++) { 
        acc += A[i * size + k] * x[k];  
      }

      // C'est terminé pour b[i].
#pragma omp single
      b[i] = acc;
 
    }

  }

}
