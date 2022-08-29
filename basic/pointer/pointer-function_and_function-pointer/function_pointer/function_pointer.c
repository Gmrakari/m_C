#include <stdio.h>

/*
** 函数指针:是指向函数的指针变量，即本质是一个指针变量
** 定义为: 类型说明符 （*函数名)(参数),例如:int (*p)(int x)
** int (*p)(int x) 声明一个函数指针
** // 把函数的地址赋值给函数指针，可以采用下面两种方式:
** p = func;  将func函数的首地址赋给指针p
** p = &func; 取地址运算符&不是必须的，因为单单一个函数标识符号就表示了它的地址
**
** 可以采用如下两种方式来通过指针调用函数
** x = (*p)();
** x= p();  //这两种格式看上去和函数调用无异，但是有些程序员倾向于第一种格式，因为它明确指出通过指针而非函数名来调用函数
**
*/

void (*funcp)();
void FileFunc(), EditFunc();

int main(int argc, char const *argv[])
{

    /* code */
    funcp = FileFunc;
    (*funcp)();

    funcp = EditFunc;
    (*funcp)();

    return 0;
}

void FileFunc()
{
    printf("FileFunc\r\n");
}

void EditFunc()
{
    printf("EditFunc\r\n");
}