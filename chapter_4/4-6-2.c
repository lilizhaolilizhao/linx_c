//
// Created by oneapm on 2019-08-12.
//

extern A;
long power(int n)
{
    long total = 1;
    int i;
    for(i=1;i<=n;i++)
        total = total * A;
    return total;
}

