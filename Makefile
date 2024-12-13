all: sorter

sorter:
	gcc sorter.c const/const.c abonent/abonent.c abonent/compares.c abonent/io.c sorts/sorts.c -o sorter.out -Wall -Wextra -std=gnu99

