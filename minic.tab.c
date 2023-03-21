/* A Bison parser, made by GNU Bison 3.7.5.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30705

/* Bison version string.  */
#define YYBISON_VERSION "3.7.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "minic.y"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "minic.tab.h"
#include "listaSimbolos.h"
#include "listaCodigo.h"

#define ROJO_T     "\x1b[31m"
#define RESET_COLOR    "\x1b[0m"

// Declaramos null a -1, y lo utilizamos como referencia para el valor vacio en identificadores
#define null -1
// Tamanyo maximo de los array
#define MAX_REG 10


// Array para llevar a cabo si un registro esta libre o ocupado
bool registro[MAX_REG] = {0};

// Variabel auxiliar que la utilizamos para guardar la posicion
PosicionListaC posicionES;

PosicionListaC posicionST;


// Array de posiciones en elque vamos guardando la ultima posicion de la tabla de Contenido
//		con la finalidad de a la hora de insertar la operacion beqz y las etiquetas la ponemos en la poscion correcta y despues
//		mostrar el contenido que correctamente, si que se pierda el orden.
int pila = 0;
PosicionListaC arrayPila[100];


// Creamos un array con los registros temporales, que lo utilizaremos para la funcion de "LiberarRegistro"
char arrayTempAux[] = {'0','1','2','3','4','5','6','7','8','9'};


Lista tablaSimbolos;
Tipo tipo;

ListaC tablaCodigo;

// Contador que serviria de Identificador Unico para cada cadena, ejemplo $str1 ,$str2, etc
int contadorCadenas = 1;

// Contador que serviria de Identificador Unico para cada etiqueta, ejemplo l1: ,l2:, etc
int contadorEtiquetas = 1;

bool error = false;

/* ======== DECLARACIONES DE FUNCIONES EXTRA A LA LISTA DE SIMBOLOS ========= */
bool perteneceTablaS(char *lexema);
void anyadeEntrada(char *lexema, Tipo tipo, int valorContenido);
bool esConstante(char *lexema);
void imprimirTablaS();

/* ======== DECLARACIONES DE FUNCIONES EXTRA A LA LISTA DE CODIGO ========= */
char *obtenerRegistro();
void liberarRegistro(char *registro);
char *concatenar(char *nombre);
void imprimirTablaC();

void yyerror();
extern int yylex();
extern int yylineno;

extern bool errorLEX;

// Eso se hace para que el minic.tab.h tambien incluya el fichero

#line 142 "minic.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "minic.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_VOID = 3,                       /* VOID  */
  YYSYMBOL_PRINT = 4,                      /* PRINT  */
  YYSYMBOL_READ = 5,                       /* READ  */
  YYSYMBOL_VAR = 6,                        /* VAR  */
  YYSYMBOL_CONST = 7,                      /* CONST  */
  YYSYMBOL_IF = 8,                         /* IF  */
  YYSYMBOL_WHILE = 9,                      /* WHILE  */
  YYSYMBOL_LLAVEI = 10,                    /* LLAVEI  */
  YYSYMBOL_LLAVED = 11,                    /* LLAVED  */
  YYSYMBOL_PARENI = 12,                    /* PARENI  */
  YYSYMBOL_PAREND = 13,                    /* PAREND  */
  YYSYMBOL_PUNTCOM = 14,                   /* PUNTCOM  */
  YYSYMBOL_COMMA = 15,                     /* COMMA  */
  YYSYMBOL_ASSIGNOP = 16,                  /* ASSIGNOP  */
  YYSYMBOL_STRING = 17,                    /* STRING  */
  YYSYMBOL_INT = 18,                       /* INT  */
  YYSYMBOL_ID = 19,                        /* ID  */
  YYSYMBOL_PLUSOP = 20,                    /* PLUSOP  */
  YYSYMBOL_MINUSOP = 21,                   /* MINUSOP  */
  YYSYMBOL_MULTOP = 22,                    /* MULTOP  */
  YYSYMBOL_DIVOP = 23,                     /* DIVOP  */
  YYSYMBOL_UMENOS = 24,                    /* UMENOS  */
  YYSYMBOL_NOELSE = 25,                    /* NOELSE  */
  YYSYMBOL_ELSE = 26,                      /* ELSE  */
  YYSYMBOL_YYACCEPT = 27,                  /* $accept  */
  YYSYMBOL_program = 28,                   /* program  */
  YYSYMBOL_29_1 = 29,                      /* $@1  */
  YYSYMBOL_declarations = 30,              /* declarations  */
  YYSYMBOL_31_2 = 31,                      /* $@2  */
  YYSYMBOL_32_3 = 32,                      /* $@3  */
  YYSYMBOL_identifier_list = 33,           /* identifier_list  */
  YYSYMBOL_asig = 34,                      /* asig  */
  YYSYMBOL_statement_list = 35,            /* statement_list  */
  YYSYMBOL_posicionES_get = 36,            /* posicionES_get  */
  YYSYMBOL_statement = 37,                 /* statement  */
  YYSYMBOL_38_4 = 38,                      /* $@4  */
  YYSYMBOL_39_5 = 39,                      /* $@5  */
  YYSYMBOL_40_6 = 40,                      /* $@6  */
  YYSYMBOL_print_list = 41,                /* print_list  */
  YYSYMBOL_print_item = 42,                /* print_item  */
  YYSYMBOL_read_list = 43,                 /* read_list  */
  YYSYMBOL_expression = 44                 /* expression  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
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
#define YYLAST   91

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  27
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  18
/* YYNRULES -- Number of rules.  */
#define YYNRULES  39
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  79

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   281


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      25,    26
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   106,   106,   106,   111,   111,   112,   112,   113,   116,
     117,   120,   130,   159,   160,   163,   166,   192,   194,   194,
     281,   334,   334,   334,   400,   401,   404,   405,   408,   441,
     487,   528,   572,   592,   612,   632,   652,   657,   670,   686
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "VOID", "PRINT",
  "READ", "VAR", "CONST", "IF", "WHILE", "LLAVEI", "LLAVED", "PARENI",
  "PAREND", "PUNTCOM", "COMMA", "ASSIGNOP", "STRING", "INT", "ID",
  "PLUSOP", "MINUSOP", "MULTOP", "DIVOP", "UMENOS", "NOELSE", "ELSE",
  "$accept", "program", "$@1", "declarations", "$@2", "$@3",
  "identifier_list", "asig", "statement_list", "posicionES_get",
  "statement", "$@4", "$@5", "$@6", "print_list", "print_item",
  "read_list", "expression", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281
};
#endif

#define YYPACT_NINF (-63)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -63,     3,    14,   -63,     9,    25,    29,    38,   -63,    63,
     -63,   -63,    -3,    31,    31,    35,    44,    65,    70,   -63,
     -63,    67,   -63,    68,    57,   -63,    59,    43,   -63,   -63,
     -63,    43,    61,   -63,    45,   -63,    64,    43,   -63,    22,
      43,    43,   -63,    31,   -63,    -2,   -63,   -63,    35,    43,
      43,    43,    43,   -63,    66,    45,    43,   -63,    37,    45,
     -63,   -63,   -63,    58,    58,   -63,   -63,   -63,    73,    23,
     -63,    30,   -63,    62,    30,   -63,   -63,    30,   -63
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     0,     1,     0,     0,     0,     0,     8,    14,
       4,     6,     0,     0,     0,     0,     0,     0,     0,    14,
       3,     0,    13,    11,     0,     9,     0,     0,    29,    39,
      38,     0,     0,    26,    28,    30,     0,     0,    21,     0,
       0,     0,     5,     0,     7,     0,    37,    24,     0,     0,
       0,     0,     0,    25,     0,    15,     0,    17,     0,    12,
      10,    36,    27,    32,    33,    34,    35,    31,     0,     0,
      16,     0,    22,    20,     0,    18,    23,     0,    19
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -63,   -63,   -63,   -63,   -63,   -63,    75,    47,    72,   -63,
     -62,   -63,   -63,   -63,   -63,    39,   -63,   -27
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,     9,    13,    14,    24,    25,    12,    68,
      22,    77,    56,    74,    32,    33,    36,    34
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      45,    15,    16,     3,    46,    17,    18,    19,    20,    73,
      55,    61,    76,    58,    59,    78,    21,     4,    49,    50,
      51,    52,    63,    64,    65,    66,    15,    16,     5,    69,
      17,    18,    19,    57,    15,    16,    72,     6,    17,    18,
      19,    21,     7,    49,    50,    51,    52,    27,     8,    21,
      23,    70,    28,    29,    30,    27,    31,    49,    50,    51,
      52,    29,    30,    35,    31,    49,    50,    51,    52,    10,
      11,    42,    43,    44,    43,    47,    48,    37,    53,    54,
      51,    52,    38,    40,    41,    67,    71,    62,    75,    26,
      60,    39
};

static const yytype_int8 yycheck[] =
{
      27,     4,     5,     0,    31,     8,     9,    10,    11,    71,
      37,    13,    74,    40,    41,    77,    19,     3,    20,    21,
      22,    23,    49,    50,    51,    52,     4,     5,    19,    56,
       8,     9,    10,    11,     4,     5,    13,    12,     8,     9,
      10,    19,    13,    20,    21,    22,    23,    12,    10,    19,
      19,    14,    17,    18,    19,    12,    21,    20,    21,    22,
      23,    18,    19,    19,    21,    20,    21,    22,    23,     6,
       7,    14,    15,    14,    15,    14,    15,    12,    14,    15,
      22,    23,    12,    16,    16,    19,    13,    48,    26,    14,
      43,    19
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    28,    29,     0,     3,    19,    12,    13,    10,    30,
       6,     7,    35,    31,    32,     4,     5,     8,     9,    10,
      11,    19,    37,    19,    33,    34,    33,    12,    17,    18,
      19,    21,    41,    42,    44,    19,    43,    12,    12,    35,
      16,    16,    14,    15,    14,    44,    44,    14,    15,    20,
      21,    22,    23,    14,    15,    44,    39,    11,    44,    44,
      34,    13,    42,    44,    44,    44,    44,    19,    36,    44,
      14,    13,    13,    37,    40,    26,    37,    38,    37
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    27,    29,    28,    31,    30,    32,    30,    30,    33,
      33,    34,    34,    35,    35,    36,    37,    37,    38,    37,
      37,    39,    40,    37,    37,    37,    41,    41,    42,    42,
      43,    43,    44,    44,    44,    44,    44,    44,    44,    44
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     9,     0,     5,     0,     5,     0,     1,
       3,     1,     3,     2,     0,     0,     4,     3,     0,     9,
       6,     0,     0,     7,     3,     3,     1,     3,     1,     1,
       1,     3,     3,     3,     3,     3,     3,     2,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
  case 2: /* $@1: %empty  */
#line 106 "minic.y"
                        {tablaSimbolos=creaLS(); tablaCodigo = creaLC();}
#line 1227 "minic.tab.c"
    break;

  case 3: /* program: $@1 VOID ID PARENI PAREND LLAVEI declarations statement_list LLAVED  */
#line 106 "minic.y"
                                                                                                                                                {imprimirTablaS(); imprimirTablaC(); liberaLS(tablaSimbolos); liberaLC(tablaCodigo); liberaLC((yyvsp[-2].codigo)); liberaLC((yyvsp[-1].codigo));}
#line 1233 "minic.tab.c"
    break;

  case 4: /* $@2: %empty  */
#line 111 "minic.y"
                                                 {tipo = VARIABLE;}
#line 1239 "minic.tab.c"
    break;

  case 5: /* declarations: declarations VAR $@2 identifier_list PUNTCOM  */
#line 111 "minic.y"
                                                                                            {(yyval.codigo) = (yyvsp[-4].codigo); concatenaLC((yyval.codigo),(yyvsp[-1].codigo)); liberaLC((yyvsp[-1].codigo));}
#line 1245 "minic.tab.c"
    break;

  case 6: /* $@3: %empty  */
#line 112 "minic.y"
                                                     {tipo = CONSTANTE;}
#line 1251 "minic.tab.c"
    break;

  case 7: /* declarations: declarations CONST $@3 identifier_list PUNTCOM  */
#line 112 "minic.y"
                                                                                                 {(yyval.codigo) = (yyvsp[-4].codigo); concatenaLC((yyval.codigo),(yyvsp[-1].codigo)); liberaLC((yyvsp[-1].codigo));}
#line 1257 "minic.tab.c"
    break;

  case 8: /* declarations: %empty  */
#line 113 "minic.y"
                                  {ListaC ListaVacia = creaLC(); (yyval.codigo) = ListaVacia;}
#line 1263 "minic.tab.c"
    break;

  case 9: /* identifier_list: asig  */
#line 116 "minic.y"
                                     {(yyval.codigo) = (yyvsp[0].codigo);}
#line 1269 "minic.tab.c"
    break;

  case 10: /* identifier_list: identifier_list COMMA asig  */
#line 117 "minic.y"
                                                             {(yyval.codigo) = (yyvsp[-2].codigo); concatenaLC((yyval.codigo),(yyvsp[0].codigo)); liberaLC((yyvsp[0].codigo));}
#line 1275 "minic.tab.c"
    break;

  case 11: /* asig: ID  */
#line 120 "minic.y"
                                   {
						// Comprobamos si no esta en la tabla se anyade
						if (!(perteneceTablaS((yyvsp[0].cadena)))) {
							anyadeEntrada((yyvsp[0].cadena), tipo, null);
							ListaC ListaVacia = creaLC(); 
							(yyval.codigo) = ListaVacia;
						} else {
							printf("Error | Variable %s ya esta declarada \n",(yyvsp[0].cadena));
							}
						}
#line 1290 "minic.tab.c"
    break;

  case 12: /* asig: ID ASSIGNOP expression  */
#line 130 "minic.y"
                                                         {
										// Comprobamos si no esta en la tabla se anyade
										if (!(perteneceTablaS((yyvsp[-2].cadena)))) {
											//Lo anyadimos a la tabla de Simbolos
											anyadeEntrada((yyvsp[-2].cadena), tipo, null);
											(yyval.codigo) = creaLC();
											
											// Creamos la concatenacion (ejemplo _$1)
											char temporal[32];
											sprintf(temporal,"_%s",(yyvsp[-2].cadena));

											Operacion oper;
											oper.op = "\tsw";
											oper.res = recuperaResLC((yyvsp[0].codigo));
											oper.arg1 = strdup(temporal);
											oper.arg2 = NULL;
											insertaLC((yyval.codigo),finalLC((yyval.codigo)),oper);
											insertaLC(tablaCodigo,finalLC(tablaCodigo),oper);
											guardaResLC((yyval.codigo),oper.res);
											liberaLC((yyvsp[0].codigo));

											} else {
												printf("Error | Variable %s ya esta declarada \n",(yyvsp[-2].cadena));
												}
											}
#line 1320 "minic.tab.c"
    break;

  case 13: /* statement_list: statement_list statement  */
#line 159 "minic.y"
                                                 {(yyval.codigo) = (yyvsp[-1].codigo); concatenaLC((yyval.codigo),(yyvsp[0].codigo)); liberaLC((yyvsp[0].codigo));}
#line 1326 "minic.tab.c"
    break;

  case 14: /* statement_list: %empty  */
#line 160 "minic.y"
                                  {ListaC ListaVacia = creaLC(); (yyval.codigo) = ListaVacia;}
#line 1332 "minic.tab.c"
    break;

  case 15: /* posicionES_get: %empty  */
#line 163 "minic.y"
                {posicionES = finalLC(tablaCodigo);}
#line 1338 "minic.tab.c"
    break;

  case 16: /* statement: ID ASSIGNOP expression PUNTCOM  */
#line 166 "minic.y"
                                                               {
													// Comprobamos el ID si esta declarado y si no es constante
													if (!(perteneceTablaS((yyvsp[-3].cadena))))
															printf("Error | Variable %s no declarada\n",(yyvsp[-3].cadena));
														else if (esConstante((yyvsp[-3].cadena))) 
															printf("Error | Asignacion a constante\n");
															else {
																(yyval.codigo) = creaLC();

																// Creamos la concatenacion (ejemplo _$1)
																char temporal[32];
																sprintf(temporal,"_%s",(yyvsp[-3].cadena));

																Operacion oper;
																oper.op = "\tsw";
																oper.res = recuperaResLC((yyvsp[-1].codigo));
																oper.arg1 = strdup(temporal);
																oper.arg2 = NULL;
																insertaLC((yyval.codigo),finalLC((yyval.codigo)),oper);
																insertaLC(tablaCodigo,finalLC(tablaCodigo),oper);
																guardaResLC((yyval.codigo),oper.res);
																
																//Libreamos 
																liberaLC((yyvsp[-1].codigo));
															}}
#line 1368 "minic.tab.c"
    break;

  case 17: /* statement: LLAVEI statement_list LLAVED  */
#line 192 "minic.y"
                                                               {(yyval.codigo) = (yyvsp[-1].codigo);}
#line 1374 "minic.tab.c"
    break;

  case 18: /* $@4: %empty  */
#line 194 "minic.y"
                                                                                            {pila++;arrayPila[pila] = finalLC(tablaCodigo);}
#line 1380 "minic.tab.c"
    break;

  case 19: /* statement: IF PARENI expression posicionES_get PAREND statement ELSE $@4 statement  */
#line 194 "minic.y"
                                                                                                                                                       {
																		
																		(yyval.codigo) = (yyvsp[-6].codigo);

																		// Creamos la etiqueta (ejemplo $l1)
																		char temporal[32];
																		sprintf(temporal,"$l%d",contadorEtiquetas);

																		// Contamos cuantas instrucciones tiene el primer statemt para despues 
																		// retroceder esa cantidad (contadorS) e insertar "beqz" correctamente
																		int contadorS = 0;

																		//		intruccionces de statement 
																		PosicionListaC p = inicioLC((yyvsp[-3].codigo));
																		while (p != finalLC((yyvsp[-3].codigo))) {
																			contadorS++;
																			p = siguienteLC((yyvsp[-3].codigo),p);
																		}

																		// Guardamos en b la posicion que tenmos actualmente en nuestro arrayPila
																		// para retroceder contadorS y modificar esa poscion b
																		// PosicionListaC b = arrayPila[pila];
																		// for(int i = 0; i < contadorS; i++){
																		// 	b = anteriorLC(tablaCodigo,b);
																		// }

																		Operacion oper;
																		oper.op = "\tbeqz";
																		oper.res = recuperaResLC((yyvsp[-6].codigo));
																		oper.arg1 = strdup(temporal);
																		oper.arg2 = NULL;

																		insertaLC(tablaCodigo,posicionES,oper);

																		concatenaLC((yyval.codigo),(yyvsp[-3].codigo));
																		liberaLC((yyvsp[-3].codigo));
																		contadorEtiquetas++;

																		// Creamos la etiqueta (ejemplo $l1)
																		char temporal2[32];
																		sprintf(temporal2,"$l%d",contadorEtiquetas);
																		

																		Operacion oper2;
																		oper2.op = "\tb";
																		oper2.res = strdup(temporal2);
																		oper2.arg1 = NULL;
																		oper2.arg2 = NULL;
																		
																		PosicionListaC media = arrayPila[pila];
																		insertaLC(tablaCodigo,media,oper2);
																		pila--;

																		guardaResLC((yyval.codigo),oper2.res);
																		
																		//Modificamos la etiqueta para que tenga los dos puntos, por ejemplo "dolar l1":
																		char *aux1 = strdup(temporal);
																		char etiqueta[32];
																		sprintf(etiqueta,"%s:",aux1);
																		
																		Operacion oper3;
																		oper3.op = strdup(etiqueta);
																		oper3.res = NULL;
																		oper3.arg1 = NULL;
																		oper3.arg2 = NULL;
																		insertaLC(tablaCodigo,siguienteLC(tablaCodigo,media),oper3);
																		guardaResLC((yyval.codigo),oper3.res);

																		concatenaLC((yyval.codigo),(yyvsp[0].codigo));
																		liberaLC((yyvsp[0].codigo));

																		//Modificamos la etiqueta para que tenga los dos puntos, por ejemplo "dolar l1":
																		char *aux2 = strdup(temporal2);
																		char etiqueta2[32];
																		sprintf(etiqueta2,"%s:",aux2);

																		Operacion oper4;
																		oper4.op = strdup(etiqueta2);
																		oper4.res = NULL;
																		oper4.arg1 = NULL;
																		oper4.arg2 = NULL;

																		insertaLC(tablaCodigo,finalLC(tablaCodigo),oper4);
																		guardaResLC((yyval.codigo),oper4.res);

																		contadorEtiquetas++;
																		}
#line 1472 "minic.tab.c"
    break;

  case 20: /* statement: IF PARENI expression posicionES_get PAREND statement  */
#line 281 "minic.y"
                                                                                                    {
														(yyval.codigo) = (yyvsp[-3].codigo);

														// Contamos cuantas instrucciones tiene el primer statemt para despues 
														// retroceder esa cantidad (contadorS) e insertar "beqz" correctamente
														int contadorS = 0;

														PosicionListaC p = inicioLC((yyvsp[0].codigo));
														while (p != finalLC((yyvsp[0].codigo))) {
															contadorS++;
															p = siguienteLC((yyvsp[0].codigo),p);
														}

														// En este caso le asignamos a b el final de tablaCodigo porque no tenemos else
														// PosicionListaC b = finalLC(tablaCodigo);
														// for(int i = 0; i < contadorS; i++){
														// 	b = anteriorLC(tablaCodigo,b);
														// }

														// Creamos la etiqueta (ejemplo $l1)
														char temporal[32];
														sprintf(temporal,"$l%d",contadorEtiquetas);

														Operacion oper;
														oper.op = "\tbeqz";
														oper.res = recuperaResLC((yyvsp[-3].codigo));
														oper.arg1 = strdup(temporal);
														oper.arg2 = NULL;

														insertaLC(tablaCodigo,posicionES,oper);
														guardaResLC((yyval.codigo),oper.res);

														concatenaLC((yyval.codigo),(yyvsp[0].codigo));

														liberaLC((yyvsp[0].codigo));

														//Modificamos la etiqueta para que tenga los dos puntos, por ejemplo "dolar l1":
														char *aux1 = strdup(temporal);
														char etiqueta[32];
														sprintf(etiqueta,"%s:",aux1);
														
														Operacion etiq;
														etiq.op = strdup(etiqueta);
														etiq.res = NULL;
														etiq.arg1 = NULL;
														etiq.arg2 = NULL;


														insertaLC(tablaCodigo,finalLC(tablaCodigo),etiq);
														guardaResLC((yyval.codigo),etiq.res);

														contadorEtiquetas++;
														}
#line 1530 "minic.tab.c"
    break;

  case 21: /* $@5: %empty  */
#line 334 "minic.y"
                                               {posicionES = finalLC(tablaCodigo);}
#line 1536 "minic.tab.c"
    break;

  case 22: /* $@6: %empty  */
#line 334 "minic.y"
                                                                                                      {posicionST = finalLC(tablaCodigo); }
#line 1542 "minic.tab.c"
    break;

  case 23: /* statement: WHILE PARENI $@5 expression PAREND $@6 statement  */
#line 334 "minic.y"
                                                                                                                                                      {
															
															// Creamos la etiqueta (ejemplo $l1)
															char temporal[32];
															sprintf(temporal,"$l%d",contadorEtiquetas);

															//Modificamos la etiqueta para que tenga los dos puntos, por ejemplo "dolar l1":
															char *aux1 = strdup(temporal);
															char etiqueta[32];
															sprintf(etiqueta,"%s:",aux1);
															
															
															Operacion oper;
															oper.op = strdup(etiqueta);
															oper.res = NULL;
															oper.arg1 = NULL;
															oper.arg2 = NULL;
															insertaLC((yyvsp[-3].codigo),inicioLC((yyvsp[-3].codigo)),oper);

															insertaLC(tablaCodigo,posicionES,oper);
															
															(yyval.codigo) = (yyvsp[-3].codigo);			

															contadorEtiquetas++;

															// Creamos la etiqueta (ejemplo $l1)
															char temporal2[32];
															sprintf(temporal2,"$l%d",contadorEtiquetas);

															//Modificamos la etiqueta para que tenga los dos puntos, por ejemplo "dolar l1":
															char *aux2 = strdup(temporal2);
															char etiqueta2[32];
															sprintf(etiqueta2,"%s:",aux2);
															
															Operacion oper2;
															oper2.op = "\tbeqz";
															oper2.res = recuperaResLC((yyvsp[-3].codigo));
															oper2.arg1 = strdup(temporal2);
															oper2.arg2 = NULL;

															insertaLC(tablaCodigo,posicionST,oper2);
															guardaResLC((yyval.codigo),oper2.res);

															concatenaLC((yyval.codigo),(yyvsp[0].codigo));
															liberaLC((yyvsp[0].codigo));

															Operacion oper3;
															oper3.op = "\tb";
															oper3.res = strdup(temporal);
															oper3.arg1 = NULL;
															oper3.arg2 = NULL;
															
															insertaLC(tablaCodigo,finalLC(tablaCodigo),oper3);
															guardaResLC((yyval.codigo),oper3.res);

															Operacion oper4;
															oper4.op = strdup(etiqueta2);
															oper4.res = NULL;
															oper4.arg1 = NULL;
															oper4.arg2 = NULL;

															insertaLC(tablaCodigo,finalLC(tablaCodigo),oper4);
															guardaResLC((yyval.codigo),oper4.res);

															contadorEtiquetas++;
														}
#line 1613 "minic.tab.c"
    break;

  case 24: /* statement: PRINT print_list PUNTCOM  */
#line 400 "minic.y"
                                                           {(yyval.codigo) = (yyvsp[-1].codigo);}
#line 1619 "minic.tab.c"
    break;

  case 25: /* statement: READ read_list PUNTCOM  */
#line 401 "minic.y"
                                                         { (yyval.codigo) = (yyvsp[-1].codigo);}
#line 1625 "minic.tab.c"
    break;

  case 26: /* print_list: print_item  */
#line 404 "minic.y"
                                           {(yyval.codigo) = (yyvsp[0].codigo);}
#line 1631 "minic.tab.c"
    break;

  case 27: /* print_list: print_list COMMA print_item  */
#line 405 "minic.y"
                                                              {(yyval.codigo) = (yyvsp[-2].codigo); concatenaLC((yyval.codigo),(yyvsp[0].codigo)); liberaLC((yyvsp[0].codigo));}
#line 1637 "minic.tab.c"
    break;

  case 28: /* print_item: expression  */
#line 408 "minic.y"
                                           {

								(yyval.codigo) = (yyvsp[0].codigo);
								

								Operacion op1;
								op1.op = "\tmove";
								op1.res = "$a0";
								op1.arg1 = recuperaResLC((yyvsp[0].codigo));
								op1.arg2 = NULL;

								insertaLC(tablaCodigo,finalLC(tablaCodigo),op1);
								guardaResLC((yyval.codigo),op1.res);
								
								Operacion op2;
								op2.op = "\tli";
								op2.res = "$v0";
								op2.arg1 = "1";
								op2.arg2 = NULL;

								insertaLC(tablaCodigo,finalLC(tablaCodigo),op2);
								guardaResLC((yyval.codigo),op2.res);

								Operacion op3;
								op3.op = "\t\tsyscall";
								op3.res =  NULL;
								op3.arg1 = NULL;
								op3.arg2 = NULL;

								insertaLC(tablaCodigo,finalLC(tablaCodigo),op3);

								guardaResLC((yyval.codigo),op3.res);
								}
#line 1675 "minic.tab.c"
    break;

  case 29: /* print_item: STRING  */
#line 441 "minic.y"
                                         {
						// Anyadimos a la tabla la cadena e incrementamos el contador
						anyadeEntrada((yyvsp[0].cadena),CADENA, contadorCadenas); 


						(yyval.codigo) = creaLC();
						
						// Creamos la etiqueta (ejemplo $str1)
						char temporal[32];
						sprintf(temporal,"$str%d",contadorCadenas);

						Operacion op1;
						op1.op = "\n\tla";
						op1.res = "$a0";
						op1.arg1 = strdup(temporal);
						op1.arg2 = NULL;

						insertaLC((yyval.codigo),finalLC((yyval.codigo)),op1);
						insertaLC(tablaCodigo,finalLC(tablaCodigo),op1);
						guardaResLC((yyval.codigo),op1.res);

						Operacion op2;
						op2.op = "\tli";
						op2.res = "$v0";
						op2.arg1 = "4";
						op2.arg2 = NULL;

						insertaLC((yyval.codigo),finalLC((yyval.codigo)),op2);
						insertaLC(tablaCodigo,finalLC(tablaCodigo),op2);
						guardaResLC((yyval.codigo),op2.res);

						Operacion op3;
						op3.op = "\t\tsyscall";
						op3.res =  NULL;
						op3.arg1 = NULL;
						op3.arg2 = NULL;

						insertaLC((yyval.codigo),finalLC((yyval.codigo)),op3);
						insertaLC(tablaCodigo,finalLC(tablaCodigo),op3);

						guardaResLC((yyval.codigo),op3.res);

						contadorCadenas++;
				}
#line 1724 "minic.tab.c"
    break;

  case 30: /* read_list: ID  */
#line 487 "minic.y"
                                   {
						// Comprobamos el ID si esta declarado y si no es constante
						if (!(perteneceTablaS((yyvsp[0].cadena))))
								printf("Error | Variable %s no declarada\n",(yyvsp[0].cadena));
							else if (esConstante((yyvsp[0].cadena))) 
								printf("Error | Asignacion a constante\n");
								else {
									(yyval.codigo) = creaLC();
									
									// Creamos la concatenacion (ejemplo _$1)
									char temporal[32];
									sprintf(temporal,"_%s",(yyvsp[0].cadena));

									Operacion op1;
									op1.op = "\n\tli";
									op1.res = "$v0";
									op1.arg1 = "5";
									op1.arg2 = NULL;

									insertaLC(tablaCodigo,finalLC(tablaCodigo),op1);
									guardaResLC((yyval.codigo),op1.res);

									Operacion op2;
									op2.op = "\t\tsyscall";
									op2.res =  NULL;
									op2.arg1 = NULL;
									op2.arg2 = NULL;

									insertaLC(tablaCodigo,finalLC(tablaCodigo),op2);
									guardaResLC((yyval.codigo),op2.res);

									Operacion op3;
									op3.op = "\tsw";
									op3.res = "$v0";
									op3.arg1 = strdup(temporal);
									op3.arg2 = NULL;

									insertaLC(tablaCodigo,finalLC(tablaCodigo),op3);
									guardaResLC((yyval.codigo),op3.res);
								}
								}
#line 1770 "minic.tab.c"
    break;

  case 31: /* read_list: read_list COMMA ID  */
#line 528 "minic.y"
                                                     {
									// Comprobamos el ID si esta declarado y si no es constante
									if (!(perteneceTablaS((yyvsp[0].cadena))))
											printf("Error | Variable %s no declarada\n",(yyvsp[0].cadena));
										else if (esConstante((yyvsp[0].cadena))) 
											printf("Error | Asignacion a constante\n");
											else {

												// Creamos la concatenacion (ejemplo _$1)
												char temporal[32];
												sprintf(temporal,"_%s",(yyvsp[0].cadena));

												Operacion op1;
												op1.op = "\n\tli";
												op1.res = "$v0";
												op1.arg1 = "5";
												op1.arg2 = NULL;

												insertaLC((yyval.codigo),finalLC((yyval.codigo)),op1);
												insertaLC(tablaCodigo,finalLC(tablaCodigo),op1);
												guardaResLC((yyval.codigo),op1.res);

												Operacion op2;
												op2.op = "\t\tsyscall";
												op2.res =  NULL;
												op2.arg1 = NULL;
												op2.arg2 = NULL;

												insertaLC((yyval.codigo),finalLC((yyval.codigo)),op2);
												insertaLC(tablaCodigo,finalLC(tablaCodigo),op2);
												guardaResLC((yyval.codigo),op2.res);

												Operacion op3;
												op3.op = "\tsw";
												op3.res = "$v0";
												op3.arg1 = strdup(temporal);
												op3.arg2 = NULL;

												insertaLC((yyval.codigo),finalLC((yyval.codigo)),op3);
												insertaLC(tablaCodigo,finalLC(tablaCodigo),op3);
												guardaResLC((yyval.codigo),op3.res);
											}
											}
#line 1818 "minic.tab.c"
    break;

  case 32: /* expression: expression PLUSOP expression  */
#line 572 "minic.y"
                                                             {
												(yyval.codigo) = (yyvsp[-2].codigo);
												concatenaLC((yyval.codigo),(yyvsp[0].codigo));
												
												Operacion oper;
												oper.op = "\tadd";
												oper.res = recuperaResLC((yyvsp[-2].codigo));
												oper.arg1 = recuperaResLC((yyvsp[-2].codigo));
												oper.arg2 = recuperaResLC((yyvsp[0].codigo));

												insertaLC(tablaCodigo,finalLC(tablaCodigo),oper);
												guardaResLC((yyval.codigo),oper.res);
												liberarRegistro(oper.arg1);
												liberarRegistro(oper.arg2);

												// Liberamos la expresion que concatenamos,
												// debido a que cuando conctatenamos, conctenaLC(a,b)
												// se hace una copia de b en a, y podemos liberar b
												liberaLC((yyvsp[0].codigo));
												}
#line 1843 "minic.tab.c"
    break;

  case 33: /* expression: expression MINUSOP expression  */
#line 592 "minic.y"
                                                                {
												(yyval.codigo) = (yyvsp[-2].codigo);
												concatenaLC((yyval.codigo),(yyvsp[0].codigo));
												
												Operacion oper;
												oper.op = "\tsub";
												oper.res = recuperaResLC((yyvsp[-2].codigo));
												oper.arg1 = recuperaResLC((yyvsp[-2].codigo));
												oper.arg2 = recuperaResLC((yyvsp[0].codigo));

												insertaLC(tablaCodigo,finalLC(tablaCodigo),oper);
												guardaResLC((yyval.codigo),oper.res);
												liberarRegistro(oper.arg1);
												liberarRegistro(oper.arg2);

												// Liberamos la expresion que concatenamos,
												// debido a que cuando conctatenamos, conctenaLC(a,b)
												// se hace una copia de b en a, y podemos liberar b
												liberaLC((yyvsp[0].codigo));
												}
#line 1868 "minic.tab.c"
    break;

  case 34: /* expression: expression MULTOP expression  */
#line 612 "minic.y"
                                                               {
												(yyval.codigo) = (yyvsp[-2].codigo);
												concatenaLC((yyval.codigo),(yyvsp[0].codigo));
												
												Operacion oper;
												oper.op = "\tmul";
												oper.res = recuperaResLC((yyvsp[-2].codigo));
												oper.arg1 = recuperaResLC((yyvsp[-2].codigo));
												oper.arg2 = recuperaResLC((yyvsp[0].codigo));

												insertaLC(tablaCodigo,finalLC(tablaCodigo),oper);
												guardaResLC((yyval.codigo),oper.res);
												liberarRegistro(oper.arg1);
												liberarRegistro(oper.arg2);

												// Liberamos la expresion que concatenamos,
												// debido a que cuando conctatenamos, conctenaLC(a,b)
												// se hace una copia de b en a, y podemos liberar b
												liberaLC((yyvsp[0].codigo));
												}
#line 1893 "minic.tab.c"
    break;

  case 35: /* expression: expression DIVOP expression  */
#line 632 "minic.y"
                                                              {
												(yyval.codigo) = (yyvsp[-2].codigo);
												concatenaLC((yyval.codigo),(yyvsp[0].codigo));
												
												Operacion oper;
												oper.op = "\tdiv";
												oper.res = recuperaResLC((yyvsp[-2].codigo));
												oper.arg1 = recuperaResLC((yyvsp[-2].codigo));
												oper.arg2 = recuperaResLC((yyvsp[0].codigo));

												insertaLC(tablaCodigo,finalLC(tablaCodigo),oper);
												guardaResLC((yyval.codigo),oper.res);
												liberarRegistro(oper.arg1);
												liberarRegistro(oper.arg2);

												// Liberamos la expresion que concatenamos,
												// debido a que cuando conctatenamos, conctenaLC(a,b)
												// se hace una copia de b en a, y podemos liberar b
												liberaLC((yyvsp[0].codigo));
												}
#line 1918 "minic.tab.c"
    break;

  case 36: /* expression: PARENI expression PAREND  */
#line 652 "minic.y"
                                                           {
											// La expresion ya esta creada no hace falta anyadir nada, debido a que los parentesis no modifican nada,
											// solo que esta en otra posicion
											(yyval.codigo) = (yyvsp[-1].codigo);
											}
#line 1928 "minic.tab.c"
    break;

  case 37: /* expression: MINUSOP expression  */
#line 657 "minic.y"
                                                                  {
													(yyval.codigo) = (yyvsp[0].codigo);

													// Tendriamos que hacer la negacion
													Operacion oper;
													oper.op = "\tneg";
													oper.res = recuperaResLC((yyvsp[0].codigo));
													oper.arg1 = recuperaResLC((yyvsp[0].codigo));
													oper.arg2 = NULL;

													insertaLC(tablaCodigo,finalLC(tablaCodigo),oper);
													guardaResLC((yyval.codigo),oper.res);
													}
#line 1946 "minic.tab.c"
    break;

  case 38: /* expression: ID  */
#line 670 "minic.y"
                                      {
					// Comprobamos si el ID esta declarado o no, no nos importa su tipo
					if (!(perteneceTablaS((yyvsp[0].cadena)))) {
						printf("Error | Variable %s no declarada\n",(yyvsp[0].cadena));
					} else {
						(yyval.codigo) = creaLC();
						Operacion oper;
						oper.op = "\n\tlw";
						oper.res = obtenerRegistro();
						oper.arg1 = concatenar((yyvsp[0].cadena));
						oper.arg2 = NULL;

						insertaLC(tablaCodigo,finalLC(tablaCodigo),oper);

						guardaResLC((yyval.codigo),oper.res);
					}}
#line 1967 "minic.tab.c"
    break;

  case 39: /* expression: INT  */
#line 686 "minic.y"
                                      {
						(yyval.codigo) = creaLC();
						Operacion oper;
						oper.op = "\tli";
						oper.res = obtenerRegistro();
						oper.arg1 = (yyvsp[0].cadena);
						oper.arg2 = NULL;

						insertaLC(tablaCodigo,finalLC(tablaCodigo),oper);

						guardaResLC((yyval.codigo),oper.res);
						}
#line 1984 "minic.tab.c"
    break;


#line 1988 "minic.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

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


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 699 "minic.y"


void yyerror()
{	
	error = true;
	if (errorLEX == true){
		errorLEX = false;
	} else {		
		printf(ROJO_T "ERROR SINTAX:" RESET_COLOR " expresion situada en la linea %d erronea\n\n", yylineno );
		while (yylex() != EOF){
			yylex();
		}
	}
}

/* ======== FUNCIONES EXTRA A LA LISTA DE SIMBOLOS ========= */
bool perteneceTablaS(char *lexema){
	/* Buscamos si esta el lexema, si no he llegado al final
		de la lista, significa que lo hemos encontrado por lo tanto true
		en caso contrario false  */

	PosicionLista pos = buscaLS(tablaSimbolos,lexema);
	if (pos != finalLS(tablaSimbolos)) {
		return true;
	} else {
		return false;
	}
}

void anyadeEntrada(char *lexema, Tipo tipo, int valorContenido){
	/* Recibe el lexema, con el tipo. 
		Creas el simbolo con el lexema y el tipo
		Y lo anyade a la lista */

	Simbolo aux;
	aux.nombre = lexema;
	aux.tipo = tipo;
	aux.valor = valorContenido;
	insertaLS(tablaSimbolos,finalLS(tablaSimbolos),aux);
}

bool esConstante(char *lexema){
	// Eso basicameente depende si el codigo ha visto el token VAR o CONST
	/* si tipo es == CONSTANTE entonces true
		en otro caso false */

	PosicionLista pos = buscaLS(tablaSimbolos,lexema);
	if(pos != finalLS(tablaSimbolos)){
		Simbolo aux = recuperaLS(tablaSimbolos,pos);

		if (aux.tipo == CONSTANTE){
			return true;
		} else {
			return false;
		}
	} else {
		/* No esta en la tabla, debido a que la posicion es igual que la final */
		return false;
	}
}
 
void imprimirTablaS() {
	if (!error) {
		/* Imprimimos la tabla */
		printf("############################\n");
		printf(".data\n");

		Lista listaID = creaLS(); // lista de ID (variables o constantes)
		Lista listaCAD = creaLS(); // lista de ID (cadenas)

		PosicionLista p = inicioLS(tablaSimbolos);
		PosicionLista final = finalLS(tablaSimbolos);

		/* Recorremos la lista de simbolos principal y en funcion de tipo lo asignamos a una de las listas locales */
		while(p != final) {
			Simbolo aux = recuperaLS(tablaSimbolos,p);

			/* En caso de ser 
				variable o constante - > "_nombreVariable"
				cadena -> "$strNumero" */
			switch(aux.tipo){
				case VARIABLE:
					insertaLS(listaID,finalLS(listaID),aux);
					break;
				case CONSTANTE: 
					insertaLS(listaID,finalLS(listaID),aux);
					break;
				case CADENA:
					insertaLS(listaCAD,finalLS(listaCAD),aux);
					break;
				default:
					break;
			}

			p = siguienteLS(tablaSimbolos,p);
		}

		/*  Despues de guardar en las listas segun el simbolo procedemos a imprimirlas */
		/* LA FINALIDAD DE ESTO ES QUE SE MUESTRE PRIMERO LOS STRINGS Y DESPUES LOS IDENTIFIERS */

		/* MOSTRAMOS LOS STRINGS */
		printf("# STRINGS ##################\n");

		PosicionLista posCad = inicioLS(listaCAD);
		PosicionLista finalCad = finalLS(listaCAD);
		
		while(posCad != finalCad){
			Simbolo auxC = recuperaLS(listaCAD,posCad);
			printf("$str%d:	.asciiz %s\n",auxC.valor,auxC.nombre);

			posCad = siguienteLS(listaCAD,posCad);
		}
		printf("\n");

		/* MOSTRAMOS LOS IDENTIFIERS */
		printf("# IDENTIFIERS ##############\n");
		PosicionLista posID = inicioLS(listaID);
		PosicionLista finalID = finalLS(listaID);

		while(posID != finalID){
			Simbolo auxID = recuperaLS(listaID,posID);
			printf("_%s:	.word 0\n",auxID.nombre);

			posID = siguienteLS(listaID,posID);
		}
		
		/* Liberamos las listas locales creadas */
		liberaLS(listaID);
		liberaLS(listaCAD);

	}
}

/* ======== FUNCIONES EXTRA A LA LISTA DE CODIGO ========= */
char *obtenerRegistro(){
	//Nos devuelve el registro temporal libre para asignarlo en ese momento
	//Tenemos un array de 10 posiciones ($t0-$t9)
	//Iremos marcando mediante un bool esta en uso (1) o esta libre (0)
	//Y creamos metodos, por ejemplo, recorre el arry y la primera posicion que este libre, marcala
	//y asignala y devuelve la cadena de carcter "$t(numero de la poscion)"

	int posicion;
	for (int i = 0; i < MAX_REG; i++){
		if(registro[i] == 0) {
			posicion = i;
			// Significa que esta ocupado
			registro[i] = 1;
			break;
		}
	}

	char temporal[32];
	sprintf(temporal,"$t%d",posicion);
	return strdup(temporal);
	
}

void liberarRegistro(char *reg){
	//liberamos ese registro
	//Recorremos el arrayTempAux y si reg posicion 2, es dercir el numero
	// es igual al que tenemos en esa posicion del array
	// ponemos a cero esa posicion del registro

	for (int i = 0; i < MAX_REG; i++){
		if (arrayTempAux[i] == reg[2]){
			// Procedemos a liberar la posicion en el array de registros booleanos
			registro[i] = 0;
		}
	}
	
}

char *concatenar(char *nombre){
	//Metdod de conctatenacion entre dos strings
	//Debido a que nuuestros identificadores tienen un "guion bajo" mas el $1 
	//que seria el nombre de la variable

	char temporal[32];
	sprintf(temporal,"_%s",nombre);
	return strdup(temporal);

}

void imprimirTablaC(){
	if (!error){
		/* printf("\n#################\n"); */
		printf("\n# MAIN #####################\n");
		printf("\t.text\n");
		printf("\n\t.globl main\n\n");
		printf("main:\n");

		PosicionListaC p = inicioLC(tablaCodigo);
		while (p != finalLC(tablaCodigo)) {
			Operacion oper;
			oper = recuperaLC(tablaCodigo,p);
			printf("%s",oper.op);
			if (oper.res) printf("\t%s",oper.res);
			if (oper.arg1) printf(",%s",oper.arg1);
			if (oper.arg2) printf(",%s",oper.arg2);
			printf("\n");
			p = siguienteLC(tablaCodigo,p);
		}

		// instruccion escrita directamente, porque es el final del codigo
		printf("\n\tli \t$v0, 10\n");
		printf("\t\tsyscall\n");
	}

}
