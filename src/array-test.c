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
   data_print (nums, 0, ARRSZ (nums));

   for (testi = 0; testi != ARRSZ (nums); testi++) {
      set_array (&array, testi, nums + testi);
      print_array (&array, 0, testi + 1);
   }

   get_nums (nums, ARRSZ (nums), maxn);
   data_print (nums, 0, ARRSZ (nums));

   for (testi = 0; testi != ARRSZ (nums); testi++) {
      get_array (&array, testi, nums + testi);
      data_print (nums, 0, testi + 1);
   }

   free_array (&array);




   error_check (init_test (&darr) != 0) return -1;

   get_nums (nums, ARRSZ (nums));
   /*
   for (testi = 0; testi != ARRSZ (nums); testi++) {
      error_check (insert_rear_darr (&darr, nums + testi) != 0)
         return -1;
      error_check (trim_cap_darr (&darr, testi + 1) != 0)
         return -1;
      darr_print (&darr);
   }
   for (testi = 0; testi != ARRSZ (nums); testi++) {
      remove_rear_darr (&darr, nums + testi);
      error_check (trim_cap_darr (&darr, ARRSZ (nums) - testi - 1) != 0)
         return -1;
      darr_print (&darr);
      fprintf (stderr, "nums[%d]: %d\n", (int) testi, nums[testi]);
   }
   for (testi = 0; testi != ARRSZ (nums); testi++) {
      error_check (insert_rear_darr (&darr, nums + testi) != 0)
         return -1;
      error_check (trim_cap_darr (&darr, testi + 1) != 0)
         return -1;
      darr_print (&darr);
   }
   for (testi = 0; testi != ARRSZ (nums); testi++) {
      remove_rear_darr (&darr, nums + testi);
      error_check (trim_cap_darr (&darr, ARRSZ (nums) - testi - 1) != 0)
         return -1;
   }
   */
   /*
   error_check (inserts_rear_darr (&darr, nums, (size_t) 1) != 0) return -1;
   error_check (trim_cap_darr (&darr, (size_t) 1) != 0) return -1;
   darr_print (&darr);
   removes_rear_darr (&darr, nums, (size_t) 1);
   error_check (trim_cap_darr (&darr, (size_t) 0) != 0) return -1;
   darr_print (&darr);
   error_check (inserts_rear_darr (&darr, nums, ARRSZ (nums)) != 0) return -1;
   error_check (trim_cap_darr (&darr, ARRSZ (nums)) != 0) return -1;
   darr_print (&darr);
   removes_rear_darr (&darr, nums, ARRSZ (nums));
   error_check (trim_cap_darr (&darr, (size_t) 0) != 0) return -1;
   darr_print (&darr);
   */
   /*
   for (testi = 0; testi != ARRSZ (nums); testi++) {
      error_check (insert_front_darr (&darr, (size_t) 0, nums + testi) != 0)
         return -1;
      error_check (trim_cap_darr (&darr, testi + 1) != 0)
         return -1;
      darr_print (&darr);
   }
   for (testi = 0; testi != ARRSZ (nums); testi++) {
      remove_front_darr (&darr, (size_t) 0, nums + testi);
      error_check (trim_cap_darr (&darr, ARRSZ (nums) - testi - 1) != 0)
         return -1;
      darr_print (&darr);
      fprintf (stderr, "nums[%d]: %d\n", (int) testi, nums[testi]);
   }
   for (testi = 0; testi != ARRSZ (nums); testi++) {
      error_check (insert_front_darr (&darr, (size_t) 0, nums + testi) != 0)
         return -1;
      error_check (trim_cap_darr (&darr, testi + 1) != 0)
         return -1;
      darr_print (&darr);
   }
   for (testi = 0; testi != ARRSZ (nums); testi++) {
      remove_front_darr (&darr, (size_t) 0, nums + testi);
      error_check (trim_cap_darr (&darr, ARRSZ (nums) - testi - 1) != 0)
         return -1;
   }
   */
   /*
   for (testi = 0; testi != ARRSZ (nums); testi++) {
      error_check (insert_front_darr (&darr, darr.n, nums + testi) != 0)
         return -1;
      error_check (trim_cap_darr (&darr, testi + 1) != 0)
         return -1;
      darr_print (&darr);
   }
   for (testi = 0; testi != ARRSZ (nums); testi++) {
      remove_front_darr (&darr, darr.n - 1, nums + testi);
      error_check (trim_cap_darr (&darr, ARRSZ (nums) - testi - 1) != 0)
         return -1;
      darr_print (&darr);
      fprintf (stderr, "nums[%d]: %d\n", (int) testi, nums[testi]);
   }
   for (testi = 0; testi != ARRSZ (nums); testi++) {
      error_check (insert_front_darr (&darr, darr.n, nums + testi) != 0)
         return -1;
      error_check (trim_cap_darr (&darr, testi + 1) != 0)
         return -1;
      darr_print (&darr);
   }
   for (testi = 0; testi != ARRSZ (nums); testi++) {
      remove_front_darr (&darr, darr.n - 1, nums + testi);
      error_check (trim_cap_darr (&darr, ARRSZ (nums) - testi - 1) != 0)
         return -1;
   }
   */
   /*
   error_check (inserts_front_darr (&darr, (size_t) 0, nums, (size_t) 1) != 0) return -1;
   error_check (trim_cap_darr (&darr, (size_t) 1) != 0) return -1;
   darr_print (&darr);
   removes_front_darr (&darr, (size_t) 0, nums, (size_t) 1);
   error_check (trim_cap_darr (&darr, (size_t) 0) != 0) return -1;
   darr_print (&darr);
   error_check (inserts_front_darr (&darr, (size_t) 0, nums, ARRSZ (nums)) != 0) return -1;
   error_check (trim_cap_darr (&darr, ARRSZ (nums)) != 0) return -1;
   darr_print (&darr);
   removes_front_darr (&darr, (size_t) 0, nums, ARRSZ (nums));
   error_check (trim_cap_darr (&darr, (size_t) 0) != 0) return -1;
   darr_print (&darr);
   */
   /*
   error_check (inserts_front_darr (&darr, darr.n, nums, (size_t) 1) != 0) return -1;
   error_check (trim_cap_darr (&darr, (size_t) 1) != 0) return -1;
   darr_print (&darr);
   removes_front_darr (&darr, darr.n, nums, (size_t) 1);
   error_check (trim_cap_darr (&darr, (size_t) 0) != 0) return -1;
   darr_print (&darr);
   error_check (inserts_front_darr (&darr, darr.n, nums, ARRSZ (nums)) != 0) return -1;
   error_check (trim_cap_darr (&darr, ARRSZ (nums)) != 0) return -1;
   darr_print (&darr);
   removes_from_darr (&darr, darr.n, nums, ARRSZ (nums));
   error_check (trim_cap_darr (&darr, (size_t) 0) != 0) return -1;
   darr_print (&darr);
   */
   /*
   for (testi = 0; testi != ntest; testi++) {
      fprintf (stderr, "testi: %d\n", (int) testi);
      error_check (test0 (&darr) != 0) return -4;
      error_check (test1 (&darr, ARRSZ (nums)) != 0) return -5;
      error_check (test2 (&darr) != 0) return -6;
      error_check (test3 (&darr) != 0) return -6;
      error_check (test4 (&darr) != 0) return -7;
      error_check (test5 (&darr, nums, ARRSZ (nums)) != 0) return -5;
      error_check (test6 (&darr) != 0) return -7;
      error_check (test7 (&darr) != 0) return -7;
      error_check (test8 (&darr) != 0) return -8;
      error_check (test9 (&darr) != 0) return -9;
   }
   */
   /*
   for (testi = 0; testi != ntest; testi++) {
      fprintf (stderr, "testi: %d\n", (int) testi);
      error_check (test9 (&darr) != 0) return -9;
      error_check (test8 (&darr) != 0) return -8;
      error_check (test7 (&darr) != 0) return -7;
      error_check (test6 (&darr) != 0) return -7;
      error_check (test5 (&darr, nums, ARRSZ (nums)) != 0) return -5;
      error_check (test4 (&darr) != 0) return -7;
      error_check (test3 (&darr) != 0) return -6;
      error_check (test2 (&darr) != 0) return -6;
      error_check (test1 (&darr, ARRSZ (nums)) != 0) return -5;
      error_check (test0 (&darr) != 0) return -4;
   }
   */
   /*
   error_check (insert_rear_test  (&darr, nums, ARRSZ (nums)) != 0) return -2;
   error_check (remove_rear_test  (&darr, nums, ARRSZ (nums)) != 0) return -2;

   error_check (reset_test (&darr) != 0) return -3;

   error_check (inserts_rear_test (&darr, nums, ARRSZ (nums)) != 0) return -2;
   error_check (removes_rear_test (&darr, nums, ARRSZ (nums)) != 0) return -2;

   error_check (reset_test (&darr) != 0) return -3;

   error_check (insert_front_test  (&darr, nums, ARRSZ (nums)) != 0) return -2;
   error_check (remove_front_test  (&darr, nums, ARRSZ (nums)) != 0) return -2;

   error_check (reset_test (&darr) != 0) return -3;

   error_check (inserts_front_test (&darr, nums, ARRSZ (nums)) != 0) return -2;
   error_check (removes_front_test (&darr, nums, ARRSZ (nums)) != 0) return -2;

   error_check (reset_test (&darr) != 0) return -3;
   */
   /*
   error_check (test0 (&darr) != 0) return -4;
   error_check (test1 (&darr, ARRSZ (nums)) != 0) return -5;
   error_check (test2 (&darr) != 0) return -6;
   error_check (test3 (&darr) != 0) return -6;
   error_check (test4 (&darr) != 0) return -7;
   error_check (test5 (&darr, nums, ARRSZ (nums)) != 0) return -5;
   error_check (test6 (&darr) != 0) return -7;
   error_check (test7 (&darr) != 0) return -7;
   error_check (test8 (&darr) != 0) return -8;
   error_check (test9 (&darr) != 0) return -9;

   error_check (reset_test (&darr) != 0) return -3;

   error_check (test9 (&darr) != 0) return -9;
   error_check (test8 (&darr) != 0) return -8;
   error_check (test7 (&darr) != 0) return -7;
   error_check (test6 (&darr) != 0) return -7;
   error_check (test5 (&darr, nums, ARRSZ (nums)) != 0) return -5;
   error_check (test4 (&darr) != 0) return -7;
   error_check (test3 (&darr) != 0) return -6;
   error_check (test2 (&darr) != 0) return -6;
   error_check (test1 (&darr, ARRSZ (nums)) != 0) return -5;
   error_check (test0 (&darr) != 0) return -4;

   error_check (reset_test (&darr) != 0) return -3;
   */

   for (testi = 0; testi != ntest; testi++)
      switch (rand () % 10) {
      case 0:
         error_check (test0 (&darr) != 0) return -4;
         break;
      case 1:
         error_check (test1 (&darr, ARRSZ (nums)) != 0) return -5;
         break;
      case 2:
         error_check (test2 (&darr) != 0) return -6;
         break;
      case 3:
         error_check (test3 (&darr) != 0) return -6;
         break;
      case 4:
         error_check (test4 (&darr) != 0) return -7;
         break;
      case 5:
         error_check (test5 (&darr, nums, ARRSZ (nums)) != 0) return -5;
         break;
      case 6:
         error_check (test6 (&darr) != 0) return -7;
         break;
      case 7:
         error_check (test7 (&darr) != 0) return -7;
         break;
      case 8:
         error_check (test8 (&darr) != 0) return -8;
         break;
      case 9:
         error_check (test9 (&darr) != 0) return -9;
         break;
      default: __builtin_unreachable ();
      }

   free_test (&darr);

   fputs ("success", stderr); fflush (stderr);

   return EXIT_SUCCESS;
}
