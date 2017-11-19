#include <iostream>
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

void inline sig_handler(int sign) {
    free(ptr);
    std::cout << "\nReceived signal. aborting." << std::endl ;
    exit(-1);
}

void inline boost_song() {
    using namespace std::chrono ;

    int i{0} ;
    while( true ) {
        std::unique_lock<std::mutex> lk{m} ;
        cv.wait( lk ) ;

        while( high_resolution_clock::now() < mid ) {
//            int32_t var[4] = { *(ptr + i), *(ptr + i + 2), *(ptr + i + 3), *(ptr + i + 4) };
            va = vld1q_s32(ptr+i);
            i++;
            if(i==limit) i=0;
        }
        std::this_thread::sleep_until( reset ) ;
    }
}

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
        cv.notify_all() ;
        std::this_thread::sleep_until( reset ) ;
        start = reset;
    }
}

int main(int argc, char *argv[]){
    signal(SIGINT, sig_handler);

    init_memory();
    for ( unsigned i = 0 ; i < std::thread::hardware_concurrency() ; ++i ) {
        std::thread t( boost_song ) ;
        t.detach() ;
    }
    if (argv[1]=="zelda")
        while(1){
            square_am_signal(0.200, 1480);
            square_am_signal(0.200, 1397);
            square_am_signal(0.200, 1175);
            square_am_signal(0.200, 1661);
            square_am_signal(0.200, 1568);
            square_am_signal(0.200, 1245);
            square_am_signal(0.200, 1568);
            square_am_signal(0.200, 1976);
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
    free(ptr);
    return 0;
}
