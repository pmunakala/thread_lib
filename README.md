#MyThread: A Lightweight User-Level Threading Library in C

This project implements a simple, cooperative, user-level threading library using the classic `ucontext` API.

Create lightweight threads  
Switch contexts without kernel threads  
Manage run queues and wait queues  Explore core OS scheduling concepts

---

## Features

- User-level threads (green threads)
- Cooperative scheduling (explicit yield/sleep)
- `mythread_create`: spawn threads
- `mythread_sleep`: put threads to sleep
- `mythread_wakeup`: resume sleeping threads
- `mythread_exit`: terminate threads
- Run and wait queues to manage thread states

---

## How It Works

- Threads are implemented with their own stack and `ucontext_t`.
- A scheduler loop iterates over runnable threads and switches context.
- Threads yield voluntarily using sleep or exit.
- No preemption or OS-managed scheduling — **you control everything**.

---

 ## Build

```bash
make 

## Run
echo LD_LIBRARY_PATH=./ 
./DemoApp
