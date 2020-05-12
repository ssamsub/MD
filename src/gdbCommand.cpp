#include  "gdbCommand.h"
#include "gdbBridge.h"

GdbCommand::GdbCommand() {}

void GdbCommand::getResult(std::string & result) const
{
    result = _resultString;
}

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////


AttachToProcessCmd::AttachToProcessCmd(int pId) : _pId(pId)
{
}

bool AttachToProcessCmd::execute(GdbBridge & bridge)
{
    std::string command = "-target-attach ";
    command.append(std::to_string(_pId));
    return bridge.executeCommand(command, _resultString);
}
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////


SetBreakpointCmd::SetBreakpointCmd(const std::string & breakPoint) : _breakPoint(breakPoint)
{
}

bool SetBreakpointCmd::execute(GdbBridge & bridge)
{
    if (_breakPoint.empty()) return false;
    std::string command = "-break-insert ";
    command.append(_breakPoint);
    return bridge.executeCommand(command, _resultString);
}
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////


ExecContinueCmd::ExecContinueCmd()
{
}

bool ExecContinueCmd::execute(GdbBridge & bridge)
{
    std::string command = "-exec-continue";
    return bridge.executeCommand(command, _resultString);
}
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////


ShowLocalsCmd::ShowLocalsCmd(bool bWithValues) : _bWithValues(bWithValues)
{
}

bool ShowLocalsCmd::execute(GdbBridge & bridge)
{
    std::string command = "-stack-list-locals ";
    command.append(_bWithValues ? "1" : "0");
    return bridge.executeCommand(command, _resultString);
}
