#pragma once

class State {
public:
    virtual void OnEnter() = 0;
    virtual void OnExit() = 0;
};