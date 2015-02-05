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
#include <stdio.h>
#include "stack.h"

char* text[] = { "hello", "world", "how", "are", "you", "doing" };

static void trace(void* data)
{
        printf("%s\n", (char*)data);
}

int main(int argc, char** argv)
{
        struct stack* stack = init_stack(text[5]);

        push_node(stack, text[4]);
        push_node(stack, text[3]);
        push_node(stack, text[2]);
        push_node(stack, text[1]);
        push_node(stack, text[0]);

        printf("\ntest 1\n\n");
        trace_stack(stack, trace);

        unwind_stack(stack);

        push_node(stack, text[0]);
        push_node(stack, text[1]);
        push_node(stack, text[2]);
        push_node(stack, text[3]);
        push_node(stack, text[4]);
        push_node(stack, text[5]);

        printf("\ntest 2\n\n");
        trace_stack(stack, trace);

        printf("\ntest 3\n\n");
        char* data = pop_node(stack);
        do {
                printf("%s\n", data);
                data = pop_node(stack);
        } while (data != NULL);

        printf("\ntest 4\n\n");
        printf("%s\n", (char*)peek_node(stack));

        fflush(stdout);

        return EXIT_SUCCESS;
}
