/**
 * @mainpage 
 *
 * Programme séquentiel initial.
 */

#include <omp.h>

#include <stdio.h>
#include <stdlib.h>

/**
 * Crée un fichier texte de nom "thread_file_xxx.txt" où xxx est le numéro
 * du thread puis y inscrit une valeur entière.
 *
 * @param[in] tid le numéro du thread.
 * @param[in] value la valeur à inscrire.
 */
void print_to_file(int tid, int value);

/**
 * Programme principal.
 *
 * @return @c EXIT_SUCCESS.
 */
int
main() {

  // Une variable entière.
  int var = 10;

  // Le numéro du thread.
  int tid = omp_get_thread_num();
  
  // Ecriture dans un fichier texte.
  print_to_file(tid, var);

  // C'est terminé.
  return EXIT_SUCCESS;
  
}

/*****************
 * print_to_file *
 *****************/

void
print_to_file(int tid, int value) {

  // Assemblage du nom de fichier.
  const size_t buf_size = 256;
  char buf[buf_size];
  sprintf(buf, "%s_%d.txt", "thread_file", tid);

  // Création, écriture puis fermeture.
  FILE* file = fopen(buf, "w");
  fprintf(file, "%d\n", value);
  fclose(file);
  
}
