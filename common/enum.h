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
        MoveLeft,
        MoveRight,
        MoveLeftFront,
        MoveLeftBack,
        MoveRightFront,
        MoveRightBack,
        TurnLeft,
        TurnRight,

        SetSpeedPercent,
        SetSpeedPlanState,
        SetEnablePubMotionStatus,

        CalibrateIMU,

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