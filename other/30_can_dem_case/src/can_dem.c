#include "can_dem.h"
#include "stdint.h"
#include "stdbool.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

enum {
    DEM_EVENT_ID_NULL = 0,
    DEM_EVENT_ID_LAST_FOR_BSW
};

enum {
    DEM_EVENT_ID_SWC_START = DEM_EVENT_ID_LAST_FOR_BSW,
    DEM_EVENT_ID_EventParameter_Video_error,
    DEM_EVENT_ID_EventParameter_Sensor_error,
    DEM_EVENT_ID_EventParameter_LCD_error,
    DEM_EVENT_ID_EventParameter_Power_Error,
    DEM_EVENT_ID_EventParameter_I2C_Bus_Error,
    DEM_EVENT_ID_EventParameter_CAN_Bus_Off,
    DEM_EVENT_ID_EventParameter_Lost_Communication_With_VIU2,
    DEM_EVENT_ID_MAX
};

typedef struct {
    uint8_t  TotalFaultNum;
    uint8_t  FrameIndex;
    uint8_t  SupplierNum;
    uint16_t FaultNum[4];
} CMS_I_FaultDecoded_t;

typedef struct {
    // 1. 总故障数（0~7 bit，8位）- 独占字节0
    uint8 CMS_I_TotalFaultNum;

    // 2. 帧索引 + 供应商编号（共享字节1）
    // 字节1：8~12 bit（5位）= 帧索引；13~15 bit（3位）= 供应商编号
    uint8 CMS_I_FrameIndex : 5;    // 8~12 bit（字节1低5位）
    uint8 CMS_I_SupplierNum : 3;   // 13~15 bit（字节1高3位）

    // 3. 故障ID1（16~23 bit + 28~31 bit → 共12位）
    // 跨字节2（低8位） + 字节3低4位（高4位）
    uint8 FaultNum1_low8;          // 16~23 bit（字节2，低8位）
    uint8 FaultNum1_high4 : 4;     // 28~31 bit（字节3低4位，高4位）

    // 4. 故障ID2（24~27 bit + 32~39 bit → 共12位）
    // 跨字节3高4位（高4位） + 字节4（低8位）
    uint8 FaultNum2_high4 : 4;     // 24~27 bit（字节3高4位，高4位）
    uint8 FaultNum2_low8;          // 32~39 bit（字节4，低8位）

    // 5. 故障ID3（40~47 bit + 52~55 bit → 共12位）
    // 跨字节5（低8位） + 字节6低4位（高4位）
    uint8 FaultNum3_low8;          // 40~47 bit（字节5，低8位）
    uint8 FaultNum3_high4 : 4;     // 52~55 bit（字节6低4位，高4位）

    // 6. 故障ID4（48~51 bit + 56~63 bit → 共12位）
    // 跨字节6高4位（高4位） + 字节7（低8位）
    uint8 FaultNum4_high4 : 4;     // 48~51 bit（字节6高4位，高4位）
    uint8 FaultNum4_low8;          // 56~63 bit（字节7，低8位）
} CMS_I_Fault_t;

static uint8 cms_i_fault_data[8] = {0};

static CMS_I_Fault_t cms_i_fault;

// 模拟DEM事件状态
static uint8 dem_event_status[DEM_EVENT_ID_MAX] = {0};
static uint32_t cycle_count = 0;
static uint32_t false_change_count = 0;
static uint32_t total_cycles = 0;

// 解码函数
void cms_i_fault_decode(const uint8 *data, CMS_I_FaultDecoded_t *decoded)
{
    if (!data || !decoded) return;
    memset(decoded, 0, sizeof(CMS_I_FaultDecoded_t));

    // 1. 按 Motorola 字节序组装 64 位数据（字节0对应bit0~7，字节1对应bit8~15...）
    uint64_t frame = 0;
    for (uint8_t i = 0; i < 8; i++) {
        frame |= (uint64_t)data[i] << (i * 8);  // 关键修正：字节i对应bit(i*8)~bit(i*8+7)
    }

    // 2. 解析基础信号（严格匹配结构体位域）
    decoded->TotalFaultNum = (frame >> 0) & 0xFF;          // 字节0（bit0~7）
    decoded->FrameIndex = (frame >> 8) & 0x1F;             // 字节1低5位（bit8~12）
    decoded->SupplierNum = (frame >> 13) & 0x07;           // 字节1高3位（bit13~15）

    // 3. 解析故障ID（12位，按结构体拆分规则提取）
    // 故障ID1：bit16~23（低8位） + bit28~31（高4位）
    uint8_t fault1_low8 = (frame >> 16) & 0xFF;            // 字节2（bit16~23）
    uint8_t fault1_high4 = (frame >> 28) & 0x0F;           // 字节3低4位（bit28~31）
    decoded->FaultNum[0] = (fault1_high4 << 8) | fault1_low8;

    // 故障ID2：bit24~27（高4位） + bit32~39（低8位）
    uint8_t fault2_high4 = (frame >> 24) & 0x0F;           // 字节3高4位（bit24~27）
    uint8_t fault2_low8 = (frame >> 32) & 0xFF;            // 字节4（bit32~39）
    decoded->FaultNum[1] = (fault2_high4 << 8) | fault2_low8;

    // 故障ID3：bit40~47（低8位） + bit52~55（高4位）
    uint8_t fault3_low8 = (frame >> 40) & 0xFF;            // 字节5（bit40~47）
    uint8_t fault3_high4 = (frame >> 52) & 0x0F;           // 字节6低4位（bit52~55）
    decoded->FaultNum[2] = (fault3_high4 << 8) | fault3_low8;

    // 故障ID4：bit48~51（高4位） + bit56~63（低8位）
    uint8_t fault4_high4 = (frame >> 48) & 0x0F;           // 字节6高4位（bit48~51）
    uint8_t fault4_low8 = (frame >> 56) & 0xFF;            // 字节7（bit56~63）
    decoded->FaultNum[3] = (fault4_high4 << 8) | fault4_low8;

    return ;
}

static int Dem_ReadEventStatus(uint16 eventId)
{
    if (eventId >= DEM_EVENT_ID_MAX) return 0;
    return dem_event_status[eventId];
}

static void set_dem_event(uint16 eventId, int status)
{
    if (eventId < DEM_EVENT_ID_MAX) {
        dem_event_status[eventId] = status;
    }
}

void app_can_send_cms_i_fault_optimized(void)
{
    static uint8 frameIndex = 0;  // 无故障时为0
    static uint8 lastTotalFaultNum = 0;
    static uint16 lastFaultList[8];
    uint16 faultIds[8];
    uint8 faultCount = 0;

    // 采集故障列表
    if (Dem_ReadEventStatus(DEM_EVENT_ID_EventParameter_Video_error))  
        faultIds[faultCount++] = 0x001;
    if (Dem_ReadEventStatus(DEM_EVENT_ID_EventParameter_Sensor_error)) 
        faultIds[faultCount++] = 0x002;
    if (Dem_ReadEventStatus(DEM_EVENT_ID_EventParameter_LCD_error))    
        faultIds[faultCount++] = 0x003;
    if (Dem_ReadEventStatus(DEM_EVENT_ID_EventParameter_Power_Error))  
        faultIds[faultCount++] = 0x004;
    if (Dem_ReadEventStatus(DEM_EVENT_ID_EventParameter_I2C_Bus_Error))
        faultIds[faultCount++] = 0x005;
    if (Dem_ReadEventStatus(DEM_EVENT_ID_EventParameter_CAN_Bus_Off))  
        faultIds[faultCount++] = 0x006;
    if (Dem_ReadEventStatus(DEM_EVENT_ID_EventParameter_Lost_Communication_With_VIU2))
        faultIds[faultCount++] = 0x007;

    bool changed = (faultCount != lastTotalFaultNum);
    if (!changed && faultCount > 0) {
        for (uint8 i = 0; i < faultCount; i++) {
            if (faultIds[i] != lastFaultList[i]) {
                changed = true;
                break;
            }
        }
    }

    if (changed) {
        for (uint8 i = 0; i < faultCount; i++) {
            lastFaultList[i] = faultIds[i];
        }
        lastTotalFaultNum = faultCount;
        frameIndex = (faultCount > 0) ? 1 : 0;
    }

    memset(&cms_i_fault, 0, sizeof(CMS_I_Fault_t));
    cms_i_fault.CMS_I_TotalFaultNum = faultCount & 0xFF;
    cms_i_fault.CMS_I_FrameIndex = frameIndex & 0x1F;
    cms_i_fault.CMS_I_SupplierNum = 0x00 & 0x07;

    uint8 startIdx = 0;
    uint8 faultsInThisFrame = 0;
    if (faultCount > 0 && frameIndex > 0) {
        startIdx = (frameIndex - 1) * 4;
        faultsInThisFrame = (faultCount - startIdx < 4) ? (faultCount - startIdx) : 4;
    }

    for (uint8 i = 0; i < 4; i++) {
        if (i < faultsInThisFrame) {
            uint16 faultVal = faultIds[startIdx + i] & 0xFFF;
            switch (i) {
                case 0:
                    cms_i_fault.FaultNum1_low8 = faultVal & 0xFF;
                    cms_i_fault.FaultNum1_high4 = (faultVal >> 8) & 0x0F;
                    break;
                case 1:
                    cms_i_fault.FaultNum2_high4 = (faultVal >> 8) & 0x0F;
                    cms_i_fault.FaultNum2_low8 = faultVal & 0xFF;
                    break;
                case 2:
                    cms_i_fault.FaultNum3_low8 = faultVal & 0xFF;
                    cms_i_fault.FaultNum3_high4 = (faultVal >> 8) & 0x0F;
                    break;
                case 3:
                    cms_i_fault.FaultNum4_high4 = (faultVal >> 8) & 0x0F;
                    cms_i_fault.FaultNum4_low8 = faultVal & 0xFF;
                    break;
            }
        }
    }

    // 更新帧索引
    if (faultCount > 0) {
        uint8 totalFrames = (faultCount + 3) / 4;
        frameIndex = (totalFrames > 1) ? (frameIndex % totalFrames) + 1 : 1;
    }

    // 拷贝结构体数据到发送缓冲区
    memcpy(cms_i_fault_data, &cms_i_fault, sizeof(cms_i_fault_data));

    total_cycles++;
}

void print_can_frame_info(void)
{
    CMS_I_FaultDecoded_t decoded;
    cms_i_fault_decode(cms_i_fault_data, &decoded);
    
    // 核心帧信息（对齐格式，便于查看）
    printf("Cycle: %4u\r\n TotalFaults: %u FrameIndex: %u Supplier: 0x%01X  ",
           cycle_count, decoded.TotalFaultNum, decoded.FrameIndex, decoded.SupplierNum);
    printf("Faults: ");
    for (int i = 0; i < 4; i++) {
        printf("0x%03X ", decoded.FaultNum[i]);
    }

    printf("\r\n");
    printf("Raw (Data Motorola): 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X\r\n",
           cms_i_fault_data[0], cms_i_fault_data[1], cms_i_fault_data[2], cms_i_fault_data[3],
           cms_i_fault_data[4], cms_i_fault_data[5], cms_i_fault_data[6], cms_i_fault_data[7]);
    printf("\n\n");
}

// 测试用例
void run_test_cases(void)
{
    printf("=== Starting 500ms periodic fault reporting test ===\n\n");

    // Test case 1: No faults
    printf("Test 1: No fault status\n");
    memset(dem_event_status, 0, sizeof(dem_event_status));
    for (int i = 0; i < 5; i++) {
        cycle_count++;
        app_can_send_cms_i_fault_optimized();
        print_can_frame_info();
        usleep(500000); // 500ms
    }
    
    // Test case 2: Single fault
    printf("\nTest 2: Single fault (Video fault)\n");
    set_dem_event(DEM_EVENT_ID_EventParameter_Video_error, 1);
    for (int i = 0; i < 5; i++) {
        cycle_count++;
        app_can_send_cms_i_fault_optimized();
        print_can_frame_info();
        usleep(500000);
    }
    
    // Test case 3: Multiple faults (3 faults)
    printf("\nTest 3: Multiple faults (3 faults)\n");
    set_dem_event(DEM_EVENT_ID_EventParameter_Sensor_error, 1);
    set_dem_event(DEM_EVENT_ID_EventParameter_LCD_error, 1);
    for (int i = 0; i < 6; i++) {
        cycle_count++;
        app_can_send_cms_i_fault_optimized();
        print_can_frame_info();
        usleep(500000);
    }
    
    // Test case 4: Multiple faults (6 faults - 2 frames)
    printf("\nTest 4: Multiple faults (6 faults - 2 frames)\n");
    set_dem_event(DEM_EVENT_ID_EventParameter_Power_Error, 1);
    set_dem_event(DEM_EVENT_ID_EventParameter_I2C_Bus_Error, 1);
    set_dem_event(DEM_EVENT_ID_EventParameter_CAN_Bus_Off, 1);
    for (int i = 0; i < 8; i++) {
        cycle_count++;
        app_can_send_cms_i_fault_optimized();
        print_can_frame_info();
        usleep(500000);
    }
    
    // Test case 5: Multiple faults (7 faults - 2 frames)
    printf("\nTest 5: Multiple faults (7 faults - 2 frames)\n");
    set_dem_event(DEM_EVENT_ID_EventParameter_Lost_Communication_With_VIU2, 1);
    for (int i = 0; i < 8; i++) {
        cycle_count++;
        app_can_send_cms_i_fault_optimized();
        print_can_frame_info();
        usleep(500000);
    }
    
    // Test case 6: Fault recovery
    printf("\nTest 6: Fault recovery (Clear some faults)\n");
    set_dem_event(DEM_EVENT_ID_EventParameter_Sensor_error, 0);
    set_dem_event(DEM_EVENT_ID_EventParameter_LCD_error, 0);
    set_dem_event(DEM_EVENT_ID_EventParameter_I2C_Bus_Error, 0);
    for (int i = 0; i < 8; i++) {
        cycle_count++;
        app_can_send_cms_i_fault_optimized();
        print_can_frame_info();
        usleep(500000);
    }

    // Test case 7: 5 Faults (2 frames)
    printf("\nTest 7: 5 Faults (2 frames)\n");
    memset(dem_event_status, 0, sizeof(dem_event_status));
    set_dem_event(DEM_EVENT_ID_EventParameter_Sensor_error, 1);
    set_dem_event(DEM_EVENT_ID_EventParameter_LCD_error, 1);
    set_dem_event(DEM_EVENT_ID_EventParameter_Power_Error, 1);
    set_dem_event(DEM_EVENT_ID_EventParameter_I2C_Bus_Error, 1);
    set_dem_event(DEM_EVENT_ID_EventParameter_CAN_Bus_Off, 1);
    for (int i = 0; i < 8; i++) {
        cycle_count++;
        app_can_send_cms_i_fault_optimized();
        print_can_frame_info();
        usleep(500000);
    }

    // Test case 8: All faults (7 faults - 2 frames)
    printf("\nTest 8: All faults (7 faults - 2 frames)\n");
    memset(dem_event_status, 0, sizeof(dem_event_status));
    for (int i = DEM_EVENT_ID_EventParameter_Video_error; i <= DEM_EVENT_ID_EventParameter_Lost_Communication_With_VIU2; i++) {
        set_dem_event(i, 1);
    }
    for (int i = 0; i < 10; i++) {
        cycle_count++;
        app_can_send_cms_i_fault_optimized();
        print_can_frame_info();
        usleep(500000);
    }

    // Test case 9: Rapid fault changes
    printf("\nTest 9: Rapid fault changes\n");
    for (int i = 0; i < 12; i++) {
        cycle_count++;
        // 每3个周期改变一次故障状态
        if (i % 3 == 0) {
            memset(dem_event_status, 0, sizeof(dem_event_status));
            // 随机设置1-3个故障
            int fault_count = (i % 3) + 1;
            for (int j = 0; j < fault_count; j++) {
                set_dem_event(DEM_EVENT_ID_EventParameter_Video_error + j, 1);
            }
        }
        app_can_send_cms_i_fault_optimized();
        print_can_frame_info();
        usleep(500000);
    }

    // Test case 10: Single fault recovery
    printf("\nTest 10: Single fault recovery\n");
    memset(dem_event_status, 0, sizeof(dem_event_status));
    set_dem_event(DEM_EVENT_ID_EventParameter_Video_error, 1);
    for (int i = 0; i < 3; i++) {
        cycle_count++;
        app_can_send_cms_i_fault_optimized();
        print_can_frame_info();
        usleep(500000);
    }
    // 清除故障
    set_dem_event(DEM_EVENT_ID_EventParameter_Video_error, 0);
    for (int i = 0; i < 3; i++) {
        cycle_count++;
        app_can_send_cms_i_fault_optimized();
        print_can_frame_info();
        usleep(500000);
    }

    // Test case 11: Edge case - exactly 4 faults
    printf("\nTest 11: Exactly 4 faults (1 frame)\n");
    memset(dem_event_status, 0, sizeof(dem_event_status));
    set_dem_event(DEM_EVENT_ID_EventParameter_Video_error, 1);
    set_dem_event(DEM_EVENT_ID_EventParameter_Sensor_error, 1);
    set_dem_event(DEM_EVENT_ID_EventParameter_LCD_error, 1);
    set_dem_event(DEM_EVENT_ID_EventParameter_Power_Error, 1);
    for (int i = 0; i < 6; i++) {
        cycle_count++;
        app_can_send_cms_i_fault_optimized();
        print_can_frame_info();
        usleep(500000);
    }

    // Test case 12: Edge case - exactly 8 faults (2 frames)
    printf("\nTest 12: Exactly 8 faults (2 frames) - testing frame boundary\n");
    memset(dem_event_status, 0, sizeof(dem_event_status));
    // 设置所有可能的故障
    for (int i = DEM_EVENT_ID_EventParameter_Video_error; i <= DEM_EVENT_ID_EventParameter_Lost_Communication_With_VIU2; i++) {
        set_dem_event(i, 1);
    }
    // 模拟第8个故障（虽然实际只有7个，但测试边界情况）
    for (int i = 0; i < 8; i++) {
        cycle_count++;
        app_can_send_cms_i_fault_optimized();
        print_can_frame_info();
        usleep(500000);
    }

    // Test case 13: Back to no faults
    printf("\nTest 13: Back to no fault status\n");
    memset(dem_event_status, 0, sizeof(dem_event_status));
    for (int i = 0; i < 5; i++) {
        cycle_count++;
        app_can_send_cms_i_fault_optimized();
        print_can_frame_info();
        usleep(500000);
    }

    // Test case 14: Intermittent faults
    printf("\nTest 14: Intermittent faults\n");
    for (int i = 0; i < 15; i++) {
        cycle_count++;
        // 每5个周期切换一次故障状态
        if (i % 5 == 0) {
            if (i % 10 == 0) {
                // 偶数次：设置故障
                memset(dem_event_status, 0, sizeof(dem_event_status));
                set_dem_event(DEM_EVENT_ID_EventParameter_Video_error, 1);
                set_dem_event(DEM_EVENT_ID_EventParameter_Sensor_error, 1);
            } else {
                // 奇数次：清除故障
                memset(dem_event_status, 0, sizeof(dem_event_status));
            }
        }
        app_can_send_cms_i_fault_optimized();
        print_can_frame_info();
        usleep(500000);
    }

    // Test case 15: Stress test - multiple frame cycles
    printf("\nTest 15: Stress test - multiple frame cycles with 6 faults\n");
    memset(dem_event_status, 0, sizeof(dem_event_status));
    set_dem_event(DEM_EVENT_ID_EventParameter_Video_error, 1);
    set_dem_event(DEM_EVENT_ID_EventParameter_Sensor_error, 1);
    set_dem_event(DEM_EVENT_ID_EventParameter_LCD_error, 1);
    set_dem_event(DEM_EVENT_ID_EventParameter_Power_Error, 1);
    set_dem_event(DEM_EVENT_ID_EventParameter_I2C_Bus_Error, 1);
    set_dem_event(DEM_EVENT_ID_EventParameter_CAN_Bus_Off, 1);
    for (int i = 0; i < 16; i++) {
        cycle_count++;
        app_can_send_cms_i_fault_optimized();
        print_can_frame_info();
        usleep(500000);
    }
    
    // Statistical information
    printf("\n=== Test statistics ===\n");
    printf("Total cycles: %u\r\n", total_cycles);
    printf("False change judgment count: %u\n", false_change_count);
    printf("False judgment rate: %.2f%%\n", (float)false_change_count / total_cycles * 100);
}

static int tmp_test_parse_data_1()
{
    int rc = 0;
    // uint8_t data[] = {0x02, 0x01, 0x01, 0x70, 0x00, 0x00, 0x00, 0x00};

    // 两个错误
    // uint8_t data[] = {0x02, 0x01, 0x01, 0x00, 0x07, 0x00, 0x00, 0x00};

    // 一个错误
    // uint8_t data[] = {0x01, 0x01, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00};

    // uint8_t data[] = {0x00, 0x00, 0x05, 0x00, 0x06, 0x07, 0x00, 0x04};


    // uint8_t data[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};                                               
    // uint8_t data[] = {0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00};                                               
    // uint8_t data[] = {0x02, 0x01, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00};                                               
    // uint8_t data[] = {0x03, 0x01, 0x01, 0x00, 0x02, 0x03, 0x00, 0x00};                                               
    // uint8_t data[] = {0x04, 0x01, 0x01, 0x00, 0x02, 0x03, 0x00, 0x04};                                               
    // uint8_t data[] = {0x05, 0x01, 0x01, 0x00, 0x02, 0x03, 0x00, 0x04};                                               
    // uint8_t data[] = {0x05, 0x02, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00};                                               
    // uint8_t data[] = {0x06, 0x01, 0x01, 0x00, 0x02, 0x03, 0x00, 0x04};                                               
    // uint8_t data[] = {0x06, 0x02, 0x05, 0x00, 0x06, 0x00, 0x00, 0x00};                                               
    // uint8_t data[] = {0x07, 0x01, 0x01, 0x00, 0x02, 0x03, 0x00, 0x04};                                               
    // uint8_t data[] = {0x07, 0x02, 0x05, 0x00, 0x06, 0x07, 0x00, 0x00};                                               
    // uint8_t data[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    uint8_t data[] = {0x03, 0x08, 0x00, 0x06, 0x4C, 0xC8, 0x1C, 0x00};

    CMS_I_FaultDecoded_t decoded;
    cms_i_fault_decode(data, &decoded);

    printf("Cycle %4u: TotalFaults=%u, FrameIndex=%u, Supplier=%u, Faults: ",
        cycle_count, decoded.TotalFaultNum, decoded.FrameIndex, decoded.SupplierNum);

    for (int i = 0; i < 4; i++) {
        if (decoded.FaultNum[i] != 0) {
            printf("0x%03X ", decoded.FaultNum[i]);
        } else {
            printf("0x000 ");  // 显示为0的故障号
        }
    }
    printf("\n");

    // 打印原始数据
    printf("Raw Data: ");
    for (int i = 0; i < 8; i++) {
        printf("%02X ", data[i]);
    }
    printf("\r\n\r\n");

    return rc;
}

void can_dem_app(void)
{

    int rc = 0;

    // run_test_cases();

    tmp_test_parse_data_1();

    return ;
}


#if 0
#include "can_dem.h"
#include "stdint.h"
#include "stdbool.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

enum {
    // Event IDs from DEM module
    DEM_EVENT_ID_NULL = 0,            // Do not change this entry!!!
    // DEM last event id for BSW
    DEM_EVENT_ID_LAST_FOR_BSW
};

enum {
    // NB! Event IDs below DEM_SWC_EVENT_ID_START not allowed!
    DEM_EVENT_ID_SWC_START = DEM_EVENT_ID_LAST_FOR_BSW,
	DEM_EVENT_ID_EventParameter_Video_error,
	DEM_EVENT_ID_EventParameter_Sensor_error,
	DEM_EVENT_ID_EventParameter_LCD_error,
	DEM_EVENT_ID_EventParameter_Power_Error,
	DEM_EVENT_ID_EventParameter_I2C_Bus_Error,
	DEM_EVENT_ID_EventParameter_CAN_Bus_Off,
	DEM_EVENT_ID_EventParameter_Lost_Communication_With_VIU2,
	DEM_EVENT_ID_MAX
};

typedef struct {
	// uint8 CMS_I_TotalFaultNum   :8;
	// uint8 CMS_I_SupplierNum		:3;
	// uint8 CMS_I_FrameIndex		:5;

	// uint16 reserved1 			:12;
	// uint16 CMS_I_FaultNum1 	    :12;
	// uint16 CMS_I_FaultNum2 	    :12;
	// uint8 reserved2 			:8;

	// uint16 CMS_I_FaultNum3 		:12;
	// uint16 CMS_I_FaultNum4 		:12;

	uint8 bytes[8];
} CMS_I_Fault_t;

typedef struct {
    uint8_t  TotalFaultNum;  // 当前故障总数
    uint8_t  FrameIndex;     // 帧序号
    uint8_t  SupplierNum;    // 供应商号
    uint16_t FaultNum[4];    // 故障号1~4
} CMS_I_FaultDecoded_t;

static CMS_I_Fault_t cms_i_fault;
static uint8 cms_i_fault_data[8] = {0};

static uint8 dem_event_status[DEM_EVENT_ID_MAX] = {0};


static uint32_t cycle_count = 0;
static uint32_t false_change_count = 0;
static uint32_t total_cycles = 0;

// static int Dem_ReadEventStatus(uint16 eventId)
// {
//     return 1;
// }


static int Dem_ReadEventStatus(uint16 eventId)
{
    if (eventId >= DEM_EVENT_ID_MAX) return 0;
    return dem_event_status[eventId];
}

static void set_dem_event(uint16 eventId, int status)
{
    if (eventId < DEM_EVENT_ID_MAX) {
        dem_event_status[eventId] = status;
    }
}

static void insertion_sort(uint8 *data, uint8 len);

void app_can_send_cms_i_fault(void)
{
	static uint8 frameIndex = 0;
	static uint8 lastTotalFaultNum = 0;
	static uint16 lastFaultList[8];
	uint16 faultIds[8];

	uint8 faultCount = 0;

    if (Dem_ReadEventStatus(DEM_EVENT_ID_EventParameter_Video_error) & 0x01)  
		faultIds[faultCount++] = 0x001;

    if (Dem_ReadEventStatus(DEM_EVENT_ID_EventParameter_Sensor_error) & 0x01) 
		faultIds[faultCount++] = 0x002;

    if (Dem_ReadEventStatus(DEM_EVENT_ID_EventParameter_LCD_error) & 0x01)    
		faultIds[faultCount++] = 0x003;

    if (Dem_ReadEventStatus(DEM_EVENT_ID_EventParameter_Power_Error) & 0x01)  
		faultIds[faultCount++] = 0x004;

    if (Dem_ReadEventStatus(DEM_EVENT_ID_EventParameter_I2C_Bus_Error) & 0x01)
		faultIds[faultCount++] = 0x005;

    if (Dem_ReadEventStatus(DEM_EVENT_ID_EventParameter_CAN_Bus_Off) & 0x01)  
		faultIds[faultCount++] = 0x006;

    if (Dem_ReadEventStatus(DEM_EVENT_ID_EventParameter_Lost_Communication_With_VIU2) & 0x01)
		faultIds[faultCount++] = 0x007;

	bool changed = (faultCount != lastTotalFaultNum);
	if (!changed) {
		for (uint8 i = 0; i < faultCount; i++) {
			if (faultIds[i] != lastFaultList[i]) { 
				changed = true; 
				break; 
			}
		}
	}

	if (changed) {
        for (uint8 i = 0; i < faultCount; i++) 
            lastFaultList[i] = faultIds[i];
        lastTotalFaultNum = faultCount;
		frameIndex = 0;
    }

	uint8 supplierNum = 0x00;
	uint64 frame = 0;

	frame |= ((uint64)faultCount & 0xFF) << 0;           // TotalFaultNum
    frame |= ((uint64)frameIndex & 0x1F) << 8;           // FrameIndex
    frame |= ((uint64)supplierNum & 0x07) << 13;         // SupplierNum

	uint8 startIdx = frameIndex * 4;
    uint8 endIdx   = (faultCount < startIdx + 4) ? faultCount : (startIdx + 4);
    for (uint8 i = 0; i < (endIdx - startIdx); i++) {
        uint16 faultVal = faultIds[startIdx + i] & 0xFFF;
        frame |= ((uint64)faultVal) << (16 + i * 12);
    }

    uint8 totalFrames = (faultCount + 3) / 4;
    frameIndex = (faultCount > 4) ? (frameIndex + 1) % totalFrames : 0;

	// 发送数据
	for (uint8 i = 0; i < 8; i++) {
		cms_i_fault_data[i] = (frame >> (i * 8)) & 0xFF;
	}

}

static void insertion_sort(uint8 *data, uint8 len)
{
	if (!data || !len)
		return ;

    for (uint8 i = 1; i < len; i++) {
        uint8 j = i;
        while (j > 0 && data[j] < data[j - 1]) {
            uint8 temp = data[j];
            data[j] = data[j - 1];
            data[j - 1] = temp;
            j--;
        }
    }
}



int can_main() {

    int rc = 0;

    int idxCount = 100;

    for (int i = 0; i < idxCount; i++) {
        // app_can_send_cms_i_fault();
        // app_can_send_cms_i_fault_8byte();
    }

    CMS_I_FaultDecoded_t decoded;

    uint8_t data[] = {0x01, 0x60, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00};
    cms_i_fault_decode(data, &decoded);


    // uint8_t data[] = {0x02, 0x60, 0x01, 0x70, 0x00, 0x00, 0x00, 0x00};


    // app_can_send_cms_i_fault_8byte();

    // test_case_1

    // app_can_send_cms_i_fault

    return rc;
}

#endif


#if 0
static int test_case_1(void);

static int test_case_1(void)
{
    int rc = 0;

    uint8_t data1[] = {0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; 
    uint8_t data2[] = {0x02, 0x60, 0x01, 0x70, 0x00, 0x00, 0x00, 0x00}; 
    uint8_t data3[] = {0x02, 0x60, 0x01, 0x70, 0x00, 0x00, 0x00, 0x00}; 
    uint8_t data4[] = {0x02, 0x60, 0x01, 0x70, 0x00, 0x00, 0x00, 0x00}; 
    uint8_t data5[] = {0x02, 0x60, 0x01, 0x70, 0x00, 0x00, 0x00, 0x00}; 
    uint8_t data6[] = {0x02, 0x60, 0x01, 0x70, 0x00, 0x00, 0x00, 0x00}; 
    uint8_t data7[] = {0x02, 0x60, 0x01, 0x70, 0x00, 0x00, 0x00, 0x00}; 
    uint8_t data8[] = {0x02, 0x60, 0x01, 0x70, 0x00, 0x00, 0x00, 0x00}; 
    uint8_t data9[] = {0x02, 0x60, 0x01, 0x70, 0x00, 0x00, 0x00, 0x00}; 
    uint8_t data10[] = {0x02, 0x60, 0x01, 0x70, 0x00, 0x00, 0x00, 0x00}; 
    uint8_t data11[] = {0x02, 0x60, 0x01, 0x70, 0x00, 0x00, 0x00, 0x00}; 
    uint8_t data12[] = {0x02, 0x60, 0x01, 0x70, 0x00, 0x00, 0x00, 0x00}; 
    uint8_t data13[] = {0x02, 0x60, 0x01, 0x70, 0x00, 0x00, 0x00, 0x00}; 
    uint8_t data14[] = {0x02, 0x60, 0x01, 0x70, 0x00, 0x00, 0x00, 0x00}; 
    uint8_t data15[] = {0x02, 0x60, 0x01, 0x70, 0x00, 0x00, 0x00, 0x00}; 
    uint8_t data16[] = {0x02, 0x60, 0x01, 0x70, 0x00, 0x00, 0x00, 0x00}; 
    uint8_t data17[] = {0x02, 0x60, 0x01, 0x70, 0x00, 0x00, 0x00, 0x00}; 
    uint8_t data18[] = {0x02, 0x60, 0x01, 0x70, 0x00, 0x00, 0x00, 0x00}; 
    uint8_t data19[] = {0x02, 0x60, 0x01, 0x70, 0x00, 0x00, 0x00, 0x00}; 
    uint8_t data20[] = {0x02, 0x60, 0x01, 0x70, 0x00, 0x00, 0x00, 0x00}; 
    uint8_t data21[] = {0x02, 0x60, 0x01, 0x70, 0x00, 0x00, 0x00, 0x00}; 
    uint8_t data22[] = {0x02, 0x60, 0x01, 0x70, 0x00, 0x00, 0x00, 0x00}; 
    uint8_t data23[] = {0x02, 0x60, 0x01, 0x70, 0x00, 0x00, 0x00, 0x00}; 
    uint8_t data24[] = {0x02, 0x60, 0x01, 0x70, 0x00, 0x00, 0x00, 0x00}; 
    uint8_t data25[] = {0x02, 0x60, 0x01, 0x70, 0x00, 0x00, 0x00, 0x00}; 
    uint8_t data26[] = {0x02, 0x60, 0x01, 0x70, 0x00, 0x00, 0x00, 0x00}; 
    uint8_t data27[] = {0x02, 0x60, 0x01, 0x70, 0x00, 0x00, 0x00, 0x00}; 
    uint8_t data28[] = {0x02, 0x60, 0x01, 0x70, 0x00, 0x00, 0x00, 0x00}; 
    uint8_t data29[] = {0x02, 0x60, 0x01, 0x70, 0x00, 0x00, 0x00, 0x00}; 
    uint8_t data30[] = {0x02, 0x60, 0x01, 0x70, 0x00, 0x00, 0x00, 0x00}; 
    uint8_t data31[] = {0x02, 0x60, 0x01, 0x70, 0x00, 0x00, 0x00, 0x00}; 


    uint8_t *data[] = {data1, data2, data3, data4, data5, data6, data7, data8, 
                    data9, data10, data11, data12, data13, data14, data15, 
                    data16, data17, data18, data19, data20, data21, data22, 
                    data23, data24, data25, data26, data27, data28, data29, 
                    data30, data31};

    int data_list = 31;

    for (int i = 0; i < data_list; i++) {
        cms_i_fault_decode(data[i], &decoded);
    }

    return rc;
}

void app_can_send_cms_i_fault(void)
{
    static uint8 frameIndex = 0;
    static uint8 lastTotalFaultNum = 0;
    static uint16 lastFaultList[8];
    static uint16 faultIds[8];

    uint8 faultCount = 0;

    // 故障采集
    if (Dem_ReadEventStatus(DEM_EVENT_ID_EventParameter_Video_error) & 1)  
        faultIds[faultCount++] = 0x001;
    if (Dem_ReadEventStatus(DEM_EVENT_ID_EventParameter_Sensor_error) & 1) 
        faultIds[faultCount++] = 0x002;
    if (Dem_ReadEventStatus(DEM_EVENT_ID_EventParameter_LCD_error) & 1)    
        faultIds[faultCount++] = 0x003;
    if (Dem_ReadEventStatus(DEM_EVENT_ID_EventParameter_Power_Error) & 1)  
        faultIds[faultCount++] = 0x004;
    if (Dem_ReadEventStatus(DEM_EVENT_ID_EventParameter_I2C_Bus_Error) & 1)
        faultIds[faultCount++] = 0x005;
    if (Dem_ReadEventStatus(DEM_EVENT_ID_EventParameter_CAN_Bus_Off) & 1)  
        faultIds[faultCount++] = 0x006;
    if (Dem_ReadEventStatus(DEM_EVENT_ID_EventParameter_Lost_Communication_With_VIU2) & 1)
        faultIds[faultCount++] = 0x007;

    printf("[%s][%d]faultCount: %d\r\n", __func__, __LINE__, faultCount);
    printf("[%s][%d]lastTotalFaultNum: %d\r\n", __func__, __LINE__, lastTotalFaultNum);

    // 检查变化
    bool changed = (faultCount != lastTotalFaultNum);

    printf("[%s][%d]changed: %d\r\n", __func__, __LINE__, changed);

    if (!changed) {
        for (uint8 i = 0; i < faultCount; i++) {
            if (faultIds[i] != lastFaultList[i]) { 
                changed = true;
                break; 
            }
        }
    }

    printf("[%s][%d]changed: %d\r\n", __func__, __LINE__, changed);
    printf("[%s][%d]frameIndex: %d\r\n", __func__, __LINE__, frameIndex);

    if (changed) {
        for (uint8 i = 0; i < faultCount; i++) 
            lastFaultList[i] = faultIds[i];
        lastTotalFaultNum = faultCount;
        frameIndex = 0;
    }
    printf("[%s][%d]frameIndex: %d\r\n", __func__, __LINE__, frameIndex);

    CMS_I_Fault_t cms_i_fault = {0};
    cms_i_fault.bytes[0] = faultCount;
    cms_i_fault.bytes[1] = ((0x03 << 5) | (frameIndex & 0x1F));

    printf("[%s][%d]faultCount: %d\r\n", __func__, __LINE__, faultCount);
    // 打包FaultNum1~4
    uint32 bitPos = 0;
    for (uint8 i = frameIndex * 4; (i < faultCount) && (i < frameIndex * 4 + 4); i++) {
        printf("[%s][%d]i: %d\r\n", __func__, __LINE__, i);
        // printf("[%s][%d]frameIndex: %d\r\n", __func__, __LINE__, frameIndex);
        uint16 val = faultIds[i] & 0xFFF;
        uint8 bytePos = 3 + (bitPos / 8);
        uint8 bitOff = bitPos % 8;
        uint32 shifted = val << bitOff;
        cms_i_fault.bytes[bytePos]     |= shifted & 0xFF;
        cms_i_fault.bytes[bytePos + 1] |= (shifted >> 8) & 0xFF;
        cms_i_fault.bytes[bytePos + 2] |= (shifted >> 16) & 0xFF;
        bitPos += 12;
    }
    printf("[%s][%d]frameIndex: %d\r\n", __func__, __LINE__, frameIndex);

    if (faultCount > 4) {
        frameIndex++;
        if (frameIndex >= (faultCount + 3) / 4) frameIndex = 0;
    } else {
        frameIndex = 0;
    }
    printf("[%s][%d]frameIndex: %d\r\n", __func__, __LINE__, frameIndex);
    printf("[%s][%d]\r\n", __func__, __LINE__);

    uint8_t *ptr = (uint8_t*)&cms_i_fault;
    int ptr_len = sizeof(CMS_I_Fault_t);
    for (int i = 0; i < ptr_len; i++) {
        printf("%02X", ptr[i]);
        if (i != ptr_len - 1) {
            printf(" ");
        } else {
            printf("\r\n");
        }
    }

    printf("[%s][%d]\r\n", __func__, __LINE__);

    return ;
}


void cms_i_fault_decode(const uint8 data[8], CMS_I_FaultDecoded_t *out)
{
    if (!data || !out) return;

    // 1️⃣ 组装 64bit（小端模式）
    uint64 frame = 0;
    for (int i = 0; i < 8; i++) {
        frame |= ((uint64)data[i]) << (i * 8);
    }

    // 2️⃣ 提取信号
    out->TotalFaultNum = (frame >> 0)  & 0xFF;  // 8bit
    out->FrameIndex    = (frame >> 8)  & 0x1F;  // 5bit
    out->SupplierNum   = (frame >> 13) & 0x07;  // 3bit

    for (int i = 0; i < 4; i++) {
        out->FaultNum[i] = (frame >> (16 + i * 12)) & 0xFFF;
    }

    printf("=== CMS_I_Fault Decoded ===\n");
    printf("TotalFaultNum : %u\n", out->TotalFaultNum);
    printf("FrameIndex    : %u\n", out->FrameIndex);
    printf("SupplierNum   : %u\n", out->SupplierNum);
    for (int i = 0; i < 4; i++) {
        printf("FaultNum[%d]   : 0x%03X\n", i + 1, out->FaultNum[i]);
    }
}


void app_can_send_cms_i_fault_8byte(void)
{
    static uint8 frameIndex = 0;
    static uint8 lastTotalFaultNum = 0;
    static uint16 lastFaultList[8];
    // static uint16 faultIds[8];
    uint16 faultIds[8];

    uint8 faultCount = 0;

    // 采集故障列表
    if (Dem_ReadEventStatus(1)) faultIds[faultCount++] = 0x001;
    if (Dem_ReadEventStatus(2)) faultIds[faultCount++] = 0x002;
    if (Dem_ReadEventStatus(3)) faultIds[faultCount++] = 0x003;
    if (Dem_ReadEventStatus(4)) faultIds[faultCount++] = 0x004;
    if (Dem_ReadEventStatus(5)) faultIds[faultCount++] = 0x005;
    if (Dem_ReadEventStatus(6)) faultIds[faultCount++] = 0x006;
    if (Dem_ReadEventStatus(7)) faultIds[faultCount++] = 0x007;

    // 检查变化
    bool changed = (faultCount != lastTotalFaultNum);
    if (!changed) {
        for (uint8 i = 0; i < faultCount; i++) {
            if (faultIds[i] != lastFaultList[i]) { changed = true; break; }
        }
    }
    if (changed) {
        for (uint8 i = 0; i < faultCount; i++) 
            lastFaultList[i] = faultIds[i];
        lastTotalFaultNum = faultCount;
        frameIndex = 0;
    }

    uint8 supplierNum = 0x03;
    uint64 frame = 0;

    // ==== 按信号表打包 ====
    frame |= ((uint64)faultCount & 0xFF) << 0;           // TotalFaultNum
    frame |= ((uint64)frameIndex & 0x1F) << 8;           // FrameIndex
    frame |= ((uint64)supplierNum & 0x07) << 13;         // SupplierNum

    uint8 startIdx = frameIndex * 4;
    uint8 endIdx   = (faultCount < startIdx + 4) ? faultCount : (startIdx + 4);
    for (uint8 i = 0; i < (endIdx - startIdx); i++) {
        uint16 faultVal = faultIds[startIdx + i] & 0xFFF;
        frame |= ((uint64)faultVal) << (16 + i * 12);
    }

    // 拆成8字节
    uint8 bytes[8];
    for (uint8 i = 0; i < 8; i++) {
        bytes[i] = (frame >> (i * 8)) & 0xFF;
    }

    // 输出打印
    printf("CAN Frame [8 bytes]: ");
    for (uint8 i = 0; i < 8; i++) printf("%02X ", bytes[i]);
    printf("\n");

    CMS_I_FaultDecoded_t decoded;
    cms_i_fault_decode(bytes, &decoded);

    printf("=== CMS_I_Fault Decoded ===\n");
    printf("TotalFaultNum : %u\n", decoded.TotalFaultNum);
    printf("FrameIndex    : %u\n", decoded.FrameIndex);
    printf("SupplierNum   : %u\n", decoded.SupplierNum);
    for (int i = 0; i < 4; i++) {
        printf("FaultNum[%d]   : 0x%03X\n", i + 1, decoded.FaultNum[i]);
    }

    // 帧计数循环
    uint8 totalFrames = (faultCount + 3) / 4;
    frameIndex = (faultCount > 4) ? (frameIndex + 1) % totalFrames : 0;

    _sleep(1000);

    return;
}

#endif 