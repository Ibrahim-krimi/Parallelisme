#include "matvec_omp_for_simd.h"

/***********************
 * matvec_omp_for_simd *
 ***********************/

void
matvec_omp_for_simd(const float A[restrict],
                    const float x[restrict],
                          float b[restrict],
                    const unsigned size) {

  // Accumulateur permettant de calculer la composante b[i].
  float acc;

  // Boucle parallèle sur les lignes de la matrice. La variable
  // partagée acc est privatisée.
#pragma omp parallel for schedule (auto) private (acc)
  for (unsigned i = 0; i < size; i ++) {

    // Initialisation de l'accumulateur.
    acc = 0.0;

    // Boucle sur les colonnes de la matrice.
#pragma omp simd reduction (+:acc)
    for (unsigned k = 0; k < size; k ++) { 
      acc += A[i * size + k] * x[k];  
    }

    // C'est terminé pour b[i].
    b[i] = acc;
 
  }

}
