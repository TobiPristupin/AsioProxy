Proxy Architecture:
1: Have a thread per connection, which performs everything for that connection.
  Pros:
    * Simple to implement
  Cons:
    * Requires creating too many threads
    * Clients are not constantly sending requests. Threads might be inactive for most of the time
    * In conclusion, we have a lot of threads and most of them are sleeping.
    * Contention in cache since many threads attempt to access simultaneously

2: Have a (smaller) thread pool that manages incoming requests. Place requests in a work queue. A (larger) thread pool
then pulls from the thread queue and performs the actions.
  Pros:
    * Less threads created
    * Threads are constantly busy
  Cons:
    * Complex to implement
    * Possible contention in work queue
    * Contention as the incoming requests thread will read from the socket while the other threads write to the socket. 
      Introduces the question of thread safety for socket read/write operations.
Decision: (2) would be hard to implement and require thinking about thread safety for sockets. (1) would be best, but
make sure that when a request comes in a new thread is created, the thread then performs the work, and the thread is 
joined when the work is finished. Essentially a thread per request.

Thoughts on Cache:
* Have a cache class
* Implement a reader-writer lock
* New request comes in, make the request and then call malloc to store the request data in the heap
* Keep track of how much we have malloced to determine if we have filled the cache
* Cache size cmd param
* For each cache entry, store the time of creation. Lazily invalidate a cache entry if X seconds have passed
* Run LRU on demand when an eviction is needed
* Note: No need to do malloc, we can use a map which uses the heap


read tutorial on making server
do we just take host and redirect request?