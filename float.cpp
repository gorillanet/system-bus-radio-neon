#include <iostream>
#include <string>
#include <iomanip>
#include <chrono>
#include <emmintrin.h>
#include <stdlib.h>
#include <inttypes.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <signal.h>
#include <math.h>

std::mutex m ;
std::condition_variable cv ;
std::chrono::high_resolution_clock::time_point mid ;
std::chrono::high_resolution_clock::time_point reset ;

double * ptr;
int64_t n = 2500;
int64_t size = sizeof(n)*n;
int32_t limit = n-4;



void inline sig_handler(int sign) {
    std::cout << "\nReceived signal. aborting." << std::endl ;
    exit(-1);
}

int init_memory(void) {
    ptr = (double *)malloc(size);
    if( ptr == NULL ){
        std::cout << "Malloc Error" << std::endl;
        return -1;
    }
    for(int i=0; i<=n; i++){
        ptr[i] = 3.1415;
    }
    return 0;
}

void square_am_signal(float time, float frequency) {
    using namespace std::chrono ;
    
    std::cout << "Playing / " << time << " seconds / " << frequency << " Hz\n" ;

    seconds const sec{1} ;
    nanoseconds const nsec{ sec } ;
    using rep = nanoseconds::rep ;
    auto nsec_per_sec = nsec.count() ;

    nanoseconds const period( static_cast<rep>( nsec_per_sec / frequency) ) ;

    auto start = high_resolution_clock::now() ;
    auto const end = start + nanoseconds( static_cast<rep>(time * nsec_per_sec) ) ;

    while (high_resolution_clock::now() < end) {
        mid = start + period / 2 ;
        reset = start + period ;
        int i = 0.0;
        while( high_resolution_clock::now() < mid ) {
            *ptr = 1 - log(*(ptr + i)) / 1.7193;
            i++;
            if(i==limit) i=0;
        }
        std::this_thread::sleep_until( reset ) ;
        start = reset;
    }
}

int main(int argc, char *argv[]){
    init_memory();
    signal(SIGINT, sig_handler);

    if (argc ==2){
        std::string str = argv[1];
        if (str=="zelda"){
            while(1){
                square_am_signal(0.150, 1568);
                square_am_signal(0.150, 1480);
                square_am_signal(0.150, 1245);
                square_am_signal(0.150, 880);
                square_am_signal(0.150, 831);
                square_am_signal(0.150, 1319);
                square_am_signal(0.150, 1661);
                square_am_signal(0.200, 2093);
            }
        }
    }
    else{
        while (1) {
            square_am_signal(0.400, 2673);
            square_am_signal(0.400, 2349);
            square_am_signal(0.400, 2093);
            square_am_signal(0.400, 2349);
            square_am_signal(0.400, 2673);
            square_am_signal(0.400, 2673);
            square_am_signal(0.790, 2673);
            square_am_signal(0.400, 2349);
            square_am_signal(0.400, 2349);
            square_am_signal(0.790, 2349);
            square_am_signal(0.400, 2673);
            square_am_signal(0.400, 3136);
            square_am_signal(0.790, 3136);
            square_am_signal(0.400, 2673);
            square_am_signal(0.400, 2349);
            square_am_signal(0.400, 2093);
            square_am_signal(0.400, 2349);
            square_am_signal(0.400, 2673);
            square_am_signal(0.400, 2673);
            square_am_signal(0.400, 2673);
            square_am_signal(0.400, 2673);
            square_am_signal(0.400, 2349);
            square_am_signal(0.400, 2349);
            square_am_signal(0.400, 2673);
            square_am_signal(0.400, 2349);
            square_am_signal(0.790, 2093);
        }
    }
    return 0;
}
