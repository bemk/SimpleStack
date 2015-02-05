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

#include <stdlib.h>
#include <string.h>
#include "stack.h"

struct stack_node {
        void* data;
        struct stack_node* next;
};

struct stack* init_stack(void* root_node)
{
        if (root_node == NULL) {
                return NULL;
        }
        struct stack* stack = malloc(sizeof(*stack));
        if (stack == NULL) {
                return stack;
        }

        memset((void*) stack, 0, sizeof(*stack));

#ifdef MULTITHREAD
        pthread_mutex_init(&stack->mutex, NULL);
        pthread_mutex_unlock(&stack->mutex);
#endif

        stack->root = malloc(sizeof(*(stack->root)));
        stack->top = stack->root;
        memset((void*) stack->top, 0, sizeof(*(stack->top)));
        stack->top->data = root_node;

        stack->depth = 1;

        return stack;
}

int16_t push_node(struct stack* stack, void* data)
{
        if (data == NULL) {
                return STACK_ILLEGAL_DATA;
        }
        if (stack == NULL) {
                return STACK_ILLEGAL_STACK;
        }

#ifdef MULTITHREAD
        pthread_mutex_lock(&stack->mutex);
#endif
        struct stack_node* node = malloc(sizeof(*node));
        if (node == NULL)
                goto cleanup;

        stack->depth++;
        memset((void*) node, 0, sizeof(*node));

        node->data = data;
        node->next = stack->top;
        stack->top = node;

        cleanup:
#ifdef MULTITHREAD
        pthread_mutex_unlock(&stack->mutex);
#endif

        return STACK_SUCCESS;
}

void* pop_node(struct stack* stack)
{
        if (stack->top == stack->root) {
                return NULL;
        }

#ifdef MULTITHREAD
        pthread_mutex_lock(&stack->mutex);
#endif

        void* ret = stack->top->data;
        stack->depth--;

        struct stack_node* top = stack->top;
        stack->top = top->next;
        memset(top, 0, sizeof(*top));

        free(top);

#ifdef MULTITHREAD
        pthread_mutex_unlock(&stack->mutex);
#endif

        return ret;
}

void* peek_node(struct stack* stack)
{
        if (stack == NULL) {
                return NULL;
        }
#ifdef MULTITHREAD
        pthread_mutex_lock(&stack->mutex);
#endif

        void* data = stack->top->data;

#ifdef MULTITHREAD
        pthread_mutex_unlock(&stack->mutex);
#endif

        return data;
}

void unwind_stack(struct stack* stack)
{
        if (stack == NULL) {
                return;
        }
#ifdef MULTITHREAD
        pthread_mutex_lock(&stack->mutex);
#endif

        void* data = NULL;
        do {
                data = pop_node(stack);
        } while (data != NULL);

#ifdef MULTITHREAD
        pthread_mutex_unlock(&stack->mutex);
#endif

        return;
}

void trace_stack(struct stack* stack, void (*fn)(void* data))
{
        if (stack == NULL || fn == NULL) {
                return;
        }
#ifdef MULTITHREAD
        pthread_mutex_lock(&stack->mutex);
#endif

        struct stack_node* runner = stack->top;
        while (runner != NULL) {
                fn(runner->data);

                runner = runner->next;
        }

#ifdef MULTITHREAD
        pthread_mutex_unlock(&stack->mutex);
#endif

        return;
}
