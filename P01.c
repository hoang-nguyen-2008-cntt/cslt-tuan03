#include <stdio.h>

long long sumOfSquares(int n)
{
    long long sum = 0;

    for (int i = 1; i <= n; i++)
    {
        sum += (long long)i * i;
    }

    return sum;
}

int checkInt(int testNo, long long expected, long long actual)
{
    if (expected == actual)
    {
        printf("Test %d: PASS\n", testNo);
        return 1;
    }

    printf("Test %d: FAIL (expected %lld, got %lld)\n",
           testNo, expected, actual);
    return 0;
}

int main(void)
{
    int passed = 0;

    passed += checkInt(1, 55, sumOfSquares(5));
    passed += checkInt(2, 0, sumOfSquares(0));
    passed += checkInt(3, 1, sumOfSquares(1));
    passed += checkInt(4, 385, sumOfSquares(10));

    printf("Passed %d/4\n", passed);

    return 0;
}
