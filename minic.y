
%{
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
%}

%union{
       char *cadena;
	   ListaC codigo;
}

%code requires {
	#include "listaCodigo.h"
}

/* %expect 1 */

%token VOID PRINT READ VAR CONST IF WHILE LLAVEI LLAVED PARENI PAREND PUNTCOM COMMA ASSIGNOP
%token <cadena> STRING
%token <cadena> INT
%token <cadena> ID


%type <codigo> expression statement statement_list print_list print_item read_list declarations identifier_list asig


%left PLUSOP MINUSOP 
%left MULTOP DIVOP
%left UMENOS

/* Aqui le damos mas precedencia al Else mas que el NO else */
%precedence NOELSE
%precedence ELSE

%%

/* En program, creamos las dos tablas, y despues aparte de imprimirlas las liberamos*/


program: 		{tablaSimbolos=creaLS(); tablaCodigo = creaLC();}	VOID ID PARENI PAREND LLAVEI declarations statement_list LLAVED {imprimirTablaS(); imprimirTablaC(); liberaLS(tablaSimbolos); liberaLC(tablaCodigo); liberaLC($7); liberaLC($8);}
				;

/* BLOQUE DE DRECLARACIOENES */
/* ====================================================================================================== */
declarations:			declarations VAR {tipo = VARIABLE;} identifier_list PUNTCOM {$$ = $1; concatenaLC($$,$4); liberaLC($4);}
				| declarations CONST {tipo = CONSTANTE;} identifier_list PUNTCOM {$$ = $1; concatenaLC($$,$4); liberaLC($4);}
				| {ListaC ListaVacia = creaLC(); $$ = ListaVacia;}// empty
				;
				
identifier_list: 		asig {$$ = $1;}
				| identifier_list COMMA asig {$$ = $1; concatenaLC($$,$3); liberaLC($3);}
				;
				
asig:				ID {
						// Comprobamos si no esta en la tabla se anyade
						if (!(perteneceTablaS($1))) {
							anyadeEntrada($1, tipo, null);
							ListaC ListaVacia = creaLC(); 
							$$ = ListaVacia;
						} else {
							printf("Error | Variable %s ya esta declarada \n",$1);
							}
						}
				| ID ASSIGNOP expression {
										// Comprobamos si no esta en la tabla se anyade
										if (!(perteneceTablaS($1))) {
											//Lo anyadimos a la tabla de Simbolos
											anyadeEntrada($1, tipo, null);
											$$ = creaLC();
											
											// Creamos la concatenacion (ejemplo _$1)
											char temporal[32];
											sprintf(temporal,"_%s",$1);

											Operacion oper;
											oper.op = "\tsw";
											oper.res = recuperaResLC($3);
											oper.arg1 = strdup(temporal);
											oper.arg2 = NULL;
											insertaLC($$,finalLC($$),oper);
											insertaLC(tablaCodigo,finalLC(tablaCodigo),oper);
											guardaResLC($$,oper.res);
											liberaLC($3);

											} else {
												printf("Error | Variable %s ya esta declarada \n",$1);
												}
											}
				;

/* BLOQUE DE SENTENCIAS */
/* ==================================================================================================== */
statement_list:		statement_list statement {$$ = $1; concatenaLC($$,$2); liberaLC($2);}
				| {ListaC ListaVacia = creaLC(); $$ = ListaVacia;} //empty 
				;
			
posicionES_get: {posicionES = finalLC(tablaCodigo);}
				;

statement:			ID ASSIGNOP expression PUNTCOM {
													// Comprobamos el ID si esta declarado y si no es constante
													$$ = creaLC();
													if (!(perteneceTablaS($1)))
															printf("Error | Variable %s no declarada\n",$1);
														else if (esConstante($1)) 
															printf("Error | Asignacion a constante\n");
															else {

																// Creamos la concatenacion (ejemplo _$1)
																char temporal[32];
																sprintf(temporal,"_%s",$1);

																Operacion oper;
																oper.op = "\tsw";
																oper.res = recuperaResLC($3);
																oper.arg1 = strdup(temporal);
																oper.arg2 = NULL;
																insertaLC($$,finalLC($$),oper);
																insertaLC(tablaCodigo,finalLC(tablaCodigo),oper);
																guardaResLC($$,oper.res);
																
																//Libreamos 
																liberaLC($3);
															}}

				| LLAVEI statement_list LLAVED {$$ = $2;}
								
				| IF PARENI expression posicionES_get PAREND statement ELSE {pila++;arrayPila[pila] = finalLC(tablaCodigo);} statement {
																		
																		$$ = $3;

																		// Creamos la etiqueta (ejemplo $l1)
																		char temporal[32];
																		sprintf(temporal,"$l%d",contadorEtiquetas);

																		// Contamos cuantas instrucciones tiene el primer statemt para despues 
																		// retroceder esa cantidad (contadorS) e insertar "beqz" correctamente
																		int contadorS = 0;

																		//		intruccionces de statement 
																		PosicionListaC p = inicioLC($6);
																		while (p != finalLC($6)) {
																			contadorS++;
																			p = siguienteLC($6,p);
																		}

																		// Guardamos en b la posicion que tenmos actualmente en nuestro arrayPila
																		// para retroceder contadorS y modificar esa poscion b
																		// PosicionListaC b = arrayPila[pila];
																		// for(int i = 0; i < contadorS; i++){
																		// 	b = anteriorLC(tablaCodigo,b);
																		// }

																		Operacion oper;
																		oper.op = "\tbeqz";
																		oper.res = recuperaResLC($3);
																		oper.arg1 = strdup(temporal);
																		oper.arg2 = NULL;

																		insertaLC(tablaCodigo,posicionES,oper);

																		concatenaLC($$,$6);
																		liberaLC($6);
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

																		guardaResLC($$,oper2.res);
																		
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
																		guardaResLC($$,oper3.res);

																		concatenaLC($$,$9);
																		liberaLC($9);

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
																		guardaResLC($$,oper4.res);

																		contadorEtiquetas++;
																		}
				| IF PARENI expression posicionES_get PAREND statement %prec NOELSE {
														$$ = $3;

														// Contamos cuantas instrucciones tiene el primer statemt para despues 
														// retroceder esa cantidad (contadorS) e insertar "beqz" correctamente
														int contadorS = 0;

														PosicionListaC p = inicioLC($6);
														while (p != finalLC($6)) {
															contadorS++;
															p = siguienteLC($6,p);
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
														oper.res = recuperaResLC($3);
														oper.arg1 = strdup(temporal);
														oper.arg2 = NULL;

														insertaLC(tablaCodigo,posicionES,oper);
														guardaResLC($$,oper.res);

														concatenaLC($$,$6);

														liberaLC($6);

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
														guardaResLC($$,etiq.res);

														contadorEtiquetas++;
														}
				| WHILE PARENI {posicionES = finalLC(tablaCodigo);} expression PAREND {posicionST = finalLC(tablaCodigo); } statement {
															
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
															insertaLC($4,inicioLC($4),oper);

															insertaLC(tablaCodigo,posicionES,oper);
															
															$$ = $4;			

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
															oper2.res = recuperaResLC($4);
															oper2.arg1 = strdup(temporal2);
															oper2.arg2 = NULL;

															insertaLC(tablaCodigo,posicionST,oper2);
															guardaResLC($$,oper2.res);

															concatenaLC($$,$7);
															liberaLC($7);

															Operacion oper3;
															oper3.op = "\tb";
															oper3.res = strdup(temporal);
															oper3.arg1 = NULL;
															oper3.arg2 = NULL;
															
															insertaLC(tablaCodigo,finalLC(tablaCodigo),oper3);
															guardaResLC($$,oper3.res);

															Operacion oper4;
															oper4.op = strdup(etiqueta2);
															oper4.res = NULL;
															oper4.arg1 = NULL;
															oper4.arg2 = NULL;

															insertaLC(tablaCodigo,finalLC(tablaCodigo),oper4);
															guardaResLC($$,oper4.res);

															contadorEtiquetas++;
														}
				| PRINT print_list PUNTCOM {$$ = $2;}
				| READ read_list PUNTCOM { $$ = $2;}
				;

print_list:			print_item {$$ = $1;}
				| print_list COMMA print_item {$$ = $1; concatenaLC($$,$3); liberaLC($3);}
				;
				
print_item:			expression {

								$$ = $1;
								

								Operacion op1;
								op1.op = "\tmove";
								op1.res = "$a0";
								op1.arg1 = recuperaResLC($1);
								op1.arg2 = NULL;

								insertaLC(tablaCodigo,finalLC(tablaCodigo),op1);
								guardaResLC($$,op1.res);
								
								Operacion op2;
								op2.op = "\tli";
								op2.res = "$v0";
								op2.arg1 = "1";
								op2.arg2 = NULL;

								insertaLC(tablaCodigo,finalLC(tablaCodigo),op2);
								guardaResLC($$,op2.res);

								Operacion op3;
								op3.op = "\t\tsyscall";
								op3.res =  NULL;
								op3.arg1 = NULL;
								op3.arg2 = NULL;

								insertaLC(tablaCodigo,finalLC(tablaCodigo),op3);

								guardaResLC($$,op3.res);
								}
				| STRING {
						// Anyadimos a la tabla la cadena e incrementamos el contador
						anyadeEntrada($1,CADENA, contadorCadenas); 


						$$ = creaLC();
						
						// Creamos la etiqueta (ejemplo $str1)
						char temporal[32];
						sprintf(temporal,"$str%d",contadorCadenas);

						Operacion op1;
						op1.op = "\n\tla";
						op1.res = "$a0";
						op1.arg1 = strdup(temporal);
						op1.arg2 = NULL;

						insertaLC($$,finalLC($$),op1);
						insertaLC(tablaCodigo,finalLC(tablaCodigo),op1);
						guardaResLC($$,op1.res);

						Operacion op2;
						op2.op = "\tli";
						op2.res = "$v0";
						op2.arg1 = "4";
						op2.arg2 = NULL;

						insertaLC($$,finalLC($$),op2);
						insertaLC(tablaCodigo,finalLC(tablaCodigo),op2);
						guardaResLC($$,op2.res);

						Operacion op3;
						op3.op = "\t\tsyscall";
						op3.res =  NULL;
						op3.arg1 = NULL;
						op3.arg2 = NULL;

						insertaLC($$,finalLC($$),op3);
						insertaLC(tablaCodigo,finalLC(tablaCodigo),op3);

						guardaResLC($$,op3.res);

						contadorCadenas++;
				}
				;
				
read_list:			ID {
						// Comprobamos el ID si esta declarado y si no es constante
						$$ = creaLC();
						if (!(perteneceTablaS($1)))
								printf("Error | Variable %s no declarada\n",$1);
							else if (esConstante($1)) 
								printf("Error | Asignacion a constante\n");
								else {
									
									// Creamos la concatenacion (ejemplo _$1)
									char temporal[32];
									sprintf(temporal,"_%s",$1);

									Operacion op1;
									op1.op = "\n\tli";
									op1.res = "$v0";
									op1.arg1 = "5";
									op1.arg2 = NULL;

									insertaLC(tablaCodigo,finalLC(tablaCodigo),op1);
									guardaResLC($$,op1.res);

									Operacion op2;
									op2.op = "\t\tsyscall";
									op2.res =  NULL;
									op2.arg1 = NULL;
									op2.arg2 = NULL;

									insertaLC(tablaCodigo,finalLC(tablaCodigo),op2);
									guardaResLC($$,op2.res);

									Operacion op3;
									op3.op = "\tsw";
									op3.res = "$v0";
									op3.arg1 = strdup(temporal);
									op3.arg2 = NULL;

									insertaLC(tablaCodigo,finalLC(tablaCodigo),op3);
									guardaResLC($$,op3.res);
								}
								}
				| read_list COMMA ID {
									// Comprobamos el ID si esta declarado y si no es constante
									if (!(perteneceTablaS($3)))
											printf("Error | Variable %s no declarada\n",$3);
										else if (esConstante($3)) 
											printf("Error | Asignacion a constante\n");
											else {

												// Creamos la concatenacion (ejemplo _$1)
												char temporal[32];
												sprintf(temporal,"_%s",$3);

												Operacion op1;
												op1.op = "\n\tli";
												op1.res = "$v0";
												op1.arg1 = "5";
												op1.arg2 = NULL;

												insertaLC($$,finalLC($$),op1);
												insertaLC(tablaCodigo,finalLC(tablaCodigo),op1);
												guardaResLC($$,op1.res);

												Operacion op2;
												op2.op = "\t\tsyscall";
												op2.res =  NULL;
												op2.arg1 = NULL;
												op2.arg2 = NULL;

												insertaLC($$,finalLC($$),op2);
												insertaLC(tablaCodigo,finalLC(tablaCodigo),op2);
												guardaResLC($$,op2.res);

												Operacion op3;
												op3.op = "\tsw";
												op3.res = "$v0";
												op3.arg1 = strdup(temporal);
												op3.arg2 = NULL;

												insertaLC($$,finalLC($$),op3);
												insertaLC(tablaCodigo,finalLC(tablaCodigo),op3);
												guardaResLC($$,op3.res);
											}
											}
				;
expression:			expression PLUSOP expression {
												$$ = $1;
												concatenaLC($$,$3);
												
												Operacion oper;
												oper.op = "\tadd";
												oper.res = recuperaResLC($1);
												oper.arg1 = recuperaResLC($1);
												oper.arg2 = recuperaResLC($3);

												insertaLC(tablaCodigo,finalLC(tablaCodigo),oper);
												guardaResLC($$,oper.res);
												liberarRegistro(oper.arg1);
												liberarRegistro(oper.arg2);

												// Liberamos la expresion que concatenamos,
												// debido a que cuando conctatenamos, conctenaLC(a,b)
												// se hace una copia de b en a, y podemos liberar b
												liberaLC($3);
												}
				| expression MINUSOP expression {
												$$ = $1;
												concatenaLC($$,$3);
												
												Operacion oper;
												oper.op = "\tsub";
												oper.res = recuperaResLC($1);
												oper.arg1 = recuperaResLC($1);
												oper.arg2 = recuperaResLC($3);

												insertaLC(tablaCodigo,finalLC(tablaCodigo),oper);
												guardaResLC($$,oper.res);
												liberarRegistro(oper.arg1);
												liberarRegistro(oper.arg2);

												// Liberamos la expresion que concatenamos,
												// debido a que cuando conctatenamos, conctenaLC(a,b)
												// se hace una copia de b en a, y podemos liberar b
												liberaLC($3);
												}
				| expression MULTOP expression {
												$$ = $1;
												concatenaLC($$,$3);
												
												Operacion oper;
												oper.op = "\tmul";
												oper.res = recuperaResLC($1);
												oper.arg1 = recuperaResLC($1);
												oper.arg2 = recuperaResLC($3);

												insertaLC(tablaCodigo,finalLC(tablaCodigo),oper);
												guardaResLC($$,oper.res);
												liberarRegistro(oper.arg1);
												liberarRegistro(oper.arg2);

												// Liberamos la expresion que concatenamos,
												// debido a que cuando conctatenamos, conctenaLC(a,b)
												// se hace una copia de b en a, y podemos liberar b
												liberaLC($3);
												}
				| expression DIVOP expression {
												$$ = $1;
												concatenaLC($$,$3);
												
												Operacion oper;
												oper.op = "\tdiv";
												oper.res = recuperaResLC($1);
												oper.arg1 = recuperaResLC($1);
												oper.arg2 = recuperaResLC($3);

												insertaLC(tablaCodigo,finalLC(tablaCodigo),oper);
												guardaResLC($$,oper.res);
												liberarRegistro(oper.arg1);
												liberarRegistro(oper.arg2);

												// Liberamos la expresion que concatenamos,
												// debido a que cuando conctatenamos, conctenaLC(a,b)
												// se hace una copia de b en a, y podemos liberar b
												liberaLC($3);
												}
				| PARENI expression PAREND {
											// La expresion ya esta creada no hace falta anyadir nada, debido a que los parentesis no modifican nada,
											// solo que esta en otra posicion
											$$ = $2;
											}
				| MINUSOP expression %prec UMENOS {
													$$ = $2;

													// Tendriamos que hacer la negacion
													Operacion oper;
													oper.op = "\tneg";
													oper.res = recuperaResLC($2);
													oper.arg1 = recuperaResLC($2);
													oper.arg2 = NULL;

													insertaLC(tablaCodigo,finalLC(tablaCodigo),oper);
													guardaResLC($$,oper.res);
													}
				| ID  {
					// Comprobamos si el ID esta declarado o no, no nos importa su tipo
					$$ = creaLC();
					if (!(perteneceTablaS($1))) {
						printf("Error | Variable %s no declarada\n",$1);
					} else {
						Operacion oper;
						oper.op = "\n\tlw";
						oper.res = obtenerRegistro();
						oper.arg1 = concatenar($1);
						oper.arg2 = NULL;

						insertaLC(tablaCodigo,finalLC(tablaCodigo),oper);

						guardaResLC($$,oper.res);
					}}
				| INT {
						$$ = creaLC();
						Operacion oper;
						oper.op = "\tli";
						oper.res = obtenerRegistro();
						oper.arg1 = $1;
						oper.arg2 = NULL;

						insertaLC(tablaCodigo,finalLC(tablaCodigo),oper);

						guardaResLC($$,oper.res);
						}
				;
%%

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