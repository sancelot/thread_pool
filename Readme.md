** Work in progress **

This program is for educative purposes.

It will implement thread pool shared amongst all cpu available in a linux system.

ThreadPool :
Creating and deallocating threads to run parallel tasks is  consuming a lot of kernel system accesses and is not efficient.
kernel accesses must be limited for performance.
To solve it  a thread pool is setted up.

A thread is allocated for each cpu core (depending on kind of application, this may be tuned), and jobs are sequentially launched on each core becoming available.

Potential Bottlenecks depending on application:
File reading and writing are slow operations

disk swap:
for efficiency , swap of the application is forbidden.
It implies that machine with not enough memory will not being able use this program.

TODO: adapt it to win32
