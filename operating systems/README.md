# Operating Systems

These C lab exercises explore how Linux processes and threads run, share data, and coordinate access to it.

| Folder | What it covers |
| --- | --- |
| [fork](fork/) | Process and parent IDs, creating child processes with `fork()`, separate copies of variables, and observing orphan and zombie processes with `ps`. |
| [helloworld with threads](helloworld%20with%20threads/) | Creating and joining POSIX threads, passing arguments to them, and updating a shared counter. |
| [monitor](monitor/) | Thread-based producer–consumer exercises with a single-slot buffer and a circular buffer, using mutexes and condition variables. Also includes a [pthread stack](monitor/pthread%20stack/) exercise with synchronized push and pop operations and an exam handout. |
| [posix shm](posix%20shm/) | Sharing memory between processes with `shm_open()` and `mmap()`, including a shared-counter exercise. |
| [semaphore](semaphore/) | Protecting a shared counter with a process-shared semaphore and coordinating producers and consumers with single-slot and circular buffers. The circular-buffer exercise includes a lab handout. |
| [shell example](shell%20example/) | A small shell that reads a command, starts it with `fork()` and `execvp()`, and waits for it to finish. |

## Running the examples

Use a Linux environment with a C compiler. Build the examples from their own directories. Use the local Makefile where provided and compile standalone pthread examples with `-pthread`.

For example, from the repository root:

```sh
cd "operating systems/helloworld with threads"
gcc -pthread helloworld_threads.c -o /tmp/lab-notes-threads
/tmp/lab-notes-threads
```
