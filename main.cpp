#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


// timer
#include <time.h>






int main (int argc, char* argv[])
{
    // some timing
    int msecond = 0, trigger = 10;

    char* file = "/home/ubuntu/MultiRunTest/multiLockTest.txt";
    int fd;
    struct flock lock;

    printf ("opening %s\n", file);
/* Open a file descriptor to the file. */
    fd = open (file, O_WRONLY);
    printf ("locking\n");
/* Initialize the flock structure. */
    memset (&lock, 0, sizeof(lock));
    lock.l_type = F_WRLCK;
/* Place a write lock on the file. */
    if(fcntl (fd, F_SETLKW, &lock)==-1){
        printf("Lock not succcessful?");
    }


    printf ("locked; hit Enter to unlock... ");
/* Wait for the user to hit Enter. */
    getchar ();


    printf ("unlocking\n");




/* Release the lock. */
    clock_t before = clock();

    lock.l_type = F_UNLCK;
    fcntl (fd, F_SETLKW, &lock);


    clock_t difference = clock() - before;
    msecond = difference * 1000 / CLOCKS_PER_SEC;

    printf ("Time Taken to Unlock in Miliseconds: (%d)\n", msecond%1000);

    close (fd);
    return 0;
}
