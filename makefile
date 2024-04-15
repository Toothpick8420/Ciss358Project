
LongIntTest:
	g++ LongInt.cpp testLongInt.cpp -fsanitize=address

run:	
	./a.out

r:
	./a.out

clean:
	rm a.out

c: 
	rm a.out
