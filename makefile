a.out :main.o main_scan.o preprocessor_scan.o scan_functions.o word_scan.o
	gcc main.o main_scan.o preprocessor_scan.o scan_functions.o word_scan.o

main.o : main.c
	gcc -c main.c
main_scan.o : main_scan.c
	gcc -c main_scan.c
preprocessor_scan.o : preprocessor_scan.c
	gcc -c preprocessor_scan.c
scan_functions.o : scan_functions.c
	gcc -c scan_functions.c
word_scan.o : word_scan.c
	gcc -c word_scan.c