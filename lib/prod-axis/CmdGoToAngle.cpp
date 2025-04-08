#include "CmdGoToAngle.h"

#include <Axis.h>
#include <CmdSequence.h>

CmdGoToAngle::CmdGoToAngle(CmdSequence* cmdSequence, long int timeMillis,
                           Axis* axis, int targetAngle, int velocity)
    : Cmd(cmdSequence, timeMillis, (0 != axis) ? axis->name() : ""),
      m_axis(axis),
      m_targetAngle(targetAngle),
      m_velocity(velocity) {}

CmdGoToAngle::~CmdGoToAngle() {}

void CmdGoToAngle::execute()
{
    if (0 != m_axis)
    {
        m_axis->goToTargetAngle(m_targetAngle, m_velocity);
    }
}

void CmdGoToAngle::leave()
{
    if (0 != m_axis)
    {
        m_axis->stop();
    }
}
