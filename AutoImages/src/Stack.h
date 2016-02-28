typedef struct Stack
{
    matrix** array;
    int index;
    int capacity;
} Stack;

Stack* createStack()
{
    Stack* p = malloc(sizeof(Stack));
    p->index = 0;
    p->capacity = 0;
    p->array = NULL;
    return p;
}

void resize(Stack* s, int newSize)
{
    if (newSize == 0)
        newSize = 1;
    matrix** oldArray = s->array;
    s->array = malloc(newSize * sizeof(matrix*));
    int i;
    for (i = 0; i < s->capacity; i++)
        s->array[i] = oldArray[i];
    s->capacity = newSize;
}

void push(Stack* s, matrix* value)
{
    if (s->index >= s->capacity)
        resize(s, s->capacity*2);

    s->array[s->index++] = value;
}

matrix* pop(Stack* s)
{
    return s->array[--s->index];
}
