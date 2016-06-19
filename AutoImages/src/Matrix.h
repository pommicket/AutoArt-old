typedef struct
{
    int size1;
    int size2;
    int** array;
}
matrix;

matrix* matrix_alloc(int size1, int size2)
{
    matrix* m = malloc(sizeof(matrix));
    m->size1 = size1;
    m->size2 = size2;
    m->array = malloc(size1*size2*sizeof(int));
    int i;
    for (i = 0; i < size1; i++)
        m->array[i] = malloc(size2*sizeof(int));
    return m;
}

matrix* cpy_matrix(matrix* m)
{
	matrix* cpy = matrix_alloc(m->size1, m->size2);
	int i, j;
	for (i = 0; i < m->size1; i++)
		for (j = 0; j < m->size2; j++)
			cpy->array[i][j] = m->array[i][j];
	return cpy;
}

matrix* sin_matrix(matrix* m)
{
    int i, j;
    for (i = 0; i < m->size1; i++)
        for (j = 0; j < m->size2; j++)
            m->array[i][j] = 255*sin((double)m->array[i][j]);
    return m;
}

matrix* cos_matrix(matrix* m)
{
    int i, j;
    for (i = 0; i < m->size1; i++)
        for (j = 0; j < m->size2; j++)
            m->array[i][j] = 255*cos((double)m->array[i][j]);
    return m;
}

matrix* sqrt_matrix(matrix* m)
{
    int i, j;
    for (i = 0; i < m->size1; i++)
        for (j = 0; j < m->size2; j++)
            m->array[i][j] = (int)sqrt((double)m->array[i][j]);
    return m;

}

void matrix_add(matrix* m1, matrix* m2)
{
    int i, j;
    for (i = 0; i < m1->size1; i++)
        for (j = 0; j < m1->size2; j++)
            m1->array[i][j] += m2->array[i][j];

}

void matrix_sub(matrix* m1, matrix* m2)
{
    int i, j;
    for (i = 0; i < m1->size1; i++)
        for (j = 0; j < m1->size2; j++)
            m1->array[i][j] -= m2->array[i][j];

}

void matrix_add_constant(matrix* m, int c)
{
    int i, j;
    for (i = 0; i < m->size1; i++)
        for (j = 0; j < m->size2; j++)
            m->array[i][j] += c;
}

void matrix_mul_elements(matrix* m1, matrix* m2)
{
    int i, j;
    for (i = 0; i < m1->size1; i++)
        for (j = 0; j < m1->size2; j++)
            m1->array[i][j] *= m2->array[i][j];

}

void matrix_scale(matrix* m, int c)
{
    int i, j;
    for (i = 0; i < m->size1; i++)
        for (j = 0; j < m->size2; j++)
            m->array[i][j] *= c;
}


matrix* mod256(matrix* m)
{
    int i, j;
    for (i = 0; i < m->size1; i++)
        for (j = 0; j < m->size2; j++)
            m->array[i][j] %= 256;
    return m;
}
