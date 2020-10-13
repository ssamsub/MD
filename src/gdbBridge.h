#ifndef GDB_BRIDGE_H
#define GDB_BRIDGE_H
#include <string>

using std::string;

class GdbBridge 
{
public:
    GdbBridge();
    ~GdbBridge();
    bool    spawnGdb();
    bool    attachToProcess(int pId);
    bool    setBreakpoint(const std::string & bpName);
    bool    execContinue();
    bool    pollBreakpointHit();
    bool    showLocals(bool bWithValues = true);
    bool    flush();    // remove anything left from read buffer
        
    bool    executeCommand(const std::string & command, std::string & result);


private:
    int _getWriteFd() const;
    int _getReadFd() const;
    int _getGdbWriteFd() const;
    int _getGdbReadFd() const;


    bool    _readTillPostAmble(std::string & readValue);
    bool    _writeCommand(const std::string & command);



private:
    int _writePipeDescriptors[2];
    int _readPipeDescriptors[2];

    bool    _gdbStarted;
    char *  _readBuffer;
    char *  _writeBuffer;

};
#endif
