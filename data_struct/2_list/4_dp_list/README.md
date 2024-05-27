## README

#### 创建memory file 方法:

`dd if=/dev/zero of=4k_mem_file bs=1k count=4`

dd 转换和复制文件工具
if 指定输入文件
of 输出文件
bs 块大小 block size
count 复制n个块

`1. chmod +x start_app.sh`

`2. ./start_app.sh`

#### 查看文件信息内容
`xxd -l 200 4k_mem_file`

