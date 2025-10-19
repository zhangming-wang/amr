#pragma once

enum ServiceType {
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

    ReadParams,
    WriteParams,
    SaveParams,

    ReadSettings,
    WriteSettings,
    SaveSettings,
};

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