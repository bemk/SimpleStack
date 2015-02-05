/*

Copyright (c) 2015, Bart Kuivenhoven
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the original author nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL BART KUIVENHOVEN BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef STACK_H_
#define STACK_H_

#include <stdlib.h>

#define MULTITHREAD
#ifdef MULTITHREAD
#include <pthread.h>
#endif


#define STACK_SUCCESS           0
#define STACK_ILLEGAL_DATA     -1
#define STACK_ILLEGAL_STACK    -2

struct stack_node;

struct stack {
        struct stack_node* root;
        struct stack_node* top;

#ifdef MULTITHREAD
        pthread_mutex_t mutex;
#endif

        int16_t depth;
};

struct stack* init_stack(void* root_node);
int16_t push_node(struct stack* stack, void* data);
void* pop_node(struct stack* stack);
void* peek_node(struct stack* stack);
void unwind_stack(struct stack* stack);
void trace_stack(struct stack* stack, void (*fn)(void* data));


#endif /* STACK_H_ */
