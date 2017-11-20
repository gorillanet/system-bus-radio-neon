main:radio.cpp
	g++ radio.cpp -O3 -Wall -mfpu=neon -std=c++11 -pthread -lrt -o neon

exp01:exp01.cpp
	g++ exp01.cpp -O3 -Wall -mfpu=neon -std=c++11 -pthread -lrt -o exp01

exp02:exp02.cpp
	g++ exp01.cpp -O3 -Wall -mfpu=neon -std=c++11 -pthread -lrt -o exp02

clean:
	rm -f neon
