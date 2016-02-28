char* add(char* a, char* b)
{
    int aLen = strlen(a);
    int bLen = strlen(b);
    char* sum = malloc(aLen + bLen + 1);
    int i;
    for (i = 0; i < aLen; i++)
        sum[i] = a[i];
    for (i = aLen; i < aLen+bLen; i++)
        sum[i] = b[i-aLen];

    sum[aLen+bLen] = 0; //Null-terminate

    return sum;
}

char* numberSpace(int number)
{
    char* str = malloc(256);
    sprintf(str, "%d ", number);
    return str;
}

int strEquals(char* a, char* b)
{

    if (strlen(a) != strlen(b))
        return 0;

    int i;
    for (i = 0; i < strlen(a); i++)
        if (a[i] != b[i])
            return 0;
    return 1;
}

char* copy(char* a)
{
    char* s = malloc(strlen(a)+1);
    int i;
    for (i = 0; i < strlen(a); i++)
        s[i] = a[i];
    s[strlen(a)] = 0;
    return s;
}
