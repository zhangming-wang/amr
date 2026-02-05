#pragma once

namespace MotionService {
    enum Type {
        Idle = 0,
        HeartBeat,
        Restart,

        Brake,
        StopMove,
        MoveFront,
        MoveBack,
        TurnLeft,
        TurnRight,

        SetSpeedPercent,
        SetSpeedPlanState,

        CalibrateMPU6050,

        ReadParams,
        WriteParams,
        SaveParams,

        ReadConfig,
        WriteConfig,
        SaveConfig,
    };
}

namespace CameraService {
    enum Type {
        Idle = 0,
        HeartBeat,
        Restart,

        Capture,
        SetEnableSeriesCapture,

        ReadParams,
        WriteParams,
        SaveParams,

        ReadConfig,
        WriteConfig,
        SaveConfig,
    };
};