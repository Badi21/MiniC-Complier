minic: main.c minic.tab.c lex.yy.c minic.tab.h listaSimbolos.c listaSimbolos.h listaCodigo.c listaCodigo.h
	gcc lex.yy.c main.c minic.tab.c listaSimbolos.c listaCodigo.c -lfl -o minic
minic.tab.c minic.tab.h: minic.y
	bison -d minic.y
lex.yy.c: minic.l
	flex minic.l
	
run: minic 
	./minic entrada1.txt
	
limpia:
	rm lex.yy.c minic.tab.c minic.tab.h minic


