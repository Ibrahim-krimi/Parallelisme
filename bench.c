/**
 * @mainpage 
 *
 * Programme de benchmarking de différents algorithmes optimisés de
 * multiplication matrice-vecteur sur le type float.
 *
 * Les algorithmes sont sélectionnés via les symboles pré-processeur
 * suivants : @c RAW (forme canonique et choix par défaut), 
 * @c OMP_FOR_I (boucle parallèle sur les lignes de la matrice), 
 * @c OMP_FOR_J1 (boucle parallèle sur les colonnes de la matrice), 
 * @c OMP_FOR_J2 (boucle parallèle les colonnes de la matrice avec 
 * région parallèle maximisée), @c OMP_SIMD (vectorisation sur les 
 * colonnes de la matrice) et enfin @c OMP_FOR_SIMD (boucle parallèle
 * sur les lignes de la matrice et vectorisation sur ses colonnes).
 *
 * Les algorithmes sont exécutés plusieurs fois afin d'obtenir des
 * durées d'exécutions significatives. Tous les tableaux sont alignés
 * sur des blocs de 16 octets.
 */

#include <stdlib.h>
#include <stdio.h>

#define SIZE  4096 // Longueur de nos vecteurs.
#define ITERS  100 // Nombre de répétitions de l'algorithme.

// Inclusion du header correspondant à l'algorithme sélectionné.
#if defined(OMP_FOR_I)
#include "matvec_omp_for_i.h"
#elif defined(OMP_FOR_J1)
#include "matvec_omp_for_j1.h"
#elif defined(OMP_FOR_J2)
#include "matvec_omp_for_j2.h"
#elif defined(OMP_SIMD)
#include "matvec_omp_simd.h"
#elif defined(OMP_FOR_SIMD)
#include "matvec_omp_for_simd.h"
#else
#include "matvec.h"
#endif

/**
 * Programme principal.
 *
 * @return @c EXIT_SUCCESS.
 */
int
main() {

  // Notre matrice (carrée) et nos deux vecteurs qui seront alloués
  // dynamiquement. Le mot-clé restrict indique que les zones mémoires
  // concernées ne se recouvrent pas.
  float *restrict A, *restrict x, *restrict b;

  // Allocation dynamique avec alignement sur des blocs de 16 octets.
  A = (float*) aligned_alloc(16, sizeof(float) * SIZE * SIZE);
  x = (float*) aligned_alloc(16, sizeof(float) * SIZE);
  b = (float*) aligned_alloc(16, sizeof(float) * SIZE);

  // Initialisation des éléments de notre matrice ainsi que de ceux du
  // vecteur x à la valeur 1.0.
  for (unsigned i = 0; i != SIZE * SIZE; A[i ++] = 1.0);
  for (unsigned i = 0; i != SIZE;        x[i ++] = 1.0);
  for (unsigned i = 0; i != SIZE;        b[i ++] = 1.0);

  // Boucle de répétition de l'algorithme.
  for (unsigned i = 0; i != ITERS; i ++) {
#if defined(OMP_FOR_I)
    matvec_omp_for_i(A, x, b, SIZE);
#elif defined(OMP_FOR_J1)
    matvec_omp_for_j1(A, x, b, SIZE);      
#elif defined(OMP_FOR_J2)
    matvec_omp_for_j2(A, x, b, SIZE);
#elif defined(OMP_SIMD)
    matvec_omp_simd(A, x, b, SIZE);
#elif defined(OMP_FOR_SIMD)
    matvec_omp_for_simd(A, x, b, SIZE);    
#else
    matvec(A, x, b, SIZE);
#endif    
  }
  
  // Vérification du résultat.
  for (unsigned i = 0; i != SIZE; i ++) {
    if ( (unsigned)b[i] != SIZE ) {
      printf("Error: %d %f\n", i, b[i]);
      return EXIT_FAILURE;
    }
  }
  
  // Désallocation.
  free(A);
  free(x);
  free(b);

  // C'est terminé.
  return EXIT_SUCCESS;
  
}
