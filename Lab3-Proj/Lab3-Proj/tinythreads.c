#include <setjmp.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "tinythreads.h"

#define NULL            0
#define DISABLE()       cli()
#define ENABLE()        sei()
#define STACKSIZE       80
#define NTHREADS        4
#define SETSTACK(buf,a) *((unsigned int *)(buf)+8) = (unsigned int)(a) + STACKSIZE - 4; \
						*((unsigned int *)(buf)+9) = (unsigned int)(a) + STACKSIZE - 4

struct thread_block {
	void (*function)(int); // code to run
	int arg; // argument to the above
	thread next; // for use in linked lists
	jmp_buf context; // machine state

	char stack[STACKSIZE]; // execution stack space
};

struct thread_block threads[NTHREADS];
struct thread_block initp;
thread freeQ = threads;
thread readyQ = NULL;
thread current = &initp;
int initialized = 0;

static void initialize(void) {
	int i;
	for (i=0; i<NTHREADS-1; i++)
	threads[i].next = &threads[i+1];
	threads[NTHREADS-1].next = NULL;
	
	//Timer things
	//Compare match
	TCCR1A |= (0x1 << COM1A1) | (0x1 << COM1A0);
	
	//Prescaler
	TCCR1B |= (0x1 << WGM12) | (0x1 << CS12) | (0x1 << CS10);
	
	//Enabling timer interrupts
	TIMSK1 |= (0x1 << OCIE1A);
	
	DISABLE();		//Disable interrupts as we just enabled them and dont want a interupt to occur whiole seting OCR1A and reseting the timer.
	
	OCR1A = 391;	// (50*10^-3 * 8 * 10^6)/(1024)
	TCNT1 = 0;		//Clear Timer register
	ENABLE();
	
	initialized = 1;
}

static void enqueue(thread p, thread *queue) {
	/*Places a thread in the given queue*/
	p->next = NULL;
	if (*queue == NULL) {
		*queue = p;
		} else {
		thread q = *queue;
		while (q->next)
		q = q->next;
		q->next = p;
	}
}
static thread dequeue(thread *queue) {
	/*Extracts the next thread from a queue*/
	thread p = *queue;
	if (*queue) {
		*queue = (*queue)->next;
		} else {
		// Empty queue, kernel panic!!!
		while (1) ; // not much else to do...
	}
	return p;
}

static void dispatch(thread next) {
	/*Jumpes to the given thread*/
	if (setjmp(current->context) == 0) {
		current = next;
		longjmp(next->context,1);
	}
}

void spawn(void (* function)(int), int arg) {
	/*Create new thread*/
	thread newp;
	DISABLE();
	if (!initialized) initialize();
	newp = dequeue(&freeQ);
	newp->function = function;
	newp->arg = arg;
	newp->next = NULL;
	if (setjmp(newp->context) == 1) {
		ENABLE();
		current->function(current->arg);
		DISABLE();
		enqueue(current, &freeQ);
		dispatch(dequeue(&readyQ));
	}

	SETSTACK(&newp->context, &newp->stack);
	enqueue(newp, &readyQ);
	ENABLE();
}

void yield(void) {
	/*Queue the current process and jump to the next one */
	DISABLE();
	enqueue(current, &readyQ);
	dispatch(dequeue(&readyQ));
	ENABLE();
}
void lock(mutex *m) {
	/*Locks and queues the currently running thread*/
	DISABLE();
	if(m->locked){
		enqueue(current,&m->waitQ);
		if(readyQ){
			dispatch(dequeue(&readyQ));
		}
	}else{
		m->locked = 1;
	}
	ENABLE();
}
void unlock(mutex *m) {
	/*Unlocks if queue is empty otherwise work on clearing queue*/
	DISABLE();
	if(m->waitQ){
		enqueue(current,&readyQ);
		dispatch(dequeue(&m->waitQ));
	}else{
		m->locked = 0;
	}

	ENABLE();
}	

ISR(PCINT1_vect){
    if(!(PINB & (0x1<<PINB7))){
        yield();
    }
}

static int count = 0;
int getCount(){
    return count;
}

void resetCount(){
    count = 0;
}

ISR(TIMER1_COMPA_vect){
    yield();
    count++;
}