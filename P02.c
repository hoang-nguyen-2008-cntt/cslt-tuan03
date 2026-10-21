#include <stdio.h>

int countDivisors(int n)
{
    int count = 0;

    for (int i = 1; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            if (i * i == n)
                count++;
            else
                count += 2;
        }
    }

    return count;
}

int checkInt(int testNo, int expected, int actual)
{
    if (expected == actual)
    {
        printf("Test %d: PASS\n", testNo);
        return 1;
    }

    printf("Test %d: FAIL (expected %d, got %d)\n",
           testNo, expected, actual);
    return 0;
}

int main(void)
{
    int passed = 0;

    passed += checkInt(1, 4, countDivisors(6));
    passed += checkInt(2, 1, countDivisors(1));
    passed += checkInt(3, 5, countDivisors(16));
    passed += checkInt(4, 6, countDivisors(12));

    printf("Passed %d/4 tests\n", passed);

    return 0;
}