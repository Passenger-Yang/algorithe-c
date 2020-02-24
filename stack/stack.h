/* stack.h */
#ifndef STACK_H
#define STACK_H
#include <stdlib.h>
#include </home/demon/C-proj/Algorithe/linkList/list.h>

//Implement stacks as linked list
typedef List Stack;

//pubilc interface
#define stack_init 		list_init
#define stack_destroy	list_destroy

int stack_push(Stack *stack, const void *data);
int stack_pop(Stack *stack, void **data);

//get the top element of the stack
#define stack_peek	((stack)->head == NULL ? NULL : (stack)->head->data)

#define stack_size	list_size

#endif


