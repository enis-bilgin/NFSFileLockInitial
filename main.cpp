#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


// timer
#include <time.h>

// custom classes
#include "fileregister.h"

// glog
#include <glog/logging.h>
#include <gflags/gflags.h>




// Timing Function
static long get_nanos(void){
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return (long)ts.tv_sec*1000000000L + ts.tv_nsec;

}


// Test Function
int main (int argc, char* argv[]) {


    gflags::ParseCommandLineFlags(&argc,&argv,true);
    google::InitGoogleLogging(argv[0]);
    FLAGS_logtostderr = true;

    std::string filename1 = "/home/ubuntu/MultiRunTest/multiLockTest1.txt";
    std::string filename2 = "/home/ubuntu/MultiRunTest/multiLockTest2.txt";
    std::string filename3 = "/home/ubuntu/MultiRunTest/multiLockTest3.txt";


    // Save Files in Register
    FileRegister::instance().addNewFile(filename1);
    FileRegister::instance().addNewFile(filename2);
    FileRegister::instance().addNewFile(filename3);


    // 1 Lock for each File RAII Type
    FileRegister::instance().lockFileToWrite();


}
