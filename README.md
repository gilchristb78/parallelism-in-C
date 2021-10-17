# parallelism-in-C
I created a simple program in C to use parallelism on multicore processors.


This Project shows how parralelism can be implimented to speed up lengthy processes by deligated tasks to seperate processes that the CPU can then seperate on to seperate cores. This program impliments a simple command of finding how many occurances of a letter are in a given file. The program will first map the file to memory using memory-mapping, then it will search the given file for a certain character and report back the file size in bytes and the number of occurances of the character. After this was fully implimented I created the ability to use parralell processes in order to speed up the process on large file sizes. The parralellism will split up the file into chunks that will be fead to the different processes, each will then report back the occurance it found inside its chunk. Attached is also a report of basic runtime testing using another program written in C comparing the different methods.

To run this file simply compile the code (proj2.c) or run off the file proj2 with the command:

./proj2 (file name) (character)
    -for a simple version that will use the read() system call
    
./proj2 (file name) (character) (number 1-8k bytes)
    -for a version that will use the read() call on a specific chunk size
    
./proj2 (file name) (character) mmap 
    -for a version that will use memory mapping
    
./proj2 (filename) (character) p(#)
    -for a version that will use parralellism with a specific number of processes
    


examples:
./proj2 proj2.c " "          (will output how man spaces are in the file)
./proj2 example.txt a 2000   (will search in 2000 bite chunks and output how many a's are in the file)
./proj2 readme.txt b mmap    (will map the file to memory then output how many b's are in the file)
./proj2 this.txt c p4        (will split the file into 4 chunks and be run parralelly on up to 4 cores and output how many c's are in the file)
