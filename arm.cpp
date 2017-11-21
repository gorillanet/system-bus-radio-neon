#include <iostream>
#include <string>
#include <iomanip>
#include <chrono>
#include <arm_neon.h>
#include <stdlib.h>
#include <inttypes.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <signal.h>

std::mutex m ;
std::condition_variable cv ;
std::chrono::high_resolution_clock::time_point mid ;
std::chrono::high_resolution_clock::time_point reset ;

int32x4_t va;
int32_t a ;
int32_t * ptr;
int32_t n = 2500;
int64_t size = sizeof(a)*n;
int32_t limit = n-4;

int init_memory(void) {
    ptr = (int32_t *)malloc(size);
    if( ptr == NULL ){
        std::cout << "Malloc Error" << std::endl;
        return -1;
    }
    for(int i=0; i<=n; i++){
        ptr[i] = i;
    }
    return 0;
}

void inline sig_handler(int sign) {
    std::cout << "\nReceived signal. aborting." << std::endl ;
    exit(-1);
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
        int i = 0;
        while( high_resolution_clock::now() < mid ) {
            va = vld1q_s32(ptr+i);
            i++;
            if(i==limit) i=0;
        }
        std::this_thread::sleep_until( reset ) ;
        start = reset;
    }
}

int main(int argc, char *argv[]){
    signal(SIGINT, sig_handler);

    init_memory();
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
    return 0;
}
