main:radio.cpp
	g++ radio.cpp -O3 -Wall -mfpu=neon -std=c++11 -pthread -lrt -o neon

exp01:exp01.cpp
	g++ exp01.cpp -O3 -Wall -mfpu=neon -std=c++11 -pthread -lrt -o exp01

intel:intel.cpp
	g++ intel.cpp -O3 -Wall -msse2 -march=native -std=c++11 -pthread -o intel

arm:arm.cpp
	g++ arm.cpp -O3 -Wall -mfpu=neon -march=native -std=c++11 -pthread -o arm

clean:
	rm -f neon
