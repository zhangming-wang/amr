#pragma once

enum ServiceType {
    Idle = 0,
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

    ReadParams,
    WriteParams,
    SaveParams,

    ReadSettings,
    WriteSettings,
    SaveSettings,
};
