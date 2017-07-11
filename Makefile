main:radio.cpp
	g++ radio.cpp -O3 -Wall -mfpu=neon -std=c++11 -pthread -lrt -o neon

clean:
	rm -f neon