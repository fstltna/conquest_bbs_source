/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "conqinit-yacc.y" /* yacc.c:339  */

/*
 * conqinit - yacc parser for conqinit
 *
 * $Id$
 *
 */

#include "c_defs.h"

#include "conqdef.h"
#include "conqcom.h"

#include "global.h"
#include "color.h"

#define NOEXTERN_CONQINIT
#include "conqinit.h"

#include "conqutil.h"

/* The default initdata */
#if 1
#include "initdata.h"
#include "sounddata.h"
#else
#warning "Enable this for debugging only! It will core if you use it in anything other than conqinit!"
  cqiGlobalInitRec_t    defaultGlobalInit = {};
  cqiShiptypeInitPtr_t  defaultShiptypes = NULL;
  cqiPlanetInitPtr_t    defaultPlanets = NULL;

  cqiSoundConfRec_t     defaultSoundConf = {};
  cqiSoundPtr_t         defaultSoundEffects = NULL;
  int                   defaultNumSoundEffects = 0;
  cqiSoundPtr_t         defaultSoundMusic = NULL;
  int                   defaultNumSoundMusic = 0;
#endif

static int cqiVerbose = 0;
int cqiDebugl = 0;

static char *ptr;

/* a nesting depth of 0 implies the top-level, though currently only
 * other sections can be defined in it, so PREVSECTION looks only at
 * nesting levels > 1.  Bascause of this, your max available nesting
 * depth is really MAX_NESTING_DEPTH - 1.
 */ 
#define MAX_NESTING_DEPTH     16
static int sections[MAX_NESTING_DEPTH] = {};
static int curDepth = 0;

#define CURSECTION()          (sections[curDepth])
#define PREVSECTION()         ((curDepth > 1) ? sections[curDepth - 1] : 0)

extern int lineNum;
extern int goterror;
extern void yyerror(char *s);

int yylex(void);

static cqiGlobalInitPtr_t      _cqiGlobal;
static cqiShiptypeInitPtr_t    _cqiShiptypes;
static cqiPlanetInitPtr_t      _cqiPlanets;
static cqiTextureInitPtr_t     _cqiTextures;
static cqiAnimationInitPtr_t   _cqiAnimations;
static cqiAnimDefInitPtr_t     _cqiAnimDefs;
 
static cqiSoundConfPtr_t       _cqiSoundConf;
static cqiSoundPtr_t           _cqiSoundEffects;
static cqiSoundPtr_t           _cqiSoundMusic;

static int globalRead        = FALSE;
static int numShiptypes      = 0;
static int numPlanets        = 0;
static int numTextures       = 0;
static int numAnimations     = 0;
static int numAnimDefs       = 0;
static int numSoundEffects   = 0;
static int numSoundMusic     = 0;

/* # loaded per file */
static int fileNumTextures   = 0;
static int fileNumAnimations = 0;
static int fileNumAnimDefs   = 0;
static int fileNumEffects    = 0;
static int fileNumMusic      = 0;

static cqiPlanetInitRec_t      currPlanet;
static cqiTextureInitRec_t     currTexture;

static cqiAnimationInitRec_t   currAnimation;
static cqiAnimDefInitRec_t     currAnimDef;

static cqiTextureAreaRec_t     currTexArea;
static int numTexAreas       = 0;
static cqiTextureAreaPtr_t currTexAreas = NULL;

static cqiSoundRec_t           currSound;

static void startSection(int section);
static void endSection(void);

static void cfgSectioni(int item, int val);
static void cfgSectionil(int item, int val1, int val2);
static void cfgSectionf(int item, real val);
static void cfgSections(int item, char *val);
static void cfgSectionb(int item, char *val);
static char *sect2str(int section);
static char *item2str(int item);
static char *team2str(int pteam);
static int str2team(char *str);
static void initrun(int rcid);
static void checkStr(char *str);
static int parsebool(char *str);



#line 185 "conqinit-yacc.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TOK_OPENSECT = 258,
    TOK_CLOSESECT = 259,
    TOK_NUMBER = 260,
    TOK_GLOBAL = 261,
    TOK_PLANETMAX = 262,
    TOK_SHIPMAX = 263,
    TOK_USERMAX = 264,
    TOK_MSGMAX = 265,
    TOK_HISTMAX = 266,
    TOK_SHIPTYPE = 267,
    TOK_ENGFAC = 268,
    TOK_WEAFAC = 269,
    TOK_ACCELFAC = 270,
    TOK_TORPWARP = 271,
    TOK_WARPMAX = 272,
    TOK_ARMYMAX = 273,
    TOK_SHMAX = 274,
    TOK_DAMMAX = 275,
    TOK_TORPMAX = 276,
    TOK_FUELMAX = 277,
    TOK_NAME = 278,
    TOK_SIZE = 279,
    TOK_PLANET = 280,
    TOK_PRIMARY = 281,
    TOK_ANGLE = 282,
    TOK_VELOCITY = 283,
    TOK_RADIUS = 284,
    TOK_PTYPE = 285,
    TOK_PTEAM = 286,
    TOK_ARMIES = 287,
    TOK_VISIBLE = 288,
    TOK_CORE = 289,
    TOK_XCOORD = 290,
    TOK_YCOORD = 291,
    TOK_TEXNAME = 292,
    TOK_COLOR = 293,
    TOK_HOMEPLANET = 294,
    TOK_TEXTURE = 295,
    TOK_FILENAME = 296,
    TOK_ANIMATION = 297,
    TOK_ANIMDEF = 298,
    TOK_STAGES = 299,
    TOK_LOOPS = 300,
    TOK_DELAYMS = 301,
    TOK_LOOPTYPE = 302,
    TOK_TIMELIMIT = 303,
    TOK_TEXANIM = 304,
    TOK_COLANIM = 305,
    TOK_GEOANIM = 306,
    TOK_TOGANIM = 307,
    TOK_ISTATE = 308,
    TOK_DELTAA = 309,
    TOK_DELTAR = 310,
    TOK_DELTAG = 311,
    TOK_DELTAB = 312,
    TOK_DELTAX = 313,
    TOK_DELTAY = 314,
    TOK_DELTAZ = 315,
    TOK_DELTAS = 316,
    TOK_SOUNDCONF = 317,
    TOK_SAMPLERATE = 318,
    TOK_VOLUME = 319,
    TOK_PAN = 320,
    TOK_STEREO = 321,
    TOK_FXCHANNELS = 322,
    TOK_CHUNKSIZE = 323,
    TOK_EFFECT = 324,
    TOK_FADEINMS = 325,
    TOK_FADEOUTMS = 326,
    TOK_LIMIT = 327,
    TOK_FRAMELIMIT = 328,
    TOK_MUSIC = 329,
    TOK_DELTAT = 330,
    TOK_SCOORD = 331,
    TOK_TCOORD = 332,
    TOK_WIDTH = 333,
    TOK_HEIGHT = 334,
    TOK_TEXAREA = 335,
    TOK_MIPMAP = 336,
    TOK_TEX_LUMINANCE = 337,
    TOK_STRING = 338,
    TOK_RATIONAL = 339
  };
#endif
/* Tokens.  */
#define TOK_OPENSECT 258
#define TOK_CLOSESECT 259
#define TOK_NUMBER 260
#define TOK_GLOBAL 261
#define TOK_PLANETMAX 262
#define TOK_SHIPMAX 263
#define TOK_USERMAX 264
#define TOK_MSGMAX 265
#define TOK_HISTMAX 266
#define TOK_SHIPTYPE 267
#define TOK_ENGFAC 268
#define TOK_WEAFAC 269
#define TOK_ACCELFAC 270
#define TOK_TORPWARP 271
#define TOK_WARPMAX 272
#define TOK_ARMYMAX 273
#define TOK_SHMAX 274
#define TOK_DAMMAX 275
#define TOK_TORPMAX 276
#define TOK_FUELMAX 277
#define TOK_NAME 278
#define TOK_SIZE 279
#define TOK_PLANET 280
#define TOK_PRIMARY 281
#define TOK_ANGLE 282
#define TOK_VELOCITY 283
#define TOK_RADIUS 284
#define TOK_PTYPE 285
#define TOK_PTEAM 286
#define TOK_ARMIES 287
#define TOK_VISIBLE 288
#define TOK_CORE 289
#define TOK_XCOORD 290
#define TOK_YCOORD 291
#define TOK_TEXNAME 292
#define TOK_COLOR 293
#define TOK_HOMEPLANET 294
#define TOK_TEXTURE 295
#define TOK_FILENAME 296
#define TOK_ANIMATION 297
#define TOK_ANIMDEF 298
#define TOK_STAGES 299
#define TOK_LOOPS 300
#define TOK_DELAYMS 301
#define TOK_LOOPTYPE 302
#define TOK_TIMELIMIT 303
#define TOK_TEXANIM 304
#define TOK_COLANIM 305
#define TOK_GEOANIM 306
#define TOK_TOGANIM 307
#define TOK_ISTATE 308
#define TOK_DELTAA 309
#define TOK_DELTAR 310
#define TOK_DELTAG 311
#define TOK_DELTAB 312
#define TOK_DELTAX 313
#define TOK_DELTAY 314
#define TOK_DELTAZ 315
#define TOK_DELTAS 316
#define TOK_SOUNDCONF 317
#define TOK_SAMPLERATE 318
#define TOK_VOLUME 319
#define TOK_PAN 320
#define TOK_STEREO 321
#define TOK_FXCHANNELS 322
#define TOK_CHUNKSIZE 323
#define TOK_EFFECT 324
#define TOK_FADEINMS 325
#define TOK_FADEOUTMS 326
#define TOK_LIMIT 327
#define TOK_FRAMELIMIT 328
#define TOK_MUSIC 329
#define TOK_DELTAT 330
#define TOK_SCOORD 331
#define TOK_TCOORD 332
#define TOK_WIDTH 333
#define TOK_HEIGHT 334
#define TOK_TEXAREA 335
#define TOK_MIPMAP 336
#define TOK_TEX_LUMINANCE 337
#define TOK_STRING 338
#define TOK_RATIONAL 339

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 121 "conqinit-yacc.y" /* yacc.c:355  */

  int num;
  char *ptr;
  real rnum;

#line 399 "conqinit-yacc.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 416 "conqinit-yacc.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   325

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  85
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  56
/* YYNRULES -- Number of rules.  */
#define YYNRULES  137
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  246

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   339

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   162,   162,   165,   166,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   180,   183,   189,   193,   196,   202,
     206,   209,   215,   219,   222,   228,   232,   235,   241,   245,
     249,   255,   259,   262,   268,   272,   275,   281,   285,   288,
     294,   298,   301,   307,   311,   314,   320,   325,   328,   334,
     338,   341,   347,   351,   354,   360,   365,   368,   374,   379,
     383,   387,   388,   389,   390,   391,   392,   393,   394,   395,
     398,   402,   406,   410,   414,   418,   422,   426,   430,   434,
     438,   442,   446,   450,   454,   458,   462,   466,   470,   474,
     478,   482,   486,   490,   494,   498,   502,   506,   510,   514,
     518,   522,   526,   530,   534,   539,   543,   547,   551,   555,
     559,   563,   567,   571,   575,   579,   583,   587,   591,   595,
     599,   603,   607,   611,   615,   619,   623,   627,   631,   635,
     639,   643,   647,   651,   655,   658,   666,   668
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOK_OPENSECT", "TOK_CLOSESECT",
  "TOK_NUMBER", "TOK_GLOBAL", "TOK_PLANETMAX", "TOK_SHIPMAX",
  "TOK_USERMAX", "TOK_MSGMAX", "TOK_HISTMAX", "TOK_SHIPTYPE", "TOK_ENGFAC",
  "TOK_WEAFAC", "TOK_ACCELFAC", "TOK_TORPWARP", "TOK_WARPMAX",
  "TOK_ARMYMAX", "TOK_SHMAX", "TOK_DAMMAX", "TOK_TORPMAX", "TOK_FUELMAX",
  "TOK_NAME", "TOK_SIZE", "TOK_PLANET", "TOK_PRIMARY", "TOK_ANGLE",
  "TOK_VELOCITY", "TOK_RADIUS", "TOK_PTYPE", "TOK_PTEAM", "TOK_ARMIES",
  "TOK_VISIBLE", "TOK_CORE", "TOK_XCOORD", "TOK_YCOORD", "TOK_TEXNAME",
  "TOK_COLOR", "TOK_HOMEPLANET", "TOK_TEXTURE", "TOK_FILENAME",
  "TOK_ANIMATION", "TOK_ANIMDEF", "TOK_STAGES", "TOK_LOOPS", "TOK_DELAYMS",
  "TOK_LOOPTYPE", "TOK_TIMELIMIT", "TOK_TEXANIM", "TOK_COLANIM",
  "TOK_GEOANIM", "TOK_TOGANIM", "TOK_ISTATE", "TOK_DELTAA", "TOK_DELTAR",
  "TOK_DELTAG", "TOK_DELTAB", "TOK_DELTAX", "TOK_DELTAY", "TOK_DELTAZ",
  "TOK_DELTAS", "TOK_SOUNDCONF", "TOK_SAMPLERATE", "TOK_VOLUME", "TOK_PAN",
  "TOK_STEREO", "TOK_FXCHANNELS", "TOK_CHUNKSIZE", "TOK_EFFECT",
  "TOK_FADEINMS", "TOK_FADEOUTMS", "TOK_LIMIT", "TOK_FRAMELIMIT",
  "TOK_MUSIC", "TOK_DELTAT", "TOK_SCOORD", "TOK_TCOORD", "TOK_WIDTH",
  "TOK_HEIGHT", "TOK_TEXAREA", "TOK_MIPMAP", "TOK_TEX_LUMINANCE",
  "TOK_STRING", "TOK_RATIONAL", "$accept", "conqinit", "sections",
  "section", "globalconfig", "startglobal", "globalword", "shiptypeconfig",
  "startshiptype", "shiptypeword", "planetconfig", "startplanet",
  "planetword", "textureconfig", "starttexture", "textureword",
  "animationconfig", "startanimation", "animationword", "animdefconfig",
  "startanimdef", "animdefword", "texanimconfig", "starttexanim",
  "texanimword", "colanimconfig", "startcolanim", "colanimword",
  "geoanimconfig", "startgeoanim", "geoanimword", "toganimconfig",
  "starttoganim", "toganimword", "istateconfig", "startistate",
  "istateword", "texareaconfig", "starttexarea", "texareaword",
  "soundconfconfig", "startsoundconf", "soundconfword", "effectconfig",
  "starteffect", "effectword", "musicconfig", "startmusic", "musicword",
  "opensect", "closesect", "stmts", "stmt", "string", "number", "rational", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339
};
# endif

#define YYPACT_NINF -80

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-80)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -80,     1,   106,   -80,   -80,   -80,   -80,   -80,   -80,   -80,
     -80,   -80,   -80,   -80,   -80,   -80,     0,   -80,   -80,     0,
     -80,   -80,     0,   -80,   -80,     0,   -80,   -80,     0,   -80,
     -80,     0,   -80,   -80,     0,   -80,   -80,     0,   -80,   -80,
       0,   191,   -80,   -80,   191,   -80,   191,   -80,   191,   -80,
     191,   -80,   191,   -80,   191,   -80,   191,   -80,   191,   -80,
       3,   -80,     4,     4,     4,     4,     4,   -79,   -79,   -79,
       4,     4,     4,     4,     4,     4,     4,   -72,     4,   -72,
     -79,   -79,   -79,   -72,   -72,     4,   -72,   -72,   -79,   -79,
     -72,   -72,   -72,   -72,   -72,     4,     4,     4,     4,     4,
     -80,   -80,   -80,   -80,   -80,   -79,   -79,   -79,   -79,   -79,
     -79,   -79,   -79,     4,     4,     4,   -72,     4,     4,     4,
       4,     4,     4,   -79,   -79,   -79,   -79,   -79,   -80,   -72,
     -72,   -80,   -80,   -80,     0,   -80,   -80,     0,   -80,   -80,
       0,   -80,   -80,     0,   -80,   -80,     0,   -80,   -80,     0,
     -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,
     -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,
     -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,
     -80,   -80,   -80,   -80,   -80,   -80,   -80,     4,   -80,   -80,
     -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,
     -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,
     -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,
     -80,   -80,   -80,   -80,   -80,   -80,   -80,   191,   -80,   191,
     -80,   191,   -80,   191,   -80,   191,   -80,   191,   -80,   -80,
     -80,   -80,   -80,   -80,   -80,   -80
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     2,     1,    16,    19,    22,    25,    28,    31,
      52,    55,    58,     4,     5,    61,     0,     6,    61,     0,
       7,    61,     0,     8,    61,     0,     9,    61,     0,    10,
      61,     0,    11,    61,     0,    12,    61,     0,    13,    61,
       0,     0,    59,    15,     0,    18,     0,    21,     0,    24,
       0,    27,     0,    30,     0,    51,     0,    54,     0,    57,
       0,    60,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    31,     0,     0,     0,     0,     0,
      34,    37,    40,    43,    46,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    49,     0,
       0,    69,    63,    61,     0,    64,    61,     0,    65,    61,
       0,    66,    61,     0,    67,    61,     0,    68,    61,     0,
      14,    62,    17,    20,    23,    26,    29,    50,    53,    56,
     134,   136,    70,    71,    72,    74,    73,   137,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,   135,    75,
      86,    88,    89,    90,    91,    92,    93,    95,    96,    97,
      99,   100,   101,   102,    87,   103,   104,   105,   106,   107,
     108,   117,   109,   110,   111,   112,   113,   114,   115,   116,
     118,   119,   120,   121,   122,   123,   124,   125,   127,   126,
     130,   128,   129,   131,   132,    98,   133,     0,    33,     0,
      36,     0,    39,     0,    42,     0,    45,     0,    48,    94,
      32,    35,    38,    41,    44,    47
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,
     -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,    11,
     -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,
     -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,
     -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,   -80,    -4,
     -44,    -1,   -80,   195,   -24,    -3
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,   131,
      30,    31,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    43,
     150,    41,   151,   179,   162,   168
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
     152,     3,   153,    42,   154,   167,   155,    61,   156,   161,
     157,   178,   158,    29,   159,    45,   160,    44,    47,     0,
      46,    49,     0,    48,    51,     0,    50,    53,     0,    52,
      55,     0,    54,    57,     0,    56,    59,     0,    58,   163,
     164,   165,   166,     0,     0,     0,   171,   172,   173,   174,
     175,   176,   177,     0,   180,     0,     0,     0,     0,     0,
       0,   187,     0,     0,     0,   169,   170,     0,     0,     0,
       0,   197,   198,   199,   200,   201,     0,   182,   183,   184,
       0,     0,     0,     0,     0,   190,   191,     0,     0,   210,
     211,   212,     0,   214,   215,   216,   217,   218,   219,     0,
       0,     0,   202,   203,   204,   205,   206,   207,   208,   209,
       0,     0,     4,     0,     0,     0,     0,     0,     5,     0,
     220,   221,   222,   223,   224,     0,     0,     0,     0,     0,
     228,     6,   227,   230,     0,   229,   232,     0,   231,   234,
       0,   233,   236,     0,   235,   238,     7,   237,     8,     9,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   239,     0,     0,     0,     0,    10,     0,
       0,     0,     0,     0,     0,    11,     0,     0,     0,     0,
      12,     0,     0,   240,     0,   241,     0,   242,     0,   243,
       0,   244,    60,   245,     0,    61,     0,     0,    62,    63,
      64,    65,    66,     0,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,     0,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,     0,    93,     0,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,     0,   113,   114,   115,   116,   117,   118,
       0,   119,   120,   121,   122,     0,   123,   124,   125,   126,
     127,   128,   129,   130,   181,     0,     0,     0,   185,   186,
       0,   188,   189,     0,     0,   192,   193,   194,   195,   196,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   213,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   225,   226
};

static const yytype_int16 yycheck[] =
{
      44,     0,    46,     3,    48,    84,    50,     4,    52,     5,
      54,    83,    56,     2,    58,    19,    60,    18,    22,    -1,
      21,    25,    -1,    24,    28,    -1,    27,    31,    -1,    30,
      34,    -1,    33,    37,    -1,    36,    40,    -1,    39,    63,
      64,    65,    66,    -1,    -1,    -1,    70,    71,    72,    73,
      74,    75,    76,    -1,    78,    -1,    -1,    -1,    -1,    -1,
      -1,    85,    -1,    -1,    -1,    68,    69,    -1,    -1,    -1,
      -1,    95,    96,    97,    98,    99,    -1,    80,    81,    82,
      -1,    -1,    -1,    -1,    -1,    88,    89,    -1,    -1,   113,
     114,   115,    -1,   117,   118,   119,   120,   121,   122,    -1,
      -1,    -1,   105,   106,   107,   108,   109,   110,   111,   112,
      -1,    -1,     6,    -1,    -1,    -1,    -1,    -1,    12,    -1,
     123,   124,   125,   126,   127,    -1,    -1,    -1,    -1,    -1,
     134,    25,   133,   137,    -1,   136,   140,    -1,   139,   143,
      -1,   142,   146,    -1,   145,   149,    40,   148,    42,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   187,    -1,    -1,    -1,    -1,    62,    -1,
      -1,    -1,    -1,    -1,    -1,    69,    -1,    -1,    -1,    -1,
      74,    -1,    -1,   227,    -1,   229,    -1,   231,    -1,   233,
      -1,   235,     1,   237,    -1,     4,    -1,    -1,     7,     8,
       9,    10,    11,    -1,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    -1,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    -1,    41,    -1,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    -1,    63,    64,    65,    66,    67,    68,
      -1,    70,    71,    72,    73,    -1,    75,    76,    77,    78,
      79,    80,    81,    82,    79,    -1,    -1,    -1,    83,    84,
      -1,    86,    87,    -1,    -1,    90,    91,    92,    93,    94,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   116,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   129,   130
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    86,    87,     0,     6,    12,    25,    40,    42,    43,
      62,    69,    74,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   136,     3,   134,   136,   134,   136,   134,   136,   134,
     136,   134,   136,   134,   136,   134,   136,   134,   136,   134,
       1,     4,     7,     8,     9,    10,    11,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    41,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    63,    64,    65,    66,    67,    68,    70,
      71,    72,    73,    75,    76,    77,    78,    79,    80,    81,
      82,   104,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     135,   137,   135,   135,   135,   135,   135,   135,   135,   135,
     135,     5,   139,   139,   139,   139,   139,    84,   140,   140,
     140,   139,   139,   139,   139,   139,   139,   139,    83,   138,
     139,   138,   140,   140,   140,   138,   138,   139,   138,   138,
     140,   140,   138,   138,   138,   138,   138,   139,   139,   139,
     139,   139,   140,   140,   140,   140,   140,   140,   140,   140,
     139,   139,   139,   138,   139,   139,   139,   139,   139,   139,
     140,   140,   140,   140,   140,   138,   138,   136,   134,   136,
     134,   136,   134,   136,   134,   136,   134,   136,   134,   139,
     135,   135,   135,   135,   135,   135
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    85,    86,    87,    87,    88,    88,    88,    88,    88,
      88,    88,    88,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     137,   137,   137,   137,   137,   137,   137,   137,   137,   137,
     137,   137,   137,   137,   137,   137,   137,   137,   137,   137,
     137,   137,   137,   137,   137,   137,   137,   137,   137,   137,
     137,   137,   137,   137,   137,   137,   137,   137,   137,   137,
     137,   137,   137,   137,   137,   137,   137,   137,   137,   137,
     137,   137,   137,   137,   137,   137,   137,   137,   137,   137,
     137,   137,   137,   137,   137,   138,   139,   140
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     2,     1,     3,     2,     1,
       3,     2,     1,     3,     2,     1,     3,     2,     1,     3,
       2,     1,     3,     2,     1,     3,     2,     1,     3,     2,
       1,     3,     2,     1,     3,     2,     1,     3,     2,     1,
       3,     2,     1,     3,     2,     1,     3,     2,     1,     1,
       1,     0,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     3,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
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

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 15:
#line 184 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                   startSection(TOK_GLOBAL);
                }
#line 1713 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 16:
#line 190 "conqinit-yacc.y" /* yacc.c:1646  */
    {;}
#line 1719 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 18:
#line 197 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                   startSection(TOK_SHIPTYPE);
                }
#line 1727 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 19:
#line 203 "conqinit-yacc.y" /* yacc.c:1646  */
    {;}
#line 1733 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 21:
#line 210 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                   startSection(TOK_PLANET);
                }
#line 1741 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 22:
#line 216 "conqinit-yacc.y" /* yacc.c:1646  */
    {;}
#line 1747 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 24:
#line 223 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                   startSection(TOK_TEXTURE);
                }
#line 1755 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 25:
#line 229 "conqinit-yacc.y" /* yacc.c:1646  */
    {;}
#line 1761 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 27:
#line 236 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                   startSection(TOK_ANIMATION);
                }
#line 1769 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 28:
#line 242 "conqinit-yacc.y" /* yacc.c:1646  */
    {;}
#line 1775 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 30:
#line 250 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                    startSection(TOK_ANIMDEF);
                }
#line 1783 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 31:
#line 256 "conqinit-yacc.y" /* yacc.c:1646  */
    {;}
#line 1789 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 33:
#line 263 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                    startSection(TOK_TEXANIM);
                }
#line 1797 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 34:
#line 269 "conqinit-yacc.y" /* yacc.c:1646  */
    {;}
#line 1803 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 36:
#line 276 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                    startSection(TOK_COLANIM);
                }
#line 1811 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 37:
#line 282 "conqinit-yacc.y" /* yacc.c:1646  */
    {;}
#line 1817 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 39:
#line 289 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                    startSection(TOK_GEOANIM);
                }
#line 1825 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 40:
#line 295 "conqinit-yacc.y" /* yacc.c:1646  */
    {;}
#line 1831 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 42:
#line 302 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                    startSection(TOK_TOGANIM);
                }
#line 1839 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 43:
#line 308 "conqinit-yacc.y" /* yacc.c:1646  */
    {;}
#line 1845 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 45:
#line 315 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                    startSection(TOK_ISTATE);
                }
#line 1853 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 46:
#line 321 "conqinit-yacc.y" /* yacc.c:1646  */
    {;}
#line 1859 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 48:
#line 329 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                    startSection(TOK_TEXAREA);
                }
#line 1867 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 49:
#line 335 "conqinit-yacc.y" /* yacc.c:1646  */
    {;}
#line 1873 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 51:
#line 342 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                      startSection(TOK_SOUNDCONF);
                   }
#line 1881 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 52:
#line 348 "conqinit-yacc.y" /* yacc.c:1646  */
    {;}
#line 1887 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 54:
#line 355 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                  startSection(TOK_EFFECT);
               }
#line 1895 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 55:
#line 361 "conqinit-yacc.y" /* yacc.c:1646  */
    {;}
#line 1901 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 57:
#line 369 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                  startSection(TOK_MUSIC);
               }
#line 1909 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 58:
#line 375 "conqinit-yacc.y" /* yacc.c:1646  */
    {;}
#line 1915 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 59:
#line 380 "conqinit-yacc.y" /* yacc.c:1646  */
    {;}
#line 1921 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 60:
#line 384 "conqinit-yacc.y" /* yacc.c:1646  */
    {endSection();}
#line 1927 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 70:
#line 399 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSectioni(TOK_PLANETMAX, (yyvsp[0].num));
                   }
#line 1935 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 71:
#line 403 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSectioni(TOK_SHIPMAX, (yyvsp[0].num));
                   }
#line 1943 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 72:
#line 407 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSectioni(TOK_USERMAX, (yyvsp[0].num));
                   }
#line 1951 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 73:
#line 411 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSectioni(TOK_HISTMAX, (yyvsp[0].num));
                   }
#line 1959 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 74:
#line 415 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSectioni(TOK_MSGMAX, (yyvsp[0].num));
                   }
#line 1967 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 75:
#line 419 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSections(TOK_NAME, (yyvsp[0].ptr));
                   }
#line 1975 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 76:
#line 423 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSectionf(TOK_ENGFAC, (yyvsp[0].rnum));
                   }
#line 1983 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 77:
#line 427 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSectionf(TOK_WEAFAC, (yyvsp[0].rnum));
                   }
#line 1991 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 78:
#line 431 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSectionf(TOK_ACCELFAC, (yyvsp[0].rnum));
                   }
#line 1999 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 79:
#line 435 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSectioni(TOK_TORPWARP, (yyvsp[0].num));
                   }
#line 2007 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 80:
#line 439 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSectioni(TOK_WARPMAX, (yyvsp[0].num));
                   }
#line 2015 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 81:
#line 443 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSectioni(TOK_ARMYMAX, (yyvsp[0].num));
                   }
#line 2023 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 82:
#line 447 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSectioni(TOK_SHMAX, (yyvsp[0].num));
                   }
#line 2031 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 83:
#line 451 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSectioni(TOK_DAMMAX, (yyvsp[0].num));
                   }
#line 2039 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 84:
#line 455 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSectioni(TOK_TORPMAX, (yyvsp[0].num));
                   }
#line 2047 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 85:
#line 459 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSectioni(TOK_FUELMAX, (yyvsp[0].num));
                   }
#line 2055 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 86:
#line 463 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSectioni(TOK_SIZE, (yyvsp[0].num));
                   }
#line 2063 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 87:
#line 467 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSectionb(TOK_HOMEPLANET, (yyvsp[0].ptr));
                   }
#line 2071 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 88:
#line 471 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSections(TOK_PRIMARY, (yyvsp[0].ptr));
                   }
#line 2079 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 89:
#line 475 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSectionf(TOK_ANGLE, (yyvsp[0].rnum));
                   }
#line 2087 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 90:
#line 479 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSectionf(TOK_VELOCITY, (yyvsp[0].rnum));
                   }
#line 2095 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 91:
#line 483 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSectionf(TOK_RADIUS, (yyvsp[0].rnum));
                   }
#line 2103 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 92:
#line 487 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSections(TOK_PTYPE, (yyvsp[0].ptr));
                   }
#line 2111 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 93:
#line 491 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSections(TOK_PTEAM, (yyvsp[0].ptr));
                   }
#line 2119 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 94:
#line 495 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSectionil(TOK_ARMIES, (yyvsp[-1].num), (yyvsp[0].num));
                   }
#line 2127 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 95:
#line 499 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSectioni(TOK_ARMIES, (yyvsp[0].num));
                   }
#line 2135 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 96:
#line 503 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSectionb(TOK_VISIBLE, (yyvsp[0].ptr));
                   }
#line 2143 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 97:
#line 507 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSectionb(TOK_CORE, (yyvsp[0].ptr));
                   }
#line 2151 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 98:
#line 511 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSectionb(TOK_MIPMAP, (yyvsp[0].ptr));
                   }
#line 2159 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 99:
#line 515 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSectionf(TOK_XCOORD, (yyvsp[0].rnum));
                   }
#line 2167 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 100:
#line 519 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSectionf(TOK_YCOORD, (yyvsp[0].rnum));
                   }
#line 2175 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 101:
#line 523 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSections(TOK_TEXNAME, (yyvsp[0].ptr));
                   }
#line 2183 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 102:
#line 527 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSections(TOK_COLOR, (yyvsp[0].ptr));
                   }
#line 2191 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 103:
#line 531 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSections(TOK_FILENAME, (yyvsp[0].ptr));
                   }
#line 2199 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 104:
#line 535 "conqinit-yacc.y" /* yacc.c:1646  */
    {            /* in this form, it's a statement
                                   rather than a section */
                        cfgSections(TOK_ANIMDEF, (yyvsp[0].ptr));
                   }
#line 2208 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 105:
#line 540 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSectioni(TOK_STAGES, (yyvsp[0].num));
                   }
#line 2216 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 106:
#line 544 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSectioni(TOK_LOOPS, (yyvsp[0].num));
                   }
#line 2224 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 107:
#line 548 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSectioni(TOK_DELAYMS, (yyvsp[0].num));
                   }
#line 2232 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 108:
#line 552 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSectioni(TOK_LOOPTYPE, (yyvsp[0].num));
                   }
#line 2240 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 109:
#line 556 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSectionf(TOK_DELTAA, (yyvsp[0].rnum));
                   }
#line 2248 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 110:
#line 560 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSectionf(TOK_DELTAR, (yyvsp[0].rnum));
                   }
#line 2256 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 111:
#line 564 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSectionf(TOK_DELTAG, (yyvsp[0].rnum));
                   }
#line 2264 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 112:
#line 568 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSectionf(TOK_DELTAB, (yyvsp[0].rnum));
                   }
#line 2272 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 113:
#line 572 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSectionf(TOK_DELTAX, (yyvsp[0].rnum));
                   }
#line 2280 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 114:
#line 576 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSectionf(TOK_DELTAY, (yyvsp[0].rnum));
                   }
#line 2288 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 115:
#line 580 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSectionf(TOK_DELTAZ, (yyvsp[0].rnum));
                   }
#line 2296 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 116:
#line 584 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSectionf(TOK_DELTAS, (yyvsp[0].rnum));
                   }
#line 2304 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 117:
#line 588 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSectioni(TOK_TIMELIMIT, (yyvsp[0].num));
                   }
#line 2312 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 118:
#line 592 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSectioni(TOK_SAMPLERATE, (yyvsp[0].num));
                   }
#line 2320 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 119:
#line 596 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSectioni(TOK_VOLUME, (yyvsp[0].num));
                   }
#line 2328 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 120:
#line 600 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSectioni(TOK_PAN, (yyvsp[0].num));
                   }
#line 2336 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 121:
#line 604 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSectionb(TOK_STEREO, (yyvsp[0].ptr));
                   }
#line 2344 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 122:
#line 608 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSectioni(TOK_FXCHANNELS, (yyvsp[0].num));
                   }
#line 2352 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 123:
#line 612 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSectioni(TOK_CHUNKSIZE, (yyvsp[0].num));
                   }
#line 2360 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 124:
#line 616 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSectioni(TOK_FADEINMS, (yyvsp[0].num));
                   }
#line 2368 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 125:
#line 620 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSectioni(TOK_FADEOUTMS, (yyvsp[0].num));
                   }
#line 2376 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 126:
#line 624 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSectioni(TOK_FRAMELIMIT, (yyvsp[0].num));
                   }
#line 2384 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 127:
#line 628 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSectioni(TOK_LIMIT, (yyvsp[0].num));
                   }
#line 2392 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 128:
#line 632 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSectionf(TOK_SCOORD, (yyvsp[0].rnum));
                   }
#line 2400 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 129:
#line 636 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSectionf(TOK_TCOORD, (yyvsp[0].rnum));
                   }
#line 2408 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 130:
#line 640 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSectionf(TOK_DELTAT, (yyvsp[0].rnum));
                   }
#line 2416 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 131:
#line 644 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSectionf(TOK_WIDTH, (yyvsp[0].rnum));
                   }
#line 2424 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 132:
#line 648 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSectionf(TOK_HEIGHT, (yyvsp[0].rnum));
                   }
#line 2432 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 133:
#line 652 "conqinit-yacc.y" /* yacc.c:1646  */
    {
                        cfgSectionb(TOK_TEX_LUMINANCE, (yyvsp[0].ptr));
                   }
#line 2440 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 135:
#line 659 "conqinit-yacc.y" /* yacc.c:1646  */
    { 
                    ptr = (char *)strdup((yyvsp[0].ptr));
                    if (ptr)
                      checkStr(ptr);
                    (yyval.ptr) = ptr;
                  }
#line 2451 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 136:
#line 666 "conqinit-yacc.y" /* yacc.c:1646  */
    { (yyval.num) = (yyvsp[0].num); }
#line 2457 "conqinit-yacc.c" /* yacc.c:1646  */
    break;

  case 137:
#line 668 "conqinit-yacc.y" /* yacc.c:1646  */
    { (yyval.rnum) = (yyvsp[0].rnum); }
#line 2463 "conqinit-yacc.c" /* yacc.c:1646  */
    break;


#line 2467 "conqinit-yacc.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 671 "conqinit-yacc.y" /* yacc.c:1906  */


/* search the 'public' planet list */
int cqiFindPlanet(char *str)
{
  int i;

  for (i=0; i < cqiGlobal->maxplanets; i++)
    if (!strncmp(cqiPlanets[i].name, str, MAXPLANETNAME))
      return i;

  return -1;
}

/* search internal planet list */
static int _cqiFindPlanet(char *str)
{
  int i;

  for (i=0; i < numPlanets; i++)
    if (!strncmp(_cqiPlanets[i].name, str, MAXPLANETNAME))
      return i;

  return -1;
}

/* search internal texture list */
static int _cqiFindTexture(char *texname)
{
  int i;

  for (i=0; i<numTextures; i++)
    if (!strncmp(_cqiTextures[i].name, texname, CQI_NAMELEN))
      return i;
  
  return -1;
}

/* search the public tex area list */
cqiTextureAreaPtr_t cqiFindTexArea(char *texnm, char *tanm, 
                                   cqiTextureAreaPtr_t defaultta)
{
  int tidx, i;

  if (!texnm || !tanm)
    {
      return defaultta;
    }

  if ((tidx = _cqiFindTexture(texnm)) == -1)
    {
      return defaultta;
    }

  for (i=0; i<_cqiTextures[tidx].numTexAreas; i++)
    if (!strncmp(_cqiTextures[tidx].texareas[i].name, tanm, MAXPLANETNAME))
      return &(_cqiTextures[tidx].texareas[i]);

  utLog("%s: could not find texarea %s in texture %s",
       __FUNCTION__,
       tanm, texnm);

  return defaultta;
}

/* search internal animation list */
static int _cqiFindAnimation(char *animname)
{
  int i;

  for (i=0; i<numAnimations; i++)
    if (!strncmp(_cqiAnimations[i].name, animname, CQI_NAMELEN))
      return i;
  
  return -1;
}

static int _cqiFindAnimDef(char *defname)
{
  int i;

  for (i=0; i<numAnimDefs; i++)
    if (!strncmp(_cqiAnimDefs[i].name, defname, CQI_NAMELEN))
      return i;
  
  return -1;
}

/* search internal effect list */
static int _cqiFindEffect(char *name)
{
  int i;

  for (i=0; i<numSoundEffects; i++)
    if (!strncmp(_cqiSoundEffects[i].name, name, CQI_NAMELEN))
      return i;
  
  return -1;
}

static int _cqiFindMusic(char *name)
{
  int i;

  for (i=0; i<numSoundMusic; i++)
    if (!strncmp(_cqiSoundMusic[i].name, name, CQI_NAMELEN))
      return i;
  
  return -1;
}

/* search public effect list */
int cqiFindEffect(char *name)
{
  int i;

  for (i=0; i<cqiNumSoundEffects; i++)
    if (!strncmp(cqiSoundEffects[i].name, name, CQI_NAMELEN))
      return i;
  
  return -1;
}

int cqiFindMusic(char *name)
{
  int i;

  for (i=0; i<cqiNumSoundMusic; i++)
    if (!strncmp(cqiSoundMusic[i].name, name, CQI_NAMELEN))
      return i;
  
  return -1;
}

static Unsgn32 hex2color(char *str)
{
  Unsgn32 v;

  /* default to 0 (black/transparent) */

  if (!str)
    return 0;

  if (sscanf(str, "%x", &v) != 1)
    {
      utLog("hex2color(): invalid color specification '%s' at line %d, setting to 0",
           str, lineNum);
      v = 0;
    }

  return v;
}
  

static int cqiValidateAnimations(void)
{
  int i, j;
  char tbuf[CQI_NAMELEN];
  int ndx;

  /* if no textures, no point */
  if (!_cqiTextures)
    return FALSE;

  if (!numAnimDefs || !numAnimations)
    return FALSE;

  /* go through each anim def, checking various things */
  for (i=0; i<numAnimDefs; i++)
    {
      /* first, if a texname specified, and there is no texanim
         associated with this animdef, make sure the texname
         exists. */
      if (_cqiAnimDefs[i].texname[0] && 
          !(_cqiAnimDefs[i].anims & CQI_ANIMS_TEX))
      {                         /* texname and no tex anim */
        /* make sure the texture exists. */
        if (_cqiFindTexture(_cqiAnimDefs[i].texname) < 0)
          {                     /* nope */
            utLog("%s: animdef %s: texture %s does not exist.",
                 __FUNCTION__, 
                 _cqiAnimDefs[i].name,
                 _cqiAnimDefs[i].texname);
            return FALSE;
          }
      }

      /* now check each anim type 
       *  
       * stages must be > 0 
       * a stage == 0 means to disable an anim type, in which case
       *  the anim type will never have been be enabled (endSection)
       */

      /* texanim */
      if (_cqiAnimDefs[i].anims & CQI_ANIMS_TEX)
        {
          if (_cqiAnimDefs[i].texanim.stages <= 0)
            {
              utLog("%s: animdef %s: texanim: stages must greater than zero.",
                   __FUNCTION__, 
                   _cqiAnimDefs[i].name);
              return FALSE;
            }
          
          /* must be a texname */
          if (!_cqiAnimDefs[i].texname[0])
            {
              /* copy the animdef name over */
              strncpy(_cqiAnimDefs[i].texname, _cqiAnimDefs[i].name, 
                      CQI_NAMELEN - 1);
            }

          /* for each stage, build a texname and make sure it
             exists */
          for (j=0; j<_cqiAnimDefs[i].texanim.stages; j++)
            {

              /* if the texanim only contains a single stage (one texture)
               * then do not append the stage number to the texname.
               */

              if (_cqiAnimDefs[i].texanim.stages == 1)
                snprintf(tbuf, CQI_NAMELEN - 1, "%s",
                         _cqiAnimDefs[i].texname);
              else
                snprintf(tbuf, CQI_NAMELEN - 1, "%s%d",
                         _cqiAnimDefs[i].texname,
                         j);
              
              /* locate the texture */
              if (_cqiFindTexture(tbuf) < 0)
                {                     /* nope */
                  utLog("%s: animdef %s: texanim: texture %s does not exist.",
                       __FUNCTION__, 
                       _cqiAnimDefs[i].name,
                       tbuf);
                  return FALSE;
                }
            }
        }
      
      /* colanim */
      if (_cqiAnimDefs[i].anims & CQI_ANIMS_COL)
        {
          if (_cqiAnimDefs[i].colanim.stages <= 0)
            {
              utLog("%s: animdef %s: colanim: stages must greater than zero.",
                   __FUNCTION__, 
                   _cqiAnimDefs[i].name);
              return FALSE;
            }
        }

      /* geoanim */
      if (_cqiAnimDefs[i].anims & CQI_ANIMS_GEO)
        {
          /* if stages is 0 (meaning infinite) then loops is meaningless -
             set to 0 and warn. */
          if (_cqiAnimDefs[i].geoanim.stages <= 0)
            {
              utLog("%s: animdef %s: geoanim: stages must greater than zero.",
                   __FUNCTION__, 
                   _cqiAnimDefs[i].name);
              return FALSE;
            }
        }
    } /* for */


  /* now, make sure each animation specifies an existing
     animdef, set up adIndex */
  for (i=0; i < numAnimations; i++)
    {
      if ((ndx = _cqiFindAnimDef(_cqiAnimations[i].animdef)) < 0)
        {                       /* nope */
          utLog("%s: animdef %s does not exist for animation %s.",
               __FUNCTION__, 
               _cqiAnimations[i].animdef,
               _cqiAnimations[i].name);
          return FALSE;
        }
      else                      /* save the index */
        _cqiAnimations[i].adIndex = ndx;
    }
          
  return TRUE;
}

static int cqiValidatePlanets(void)
{
  int i;
  int mur = -1;
  int homeplan[NUMPLAYERTEAMS];             /* count of home planets */

  /* first things first... If there was no global read, then no
     point in continuing */

  if (!globalRead)
    return FALSE;

  memset((void *)homeplan, 0, sizeof(int) * NUMPLAYERTEAMS);

  if (mur < 0)
    {
      if ((mur = _cqiFindPlanet("Murisak")) < 0)
        {
          utLog("%s: cannot find planet Murisak, which must exist",
                  __FUNCTION__);
          mur = 0;
        }
    }

  /* first fill in any empty slots */
  if (numPlanets < NUMPLANETS)
    {
      for (i = numPlanets; i < _cqiGlobal->maxplanets; i++)
        {
          /* use the slot number in the name to reduce chance of dup names */
          snprintf(_cqiPlanets[i].name, MAXPLANETNAME - 1, "ZZExtra %d", 
                   i);
          /* FIXME - no hc mur */
          strcpy(_cqiPlanets[i].primname, "Murisak");

          _cqiPlanets[i].primary = mur;
          _cqiPlanets[i].angle = 0.0;
          _cqiPlanets[i].velocity = 0.0;
          _cqiPlanets[i].radius = 0.0;
          _cqiPlanets[i].ptype = PLANET_GHOST;
          _cqiPlanets[i].pteam = TEAM_NOTEAM;
          _cqiPlanets[i].armies = 0;
          _cqiPlanets[i].visible = FALSE;
          _cqiPlanets[i].core = FALSE;
          _cqiPlanets[i].xcoord = 0.0;
          _cqiPlanets[i].ycoord = 0.0;
          /* leave texname blank so default rules will fire if neccessary */
        }

      if (cqiVerbose)
        utLog("%s: filled %d unspecified planet slots.",
                __FUNCTION__, NUMPLANETS - numPlanets);
    }


  for (i=0; i < numPlanets; i++)
    {
      /* see if the primary name == name, if so, orbit mur and vel = 0 */

      if (!strncmp(_cqiPlanets[i].name, _cqiPlanets[i].primname, 
                   MAXPLANETNAME))
        {
          _cqiPlanets[i].velocity = 0.0;

          /* FIXME - need a ghost 0, not harcoded mur */
          _cqiPlanets[i].primary = mur;
        }
      else
        {                       /* else, find the primary, default to mur */
          if ((_cqiPlanets[i].primary = _cqiFindPlanet(_cqiPlanets[i].primname)) < 0)
            {                   /* couldn't find it */
              if (cqiVerbose && i != mur)
                utLog("%s: can't find primary '%s' for planet '%s', defaulting to '%s'",
                        __FUNCTION__,
                        _cqiPlanets[i].primname,
                        _cqiPlanets[i].name,
                        _cqiPlanets[mur].name);
              
              _cqiPlanets[i].primary = mur;
            }
        }

      /* count home planets */

      if (_cqiPlanets[i].homeplanet)
        switch (_cqiPlanets[i].pteam)
          {
          case TEAM_FEDERATION:
          case TEAM_ROMULAN:
          case TEAM_KLINGON:
          case TEAM_ORION:
            homeplan[_cqiPlanets[i].pteam]++;
            break;
          default:
            break;
          }

    }


  /* make sure 3 homeplanets per 'normal' team have been specified */
  for (i=0; i < NUMPLAYERTEAMS; i++)
    {
      if (homeplan[i] != 3)
        {
          utLog("%s: team %s must have 3 homeplanets. %d were specified.",
                  __FUNCTION__, team2str(i), homeplan[i]);
          return FALSE;
        }
    }


  if (cqiVerbose)
    utLog("%s: total planets %d (%d loaded, %d extra)",
            __FUNCTION__,
            _cqiGlobal->maxplanets, 
            numPlanets, 
            _cqiGlobal->maxplanets - numPlanets);


  return TRUE;
}

/* parse a file */
int cqiLoadRC(int rcid, char *filename, int verbosity, int debugl)
{
  FILE *infile;
  extern FILE *yyin;
  int fail = FALSE;
  char buffer[BUFFER_SIZE];

  cqiDebugl = debugl;
  cqiVerbose = verbosity;

  switch (rcid)
    {
    case CQI_FILE_CONQINITRC:   /* optional */
      if (filename)
        strncpy(buffer, filename, BUFFER_SIZE - 1);
      else
        snprintf(buffer, sizeof(buffer)-1, "%s/%s", utGetPath(CONQETC), 
                 "conqinitrc");
      break;
    case CQI_FILE_TEXTURESRC:
    case CQI_FILE_TEXTURESRC_ADD: 
      if (filename)
        strncpy(buffer, filename, BUFFER_SIZE - 1);
      else
        snprintf(buffer, sizeof(buffer)-1, "%s/%s", utGetPath(CONQETC), 
                 "texturesrc");
      break;
    case CQI_FILE_SOUNDRC:
    case CQI_FILE_SOUNDRC_ADD: 
      if (filename)
        strncpy(buffer, filename, BUFFER_SIZE - 1);
      else
        snprintf(buffer, sizeof(buffer)-1, "%s/%s", utGetPath(CONQETC), 
                 "soundrc");
      break;
    default:                    /* programmer error */
      utLog("%s: invalid rcid %d, bailing.", __FUNCTION__, rcid);
      return FALSE;
      break;
    }

  utLog("%s: Loading '%s'...", __FUNCTION__, buffer);
  if ((infile = fopen(buffer, "r")) == NULL)
    {
      utLog("%s: fopen(%s) failed: %s",
           __FUNCTION__,
           buffer,
           strerror(errno));
      
      /* a failed CQI_FILE_TEXTURESRC_ADD is no big deal,
         CQI_FILE_TEXTURESRC/CONQINITRC is another story however... */

      utLog("%s: using default init tables.", __FUNCTION__);
      switch(rcid)
        {
        case CQI_FILE_TEXTURESRC:
          {
            utLog("%s: FATAL: no textures.", __FUNCTION__);
            return FALSE;
          }
          break;
          
        case CQI_FILE_SOUNDRC:
          {
            cqiSoundConf = &defaultSoundConf;
            cqiSoundEffects  = defaultSoundEffects;
            cqiNumSoundEffects = defaultNumSoundEffects;
            cqiSoundMusic = defaultSoundMusic;
            cqiNumSoundMusic = defaultNumSoundMusic;
          }
          break;
        }

      return FALSE;
    }

  initrun(rcid);

  yyin = infile;

  goterror = FALSE;
  lineNum = 0;
  if ( yyparse() == ERR || goterror )
    {
      utLog("conqinit: parse error." );
      fail = TRUE;
    }
  
  fclose(infile);

  /* check textures early */
  if (rcid == CQI_FILE_TEXTURESRC || 
      rcid == CQI_FILE_TEXTURESRC_ADD)
    {
      if (fail && rcid == CQI_FILE_TEXTURESRC)
        {
          utLog("%s: FATAL: no textures.", __FUNCTION__);
          return FALSE;
        }

      cqiTextures = _cqiTextures;
      cqiNumTextures = numTextures;

      if (cqiVerbose)
        utLog("%s: loaded %d texture descriptors.",
             __FUNCTION__, fileNumTextures);

      /* now validate any animations */
      if (!cqiValidateAnimations())
        {
          utLog("%s: FATAL: no animations.", __FUNCTION__);
          return FALSE;
        }

      if (cqiVerbose)
        {
          utLog("%s: loaded %d Animation descriptors.",
               __FUNCTION__, fileNumAnimations);
          utLog("%s: loaded %d Animation definitions.",
               __FUNCTION__, fileNumAnimDefs);
        }

      cqiAnimations = _cqiAnimations;
      cqiNumAnimations = numAnimations;
      cqiAnimDefs = _cqiAnimDefs;
      cqiNumAnimDefs = numAnimDefs;

      return TRUE;
    }

  /* sounds */
  if (rcid == CQI_FILE_SOUNDRC || rcid == CQI_FILE_SOUNDRC_ADD)
    {
      if (fail && rcid == CQI_FILE_SOUNDRC)
        {
          utLog("%s: using default sound data.", __FUNCTION__);
          cqiSoundConf = &defaultSoundConf;
          cqiSoundEffects  = defaultSoundEffects;
          cqiNumSoundEffects = defaultNumSoundEffects;
          cqiSoundMusic = defaultSoundMusic;
          cqiNumSoundMusic = defaultNumSoundMusic;

          return FALSE;
        }

      utLog("%s: loaded %d Music definitions.",
           __FUNCTION__, fileNumMusic);
      utLog("%s: loaded %d Effect definitions.",
           __FUNCTION__, fileNumEffects);
      cqiSoundConf = _cqiSoundConf;
      cqiSoundEffects = _cqiSoundEffects;
      cqiNumSoundEffects = numSoundEffects;
      cqiSoundMusic = _cqiSoundMusic;
      cqiNumSoundMusic = numSoundMusic;

      return TRUE;
    }


  if (!fail && !cqiValidatePlanets())
    {
      utLog("%s: cqiValidatePlanets() failed.", __FUNCTION__);

      cqiGlobal    = &defaultGlobalInit;
      cqiShiptypes = defaultShiptypes;
      cqiPlanets   = defaultPlanets;
      utLog("%s: using default init tables.", __FUNCTION__);
      return FALSE;
    }

  if (!fail)
    {
      /* if we were successful, export the new tables */
      cqiGlobal    = _cqiGlobal;
      cqiShiptypes = _cqiShiptypes;
      cqiPlanets   = _cqiPlanets;
    }
  else
    {                           /* use the defaults */
      utLog("%s: using default init tables.", __FUNCTION__);
      cqiGlobal    = &defaultGlobalInit;
      cqiShiptypes = defaultShiptypes;
      cqiPlanets   = defaultPlanets;
    }

  return (fail) ? FALSE: TRUE;
}

static char *ptype2str(int ptype)
{
  switch (ptype)
    {
    case PLANET_CLASSM:
      return "M";
      break;
    case PLANET_DEAD:
      return "D";
      break;
    case PLANET_SUN:
      return "S";
      break;
    case PLANET_MOON:
      return "m";
      break;
    case PLANET_GHOST:
      return "G";
      break;
    case PLANET_CLASSA:
      return "A";
      break;
    case PLANET_CLASSO:
      return "O";
      break;
    case PLANET_CLASSZ:
      return "Z";
      break;
    }
  
  return "?";
}

static int str2ptype(char *str)
{
  
  /* we will just look at the first byte  */
  switch (str[0])
    {
    case 'M':
      return PLANET_CLASSM;
      break;
    case 'D':
      return PLANET_DEAD;
      break;
    case 'S':
      return PLANET_SUN;
      break;
    case 'm':
      return PLANET_MOON;
      break;
    case 'G':
      return PLANET_GHOST;
      break;
    case 'A':
      return PLANET_CLASSA;
      break;
    case 'O':
      return PLANET_CLASSO;
      break;
    case 'Z':
      return PLANET_CLASSZ;
      break;
    }
  
  return PLANET_DEAD;           /* default */
}


static char *team2str(int pteam)
{
  switch (pteam)
    {
    case TEAM_FEDERATION:
      return "F";
      break;
    case TEAM_ROMULAN:
      return "R";
      break;
    case TEAM_KLINGON:
      return "K";
      break;
    case TEAM_ORION:
      return "O";
      break;
    case TEAM_SELFRULED:
      return "S";
      break;
    case TEAM_NOTEAM:
      return "N";
      break;
    case TEAM_GOD:
      return "G";
      break;
    case TEAM_EMPIRE:
      return "E";
      break;
    }  
  
  return "?";
}

static int str2team(char *str)
{
  switch (str[0])
    {
    case 'F':
      return TEAM_FEDERATION;
      break;
    case 'R':
      return TEAM_ROMULAN;
      break;
    case 'K':
      return TEAM_KLINGON;
      break;
    case 'O':
      return TEAM_ORION;
      break;
    case 'S':
      return TEAM_SELFRULED;
      break;
    case 'N':
      return TEAM_NOTEAM;
      break;
    case 'G':
      return TEAM_GOD;
      break;
    case 'E':
      return TEAM_EMPIRE;
      break;
    }  
  
  return TEAM_NOTEAM;           /* default */
}

/* Dump the parsed soundrc to stdout in sounddata.h format */
/* this includes soundconf, effects, and music */
void dumpSoundDataHdr(void)
{
  char buf[MAXLINE];
  int i;
  

  if (!cqiSoundConf || !cqiNumSoundEffects)
    return;

  /* preamble */
  utFormatTime( buf, 0 );
  printf("/* Generated by conqinit on %s */\n", buf);
  printf("/* $Id$ */\n");
  printf("\n\n");

  printf("#ifndef _SOUNDDATA_H\n");
  printf("#define _SOUNDDATA_H\n\n");


  printf("static cqiSoundConfRec_t defaultSoundConf = {\n");
  printf("  %d,\n", cqiSoundConf->samplerate);
  printf("  %d,\n", cqiSoundConf->stereo);
  printf("  %d,\n", cqiSoundConf->fxchannels);
  printf("  %d\n", cqiSoundConf->chunksize);
  printf("};\n\n");
    

  printf("static int defaultNumSoundMusic = %d;\n\n", cqiNumSoundMusic);

  /* if there is no music built in... */
  if (!cqiNumSoundMusic)
    {
      printf("static cqiSoundRec_t *defaultSoundMusic = NULL;\n");
      printf("\n\n");
    }
  else
    {
      printf("static cqiSoundRec_t defaultSoundMusic[%d] = {\n", 
             cqiNumSoundMusic);
      
      /* music */
      for (i=0; i<cqiNumSoundMusic; i++)
        printf(" { \"%s\", \"%s\", %d, %d, %d, %d, %d, %d, %d, %d },\n",
               cqiSoundMusic[i].name,
               cqiSoundMusic[i].filename,
               cqiSoundMusic[i].volume,
               cqiSoundMusic[i].pan,
               cqiSoundMusic[i].fadeinms,
               cqiSoundMusic[i].fadeoutms,
               cqiSoundMusic[i].loops,
               cqiSoundMusic[i].limit,
               cqiSoundMusic[i].framelimit,
               cqiSoundMusic[i].delayms);
      
      printf("};\n\n");
    }

  /* effect */
  printf("static int defaultNumSoundEffects = %d;\n\n", cqiNumSoundEffects);
  printf("static cqiSoundRec_t defaultSoundEffects[%d] = {\n", 
         cqiNumSoundEffects);

  for (i=0; i<cqiNumSoundEffects; i++)
    printf(" { \"%s\", \"%s\", %d, %d, %d, %d, %d, %d, %d, %d },\n",
           cqiSoundEffects[i].name,
           cqiSoundEffects[i].filename,
           cqiSoundEffects[i].volume,
           cqiSoundEffects[i].pan,
           cqiSoundEffects[i].fadeinms,
           cqiSoundEffects[i].fadeoutms,
           cqiSoundEffects[i].loops,
           cqiSoundEffects[i].limit,
           cqiSoundEffects[i].framelimit,
           cqiSoundEffects[i].delayms);
  
  printf("};\n\n");

  printf("#endif /* _SOUNDDATA_H */\n\n");

  
  return;
}


/* Dump the parsed initdata to stdout in initdata.h format */
void dumpInitDataHdr(void)
{
  char buf[MAXLINE];
  int i;
  
  /* preamble */
  utFormatTime( buf, 0 );
  printf("/* Generated by conqinit on %s */\n", buf);
  printf("/* $Id$ */\n");
  printf("\n\n");

  printf("#ifndef _INITDATA_H\n");
  printf("#define _INITDATA_H\n\n");

  /* FIXME, need to use dynamics when ready */
  /* globals always first! */  

  printf("static cqiGlobalInitRec_t defaultGlobalInit = {\n");
  printf("\t %d,\n", cqiGlobal->maxplanets);
  printf("\t %d,\n", cqiGlobal->maxships);
  printf("\t %d,\n", cqiGlobal->maxusers); 
  printf("\t %d,\n", cqiGlobal->maxhist); 
  printf("\t %d,\n", cqiGlobal->maxmsgs); 
  printf("\t %d,\n", cqiGlobal->maxtorps); 
  printf("\t %d\n", cqiGlobal->maxshiptypes); 
  printf("};\n\n");

  /* shiptypes */
  
  printf("/* The shiptype sections are currently ignored. */\n");

  printf("static cqiShiptypeInitRec_t defaultShiptypes[%d] = {\n",
         cqiGlobal->maxshiptypes); 
  for (i=0; i < cqiGlobal->maxshiptypes; i++)
    {
      printf(" { \n");
      printf("   \"%s\",\n", cqiShiptypes[i].name);
      printf("   %f,\n", cqiShiptypes[i].engfac);
      printf("   %f,\n", cqiShiptypes[i].weafac);
      printf("   %f,\n", cqiShiptypes[i].accelfac);
      printf("   %d,\n", cqiShiptypes[i].torpwarp);
      printf("   %d,\n", cqiShiptypes[i].warpmax);
      printf("   %d,\n", cqiShiptypes[i].armymax);
      printf("   %d,\n", cqiShiptypes[i].shmax);
      printf("   %d,\n", cqiShiptypes[i].dammax);
      printf("   %d,\n", cqiShiptypes[i].torpmax);
      printf("   %d\n", cqiShiptypes[i].fuelmax);
      printf(" },\n");
    }
  printf("};\n\n");
  
  /* planets */  
  printf("static cqiPlanetInitRec_t defaultPlanets[%d] = {\n",
         cqiGlobal->maxplanets); 

  for (i=0; i < cqiGlobal->maxplanets; i++)
    {
      printf(" { \n");
      printf("   \"%s\",\n", cqiPlanets[i].name);

/* FIXME - planet name == primary indicates stationary */
      
      if (cqiPlanets[i].primary)
        {
          printf("   \"%s\",\n", cqiPlanets[cqiPlanets[i].primary].name);
          printf("   %d,\n", cqiPlanets[i].primary);
        }
      else  
        {
          printf("   \"Murisak\",\n");      
          printf("   0,\n");
        }

      printf("   %f,\n", cqiPlanets[i].angle);
      printf("   %f,\n", cqiPlanets[i].velocity);
      printf("   %f,\n", cqiPlanets[i].radius);
      printf("   %d,\n", cqiPlanets[i].ptype);
      printf("   %d,\n", cqiPlanets[i].pteam);
      printf("   %d,\n", cqiPlanets[i].armies);
      printf("   %d,\n", cqiPlanets[i].visible);
      printf("   %d,\n", cqiPlanets[i].core);
      printf("   %d,\n", cqiPlanets[i].homeplanet);

      printf("   %f,\n", cqiPlanets[i].xcoord);
      printf("   %f,\n", cqiPlanets[i].ycoord);
      
      printf("   %d,\n", (int)cqiPlanets[i].size);

      /* we never write out a planet texture name */
      printf("   \"\",\n");

      printf(" },\n");

    }
  printf("};\n\n");

  printf("#endif /* _INITDATA_H */\n\n");

  
  return;
}


/* Dump the current universe to stdout in conqinitrc format */
void dumpUniverse(void)
{
  char buf[MAXLINE];
  int i, j;
  
  map_common();

  utFormatTime( buf, 0 );
  printf("# Generated by conqinit on %s\n", buf);
  printf("#\n#\n");
  /* comments */
  printf("# Valid values for planets->ptype: \n");
  printf("#     \"M\"               Class M (fuel)\n");
  printf("#     \"D\"               Class D (dead)\n");
  printf("#     \"S\"               Sun\n");
  printf("#     \"m\"               Moon\n");
  printf("#     \"G\"               Ghost\n");
  printf("#     \"A\"               Class A\n");
  printf("#     \"O\"               Class O\n");
  printf("#     \"Z\"               Class Z\n");
  printf("#\n#\n");
  printf("# Valid values for planets->pteam: \n");
  printf("#     \"F\"               Federation\n");
  printf("#     \"R\"               Romulan\n");
  printf("#     \"K\"               Klingon\n");
  printf("#     \"O\"               Orion\n");
  printf("#     \"S\"               Self Ruled\n");
  printf("#     \"N\"               No Team (non)\n");
  printf("#     \"G\"               God\n");
  printf("#     \"E\"               Empire\n");
  printf("#\n");
  printf("# armies can be specified as a single or pair of numbers.\n");
  printf("#\n");
  printf("# armies 50             sets armies to 50\n");
  printf("# armies 20 100         set armies to random value between 20 and 100\n");
  printf("#\n");
  printf("# If the angle specified for a planet is negative, then a random angle\n");
  printf("# will be chosen\n");

  printf("#\n\n");

  /* FIXME, need to use dynamics when ready */

  /* global is always first */  

  printf("# DO NOT CHANGE VALUES IN THE GLOBAL SECTION\n");
  printf("# Doing so will break compatibility, and we aren't ready\n");
  printf("# for that yet.\n");
  printf("global {\n");
  printf("  planetmax 60\n");
  printf("  shipmax   20\n");
  printf("  usermax   500\n");
  printf("  histmax   40\n");
  printf("  msgmax    60\n");
  printf("}\n\n");
  
  /* shiptypes */
  
  printf("# The shiptype sections are currently ignored.\n");
  for (i=0; i < MAXNUMSHIPTYPES; i++)
    {
      printf("shiptype {\n");
      printf("  name       \"%s\"\n", ShipTypes[i].name);
      printf("  engfac     %f\n", ShipTypes[i].engfac);
      printf("  weafac     %f\n", ShipTypes[i].weafac);
      printf("  accelfac   %f\n", ShipTypes[i].accelfac);
      printf("  torpwarp   %d\n", (int)ShipTypes[i].torpwarp);
      printf("  warpmax    %d\n", (int)ShipTypes[i].warplim);
      printf("  armymax    %d\n", ShipTypes[i].armylim);
      printf("  shmax      100\n");
      printf("  dammax     100\n");
      printf("  torpmax    9\n");
      printf("  fuelmax    999\n");
      printf("}\n\n");
    }
  
  /* planets */  
  for (i=1; i <= NUMPLANETS; i++)
    {
      printf("planet {\n");
      printf("  name        \"%s\"\n", Planets[i].name);

/* FIXME - planet name == primary indicates stationary */
      if (Planets[i].primary)
        printf("  primary     \"%s\"\n", Planets[Planets[i].primary].name);
      else  
        printf("  primary     \"\"\n");      

      printf("  angle       %f\n", Planets[i].orbang);
      printf("  velocity    %f\n", Planets[i].orbvel);
      printf("  radius      %f\n", Planets[i].orbrad);
      printf("  ptype       \"%s\"\n", ptype2str(Planets[i].type));
      printf("  pteam       \"%s\"\n", team2str(Planets[i].team));
      printf("  armies      %d\n", Planets[i].armies);
      printf("  visible     \"%s\"\n", (Planets[i].real) ? "yes" : "no");
      if (i <= NUM_BASEPLANETS && Planets[i].real && 
          (Planets[i].type != PLANET_MOON && Planets[i].type != PLANET_SUN &&
           Planets[i].type != PLANET_GHOST))
        printf("  core        \"yes\"\n");
      else
        printf("  core        \"no\"\n");
      
      /* look for homeplanets.  The 'homeplanet' concept should be moved
         into the planet struct of the cmn block someday. */
      for (j=0; j<3; j++)
        if (Teams[Planets[i].team].teamhplanets[j] == i)
          break;

      if (j >= 3)
        printf("  homeplanet  \"no\"\n");
      else
        printf("  homeplanet  \"yes\"\n");

      printf("  x           %f\n", Planets[i].x);
      printf("  y           %f\n", Planets[i].y);
      
      switch(Planets[i].type)
        {
        case PLANET_SUN:
          printf("  size        1500\n");
          printf("  texname     \"star\"\n");
          break;
        case PLANET_CLASSM:
          printf("  size        300\n");
          printf("  texname     \"classm\"\n");
          break;
        case PLANET_MOON:
          printf("  size        160\n");
          printf("  texname     \"luna\"\n");
          break;
        default:
          printf("  size        300\n");
          printf("  texname     \"classd\"\n");
          break;
        }

      printf("}\n\n");
    }
  
  return;
}

    
static void startSection(int section)
{
  if (cqiDebugl)
    utLog("%s: [%d] %s", __FUNCTION__, 
         curDepth + 1,
         sect2str(section));
  
  /* check for overflow */
  if ((curDepth + 1) >= MAX_NESTING_DEPTH)
    {
      utLog("CQI: %s: maximum nesting depth (%d) exceeded, ignoring "
           "section %s, near line %d", 
           __FUNCTION__, MAX_NESTING_DEPTH, sect2str(section),
           lineNum);
      goterror++;
      /* just return here as we haven't changed curDepth yet */
      return;
    }

  /* add it to the list */
  sections[++curDepth] = section;

  switch (section)
    {
    case TOK_GLOBAL:    
      {
        if (globalRead)
          {
            utLog("%s: global section already configured\n",
                 __FUNCTION__);
            goterror++;
            goto error_return;
          }

        _cqiGlobal = malloc(sizeof(cqiGlobalInitRec_t));
        if (!_cqiGlobal)
          {
            utLog("%s: Could not allocate GlobalInitRec",
                    __FUNCTION__);
            goterror++;
            goto error_return;
          }
        else
          memset((void *)_cqiGlobal, 0, sizeof(cqiGlobalInitRec_t));
      }
      break;

    case TOK_SHIPTYPE:    
      {
        if (!globalRead)
          {
            utLog("%s: Have not read the global section (which must always be first). Ignoring SHIPTYPE",
                    __FUNCTION__);
            goterror++;
            goto error_return;
          }
      }
      break;
    case TOK_PLANET:    
      {
        if (!globalRead)
          {
            utLog("%s: Have not read the global section (which must always be first). Ignoring PLANET",
                    __FUNCTION__);
            goterror++;
            return;
          }
        /* clear and init the planet for parsing */
        memset((void *)&currPlanet, 0, sizeof(cqiPlanetInitRec_t));

        currPlanet.primary = -1;
        currPlanet.size = 300;  /* ### */
      }
      break;

    case TOK_TEXTURE:
      {
        memset((void *)&currTexture, 0, sizeof(cqiTextureInitRec_t));
        currTexAreas = NULL;
        numTexAreas = 0;
      }
      break;

    case TOK_ANIMATION:
      {
        memset((void *)&currAnimation, 0, sizeof(cqiAnimationInitRec_t));
        currAnimation.adIndex = -1;
      }
      break;

    case TOK_ANIMDEF:
      {
        if (PREVSECTION() == TOK_ANIMATION) /* an inlined animdef */
          { 
            int _adndx = -1;
            char tmpname[CQI_NAMELEN];

            /* inlined animdef 
             *
             * for inlined animdefs, the animation name it's a part of,
             * must have been specified already.  If not, then
             * something is wrong, declare an error and bail.
             */
            if (!currAnimation.name[0])
              {
                utLog("CQI: can't inline animdef at or near line %d: "
                     "animation's name has not been specified.", 
                     lineNum);
                goterror++;
                goto error_return;
              }
                
            /* Now, see if an animdef name was specified in the
             * animation.  If so, then we want to derive our new
             * animdef from a previously existing one, which must
             * already have been defined.
             */
            if (currAnimation.animdef[0])
              {                 
                /* it's been specified, look for it and init our new
                 * animdef with it 
                 */
                if ((_adndx = _cqiFindAnimDef(currAnimation.animdef)) < 0)
                  {
                    /* couldn't find it, error */
                    utLog("CQI: can't inline animdef at or near line %d: "
                         "source animdef %s is not defined.", 
                         lineNum, currAnimation.animdef);
                    goterror++;
                    goto error_return;
                  }

                /* initialize it, the new animdef name will be overridden
                 * below 
                 */
                currAnimDef = _cqiAnimDefs[_adndx];
              }
            else
              {                 /* just inlining a complete animdef, init */
                memset((void *)&currAnimDef, 0, sizeof(cqiAnimDefInitRec_t));
              }

            /* choose a unique name for this animdef.  We prefix it
             * with '.' (since '.' cannot be specified as part of a
             * name in a config file), and add the current (projected)
             * slot number to make it unique.
             */
            snprintf(tmpname, 
                     CQI_NAMELEN - 1 - (strlen(".-NNNNNN")), 
                     ".%s",
                     currAnimation.name);
            snprintf(currAnimDef.name, CQI_NAMELEN - 1, "%s-%06d",
                     tmpname, numAnimDefs + 1);

            /* now, reset the animation's animdef specification
             * (whether or not it had one) to point toward the new
             * animdef 
             */
            strncpy(currAnimation.animdef, currAnimDef.name, CQI_NAMELEN - 1);
          }
        else
          {
            /* a global animdef */
            memset((void *)&currAnimDef, 0, sizeof(cqiAnimDefInitRec_t));
          }
      }
      break;

    case TOK_SOUNDCONF:    
      {
        if (!_cqiSoundConf)
          {                     /* starting fresh */
            _cqiSoundConf = malloc(sizeof(cqiSoundConfRec_t));
            if (!_cqiSoundConf)
              {
                utLog("%s: Could not allocate SoundConf",
                     __FUNCTION__);
                goterror++;
                goto error_return;
              }
            else
              {
                memset((void *)_cqiSoundConf, 0, sizeof(cqiSoundConfRec_t));
                _cqiSoundConf->stereo = TRUE; /* default to stereo */
              }
            
          } /* else we are just overriding */
      }
      break;

    case TOK_EFFECT:
    case TOK_MUSIC:
      {
        memset((void *)&currSound, 0, sizeof(cqiSoundRec_t));
        
        currSound.loops = 1;    /* default to 1 loop */
        currSound.volume = 100;
        currSound.pan = 0;
      }
      break;

    default:
      break;
    }
  
  return;

  /* clean things up if there was an error */
 error_return:
  /* remove the section from the list */
  sections[curDepth] = 0;
  curDepth--;
  return;
}

static void endSection(void)
{
  if (cqiDebugl)
    utLog("%s: [%d] %s", __FUNCTION__, curDepth, sect2str(CURSECTION()));
  
  switch (CURSECTION())
    {
    case TOK_GLOBAL:    
      {                         /* make sure everything is specified, alloc
                                   new planet/shiptype arrays, reset counts
                                */ 
        
        if (!_cqiGlobal->maxplanets || !_cqiGlobal->maxships ||
            !_cqiGlobal->maxusers || !_cqiGlobal->maxhist ||
            !_cqiGlobal->maxmsgs)
          {                     /* something missing */
            utLog("CQI: GLOBAL section is incomplete, ignoring.");
            globalRead = FALSE; /* redundant I know, but.... */
          }
        else
          globalRead = TRUE;
        
        if (globalRead)
          {                     /* alloc new planet array */
            _cqiPlanets = malloc(sizeof(cqiPlanetInitRec_t) *
                                 _cqiGlobal->maxplanets);
            
            numPlanets = 0;
            
            if (!_cqiPlanets)
              {
                utLog("CQI: could not allocate memory for planets.");
                globalRead = FALSE; /* redundant I know, but.... */
                goterror++;
              }
            else
              memset((void *)_cqiPlanets, 0, sizeof(cqiPlanetInitRec_t) *
                     _cqiGlobal->maxplanets);
          }
      }
      break;
      
    case TOK_SHIPTYPE:    
      break;

    case TOK_TEXANIM:
      {
        /* stage == 0 means to disable the anim type */
        if (currAnimDef.texanim.stages) 
          currAnimDef.anims |= CQI_ANIMS_TEX; 
        else
          currAnimDef.anims &= ~CQI_ANIMS_TEX; 
          
      }
      break;

    case TOK_COLANIM:
      {
        /* stage == 0 means to disable the anim type */
        if (currAnimDef.colanim.stages)
          currAnimDef.anims |= CQI_ANIMS_COL; 
        else
          currAnimDef.anims &= ~CQI_ANIMS_COL; 
      }
      break;

    case TOK_GEOANIM:
      {
        /* stage == 0 means to disable the anim type */
        if (currAnimDef.geoanim.stages)
          currAnimDef.anims |= CQI_ANIMS_GEO;
        else
          currAnimDef.anims &= ~CQI_ANIMS_GEO; 
      }
      break;

    case TOK_TOGANIM:
      {
        /* delayms on a toganim == 0 means to disable the anim type */
        if (currAnimDef.toganim.delayms)
          currAnimDef.anims |= CQI_ANIMS_TOG;
        else
          currAnimDef.anims &= ~CQI_ANIMS_TOG; 
      }
      break;
      
    case TOK_TEXAREA:
      /* this is only valid from within a texture definition */
      if (PREVSECTION() == TOK_TEXTURE)
        {
          cqiTextureAreaPtr_t taptr;
          
          if (strlen(currTexArea.name))
            {
              
              /* resize the current list and add to it. */
              
              taptr = (cqiTextureAreaPtr_t)realloc((void *)currTexAreas, 
                                                   sizeof(cqiTextureAreaRec_t) * 
                                                   (numTexAreas + 1));
              
              if (!taptr)
                {  
                  utLog("CQI: Could not realloc %d texareas for texture %s, "
                       "ignoring texarea '%s'",
                       numTexAreas + 1,
                       currTexture.name,
                       currTexArea.name);
                  break;
                }
              
              currTexAreas = taptr;
              currTexAreas[numTexAreas] = currTexArea;
              numTexAreas++;
              currTexture.texareas = currTexAreas;
              currTexture.numTexAreas = numTexAreas;
              
            }
          else
            {
              utLog("CQI: texarea name at or near line %d was not specified, "
                   "ignoring.",
                   lineNum);
              goto endsection;
            }
        }
      break;

    case TOK_PLANET:    
      {
        /* check some basic things */
        if (!currPlanet.name[0] || !currPlanet.primname[0])
          {
            utLog("CQI: planet %d is missing name and/or primary",
                 numPlanets);
            goterror++;
            return;
          }
        
        if (numPlanets >= _cqiGlobal->maxplanets)
          {
            utLog("CQI: planet '%s' (%d) exceeds maxplanets (%d), ignoring.",
                  currPlanet.name, numPlanets, 
                 _cqiGlobal->maxplanets);
            goto endsection;
          }
        
        /* need more checks here ? */
        
        /* add it */
        _cqiPlanets[numPlanets] = currPlanet;
        numPlanets++;
      }
      
      break;
      
    case TOK_TEXTURE:
      {
        cqiTextureInitPtr_t texptr;
        int exists = -1;
        
        /* verify the required info was provided */
        if (!strlen(currTexture.name))
          {
            utLog("CQI: texture name at or near line %d was not specified, "
                 "ignoring.",
                 lineNum);
            goto endsection;
          }
        
        /* if the texture was overridden by a later definition
           just copy the new definition over it */
        exists = _cqiFindTexture(currTexture.name);
        
        /* if a filename wasn't specified, and this is not a 'color only'
           texture, then copy in the texname as the default */
        if (!strlen(currTexture.filename) && 
            !(currTexture.flags & CQITEX_F_COLOR_SPEC))
          strncpy(currTexture.filename, currTexture.name, CQI_NAMELEN - 1);
        
        if (exists >= 0)
          {
            /* overwrite existing texture def */
            _cqiTextures[exists] = currTexture;
            if (cqiDebugl)
              utLog("CQI: texture '%s' near line %d: overriding already "
                   "loaded texture.",
                   currTexture.name, lineNum);
          }
        else
          {                     /* make a new one */
            texptr = (cqiTextureInitPtr_t)realloc((void *)_cqiTextures, 
                                                  sizeof(cqiTextureInitRec_t) * 
                                                  (numTextures + 1));
            
            if (!texptr)
              {  
                utLog("CQI: Could not realloc %d textures, ignoring texture '%s'",
                     numTextures + 1,
                     currTexture.name);
                goto endsection;
              }

            _cqiTextures = texptr;
            _cqiTextures[numTextures] = currTexture;
            numTextures++;

            /* warn if the texture did not specify a color (will be
             *  black and transparent) 
             */

            if (!(currTexture.flags & CQITEX_F_HAS_COLOR))
              utLog("CQI: warning, texture '%s' does not specify a color", 
                    currTexture.name);

          }
        fileNumTextures++;
      }
      break;

    case TOK_ANIMATION:
      {
        cqiAnimationInitPtr_t animptr;
        int exists = -1;
        
        /* verify the required info was provided */
        if (!strlen(currAnimation.name))
          {
            utLog("CQI: animation name at or near line %d was not specified, "
                 "ignoring.",
                 lineNum);
            goto endsection;
          }
        
        /* if the animation was overridden by a later definition
           just copy the new definition over it */

        exists = _cqiFindAnimation(currAnimation.name);

        /* if a animdef wasn't specified, then copy in the
           name as the default */
        if (!strlen(currAnimation.animdef))
          strncpy(currAnimation.animdef, currAnimation.name, CQI_NAMELEN - 1);

        if (exists >= 0)
          {
            _cqiAnimations[exists] = currAnimation;
            if (cqiDebugl)
              utLog("CQI: animation '%s' near line %d: overriding already "
                   "loaded animation.",
                   currAnimation.name, lineNum);
          }
        else
          {                     /* make a new one */
            animptr = (cqiAnimationInitPtr_t)realloc((void *)_cqiAnimations, 
                                                  sizeof(cqiAnimationInitRec_t) * 
                                                  (numAnimations + 1));
            
            if (!animptr)
              {  
                utLog("CQI: Could not realloc %d animations, ignoring "
                     "animation '%s'",
                     numAnimations + 1,
                     currAnimation.name);
                goto endsection;
              }
            
            _cqiAnimations = animptr;
            _cqiAnimations[numAnimations] = currAnimation;
            numAnimations++;
          }
        fileNumAnimations++;
      }        
      break;
      
    case TOK_ANIMDEF:
      {
        cqiAnimDefInitPtr_t animptr;
        int exists = -1;
        
        /* verify the required info was provided */
        if (!strlen(currAnimDef.name))
          {
            utLog("CQI: animdef name at or near line %d was not specified, "
                 "ignoring.",
                 lineNum);
            goto endsection;
          }
        
        exists = _cqiFindAnimDef(currAnimDef.name);

        if (exists >= 0)
          {
            _cqiAnimDefs[exists] = currAnimDef;
            if (cqiDebugl)
              utLog("CQI: animdef '%s' near line %d: overriding already loaded "
                   "animdef.",
                   currAnimDef.name, lineNum);
          }
        else if (!currAnimDef.anims)
          {                     /* no animation types were declared */
            utLog("CQI: animdef '%s' near line %d: declared no animation "
                 "type sections. Ignoring.",
                 currAnimDef.name, lineNum);
            goto endsection;
          }
        else
          {                     /* make a new one */
            animptr = (cqiAnimDefInitPtr_t)realloc((void *)_cqiAnimDefs, 
                                                  sizeof(cqiAnimDefInitRec_t) * 
                                                  (numAnimDefs + 1));
            
            if (!animptr)
              {  
                utLog("CQI: Could not realloc %d animdefs, ignoring "
                     "animdef '%s'",
                     numAnimDefs + 1,
                     currAnimDef.name);
                goto endsection;
              }
            
            _cqiAnimDefs = animptr;
            _cqiAnimDefs[numAnimDefs] = currAnimDef;
            numAnimDefs++;
          }
        fileNumAnimDefs++;
      }        
      break;
      
    case TOK_SOUNDCONF:    
      {                         /* make sure everything is specified */

        if (!_cqiSoundConf->samplerate)
          _cqiSoundConf->samplerate = 22050;
        
        /* stereo is already enabled by default in startSection() */

        if (!_cqiSoundConf->fxchannels)
          _cqiSoundConf->fxchannels = 16;

        if (!_cqiSoundConf->chunksize)
          _cqiSoundConf->chunksize = 512;
      }
      break;


    case TOK_EFFECT:
      {
        cqiSoundPtr_t sndptr;
        int exists = -1;
        
        /* verify the required info was provided */
        if (!strlen(currSound.name))
          {
            utLog("CQI: effect name at or near line %d was not specified, "
                 "ignoring.",
                 lineNum);
            goto endsection;
          }

        /* if the effect was overridden by a later definition
           just copy the new definition over it */
        exists = _cqiFindEffect(currSound.name);

        /* if a filename wasn't specified, then copy in the name
           as the default */
        if (!strlen(currSound.filename))
          strncpy(currSound.filename, currSound.name, CQI_NAMELEN - 1);

        if (exists >= 0)
          {
            /* overwrite existing def */
            _cqiSoundEffects[exists] = currSound;
            if (cqiDebugl)
              utLog("CQI: effect '%s' near line %d: overriding already "
                   "loaded effect.",
                   currSound.name, lineNum);
          }
        else
          {                     /* make a new one */
            sndptr = (cqiSoundPtr_t)realloc((void *)_cqiSoundEffects, 
                                                  sizeof(cqiSoundRec_t) * 
                                                  (numSoundEffects + 1));
            
            if (!sndptr)
              {  
                utLog("CQI: Could not realloc %d effect, ignoring effect '%s'",
                     numSoundEffects + 1,
                     currSound.name);
                goto endsection;
              }
            
            _cqiSoundEffects = sndptr;
            _cqiSoundEffects[numSoundEffects] = currSound;
            numSoundEffects++;
          }
        fileNumEffects++;
      }
      break;

    case TOK_MUSIC:
      {
        cqiSoundPtr_t sndptr;
        int exists = -1;
        
        /* verify the required info was provided */
        if (!strlen(currSound.name))
          {
            utLog("CQI: music name at or near line %d was not specified, "
                 "ignoring.",
                 lineNum);
            goto endsection;
          }

        /* if the music was overridden by a later definition
           just copy the new definition over it */
        exists = _cqiFindMusic(currSound.name);

        /* if a filename wasn't specified, then copy in the name
           as the default */
        if (!strlen(currSound.filename))
          strncpy(currSound.filename, currSound.name, CQI_NAMELEN - 1);

        if (exists >= 0)
          {
            /* overwrite existing def */
            _cqiSoundMusic[exists] = currSound;
            if (cqiDebugl)
              utLog("CQI: music '%s' near line %d: overriding already "
                   "loaded music slot.",
                   currSound.name, lineNum);
          }
        else
          {                     /* make a new one */
            sndptr = (cqiSoundPtr_t)realloc((void *)_cqiSoundMusic, 
                                                  sizeof(cqiSoundRec_t) * 
                                                  (numSoundMusic + 1));
            
            if (!sndptr)
              {  
                utLog("CQI: Could not realloc %d music slots, "
                     "ignoring music '%s'",
                     numSoundMusic + 1,
                     currSound.name);
                goto endsection;
              }
            
            _cqiSoundMusic = sndptr;
            _cqiSoundMusic[numSoundMusic] = currSound;
            numSoundMusic++;
          }
        fileNumMusic++;
      }
      break;

    default:
      break;
    }

 endsection:

  sections[curDepth] = 0;
  if (curDepth > 0)
    curDepth--;
  
  return;
}

/* integers */
static void cfgSectioni(int item, int val)
{
  if (cqiDebugl)
    utLog(" [%d] section = %s\titem = %s\tvali = %d",
         curDepth, sect2str(CURSECTION()), item2str(item), val);
  
  switch (CURSECTION())
    {
    case TOK_GLOBAL:    
      {
        switch (item)
          {
          case TOK_PLANETMAX:
            _cqiGlobal->maxplanets = abs(val);
            break;
          case TOK_SHIPMAX: 
            _cqiGlobal->maxships = abs(val);
            break;
          case TOK_USERMAX: 
            _cqiGlobal->maxusers = abs(val);
            break;
          case TOK_HISTMAX: 
            _cqiGlobal->maxhist = abs(val);
            break;
          case TOK_MSGMAX: 
            _cqiGlobal->maxmsgs = abs(val);
            break;
          }            
      }

      break;
    case TOK_SHIPTYPE:    
      break;
    case TOK_PLANET:    
      {
        switch(item)
          {
          case TOK_ARMIES:
            currPlanet.armies = abs(val);
            break;
          case TOK_SIZE:
            currPlanet.size = fabs((real)val);
            break;
          }
      }
      break;
    case TOK_ANIMDEF:
      {
        currAnimDef.timelimit = abs(val);
      }
      break;

    case TOK_SOUNDCONF:    
      {
        switch (item)
          {
          case TOK_SAMPLERATE:
            _cqiSoundConf->samplerate = CLAMP(8192, 44100, abs(val));
            break;
          case TOK_FXCHANNELS:
            _cqiSoundConf->fxchannels = CLAMP(2, 64, abs(val));
            break;
          case TOK_CHUNKSIZE:
            _cqiSoundConf->chunksize = CLAMP(256, 8192, abs(val));
            break;
          default:
            break;
          }
      }

    case TOK_EFFECT:
    case TOK_MUSIC:
      {
        switch(item)
          {
          case TOK_VOLUME:
            currSound.volume = CLAMP(0, 100, abs(val));
            break;
          case TOK_PAN:
            currSound.pan = CLAMP(-128, 128, abs(val));
            break;
          case TOK_FADEINMS:
            currSound.fadeinms = CLAMP(0, 10000, abs(val));
            break;
          case TOK_FADEOUTMS:
            currSound.fadeoutms = CLAMP(0, 10000, abs(val));
            break;
          case TOK_LOOPS:
            currSound.loops = abs(val);
            break;
          case TOK_LIMIT:
            currSound.limit = abs(val);
            break;
          case TOK_FRAMELIMIT:
            currSound.framelimit = abs(val);
            break;
          case TOK_DELAYMS:
            currSound.delayms = abs(val);
            break;
          }

      }

    case TOK_TEXANIM:
      {
        switch(item)
          {
          case TOK_STAGES:
            currAnimDef.texanim.stages = abs(val);
            break;
          case TOK_LOOPS:
            currAnimDef.texanim.loops = abs(val);
            break;
          case TOK_DELAYMS:
            currAnimDef.texanim.delayms = abs(val);
            break;
          case TOK_LOOPTYPE:
            currAnimDef.texanim.looptype = abs(val);
            break;
          }
      }
      break;
      
    case TOK_COLANIM:
      {
        switch(item)
          {
          case TOK_STAGES:
            currAnimDef.colanim.stages = abs(val);
            break;
          case TOK_LOOPS:
            currAnimDef.colanim.loops = abs(val);
            break;
          case TOK_DELAYMS:
            currAnimDef.colanim.delayms = abs(val);
            break;
          case TOK_LOOPTYPE:
            currAnimDef.colanim.looptype = abs(val);
            break;
          }
      }
      break;
      
    case TOK_GEOANIM:
      {
        switch(item)
          {
          case TOK_STAGES:
            currAnimDef.geoanim.stages = abs(val);
            break;
          case TOK_LOOPS:
            currAnimDef.geoanim.loops = abs(val);
            break;
          case TOK_DELAYMS:
            currAnimDef.geoanim.delayms = abs(val);
            break;
          case TOK_LOOPTYPE:
            currAnimDef.geoanim.looptype = abs(val);
            break;
          }
      }
      break;
      
    case TOK_TOGANIM:
      {
        switch(item)
          {
          case TOK_DELAYMS:
            currAnimDef.toganim.delayms = abs(val);
            break;
          }
      }
      break;
      
    case TOK_ISTATE:
      {
        switch(item)
          {
          case TOK_SIZE:
            currAnimDef.isize = fabs((real)val);
            currAnimDef.istates |= AD_ISTATE_SZ;
            break;
          }
      }
      break;
      
    default:
      break;
    }

  return;
}

/* integer pair */
void cfgSectionil(int item, int val1, int val2)
{
  if (cqiDebugl)
    utLog(" [%d] section = %s\titem = %s\tvalil = %d, %d",
         curDepth, sect2str(CURSECTION()), item2str(item), val1, val2);

  switch (CURSECTION())
    {
    case TOK_PLANET:    
      {
        switch (item)
          {
          case TOK_ARMIES:
            {
              /* if we got a pair, randomly init one */
              /* make sure it's valid of course... */
              if (val1 >= val2 || val2 <= val1)
                {
                  utLog("%s: Planet '%s's army min must be less than it's max: min %d max %d is invalid.",
                       __FUNCTION__,
                       currPlanet.name,
                       val1, val2);
                  currPlanet.armies = 0;
                }
              else
                currPlanet.armies = rndint(abs(val1), abs(val2));

#if 0
              utLog("ARMIES got %d %d, rnd = %d\n",
                   val1, val2, currPlanet.armies);
#endif
            }
            break;
          }
      }
    }

  return;
}


/* reals */
static void cfgSectionf(int item, real val)
{
  if (cqiDebugl)
    utLog(" [%d] section = %s\titem = %s\tvalf = %f",
         curDepth, sect2str(CURSECTION()), item2str(item), val);

  switch (CURSECTION())
    {
    case TOK_GLOBAL:    
      break;
    case TOK_SHIPTYPE:    
      break;
    case TOK_PLANET:    
      {
        switch (item)
          {
          case TOK_ANGLE:
            currPlanet.angle = val;
            break;
          case TOK_VELOCITY:
            currPlanet.velocity = val;
            break;
          case TOK_RADIUS:
            currPlanet.radius = val;
            break;
          case TOK_XCOORD:
            currPlanet.xcoord = val;
            break;
          case TOK_YCOORD:
            currPlanet.ycoord = val;
            break;
          }
      }

      break;

    case TOK_TEXANIM:
      {
        switch(item)
          {
          case TOK_DELTAS:
            currAnimDef.texanim.deltas = val;
            break;
          case TOK_DELTAT:
            currAnimDef.texanim.deltat = val;
            break;
          }
      }
      break;
    case TOK_COLANIM:
      {
        switch(item)
          {
          case TOK_DELTAA:
            currAnimDef.colanim.deltaa = val;
            break;
          case TOK_DELTAR: /* red */
            currAnimDef.colanim.deltar = val;
            break;
          case TOK_DELTAG:
            currAnimDef.colanim.deltag = val;
            break;
          case TOK_DELTAB:
            currAnimDef.colanim.deltab = val;
            break;
          }
      }
      break;
      
    case TOK_GEOANIM:
      {
        switch(item)
          {
          case TOK_DELTAX:
            currAnimDef.geoanim.deltax = val;
            break;
          case TOK_DELTAY:
            currAnimDef.geoanim.deltay = val;
            break;
          case TOK_DELTAZ:
            currAnimDef.geoanim.deltaz = val;
            break;
          case TOK_DELTAR: /* rotation */
            currAnimDef.geoanim.deltar = val;
            break;
          case TOK_DELTAS: /* size */
            currAnimDef.geoanim.deltas = val;
            break;
          }
      }
      break;
      
    case TOK_ISTATE:
      {
        switch(item)
          {
          case TOK_ANGLE:
            currAnimDef.iangle = val;
            currAnimDef.istates |= AD_ISTATE_ANG;
            break;
          }
      }
      break;

    case TOK_TEXAREA:
      {
        switch(item)
          {
          case TOK_XCOORD:
            currTexArea.x = fabs(val);
            break;
          case TOK_YCOORD:
            currTexArea.y = fabs(val);
            break;
          case TOK_WIDTH:
            currTexArea.w = fabs(val);
            break;
          case TOK_HEIGHT:
            currTexArea.h = fabs(val);
            break;
          }
      }
      break;
      
    default:
      break;
    }
  return;
}

/* strings */
void cfgSections(int item, char *val)
{
  if (cqiDebugl)
    utLog(" [%d] section = %s\titem = %s\tvals = '%s'",
         curDepth, sect2str(CURSECTION()), 
         item2str(item), (val) ? val : "(NULL)" );

  if (!val)
    return;

  switch (CURSECTION())
    {
    case TOK_GLOBAL:    
      break;
    case TOK_SHIPTYPE:    
      break;
    case TOK_TEXAREA:
      {
        switch (item)
          {
          case TOK_NAME:
            strncpy(currTexArea.name, val, CQI_NAMELEN - 1);
            break;
          }
      }
      break;
    case TOK_TEXANIM:
      {
        switch(item)
          {
          case TOK_COLOR:
            currAnimDef.texanim.color = hex2color(val);
            break;
          }
      }
      break;
      
    case TOK_COLANIM:
      {
        switch(item)
          {
          case TOK_COLOR:
            currAnimDef.colanim.color = hex2color(val);
            break;
          }
      }
      break;
      
    case TOK_ISTATE:
      {
        switch(item)
          {
          case TOK_COLOR:
            currAnimDef.icolor = hex2color(val);
            currAnimDef.istates |= AD_ISTATE_COL;
            break;
          case TOK_TEXNAME:
            strncpy(currAnimDef.itexname, val, CQI_NAMELEN - 1);
            currAnimDef.istates |= AD_ISTATE_TEX;
            break;
          }
      }
      break;
      
    case TOK_PLANET:    
      {
        switch (item)
          {
          case TOK_NAME:
            strncpy(currPlanet.name, val, MAXPLANETNAME - 1);
            break;
          case TOK_PRIMARY:
            strncpy(currPlanet.primname, val, MAXPLANETNAME - 1);
            break;
          case TOK_PTYPE:
            currPlanet.ptype = str2ptype(val);
            break;
          case TOK_PTEAM:
            currPlanet.pteam = str2team(val);
            break;
          case TOK_TEXNAME:
            strncpy(currPlanet.texname, val, CQI_NAMELEN - 1);
            break;
          case TOK_COLOR:
            /* this used to be allowed, so for now just warn if 
             * verbose is on 
             */
            if (cqDebug)
              utLog("CQI: 'color' is no longer valid in planet definitions");
            break;
          }
      }
      break;

    case TOK_TEXTURE:
      {
        switch(item)
          {
          case TOK_NAME:
            strncpy(currTexture.name, val, CQI_NAMELEN - 1);
            break;
          case TOK_FILENAME:
            if (val[0] == 0)    /* empty filename means only color matters */
              currTexture.flags |= CQITEX_F_COLOR_SPEC;
            else
              strncpy(currTexture.filename, val, CQI_NAMELEN - 1);
            break;
          case TOK_COLOR:
            currTexture.flags |= CQITEX_F_HAS_COLOR;
            currTexture.color = hex2color(val);
            break;
          }            
      }
      break;
      
    case TOK_ANIMATION:
       {
        switch(item)
          {
          case TOK_NAME:
            strncpy(currAnimation.name, val, CQI_NAMELEN - 1);
            break;
          case TOK_ANIMDEF:
            strncpy(currAnimation.animdef, val, CQI_NAMELEN - 1);
            break;
          }
      }
      break;

    case TOK_ANIMDEF:
       {
        switch(item)
          {
          case TOK_NAME:
            if (PREVSECTION() == TOK_ANIMATION)
              {
                /* not allowed to set a name on inlined animdefs - it's
                 * already been done for you.
                 */
                  utLog("CQI: field 'name' is ignored for inlined animdefs.");
              }
            else
              strncpy(currAnimDef.name, val, CQI_NAMELEN - 1);
            break;
          case TOK_TEXNAME:
            strncpy(currAnimDef.texname, val, CQI_NAMELEN - 1);
            break;
          }
      }
      break;

    case TOK_EFFECT:
    case TOK_MUSIC:
      {
        switch(item)
          {
          case TOK_NAME:
            strncpy(currSound.name, val, CQI_NAMELEN - 1);
            break;
          case TOK_FILENAME:
            strncpy(currSound.filename, val, CQI_NAMELEN - 1);
          }
      }
      break;

    }

  /* be sure to free the value allocated */
  free(val);
  return;
}

/* booleans */
static void cfgSectionb(int item, char *val)
{
  int bval = parsebool(val);

  if (cqiDebugl)
    utLog(" [%d] section = %s\titem = %s\tvalb = '%s'",
         curDepth, sect2str(CURSECTION()), item2str(item), 
         (bval ? "yes" : "no"));

  if (bval == -1)
    {                           /* an error, do something sane */
      bval = 0;
    }
  
  switch (CURSECTION())
    {
    case TOK_GLOBAL:    
      break;
    case TOK_SHIPTYPE:    
      break;
    case TOK_PLANET:    
      {
        switch(item) 
          {
          case TOK_VISIBLE:
            currPlanet.visible = bval;
            break;
          case TOK_CORE:
            currPlanet.core = bval;
            break;
          case TOK_HOMEPLANET:
            currPlanet.homeplanet = bval;
            break;
          }
      }
      break;

    case TOK_TEXTURE:
      {
        switch(item) 
          {
          case TOK_MIPMAP:
            if (bval)
              currTexture.flags |= CQITEX_F_GEN_MIPMAPS;
            else
              currTexture.flags &= ~CQITEX_F_GEN_MIPMAPS;
              
            break;

          case TOK_TEX_LUMINANCE:
            if (bval)
              currTexture.flags |= CQITEX_F_IS_LUMINANCE;
            else
              currTexture.flags &= ~CQITEX_F_IS_LUMINANCE;
              
            break;
          }
      }
      break;

    case TOK_SOUNDCONF:    
      {
        switch (item)
          {
          case TOK_STEREO:
            _cqiSoundConf->stereo = bval;
            break;
          }
      }
      break;
      
    default:
      break;
    }
  
  return;
}

static char *sect2str(int section)
{
  switch (section)
    {
    case TOK_GLOBAL:
      return "GLOBAL";
      break;
    case TOK_SHIPTYPE:
      return "SHIPTYPE";
      break;
    case TOK_PLANET:
      return "PLANET";
      break;
    case TOK_TEXTURE:
      return "TEXTURE";
      break;
    case TOK_ANIMATION:
      return "ANIMATION";
      break;
    case TOK_ANIMDEF:
      return "ANIMDEF";
      break;
    case TOK_SOUNDCONF:
      return "SOUNDCONF";
      break;
    case TOK_EFFECT:
      return "EFFECT";
      break;
    case TOK_MUSIC:
      return "MUSIC";
      break;
    case TOK_LIMIT:
      return "LIMIT";
      break;
    case TOK_FRAMELIMIT:
      return "FRAMELIMIT";
      break;

      /* nested sections */
    case TOK_TEXANIM:
      return "TEXANIM";
      break;
    case TOK_COLANIM:
      return "COLANIM";
      break;
    case TOK_GEOANIM:
      return "GEOANIM";
      break;
    case TOK_TOGANIM:
      return "TOGANIM";
      break;
    case TOK_ISTATE:
      return "ISTATE";
      break;
    case TOK_TEXAREA:
      return "TEXAREA";
      break;
    }
  
  return "UNKNOWN";
}

static char *item2str(int item)
{
  switch (item)
    {
    case TOK_PLANETMAX:
      return "PLANETMAX";
      break;
    case TOK_SHIPMAX:
      return "SHIPMAX";
      break;
    case TOK_USERMAX:
      return "USERMAX";
      break;
    case TOK_HISTMAX:
      return "HISTMAX";
      break;
    case TOK_MSGMAX:
      return "MSGMAX";
      break;
    case TOK_NAME:
      return "NAME";
      break;
    case TOK_ENGFAC:
      return "ENGFAC";
      break;
    case TOK_WEAFAC:
      return "WEAFAC";
      break;
    case TOK_ACCELFAC:
      return "ACCELFAC";
      break;
    case TOK_TORPWARP:
      return "TORPWARP";
      break;
    case TOK_WARPMAX:
      return "WARPMAX";
      break;
    case TOK_ARMYMAX:
      return "ARMYMAX";
      break;
    case TOK_SHMAX:
      return "SHMAX";
      break;
    case TOK_DAMMAX:
      return "DAMMAX";
      break;
    case TOK_TORPMAX:
      return "TORPMAX";
      break;
    case TOK_SIZE:
      return "SIZE";
      break;
    case TOK_FUELMAX:
      return "FUELMAX";
      break;
    case TOK_PRIMARY:
      return "PRIMARY";
      break;
    case TOK_ANGLE:
      return "ANGLE";
      break;
    case TOK_VELOCITY:
      return "VELOCITY";
      break;
    case TOK_RADIUS:
      return "RADIUS";
      break;
    case TOK_PTYPE:
      return "PTYPE";
      break;
    case TOK_PTEAM:
      return "PTEAM";
      break;
    case TOK_ARMIES:
      return "ARMIES";
      break;
    case TOK_VISIBLE:
      return "VISIBLE";
      break;
    case TOK_CORE:
      return "CORE";
      break;
    case TOK_XCOORD:
      return "XCOORD";
      break;
    case TOK_YCOORD:
      return "YCOORD";
      break;
    case TOK_SCOORD:
      return "SCOORD";
      break;
    case TOK_TCOORD:
      return "TCOORD";
      break;
    case TOK_TEXNAME:
      return "TEXNAME";
      break;
    case TOK_COLOR:
      return "COLOR";
      break;
    case TOK_HOMEPLANET:
      return "HOMEPLANET";
      break;
    case TOK_FILENAME:
      return "FILENAME";
      break;
    case TOK_ANIMDEF:
      return "ANIMDEF";
      break;
    case TOK_TIMELIMIT:
      return "TIMELIMIT";
      break;
    case TOK_STAGES:
      return "STAGES";
      break;
    case TOK_LOOPS:
      return "LOOPS";
      break;
    case TOK_DELAYMS:
      return "DELAYMS";
      break;
    case TOK_LOOPTYPE:
      return "LOOPTYPE";
      break;
    case TOK_DELTAA:
      return "DELTAA";
      break;
    case TOK_DELTAR:
      return "DELTAR";
      break;
    case TOK_DELTAG:
      return "DELTAG";
      break;
    case TOK_DELTAB:
      return "DELTAB";
      break;
    case TOK_DELTAX:
      return "DELTAX";
      break;
    case TOK_DELTAY:
      return "DELTAY";
      break;
    case TOK_DELTAZ:
      return "DELTAZ";
      break;
    case TOK_DELTAS:
      return "DELTAS";
      break;
    case TOK_DELTAT:
      return "DELTAT";
      break;
    case TOK_WIDTH:
      return "WIDTH";
      break;
    case TOK_HEIGHT:
      return "HEIGHT";
      break;
    case TOK_MIPMAP:
      return "MIPMAP";
      break;

    case TOK_SAMPLERATE:
      return "SAMPLERATE";
      break;
    case TOK_VOLUME:
      return "VOLUME";
      break;
    case TOK_PAN:
      return "PAN";
      break;
    case TOK_STEREO:
      return "STEREO";
      break;
    case TOK_FXCHANNELS:
      return "FXCHANNELS";
      break;
    case TOK_CHUNKSIZE:
      return "CHUNKSIZE";
      break;
    case TOK_FADEINMS:
      return "FADEINMS";
      break;
    case TOK_FADEOUTMS:
      return "FADEOUTMS";
      break;
    case TOK_LIMIT:
      return "LIMIT";
      break;
    }
  
  return "UNKNOWN";
}

/* go through the string and convert all '.', '/', '\', and
 * non-printable characters into '_'.  Remove any double quotes. 
 *
 */
static void checkStr(char *str)
{
  char *s = str, *s2;
  
  if (!s)
    return;

  while (*s)
    {
      switch (*s)
        {
        case '\\':
        case '/':
        case '.':
        case ' ':
          *s = '_';
          s++;
          break;

        case '"':               /* copy over it */
          {
            s2 = s + 1;
            do 
              {
                *(s2 - 1) = *s2;
                s2++;
              } while (*(s2 - 1));
          }
          /* do not increment s here */
          break;
          
        default:
          {
            if (!isprint((unsigned int)*s))
              *s = '_';
          }
          s++;
          break;
        }

    }

  return;
}

static int parsebool(char *str)
{
  char *s;
  
  s = str;
  
  if (!s)
    return(-1);
  
  while(*s)
    {
      *s = (char)tolower(*s);
      s++;
    }
  
  if (((char *)strstr("false", str) != NULL) ||
      ((char *)strstr("no", str) != NULL)    ||
      ((char *)strstr("off", str) != NULL))
    {
      return(FALSE);
    }
  else if (((char *)strstr("true", str) != NULL) ||
           ((char *)strstr("yes", str) != NULL)  ||
           ((char *)strstr("on", str) != NULL))
    {
      return(TRUE);
    }
  else
    {
      utLog("parsebool(): error parsing '%s' line %d, \n\t%s\n",
              str, lineNum,
              "Boolean value must be 'yes', 'no', 'true', 'false', 'on', or 'off'.");
      return(-1);
    }
}


/* initrun - initalize for the run */
static void initrun(int rcid)
{

  switch (rcid)
    {
    case CQI_FILE_CONQINITRC:
      {
        if (_cqiGlobal)
          {
            if (_cqiGlobal != &defaultGlobalInit)
              free(_cqiGlobal);
            _cqiGlobal = NULL;
            globalRead = FALSE;
          }
        
        if (_cqiShiptypes)
          {
            if (_cqiShiptypes != defaultShiptypes)
              free(_cqiShiptypes);
            _cqiShiptypes = NULL;
            numShiptypes = 0;
          }
        
        if (_cqiPlanets)
          {
            if (_cqiPlanets != defaultPlanets)
              free(_cqiPlanets);
            _cqiPlanets = NULL;
            numPlanets = 0;
          }
      }

      break;

    case CQI_FILE_SOUNDRC:
    case CQI_FILE_SOUNDRC_ADD:
      {
        if (rcid == CQI_FILE_SOUNDRC)
          {                       /* if we are not adding, re-init */
            if (_cqiSoundConf)
              {
                if (_cqiSoundConf != &defaultSoundConf)
                  free(_cqiSoundConf);
                _cqiSoundConf = NULL;
              }              
            
            if (_cqiSoundEffects)
              {
                if (_cqiSoundEffects != defaultSoundEffects)
                  free(_cqiSoundEffects);
                _cqiSoundEffects = NULL;
              }
            numSoundEffects = 0;
            
            if (_cqiSoundMusic)
              {
                if (_cqiSoundMusic != defaultSoundMusic)
                  free(_cqiSoundMusic);
                _cqiSoundMusic = NULL;
              }
            numSoundMusic = 0;
          }
        
        fileNumEffects = 0;
        fileNumMusic = 0;

      }
      break;

    case CQI_FILE_TEXTURESRC:
    case CQI_FILE_TEXTURESRC_ADD:
      {      /* free/setup textures here */
        if (rcid == CQI_FILE_TEXTURESRC)
          {                       /* if we are not adding, re-init */
            if (_cqiTextures)
              {
                free(_cqiTextures);
                _cqiTextures = NULL;
              }
            numTextures = 0;
            
            if (_cqiAnimations)
              {
                free(_cqiAnimations);
                _cqiAnimations = NULL;
              }
            numAnimations = 0;
            
            if (_cqiAnimDefs)
              {
                free(_cqiAnimDefs);
                _cqiAnimDefs = NULL;
              }
            numAnimDefs = 0;
          }
        
        fileNumTextures = 0;
        fileNumAnimations = 0;
        fileNumAnimDefs = 0;
      }
      break;

   default:
      utLog("CQI: initrun: unkown rcid %d", rcid);
      break;
    }

  return;
  
}


