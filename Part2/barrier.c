/**
 * @mainpage 
 *
 * Directive barrier.
 */

#include <omp.h>

#include <stdio.h>
#include <stdlib.h>

/**
 * Programme principal.
 *
 * @return @c EXIT_SUCCESS.
 */
int
main() {

  // Obtention du nombre de threads disponibles.
  int threads;
#pragma omp parallel
  {
#pragma omp single
    threads = omp_get_num_threads();
  }
  
  // Déclaration d'un tableau avec un emplacement par thread.
  int values[threads];

#pragma omp parallel
  {

    // Chaque thread récupère son identifiant qui est également l'indice
    // de son emplacement dans le tableau.
    int tid = omp_get_thread_num();

    // Chaque thread inscrit son identifiant à son emplacement.
    values[tid] = tid;

    // Personne ne franchit cette ligne tant que le tableau n'est pas complété.
#pragma omp barrier

    // Chaque thread détermine le tid du thread situé derrière lui puis
    // récupère sa valeur.
    int tid_next   = (tid + 1) % threads;
    int value_next = values[tid_next];

    // Personne ne franchit cette ligne tant que tous les threads ne
    // disposent pas de la valeur du thread situé derrière eux.
#pragma omp barrier

    // Tout est ok : permutation.
    values[tid] = value_next;

  }

  // Affichage du tableau sur la sortie standard.
  for (int i = 0; i < threads; i ++) {
    printf("%d\t", values[i]);
  }
  printf("\n");
  
  // C'est terminé.
  return EXIT_SUCCESS;
  
}
