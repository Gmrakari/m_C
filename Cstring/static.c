#include <stdio.h>
static int cnt = 0;
void func() {
    //static int cnt;
    cnt++;
    printf("%d\n", cnt);
}



int main() {
    func();
    printf("%d\n", cnt);
}