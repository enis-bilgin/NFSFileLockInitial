#ifndef FNCTLRAIILOCK_HPP
#define FNCTLRAIILOCK_HPP

#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <glog/logging.h>

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
        LOG(INFO) << "LOCKED " << fd;
    }

    // unlock on destruction
    ~fnctlRaiiLock(){
        raiLocker_.locker_.l_type = F_UNLCK;
        fcntl (fileDescriptor_, F_SETLKW, &raiLocker_); // unlock
        fileDescriptor_ = int(); // reset fd
        LOG(INFO) << "UNLOCKED ";
    }


private:
    // delete this
    fnctlRaiiLock(const fnctlRaiiLock&) = delete; // no copy

    int fileDescriptor_;
    FnctlRAIILock raiLocker_;
};


#endif