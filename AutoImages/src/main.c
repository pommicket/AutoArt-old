#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"
#include "Matrix.h"
#include "Stack.h"
#include "StringFunctions.h"
#include "Random.h"


#define FUNCTION_LENGTH 20



double chanceEnd(int length)
{
    return 2.0/(1+exp(-(double)length/FUNCTION_LENGTH))-1;
}


char* randFunction()
{
    char* function;
    int hasX = 0;
    int hasY = 0;
    int operation;
    int numbersOnStack;
    int i;
    while (!(hasX && hasY))
    {
        function = "x ";
        hasX = 0;
        hasY = 0;
        numbersOnStack = 1;
        for (i = 0; i < FUNCTION_LENGTH; i++)
        {
            if (numbersOnStack > 1)
                operation = randrange(0, 9);
            else
                operation = randrange(0, 6);
            switch (operation)
            {
            case 0:
                function = add(function, "x ");
                hasX = 1;
                numbersOnStack++;
                break;
            case 1:
                function = add(function, "y ");
                hasY = 1;
                numbersOnStack++;
                break;
            case 2:
                function = add(function, numberSpace(randrange(0, 200)));
                numbersOnStack++;
                break;
            case 3:
                function = add(function, "sqrt ");
                break;
            case 4:
                function = add(function, "cos ");
                break;
            case 5:
                function = add(function, "sin ");
                break;
            case 6:
                function = add(function, "+ ");
                numbersOnStack--;
                break;
            case 7:
                function = add(function, "- ");
                numbersOnStack--;
                break;
            case 8:
                function = add(function, "* ");
                numbersOnStack--;
                break;

            }
        }
        while (numbersOnStack-- > 1)
        {
            operation = randrange(0, 3);
            switch(operation)
            {
            case 0:
                function = add(function, "+ ");
                break;
            case 1:
                function = add(function, "- ");
                break;
            case 2:
                function = add(function, "* ");
                break;
            }
        }

    }
    return function;

}

matrix* evalFunction(char* function, int width, int height)
{
    matrix* x = matrix_alloc(width, height);
    matrix* y = matrix_alloc(width, height);
    int i, j;

    for (i = 0; i < x->size1; i++)
    {
        for (j = 0; j < x->size2; j++)
        {
            x->array[i][j] = i;
            y->array[i][j] = j;
        }
    }

    Stack* stack = createStack();
    char* token;
    token = strtok(function, " ");
    while (token != NULL)
    {
        if (strlen(token) == 0)
        {
            token = strtok(NULL, " ");
            continue;
        }

        if (strEquals(token, "x"))
            push(stack, cpy_matrix(x));
        else if (strEquals(token, "y"))
            push(stack, cpy_matrix(y));
        else if (strEquals(token, "sin"))
            push(stack, sin_matrix(pop(stack)));
        else if (strEquals(token, "cos"))
            push(stack, cos_matrix(pop(stack)));
        else if (strEquals(token, "sqrt"))
            push(stack, sqrt_matrix(pop(stack)));
        else if (strEquals(token, "+"))
        {
            matrix* a = pop(stack);
            matrix* b = pop(stack);
            if (a->size1 == 1 && a->size2 == 1 && !(b->size1 == 1 && b->size2 == 1))
            {
                matrix_add_constant(b, a->array[0][0]);
                push(stack, b);
            }
            else if (!(a->size1 == 1 && a->size2 == 1) && b->size1 == 1 && b->size2 == 1)
            {
                matrix_add_constant(a, b->array[0][0]);
                push(stack, a);
            }
            else
            {
                matrix_add(a, b);
                push(stack, a);
            }
        }
        else if (strEquals(token, "-"))
        {
            matrix* a = pop(stack);
            matrix* b = pop(stack);
            if (a->size1 == 1 && a->size2 == 1 && !(b->size1 == 1 && b->size2 == 1))
            {
                matrix_add_constant(b, -a->array[0][0]);
                push(stack, b);
            }
            else if (!(a->size1 == 1 && a->size2 == 1) && b->size1 == 1 && b->size2 == 1)
            {
                matrix_add_constant(a, -b->array[0][0]);
                push(stack, a);
            }
            else
            {
                matrix_sub(a, b);
                push(stack, a);
            }
        }
        else if (strEquals(token, "*"))
        {
            matrix* a = pop(stack);
            matrix* b = pop(stack);
            if (a->size1 == 1 && a->size2 == 1 && !(b->size1 == 1 && b->size2 == 1))
            {
                matrix_scale(b, a->array[0][0]);
                push(stack, b);
            }
            else if (!(a->size1 == 1 && a->size2 == 1) && b->size1 == 1 && b->size2 == 1)
            {
                matrix_scale(a, b->array[0][0]);
                push(stack, a);
            }
            else
            {
                matrix_mul_elements(a, b);
                push(stack, a);
            }
        }
        else
        {
            matrix* m = matrix_alloc(1, 1);
            m->array[0][0] = atof(token);
            push(stack, m);
        }

        token = strtok(NULL, " ");
    }
    
    printf("This should be 77: %d\n", x->array[77][21]);
	printf("This should be 27: %d\n", y->array[77][27]);
    return pop(stack);
}

void createImage(char* name, int width, int height)
{
    int i, j;
    unsigned char* img;

    matrix* r;
    matrix* g;
    matrix* b;

    char* rfunction = randFunction();
    char* gfunction = randFunction();
    char* bfunction = randFunction();
    printf("%s\n%s\n%s\n", rfunction, gfunction, bfunction);
    r = mod256(evalFunction(rfunction, width, height));
    g = mod256(evalFunction(gfunction, width, height));
    b = mod256(evalFunction(bfunction, width, height));
    img = malloc(width*height*4);

    for (i = 0; i < width*height; i++)
    {
        img[4*i]   = (unsigned char)r->array[i/height][i%height];
        img[4*i+1] = (unsigned char)g->array[i/height][i%height];
        img[4*i+2] = (unsigned char)b->array[i/height][i%height];
        img[4*i+3] = 255;
    }
    stbi_write_png(name, width, height, 4, img, 0);
    stbi_image_free(img);
}

char* imgX(int i, int q)
{
    char* str = malloc(256);
    sprintf(str, "%d%d.png", q, i);
    return str;
}

int main()
{
    srand(time(NULL));
    int w, h, n, q, i;

    printf("Width (1440 is recommended): ");
    scanf("%d", &w);
    printf("Height (900 is recommended): ");
    scanf("%d", &h);
    printf("Number (5 is recommended): ");
    scanf("%d", &n);

    q = rand();
    for (i = 0; i < n; i++)
    {
        printf("---------------%d/%d---------------\n", i, n);
        createImage(imgX(i, q), w, h);
    }
    return 0;
}
