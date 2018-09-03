/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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

#ifndef YY_YY_CONQINIT_YACC_H_INCLUDED
# define YY_YY_CONQINIT_YACC_H_INCLUDED
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
#line 121 "conqinit-yacc.y" /* yacc.c:1909  */

  int num;
  char *ptr;
  real rnum;

#line 228 "conqinit-yacc.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_CONQINIT_YACC_H_INCLUDED  */
