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


#### app start

1. main中调用db_list_app
2. 函数从db_list_app入口
3. 初始化:
    在db_conf.h中修改配置信息
    USE_INIT_MEMORY_SECTOR = 1,程序会清除4k_mem_file的信息;执行./start_app.sh
4. 进行add/del/select测试
    add测试: 
        USE_INIT_MEMORY_SECTOR = 0, USE_ADD_TEST = 1, USE_DEL_TEST = 0, USE_SELECT_TEST = 0, 
        执行./start_app.sh;
    
    del测试: 
        USE_INIT_MEMORY_SECTOR = 0, USE_ADD_TEST = 0, USE_DEL_TEST = 1, USE_SELECT_TEST = 0,
        执行./start_app.sh;
    
    select测试:
        USE_INIT_MEMORY_SECTOR = 0, USE_ADD_TEST = 0, USE_DEL_TEST = 0, USE_SELECT_TEST = 0,
        执行./start_app.sh;
