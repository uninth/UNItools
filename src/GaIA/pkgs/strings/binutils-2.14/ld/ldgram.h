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
/* Line 1268 of yacc.c.  */
#line 280 "y.tab.h"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;



