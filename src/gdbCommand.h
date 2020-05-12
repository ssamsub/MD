#ifndef GDB_COMMAND_H
#define GDB_COMMAND_H

#include <string>

class GdbBridge;

class GdbCommand
{
public:
    GdbCommand();
    GdbCommand(const std::string & command);
    void getResult(std::string & result) const;
    virtual bool    execute(GdbBridge & bridge) = 0;
protected:
    std::string _resultString;
};

class AttachToProcessCmd : public GdbCommand
{
public:
    AttachToProcessCmd(int pId);
    bool    execute(GdbBridge & bridge) override;
private:
    int _pId;
};

class SetBreakpointCmd : public GdbCommand
{
public:
    SetBreakpointCmd(const std::string & breakPoint);
    bool    execute(GdbBridge & bridge) override;
private:
    std::string _breakPoint;
};

class ExecContinueCmd : public GdbCommand
{
public:
    ExecContinueCmd();
    bool    execute(GdbBridge & bridge) override;
};

class ShowLocalsCmd : public GdbCommand
{
public:
    ShowLocalsCmd(bool bWithValues);
    bool    execute(GdbBridge & bridge) override;
private:
    bool _bWithValues;
};
#endif
