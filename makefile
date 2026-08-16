a.out :main.o scan.o preprocessor_scan.o scan_functions.o word_scan.o evaluation.o
	gcc main.o scan.o preprocessor_scan.o scan_functions.o word_scan.o evaluation.o

main.o : main.c
	gcc -c main.c
scan.o : scan.c
	gcc -c scan.c
preprocessor_scan.o : preprocessor_scan.c
	gcc -c preprocessor_scan.c
scan_functions.o : scan_functions.c
	gcc -c scan_functions.c
word_scan.o : word_scan.c
	gcc -c word_scan.c
evaluation.o : evaluation.c
	gcc -c evaluation.c