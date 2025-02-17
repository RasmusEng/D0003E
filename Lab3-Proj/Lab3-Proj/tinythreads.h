/*
*
* tinythreads.h
*
*/
#ifndef _TINYTHREADS_H
#define _TINYTHREADS_H

struct thread_block;
typedef struct thread_block *thread;
void timerInit();
void spawn(void (*code)(int), int arg);
void yield(void);
void addCount();
int getCount();
void resetCount();

#endif