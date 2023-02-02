#include <stdio.h>
#include <time.h>

void delay(double dly)
{
    /* save start time */
    const time_t start = time(NULL);

    time_t current;
    do
    {
        /* get current time */
        time(&current);

        /* break loop when the requested number of seconds have elapsed */
    } while (difftime(current, start) < dly);
}

int last_x;
int last_y;

static int cnt = 0;
void func(int x, int y)
{
    int m_x = 2;
    int m_y = 3;
    int flag = 1;

    if (m_x != x && m_y != y && flag == 1)
    {
        delay(10);
        if (m_x != x && m_y != y && flag == 1)
        {
            last_x = m_x;
            last_y = m_y;

            printf("test 01\r\n");
        }

        while (flag)
        {
            cnt++;
            if (cnt > 50)
                break;
        }
    }
    else
    {
        flag = 0;
    }

    if (cnt % 50 == 0)
    {
        printf("test2\r\n");
    }
}

void test2() {
    char arr[] = "abc";
    printf("%ld\r\n", sizeof(arr));
}

int main()
{
    // int x = 1;
    // int y = 0;
    // func(x, y);
    test2();
}