

polynomial:
	g++ LongInt.cpp Polynomial.cpp testPolynomial.cpp -fsanitize=address
p:
	g++ LongInt.cpp Polynomial.cpp testPolynomial.cpp -fsanitize=address


longint:
	g++ LongInt.cpp testLongInt.cpp -fsanitize=address
l:
	g++ LongInt.cpp testLongInt.cpp -fsanitize=address


run:	
	./a.out
r:
	./a.out

clean:
	rm a.out
c: 
	rm a.out
