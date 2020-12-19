# Reader_Writer-Locks
In computer science, the readers–writers problems are examples of a common computing problem in concurrency. There are at least three variations of the problems, which deal with situations in which many concurrent threads of execution try to access the same shared resource at one time.

Classic Solution:
Reader()
   Wait until no writers
   Access database
   Check out – wake up a waiting writer
Writer()
   Wait until no active readers or writers
   Access database
   Check out – wake up waiting readers or writer
   
C++ 14 Solution:
With C++14 came reader-writer locks. The idea is straightforward and promising. Arbitrary reading threads can access the critical region at the same time, but only one thread is allowed to write.

The source code has both the code implementation.
