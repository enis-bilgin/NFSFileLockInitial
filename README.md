#FileLockTestRepo
Lock-Unlock Test Repo



**Purpose**

Initial development of NFS Type lock file, not a perfect lock but considerable for 2+ seconds file locks
Unfortunately NFS File lock uses flock which is not really reliable per this article
* http://0pointer.de/blog/projects/locking.html

It works in most cases, if there is some LOG or end of the day logs it could be used
    
    
    
   


