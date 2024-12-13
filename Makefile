all: sorter

sorter:
	gcc sorter.c const/const.c abonent/abonent.c abonent/io.c sorts/sorts.c -o sorter.out -Wall -Wextra

