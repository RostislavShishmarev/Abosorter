all: sorter

sorter:
	gcc main.c const/const.c abonent/abonent.c abonent/io.c sorts/sorts.c -o sorter.out

