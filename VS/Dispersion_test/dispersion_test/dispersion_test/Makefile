all : clg_test

objects = challenge.o main.o

$(objects): %.o: %.c
	gcc -c -Wall $< -o $@

clg_test : $(objects)
	gcc -Wall $^ -o $@ -lm 

clean :
	-rm clg_test
	-rm *.o
