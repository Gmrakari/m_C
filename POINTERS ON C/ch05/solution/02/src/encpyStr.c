#include <stdio.h>

int encrypt(char ch, int base)
{
    ch -= base;
    ch += 13;
    ch %= 26;
    return ch;
}

int encrypt2(char ch)
{
    if (ch >= 'a' && ch <= 'z') 
        return 'a' + ((ch - 'a') + 13) % 26;
    else if (ch >= 'A' && ch <= 'Z')
        return 'A' + ((ch - 'A') + 13) % 26;
    else
        return ch;
}

void func()
{
    int ch;
    while ((ch = getchar()) != '\n')
    {
        if (ch >= 'A' && ch <= 'Z')
            ch = encrypt(ch, 'A');
        else if (ch >= 'a' && ch <= 'z')
            ch = encrypt(ch, 'a');
        else {
            putchar(ch);
        }
    }
    // putchar(ch);
}

void func2() {
    int ch;
    while ((ch = getchar()) && ch != '\n') {
        if (ch >= 'A' && ch <= 'Z' || ch >= 'a' && ch <= 'z') 
            putchar(encrypt2(ch));
        else
            putchar(ch);
    }
    printf("\n");
}

// test successful
// input:
// ADA
// output:
// NQN
void test()
{
    // func();
    func2();
    return;
}

int main()
{
    test();
    return 0;
}
