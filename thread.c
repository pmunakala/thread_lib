/*
 * MIT License
 * 
 * Copyright (c) 2025 PRadeep Kumar Munakala
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include<time.h>
#include<signal.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<ucontext.h>
#include<stdarg.h>
#include "Queue.h"
#include "thread.h"

extern ucontext_t uctx_main;
extern queue_head_t *run_queue_thread;
extern queue_head_t *wait_queue_thread;

void mythread_sleep (mythread_id_t idx)
{

    void *data;
    mythread_t *t1;

    t1 = get_first_item(run_queue_thread);

    if (t1->id == idx) {
        dequeue(&run_queue_thread, t1);
        enqueue(&wait_queue_thread, t1);
        t1->state = THREAD_SLEEP;
        swapcontext(&t1->contxt, &uctx_main);
    } else {
        while (t1 = get_next_item(run_queue_thread, t1)) {
            if (t1->id == idx) {
                dequeue(&run_queue_thread, t1);
                enqueue(&wait_queue_thread, t1);
                t1->state = THREAD_SLEEP;
                swapcontext(&t1->contxt, &uctx_main);
                break;
            }
        }
    }
}

void mythread_wakeup (mythread_id_t idx)
{
    void *data;
    mythread_t *t1;

    t1 = get_first_item(wait_queue_thread);

    if (!t1) {
        return;
    }

    if (!is_mythread_sleeping(t1)) {
        return;
    }
    
    if (t1->id == idx) {
        dequeue(&wait_queue_thread, t1);
        enqueue(&run_queue_thread, t1);
        t1->state = THREAD_SUSPEND;
    } else {
        while (t1 = get_next_item(run_queue_thread, t1)) {
            if (t1->id == idx) {
                dequeue(&wait_queue_thread, t1);
                enqueue(&run_queue_thread, t1);
                t1->state = THREAD_SUSPEND;
                break;
            }
        }
    }
}

void mythread_exit (mythread_id_t idx)
{
    void *data;
    mythread_t *t1;

    t1 = get_first_item(run_queue_thread);
    if (t1->id == idx) {
        dequeue(&run_queue_thread, t1);
        swapcontext(&t1->contxt, &uctx_main);
    } else {
        while (t1 = get_next_item(run_queue_thread, t1)) {
            if (t1->id == idx) {
                dequeue(&run_queue_thread, t1);
                swapcontext(&t1->contxt, &uctx_main);
                break;
            }
        }
   }
}

void thread_wrapper (void *arg)
{
    mythread_t *thd = arg;
    thd->thread_func();
    mythread_exit(thd->id);
}

/*
 * This is a constructer funtction which will be invoked before main.
 */
void init_mythread_lib ()
{
    printf("My thread called");
    run_queue_thread = queue_init(run_queue_thread, 10);
    wait_queue_thread = queue_init(wait_queue_thread, 10);
}

mythread_id_t mythread_create (mythread_t *thread1, void (*func)(void))
{

    static int thread_id = 1;
    mythread_t *thread = NULL;

    thread = (mythread_t *)malloc(sizeof(mythread_t));

    if (getcontext(&thread->contxt) == -1) {
        printf("Create: Unable to get context\n");
        return -1;
    }
    
    thread->thread_func = func;
    thread->id = thread_id++;
    thread->state = THREAD_SUSPEND;
    printf("thread->id %d\n", thread->id);
    thread->contxt.uc_stack.ss_sp = malloc(8192);
    thread->contxt.uc_stack.ss_size = 8192;

    makecontext(&thread->contxt,(void (*)(void))thread_wrapper,1, thread);
    enqueue(&run_queue_thread, thread);

    return thread->id;
}

void scheduler_run (void) { 

    mythread_t *th1;
    getcontext(&uctx_main);

    while(1) {
        if (run_queue_thread) {
            th1 = get_first_item(run_queue_thread);
            while(th1) {
                schedule_nexttask(th1);
                th1 = get_next_item(run_queue_thread, th1);
            }
        }
    }   
}
