//this file is stored inside examples online now

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define //...

int main(int argc, char *argv[]){
  pthread_t threads[NUM_THREADS]; //id's
  int rc;
  long t;
  //looop through...
  

}

/*
  identify the code the thread will run
  start the thread code running
  exit from thread
  ...

  POSIX API has all this functionality -> DON'T DETACH THREADS

  pthread_create (thread, attr, start_routine, arg_)
  -Create & start thread routine running

  pthread_exit(status) //with void*
  -exit thread and return status value
  pthread_cancel(thread)
  -cancel specific thread with given trhread ID(tid)
  pthread_join(threadID)
  -
  pthread_deatch()
  -
