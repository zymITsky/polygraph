/*
 * FILE : pysary_wrap.c
 * 
 * This file was automatically generated by :
 * Simplified Wrapper and Interface Generator (SWIG)
 * Version 1.1 (Patch 5)
 * 
 * Portions Copyright (c) 1995-1998
 * The University of Utah and The Regents of the University of California.
 * Permission is granted to distribute this file in any manner provided
 * this notice remains intact.
 * 
 * Do not make changes to this file--changes will be lost!
 *
 */


#define SWIGCODE
/* Implementation : PYTHON */

#define SWIGPYTHON
#include <string.h>
#include <stdlib.h>
/***********************************************************************
 * $Header: /home/jnewsome/projects/ece_afs_cvs/cvs/polygraph_dist/polygraph/pysary/pysary_wrap.c,v 1.1 2005-06-16 15:26:21 jnewsome Exp $
 * swig_lib/python/python.cfg
 *
 * This file contains coded needed to add variable linking to the
 * Python interpreter.   C variables are added as a new kind of Python
 * datatype.
 *
 * Also contains supporting code for building python under Windows
 * and things like that.
 *
 * $Log: pysary_wrap.c,v $
 * Revision 1.1  2005-06-16 15:26:21  jnewsome
 * Initial revision
 *
 ************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif
#include "Python.h"
#ifdef __cplusplus
}
#endif

/* Definitions for Windows/Unix exporting */
#if defined(__WIN32__)
#   if defined(_MSC_VER)
#	define SWIGEXPORT(a,b) __declspec(dllexport) a b
#   else
#	if defined(__BORLANDC__)
#	    define SWIGEXPORT(a,b) a _export b
#	else
#	    define SWIGEXPORT(a,b) a b
#	endif
#   endif
#else
#   define SWIGEXPORT(a,b) a b
#endif

#ifdef SWIG_GLOBAL
#ifdef __cplusplus
#define SWIGSTATIC extern "C"
#else
#define SWIGSTATIC
#endif
#endif

#ifndef SWIGSTATIC
#define SWIGSTATIC static
#endif

typedef struct {
  char  *name;
  PyObject *(*get_attr)(void);
  int (*set_attr)(PyObject *);
} swig_globalvar;

typedef struct swig_varlinkobject {
  PyObject_HEAD
  swig_globalvar **vars;
  int      nvars;
  int      maxvars;
} swig_varlinkobject;

/* ----------------------------------------------------------------------
   swig_varlink_repr()

   Function for python repr method
   ---------------------------------------------------------------------- */

static PyObject *
swig_varlink_repr(swig_varlinkobject *v)
{
  v = v;
  return PyString_FromString("<Global variables>");
}

/* ---------------------------------------------------------------------
   swig_varlink_print()

   Print out all of the global variable names
   --------------------------------------------------------------------- */

static int
swig_varlink_print(swig_varlinkobject *v, FILE *fp, int flags)
{

  int i = 0;
  flags = flags;
  fprintf(fp,"Global variables { ");
  while (v->vars[i]) {
    fprintf(fp,"%s", v->vars[i]->name);
    i++;
    if (v->vars[i]) fprintf(fp,", ");
  }
  fprintf(fp," }\n");
  return 0;
}

/* --------------------------------------------------------------------
   swig_varlink_getattr
 
   This function gets the value of a variable and returns it as a
   PyObject.   In our case, we'll be looking at the datatype and
   converting into a number or string
   -------------------------------------------------------------------- */

static PyObject *
swig_varlink_getattr(swig_varlinkobject *v, char *n)
{
  int i = 0;
  char temp[128];

  while (v->vars[i]) {
    if (strcmp(v->vars[i]->name,n) == 0) {
      return (*v->vars[i]->get_attr)();
    }
    i++;
  }
  sprintf(temp,"C global variable %s not found.", n);
  PyErr_SetString(PyExc_NameError,temp);
  return NULL;
}

/* -------------------------------------------------------------------
   swig_varlink_setattr()

   This function sets the value of a variable.
   ------------------------------------------------------------------- */

static int
swig_varlink_setattr(swig_varlinkobject *v, char *n, PyObject *p)
{
  char temp[128];
  int i = 0;
  while (v->vars[i]) {
    if (strcmp(v->vars[i]->name,n) == 0) {
      return (*v->vars[i]->set_attr)(p);
    }
    i++;
  }
  sprintf(temp,"C global variable %s not found.", n);
  PyErr_SetString(PyExc_NameError,temp);
  return 1;
}

statichere PyTypeObject varlinktype = {
/*  PyObject_HEAD_INIT(&PyType_Type)  Note : This doesn't work on some machines */
  PyObject_HEAD_INIT(0)              
  0,
  "varlink",                          /* Type name    */
  sizeof(swig_varlinkobject),         /* Basic size   */
  0,                                  /* Itemsize     */
  0,                                  /* Deallocator  */ 
  (printfunc) swig_varlink_print,     /* Print        */
  (getattrfunc) swig_varlink_getattr, /* get attr     */
  (setattrfunc) swig_varlink_setattr, /* Set attr     */
  0,                                  /* tp_compare   */
  (reprfunc) swig_varlink_repr,       /* tp_repr      */    
  0,                                  /* tp_as_number */
  0,                                  /* tp_as_mapping*/
  0,                                  /* tp_hash      */
};

/* Create a variable linking object for use later */

SWIGSTATIC PyObject *
SWIG_newvarlink(void)
{
  swig_varlinkobject *result = 0;
  result = PyMem_NEW(swig_varlinkobject,1);
  varlinktype.ob_type = &PyType_Type;    /* Patch varlinktype into a PyType */
  result->ob_type = &varlinktype;
  /*  _Py_NewReference(result);  Does not seem to be necessary */
  result->nvars = 0;
  result->maxvars = 64;
  result->vars = (swig_globalvar **) malloc(64*sizeof(swig_globalvar *));
  result->vars[0] = 0;
  result->ob_refcnt = 0;
  Py_XINCREF((PyObject *) result);
  return ((PyObject*) result);
}

SWIGSTATIC void
SWIG_addvarlink(PyObject *p, char *name,
	   PyObject *(*get_attr)(void), int (*set_attr)(PyObject *p))
{
  swig_varlinkobject *v;
  v= (swig_varlinkobject *) p;
	
  if (v->nvars >= v->maxvars -1) {
    v->maxvars = 2*v->maxvars;
    v->vars = (swig_globalvar **) realloc(v->vars,v->maxvars*sizeof(swig_globalvar *));
    if (v->vars == NULL) {
      fprintf(stderr,"SWIG : Fatal error in initializing Python module.\n");
      exit(1);
    }
  }
  v->vars[v->nvars] = (swig_globalvar *) malloc(sizeof(swig_globalvar));
  v->vars[v->nvars]->name = (char *) malloc(strlen(name)+1);
  strcpy(v->vars[v->nvars]->name,name);
  v->vars[v->nvars]->get_attr = get_attr;
  v->vars[v->nvars]->set_attr = set_attr;
  v->nvars++;
  v->vars[v->nvars] = 0;
}



/*****************************************************************************
 * $Header: /home/jnewsome/projects/ece_afs_cvs/cvs/polygraph_dist/polygraph/pysary/pysary_wrap.c,v 1.1 2005-06-16 15:26:21 jnewsome Exp $
 *
 * swigptr.swg
 *
 * This file contains supporting code for the SWIG run-time type checking
 * mechanism.  The following functions are available :
 *
 * SWIG_RegisterMapping(char *origtype, char *newtype, void *(*cast)(void *));
 *
 *      Registers a new type-mapping with the type-checker.  origtype is the
 *      original datatype and newtype is an equivalent type.  cast is optional
 *      pointer to a function to cast pointer values between types (this
 *      is typically used to cast pointers from derived classes to base classes in C++)
 *      
 * SWIG_MakePtr(char *buffer, void *ptr, char *typestring);
 *     
 *      Makes a pointer string from a pointer and typestring.  The result is returned
 *      in buffer which is assumed to hold enough space for the result.
 *
 * char * SWIG_GetPtr(char *buffer, void **ptr, char *type)
 *
 *      Gets a pointer value from a string.  If there is a type-mismatch, returns
 *      a character string to the received type.  On success, returns NULL.
 *
 *
 * You can remap these functions by making a file called "swigptr.swg" in
 * your the same directory as the interface file you are wrapping.
 *
 * These functions are normally declared static, but this file can be
 * can be used in a multi-module environment by redefining the symbol
 * SWIGSTATIC.
 *****************************************************************************/

#include <stdlib.h>

#ifdef SWIG_GLOBAL
#ifdef __cplusplus
#define SWIGSTATIC extern "C"
#else
#define SWIGSTATIC
#endif
#endif

#ifndef SWIGSTATIC
#define SWIGSTATIC static
#endif


/* SWIG pointer structure */

typedef struct SwigPtrType {
  char               *name;               /* Datatype name                  */
  int                 len;                /* Length (used for optimization) */
  void               *(*cast)(void *);    /* Pointer casting function       */
  struct SwigPtrType *next;               /* Linked list pointer            */
} SwigPtrType;

/* Pointer cache structure */

typedef struct {
  int                 stat;               /* Status (valid) bit             */
  SwigPtrType        *tp;                 /* Pointer to type structure      */
  char                name[256];          /* Given datatype name            */
  char                mapped[256];        /* Equivalent name                */
} SwigCacheType;

/* Some variables  */

static int SwigPtrMax  = 64;           /* Max entries that can be currently held */
                                       /* This value may be adjusted dynamically */
static int SwigPtrN    = 0;            /* Current number of entries              */
static int SwigPtrSort = 0;            /* Status flag indicating sort            */
static int SwigStart[256];             /* Starting positions of types            */

/* Pointer table */
static SwigPtrType *SwigPtrTable = 0;  /* Table containing pointer equivalences  */

/* Cached values */

#define SWIG_CACHESIZE  8
#define SWIG_CACHEMASK  0x7
static SwigCacheType SwigCache[SWIG_CACHESIZE];  
static int SwigCacheIndex = 0;
static int SwigLastCache = 0;

/* Sort comparison function */
static int swigsort(const void *data1, const void *data2) {
	SwigPtrType *d1 = (SwigPtrType *) data1;
	SwigPtrType *d2 = (SwigPtrType *) data2;
	return strcmp(d1->name,d2->name);
}

/* Binary Search function */
static int swigcmp(const void *key, const void *data) {
  char *k = (char *) key;
  SwigPtrType *d = (SwigPtrType *) data;
  return strncmp(k,d->name,d->len);
}

/* Register a new datatype with the type-checker */

SWIGSTATIC 
void SWIG_RegisterMapping(char *origtype, char *newtype, void *(*cast)(void *)) {

  int i;
  SwigPtrType *t = 0,*t1;

  /* Allocate the pointer table if necessary */

  if (!SwigPtrTable) {     
    SwigPtrTable = (SwigPtrType *) malloc(SwigPtrMax*sizeof(SwigPtrType));
    SwigPtrN = 0;
  }
  /* Grow the table */
  if (SwigPtrN >= SwigPtrMax) {
    SwigPtrMax = 2*SwigPtrMax;
    SwigPtrTable = (SwigPtrType *) realloc((char *) SwigPtrTable,SwigPtrMax*sizeof(SwigPtrType));
  }
  for (i = 0; i < SwigPtrN; i++)
    if (strcmp(SwigPtrTable[i].name,origtype) == 0) {
      t = &SwigPtrTable[i];
      break;
    }
  if (!t) {
    t = &SwigPtrTable[SwigPtrN];
    t->name = origtype;
    t->len = strlen(t->name);
    t->cast = 0;
    t->next = 0;
    SwigPtrN++;
  }

  /* Check for existing entry */

  while (t->next) {
    if ((strcmp(t->name,newtype) == 0)) {
      if (cast) t->cast = cast;
      return;
    }
    t = t->next;
  }
  
  /* Now place entry (in sorted order) */

  t1 = (SwigPtrType *) malloc(sizeof(SwigPtrType));
  t1->name = newtype;
  t1->len = strlen(t1->name);
  t1->cast = cast;
  t1->next = 0;            
  t->next = t1;           
  SwigPtrSort = 0;
}

/* Make a pointer value string */

SWIGSTATIC 
void SWIG_MakePtr(char *_c, const void *_ptr, char *type) {
  static char _hex[16] =
  {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
   'a', 'b', 'c', 'd', 'e', 'f'};
  unsigned long _p, _s;
  char _result[20], *_r;    /* Note : a 64-bit hex number = 16 digits */
  _r = _result;
  _p = (unsigned long) _ptr;
  if (_p > 0) {
    while (_p > 0) {
      _s = _p & 0xf;
      *(_r++) = _hex[_s];
      _p = _p >> 4;
    }
    *_r = '_';
    while (_r >= _result)
      *(_c++) = *(_r--);
  } else {
    strcpy (_c, "NULL");
  }
  if (_ptr)
    strcpy (_c, type);
}

/* Define for backwards compatibility */

#define _swig_make_hex   SWIG_MakePtr 

/* Function for getting a pointer value */

SWIGSTATIC 
char *SWIG_GetPtr(char *_c, void **ptr, char *_t)
{
  unsigned long _p;
  char temp_type[256];
  char *name;
  int  i, len;
  SwigPtrType *sp,*tp;
  SwigCacheType *cache;
  int  start, end;
  _p = 0;

  /* Pointer values must start with leading underscore */
  if (*_c == '_') {
      _c++;
      /* Extract hex value from pointer */
      while (*_c) {
	  if ((*_c >= '0') && (*_c <= '9'))
	    _p = (_p << 4) + (*_c - '0');
	  else if ((*_c >= 'a') && (*_c <= 'f'))
	    _p = (_p << 4) + ((*_c - 'a') + 10);
	  else
	    break;
	  _c++;
      }

      if (_t) {
	if (strcmp(_t,_c)) { 
	  if (!SwigPtrSort) {
	    qsort((void *) SwigPtrTable, SwigPtrN, sizeof(SwigPtrType), swigsort); 
	    for (i = 0; i < 256; i++) {
	      SwigStart[i] = SwigPtrN;
	    }
	    for (i = SwigPtrN-1; i >= 0; i--) {
	      SwigStart[(int) (SwigPtrTable[i].name[1])] = i;
	    }
	    for (i = 255; i >= 1; i--) {
	      if (SwigStart[i-1] > SwigStart[i])
		SwigStart[i-1] = SwigStart[i];
	    }
	    SwigPtrSort = 1;
	    for (i = 0; i < SWIG_CACHESIZE; i++)  
	      SwigCache[i].stat = 0;
	  }
	  
	  /* First check cache for matches.  Uses last cache value as starting point */
	  cache = &SwigCache[SwigLastCache];
	  for (i = 0; i < SWIG_CACHESIZE; i++) {
	    if (cache->stat) {
	      if (strcmp(_t,cache->name) == 0) {
		if (strcmp(_c,cache->mapped) == 0) {
		  cache->stat++;
		  *ptr = (void *) _p;
		  if (cache->tp->cast) *ptr = (*(cache->tp->cast))(*ptr);
		  return (char *) 0;
		}
	      }
	    }
	    SwigLastCache = (SwigLastCache+1) & SWIG_CACHEMASK;
	    if (!SwigLastCache) cache = SwigCache;
	    else cache++;
	  }
	  /* We have a type mismatch.  Will have to look through our type
	     mapping table to figure out whether or not we can accept this datatype */

	  start = SwigStart[(int) _t[1]];
	  end = SwigStart[(int) _t[1]+1];
	  sp = &SwigPtrTable[start];
	  while (start < end) {
	    if (swigcmp(_t,sp) == 0) break;
	    sp++;
	    start++;
	  }
	  if (start >= end) sp = 0;
	  /* Try to find a match for this */
	  if (sp) {
	    while (swigcmp(_t,sp) == 0) {
	      name = sp->name;
	      len = sp->len;
	      tp = sp->next;
	      /* Try to find entry for our given datatype */
	      while(tp) {
		if (tp->len >= 255) {
		  return _c;
		}
		strcpy(temp_type,tp->name);
		strncat(temp_type,_t+len,255-tp->len);
		if (strcmp(_c,temp_type) == 0) {
		  
		  strcpy(SwigCache[SwigCacheIndex].mapped,_c);
		  strcpy(SwigCache[SwigCacheIndex].name,_t);
		  SwigCache[SwigCacheIndex].stat = 1;
		  SwigCache[SwigCacheIndex].tp = tp;
		  SwigCacheIndex = SwigCacheIndex & SWIG_CACHEMASK;
		  
		  /* Get pointer value */
		  *ptr = (void *) _p;
		  if (tp->cast) *ptr = (*(tp->cast))(*ptr);
		  return (char *) 0;
		}
		tp = tp->next;
	      }
	      sp++;
	      /* Hmmm. Didn't find it this time */
	    }
	  }
	  /* Didn't find any sort of match for this data.  
	     Get the pointer value and return the received type */
	  *ptr = (void *) _p;
	  return _c;
	} else {
	  /* Found a match on the first try.  Return pointer value */
	  *ptr = (void *) _p;
	  return (char *) 0;
	}
      } else {
	/* No type specified.  Good luck */
	*ptr = (void *) _p;
	return (char *) 0;
      }
  } else {
    if (strcmp (_c, "NULL") == 0) {
	*ptr = (void *) 0;
	return (char *) 0;
    }
    *ptr = (void *) 0;	
    return _c;
  }
}

/* Compatibility mode */

#define _swig_get_hex  SWIG_GetPtr

#define SWIG_init    initpysary

#define SWIG_name    "pysary"

#include <sary/saryer.h>
#include <glib.h>
#include <sary/mmap.h>
#include <sary/text.h>
#include <sary/i.h>
#include <sary/saryconfig.h>
extern Saryer *saryer_new(const gchar *);
extern Saryer *saryer_new2(const gchar *,const gchar *);
extern void saryer_destroy(Saryer *);
extern gboolean saryer_search(Saryer *,const gchar *);
extern gboolean saryer_search2(Saryer *,const gchar *,SaryInt );
extern gboolean saryer_isearch(Saryer *,const gchar *,SaryInt );
extern void saryer_isearch_reset(Saryer *);
extern gboolean saryer_icase_search(Saryer *,const gchar *);
extern gboolean saryer_icase_search2(Saryer *,const gchar *,SaryInt );
extern SaryText *saryer_get_text(Saryer *);
extern SaryMmap *saryer_get_array(Saryer *);
extern gchar *saryer_get_next_line(Saryer *);
extern gchar *saryer_get_next_line2(Saryer *,SaryInt *);
extern gchar *saryer_get_next_context_lines(Saryer *,SaryInt ,SaryInt );
extern gchar *saryer_get_next_context_lines2(Saryer *,SaryInt ,SaryInt ,SaryInt *);
extern gchar *saryer_get_next_tagged_region(Saryer *,const gchar *,const gchar *);
extern gchar *saryer_get_next_tagged_region2(Saryer *,const gchar *,SaryInt ,const gchar *,SaryInt ,SaryInt *);
extern SaryText *saryer_get_next_occurrence(Saryer *);
extern gchar *saryer_peek_next_position(Saryer *);
extern SaryInt saryer_count_occurrences(Saryer *);
extern void saryer_sort_occurrences(Saryer *);
extern void saryer_enable_cache(Saryer *);
static PyObject *_wrap_saryer_new(PyObject *self, PyObject *args) {
    PyObject * _resultobj;
    Saryer * _result;
    gchar * _arg0;
    char _ptemp[128];

    self = self;
    if(!PyArg_ParseTuple(args,"s:saryer_new",&_arg0)) 
        return NULL;
    _result = (Saryer *)saryer_new(_arg0);
    SWIG_MakePtr(_ptemp, (char *) _result,"_Saryer_p");
    _resultobj = Py_BuildValue("s",_ptemp);
    return _resultobj;
}

static PyObject *_wrap_saryer_new2(PyObject *self, PyObject *args) {
    PyObject * _resultobj;
    Saryer * _result;
    gchar * _arg0;
    gchar * _arg1;
    char _ptemp[128];

    self = self;
    if(!PyArg_ParseTuple(args,"ss:saryer_new2",&_arg0,&_arg1)) 
        return NULL;
    _result = (Saryer *)saryer_new2(_arg0,_arg1);
    SWIG_MakePtr(_ptemp, (char *) _result,"_Saryer_p");
    _resultobj = Py_BuildValue("s",_ptemp);
    return _resultobj;
}

static PyObject *_wrap_saryer_destroy(PyObject *self, PyObject *args) {
    PyObject * _resultobj;
    Saryer * _arg0;
    char * _argc0 = 0;

    self = self;
    if(!PyArg_ParseTuple(args,"s:saryer_destroy",&_argc0)) 
        return NULL;
    if (_argc0) {
        if (SWIG_GetPtr(_argc0,(void **) &_arg0,"_Saryer_p")) {
            PyErr_SetString(PyExc_TypeError,"Type error in argument 1 of saryer_destroy. Expected _Saryer_p.");
        return NULL;
        }
    }
    saryer_destroy(_arg0);
    Py_INCREF(Py_None);
    _resultobj = Py_None;
    return _resultobj;
}

static PyObject *_wrap_saryer_search(PyObject *self, PyObject *args) {
    PyObject * _resultobj;
    gboolean  _result;
    Saryer * _arg0;
    gchar * _arg1;
    char * _argc0 = 0;

    self = self;
    if(!PyArg_ParseTuple(args,"ss:saryer_search",&_argc0,&_arg1)) 
        return NULL;
    if (_argc0) {
        if (SWIG_GetPtr(_argc0,(void **) &_arg0,"_Saryer_p")) {
            PyErr_SetString(PyExc_TypeError,"Type error in argument 1 of saryer_search. Expected _Saryer_p.");
        return NULL;
        }
    }
    _result = (gboolean )saryer_search(_arg0,_arg1);
    _resultobj = Py_BuildValue("i",_result);
    return _resultobj;
}

static PyObject *_wrap_saryer_search2(PyObject *self, PyObject *args) {
    PyObject * _resultobj;
    gboolean  _result;
    Saryer * _arg0;
    gchar * _arg1;
    SaryInt  _arg2;
    char * _argc0 = 0;

    self = self;
    if(!PyArg_ParseTuple(args,"ss#:saryer_search2",&_argc0,&_arg1,&_arg2)) 
        return NULL;
    if (_argc0) {
        if (SWIG_GetPtr(_argc0,(void **) &_arg0,"_Saryer_p")) {
            PyErr_SetString(PyExc_TypeError,"Type error in argument 1 of saryer_search2. Expected _Saryer_p.");
        return NULL;
        }
    }
    _result = (gboolean )saryer_search2(_arg0,_arg1,_arg2);
    _resultobj = Py_BuildValue("i",_result);
    return _resultobj;
}

static PyObject *_wrap_saryer_isearch(PyObject *self, PyObject *args) {
    PyObject * _resultobj;
    gboolean  _result;
    Saryer * _arg0;
    gchar * _arg1;
    SaryInt  _arg2;
    char * _argc0 = 0;

    self = self;
    if(!PyArg_ParseTuple(args,"ssi:saryer_isearch",&_argc0,&_arg1,&_arg2)) 
        return NULL;
    if (_argc0) {
        if (SWIG_GetPtr(_argc0,(void **) &_arg0,"_Saryer_p")) {
            PyErr_SetString(PyExc_TypeError,"Type error in argument 1 of saryer_isearch. Expected _Saryer_p.");
        return NULL;
        }
    }
    _result = (gboolean )saryer_isearch(_arg0,_arg1,_arg2);
    _resultobj = Py_BuildValue("i",_result);
    return _resultobj;
}

static PyObject *_wrap_saryer_isearch_reset(PyObject *self, PyObject *args) {
    PyObject * _resultobj;
    Saryer * _arg0;
    char * _argc0 = 0;

    self = self;
    if(!PyArg_ParseTuple(args,"s:saryer_isearch_reset",&_argc0)) 
        return NULL;
    if (_argc0) {
        if (SWIG_GetPtr(_argc0,(void **) &_arg0,"_Saryer_p")) {
            PyErr_SetString(PyExc_TypeError,"Type error in argument 1 of saryer_isearch_reset. Expected _Saryer_p.");
        return NULL;
        }
    }
    saryer_isearch_reset(_arg0);
    Py_INCREF(Py_None);
    _resultobj = Py_None;
    return _resultobj;
}

static PyObject *_wrap_saryer_icase_search(PyObject *self, PyObject *args) {
    PyObject * _resultobj;
    gboolean  _result;
    Saryer * _arg0;
    gchar * _arg1;
    char * _argc0 = 0;

    self = self;
    if(!PyArg_ParseTuple(args,"ss:saryer_icase_search",&_argc0,&_arg1)) 
        return NULL;
    if (_argc0) {
        if (SWIG_GetPtr(_argc0,(void **) &_arg0,"_Saryer_p")) {
            PyErr_SetString(PyExc_TypeError,"Type error in argument 1 of saryer_icase_search. Expected _Saryer_p.");
        return NULL;
        }
    }
    _result = (gboolean )saryer_icase_search(_arg0,_arg1);
    _resultobj = Py_BuildValue("i",_result);
    return _resultobj;
}

static PyObject *_wrap_saryer_icase_search2(PyObject *self, PyObject *args) {
    PyObject * _resultobj;
    gboolean  _result;
    Saryer * _arg0;
    gchar * _arg1;
    SaryInt  _arg2;
    char * _argc0 = 0;

    self = self;
    if(!PyArg_ParseTuple(args,"ssi:saryer_icase_search2",&_argc0,&_arg1,&_arg2)) 
        return NULL;
    if (_argc0) {
        if (SWIG_GetPtr(_argc0,(void **) &_arg0,"_Saryer_p")) {
            PyErr_SetString(PyExc_TypeError,"Type error in argument 1 of saryer_icase_search2. Expected _Saryer_p.");
        return NULL;
        }
    }
    _result = (gboolean )saryer_icase_search2(_arg0,_arg1,_arg2);
    _resultobj = Py_BuildValue("i",_result);
    return _resultobj;
}

static PyObject *_wrap_saryer_get_text(PyObject *self, PyObject *args) {
    PyObject * _resultobj;
    SaryText * _result;
    Saryer * _arg0;
    char * _argc0 = 0;
    char _ptemp[128];

    self = self;
    if(!PyArg_ParseTuple(args,"s:saryer_get_text",&_argc0)) 
        return NULL;
    if (_argc0) {
        if (SWIG_GetPtr(_argc0,(void **) &_arg0,"_Saryer_p")) {
            PyErr_SetString(PyExc_TypeError,"Type error in argument 1 of saryer_get_text. Expected _Saryer_p.");
        return NULL;
        }
    }
    _result = (SaryText *)saryer_get_text(_arg0);
    SWIG_MakePtr(_ptemp, (char *) _result,"_SaryText_p");
    _resultobj = Py_BuildValue("s",_ptemp);
    return _resultobj;
}

static PyObject *_wrap_saryer_get_array(PyObject *self, PyObject *args) {
    PyObject * _resultobj;
    SaryMmap * _result;
    Saryer * _arg0;
    char * _argc0 = 0;
    char _ptemp[128];

    self = self;
    if(!PyArg_ParseTuple(args,"s:saryer_get_array",&_argc0)) 
        return NULL;
    if (_argc0) {
        if (SWIG_GetPtr(_argc0,(void **) &_arg0,"_Saryer_p")) {
            PyErr_SetString(PyExc_TypeError,"Type error in argument 1 of saryer_get_array. Expected _Saryer_p.");
        return NULL;
        }
    }
    _result = (SaryMmap *)saryer_get_array(_arg0);
    SWIG_MakePtr(_ptemp, (char *) _result,"_SaryMmap_p");
    _resultobj = Py_BuildValue("s",_ptemp);
    return _resultobj;
}

static PyObject *_wrap_saryer_get_next_offset(PyObject *self, PyObject *args) {
    PyObject * _resultobj;
    SaryInt  _result;
    Saryer * _arg0;
    char * _argc0 = 0;

    self = self;
    if(!PyArg_ParseTuple(args,"s:saryer_get_next_offset",&_argc0)) 
        return NULL;
    if (_argc0) {
        if (SWIG_GetPtr(_argc0,(void **) &_arg0,"_Saryer_p")) {
            PyErr_SetString(PyExc_TypeError,"Type error in argument 1 of saryer_get_next_offset. Expected _Saryer_p.");
        return NULL;
        }
    }
    _result = (SaryInt )saryer_get_next_offset(_arg0);
    _resultobj = Py_BuildValue("i",_result);
    return _resultobj;
}

static PyObject *_wrap_saryer_get_next_line(PyObject *self, PyObject *args) {
    PyObject * _resultobj;
    gchar * _result;
    Saryer * _arg0;
    char * _argc0 = 0;

    self = self;
    if(!PyArg_ParseTuple(args,"s:saryer_get_next_line",&_argc0)) 
        return NULL;
    if (_argc0) {
        if (SWIG_GetPtr(_argc0,(void **) &_arg0,"_Saryer_p")) {
            PyErr_SetString(PyExc_TypeError,"Type error in argument 1 of saryer_get_next_line. Expected _Saryer_p.");
        return NULL;
        }
    }
    _result = (gchar *)saryer_get_next_line(_arg0);
    _resultobj = Py_BuildValue("s", _result);
    return _resultobj;
}

static PyObject *_wrap_saryer_get_next_line2(PyObject *self, PyObject *args) {
    PyObject * _resultobj;
    gchar * _result;
    Saryer * _arg0;
    SaryInt * _arg1;
    char * _argc0 = 0;
    char * _argc1 = 0;

    self = self;
    if(!PyArg_ParseTuple(args,"ss:saryer_get_next_line2",&_argc0,&_argc1)) 
        return NULL;
    if (_argc0) {
        if (SWIG_GetPtr(_argc0,(void **) &_arg0,"_Saryer_p")) {
            PyErr_SetString(PyExc_TypeError,"Type error in argument 1 of saryer_get_next_line2. Expected _Saryer_p.");
        return NULL;
        }
    }
    if (_argc1) {
        if (SWIG_GetPtr(_argc1,(void **) &_arg1,"_SaryInt_p")) {
            PyErr_SetString(PyExc_TypeError,"Type error in argument 2 of saryer_get_next_line2. Expected _SaryInt_p.");
        return NULL;
        }
    }
    _result = (gchar *)saryer_get_next_line2(_arg0,_arg1);
    _resultobj = Py_BuildValue("s", _result);
    return _resultobj;
}

static PyObject *_wrap_saryer_get_next_context_lines(PyObject *self, PyObject *args) {
    PyObject * _resultobj;
    gchar * _result;
    Saryer * _arg0;
    SaryInt  _arg1;
    SaryInt  _arg2;
    char * _argc0 = 0;

    self = self;
    if(!PyArg_ParseTuple(args,"sii:saryer_get_next_context_lines",&_argc0,&_arg1,&_arg2)) 
        return NULL;
    if (_argc0) {
        if (SWIG_GetPtr(_argc0,(void **) &_arg0,"_Saryer_p")) {
            PyErr_SetString(PyExc_TypeError,"Type error in argument 1 of saryer_get_next_context_lines. Expected _Saryer_p.");
        return NULL;
        }
    }
    _result = (gchar *)saryer_get_next_context_lines(_arg0,_arg1,_arg2);
    _resultobj = Py_BuildValue("s", _result);
    return _resultobj;
}

static PyObject *_wrap_saryer_get_next_context_lines2(PyObject *self, PyObject *args) {
    PyObject * _resultobj;
    gchar * _result;
    Saryer * _arg0;
    SaryInt  _arg1;
    SaryInt  _arg2;
    SaryInt * _arg3;
    char * _argc0 = 0;
    char * _argc3 = 0;

    self = self;
    if(!PyArg_ParseTuple(args,"siis:saryer_get_next_context_lines2",&_argc0,&_arg1,&_arg2,&_argc3)) 
        return NULL;
    if (_argc0) {
        if (SWIG_GetPtr(_argc0,(void **) &_arg0,"_Saryer_p")) {
            PyErr_SetString(PyExc_TypeError,"Type error in argument 1 of saryer_get_next_context_lines2. Expected _Saryer_p.");
        return NULL;
        }
    }
    if (_argc3) {
        if (SWIG_GetPtr(_argc3,(void **) &_arg3,"_SaryInt_p")) {
            PyErr_SetString(PyExc_TypeError,"Type error in argument 4 of saryer_get_next_context_lines2. Expected _SaryInt_p.");
        return NULL;
        }
    }
    _result = (gchar *)saryer_get_next_context_lines2(_arg0,_arg1,_arg2,_arg3);
    _resultobj = Py_BuildValue("s", _result);
    return _resultobj;
}

static PyObject *_wrap_saryer_get_next_tagged_region(PyObject *self, PyObject *args) {
    PyObject * _resultobj;
    gchar * _result;
    Saryer * _arg0;
    gchar * _arg1;
    gchar * _arg2;
    char * _argc0 = 0;

    self = self;
    if(!PyArg_ParseTuple(args,"sss:saryer_get_next_tagged_region",&_argc0,&_arg1,&_arg2)) 
        return NULL;
    if (_argc0) {
        if (SWIG_GetPtr(_argc0,(void **) &_arg0,"_Saryer_p")) {
            PyErr_SetString(PyExc_TypeError,"Type error in argument 1 of saryer_get_next_tagged_region. Expected _Saryer_p.");
        return NULL;
        }
    }
    _result = (gchar *)saryer_get_next_tagged_region(_arg0,_arg1,_arg2);
    _resultobj = Py_BuildValue("s", _result);
    return _resultobj;
}

static PyObject *_wrap_saryer_get_next_tagged_region2(PyObject *self, PyObject *args) {
    PyObject * _resultobj;
    gchar * _result;
    Saryer * _arg0;
    gchar * _arg1;
    SaryInt  _arg2;
    gchar * _arg3;
    SaryInt  _arg4;
    SaryInt * _arg5;
    char * _argc0 = 0;
    char * _argc5 = 0;

    self = self;
    if(!PyArg_ParseTuple(args,"ssisis:saryer_get_next_tagged_region2",&_argc0,&_arg1,&_arg2,&_arg3,&_arg4,&_argc5)) 
        return NULL;
    if (_argc0) {
        if (SWIG_GetPtr(_argc0,(void **) &_arg0,"_Saryer_p")) {
            PyErr_SetString(PyExc_TypeError,"Type error in argument 1 of saryer_get_next_tagged_region2. Expected _Saryer_p.");
        return NULL;
        }
    }
    if (_argc5) {
        if (SWIG_GetPtr(_argc5,(void **) &_arg5,"_SaryInt_p")) {
            PyErr_SetString(PyExc_TypeError,"Type error in argument 6 of saryer_get_next_tagged_region2. Expected _SaryInt_p.");
        return NULL;
        }
    }
    _result = (gchar *)saryer_get_next_tagged_region2(_arg0,_arg1,_arg2,_arg3,_arg4,_arg5);
    _resultobj = Py_BuildValue("s", _result);
    return _resultobj;
}

static PyObject *_wrap_saryer_get_next_occurrence(PyObject *self, PyObject *args) {
    PyObject * _resultobj;
    SaryText * _result;
    Saryer * _arg0;
    char * _argc0 = 0;
    char _ptemp[128];

    self = self;
    if(!PyArg_ParseTuple(args,"s:saryer_get_next_occurrence",&_argc0)) 
        return NULL;
    if (_argc0) {
        if (SWIG_GetPtr(_argc0,(void **) &_arg0,"_Saryer_p")) {
            PyErr_SetString(PyExc_TypeError,"Type error in argument 1 of saryer_get_next_occurrence. Expected _Saryer_p.");
        return NULL;
        }
    }
    _result = (SaryText *)saryer_get_next_occurrence(_arg0);
    SWIG_MakePtr(_ptemp, (char *) _result,"_SaryText_p");
    _resultobj = Py_BuildValue("s",_ptemp);
    return _resultobj;
}

static PyObject *_wrap_saryer_peek_next_position(PyObject *self, PyObject *args) {
    PyObject * _resultobj;
    gchar * _result;
    Saryer * _arg0;
    char * _argc0 = 0;

    self = self;
    if(!PyArg_ParseTuple(args,"s:saryer_peek_next_position",&_argc0)) 
        return NULL;
    if (_argc0) {
        if (SWIG_GetPtr(_argc0,(void **) &_arg0,"_Saryer_p")) {
            PyErr_SetString(PyExc_TypeError,"Type error in argument 1 of saryer_peek_next_position. Expected _Saryer_p.");
        return NULL;
        }
    }
    _result = (gchar *)saryer_peek_next_position(_arg0);
    _resultobj = Py_BuildValue("s", _result);
    return _resultobj;
}

static PyObject *_wrap_saryer_count_occurrences(PyObject *self, PyObject *args) {
    PyObject * _resultobj;
    SaryInt  _result;
    Saryer * _arg0;
    char * _argc0 = 0;

    self = self;
    if(!PyArg_ParseTuple(args,"s:saryer_count_occurrences",&_argc0)) 
        return NULL;
    if (_argc0) {
        if (SWIG_GetPtr(_argc0,(void **) &_arg0,"_Saryer_p")) {
            PyErr_SetString(PyExc_TypeError,"Type error in argument 1 of saryer_count_occurrences. Expected _Saryer_p.");
        return NULL;
        }
    }
    _result = (SaryInt )saryer_count_occurrences(_arg0);
    _resultobj = Py_BuildValue("i",_result);
    return _resultobj;
}

static PyObject *_wrap_saryer_sort_occurrences(PyObject *self, PyObject *args) {
    PyObject * _resultobj;
    Saryer * _arg0;
    char * _argc0 = 0;

    self = self;
    if(!PyArg_ParseTuple(args,"s:saryer_sort_occurrences",&_argc0)) 
        return NULL;
    if (_argc0) {
        if (SWIG_GetPtr(_argc0,(void **) &_arg0,"_Saryer_p")) {
            PyErr_SetString(PyExc_TypeError,"Type error in argument 1 of saryer_sort_occurrences. Expected _Saryer_p.");
        return NULL;
        }
    }
    saryer_sort_occurrences(_arg0);
    Py_INCREF(Py_None);
    _resultobj = Py_None;
    return _resultobj;
}

static PyObject *_wrap_saryer_enable_cache(PyObject *self, PyObject *args) {
    PyObject * _resultobj;
    Saryer * _arg0;
    char * _argc0 = 0;

    self = self;
    if(!PyArg_ParseTuple(args,"s:saryer_enable_cache",&_argc0)) 
        return NULL;
    if (_argc0) {
        if (SWIG_GetPtr(_argc0,(void **) &_arg0,"_Saryer_p")) {
            PyErr_SetString(PyExc_TypeError,"Type error in argument 1 of saryer_enable_cache. Expected _Saryer_p.");
        return NULL;
        }
    }
    saryer_enable_cache(_arg0);
    Py_INCREF(Py_None);
    _resultobj = Py_None;
    return _resultobj;
}

static PyMethodDef pysaryMethods[] = {
	 { "saryer_enable_cache", _wrap_saryer_enable_cache, 1 },
	 { "saryer_sort_occurrences", _wrap_saryer_sort_occurrences, 1 },
	 { "saryer_count_occurrences", _wrap_saryer_count_occurrences, 1 },
	 { "saryer_peek_next_position", _wrap_saryer_peek_next_position, 1 },
	 { "saryer_get_next_occurrence", _wrap_saryer_get_next_occurrence, 1 },
	 { "saryer_get_next_tagged_region2", _wrap_saryer_get_next_tagged_region2, 1 },
	 { "saryer_get_next_tagged_region", _wrap_saryer_get_next_tagged_region, 1 },
	 { "saryer_get_next_context_lines2", _wrap_saryer_get_next_context_lines2, 1 },
	 { "saryer_get_next_context_lines", _wrap_saryer_get_next_context_lines, 1 },
	 { "saryer_get_next_line2", _wrap_saryer_get_next_line2, 1 },
	 { "saryer_get_next_line", _wrap_saryer_get_next_line, 1 },
	 { "saryer_get_next_offset", _wrap_saryer_get_next_offset, 1 },
	 { "saryer_get_array", _wrap_saryer_get_array, 1 },
	 { "saryer_get_text", _wrap_saryer_get_text, 1 },
	 { "saryer_icase_search2", _wrap_saryer_icase_search2, 1 },
	 { "saryer_icase_search", _wrap_saryer_icase_search, 1 },
	 { "saryer_isearch_reset", _wrap_saryer_isearch_reset, 1 },
	 { "saryer_isearch", _wrap_saryer_isearch, 1 },
	 { "saryer_search2", _wrap_saryer_search2, 1 },
	 { "saryer_search", _wrap_saryer_search, 1 },
	 { "saryer_destroy", _wrap_saryer_destroy, 1 },
	 { "saryer_new2", _wrap_saryer_new2, 1 },
	 { "saryer_new", _wrap_saryer_new, 1 },
	 { NULL, NULL }
};
static PyObject *SWIG_globals;
#ifdef __cplusplus
extern "C" 
#endif
SWIGEXPORT(void,initpysary)() {
	 PyObject *m, *d;
	 SWIG_globals = SWIG_newvarlink();
	 m = Py_InitModule("pysary", pysaryMethods);
	 d = PyModule_GetDict(m);
/*
 * These are the pointer type-equivalency mappings. 
 * (Used by the SWIG pointer type-checker).
 */
	 SWIG_RegisterMapping("_signed_long","_long",0);
	 SWIG_RegisterMapping("_long","_unsigned_long",0);
	 SWIG_RegisterMapping("_long","_signed_long",0);
	 SWIG_RegisterMapping("_gboolean","_SaryInt",0);
	 SWIG_RegisterMapping("_gboolean","_int",0);
	 SWIG_RegisterMapping("_gboolean","_signed_int",0);
	 SWIG_RegisterMapping("_gboolean","_unsigned_int",0);
	 SWIG_RegisterMapping("_char","_gchar",0);
	 SWIG_RegisterMapping("_gchar","_char",0);
	 SWIG_RegisterMapping("_unsigned_long","_long",0);
	 SWIG_RegisterMapping("_SaryInt","_int",0);
	 SWIG_RegisterMapping("_SaryInt","_signed_int",0);
	 SWIG_RegisterMapping("_SaryInt","_unsigned_int",0);
	 SWIG_RegisterMapping("_SaryInt","_gboolean",0);
	 SWIG_RegisterMapping("_signed_int","_SaryInt",0);
	 SWIG_RegisterMapping("_signed_int","_gboolean",0);
	 SWIG_RegisterMapping("_signed_int","_int",0);
	 SWIG_RegisterMapping("_unsigned_short","_short",0);
	 SWIG_RegisterMapping("_signed_short","_short",0);
	 SWIG_RegisterMapping("_unsigned_int","_SaryInt",0);
	 SWIG_RegisterMapping("_unsigned_int","_gboolean",0);
	 SWIG_RegisterMapping("_unsigned_int","_int",0);
	 SWIG_RegisterMapping("_short","_unsigned_short",0);
	 SWIG_RegisterMapping("_short","_signed_short",0);
	 SWIG_RegisterMapping("_int","_SaryInt",0);
	 SWIG_RegisterMapping("_int","_gboolean",0);
	 SWIG_RegisterMapping("_int","_unsigned_int",0);
	 SWIG_RegisterMapping("_int","_signed_int",0);
}
