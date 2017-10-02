#if HAVE_CONFIG_H
#include <config.h>
#endif

#define _POSIX_C_SOURCE 200112L
#define __STDC_VERSION__ 200112L

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

/*#include <math.h>*/
#include <swap.h>

#include <array.h>

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

/* must provide callback for printing array->data */

__attribute__ ((nonnull (1), nothrow))
static void array_print (array_t const *restrict array,
   size_t i, size_t j) {
   fprintf (stderr, "esz : %d\n", (int) array->esz);  fflush (stderr);
   fprintf (stderr, "maxn: %d\n", (int) array->n); fflush (stderr);
   data_print (array->data, i, j);
}

__attribute__ ((nonnull (1), nothrow))
static void get_nums (int nums[], size_t snum, int maxnum) {
   size_t k;
   for (k = 0; k != snum; k++)
      nums[k] = rand () % maxnum;
}











__attribute__ ((nonnull (1), nothrow))
static void dumpq(array_t const *restrict q) {
   size_t i;
   fputs ("Q: ", stderr);
   for (i = 0; i != q->n; i++) {
      void *restrict head = index_array (q, i);
      fprintf (stderr, "(%1d:%3d), ", (int) i, *(int *restrict) head);
   }
   fputs ("\n", stderr);
}










__attribute__ ((nothrow, warn_unused_result))
int main (void) {
   array_t array;
   time_t t;
   int nums[10];
   int maxn = 20;
   size_t ntest = 100;
   size_t testi;
   int valid[ARRSZ (nums)];

   t = time (NULL);
   srand ((unsigned int) t);

   error_check (alloc_array (&array, sizeof (int), ARRSZ (nums)) != 0)
      return -2;

   get_nums (nums, ARRSZ (nums), maxn);
   data_print (nums, (size_t) 0, ARRSZ (nums));

   array_print (&array, (size_t) 0, (size_t) 0);
   for (testi = 0; testi != ARRSZ (nums); testi++) {
      fprintf (stderr, "nums[%d]: %d\n", (int) testi, nums[testi]);
      set_array (&array, testi, nums + testi);
      array_print (&array, (size_t) 0, testi + 1);
   }

   get_nums (nums, ARRSZ (nums), maxn);
   data_print (nums, (size_t) 0, ARRSZ (nums));

   for (testi = 0; testi != ARRSZ (nums); testi++) {
      get_array (&array, testi, nums + testi);
      data_print (nums, (size_t) 0, testi + 1);
   }

   get_nums (nums, ARRSZ (nums), maxn);
   data_print (nums, (size_t) 0, ARRSZ (nums));

   array_print (&array, (size_t) 0, (size_t) 0);
   sets_array (&array, (size_t) 0, nums, ARRSZ (nums));
   array_print (&array, (size_t) 0, ARRSZ (nums));

   get_nums (nums, ARRSZ (nums), maxn);
   data_print (nums, (size_t) 0, ARRSZ (nums));

   gets_array (&array, (size_t) 0, nums, ARRSZ (nums));
   data_print (nums, (size_t) 0, ARRSZ (nums));



   for (testi = 0; testi != ARRSZ (nums); testi++)
      valid[testi] = (int) testi;
   for (testi = 0; testi != ARRSZ (nums); testi++)
      set_array (&array, testi, valid + testi);
   for (testi = 0; testi != ARRSZ (nums); testi++)
      get_array (&array, testi, nums + testi);
   for (testi = 0; testi != ARRSZ (nums); testi++)
      assert (valid[testi] == nums[testi]);

   for (testi = 0; testi != ARRSZ (nums); testi++)
      valid[testi] = (int)  (ARRSZ (nums) - testi);
   sets_array (&array, (size_t) 0, valid, ARRSZ (nums));
   gets_array (&array, (size_t) 0, nums,  ARRSZ (nums));
   for (testi = 0; testi != ARRSZ (nums); testi++)
      assert (valid[testi] == nums[testi]);

   for (testi = 0; testi != ARRSZ (nums); testi++)
      valid[testi] = (int) testi;
   sets_array (&array, (size_t) 0, valid, ARRSZ (nums));
   for (testi = 0; testi != ARRSZ (nums) / 2; testi++) {
      cp_array (&array, testi, ARRSZ (nums) / 2 + testi);
      valid[ARRSZ (nums) / 2 + testi] = valid[testi];
   }
   gets_array (&array, (size_t) 0, nums,  ARRSZ (nums));
   for (testi = 0; testi != ARRSZ (nums); testi++)
      assert (valid[testi] == nums[testi]);

   for (testi = 0; testi != ARRSZ (nums); testi++)
      valid[testi] = (int) (ARRSZ (nums) - testi);
   sets_array (&array, (size_t) 0, valid, ARRSZ (nums));
   cps_array (&array, (size_t) 0, ARRSZ (nums) / 2, ARRSZ (nums) / 2);
   for (testi = 0; testi != ARRSZ (nums) / 2; testi++)
      valid[ARRSZ (nums) / 2 + testi] = valid[testi];
   gets_array (&array, (size_t) 0, nums,  ARRSZ (nums));
   for (testi = 0; testi != ARRSZ (nums); testi++)
      assert (valid[testi] == nums[testi]);

   for (testi = 0; testi != ARRSZ (nums); testi++)
      valid[testi] = (int) testi;
   sets_array (&array, (size_t) 0, valid, ARRSZ (nums));
   for (testi = 0; testi != ARRSZ (nums) - 1; testi++) {
      mvs_array (&array, testi, testi + 1, ARRSZ (nums) - testi - 1);
      valid[testi + 1] = valid[0];
   }
   gets_array (&array, (size_t) 0, nums,  ARRSZ (nums));
   for (testi = 0; testi != ARRSZ (nums); testi++)
      assert (valid[testi] == nums[testi]);

   for (testi = 0; testi != ARRSZ (nums); testi++)
      valid[testi] = (int) testi;
   for (testi = 0; testi <= ARRSZ (nums) / 2; testi += 2) {
      swaps_array2 (&array, testi, ARRSZ (nums) - testi - 1, (size_t) 2);
      swap2 (valid + testi, nums + ARRSZ (nums) - testi - 2, sizeof (int));
      swap2 (valid + testi + 1, nums+ ARRSZ (nums) - testi - 1, sizeof (int));
   }
   gets_array (&array, (size_t) 0, nums,  ARRSZ (nums));
   for (testi = 0; testi != ARRSZ (nums); testi++)
      assert (valid[testi] == nums[testi]);

   for (testi = 0; testi != ARRSZ (nums); testi++)
      valid[testi] = (int) (ARRSZ (nums) - testi);
   sets_array (&array, (size_t) 0, valid, ARRSZ (nums));
   for (testi = 0; testi != ARRSZ (nums); testi++)
      assert (indexOf_array (&array, valid + testi) == testi);
   for (testi = 0; testi != ARRSZ (nums); testi++)
      assert (contains_array (&array, valid + testi));

   for (testi = 0; testi != ARRSZ (nums); testi++)
      valid[testi] = (int) (20 + testi);
   for (testi = 0; testi != ARRSZ (nums); testi++)
      assert (! contains_array (&array, valid + testi));

   free_array (&array);

   fputs ("success", stderr); fflush (stderr);

   return EXIT_SUCCESS;
}
