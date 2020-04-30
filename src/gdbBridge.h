#ifndef GDB_BRIDGE_H
#define GDB_BRIDGE_H

class GdbBridge 
{
public:
    GdbBridge();
    void spawnGdb();


private:
    int _pipeDescritor[2];

};
#endif
