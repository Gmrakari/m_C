#include "fsm_base.h"


void initTrafficLight(TrafficLightFSM *light) {
    light->current_state = RED_LIGHT;
    light->red_duration = 10;
    light->green_duration = 5;
    light->yellow_duration = 3;
    light->timer = light->red_duration;
}

// 获取状态名称
const char* getStateName(TrafficLightState state) {
    switch(state) {
        case RED_LIGHT: return "Red Light";
        case GREEN_LIGHT: return "Green Light";
        case YELLOW_LIGHT: return "Yellow Light";
        default: return "Unknown";
    }
}

// 状态转移函数
void transitionState(TrafficLightFSM *light) {
    switch(light->current_state) {
        case RED_LIGHT:
            light->current_state = GREEN_LIGHT;
            light->timer = light->green_duration;
            break;
            
        case GREEN_LIGHT:
            light->current_state = YELLOW_LIGHT;
            light->timer = light->yellow_duration;
            break;
            
        case YELLOW_LIGHT:
            light->current_state = RED_LIGHT;
            light->timer = light->red_duration;
            break;
    }
}

// 更新交通灯状态
void updateTrafficLight(TrafficLightFSM *light) {
    light->timer--;
    
    // 如果计时器归零，进行状态转移
    if(light->timer <= 0) {
        transitionState(light);
    }
}

// 显示交通灯信息
void displayTrafficLight(const TrafficLightFSM *light) {
    printf("\n===traffic light status ===\n");
    printf("current state: %s\n", getStateName(light->current_state));
    printf("left time: %d seconds\n", light->timer);
    
    // 显示对应的交通指示
    switch(light->current_state) {
        case RED_LIGHT:
            printf("vehicle: stop\n");
            printf("pedestrian: waiting\n");
            break;
        case GREEN_LIGHT:
            printf("Vehicle: pass\n");
            printf("pedestrian: waiting\n");
            break;
        case YELLOW_LIGHT:
            printf("car: Prepare to pass\n");
            printf("pedestrian: Prepare to pass\n");
            break;
    }
    printf("==================\n");
}

// 模拟交通灯运行
void simulateTrafficLight(TrafficLightFSM *light, int simulation_time) {
    printf("start to simulate traffic light total time: %d seconds\r\n", simulation_time);
    
    for(int i = 0; i < simulation_time; i++) {
        displayTrafficLight(light);
        updateTrafficLight(light);
        sleep(1);  // 等待1秒

        // 清屏（可选，使显示更清晰）
        // system("clear");
    }
}


void initAdvancedTrafficLight(AdvancedTrafficLight *adv_light) {
    initTrafficLight(&adv_light->fsm);
    adv_light->emergency_mode = 0;
    adv_light->night_mode = 0;
}

void setEmergencyMode(AdvancedTrafficLight *adv_light, int enable) {
    adv_light->emergency_mode = enable;
    if(enable) {
        printf("emergency mode: yellow light is flashing\r\n");
    }
}

void setNightMode(AdvancedTrafficLight *adv_light, int enable) {
    adv_light->night_mode = enable;
    if(enable) {
        printf("night mode: yellow light is flashing\r\n");
    }
}

void updateAdvancedTrafficLight(AdvancedTrafficLight *adv_light) {
    if(adv_light->emergency_mode || adv_light->night_mode) {
        // 紧急模式或夜间模式：黄灯闪烁
        adv_light->fsm.current_state = YELLOW_LIGHT;
        printf("The yellow light is flashing\r\n");
    } else {
        updateTrafficLight(&adv_light->fsm);
    }
}

int fsg_base_main() 
{
    printf("===Traffic light demo===\r\n");

    // 基础版本演示
    TrafficLightFSM traffic_light;
    initTrafficLight(&traffic_light);
    
    // 模拟运行120秒
    simulateTrafficLight(&traffic_light, 30);
    
    // // 高级版本演示
    // printf("\n\nadvence traffic light demo\r\n");
    // AdvancedTrafficLight adv_light;
    // initAdvancedTrafficLight(&adv_light);
    
    // // 正常模式运行30秒
    // for(int i = 0; i < 30; i++) {
    //     displayTrafficLight(&adv_light.fsm);
    //     updateAdvancedTrafficLight(&adv_light);
    //     sleep(1);
    // }

    // // 切换到紧急模式
    // setEmergencyMode(&adv_light, 1);
    // for(int i = 0; i < 10; i++) {
    //     displayTrafficLight(&adv_light.fsm);
    //     updateAdvancedTrafficLight(&adv_light);
    //     sleep(1);
    // }
    
    // // 恢复正常模式
    // setEmergencyMode(&adv_light, 0);
    // printf("recory normal mode\r\n");
    
    return 0;
}
