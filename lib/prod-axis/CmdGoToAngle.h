#ifndef CMDGOTOANGLE_H
#define CMDGOTOANGLE_H

#pragma once

#include <Cmd.h>

class Axis;

class CmdGoToAngle : public Cmd
{
public:
    CmdGoToAngle(CmdSequence* cmdSequence, long int timeMillis, Axis* axis, int targetAngle, int velocity);
    virtual ~CmdGoToAngle();

    void execute();
    void leave();

private:
    Axis* m_axis;
    int m_targetAngle;
    int m_velocity;
};

#endif