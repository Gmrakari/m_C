
一、上电检查主数据有效性
1. 检查主数据src_data_sector是否有效
	 a. 读取主数据区，检查crc校验码  （从flash数据加载到内存， 检查主分区和备份分区)
	 b. 如果crc校验通过，认为数据有效
	 c. 否则，数据已经损坏，需要从备份区恢复

2. 从备份区恢复数据
	a. 检查备份区
		1).读取crc校验
		2).如果crc有效，从备份区恢复数据到src_data_sector
		3).备份区1有效，从有效备份区恢复数据
		4).备份区都无效，清空数据（清空备份分区数据和主扇区数据),重启
	b.恢复数据
		1). 将有效的备份区复制到主数据中
		2). 恢复后重新进行crc校验，确保恢复的数据是有效的

二、数据写入
1.主数据有效
	a.写入新的数据到主数据中
		2）.在备份成功之后，开始向主数据区src写入新数据
		1). 写入数据，计算crc校验码并保存

	b.写入备份区
		1). 在写入新的数据之前，先更新备份区，将主数据拷贝到bak1
		2). 确保备份区都成功备份，设置备份区的校验值
		3). 如果备份过程中发生断电，将从主数据区恢复
2.主数据无效
	a.从备份区恢复数据
		1). 将有效的备份内容恢复到src数据中
		2）. 恢复后进行crc校验，确保数据有效
	b. 写入主数据区
		1).数据从备份区恢复，直接向主数据中写入新的数据，并且更新标志位和crc校验
	c. 更新备份区
		1). 写入完成之后，将src数据备份到bak1中
		2). 备份区更新成功

```C
// crc32
int cal_crc32(const uint8_t *data, int length, uint32_t *o_crc)
{
    if (!data || !o_crc) {
        printf("[%s][%d]invalid in param!\r\n", __func__, __LINE__);
        return -1;
    }

    uint32_t crc = 0xFFFFFFFF;
    for (int i = 0; i < length; i++) {
        crc ^= data[i];
        for (int j = 0; j < 8; j++) {
            if (crc & 0x01) {
                crc = (crc >> 1) ^ 0xEDB88320;
            } else {
                crc >>= 1;
            }
        }
    }

    *o_crc = crc ^ 0xFFFFFFFF;

    return 0;
}
```

linux下查看文件hex信息
xxd -l bytes_num filename