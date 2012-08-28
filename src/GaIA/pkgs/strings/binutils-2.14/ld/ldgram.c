/* A Bison parser, made by GNU Bison 1.875c.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INT = 258,
     NAME = 259,
     LNAME = 260,
     OREQ = 261,
     ANDEQ = 262,
     RSHIFTEQ = 263,
     LSHIFTEQ = 264,
     DIVEQ = 265,
     MULTEQ = 266,
     MINUSEQ = 267,
     PLUSEQ = 268,
     OROR = 269,
     ANDAND = 270,
     NE = 271,
     EQ = 272,
     GE = 273,
     LE = 274,
     RSHIFT = 275,
     LSHIFT = 276,
     UNARY = 277,
     END = 278,
     ALIGN_K = 279,
     BLOCK = 280,
     BIND = 281,
     QUAD = 282,
     SQUAD = 283,
     LONG = 284,
     SHORT = 285,
     BYTE = 286,
     SECTIONS = 287,
     PHDRS = 288,
     SORT = 289,
     DATA_SEGMENT_ALIGN = 290,
     DATA_SEGMENT_END = 291,
     SIZEOF_HEADERS = 292,
     OUTPUT_FORMAT = 293,
     FORCE_COMMON_ALLOCATION = 294,
     OUTPUT_ARCH = 295,
     INHIBIT_COMMON_ALLOCATION = 296,
     INCLUDE = 297,
     MEMORY = 298,
     DEFSYMEND = 299,
     NOLOAD = 300,
     DSECT = 301,
     COPY = 302,
     INFO = 303,
     OVERLAY = 304,
     DEFINED = 305,
     TARGET_K = 306,
     SEARCH_DIR = 307,
     MAP = 308,
     ENTRY = 309,
     NEXT = 310,
     SIZEOF = 311,
     ADDR = 312,
     LOADADDR = 313,
     MAX_K = 314,
     MIN_K = 315,
     STARTUP = 316,
     HLL = 317,
     SYSLIB = 318,
     FLOAT = 319,
     NOFLOAT = 320,
     NOCROSSREFS = 321,
     ORIGIN = 322,
     FILL = 323,
     LENGTH = 324,
     CREATE_OBJECT_SYMBOLS = 325,
     INPUT = 326,
     GROUP = 327,
     OUTPUT = 328,
     CONSTRUCTORS = 329,
     ALIGNMOD = 330,
     AT = 331,
     PROVIDE = 332,
     CHIP = 333,
     LIST = 334,
     SECT = 335,
     ABSOLUTE = 336,
     LOAD = 337,
     NEWLINE = 338,
     ENDWORD = 339,
     ORDER = 340,
     NAMEWORD = 341,
     ASSERT_K = 342,
     FORMAT = 343,
     PUBLIC = 344,
     BASE = 345,
     ALIAS = 346,
     TRUNCATE = 347,
     REL = 348,
     INPUT_SCRIPT = 349,
     INPUT_MRI_SCRIPT = 350,
     INPUT_DEFSYM = 351,
     CASE = 352,
     EXTERN = 353,
     START = 354,
     VERS_TAG = 355,
     VERS_IDENTIFIER = 356,
     GLOBAL = 357,
     LOCAL = 358,
     VERSIONK = 359,
     INPUT_VERSION_SCRIPT = 360,
     KEEP = 361,
     EXCLUDE_FILE = 362
   };
#endif
#define INT 258
#define NAME 259
#define LNAME 260
#define OREQ 261
#define ANDEQ 262
#define RSHIFTEQ 263
#define LSHIFTEQ 264
#define DIVEQ 265
#define MULTEQ 266
#define MINUSEQ 267
#define PLUSEQ 268
#define OROR 269
#define ANDAND 270
#define NE 271
#define EQ 272
#define GE 273
#define LE 274
#define RSHIFT 275
#define LSHIFT 276
#define UNARY 277
#define END 278
#define ALIGN_K 279
#define BLOCK 280
#define BIND 281
#define QUAD 282
#define SQUAD 283
#define LONG 284
#define SHORT 285
#define BYTE 286
#define SECTIONS 287
#define PHDRS 288
#define SORT 289
#define DATA_SEGMENT_ALIGN 290
#define DATA_SEGMENT_END 291
#define SIZEOF_HEADERS 292
#define OUTPUT_FORMAT 293
#define FORCE_COMMON_ALLOCATION 294
#define OUTPUT_ARCH 295
#define INHIBIT_COMMON_ALLOCATION 296
#define INCLUDE 297
#define MEMORY 298
#define DEFSYMEND 299
#define NOLOAD 300
#define DSECT 301
#define COPY 302
#define INFO 303
#define OVERLAY 304
#define DEFINED 305
#define TARGET_K 306
#define SEARCH_DIR 307
#define MAP 308
#define ENTRY 309
#define NEXT 310
#define SIZEOF 311
#define ADDR 312
#define LOADADDR 313
#define MAX_K 314
#define MIN_K 315
#define STARTUP 316
#define HLL 317
#define SYSLIB 318
#define FLOAT 319
#define NOFLOAT 320
#define NOCROSSREFS 321
#define ORIGIN 322
#define FILL 323
#define LENGTH 324
#define CREATE_OBJECT_SYMBOLS 325
#define INPUT 326
#define GROUP 327
#define OUTPUT 328
#define CONSTRUCTORS 329
#define ALIGNMOD 330
#define AT 331
#define PROVIDE 332
#define CHIP 333
#define LIST 334
#define SECT 335
#define ABSOLUTE 336
#define LOAD 337
#define NEWLINE 338
#define ENDWORD 339
#define ORDER 340
#define NAMEWORD 341
#define ASSERT_K 342
#define FORMAT 343
#define PUBLIC 344
#define BASE 345
#define ALIAS 346
#define TRUNCATE 347
#define REL 348
#define INPUT_SCRIPT 349
#define INPUT_MRI_SCRIPT 350
#define INPUT_DEFSYM 351
#define CASE 352
#define EXTERN 353
#define START 354
#define VERS_TAG 355
#define VERS_IDENTIFIER 356
#define GLOBAL 357
#define LOCAL 358
#define VERSIONK 359
#define INPUT_VERSION_SCRIPT 360
#define KEEP 361
#define EXCLUDE_FILE 362




/* Copy the first part of user declarations.  */
#line 22 "ldgram.y"

/*

 */

#define DONTDECLARE_MALLOC

#include "bfd.h"
#include "sysdep.h"
#include "bfdlink.h"
#include "ld.h"
#include "ldexp.h"
#include "ldver.h"
#include "ldlang.h"
#include "ldfile.h"
#include "ldemul.h"
#include "ldmisc.h"
#include "ldmain.h"
#include "mri.h"
#include "ldctor.h"
#include "ldlex.h"

#ifndef YYDEBUG
#define YYDEBUG 1
#endif

static enum section_type sectype;

lang_memory_region_type *region;

bfd_boolean ldgram_want_filename = TRUE;
FILE *saved_script_handle = NULL;
bfd_boolean force_make_executable = FALSE;

bfd_boolean ldgram_in_script = FALSE;
bfd_boolean ldgram_had_equals = FALSE;
bfd_boolean ldgram_had_keep = FALSE;
char *ldgram_vers_current_lang = NULL;

#define ERROR_NAME_MAX 20
static char *error_names[ERROR_NAME_MAX];
static int error_index;
#define PUSH_ERROR(x) if (error_index < ERROR_NAME_MAX) error_names[error_index] = x; error_index++;
#define POP_ERROR()   error_index--;


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 67 "ldgram.y"
typedef union YYSTYPE {
  bfd_vma integer;
  struct big_int
    {
      bfd_vma integer;
      char *str;
    } bigint;
  fill_type *fill;
  char *name;
  const char *cname;
  struct wildcard_spec wildcard;
  struct wildcard_list *wildcard_list;
  struct name_list *name_list;
  int token;
  union etree_union *etree;
  struct phdr_info
    {
      bfd_boolean filehdr;
      bfd_boolean phdrs;
      union etree_union *at;
      union etree_union *flags;
    } phdr;
  struct lang_nocrossref *nocrossref;
  struct lang_output_section_phdr_list *section_phdr;
  struct bfd_elf_version_deps *deflist;
  struct bfd_elf_version_expr *versyms;
  struct bfd_elf_version_tree *versnode;
} YYSTYPE;
/* Line 191 of yacc.c.  */
#line 365 "y.tab.c"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 214 of yacc.c.  */
#line 377 "y.tab.c"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   define YYSTACK_ALLOC alloca
#  endif
# else
#  if defined (alloca) || defined (_ALLOCA_H)
#   define YYSTACK_ALLOC alloca
#  else
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC malloc
#  define YYSTACK_FREE free
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (defined (YYSTYPE_IS_TRIVIAL) && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined (__GNUC__) && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  14
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1425

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  131
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  107
/* YYNRULES -- Number of rules. */
#define YYNRULES  298
/* YYNRULES -- Number of states. */
#define YYNSTATES  611

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   362

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   129,     2,     2,     2,    34,    21,     2,
      37,   126,    32,    30,   124,    31,     2,    33,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    16,   125,
      24,     6,    25,    15,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   127,     2,   128,    20,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    51,    19,    52,   130,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     7,     8,     9,    10,    11,    12,    13,    14,    17,
      18,    22,    23,    26,    27,    28,    29,    35,    36,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short yyprhs[] =
{
       0,     0,     3,     6,     9,    12,    15,    17,    18,    23,
      24,    27,    31,    32,    35,    40,    42,    44,    47,    49,
      54,    59,    63,    66,    71,    75,    80,    85,    90,    95,
     100,   103,   106,   109,   114,   119,   122,   125,   128,   131,
     132,   138,   141,   142,   146,   149,   150,   152,   156,   158,
     162,   163,   165,   169,   171,   174,   178,   179,   182,   185,
     186,   188,   190,   192,   194,   196,   198,   200,   202,   204,
     206,   211,   216,   221,   226,   235,   240,   242,   244,   249,
     250,   256,   261,   262,   268,   273,   278,   280,   284,   287,
     289,   293,   296,   301,   304,   307,   308,   313,   316,   318,
     320,   322,   324,   330,   335,   344,   347,   349,   353,   355,
     357,   361,   366,   368,   369,   375,   378,   380,   382,   384,
     389,   391,   396,   401,   404,   406,   407,   409,   411,   413,
     415,   417,   419,   421,   424,   425,   427,   429,   431,   433,
     435,   437,   439,   441,   443,   445,   449,   453,   460,   462,
     463,   469,   472,   476,   477,   478,   486,   490,   494,   495,
     499,   501,   504,   506,   509,   514,   519,   523,   527,   529,
     534,   538,   539,   541,   543,   544,   547,   551,   552,   555,
     558,   562,   567,   570,   573,   576,   580,   584,   588,   592,
     596,   600,   604,   608,   612,   616,   620,   624,   628,   632,
     636,   640,   646,   650,   654,   659,   661,   663,   668,   673,
     678,   683,   688,   695,   700,   705,   707,   714,   721,   728,
     732,   733,   738,   739,   740,   741,   742,   743,   744,   761,
     762,   763,   764,   765,   766,   784,   785,   786,   794,   796,
     798,   800,   802,   804,   808,   809,   812,   816,   819,   826,
     837,   840,   842,   843,   845,   848,   849,   850,   854,   855,
     856,   857,   858,   870,   875,   876,   879,   880,   881,   888,
     890,   891,   895,   901,   902,   906,   907,   910,   911,   917,
     919,   922,   927,   933,   940,   942,   945,   946,   949,   954,
     959,   968,   970,   974,   975,   985,   986,   994,   995
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const short yyrhs[] =
{
     132,     0,    -1,   110,   146,    -1,   111,   136,    -1,   121,
     226,    -1,   112,   134,    -1,     4,    -1,    -1,   135,     4,
       6,   191,    -1,    -1,   137,   138,    -1,   138,   139,    99,
      -1,    -1,    94,   191,    -1,    94,   191,   124,   191,    -1,
       4,    -1,    95,    -1,   101,   141,    -1,   100,    -1,   105,
       4,     6,   191,    -1,   105,     4,   124,   191,    -1,   105,
       4,   191,    -1,   104,     4,    -1,    96,     4,   124,   191,
      -1,    96,     4,   191,    -1,    96,     4,     6,   191,    -1,
      38,     4,     6,   191,    -1,    38,     4,   124,   191,    -1,
      91,     4,     6,   191,    -1,    91,     4,   124,   191,    -1,
      97,   143,    -1,    98,   142,    -1,   102,     4,    -1,   107,
       4,   124,     4,    -1,   107,     4,   124,     3,    -1,   106,
     191,    -1,   108,     3,    -1,   113,   144,    -1,   114,   145,
      -1,    -1,    58,   133,   140,   138,    36,    -1,   115,     4,
      -1,    -1,   141,   124,     4,    -1,   141,     4,    -1,    -1,
       4,    -1,   142,   124,     4,    -1,     4,    -1,   143,   124,
       4,    -1,    -1,     4,    -1,   144,   124,     4,    -1,     4,
      -1,   145,     4,    -1,   145,   124,     4,    -1,    -1,   147,
     148,    -1,   148,   149,    -1,    -1,   173,    -1,   153,    -1,
     218,    -1,   182,    -1,   183,    -1,   185,    -1,   187,    -1,
     155,    -1,   228,    -1,   125,    -1,    67,    37,     4,   126,
      -1,    68,    37,   133,   126,    -1,    89,    37,   133,   126,
      -1,    54,    37,     4,   126,    -1,    54,    37,     4,   124,
       4,   124,     4,   126,    -1,    56,    37,     4,   126,    -1,
      55,    -1,    57,    -1,    87,    37,   152,   126,    -1,    -1,
      88,   150,    37,   152,   126,    -1,    69,    37,   133,   126,
      -1,    -1,    58,   133,   151,   148,    36,    -1,    82,    37,
     188,   126,    -1,   114,    37,   145,   126,    -1,     4,    -1,
     152,   124,     4,    -1,   152,     4,    -1,     5,    -1,   152,
     124,     5,    -1,   152,     5,    -1,    46,    51,   154,    52,
      -1,   154,   194,    -1,   154,   155,    -1,    -1,    70,    37,
       4,   126,    -1,   171,   170,    -1,     4,    -1,    32,    -1,
      15,    -1,   156,    -1,   123,    37,   158,   126,   156,    -1,
      48,    37,   156,   126,    -1,    48,    37,   123,    37,   158,
     126,   156,   126,    -1,   158,   156,    -1,   156,    -1,   159,
     172,   157,    -1,   157,    -1,     4,    -1,   127,   159,   128,
      -1,   157,    37,   159,   126,    -1,   160,    -1,    -1,   122,
      37,   162,   160,   126,    -1,   171,   170,    -1,    86,    -1,
     125,    -1,    90,    -1,    48,    37,    90,   126,    -1,   161,
      -1,   166,    37,   189,   126,    -1,    84,    37,   167,   126,
      -1,   164,   163,    -1,   163,    -1,    -1,   164,    -1,    41,
      -1,    42,    -1,    43,    -1,    44,    -1,    45,    -1,   189,
      -1,     6,   167,    -1,    -1,    14,    -1,    13,    -1,    12,
      -1,    11,    -1,    10,    -1,     9,    -1,     8,    -1,     7,
      -1,   125,    -1,   124,    -1,     4,     6,   189,    -1,     4,
     169,   189,    -1,    93,    37,     4,     6,   189,   126,    -1,
     124,    -1,    -1,    59,    51,   175,   174,    52,    -1,   174,
     175,    -1,   174,   124,   175,    -1,    -1,    -1,     4,   176,
     179,    16,   177,   172,   178,    -1,    83,     6,   189,    -1,
      85,     6,   189,    -1,    -1,    37,   180,   126,    -1,   181,
      -1,   180,   181,    -1,     4,    -1,   129,     4,    -1,    77,
      37,   133,   126,    -1,    78,    37,   184,   126,    -1,    78,
      37,   126,    -1,   184,   172,   133,    -1,   133,    -1,    79,
      37,   186,   126,    -1,   186,   172,   133,    -1,    -1,    80,
      -1,    81,    -1,    -1,     4,   188,    -1,     4,   124,   188,
      -1,    -1,   190,   191,    -1,    31,   191,    -1,    37,   191,
     126,    -1,    71,    37,   191,   126,    -1,   129,   191,    -1,
      30,   191,    -1,   130,   191,    -1,   191,    32,   191,    -1,
     191,    33,   191,    -1,   191,    34,   191,    -1,   191,    30,
     191,    -1,   191,    31,   191,    -1,   191,    29,   191,    -1,
     191,    28,   191,    -1,   191,    23,   191,    -1,   191,    22,
     191,    -1,   191,    27,   191,    -1,   191,    26,   191,    -1,
     191,    24,   191,    -1,   191,    25,   191,    -1,   191,    21,
     191,    -1,   191,    20,   191,    -1,   191,    19,   191,    -1,
     191,    15,   191,    16,   191,    -1,   191,    18,   191,    -1,
     191,    17,   191,    -1,    66,    37,     4,   126,    -1,     3,
      -1,    53,    -1,    72,    37,     4,   126,    -1,    73,    37,
       4,   126,    -1,    74,    37,     4,   126,    -1,    97,    37,
     191,   126,    -1,    38,    37,   191,   126,    -1,    49,    37,
     191,   124,   191,   126,    -1,    50,    37,   191,   126,    -1,
      39,    37,   191,   126,    -1,     4,    -1,    75,    37,   191,
     124,   191,   126,    -1,    76,    37,   191,   124,   191,   126,
      -1,   103,    37,   191,   124,     4,   126,    -1,    92,    25,
       4,    -1,    -1,    92,    37,   191,   126,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     4,   195,   209,   193,   196,    51,
     197,   165,    52,   198,   212,   192,   213,   168,   199,   172,
      -1,    -1,    -1,    -1,    -1,    -1,    65,   200,   210,   211,
     193,   201,    51,   202,   214,    52,   203,   212,   192,   213,
     168,   204,   172,    -1,    -1,    -1,    88,   205,   209,   206,
      51,   154,    52,    -1,    61,    -1,    62,    -1,    63,    -1,
      64,    -1,    65,    -1,    37,   207,   126,    -1,    -1,    37,
     126,    -1,   191,   208,    16,    -1,   208,    16,    -1,    40,
      37,   191,   126,   208,    16,    -1,    40,    37,   191,   126,
      39,    37,   191,   126,   208,    16,    -1,   191,    16,    -1,
      16,    -1,    -1,    82,    -1,    25,     4,    -1,    -1,    -1,
     213,    16,     4,    -1,    -1,    -1,    -1,    -1,   214,     4,
     215,    51,   165,    52,   216,   213,   168,   217,   172,    -1,
      47,    51,   219,    52,    -1,    -1,   219,   220,    -1,    -1,
      -1,     4,   221,   223,   224,   222,   125,    -1,   191,    -1,
      -1,     4,   225,   224,    -1,    92,    37,   191,   126,   224,
      -1,    -1,    37,   191,   126,    -1,    -1,   227,   230,    -1,
      -1,   229,   120,    51,   230,    52,    -1,   231,    -1,   230,
     231,    -1,    51,   233,    52,   125,    -1,   116,    51,   233,
      52,   125,    -1,   116,    51,   233,    52,   232,   125,    -1,
     116,    -1,   232,   116,    -1,    -1,   234,   125,    -1,   118,
      16,   234,   125,    -1,   119,    16,   234,   125,    -1,   118,
      16,   234,   125,   119,    16,   234,   125,    -1,   117,    -1,
     234,   125,   117,    -1,    -1,   234,   125,   114,     4,    51,
     235,   234,   237,    52,    -1,    -1,   114,     4,    51,   236,
     234,   237,    52,    -1,    -1,   125,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short yyrline[] =
{
       0,   162,   162,   163,   164,   165,   169,   173,   173,   183,
     183,   196,   197,   201,   202,   203,   206,   209,   210,   211,
     213,   215,   217,   219,   221,   223,   225,   227,   229,   231,
     233,   234,   235,   237,   239,   241,   243,   245,   246,   248,
     247,   251,   253,   257,   258,   259,   263,   265,   269,   271,
     276,   277,   278,   282,   284,   286,   291,   291,   302,   303,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319,   321,   323,   325,   328,   330,   332,   334,   336,   338,
     337,   341,   344,   343,   347,   351,   355,   358,   361,   364,
     367,   370,   376,   380,   381,   382,   386,   388,   394,   398,
     402,   409,   415,   421,   427,   436,   445,   456,   465,   476,
     484,   488,   495,   497,   496,   503,   504,   508,   509,   514,
     519,   520,   525,   532,   533,   536,   538,   542,   544,   546,
     548,   550,   555,   565,   567,   571,   573,   575,   577,   579,
     581,   583,   585,   590,   590,   595,   599,   607,   615,   615,
     619,   623,   624,   625,   630,   629,   637,   645,   655,   656,
     660,   661,   665,   667,   672,   677,   678,   683,   685,   691,
     693,   695,   699,   701,   707,   710,   719,   730,   730,   736,
     738,   740,   742,   744,   746,   749,   751,   753,   755,   757,
     759,   761,   763,   765,   767,   769,   771,   773,   775,   777,
     779,   781,   783,   785,   787,   789,   791,   794,   796,   798,
     800,   802,   804,   806,   808,   810,   812,   814,   816,   822,
     823,   827,   828,   831,   833,   835,   841,   843,   831,   850,
     852,   854,   859,   861,   849,   871,   873,   871,   881,   882,
     883,   884,   885,   889,   890,   891,   895,   896,   901,   902,
     907,   908,   913,   914,   919,   921,   926,   929,   942,   946,
     951,   953,   944,   961,   964,   966,   970,   971,   970,   980,
    1023,  1026,  1038,  1047,  1050,  1059,  1059,  1073,  1073,  1083,
    1084,  1088,  1092,  1096,  1103,  1107,  1115,  1118,  1122,  1126,
    1130,  1137,  1141,  1146,  1145,  1156,  1155,  1167,  1169
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "NAME", "LNAME", "'='", "OREQ",
  "ANDEQ", "RSHIFTEQ", "LSHIFTEQ", "DIVEQ", "MULTEQ", "MINUSEQ", "PLUSEQ",
  "'?'", "':'", "OROR", "ANDAND", "'|'", "'^'", "'&'", "NE", "EQ", "'<'",
  "'>'", "GE", "LE", "RSHIFT", "LSHIFT", "'+'", "'-'", "'*'", "'/'", "'%'",
  "UNARY", "END", "'('", "ALIGN_K", "BLOCK", "BIND", "QUAD", "SQUAD",
  "LONG", "SHORT", "BYTE", "SECTIONS", "PHDRS", "SORT",
  "DATA_SEGMENT_ALIGN", "DATA_SEGMENT_END", "'{'", "'}'", "SIZEOF_HEADERS",
  "OUTPUT_FORMAT", "FORCE_COMMON_ALLOCATION", "OUTPUT_ARCH",
  "INHIBIT_COMMON_ALLOCATION", "INCLUDE", "MEMORY", "DEFSYMEND", "NOLOAD",
  "DSECT", "COPY", "INFO", "OVERLAY", "DEFINED", "TARGET_K", "SEARCH_DIR",
  "MAP", "ENTRY", "NEXT", "SIZEOF", "ADDR", "LOADADDR", "MAX_K", "MIN_K",
  "STARTUP", "HLL", "SYSLIB", "FLOAT", "NOFLOAT", "NOCROSSREFS", "ORIGIN",
  "FILL", "LENGTH", "CREATE_OBJECT_SYMBOLS", "INPUT", "GROUP", "OUTPUT",
  "CONSTRUCTORS", "ALIGNMOD", "AT", "PROVIDE", "CHIP", "LIST", "SECT",
  "ABSOLUTE", "LOAD", "NEWLINE", "ENDWORD", "ORDER", "NAMEWORD",
  "ASSERT_K", "FORMAT", "PUBLIC", "BASE", "ALIAS", "TRUNCATE", "REL",
  "INPUT_SCRIPT", "INPUT_MRI_SCRIPT", "INPUT_DEFSYM", "CASE", "EXTERN",
  "START", "VERS_TAG", "VERS_IDENTIFIER", "GLOBAL", "LOCAL", "VERSIONK",
  "INPUT_VERSION_SCRIPT", "KEEP", "EXCLUDE_FILE", "','", "';'", "')'",
  "'['", "']'", "'!'", "'~'", "$accept", "file", "filename", "defsym_expr",
  "@1", "mri_script_file", "@2", "mri_script_lines", "mri_script_command",
  "@3", "ordernamelist", "mri_load_name_list", "mri_abs_name_list",
  "casesymlist", "extern_name_list", "script_file", "@4", "ifile_list",
  "ifile_p1", "@5", "@6", "input_list", "sections", "sec_or_group_p1",
  "statement_anywhere", "wildcard_name", "wildcard_spec",
  "exclude_name_list", "file_NAME_list", "input_section_spec_no_keep",
  "input_section_spec", "@7", "statement", "statement_list",
  "statement_list_opt", "length", "fill_exp", "fill_opt", "assign_op",
  "end", "assignment", "opt_comma", "memory", "memory_spec_list",
  "memory_spec", "@8", "origin_spec", "length_spec", "attributes_opt",
  "attributes_list", "attributes_string", "startup", "high_level_library",
  "high_level_library_NAME_list", "low_level_library",
  "low_level_library_NAME_list", "floating_point_support",
  "nocrossref_list", "mustbe_exp", "@9", "exp", "memspec_at_opt", "opt_at",
  "section", "@10", "@11", "@12", "@13", "@14", "@15", "@16", "@17", "@18",
  "@19", "@20", "@21", "type", "atype", "opt_exp_with_type",
  "opt_exp_without_type", "opt_nocrossrefs", "memspec_opt", "phdr_opt",
  "overlay_section", "@22", "@23", "@24", "phdrs", "phdr_list", "phdr",
  "@25", "@26", "phdr_type", "phdr_qualifiers", "phdr_val",
  "version_script_file", "@27", "version", "@28", "vers_nodes",
  "vers_node", "verdep", "vers_tag", "vers_defns", "@29", "@30",
  "opt_semicolon", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short yytoknum[] =
{
       0,   256,   257,   258,   259,   260,    61,   261,   262,   263,
     264,   265,   266,   267,   268,    63,    58,   269,   270,   124,
      94,    38,   271,   272,    60,    62,   273,   274,   275,   276,
      43,    45,    42,    47,    37,   277,   278,    40,   279,   280,
     281,   282,   283,   284,   285,   286,   287,   288,   289,   290,
     291,   123,   125,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319,   320,   321,   322,   323,   324,   325,   326,   327,   328,
     329,   330,   331,   332,   333,   334,   335,   336,   337,   338,
     339,   340,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,   352,   353,   354,   355,   356,   357,   358,
     359,   360,   361,   362,    44,    59,    41,    91,    93,    33,
     126
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,   131,   132,   132,   132,   132,   133,   135,   134,   137,
     136,   138,   138,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   140,
     139,   139,   139,   141,   141,   141,   142,   142,   143,   143,
     144,   144,   144,   145,   145,   145,   147,   146,   148,   148,
     149,   149,   149,   149,   149,   149,   149,   149,   149,   149,
     149,   149,   149,   149,   149,   149,   149,   149,   149,   150,
     149,   149,   151,   149,   149,   149,   152,   152,   152,   152,
     152,   152,   153,   154,   154,   154,   155,   155,   156,   156,
     156,   157,   157,   157,   157,   158,   158,   159,   159,   160,
     160,   160,   161,   162,   161,   163,   163,   163,   163,   163,
     163,   163,   163,   164,   164,   165,   165,   166,   166,   166,
     166,   166,   167,   168,   168,   169,   169,   169,   169,   169,
     169,   169,   169,   170,   170,   171,   171,   171,   172,   172,
     173,   174,   174,   174,   176,   175,   177,   178,   179,   179,
     180,   180,   181,   181,   182,   183,   183,   184,   184,   185,
     186,   186,   187,   187,   188,   188,   188,   190,   189,   191,
     191,   191,   191,   191,   191,   191,   191,   191,   191,   191,
     191,   191,   191,   191,   191,   191,   191,   191,   191,   191,
     191,   191,   191,   191,   191,   191,   191,   191,   191,   191,
     191,   191,   191,   191,   191,   191,   191,   191,   191,   192,
     192,   193,   193,   195,   196,   197,   198,   199,   194,   200,
     201,   202,   203,   204,   194,   205,   206,   194,   207,   207,
     207,   207,   207,   208,   208,   208,   209,   209,   209,   209,
     210,   210,   211,   211,   212,   212,   213,   213,   214,   215,
     216,   217,   214,   218,   219,   219,   221,   222,   220,   223,
     224,   224,   224,   225,   225,   227,   226,   229,   228,   230,
     230,   231,   231,   231,   232,   232,   233,   233,   233,   233,
     233,   234,   234,   235,   234,   236,   234,   237,   237
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     2,     2,     2,     2,     1,     0,     4,     0,
       2,     3,     0,     2,     4,     1,     1,     2,     1,     4,
       4,     3,     2,     4,     3,     4,     4,     4,     4,     4,
       2,     2,     2,     4,     4,     2,     2,     2,     2,     0,
       5,     2,     0,     3,     2,     0,     1,     3,     1,     3,
       0,     1,     3,     1,     2,     3,     0,     2,     2,     0,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       4,     4,     4,     4,     8,     4,     1,     1,     4,     0,
       5,     4,     0,     5,     4,     4,     1,     3,     2,     1,
       3,     2,     4,     2,     2,     0,     4,     2,     1,     1,
       1,     1,     5,     4,     8,     2,     1,     3,     1,     1,
       3,     4,     1,     0,     5,     2,     1,     1,     1,     4,
       1,     4,     4,     2,     1,     0,     1,     1,     1,     1,
       1,     1,     1,     2,     0,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     3,     6,     1,     0,
       5,     2,     3,     0,     0,     7,     3,     3,     0,     3,
       1,     2,     1,     2,     4,     4,     3,     3,     1,     4,
       3,     0,     1,     1,     0,     2,     3,     0,     2,     2,
       3,     4,     2,     2,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     5,     3,     3,     4,     1,     1,     4,     4,     4,
       4,     4,     6,     4,     4,     1,     6,     6,     6,     3,
       0,     4,     0,     0,     0,     0,     0,     0,    16,     0,
       0,     0,     0,     0,    17,     0,     0,     7,     1,     1,
       1,     1,     1,     3,     0,     2,     3,     2,     6,    10,
       2,     1,     0,     1,     2,     0,     0,     3,     0,     0,
       0,     0,    11,     4,     0,     2,     0,     0,     6,     1,
       0,     3,     5,     0,     3,     0,     2,     0,     5,     1,
       2,     4,     5,     6,     1,     2,     0,     2,     4,     4,
       8,     1,     3,     0,     9,     0,     7,     0,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned short yydefact[] =
{
       0,    56,     9,     7,   275,     0,     2,    59,     3,    12,
       5,     0,     4,     0,     1,    57,    10,     0,   286,     0,
     276,   279,     0,     0,     0,     0,    76,     0,    77,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   172,   173,
       0,     0,    79,     0,     0,     0,    69,    58,    61,    67,
       0,    60,    63,    64,    65,    66,    62,    68,     0,    15,
       0,     0,     0,     0,    16,     0,     0,     0,    18,    45,
       0,     0,     0,     0,     0,     0,    50,     0,     0,     0,
       0,     0,   291,     0,     0,     0,     0,   286,   280,   177,
     142,   141,   140,   139,   138,   137,   136,   135,   177,    95,
     264,     0,     0,     6,    82,     0,     0,     0,     0,     0,
       0,     0,   171,   174,     0,     0,     0,     0,     0,   144,
     143,    97,     0,     0,    39,     0,   205,   215,     0,     0,
       0,     0,     0,     0,     0,   206,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    13,     0,    48,
      30,    46,    31,    17,    32,    22,     0,    35,     0,    36,
      51,    37,    53,    38,    41,    11,     8,     0,     0,     0,
       0,   287,     0,   145,     0,   146,     0,     0,     0,     0,
      59,   154,   153,     0,     0,     0,     0,     0,   166,   168,
     149,   149,   174,     0,    86,    89,     0,     0,     0,     0,
       0,     0,     0,     0,    12,     0,     0,   183,   179,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   182,   184,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    24,     0,     0,
      44,     0,     0,     0,    21,     0,     0,    54,     0,   295,
       0,     0,   281,     0,   292,     0,   178,   223,    92,   229,
     235,    94,    93,   266,   263,   265,     0,    73,    75,   277,
     158,     0,    70,    71,    81,    96,   164,   148,   165,     0,
     169,     0,   174,   175,    84,    88,    91,     0,    78,     0,
      72,   177,    85,     0,    26,    27,    42,    28,    29,   180,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   203,   202,   200,   199,   198,   193,
     192,   196,   197,   195,   194,   191,   190,   188,   189,   185,
     186,   187,    14,    25,    23,    49,    47,    43,    19,    20,
      34,    33,    52,    55,     0,   288,   289,     0,   284,   282,
       0,   244,     0,   244,     0,     0,    83,     0,     0,   150,
       0,   151,   167,   170,   176,    87,    90,    80,     0,   278,
      40,   211,   214,     0,   213,   204,   181,   207,   208,   209,
       0,     0,   210,     0,     0,   297,     0,   293,   285,   283,
       0,     0,   244,     0,   222,   251,     0,   252,   236,   269,
     270,     0,   162,     0,     0,   160,     0,   152,   147,     0,
       0,     0,     0,   201,   298,     0,     0,     0,   238,   239,
     240,   241,   242,   245,     0,     0,     0,     0,   247,     0,
     224,   250,   253,   222,     0,   273,     0,   267,     0,   163,
     159,   161,     0,   149,   212,   216,   217,   218,   296,     0,
     297,   243,     0,   246,     0,     0,   230,    95,     0,   270,
       0,     0,    74,   177,     0,   290,     0,   244,     0,   225,
       0,     0,     0,   271,     0,   268,   156,     0,   155,   294,
       0,     0,   221,   125,   231,   237,   274,   270,   177,     0,
     248,   109,   100,    99,   127,   128,   129,   130,   131,     0,
       0,   116,   118,     0,     0,   117,     0,   101,     0,   112,
     120,   124,   126,     0,     0,     0,   258,   272,   157,     0,
       0,   177,   113,     0,    98,     0,   108,   149,     0,   123,
     226,   177,   115,     0,   244,     0,     0,     0,     0,   132,
       0,   106,     0,     0,   110,     0,   149,   255,     0,   259,
     232,     0,   119,     0,   103,   122,    98,     0,     0,   105,
     107,   111,     0,   220,   121,     0,   255,   249,     0,   114,
     102,   254,     0,   256,   125,   220,     0,     0,   134,     0,
     256,     0,   219,   177,     0,   227,   260,   134,   104,   133,
     257,   149,   256,   233,   228,   134,   149,   261,   234,   149,
     262
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short yydefgoto[] =
{
      -1,     5,   104,    10,    11,     8,     9,    16,    79,   204,
     153,   152,   150,   161,   163,     6,     7,    15,    47,   115,
     180,   196,    48,   176,    49,   517,   518,   552,   537,   519,
     520,   550,   521,   522,   523,   524,   548,   595,    98,   121,
      50,   555,    51,   281,   182,   280,   453,   488,   368,   414,
     415,    52,    53,   190,    54,   191,    55,   193,   549,   174,
     209,   583,   440,   272,   361,   465,   493,   557,   601,   362,
     480,   526,   576,   606,   363,   444,   434,   403,   404,   407,
     443,   573,   588,   543,   575,   602,   609,    56,   177,   275,
     364,   471,   410,   447,   469,    12,    13,    57,    58,    20,
      21,   360,    85,    86,   427,   354,   425
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -552
static const short yypact[] =
{
      92,  -552,  -552,  -552,  -552,    33,  -552,  -552,  -552,  -552,
    -552,    42,  -552,   -27,  -552,   653,   739,    57,   113,    62,
     -27,  -552,   336,    95,   146,    71,  -552,   156,  -552,    70,
     150,   170,   174,   188,   189,   196,   209,   226,  -552,  -552,
     241,   242,  -552,   243,   244,   254,  -552,  -552,  -552,  -552,
     -24,  -552,  -552,  -552,  -552,  -552,  -552,  -552,   173,  -552,
     290,    70,   291,   552,  -552,   292,   293,   294,  -552,  -552,
     299,   300,   301,   552,   302,   304,   306,   307,   308,   214,
     552,   311,  -552,   303,   310,   266,   195,   113,  -552,  -552,
    -552,  -552,  -552,  -552,  -552,  -552,  -552,  -552,  -552,  -552,
    -552,   318,   323,  -552,  -552,   326,   327,    70,    70,   329,
      70,    16,  -552,   330,   122,   314,    70,   334,   307,  -552,
    -552,  -552,   305,    75,  -552,    76,  -552,  -552,   552,   552,
     552,   316,   317,   333,   337,  -552,   338,   339,   340,   341,
     342,   343,   344,   345,   348,   552,   552,   641,   286,  -552,
     231,  -552,   247,    37,  -552,  -552,   389,  1303,   248,  -552,
    -552,   262,  -552,    64,  -552,  -552,  1303,   346,   121,   121,
     263,   123,   347,  -552,   552,  -552,    26,    19,   -31,   261,
    -552,  -552,  -552,   264,   265,   268,   270,   272,  -552,  -552,
     119,   142,    65,   274,  -552,  -552,    30,   122,   275,   397,
      61,   -27,   552,   552,  -552,   552,   552,  -552,  -552,   865,
     552,   552,   552,   552,   400,   552,   401,   403,   407,   552,
     552,   552,   552,  -552,  -552,   552,   552,   552,   552,   552,
     552,   552,   552,   552,   552,   552,   552,   552,   552,   552,
     552,   552,   552,   552,   552,   552,   552,  1303,   408,   410,
    -552,   413,   552,   552,  1303,   114,   418,  -552,   419,  -552,
     309,   315,  -552,   420,  -552,   -67,  1303,   336,  -552,  -552,
    -552,  -552,  -552,  -552,  -552,  -552,   421,  -552,  -552,   702,
     392,    23,  -552,  -552,  -552,  -552,  -552,  -552,  -552,    70,
    -552,    70,   330,  -552,  -552,  -552,  -552,   126,  -552,    68,
    -552,  -552,  -552,   -14,  1303,  1303,   764,  1303,  1303,  -552,
     885,   905,  1165,   925,   319,   945,   320,   321,   322,  1195,
    1215,   975,  1235,  1345,  1322,  1253,  1380,   445,   781,  1391,
    1391,   335,   335,   335,   335,   225,   225,   219,   219,  -552,
    -552,  -552,  1303,  1303,  1303,  -552,  -552,  -552,  1303,  1303,
    -552,  -552,  -552,  -552,   121,    91,   123,   379,  -552,  -552,
     -26,   450,   501,   450,   552,   312,  -552,     4,   415,  -552,
     326,  -552,  -552,  -552,  -552,  -552,  -552,  -552,   324,  -552,
    -552,  -552,  -552,   552,  -552,  -552,  -552,  -552,  -552,  -552,
     552,   552,  -552,   428,   552,   331,   417,  -552,  -552,  -552,
     211,   398,  1273,   425,   351,  -552,  1365,   362,  -552,  1303,
      17,   447,  -552,   453,     3,  -552,   366,  -552,  -552,   995,
    1015,  1035,   332,  1303,   123,   430,   121,   121,  -552,  -552,
    -552,  -552,  -552,  -552,   357,   552,    60,   443,  -552,   448,
    -552,  -552,  -552,   351,   433,   454,   456,  -552,   368,  -552,
    -552,  -552,   489,   372,  -552,  -552,  -552,  -552,  -552,   373,
     331,  -552,  1055,  -552,   552,   446,  -552,  -552,   552,    17,
     552,   376,  -552,  -552,   422,   123,   457,    98,  1085,  -552,
     451,    27,  1105,  -552,  1125,  -552,  -552,   500,  -552,  -552,
     471,   494,  -552,   602,  -552,  -552,  -552,    17,  -552,   552,
    -552,   210,  -552,  -552,  -552,  -552,  -552,  -552,  -552,   474,
     475,  -552,  -552,   477,   478,  -552,    32,  -552,   483,  -552,
    -552,  -552,   602,   476,   490,   -24,  -552,  -552,  -552,  1145,
      72,  -552,  -552,    25,  -552,   492,  -552,   -21,    32,  -552,
    -552,  -552,  -552,    46,   493,   409,   496,   411,   416,  -552,
      11,  -552,    10,    73,  -552,    32,   143,   509,   423,  -552,
    -552,   520,  -552,    25,  -552,  -552,   426,   431,    25,  -552,
    -552,  -552,   537,   452,  -552,   495,   509,  -552,    13,  -552,
    -552,  -552,   518,  -552,   602,   452,    25,   541,    38,   506,
    -552,   434,  -552,  -552,   544,  -552,  -552,    38,  -552,  -552,
    -552,   372,  -552,  -552,  -552,    38,   372,  -552,  -552,   372,
    -552
};

/* YYPGOTO[NTERM-NUM].  */
static const short yypgoto[] =
{
    -552,  -552,   -55,  -552,  -552,  -552,  -552,   355,  -552,  -552,
    -552,  -552,  -552,  -552,   444,  -552,  -552,   381,  -552,  -552,
    -552,   367,  -552,    96,  -172,  -324,  -410,     2,    28,    18,
    -552,  -552,    47,  -552,   -13,  -552,   -23,  -535,  -552,    53,
    -474,  -188,  -552,  -552,  -259,  -552,  -552,  -552,  -552,  -552,
     167,  -552,  -552,  -552,  -552,  -552,  -552,  -176,   -89,  -552,
     -62,    -1,   144,  -552,  -552,  -552,  -552,  -552,  -552,  -552,
    -552,  -552,  -552,  -552,  -552,  -552,  -552,  -392,   222,  -552,
    -552,    12,  -551,  -552,  -552,  -552,  -552,  -552,  -552,  -552,
    -552,  -552,  -552,  -437,  -552,  -552,  -552,  -552,  -552,   385,
     -15,  -552,   505,  -156,  -552,  -552,   133
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -278
static const short yytable[] =
{
     173,   147,   289,   291,   271,    88,   124,   412,   412,   175,
     437,   157,   260,   261,   534,   566,   293,   534,   166,   525,
     103,   445,   371,   273,    18,   502,   502,   181,   502,   534,
     267,   267,   483,    14,   295,   296,   534,    18,   379,   597,
     502,   250,   503,   503,   593,   503,    17,   502,   525,   358,
     559,   605,   184,   185,   594,   187,   189,   503,   359,   535,
     527,   198,   603,    80,   503,   257,   207,   208,   257,   192,
     607,   274,   295,   296,   103,   369,   534,   534,   268,   495,
     535,   202,   205,   223,   224,   491,   247,   502,   502,    19,
     398,   269,   269,   276,   254,   277,    34,    34,   560,   399,
     119,   120,    19,   287,   503,   503,   536,   554,   101,   446,
     525,   417,   266,    87,   270,   270,   374,   350,   351,    44,
      44,   428,   429,   430,   431,   432,   194,   195,   536,   450,
     375,   376,   413,   413,   514,   436,   568,   490,   516,   586,
     304,   305,   188,   307,   308,   570,    99,   370,   310,   311,
     312,   313,   561,   315,   297,   514,   298,   319,   320,   321,
     322,   251,   545,   323,   324,   325,   326,   327,   328,   329,
     330,   331,   332,   333,   334,   335,   336,   337,   338,   339,
     340,   341,   342,   343,   344,   258,   433,   302,   258,   292,
     348,   349,   297,   102,   377,   546,   546,   100,   395,   203,
     206,   105,     1,     2,     3,   263,   547,   106,   264,   551,
     396,   107,   378,     4,   126,   127,    89,    90,    91,    92,
      93,    94,    95,    96,    97,   108,   109,    81,   569,   547,
      82,    83,    84,   110,   372,    81,   373,   263,    82,   551,
     264,   128,   129,   287,   580,   288,   111,   -98,   130,   131,
     132,   241,   242,   243,   569,   239,   240,   241,   242,   243,
     133,   134,   591,   112,   135,   474,   287,   287,   290,   571,
     459,   460,   428,   429,   430,   431,   432,   136,   113,   114,
     116,   117,   137,   138,   139,   140,   141,   142,    88,   126,
     127,   118,   245,   122,   123,   125,   148,   149,   151,   402,
     406,   402,   409,   154,   155,   156,   158,   159,   143,   271,
     160,   162,   164,   165,   144,   167,   128,   129,   170,   168,
     171,   419,   178,   130,   131,   132,   169,   179,   420,   421,
     181,   183,   423,   186,   192,   133,   134,   433,   199,   135,
     145,   146,    89,    90,    91,    92,    93,    94,    95,    96,
      97,   197,   136,   210,   211,   248,   201,   137,   138,   139,
     140,   141,   142,   237,   238,   239,   240,   241,   242,   243,
     212,   249,   255,   462,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   143,   486,   222,   256,   278,   262,   144,
     282,   283,   126,   127,   284,   252,   285,   259,   286,   265,
     294,   300,   478,   301,   314,   316,   482,   317,   484,   528,
     246,   318,   345,   604,   346,   145,   146,   347,   608,   128,
     129,   610,   352,   353,   357,   365,   130,   131,   132,   367,
     397,   416,   422,   426,   355,   435,   411,   529,   133,   134,
     356,   438,   135,   439,   442,   385,   387,   388,   389,   452,
     418,   448,   558,   126,   127,   136,   424,   449,   457,   463,
     137,   138,   139,   140,   141,   142,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     128,   129,   458,   461,   467,   464,   143,   400,   131,   132,
     401,   468,   144,   470,   472,   473,   287,   479,   475,   133,
     134,   485,   494,   135,   126,   127,   498,   487,   499,   489,
     500,   530,   531,   253,   532,   533,   136,   405,   145,   146,
     538,   137,   138,   139,   140,   141,   142,   541,   540,   553,
     436,   128,   129,   563,   572,   562,   577,   564,   130,   131,
     132,   581,   565,   587,   582,   592,   584,   143,   600,   574,
     133,   134,  -109,   144,   135,   126,   127,   579,   596,   306,
     598,   279,   200,   481,   299,   578,   556,   136,   567,   539,
     599,   589,   137,   138,   139,   140,   141,   142,   542,   145,
     146,   451,   128,   129,   590,   408,   303,   466,   585,   130,
     131,   132,   172,   476,     0,     0,     0,     0,   143,     0,
       0,   133,   134,     0,   144,   135,   501,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   502,   136,     0,
       0,     0,     0,   137,   138,   139,   140,   141,   142,     0,
     145,   146,     0,     0,   503,     0,     0,     0,     0,     0,
       0,     0,     0,   504,   505,   506,   507,   508,     0,   143,
     509,     0,     0,     0,     0,   144,   225,    22,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,     0,     0,     0,     0,
       0,   145,   146,     0,     0,     0,   510,     0,   511,     0,
       0,     0,   512,     0,     0,    44,     0,     0,     0,    23,
      24,     0,     0,     0,     0,     0,    22,    25,    26,    27,
      28,    29,    30,     0,     0,     0,     0,     0,     0,     0,
      31,    32,    33,    34,   513,   514,     0,   515,     0,   516,
      35,    36,    37,    38,    39,    40,     0,     0,   366,     0,
      41,    42,    43,    59,     0,     0,    44,     0,    23,    24,
       0,     0,     0,     0,     0,     0,    25,    26,    27,    28,
      29,    30,     0,     0,     0,   244,     0,    45,    59,    31,
      32,    33,    34,  -277,     0,     0,     0,    60,    46,    35,
      36,    37,    38,    39,    40,     0,     0,     0,     0,    41,
      42,    43,     0,     0,     0,    44,     0,    61,     0,     0,
     380,     0,    60,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,    45,     0,     0,     0,
       0,     0,    61,     0,     0,     0,     0,    46,     0,     0,
      62,     0,     0,    63,    64,    65,    66,    67,   -42,    68,
      69,    70,     0,    71,    72,    73,    74,    75,     0,     0,
       0,     0,    76,    77,    78,    62,     0,     0,    63,    64,
      65,    66,    67,     0,    68,    69,    70,     0,    71,    72,
      73,    74,    75,     0,     0,     0,     0,    76,    77,    78,
     225,     0,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     225,     0,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     225,     0,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     225,     0,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     225,     0,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     225,   309,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     225,   381,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     225,   382,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     225,   384,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     225,   386,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     225,   392,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     225,   454,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     225,   455,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     225,   456,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     225,   477,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     225,   492,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     225,   496,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     225,   497,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
       0,   544,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,   243,   225,   383,
     226,   227,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,   243,     0,     0,
     436,     0,     0,     0,     0,     0,     0,     0,   225,   390,
     226,   227,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,   243,     0,   391,
     227,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,   243,     0,     0,   393,
     225,   394,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     225,   441,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,   243,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243
};

static const short yycheck[] =
{
      89,    63,   190,   191,   176,    20,    61,     4,     4,    98,
     402,    73,   168,   169,     4,     4,   192,     4,    80,   493,
       4,     4,   281,     4,    51,    15,    15,     4,    15,     4,
       4,     4,   469,     0,     4,     5,     4,    51,    52,   590,
      15,     4,    32,    32,     6,    32,     4,    15,   522,   116,
       4,   602,   107,   108,    16,   110,   111,    32,   125,    48,
     497,   116,   597,     6,    32,     4,   128,   129,     4,     4,
     605,    52,     4,     5,     4,    52,     4,     4,    52,    52,
      48,     6,     6,   145,   146,   477,   148,    15,    15,   116,
     116,    65,    65,   124,   156,   126,    70,    70,    52,   125,
     124,   125,   116,   124,    32,    32,   516,   128,    37,    92,
     584,   370,   174,    51,    88,    88,   292,     3,     4,    93,
      93,    61,    62,    63,    64,    65,     4,     5,   538,   126,
       4,     5,   129,   129,   123,    37,   126,    39,   127,   126,
     202,   203,   126,   205,   206,   555,    51,   124,   210,   211,
     212,   213,   544,   215,   124,   123,   126,   219,   220,   221,
     222,   124,    90,   225,   226,   227,   228,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,   243,   244,   245,   246,   124,   126,   126,   124,   124,
     252,   253,   124,    37,   126,   123,   123,    51,   354,   124,
     124,    51,   110,   111,   112,   114,   530,    37,   117,   533,
     119,    37,   301,   121,     3,     4,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    37,    37,   114,   552,   553,
     117,   118,   119,    37,   289,   114,   291,   114,   117,   563,
     117,    30,    31,   124,   568,   126,    37,    37,    37,    38,
      39,    32,    33,    34,   578,    30,    31,    32,    33,    34,
      49,    50,   586,    37,    53,   453,   124,   124,   126,   126,
     426,   427,    61,    62,    63,    64,    65,    66,    37,    37,
      37,    37,    71,    72,    73,    74,    75,    76,   303,     3,
       4,    37,     6,   120,     4,     4,     4,     4,     4,   361,
     362,   363,   364,     4,     4,     4,     4,     3,    97,   481,
       4,     4,     4,    99,   103,     4,    30,    31,    52,    16,
     125,   383,     4,    37,    38,    39,    16,     4,   390,   391,
       4,     4,   394,     4,     4,    49,    50,   126,     4,    53,
     129,   130,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    37,    66,    37,    37,   124,    51,    71,    72,    73,
      74,    75,    76,    28,    29,    30,    31,    32,    33,    34,
      37,   124,   124,   435,    37,    37,    37,    37,    37,    37,
      37,    37,    37,    97,   473,    37,   124,   126,   125,   103,
     126,   126,     3,     4,   126,     6,   126,    51,   126,    52,
     126,   126,   464,     6,     4,     4,   468,     4,   470,   498,
     124,     4,     4,   601,     4,   129,   130,     4,   606,    30,
      31,   609,     4,     4,     4,     4,    37,    38,    39,    37,
      51,    16,     4,    16,   125,    37,   124,   499,    49,    50,
     125,    16,    53,    92,    82,   126,   126,   126,   126,    83,
     126,     4,   541,     3,     4,    66,   125,     4,   126,    16,
      71,    72,    73,    74,    75,    76,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      30,    31,    52,   126,    51,    37,    97,    37,    38,    39,
      40,    37,   103,    37,   126,     6,   124,    51,   125,    49,
      50,   125,    51,    53,     3,     4,     6,    85,    37,    52,
      16,    37,    37,   124,    37,    37,    66,    16,   129,   130,
      37,    71,    72,    73,    74,    75,    76,    37,    52,    37,
      37,    30,    31,    37,    25,   126,    16,   126,    37,    38,
      39,     4,   126,    25,    92,     4,    51,    97,     4,   126,
      49,    50,   126,   103,    53,     3,     4,   126,    52,   204,
     126,   180,   118,   467,   197,   563,   538,    66,   550,   522,
     593,   584,    71,    72,    73,    74,    75,    76,   525,   129,
     130,   414,    30,    31,   585,   363,   201,   443,   576,    37,
      38,    39,    87,   460,    -1,    -1,    -1,    -1,    97,    -1,
      -1,    49,    50,    -1,   103,    53,     4,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    15,    66,    -1,
      -1,    -1,    -1,    71,    72,    73,    74,    75,    76,    -1,
     129,   130,    -1,    -1,    32,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    41,    42,    43,    44,    45,    -1,    97,
      48,    -1,    -1,    -1,    -1,   103,    15,     4,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    -1,    -1,    -1,    -1,
      -1,   129,   130,    -1,    -1,    -1,    84,    -1,    86,    -1,
      -1,    -1,    90,    -1,    -1,    93,    -1,    -1,    -1,    46,
      47,    -1,    -1,    -1,    -1,    -1,     4,    54,    55,    56,
      57,    58,    59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      67,    68,    69,    70,   122,   123,    -1,   125,    -1,   127,
      77,    78,    79,    80,    81,    82,    -1,    -1,    36,    -1,
      87,    88,    89,     4,    -1,    -1,    93,    -1,    46,    47,
      -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    59,    -1,    -1,    -1,   124,    -1,   114,     4,    67,
      68,    69,    70,   120,    -1,    -1,    -1,    38,   125,    77,
      78,    79,    80,    81,    82,    -1,    -1,    -1,    -1,    87,
      88,    89,    -1,    -1,    -1,    93,    -1,    58,    -1,    -1,
      36,    -1,    38,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,   114,    -1,    -1,    -1,
      -1,    -1,    58,    -1,    -1,    -1,    -1,   125,    -1,    -1,
      91,    -1,    -1,    94,    95,    96,    97,    98,    99,   100,
     101,   102,    -1,   104,   105,   106,   107,   108,    -1,    -1,
      -1,    -1,   113,   114,   115,    91,    -1,    -1,    94,    95,
      96,    97,    98,    -1,   100,   101,   102,    -1,   104,   105,
     106,   107,   108,    -1,    -1,    -1,    -1,   113,   114,   115,
      15,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      15,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      15,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      15,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      15,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      15,   126,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      15,   126,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      15,   126,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      15,   126,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      15,   126,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      15,   126,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      15,   126,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      15,   126,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      15,   126,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      15,   126,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      15,   126,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      15,   126,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      15,   126,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      -1,   126,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    15,   124,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    -1,    -1,
      37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    15,   124,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    -1,   124,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    -1,    -1,   124,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,   110,   111,   112,   121,   132,   146,   147,   136,   137,
     134,   135,   226,   227,     0,   148,   138,     4,    51,   116,
     230,   231,     4,    46,    47,    54,    55,    56,    57,    58,
      59,    67,    68,    69,    70,    77,    78,    79,    80,    81,
      82,    87,    88,    89,    93,   114,   125,   149,   153,   155,
     171,   173,   182,   183,   185,   187,   218,   228,   229,     4,
      38,    58,    91,    94,    95,    96,    97,    98,   100,   101,
     102,   104,   105,   106,   107,   108,   113,   114,   115,   139,
       6,   114,   117,   118,   119,   233,   234,    51,   231,     6,
       7,     8,     9,    10,    11,    12,    13,    14,   169,    51,
      51,    37,    37,     4,   133,    51,    37,    37,    37,    37,
      37,    37,    37,    37,    37,   150,    37,    37,    37,   124,
     125,   170,   120,     4,   133,     4,     3,     4,    30,    31,
      37,    38,    39,    49,    50,    53,    66,    71,    72,    73,
      74,    75,    76,    97,   103,   129,   130,   191,     4,     4,
     143,     4,   142,   141,     4,     4,     4,   191,     4,     3,
       4,   144,     4,   145,     4,    99,   191,     4,    16,    16,
      52,   125,   233,   189,   190,   189,   154,   219,     4,     4,
     151,     4,   175,     4,   133,   133,     4,   133,   126,   133,
     184,   186,     4,   188,     4,     5,   152,    37,   133,     4,
     145,    51,     6,   124,   140,     6,   124,   191,   191,   191,
      37,    37,    37,    37,    37,    37,    37,    37,    37,    37,
      37,    37,    37,   191,   191,    15,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,   124,     6,   124,   191,   124,   124,
       4,   124,     6,   124,   191,   124,   124,     4,   124,    51,
     234,   234,   125,   114,   117,    52,   191,     4,    52,    65,
      88,   155,   194,     4,    52,   220,   124,   126,   126,   148,
     176,   174,   126,   126,   126,   126,   126,   124,   126,   172,
     126,   172,   124,   188,   126,     4,     5,   124,   126,   152,
     126,     6,   126,   230,   191,   191,   138,   191,   191,   126,
     191,   191,   191,   191,     4,   191,     4,     4,     4,   191,
     191,   191,   191,   191,   191,   191,   191,   191,   191,   191,
     191,   191,   191,   191,   191,   191,   191,   191,   191,   191,
     191,   191,   191,   191,   191,     4,     4,     4,   191,   191,
       3,     4,     4,     4,   236,   125,   125,     4,   116,   125,
     232,   195,   200,   205,   221,     4,    36,    37,   179,    52,
     124,   175,   133,   133,   188,     4,     5,   126,   189,    52,
      36,   126,   126,   124,   126,   126,   126,   126,   126,   126,
     124,   124,   126,   124,    16,   234,   119,    51,   116,   125,
      37,    40,   191,   208,   209,    16,   191,   210,   209,   191,
     223,   124,     4,   129,   180,   181,    16,   175,   126,   191,
     191,   191,     4,   191,   125,   237,    16,   235,    61,    62,
      63,    64,    65,   126,   207,    37,    37,   208,    16,    92,
     193,    16,    82,   211,   206,     4,    92,   224,     4,     4,
     126,   181,    83,   177,   126,   126,   126,   126,    52,   234,
     234,   126,   191,    16,    37,   196,   193,    51,    37,   225,
      37,   222,   126,     6,   172,   125,   237,   126,   191,    51,
     201,   154,   191,   224,   191,   125,   189,    85,   178,    52,
      39,   208,   126,   197,    51,    52,   126,   126,     6,    37,
      16,     4,    15,    32,    41,    42,    43,    44,    45,    48,
      84,    86,    90,   122,   123,   125,   127,   156,   157,   160,
     161,   163,   164,   165,   166,   171,   202,   224,   189,   191,
      37,    37,    37,    37,     4,    48,   157,   159,    37,   163,
      52,    37,   170,   214,   126,    90,   123,   156,   167,   189,
     162,   156,   158,    37,   128,   172,   159,   198,   189,     4,
      52,   208,   126,    37,   126,   126,     4,   160,   126,   156,
     157,   126,    25,   212,   126,   215,   203,    16,   158,   126,
     156,     4,    92,   192,    51,   212,   126,    25,   213,   165,
     192,   156,     4,     6,    16,   168,    52,   213,   126,   167,
       4,   199,   216,   168,   172,   213,   204,   168,   172,   217,
     172
};

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)		\
   ((Current).first_line   = (Rhs)[1].first_line,	\
    (Current).first_column = (Rhs)[1].first_column,	\
    (Current).last_line    = (Rhs)[N].last_line,	\
    (Current).last_column  = (Rhs)[N].last_column)
#endif

/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (0)

# define YYDSYMPRINT(Args)			\
do {						\
  if (yydebug)					\
    yysymprint Args;				\
} while (0)

# define YYDSYMPRINTF(Title, Token, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr, 					\
                  Token, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short *bottom, short *top)
#else
static void
yy_stack_print (bottom, top)
    short *bottom;
    short *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print (int yyrule)
#else
static void
yy_reduce_print (yyrule)
    int yyrule;
#endif
{
  int yyi;
  unsigned int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
             yyrule - 1, yylno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname [yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname [yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (Rule);		\
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YYDSYMPRINT(Args)
# define YYDSYMPRINTF(Title, Token, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if defined (YYMAXDEPTH) && YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

#endif /* !YYERROR_VERBOSE */



#if YYDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (yytype < YYNTOKENS)
    {
      YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
# ifdef YYPRINT
      YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
    }
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yydestruct (int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yytype, yyvaluep)
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  switch (yytype)
    {

      default:
        break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM);
# else
int yyparse ();
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;



#define YYPOPSTACK   (yyvsp--, yyssp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YYDSYMPRINTF ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %s, ", yytname[yytoken]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;


  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 7:
#line 173 "ldgram.y"
    { ldlex_defsym(); }
    break;

  case 8:
#line 175 "ldgram.y"
    {
		  ldlex_popstate();
		  lang_add_assignment(exp_assop(yyvsp[-1].token,yyvsp[-2].name,yyvsp[0].etree));
		}
    break;

  case 9:
#line 183 "ldgram.y"
    {
		  ldlex_mri_script ();
		  PUSH_ERROR (_("MRI style script"));
		}
    break;

  case 10:
#line 188 "ldgram.y"
    {
		  ldlex_popstate ();
		  mri_draw_tree ();
		  POP_ERROR ();
		}
    break;

  case 15:
#line 203 "ldgram.y"
    {
			einfo(_("%P%F: unrecognised keyword in MRI style script '%s'\n"),yyvsp[0].name);
			}
    break;

  case 16:
#line 206 "ldgram.y"
    {
			config.map_filename = "-";
			}
    break;

  case 19:
#line 212 "ldgram.y"
    { mri_public(yyvsp[-2].name, yyvsp[0].etree); }
    break;

  case 20:
#line 214 "ldgram.y"
    { mri_public(yyvsp[-2].name, yyvsp[0].etree); }
    break;

  case 21:
#line 216 "ldgram.y"
    { mri_public(yyvsp[-1].name, yyvsp[0].etree); }
    break;

  case 22:
#line 218 "ldgram.y"
    { mri_format(yyvsp[0].name); }
    break;

  case 23:
#line 220 "ldgram.y"
    { mri_output_section(yyvsp[-2].name, yyvsp[0].etree);}
    break;

  case 24:
#line 222 "ldgram.y"
    { mri_output_section(yyvsp[-1].name, yyvsp[0].etree);}
    break;

  case 25:
#line 224 "ldgram.y"
    { mri_output_section(yyvsp[-2].name, yyvsp[0].etree);}
    break;

  case 26:
#line 226 "ldgram.y"
    { mri_align(yyvsp[-2].name,yyvsp[0].etree); }
    break;

  case 27:
#line 228 "ldgram.y"
    { mri_align(yyvsp[-2].name,yyvsp[0].etree); }
    break;

  case 28:
#line 230 "ldgram.y"
    { mri_alignmod(yyvsp[-2].name,yyvsp[0].etree); }
    break;

  case 29:
#line 232 "ldgram.y"
    { mri_alignmod(yyvsp[-2].name,yyvsp[0].etree); }
    break;

  case 32:
#line 236 "ldgram.y"
    { mri_name(yyvsp[0].name); }
    break;

  case 33:
#line 238 "ldgram.y"
    { mri_alias(yyvsp[-2].name,yyvsp[0].name,0);}
    break;

  case 34:
#line 240 "ldgram.y"
    { mri_alias (yyvsp[-2].name, 0, (int) yyvsp[0].bigint.integer); }
    break;

  case 35:
#line 242 "ldgram.y"
    { mri_base(yyvsp[0].etree); }
    break;

  case 36:
#line 244 "ldgram.y"
    { mri_truncate ((unsigned int) yyvsp[0].bigint.integer); }
    break;

  case 39:
#line 248 "ldgram.y"
    { ldlex_script (); ldfile_open_command_file(yyvsp[0].name); }
    break;

  case 40:
#line 250 "ldgram.y"
    { ldlex_popstate (); }
    break;

  case 41:
#line 252 "ldgram.y"
    { lang_add_entry (yyvsp[0].name, FALSE); }
    break;

  case 43:
#line 257 "ldgram.y"
    { mri_order(yyvsp[0].name); }
    break;

  case 44:
#line 258 "ldgram.y"
    { mri_order(yyvsp[0].name); }
    break;

  case 46:
#line 264 "ldgram.y"
    { mri_load(yyvsp[0].name); }
    break;

  case 47:
#line 265 "ldgram.y"
    { mri_load(yyvsp[0].name); }
    break;

  case 48:
#line 270 "ldgram.y"
    { mri_only_load(yyvsp[0].name); }
    break;

  case 49:
#line 272 "ldgram.y"
    { mri_only_load(yyvsp[0].name); }
    break;

  case 50:
#line 276 "ldgram.y"
    { yyval.name = NULL; }
    break;

  case 53:
#line 283 "ldgram.y"
    { ldlang_add_undef (yyvsp[0].name); }
    break;

  case 54:
#line 285 "ldgram.y"
    { ldlang_add_undef (yyvsp[0].name); }
    break;

  case 55:
#line 287 "ldgram.y"
    { ldlang_add_undef (yyvsp[0].name); }
    break;

  case 56:
#line 291 "ldgram.y"
    {
	 ldlex_both();
	}
    break;

  case 57:
#line 295 "ldgram.y"
    {
	ldlex_popstate();
	}
    break;

  case 70:
#line 320 "ldgram.y"
    { lang_add_target(yyvsp[-1].name); }
    break;

  case 71:
#line 322 "ldgram.y"
    { ldfile_add_library_path (yyvsp[-1].name, FALSE); }
    break;

  case 72:
#line 324 "ldgram.y"
    { lang_add_output(yyvsp[-1].name, 1); }
    break;

  case 73:
#line 326 "ldgram.y"
    { lang_add_output_format (yyvsp[-1].name, (char *) NULL,
					    (char *) NULL, 1); }
    break;

  case 74:
#line 329 "ldgram.y"
    { lang_add_output_format (yyvsp[-5].name, yyvsp[-3].name, yyvsp[-1].name, 1); }
    break;

  case 75:
#line 331 "ldgram.y"
    { ldfile_set_output_arch(yyvsp[-1].name); }
    break;

  case 76:
#line 333 "ldgram.y"
    { command_line.force_common_definition = TRUE ; }
    break;

  case 77:
#line 335 "ldgram.y"
    { command_line.inhibit_common_definition = TRUE ; }
    break;

  case 79:
#line 338 "ldgram.y"
    { lang_enter_group (); }
    break;

  case 80:
#line 340 "ldgram.y"
    { lang_leave_group (); }
    break;

  case 81:
#line 342 "ldgram.y"
    { lang_add_map(yyvsp[-1].name); }
    break;

  case 82:
#line 344 "ldgram.y"
    { ldlex_script (); ldfile_open_command_file(yyvsp[0].name); }
    break;

  case 83:
#line 346 "ldgram.y"
    { ldlex_popstate (); }
    break;

  case 84:
#line 348 "ldgram.y"
    {
		  lang_add_nocrossref (yyvsp[-1].nocrossref);
		}
    break;

  case 86:
#line 356 "ldgram.y"
    { lang_add_input_file(yyvsp[0].name,lang_input_file_is_search_file_enum,
				 (char *)NULL); }
    break;

  case 87:
#line 359 "ldgram.y"
    { lang_add_input_file(yyvsp[0].name,lang_input_file_is_search_file_enum,
				 (char *)NULL); }
    break;

  case 88:
#line 362 "ldgram.y"
    { lang_add_input_file(yyvsp[0].name,lang_input_file_is_search_file_enum,
				 (char *)NULL); }
    break;

  case 89:
#line 365 "ldgram.y"
    { lang_add_input_file(yyvsp[0].name,lang_input_file_is_l_enum,
				 (char *)NULL); }
    break;

  case 90:
#line 368 "ldgram.y"
    { lang_add_input_file(yyvsp[0].name,lang_input_file_is_l_enum,
				 (char *)NULL); }
    break;

  case 91:
#line 371 "ldgram.y"
    { lang_add_input_file(yyvsp[0].name,lang_input_file_is_l_enum,
				 (char *)NULL); }
    break;

  case 96:
#line 387 "ldgram.y"
    { lang_add_entry (yyvsp[-1].name, FALSE); }
    break;

  case 98:
#line 395 "ldgram.y"
    {
			  yyval.cname = yyvsp[0].name;
			}
    break;

  case 99:
#line 399 "ldgram.y"
    {
			  yyval.cname = "*";
			}
    break;

  case 100:
#line 403 "ldgram.y"
    {
			  yyval.cname = "?";
			}
    break;

  case 101:
#line 410 "ldgram.y"
    {
			  yyval.wildcard.name = yyvsp[0].cname;
			  yyval.wildcard.sorted = FALSE;
			  yyval.wildcard.exclude_name_list = NULL;
			}
    break;

  case 102:
#line 416 "ldgram.y"
    {
			  yyval.wildcard.name = yyvsp[0].cname;
			  yyval.wildcard.sorted = FALSE;
			  yyval.wildcard.exclude_name_list = yyvsp[-2].name_list;
			}
    break;

  case 103:
#line 422 "ldgram.y"
    {
			  yyval.wildcard.name = yyvsp[-1].cname;
			  yyval.wildcard.sorted = TRUE;
			  yyval.wildcard.exclude_name_list = NULL;
			}
    break;

  case 104:
#line 428 "ldgram.y"
    {
			  yyval.wildcard.name = yyvsp[-1].cname;
			  yyval.wildcard.sorted = TRUE;
			  yyval.wildcard.exclude_name_list = yyvsp[-3].name_list;
			}
    break;

  case 105:
#line 437 "ldgram.y"
    {
			  struct name_list *tmp;
			  tmp = (struct name_list *) xmalloc (sizeof *tmp);
			  tmp->name = yyvsp[0].cname;
			  tmp->next = yyvsp[-1].name_list;
			  yyval.name_list = tmp;
			}
    break;

  case 106:
#line 446 "ldgram.y"
    {
			  struct name_list *tmp;
			  tmp = (struct name_list *) xmalloc (sizeof *tmp);
			  tmp->name = yyvsp[0].cname;
			  tmp->next = NULL;
			  yyval.name_list = tmp;
			}
    break;

  case 107:
#line 457 "ldgram.y"
    {
			  struct wildcard_list *tmp;
			  tmp = (struct wildcard_list *) xmalloc (sizeof *tmp);
			  tmp->next = yyvsp[-2].wildcard_list;
			  tmp->spec = yyvsp[0].wildcard;
			  yyval.wildcard_list = tmp;
			}
    break;

  case 108:
#line 466 "ldgram.y"
    {
			  struct wildcard_list *tmp;
			  tmp = (struct wildcard_list *) xmalloc (sizeof *tmp);
			  tmp->next = NULL;
			  tmp->spec = yyvsp[0].wildcard;
			  yyval.wildcard_list = tmp;
			}
    break;

  case 109:
#line 477 "ldgram.y"
    {
			  struct wildcard_spec tmp;
			  tmp.name = yyvsp[0].name;
			  tmp.exclude_name_list = NULL;
			  tmp.sorted = FALSE;
			  lang_add_wild (&tmp, NULL, ldgram_had_keep);
			}
    break;

  case 110:
#line 485 "ldgram.y"
    {
			  lang_add_wild (NULL, yyvsp[-1].wildcard_list, ldgram_had_keep);
			}
    break;

  case 111:
#line 489 "ldgram.y"
    {
			  lang_add_wild (&yyvsp[-3].wildcard, yyvsp[-1].wildcard_list, ldgram_had_keep);
			}
    break;

  case 113:
#line 497 "ldgram.y"
    { ldgram_had_keep = TRUE; }
    break;

  case 114:
#line 499 "ldgram.y"
    { ldgram_had_keep = FALSE; }
    break;

  case 116:
#line 505 "ldgram.y"
    {
 		lang_add_attribute(lang_object_symbols_statement_enum);
	      	}
    break;

  case 118:
#line 510 "ldgram.y"
    {

		  lang_add_attribute(lang_constructors_statement_enum);
		}
    break;

  case 119:
#line 515 "ldgram.y"
    {
		  constructors_sorted = TRUE;
		  lang_add_attribute (lang_constructors_statement_enum);
		}
    break;

  case 121:
#line 521 "ldgram.y"
    {
			  lang_add_data ((int) yyvsp[-3].integer, yyvsp[-1].etree);
			}
    break;

  case 122:
#line 526 "ldgram.y"
    {
			  lang_add_fill (yyvsp[-1].fill);
			}
    break;

  case 127:
#line 543 "ldgram.y"
    { yyval.integer = yyvsp[0].token; }
    break;

  case 128:
#line 545 "ldgram.y"
    { yyval.integer = yyvsp[0].token; }
    break;

  case 129:
#line 547 "ldgram.y"
    { yyval.integer = yyvsp[0].token; }
    break;

  case 130:
#line 549 "ldgram.y"
    { yyval.integer = yyvsp[0].token; }
    break;

  case 131:
#line 551 "ldgram.y"
    { yyval.integer = yyvsp[0].token; }
    break;

  case 132:
#line 556 "ldgram.y"
    {
		  yyval.fill = exp_get_fill (yyvsp[0].etree,
				     0,
				     "fill value",
				     lang_first_phase_enum);
		}
    break;

  case 133:
#line 566 "ldgram.y"
    { yyval.fill = yyvsp[0].fill; }
    break;

  case 134:
#line 567 "ldgram.y"
    { yyval.fill = (fill_type *) 0; }
    break;

  case 135:
#line 572 "ldgram.y"
    { yyval.token = '+'; }
    break;

  case 136:
#line 574 "ldgram.y"
    { yyval.token = '-'; }
    break;

  case 137:
#line 576 "ldgram.y"
    { yyval.token = '*'; }
    break;

  case 138:
#line 578 "ldgram.y"
    { yyval.token = '/'; }
    break;

  case 139:
#line 580 "ldgram.y"
    { yyval.token = LSHIFT; }
    break;

  case 140:
#line 582 "ldgram.y"
    { yyval.token = RSHIFT; }
    break;

  case 141:
#line 584 "ldgram.y"
    { yyval.token = '&'; }
    break;

  case 142:
#line 586 "ldgram.y"
    { yyval.token = '|'; }
    break;

  case 145:
#line 596 "ldgram.y"
    {
		  lang_add_assignment (exp_assop (yyvsp[-1].token, yyvsp[-2].name, yyvsp[0].etree));
		}
    break;

  case 146:
#line 600 "ldgram.y"
    {
		  lang_add_assignment (exp_assop ('=', yyvsp[-2].name,
						  exp_binop (yyvsp[-1].token,
							     exp_nameop (NAME,
									 yyvsp[-2].name),
							     yyvsp[0].etree)));
		}
    break;

  case 147:
#line 608 "ldgram.y"
    {
		  lang_add_assignment (exp_provide (yyvsp[-3].name, yyvsp[-1].etree));
		}
    break;

  case 154:
#line 630 "ldgram.y"
    { region = lang_memory_region_lookup(yyvsp[0].name); }
    break;

  case 155:
#line 633 "ldgram.y"
    {}
    break;

  case 156:
#line 638 "ldgram.y"
    { region->current =
		 region->origin =
		 exp_get_vma(yyvsp[0].etree, 0L,"origin", lang_first_phase_enum);
}
    break;

  case 157:
#line 646 "ldgram.y"
    { region->length = exp_get_vma(yyvsp[0].etree,
					       ~((bfd_vma)0),
					       "length",
					       lang_first_phase_enum);
		}
    break;

  case 158:
#line 655 "ldgram.y"
    { /* dummy action to avoid bison 1.25 error message */ }
    break;

  case 162:
#line 666 "ldgram.y"
    { lang_set_flags (region, yyvsp[0].name, 0); }
    break;

  case 163:
#line 668 "ldgram.y"
    { lang_set_flags (region, yyvsp[0].name, 1); }
    break;

  case 164:
#line 673 "ldgram.y"
    { lang_startup(yyvsp[-1].name); }
    break;

  case 166:
#line 679 "ldgram.y"
    { ldemul_hll((char *)NULL); }
    break;

  case 167:
#line 684 "ldgram.y"
    { ldemul_hll(yyvsp[0].name); }
    break;

  case 168:
#line 686 "ldgram.y"
    { ldemul_hll(yyvsp[0].name); }
    break;

  case 170:
#line 694 "ldgram.y"
    { ldemul_syslib(yyvsp[0].name); }
    break;

  case 172:
#line 700 "ldgram.y"
    { lang_float(TRUE); }
    break;

  case 173:
#line 702 "ldgram.y"
    { lang_float(FALSE); }
    break;

  case 174:
#line 707 "ldgram.y"
    {
		  yyval.nocrossref = NULL;
		}
    break;

  case 175:
#line 711 "ldgram.y"
    {
		  struct lang_nocrossref *n;

		  n = (struct lang_nocrossref *) xmalloc (sizeof *n);
		  n->name = yyvsp[-1].name;
		  n->next = yyvsp[0].nocrossref;
		  yyval.nocrossref = n;
		}
    break;

  case 176:
#line 720 "ldgram.y"
    {
		  struct lang_nocrossref *n;

		  n = (struct lang_nocrossref *) xmalloc (sizeof *n);
		  n->name = yyvsp[-2].name;
		  n->next = yyvsp[0].nocrossref;
		  yyval.nocrossref = n;
		}
    break;

  case 177:
#line 730 "ldgram.y"
    { ldlex_expression(); }
    break;

  case 178:
#line 732 "ldgram.y"
    { ldlex_popstate(); yyval.etree=yyvsp[0].etree;}
    break;

  case 179:
#line 737 "ldgram.y"
    { yyval.etree = exp_unop('-', yyvsp[0].etree); }
    break;

  case 180:
#line 739 "ldgram.y"
    { yyval.etree = yyvsp[-1].etree; }
    break;

  case 181:
#line 741 "ldgram.y"
    { yyval.etree = exp_unop((int) yyvsp[-3].integer,yyvsp[-1].etree); }
    break;

  case 182:
#line 743 "ldgram.y"
    { yyval.etree = exp_unop('!', yyvsp[0].etree); }
    break;

  case 183:
#line 745 "ldgram.y"
    { yyval.etree = yyvsp[0].etree; }
    break;

  case 184:
#line 747 "ldgram.y"
    { yyval.etree = exp_unop('~', yyvsp[0].etree);}
    break;

  case 185:
#line 750 "ldgram.y"
    { yyval.etree = exp_binop('*', yyvsp[-2].etree, yyvsp[0].etree); }
    break;

  case 186:
#line 752 "ldgram.y"
    { yyval.etree = exp_binop('/', yyvsp[-2].etree, yyvsp[0].etree); }
    break;

  case 187:
#line 754 "ldgram.y"
    { yyval.etree = exp_binop('%', yyvsp[-2].etree, yyvsp[0].etree); }
    break;

  case 188:
#line 756 "ldgram.y"
    { yyval.etree = exp_binop('+', yyvsp[-2].etree, yyvsp[0].etree); }
    break;

  case 189:
#line 758 "ldgram.y"
    { yyval.etree = exp_binop('-' , yyvsp[-2].etree, yyvsp[0].etree); }
    break;

  case 190:
#line 760 "ldgram.y"
    { yyval.etree = exp_binop(LSHIFT , yyvsp[-2].etree, yyvsp[0].etree); }
    break;

  case 191:
#line 762 "ldgram.y"
    { yyval.etree = exp_binop(RSHIFT , yyvsp[-2].etree, yyvsp[0].etree); }
    break;

  case 192:
#line 764 "ldgram.y"
    { yyval.etree = exp_binop(EQ , yyvsp[-2].etree, yyvsp[0].etree); }
    break;

  case 193:
#line 766 "ldgram.y"
    { yyval.etree = exp_binop(NE , yyvsp[-2].etree, yyvsp[0].etree); }
    break;

  case 194:
#line 768 "ldgram.y"
    { yyval.etree = exp_binop(LE , yyvsp[-2].etree, yyvsp[0].etree); }
    break;

  case 195:
#line 770 "ldgram.y"
    { yyval.etree = exp_binop(GE , yyvsp[-2].etree, yyvsp[0].etree); }
    break;

  case 196:
#line 772 "ldgram.y"
    { yyval.etree = exp_binop('<' , yyvsp[-2].etree, yyvsp[0].etree); }
    break;

  case 197:
#line 774 "ldgram.y"
    { yyval.etree = exp_binop('>' , yyvsp[-2].etree, yyvsp[0].etree); }
    break;

  case 198:
#line 776 "ldgram.y"
    { yyval.etree = exp_binop('&' , yyvsp[-2].etree, yyvsp[0].etree); }
    break;

  case 199:
#line 778 "ldgram.y"
    { yyval.etree = exp_binop('^' , yyvsp[-2].etree, yyvsp[0].etree); }
    break;

  case 200:
#line 780 "ldgram.y"
    { yyval.etree = exp_binop('|' , yyvsp[-2].etree, yyvsp[0].etree); }
    break;

  case 201:
#line 782 "ldgram.y"
    { yyval.etree = exp_trinop('?' , yyvsp[-4].etree, yyvsp[-2].etree, yyvsp[0].etree); }
    break;

  case 202:
#line 784 "ldgram.y"
    { yyval.etree = exp_binop(ANDAND , yyvsp[-2].etree, yyvsp[0].etree); }
    break;

  case 203:
#line 786 "ldgram.y"
    { yyval.etree = exp_binop(OROR , yyvsp[-2].etree, yyvsp[0].etree); }
    break;

  case 204:
#line 788 "ldgram.y"
    { yyval.etree = exp_nameop(DEFINED, yyvsp[-1].name); }
    break;

  case 205:
#line 790 "ldgram.y"
    { yyval.etree = exp_bigintop (yyvsp[0].bigint.integer, yyvsp[0].bigint.str); }
    break;

  case 206:
#line 792 "ldgram.y"
    { yyval.etree = exp_nameop(SIZEOF_HEADERS,0); }
    break;

  case 207:
#line 795 "ldgram.y"
    { yyval.etree = exp_nameop(SIZEOF,yyvsp[-1].name); }
    break;

  case 208:
#line 797 "ldgram.y"
    { yyval.etree = exp_nameop(ADDR,yyvsp[-1].name); }
    break;

  case 209:
#line 799 "ldgram.y"
    { yyval.etree = exp_nameop(LOADADDR,yyvsp[-1].name); }
    break;

  case 210:
#line 801 "ldgram.y"
    { yyval.etree = exp_unop(ABSOLUTE, yyvsp[-1].etree); }
    break;

  case 211:
#line 803 "ldgram.y"
    { yyval.etree = exp_unop(ALIGN_K,yyvsp[-1].etree); }
    break;

  case 212:
#line 805 "ldgram.y"
    { yyval.etree = exp_binop (DATA_SEGMENT_ALIGN, yyvsp[-3].etree, yyvsp[-1].etree); }
    break;

  case 213:
#line 807 "ldgram.y"
    { yyval.etree = exp_unop(DATA_SEGMENT_END, yyvsp[-1].etree); }
    break;

  case 214:
#line 809 "ldgram.y"
    { yyval.etree = exp_unop(ALIGN_K,yyvsp[-1].etree); }
    break;

  case 215:
#line 811 "ldgram.y"
    { yyval.etree = exp_nameop(NAME,yyvsp[0].name); }
    break;

  case 216:
#line 813 "ldgram.y"
    { yyval.etree = exp_binop (MAX_K, yyvsp[-3].etree, yyvsp[-1].etree ); }
    break;

  case 217:
#line 815 "ldgram.y"
    { yyval.etree = exp_binop (MIN_K, yyvsp[-3].etree, yyvsp[-1].etree ); }
    break;

  case 218:
#line 817 "ldgram.y"
    { yyval.etree = exp_assert (yyvsp[-3].etree, yyvsp[-1].name); }
    break;

  case 219:
#line 822 "ldgram.y"
    { yyval.name = yyvsp[0].name; }
    break;

  case 220:
#line 823 "ldgram.y"
    { yyval.name = 0; }
    break;

  case 221:
#line 827 "ldgram.y"
    { yyval.etree = yyvsp[-1].etree; }
    break;

  case 222:
#line 828 "ldgram.y"
    { yyval.etree = 0; }
    break;

  case 223:
#line 831 "ldgram.y"
    { ldlex_expression(); }
    break;

  case 224:
#line 833 "ldgram.y"
    { ldlex_popstate (); ldlex_script (); }
    break;

  case 225:
#line 835 "ldgram.y"
    {
			  lang_enter_output_section_statement(yyvsp[-5].name, yyvsp[-3].etree,
							      sectype,
							      0, 0, 0, yyvsp[-2].etree);
			}
    break;

  case 226:
#line 841 "ldgram.y"
    { ldlex_popstate (); ldlex_expression (); }
    break;

  case 227:
#line 843 "ldgram.y"
    {
		  ldlex_popstate ();
		  lang_leave_output_section_statement (yyvsp[0].fill, yyvsp[-3].name, yyvsp[-1].section_phdr, yyvsp[-2].name);
		}
    break;

  case 228:
#line 848 "ldgram.y"
    {}
    break;

  case 229:
#line 850 "ldgram.y"
    { ldlex_expression (); }
    break;

  case 230:
#line 852 "ldgram.y"
    { ldlex_popstate (); ldlex_script (); }
    break;

  case 231:
#line 854 "ldgram.y"
    {
			  lang_enter_overlay (yyvsp[-4].etree);
			}
    break;

  case 232:
#line 859 "ldgram.y"
    { ldlex_popstate (); ldlex_expression (); }
    break;

  case 233:
#line 861 "ldgram.y"
    {
			  ldlex_popstate ();
			  lang_leave_overlay (yyvsp[-10].etree, (int) yyvsp[-11].integer,
					      yyvsp[0].fill, yyvsp[-3].name, yyvsp[-1].section_phdr, yyvsp[-2].name);
			}
    break;

  case 235:
#line 871 "ldgram.y"
    { ldlex_expression (); }
    break;

  case 236:
#line 873 "ldgram.y"
    {
		  ldlex_popstate ();
		  lang_add_assignment (exp_assop ('=', ".", yyvsp[0].etree));
		}
    break;

  case 238:
#line 881 "ldgram.y"
    { sectype = noload_section; }
    break;

  case 239:
#line 882 "ldgram.y"
    { sectype = dsect_section; }
    break;

  case 240:
#line 883 "ldgram.y"
    { sectype = copy_section; }
    break;

  case 241:
#line 884 "ldgram.y"
    { sectype = info_section; }
    break;

  case 242:
#line 885 "ldgram.y"
    { sectype = overlay_section; }
    break;

  case 244:
#line 890 "ldgram.y"
    { sectype = normal_section; }
    break;

  case 245:
#line 891 "ldgram.y"
    { sectype = normal_section; }
    break;

  case 246:
#line 895 "ldgram.y"
    { yyval.etree = yyvsp[-2].etree; }
    break;

  case 247:
#line 896 "ldgram.y"
    { yyval.etree = (etree_type *)NULL;  }
    break;

  case 248:
#line 901 "ldgram.y"
    { yyval.etree = yyvsp[-3].etree; }
    break;

  case 249:
#line 903 "ldgram.y"
    { yyval.etree = yyvsp[-7].etree; }
    break;

  case 250:
#line 907 "ldgram.y"
    { yyval.etree = yyvsp[-1].etree; }
    break;

  case 251:
#line 908 "ldgram.y"
    { yyval.etree = (etree_type *) NULL;  }
    break;

  case 252:
#line 913 "ldgram.y"
    { yyval.integer = 0; }
    break;

  case 253:
#line 915 "ldgram.y"
    { yyval.integer = 1; }
    break;

  case 254:
#line 920 "ldgram.y"
    { yyval.name = yyvsp[0].name; }
    break;

  case 255:
#line 921 "ldgram.y"
    { yyval.name = "*default*"; }
    break;

  case 256:
#line 926 "ldgram.y"
    {
		  yyval.section_phdr = NULL;
		}
    break;

  case 257:
#line 930 "ldgram.y"
    {
		  struct lang_output_section_phdr_list *n;

		  n = ((struct lang_output_section_phdr_list *)
		       xmalloc (sizeof *n));
		  n->name = yyvsp[0].name;
		  n->used = FALSE;
		  n->next = yyvsp[-2].section_phdr;
		  yyval.section_phdr = n;
		}
    break;

  case 259:
#line 946 "ldgram.y"
    {
			  ldlex_script ();
			  lang_enter_overlay_section (yyvsp[0].name);
			}
    break;

  case 260:
#line 951 "ldgram.y"
    { ldlex_popstate (); ldlex_expression (); }
    break;

  case 261:
#line 953 "ldgram.y"
    {
			  ldlex_popstate ();
			  lang_leave_overlay_section (yyvsp[0].fill, yyvsp[-1].section_phdr);
			}
    break;

  case 266:
#line 970 "ldgram.y"
    { ldlex_expression (); }
    break;

  case 267:
#line 971 "ldgram.y"
    { ldlex_popstate (); }
    break;

  case 268:
#line 973 "ldgram.y"
    {
		  lang_new_phdr (yyvsp[-5].name, yyvsp[-3].etree, yyvsp[-2].phdr.filehdr, yyvsp[-2].phdr.phdrs, yyvsp[-2].phdr.at,
				 yyvsp[-2].phdr.flags);
		}
    break;

  case 269:
#line 981 "ldgram.y"
    {
		  yyval.etree = yyvsp[0].etree;

		  if (yyvsp[0].etree->type.node_class == etree_name
		      && yyvsp[0].etree->type.node_code == NAME)
		    {
		      const char *s;
		      unsigned int i;
		      static const char * const phdr_types[] =
			{
			  "PT_NULL", "PT_LOAD", "PT_DYNAMIC",
			  "PT_INTERP", "PT_NOTE", "PT_SHLIB",
			  "PT_PHDR", "PT_TLS"
			};

		      s = yyvsp[0].etree->name.name;
		      for (i = 0;
			   i < sizeof phdr_types / sizeof phdr_types[0];
			   i++)
			if (strcmp (s, phdr_types[i]) == 0)
			  {
			    yyval.etree = exp_intop (i);
			    break;
			  }
		      if (i == sizeof phdr_types / sizeof phdr_types[0])
			{
			  if (strcmp (s, "PT_GNU_EH_FRAME") == 0)
			    yyval.etree = exp_intop (0x6474e550);
			  else
			    {
			      einfo (_("\
%X%P:%S: unknown phdr type `%s' (try integer literal)\n"),
				     s);
			      yyval.etree = exp_intop (0);
			    }
			}
		    }
		}
    break;

  case 270:
#line 1023 "ldgram.y"
    {
		  memset (&yyval.phdr, 0, sizeof (struct phdr_info));
		}
    break;

  case 271:
#line 1027 "ldgram.y"
    {
		  yyval.phdr = yyvsp[0].phdr;
		  if (strcmp (yyvsp[-2].name, "FILEHDR") == 0 && yyvsp[-1].etree == NULL)
		    yyval.phdr.filehdr = TRUE;
		  else if (strcmp (yyvsp[-2].name, "PHDRS") == 0 && yyvsp[-1].etree == NULL)
		    yyval.phdr.phdrs = TRUE;
		  else if (strcmp (yyvsp[-2].name, "FLAGS") == 0 && yyvsp[-1].etree != NULL)
		    yyval.phdr.flags = yyvsp[-1].etree;
		  else
		    einfo (_("%X%P:%S: PHDRS syntax error at `%s'\n"), yyvsp[-2].name);
		}
    break;

  case 272:
#line 1039 "ldgram.y"
    {
		  yyval.phdr = yyvsp[0].phdr;
		  yyval.phdr.at = yyvsp[-2].etree;
		}
    break;

  case 273:
#line 1047 "ldgram.y"
    {
		  yyval.etree = NULL;
		}
    break;

  case 274:
#line 1051 "ldgram.y"
    {
		  yyval.etree = yyvsp[-1].etree;
		}
    break;

  case 275:
#line 1059 "ldgram.y"
    {
		  ldlex_version_file ();
		  PUSH_ERROR (_("VERSION script"));
		}
    break;

  case 276:
#line 1064 "ldgram.y"
    {
		  ldlex_popstate ();
		  POP_ERROR ();
		}
    break;

  case 277:
#line 1073 "ldgram.y"
    {
		  ldlex_version_script ();
		}
    break;

  case 278:
#line 1077 "ldgram.y"
    {
		  ldlex_popstate ();
		}
    break;

  case 281:
#line 1089 "ldgram.y"
    {
		  lang_register_vers_node (NULL, yyvsp[-2].versnode, NULL);
		}
    break;

  case 282:
#line 1093 "ldgram.y"
    {
		  lang_register_vers_node (yyvsp[-4].name, yyvsp[-2].versnode, NULL);
		}
    break;

  case 283:
#line 1097 "ldgram.y"
    {
		  lang_register_vers_node (yyvsp[-5].name, yyvsp[-3].versnode, yyvsp[-1].deflist);
		}
    break;

  case 284:
#line 1104 "ldgram.y"
    {
		  yyval.deflist = lang_add_vers_depend (NULL, yyvsp[0].name);
		}
    break;

  case 285:
#line 1108 "ldgram.y"
    {
		  yyval.deflist = lang_add_vers_depend (yyvsp[-1].deflist, yyvsp[0].name);
		}
    break;

  case 286:
#line 1115 "ldgram.y"
    {
		  yyval.versnode = lang_new_vers_node (NULL, NULL);
		}
    break;

  case 287:
#line 1119 "ldgram.y"
    {
		  yyval.versnode = lang_new_vers_node (yyvsp[-1].versyms, NULL);
		}
    break;

  case 288:
#line 1123 "ldgram.y"
    {
		  yyval.versnode = lang_new_vers_node (yyvsp[-1].versyms, NULL);
		}
    break;

  case 289:
#line 1127 "ldgram.y"
    {
		  yyval.versnode = lang_new_vers_node (NULL, yyvsp[-1].versyms);
		}
    break;

  case 290:
#line 1131 "ldgram.y"
    {
		  yyval.versnode = lang_new_vers_node (yyvsp[-5].versyms, yyvsp[-1].versyms);
		}
    break;

  case 291:
#line 1138 "ldgram.y"
    {
		  yyval.versyms = lang_new_vers_pattern (NULL, yyvsp[0].name, ldgram_vers_current_lang);
		}
    break;

  case 292:
#line 1142 "ldgram.y"
    {
		  yyval.versyms = lang_new_vers_pattern (yyvsp[-2].versyms, yyvsp[0].name, ldgram_vers_current_lang);
		}
    break;

  case 293:
#line 1146 "ldgram.y"
    {
			  yyval.name = ldgram_vers_current_lang;
			  ldgram_vers_current_lang = yyvsp[-1].name;
			}
    break;

  case 294:
#line 1151 "ldgram.y"
    {
			  yyval.versyms = yyvsp[-2].versyms;
			  ldgram_vers_current_lang = yyvsp[-3].name;
			}
    break;

  case 295:
#line 1156 "ldgram.y"
    {
			  yyval.name = ldgram_vers_current_lang;
			  ldgram_vers_current_lang = yyvsp[-1].name;
			}
    break;

  case 296:
#line 1161 "ldgram.y"
    {
			  yyval.versyms = yyvsp[-2].versyms;
			  ldgram_vers_current_lang = yyvsp[-3].name;
			}
    break;


    }

/* Line 993 of yacc.c.  */
#line 3400 "y.tab.c"

  yyvsp -= yylen;
  yyssp -= yylen;


  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  int yytype = YYTRANSLATE (yychar);
	  const char* yyprefix;
	  char *yymsg;
	  int yyx;

	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  int yyxbegin = yyn < 0 ? -yyn : 0;

	  /* Stay within bounds of both yycheck and yytname.  */
	  int yychecklim = YYLAST - yyn;
	  int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
	  int yycount = 0;

	  yyprefix = ", expecting ";
	  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      {
		yysize += yystrlen (yyprefix) + yystrlen (yytname [yyx]);
		yycount += 1;
		if (yycount == 5)
		  {
		    yysize = 0;
		    break;
		  }
	      }
	  yysize += (sizeof ("syntax error, unexpected ")
		     + yystrlen (yytname[yytype]));
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[yytype]);

	      if (yycount < 5)
		{
		  yyprefix = ", expecting ";
		  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
		    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		      {
			yyp = yystpcpy (yyp, yyprefix);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yyprefix = " or ";
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("syntax error; also virtual memory exhausted");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror ("syntax error");
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* If at end of input, pop the error token,
	     then the rest of the stack, then return failure.  */
	  if (yychar == YYEOF)
	     for (;;)
	       {
		 YYPOPSTACK;
		 if (yyssp == yyss)
		   YYABORT;
		 YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
		 yydestruct (yystos[*yyssp], yyvsp);
	       }
        }
      else
	{
	  YYDSYMPRINTF ("Error: discarding", yytoken, &yylval, &yylloc);
	  yydestruct (yytoken, &yylval);
	  yychar = YYEMPTY;

	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

#ifdef __GNUC__
  /* Pacify GCC when the user code never invokes YYERROR and the label
     yyerrorlab therefore never appears in user code.  */
  if (0)
     goto yyerrorlab;
#endif

  yyvsp -= yylen;
  yyssp -= yylen;
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
      yydestruct (yystos[yystate], yyvsp);
      YYPOPSTACK;
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;


  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*----------------------------------------------.
| yyoverflowlab -- parser overflow comes here.  |
`----------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 1172 "ldgram.y"

void
yyerror(arg)
     const char *arg;
{
  if (ldfile_assumed_script)
    einfo (_("%P:%s: file format not recognized; treating as linker script\n"),
	   ldfile_input_filename);
  if (error_index > 0 && error_index < ERROR_NAME_MAX)
     einfo ("%P%F:%S: %s in %s\n", arg, error_names[error_index-1]);
  else
     einfo ("%P%F:%S: %s\n", arg);
}

