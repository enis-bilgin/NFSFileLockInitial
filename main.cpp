#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


// timer
#include <time.h>

// custom classes
#include "fnctlRAIILock.h"
#include "fileregister.h"

// glog
#include <glog/logging.h>
#include <gflags/gflags.h>





static long get_nanos(void){
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return (long)ts.tv_sec*1000000000L + ts.tv_nsec;

}

int main (int argc, char* argv[]) {


    gflags::ParseCommandLineFlags(&argc,&argv,true);
    google::InitGoogleLogging(argv[0]);

    FLAGS_logtostderr = true;

    std::string filename = "/home/ubuntu/MultiRunTest/multiLockTest.txt";
    int fd;

    struct flock lock;

    printf ("opening %s\n", filename.c_str());

    // Open a file descriptor to the file
    fd = open (filename.c_str(), O_WRONLY);
    printf ("locking\n");


    // Initialize the flock structure
    memset (&lock, 0, sizeof(lock));
    lock.l_type = F_WRLCK;

    auto start = get_nanos();

    // Place a write lock on the file
    if(fcntl (fd, F_SETLKW, &lock)==-1){
        printf("Lock not succcessful?");
    }
    auto end = get_nanos();

    LOG(INFO) << "Time Taken to Lock in Miliseconds:" << end-start;

    printf ("locked; hit Enter to unlock... ");


    // Wait for the user to hit Enter.
    getchar ();


    printf ("unlocking\n");




/* Release the lock. */
    lock.l_type = F_UNLCK;
    fcntl (fd, F_SETLKW, &lock);

    close (fd);
    return 0;
}
