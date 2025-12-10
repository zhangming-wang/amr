#pragma once

#include <iostream>
#include <math.h>

struct pathInitData {
    float max_acc = 0;    // 最大加速度
    float Jerk = 0;       // 加加速度
    float cmd_pos = 0;    // 位移
    float v0 = 0;         // 初速度
    float VMax = 0;       // 最大速度
    float ve = 0;         // 末速度
    float deltaT = 0.001; // 规划时最小时间单位(默认0.001s)
};

class PathPlan {
public:
    bool performPath(bool path_pause = false);                                                                   // 执行规划
    void get_move_msg(float &curProportion, float &curPos_m, float &curVs_m, float &curAcc_m, float &curTime_m); // 获得当前所走总位移、速度、加速度、时间
    void ini_path_data(const pathInitData &pathInit);                                                            // 初始化参数
    bool pathBusy();                                                                                             // 判断是否在规划中

private:
    float deltaT = 0.001;

    const float coverAccuracy = pow(10, -12); // 弥补float精度
    const float maxProportion = 1;

    float cmd_pos = 0, remaining_pos = 0, dec_move_pos = 0, cur_move_pos = 0;
    float v0 = 0, Vmax = 0, ve = 0, vs = 0, dec_ve = 0;
    float maxAcc = 0, Jerk = 0, val_Auv = 0;
    float recordTime = 0, ficureTimeRecord = 0, recordDis = 0;

    bool decInit = false, dec_finished = false, path_pause_cmd = false;
    bool path_busy = false, can_do_path = false;

    int preView_phase = 0;
    bool preViewDone = false;

    int moveDir = 0;
    int ficureMoveDir = 0;

    int acc_t = 0;
    float ficureTime[4] = {0, 0, 0, 0};
    float ficureV[3] = {0, 0, 0};
    float ficureAcc[3] = {0, 0, 0};
    float ficureDis[3] = {0, 0, 0};

    enum enumType { positiveAcceleration,
                    steadyAcceleration,
                    negetiveAcceleration };
    void judge_path_condition();                                                                                             // 进行规划条件判断
    void doMotionPlan(bool doPath);                                                                                          // 运行单位时间计算
    bool preView(enumType motionType);                                                                                       // 前瞻下一个单位时间,并做出判断
    void preFicure();                                                                                                        // 前瞻完成,将后半程各个阶段的信息计算出来
    void movePreViewPos(enumType motionType);                                                                                // 前瞻后运动一个单位时间的计算
    void moveFicurePos(enumType motionType, const float time);                                                               // 后半程运动一个单位时间的计算
    void get_time_point(const float vEnd, float &cal_vmax, float &cal_maxAcc, float &t1_tmp, float &t2_tmp, float &moveDis); // 获取到达最大速度的时间,最大加速度,以及后半程各阶段时间
    void get_ficure_point(const float vBegin, const float vEnd, const float t1_tmp, const float t2_tmp);                     // 获取后半程时间,位移,速度,加速度节点信息
};
