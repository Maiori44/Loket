#ifndef DYNSTACK
#define DYNSTACK

#define ITERATE_STACK(stack) for (int i = 0; i < stack->pos; i++)
#define ITERATE_STACK_BACKWARDS(stack) for (int i = stack->pos - 1; i >= 0; i--)

typedef struct {
	int *stack;
	unsigned int pos;
	unsigned int size;
} dynstack;

dynstack *newstack(unsigned int size);
void reallocstack(dynstack *stack);
void pushstack(dynstack *stack, int n);
void pushstack(dynstack *stack, int n);
int popstack(dynstack *stack);
int peekstack(dynstack *stack);
void freestack(dynstack *stack);
void printstack(dynstack *stack);

#endif