#include "gdbBridge.h"
#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <string>
#include "unistd.h"
#include <cstring>

GdbBridge::GdbBridge() : _gdbStarted(false)
{
    _readBuffer = new char[256];
    _writeBuffer = new char[256];
}

GdbBridge::~GdbBridge()
{
    delete [] _readBuffer;
    delete [] _writeBuffer;
}

bool GdbBridge::spawnGdb()
{
    pipe(_readPipeDescriptors);
    pipe(_writePipeDescriptors);

    int forkRet = fork();

    if (forkRet) {              // PARENT
        close(_getGdbReadFd());
        close(_getGdbWriteFd());
        // parent reads gdb status
        std::string readBuffer;
        bool ret = _readTillPostAmble(readBuffer);
        if (!ret) exit(-1);
        
        _gdbStarted = true;
        return true;
    } else if (forkRet == 0) {  // CHILD
        close(_getReadFd());
        close(_getWriteFd());
        // Close and redirect stdin/out
        close(0);
        dup2(_getGdbReadFd(), 0);
        close(1);
        dup2(_getGdbWriteFd(), 1);
        int ret = execlp("gdb", "gdb", "--interpreter=mi", (const char *)NULL);
        if (ret != 0) exit(-1);
    }
    return false;
}

bool GdbBridge::attachToProcess(int pId)
{
    if (!_gdbStarted) return false;
    std::string command = "-target-attach ";
    command.append(std::to_string(pId));
    if (!_writeCommand(command)) return false;

    std::string readBuffer;
    bool ret = _readTillPostAmble(readBuffer);
  //std::cout << __func__ << ": " << readBuffer << std::endl;
    return ret;
}

bool GdbBridge::setBreakpoint(const std::string & bpName)
{
    if (bpName.empty()) return false;
    std::string command = "-break-insert ";
    command.append(bpName);
    if (!_writeCommand(command)) return false;
    std::string readBuffer;
    bool ret = _readTillPostAmble(readBuffer);
    std::cout << __func__ << ": " << readBuffer << std::endl;
    return ret;
}

bool GdbBridge::execContinue()
{
    std::string command = "-exec-continue";
    if (!_writeCommand(command)) return false;
    std::string readBuffer;
    bool ret = _readTillPostAmble(readBuffer);
    std::cout << __func__ << ": " << readBuffer << std::endl;
    return ret;
}

bool GdbBridge::showLocals(bool bWithValues)
{
    std::string command = "-stack-list-locals ";
    command.append(bWithValues ? "1" : "0");
    if (!_writeCommand(command)) return false;
    std::string readBuffer;
    bool ret = _readTillPostAmble(readBuffer);
    std::cout << __func__ << ": " << readBuffer << std::endl;
    return ret;
}

bool GdbBridge::_writeCommand(const std::string & command)
{
    std::string cmd = command;
    cmd.append("\n");
    strncpy(_writeBuffer, cmd.c_str(), cmd.length());
    _writeBuffer[cmd.length()] = '\0';

    int nBytesWritten = write(_getWriteFd(), _writeBuffer, cmd.length()); 
    if (!nBytesWritten) return false;
    return true;
}

bool GdbBridge::_readTillPostAmble(std::string & readValue)
{
    readValue.clear();
    std::string readBuffer;
    std::string termString = "(gdb) \n";
    int nBytesRead = 0;
    while (1) {
        if ((nBytesRead = read(_getReadFd(), _readBuffer, 256))) {
            _readBuffer[nBytesRead] = 0;
            readValue.append(_readBuffer);
            if (readValue.length() < termString.length()) continue;
            if (readValue.substr(readValue.length() - termString.length()) == termString) {
                return true;
            }
        }
        else return false;
    }
    return false;
}

int GdbBridge::_getWriteFd() const
{
    return _writePipeDescriptors[1];
}

int GdbBridge::_getReadFd() const
{
    return _readPipeDescriptors[0];
}

int GdbBridge::_getGdbWriteFd() const
{
    return _readPipeDescriptors[1];
}

int GdbBridge::_getGdbReadFd() const
{
    return _writePipeDescriptors[0];
}
