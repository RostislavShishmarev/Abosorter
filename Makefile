all: sorter

sorter:
	cc main.c abonent/abonent.c abonent/io.c sorts/sorts.c -o sorter.out

