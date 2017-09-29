#if HAVE_CONFIG_H
#include <config.h>
#endif

#define _POSIX_C_SOURCE 200112L
#define __STDC_VERSION__ 200112L

#define NDEBUG 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

/*#include <math.h>*/

#include <darr.h>
#include <darr-resize.h>

static void data_print (void const *restrict data,
   size_t i, size_t j) {
   fprintf (stderr, "["); fflush (stderr);
   /*if (array->n != 0) {*/
   if (i != j) {
      fprintf (stderr, "%d", ((int const *restrict) data)[i]); fflush (stderr);
      for (i++; i != j; i++)
         fprintf (stderr, ", %d", ((int const *restrict) data)[i]); fflush (stderr);
   }
   fprintf (stderr, "]\n"); fflush (stderr);
}

/* must provide acllback for printing array->data */

__attribute__ ((nonnull (1), nothrow))
static void array_print (array_t const *restrict array,
   size_t i, size_t j) {
   fprintf (stderr, "esz : %d\n", (int) array->esz);  fflush (stderr);
   fprintf (stderr, "maxn: %d\n", (int) array->n); fflush (stderr);
   data_print (array, i, j);
}

__attribute__ ((nonnull (1), nothrow))
static void get_nums (int nums[], size_t snum, int maxnum) {
   size_t k;
   for (k = 0; k != snum; k++)
      nums[k] = rand () % maxnum;
}

__attribute__ ((nothrow, warn_unused_result))
int main (void) {
   array_t array;
   time_t t;
   int nums[10];
   int maxn = 20;
   size_t ntest = 100;
   size_t testi;

   t = time (NULL);
   srand ((unsigned int) t);

   error_check (alloc_array (&array, sizeof (int), ARRSZ (nums)) != 0)
      return -2;

   get_nums (nums, ARRSZ (nums), maxn);
   data_print (nums, (size_t) 0, ARRSZ (nums));

   array_print (&array, (size_t) 0, 0);
   for (testi = 0; testi != ARRSZ (nums); testi++) {
      set_array (&array, testi, nums + testi);
      array_print (&array, (size_t) 0, testi + 1);
   }

   get_nums (nums, ARRSZ (nums), maxn);
   data_print (nums, (size_t) 0, ARRSZ (nums));

   for (testi = 0; testi != ARRSZ (nums); testi++) {
      get_array (&array, testi, nums + testi);
      data_print (nums, (size_t) 0, testi + 1);
   }

   free_array (&array);

   fputs ("success", stderr); fflush (stderr);

   return EXIT_SUCCESS;
}
