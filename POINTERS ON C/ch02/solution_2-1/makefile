
# 预处理:处理#include,#define,#ifdef等宏命令
# 编译:把预处理完的文件编译为会汇编程序.s
# 汇编:把汇编程序.s编译为.o二进制文件
# 链接:把多个二进制文件.o集合(链接)成一个可执行文件


# 目标文件名
target = app

# 编译器
CC = gcc

# 编译参数 打印出gcc提供的警告信息
CFLAG = -Wall

# 编译包含的头文件所在目录
include = -I./

# 所有用到的源文件
src = $(wildcard ./*.c)

# 把源文件src字符串的后缀.c 改为.o
obj = $(patsubst ./%.c, ./%.o, $(src))

$(target) : $(obj)
	$(CC) $^ -o $@

# 重定义隐藏规则，匹配上述目标
%.o : %.CC
	$(CC) -c $(include) $(CFLAG) $< -o $@

# 清空除源文件外的所有生成文件
.PHONY:clean
clean:
	rm $(obj) $(target) -f
