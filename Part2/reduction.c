/**
 * @mainpage 
 *
 * Directive reduction.
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

#pragma omp parallel reduction(+:var)
  {

    // Chaque thread incrémente sa copie locale.
    var ++;
    
  }

  // Affichage du résultat sur la sortie standard.
  printf("%d\n", var);

  // C'est terminé.
  return EXIT_SUCCESS;
  
}
