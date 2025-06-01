#
# MIT License
# 
# Copyright (c) 2025 PRadeep Kumar Munakala
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#/


OBJS += Queue.o thread.o

SHARED_LIB := mythread.so

DEMO_APP := DemoApp

CFLAGS = -g -fpic
CC    =  gcc 

all: $(SHARED_LIB) $(DEMO_APP)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

    
$(SHARED_LIB): $(OBJS)
	$(CC) -shared $(OBJS) -o libmythread.so 

APP_OBJS += main.o

$(DEMO_APP): $(SHARED_LIB) $(APP_OBJS)
	$(CC) -o $(DEMO_APP) $(APP_OBJS) -L./ -lmythread

.PHONY: $(SHARED_LIB) $(DEMO_APP)
	 
clean:
	rm *.o *.so $(DEMO_APP)
