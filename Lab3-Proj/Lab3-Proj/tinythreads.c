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

static int count = 0;

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
	
	initialized = 1;
}

void timerInit(void){
	//Timer things
	//Compare match
	TCCR1A |= (0x1 << COM1A1) | (0x1 << COM1A0);
	
	//Prescaler
	TCCR1B |= (0x1 << WGM12) | (0x1 << CS12) | (0x1 << CS10);
	
	//Enabling timer interrupts
	TIMSK1 |= (0x1 << OCIE1A);
	
	DISABLE();		//Disable interrupts as we just enabled them and dont want a interupt to occur while setting OCR1A and reseting the timer.
	
	OCR1A = 3906;	// (50*10^-2 * 8 * 10^6)/(1024)
	TCNT1 = 0;		//Clear Timer register
	ENABLE();
}


static void enqueue(thread p, thread *queue) {
	p->next = *queue;
	*queue = p;
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
	/* Creates new thread ?????? */
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
	yield();
	/* Runs the new thread ??*/
	
	ENABLE();
}

void yield(void) {
	/*Queue the current process and jump to the next one */
	DISABLE();
	thread t = dequeue(&readyQ);
	enqueue(current, &readyQ);
	dispatch(t);
	ENABLE();
}