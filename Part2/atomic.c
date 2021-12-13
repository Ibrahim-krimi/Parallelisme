/**
 * @mainpage 
 *
 * Directive atomic. 
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * Programme principal.
 *
 * @return @c EXIT_SUCCESS.
 */
int
main() {

  // Une variable entière.
  int var = 0;

#pragma omp parallel
  {

    // Incrémentation de la variable partagée.
#pragma omp atomic
    var += 1;
    
  }

  // Affichage du résultat sur la sortie standard.
  printf("%d\n", var);

  // C'est terminé.
  return EXIT_SUCCESS;
  
}
