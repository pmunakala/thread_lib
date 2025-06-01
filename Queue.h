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
#ifndef __QUEUE_H__
#define __QUEUE_H__

typedef struct queue_s
{
    void *data;
    struct queue_s *next;
} queue_t;

typedef struct Queue_head_s
{
    queue_t *elm;
    int count;
    int max_depth;
} queue_head_t;

queue_head_t *queue_init (queue_head_t *queue, int depth);

int enqueue (queue_head_t **pHead, void *elm);

int dequeue (queue_head_t **pHead, void *elm);

void *get_first_item (queue_head_t *pHead);
void *get_next_item (queue_head_t *pHead, void *element);
#endif
