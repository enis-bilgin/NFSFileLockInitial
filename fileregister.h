#ifndef FILEREGISTER_HPP
#define FILEREGISTER_HPP

#include <string>
#include <vector>
#include <algorithm>
#include <glog/logging.h>

// Lock / Unlock class
#include <fcntl.h>





struct FileEntry {
    std::string filename; // file directory
    int fd{}; // file descriptor
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
        if(fileList.back().fd != -1){
            fileList.push_back(singleFileEntry);
            LOG(INFO) << "File Entry Success for File: " << filename;
        } else{
            LOG(INFO) << "File Entry Failed for File: " << filename;
        }
    }

    void removeFileByName(std::string& filenameremove){
        fileList.erase(std::remove_if(fileList.begin(), fileList.end(), [&](FileEntry const& fileEntry){
            return fileEntry.filename == filenameremove;
        }));
    }


private:
    FileRegister() {} // ctor

    ~FileRegister() { // on destruction close files
        for(auto fileEntry : fileList)
            close(fileEntry.fd);
    }

    // delete these
    FileRegister(const FileRegister&)           = delete;
    FileRegister(FileRegister&)                 = delete;
    FileRegister operator=(const FileRegister&) = delete;
    FileRegister operator=(FileRegister&&)      = delete;

    // keep file names and their file descriptors
    std::vector<FileEntry> fileList;

};


#endif