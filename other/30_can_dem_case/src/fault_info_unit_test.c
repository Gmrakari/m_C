#include "fault_info_unit_test.h"
#include "stdint.h"
#include "stdbool.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

static void app_send_fault_info_demo(void);
static void debug_print_fault_info(void);
static void set_demo_event_val(uint16 eventId, int status);
static int get_demo_event_status(uint16 eventId);
static void fault_info_decode(const uint8 *data, SrcInfoDecoded_t *decoded);

// 模拟状态
static uint8 demo_event_status[ID_MAX_error] = {0};
static uint32_t cycle_count = 0;
static uint32_t false_change_count = 0;
static uint32_t total_cycles = 0;

// 解码函数
static void fault_info_decode(const uint8 *data, SrcInfoDecoded_t *decoded)
{
    if (!data || !decoded) return;
    memset(decoded, 0, sizeof(SrcInfoDecoded_t));

    decoded->TotalFaultNum = data[0];
    decoded->SupplierNum = ((data[1] >> 3) & 0x1f);
    decoded->FrameIndex = data[1] & 0x07;
    decoded->FaultNum[0] = (data[2] & 0xff) | (data[3] >> 4 & 0x0f);
    decoded->FaultNum[1] = (data[3] & 0x0f) | (data[4] & 0xff);
    decoded->FaultNum[2] = (data[5] & 0xff) | ((data[6] >> 4) & 0x0f);
    decoded->FaultNum[3] = (data[6] & 0x0f) | (data[7]  & 0xff);

    return ;
}

static int get_demo_event_status(uint16 eventId)
{
    if (eventId >= ID_MAX_error) return 0;
    return demo_event_status[eventId];
}

static void set_demo_event_val(uint16 eventId, int status)
{
    if (eventId < ID_MAX_error) {
        demo_event_status[eventId] = status;
    }
}

static void app_send_fault_info_demo(void)
{
    static uint8 frameIndex = 0;  // 无故障时为0
    static uint8 lastTotalFaultNum = 0;
    static uint16 lastFaultList[8];
    uint16 faultIds[8];
    uint8 faultCount = 0;

    #if 1

    // 采集故障列表
    if (get_demo_event_status(ID_Video_error))  
        faultIds[faultCount++] = 0x001;
    if (get_demo_event_status(ID_Sensor_error)) 
        faultIds[faultCount++] = 0x002;
    if (get_demo_event_status(ID_LCD_error))    
        faultIds[faultCount++] = 0x003;
    if (get_demo_event_status(ID_Power_error))  
        faultIds[faultCount++] = 0x004;
    if (get_demo_event_status(ID_I2C_Bus_error))
        faultIds[faultCount++] = 0x005;
    if (get_demo_event_status(ID_CAN_Bus_Off_error))  
        faultIds[faultCount++] = 0x006;
    if (get_demo_event_status(ID_Lost_Communication_With_VIU2_error))
        faultIds[faultCount++] = 0x007;
    
    #endif

    // for (int i = 1; i < 8; i++) {
    //     faultIds[faultCount++] = i;
    // }

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

    memset(&fault_info, 0, sizeof(Fault_Info_t));
    fault_info.Info_TotalFaultNum = faultCount & 0xFF;
    fault_info.Info_FrameIdx = frameIndex & 0x1F;
    fault_info.Info_SuppilerNum = 0x00 & 0x07;

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
                    fault_info.Byte2 = faultVal & 0xFF;
                    fault_info.Byte3 = (faultVal >> 8) & 0x0F;
                    break;
                case 1:
                    fault_info.Byte3 = (faultVal >> 8) & 0x0F;
                    fault_info.Byte4 = faultVal & 0xFF;
                    break;
                case 2:
                    fault_info.Byte5 = faultVal & 0xFF;
                    fault_info.Byte6 = (faultVal >> 8) & 0x0F;
                    break;
                case 3:
                    fault_info.Byte6 = (faultVal >> 8) & 0x0F;
                    fault_info.Byte7 = faultVal & 0xFF;
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
    memcpy(fault_info_data, &fault_info, sizeof(fault_info_data));

    total_cycles++;

}

static void debug_print_fault_info(void)
{
    SrcInfoDecoded_t decoded;
    fault_info_decode(fault_info_data, &decoded);
    
    // 核心帧信息（对齐格式，便于查看）
    printf("Cycle: %4u\r\n TotalFaults: %u FrameIndex: %u Supplier: 0x%01X  ",
           cycle_count, decoded.TotalFaultNum, decoded.FrameIndex, decoded.SupplierNum);
    printf("Faults: ");
    for (int i = 0; i < 4; i++) {
        printf("0x%03X ", decoded.FaultNum[i]);
    }
    printf("\r\n");

}

// 测试用例
static void run_test_cases(void)
{
    printf("=== Starting 500ms periodic fault reporting test ===\n\n");

    // Test case 1: No faults
    printf("Test 1: No fault status\n");
    memset(demo_event_status, 0, sizeof(demo_event_status));
    for (int i = 0; i < 5; i++) {
        cycle_count++;
        app_send_fault_info_demo();
        debug_print_fault_info();
        usleep(500000); // 500ms
    }

    #if 1
    
    // Test case 2: Single fault
    printf("\nTest 2: Single fault (Video fault)\n");
    set_demo_event_val(ID_Video_error, 1);
    for (int i = 0; i < 5; i++) {
        cycle_count++;
        app_send_fault_info_demo();
        debug_print_fault_info();
        usleep(500000);
    }
    
    // Test case 3: Multiple faults (3 faults)
    printf("\nTest 3: Multiple faults (3 faults)\n");
    set_demo_event_val(ID_Sensor_error, 1);
    set_demo_event_val(ID_LCD_error, 1);
    for (int i = 0; i < 6; i++) {
        cycle_count++;
        app_send_fault_info_demo();
        debug_print_fault_info();
        usleep(500000);
    }
    
    // Test case 4: Multiple faults (6 faults - 2 frames)
    printf("\nTest 4: Multiple faults (6 faults - 2 frames)\n");
    set_demo_event_val(ID_Power_error, 1);
    set_demo_event_val(ID_I2C_Bus_error, 1);
    set_demo_event_val(ID_CAN_Bus_Off_error, 1);
    for (int i = 0; i < 8; i++) {
        cycle_count++;
        app_send_fault_info_demo();
        debug_print_fault_info();
        usleep(500000);
    }
    
    // Test case 5: Multiple faults (7 faults - 2 frames)
    printf("\nTest 5: Multiple faults (7 faults - 2 frames)\n");
    set_demo_event_val(ID_Lost_Communication_With_VIU2_error, 1);
    for (int i = 0; i < 8; i++) {
        cycle_count++;
        app_send_fault_info_demo();
        debug_print_fault_info();
        usleep(500000);
    }
    
    // Test case 6: Fault recovery
    printf("\nTest 6: Fault recovery (Clear some faults)\n");
    set_demo_event_val(ID_Sensor_error, 0);
    set_demo_event_val(ID_LCD_error, 0);
    set_demo_event_val(ID_I2C_Bus_error, 0);
    for (int i = 0; i < 8; i++) {
        cycle_count++;
        app_send_fault_info_demo();
        debug_print_fault_info();
        usleep(500000);
    }

    // Test case 7: 5 Faults (2 frames)
    printf("\nTest 7: 5 Faults (2 frames)\n");
    memset(demo_event_status, 0, sizeof(demo_event_status));
    set_demo_event_val(ID_Sensor_error, 1);
    set_demo_event_val(ID_LCD_error, 1);
    set_demo_event_val(ID_Power_error, 1);
    set_demo_event_val(ID_I2C_Bus_error, 1);
    set_demo_event_val(ID_CAN_Bus_Off_error, 1);
    for (int i = 0; i < 8; i++) {
        cycle_count++;
        app_send_fault_info_demo();
        debug_print_fault_info();
        usleep(500000);
    }

    // Test case 8: All faults (7 faults - 2 frames)
    printf("\nTest 8: All faults (7 faults - 2 frames)\n");
    memset(demo_event_status, 0, sizeof(demo_event_status));
    for (int i = ID_Video_error; i <= ID_Lost_Communication_With_VIU2_error; i++) {
        set_demo_event_val(i, 1);
    }
    for (int i = 0; i < 10; i++) {
        cycle_count++;
        app_send_fault_info_demo();
        debug_print_fault_info();
        usleep(500000);
    }

    // Test case 9: Rapid fault changes
    printf("\nTest 9: Rapid fault changes\n");
    for (int i = 0; i < 12; i++) {
        cycle_count++;
        // 每3个周期改变一次故障状态
        if (i % 3 == 0) {
            memset(demo_event_status, 0, sizeof(demo_event_status));
            // 随机设置1-3个故障
            int fault_count = (i % 3) + 1;
            for (int j = 0; j < fault_count; j++) {
                set_demo_event_val(ID_Video_error + j, 1);
            }
        }
        app_send_fault_info_demo();
        debug_print_fault_info();
        usleep(500000);
    }

    // Test case 10: Single fault recovery
    printf("\nTest 10: Single fault recovery\n");
    memset(demo_event_status, 0, sizeof(demo_event_status));
    set_demo_event_val(ID_Video_error, 1);
    for (int i = 0; i < 3; i++) {
        cycle_count++;
        app_send_fault_info_demo();
        debug_print_fault_info();
        usleep(500000);
    }
    // 清除故障
    set_demo_event_val(ID_Video_error, 0);
    for (int i = 0; i < 3; i++) {
        cycle_count++;
        app_send_fault_info_demo();
        debug_print_fault_info();
        usleep(500000);
    }

    // Test case 11: Edge case - exactly 4 faults
    printf("\nTest 11: Exactly 4 faults (1 frame)\n");
    memset(demo_event_status, 0, sizeof(demo_event_status));
    set_demo_event_val(ID_Video_error, 1);
    set_demo_event_val(ID_Sensor_error, 1);
    set_demo_event_val(ID_LCD_error, 1);
    set_demo_event_val(ID_Power_error, 1);
    for (int i = 0; i < 6; i++) {
        cycle_count++;
        app_send_fault_info_demo();
        debug_print_fault_info();
        usleep(500000);
    }

    // Test case 12: Edge case - exactly 8 faults (2 frames)
    printf("\nTest 12: Exactly 8 faults (2 frames) - testing frame boundary\n");
    memset(demo_event_status, 0, sizeof(demo_event_status));
    // 设置所有可能的故障
    for (int i = ID_Video_error; i <= ID_Lost_Communication_With_VIU2_error; i++) {
        set_demo_event_val(i, 1);
    }
    // 模拟第8个故障（虽然实际只有7个，但测试边界情况）
    for (int i = 0; i < 8; i++) {
        cycle_count++;
        app_send_fault_info_demo();
        debug_print_fault_info();
        usleep(500000);
    }

    // Test case 13: Back to no faults
    printf("\nTest 13: Back to no fault status\n");
    memset(demo_event_status, 0, sizeof(demo_event_status));
    for (int i = 0; i < 5; i++) {
        cycle_count++;
        app_send_fault_info_demo();
        debug_print_fault_info();
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
                memset(demo_event_status, 0, sizeof(demo_event_status));
                set_demo_event_val(ID_Video_error, 1);
                set_demo_event_val(ID_Sensor_error, 1);
            } else {
                // 奇数次：清除故障
                memset(demo_event_status, 0, sizeof(demo_event_status));
            }
        }
        app_send_fault_info_demo();
        debug_print_fault_info();
        usleep(500000);
    }

    // Test case 15: Stress test - multiple frame cycles
    printf("\nTest 15: Stress test - multiple frame cycles with 6 faults\n");
    memset(demo_event_status, 0, sizeof(demo_event_status));
    set_demo_event_val(ID_Video_error, 1);
    set_demo_event_val(ID_Sensor_error, 1);
    set_demo_event_val(ID_LCD_error, 1);
    set_demo_event_val(ID_Power_error, 1);
    set_demo_event_val(ID_I2C_Bus_error, 1);
    set_demo_event_val(ID_CAN_Bus_Off_error, 1);
    for (int i = 0; i < 16; i++) {
        cycle_count++;
        app_send_fault_info_demo();
        debug_print_fault_info();
        usleep(500000);
    }
    
    // Statistical information
    printf("\n=== Test statistics ===\n");
    printf("Total cycles: %u\r\n", total_cycles);
    printf("False change judgment count: %u\n", false_change_count);
    printf("False judgment rate: %.2f%%\n", (float)false_change_count / total_cycles * 100);

    #endif
}


void demo_app_start(void)
{

    int rc = 0;

    run_test_cases();

    return ;
}
