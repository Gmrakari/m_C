#ifndef _FSM_BASE_H_
#define _FSM_BASE_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// 交通灯状态枚举
typedef enum {
    RED_LIGHT,      // 红灯
    GREEN_LIGHT,    // 绿灯  
    YELLOW_LIGHT    // 黄灯
} TrafficLightState;

// 交通灯结构体
typedef struct {
    TrafficLightState current_state;    // 当前状态
    int red_duration;                   // 红灯持续时间(秒)
    int green_duration;                 // 绿灯持续时间(秒)
    int yellow_duration;                // 黄灯持续时间(秒)
    int timer;                          // 当前状态计时器
} TrafficLightFSM;

// 初始化交通灯
void initTrafficLight(TrafficLightFSM *light);

// 获取状态名称
const char* getStateName(TrafficLightState state);


// 状态转移函数
void transitionState(TrafficLightFSM *light);

// 更新交通灯状态
void updateTrafficLight(TrafficLightFSM *light);

// 显示交通灯信息
void displayTrafficLight(const TrafficLightFSM *light);

// 模拟交通灯运行
void simulateTrafficLight(TrafficLightFSM *light, int simulation_time);

// 高级版本：支持配置的交通灯
typedef struct {
    TrafficLightFSM fsm;
    int emergency_mode;  // 紧急模式
    int night_mode;      // 夜间模式
} AdvancedTrafficLight;

void initAdvancedTrafficLight(AdvancedTrafficLight *adv_light);

void setEmergencyMode(AdvancedTrafficLight *adv_light, int enable);

void setNightMode(AdvancedTrafficLight *adv_light, int enable);

void updateAdvancedTrafficLight(AdvancedTrafficLight *adv_light);

int fsg_base_main();


#endif // _FSM_BASE_H_