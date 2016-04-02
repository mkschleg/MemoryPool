#ifndef _MEMPOOL_H
#define _MEMPOOL_H

class Pool {

 private:
  unsigned char* pool;
  int* firstNode;
 public:
  Pool(int);
  void* allocate (unsigned int);
  void deallocate (void* ptr);

  void print_size();

};






#endif
