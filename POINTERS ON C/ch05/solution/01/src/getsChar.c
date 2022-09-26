#include <stdio.h>
#include <stdlib.h>

void func()
{
    char ch[50];
    scanf("%s", ch);

    for (int i = 0; ch[i] != '\0'; i++)
    {
        if (ch[i] >= 'A' && ch[i] <= 'Z')
        {
            ch[i] = ch[i] - 'A' + 'a';
        }
        else
        {
            continue;
        }
    }

    puts(ch);
    printf("%s\n", ch);
    return;
}

// input:
// QEIWUQAKN

// output:
// qeiwuqakn
void test()
{
    func();
    return;
}

int main()
{
    test();
    return 0;
}