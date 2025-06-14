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

#include <stdio.h>
#include <unistd.h>
#include "thread.h"

mythread_id_t t_id1, t_id2;

void thread_a (void)
{
	while (1) {
		printf("%s executing\n", __func__);
		mythread_suspend(t_id1);
		sleep(1);
		
       }
}
void thread_b (void)
{

	while (1) {
		printf("%s executing\n", __func__);
		mythread_suspend(t_id2);
		sleep(1);
        }
}

int main (void)
{ 
    t_id1 = mythread_create(NULL, thread_a);
    t_id2 = mythread_create(NULL, thread_b);
    scheduler_run();
	
}

