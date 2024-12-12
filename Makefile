all: sorter

sorter:
	gcc main.c abonent/abonent.c abonent/io.c sorts/sorts.c -o sorter.out

