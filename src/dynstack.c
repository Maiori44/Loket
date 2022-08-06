#include <stdlib.h>
#include <stdio.h>
#include "dynstack.h"

dynstack *newstack(unsigned int size) {
	dynstack *stack = malloc(sizeof(dynstack));
	stack->stack = malloc(sizeof(int) * size);
	stack->pos = 0;
	stack->size = size;
	return stack;
}

void reallocstack(dynstack *stack) {
	stack->size *= 1.5;
	stack->stack = realloc(stack->stack, sizeof(int) * stack->size);
}

void pushstack(dynstack *stack, int n) {
	if (stack->pos >= stack->size)
		reallocstack(stack);
	stack->stack[stack->pos++] = n;
}

int popstack(dynstack *stack) {
	if (stack->pos == 0)
		return -1;
	return stack->stack[--stack->pos];
}

int peekstack(dynstack *stack) {
	if (stack->pos == 0)
		return -1;
	return stack->stack[stack->pos - 1];
}

void freestack(dynstack *stack) {
	free(stack->stack);
	free(stack);
}

void printstack(dynstack *stack) {
	ITERATE_STACK(stack)
		printf("%d ", stack->stack[i]);
}