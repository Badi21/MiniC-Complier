%{
#include <stdio.h>
#include<stdbool.h>
#include "minic.tab.h"
#include "listaSimbolos.h"
#include "listaCodigo.h"

#define VERDE_T        "\x1b[32m"
#define AMARILLO_T "\x1b[33m"
#define RESET_COLOR    "\x1b[0m"

int id_function();
int int_function();
int string_function();

void error_lexico();
void error_multi();
void mostrarCont();
void contador();
void compError();
void yyerror();

int inicioMulti;
int cont_error = 0;
bool errorLEX = false;

%}
digito              [0-9]
letra               [a-zA-Z]
entero              {digito}+
cadena		     	\"([^"]|\\\")*\"
coment_Line_good	([^*]|[*]+[^*/])*[*]*"*/"
coment_Line_bad		([^*]|[*]+[^*/])*[*]*

%x	COMMULTI

%option yylineno

%%
[ \n\t]+                                    								;
"//"(.*)[\n]                                								;

"/*"																		{BEGIN (COMMULTI); inicioMulti = yylineno;}
<COMMULTI>{coment_Line_good}												{BEGIN (0);}
<COMMULTI>{coment_Line_bad}													;
<COMMULTI><<EOF>>															{error_multi(); mostrarCont(); exit(1);}		

void                                       									return VOID;
print 																		return PRINT;
read																		return READ;
var																			return VAR;
const																		return CONST;
if																			return IF;
else																		return ELSE;
while                                      									return WHILE;
({letra}|_)({letra}|{digito}|_)*          									return id_function();
{entero}                                    								return int_function();

{cadena}																	return string_function();


"{"					     													return LLAVEI;
"}"																			return LLAVED;
"("                                         								return PARENI;		
")"                                         								return PAREND;
";"                                         								return PUNTCOM;
","                                         								return COMMA;
"="                                         								return ASSIGNOP;
"+"                                         								return PLUSOP;
"-"                                         								return MINUSOP;
"/"																			return DIVOP;
"*"																			return MULTOP;
[^A-Za-z0-9{}();,=+\-/*\s\n\t_ "]+                         					error_lexico();
<<EOF>>																		{compError(); exit(1);}
%%

void error_lexico(){
	printf(AMARILLO_T "ERROR LEX:" RESET_COLOR " caracteres no validos en linea %d : " VERDE_T" %s\n\n", yylineno, yytext);
	contador();
	errorLEX = true;
	yyerror();
}

void error_multi(){
	printf(AMARILLO_T "ERROR LEX:" RESET_COLOR " comentario no cerrado iniciado en linea %d\n\n", inicioMulti);
	contador();	
	errorLEX = true;
	yyerror();
}

int id_function(){
	if (yyleng > 16){
		printf(AMARILLO_T "ERROR LEX:" RESET_COLOR " identificador demasiado largo en linea %d : " VERDE_T " %s\n\n", yylineno, yytext);
		contador();
		errorLEX = true;
		yyerror();
		return ID;

	}else{
		yylval.cadena = strdup(yytext);
		return ID;
	}
}

int int_function(){
	if (atol(yytext) > 2147483648){
		printf(AMARILLO_T "ERROR LEX:" RESET_COLOR " entero demasiado grande en linea %d : " VERDE_T " %s\n\n", yylineno, yytext);
		contador();
		errorLEX = true;
		yyerror();
		return INT;

	}else{
		yylval.cadena = strdup(yytext);
		return INT;
	}
}

int string_function(){
	yylval.cadena = strdup(yytext); 
	return STRING;
}

void contador(){
	cont_error++;
}

void mostrarCont(){
	printf(RESET_COLOR"----------------------\n");
	printf(RESET_COLOR "Errores lexicos: %d\n", cont_error);
}

void compError(){
	if (cont_error > 0 ) mostrarCont();
}
