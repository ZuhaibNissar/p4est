/*
  This file is part of p4est.
  p4est is a C library to manage a parallel collection of quadtrees and/or
  octrees.

  Copyright (C) 2007 Carsten Burstedde, Lucas Wilcox.

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __P4EST_BASE_H__
#define __P4EST_BASE_H__

/*
 * this header is the only one that includes p4est_config.h
 * it is not installed in the final include directory
 */

#ifdef HAVE_CONFIG_H
#include <p4est_config.h>
#endif

#ifdef HAVE_STDIO_H
#include <stdio.h>
#endif

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#ifdef HAVE_STRING_H
#include <string.h>
#endif

#ifdef HAVE_CTYPE_H
#include <ctype.h>
#endif

#if(defined HAVE_BACKTRACE && defined HAVE_BACKTRACE_SYMBOLS)
#define P4EST_BACKTRACE
#endif

#define P4EST_CHECK_ABORT(c,s)                     \
  do {                                             \
    if (!(c)) {                                    \
      fprintf (stderr, "Abort: %s\n   in %s:%d\n", \
               (s), __FILE__, __LINE__);           \
      p4est_abort ();                              \
    }                                              \
  } while (0)
#define P4EST_CHECK_ALLOC(p) P4EST_CHECK_ABORT (((p) != NULL), "Allocation")
#define P4EST_CHECK_REALLOC(p,n) P4EST_CHECK_ABORT (((p) != NULL || (n) == 0), \
                                                    "Allocation")
#define P4EST_CHECK_MPI(r) P4EST_CHECK_ABORT ((r) == MPI_SUCCESS, "MPI operation")
#define P4EST_ASSERT(c) P4EST_CHECK_ABORT ((c), "Assertion '" #c "'")

#define P4EST_ALLOC(t,n) (t *) p4est_malloc ((n) * sizeof(t))
#define P4EST_ALLOC_ZERO(t,n) (t *) p4est_calloc ((n), sizeof(t))
#define P4EST_REALLOC(p,t,n) (t *) p4est_realloc ((p), (n) * sizeof(t))

/* it is allowed to call P4EST_FREE (NULL) which does nothing. */
#define P4EST_FREE(p) p4est_free (p)

#define P4EST_MIN(a,b) (((a) < (b)) ? (a) : (b))
#define P4EST_MAX(a,b) (((a) > (b)) ? (a) : (b))

void               *p4est_malloc (size_t size);
void               *p4est_calloc (size_t nmemb, size_t size);
void               *p4est_realloc (void *ptr, size_t size);
void                p4est_free (void *ptr);
void                p4est_memory_check (void);

void                p4est_abort (void);

#endif /* !__P4EST_BASE_H__ */
