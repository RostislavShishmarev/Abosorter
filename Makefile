all: sorter timer

sorter:
	gcc sorter.c const/const.c abonent/abonent.c abonent/compares.c abonent/io.c sorts/sorts.c -o sorter.out -Wall -Wextra -std=gnu99

sorter_debug:
	gcc sorter.c const/const.c abonent/abonent.c abonent/compares.c abonent/io.c sorts/sorts.c -o sorter.out -Wall -Wextra -std=gnu99 -g

timer:
	gcc timer.c const/const.c abonent/abonent.c abonent/compares.c sorts/sorts.c -o timer.out -Wall -Wextra -std=gnu99

timer_debug:
	gcc timer.c const/const.c abonent/abonent.c abonent/compares.c sorts/sorts.c -o sorter.out -Wall -Wextra -std=gnu99 -g
