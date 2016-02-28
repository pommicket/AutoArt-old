double rand01()
{
    return (double)rand() / RAND_MAX;
}

int randrange(int start, int end)
{
    return (int)(rand01()*(end-start)) + start;
}
