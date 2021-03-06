#ifndef FILEREGISTER_HPP
#define FILEREGISTER_HPP

#include <string>
#include <vector>
#include <algorithm>
#include <glog/logging.h>

// sleep
#include <chrono>
#include <thread>

// Lock / Unlock class
#include "fnctlRAIILock.h"


struct FileEntry {
    std::string filename; // file directory
    int fd; // file descriptor
};


class FileRegister {
public:

    static FileRegister& instance(){
        static FileRegister inst;
        return inst;
    }

    // Add new Entry
    void addNewFile(std::string& filename){
        LOG(INFO) << "Opening FILE: " << filename;

        // Create an Entry and Save
        FileEntry singleFileEntry;
        singleFileEntry.filename = filename;
        singleFileEntry.fd = open(filename.c_str(), O_WRONLY);

        // Success / Fail Log
        if(singleFileEntry.fd != openFail){
            fileList.emplace_back(singleFileEntry);
            LOG(INFO) << "File Entry SUCCESS for File: " << filename;
        } else{
            LOG(INFO) << "File Entry FAILED for File: " << filename;
        }
    }

    void removeFileByName(std::string& filenameremove){
        fileList.erase(std::remove_if(fileList.begin(), fileList.end(), [&](FileEntry const& fileEntry){
            return fileEntry.filename == filenameremove;
        }));
    }



    void lockFileToWrite(std::string& filenametowrite) {
        for(auto eachEntry : fileList) {
            if(eachEntry.filename == filenametowrite){
                while(true) {
                    {
                        fnctlRaiiLock guardfnctl(eachEntry.fd); // locked
                        LOG(INFO) << "Writing";
                        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
                       // write(eachEntry.fd, "Writing from Thread and then Sleep for 5 milliseconds\n", 54); // write
                    }
                    LOG(INFO) << "Sleeping";
                    std::this_thread::sleep_for(std::chrono::milliseconds(4000));


                }
            }
        }
    }


    void readLockedFiles(std::string& filenametoread){
        for(auto eachEntry : fileList){
            if(eachEntry.filename == filenametoread){
                while(true) {
                    {
                        fnctlRaiiLock guardfnctl(eachEntry.fd); // locked
                        // unlocked
                        std::this_thread::sleep_for(std::chrono::milliseconds(2000));

//                        char readLine[60];
                        //read(eachEntry.fd,readLine,54);
                        LOG(INFO) << "Reading" ;
                    }


                }

            }
        }
    }



private:
    FileRegister() {} // ctor

    ~FileRegister() { // on destruction close files
        for(auto fileEntry : fileList){
            // sleep 2 sec before close
            // it should not close the fd before releases the lock
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            close(fileEntry.fd);
        }

    }

    const int openFail = -1;

    // delete these
    FileRegister(const FileRegister&)           = delete;
    FileRegister(FileRegister&)                 = delete;
    FileRegister operator=(const FileRegister&) = delete;
    FileRegister operator=(FileRegister&&)      = delete;

    // keep file names and their file descriptors
    std::vector<FileEntry> fileList;

};


#endif