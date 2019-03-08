#ifndef FNCTLRAIILOCK_HPP
#define FNCTLRAIILOCK_HPP

#include <fcntl.h>
#include <unistd.h>
#include <string.h>

/*
 * fnctl struct wrapper
 */
struct FnctlRAIILock{
    flock locker_{};
    FnctlRAIILock(){
        memset(&locker_, 0, sizeof(locker_));
        locker_.l_type = F_WRLCK;
    }
};

/*
 * RAII Type Lock
 */
class fnctlRaiiLock {
public:
    // lock on construction, no default constructor
    explicit fnctlRaiiLock(int fd){
        fileDescriptor_ = fd;
        fcntl (fileDescriptor_, F_SETLKW, &raiLocker_);
    }

    // unlock on destruction
    ~fnctlRaiiLock(){
        fileDescriptor_ = int(); // reset fd
        fcntl (fileDescriptor_, F_SETLKW, &raiLocker_); // unlock
    }



private:
    // delete this
    fnctlRaiiLock(const fnctlRaiiLock&) = delete; // no copy

    int fileDescriptor_;
    FnctlRAIILock raiLocker_;
};


#endif