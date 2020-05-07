#include "gdbBridge.h"
#include <iostream>

int main(int argc, char ** argv)
{
    GdbBridge bridge;
    bool ret = bridge.spawnGdb();
    int pId = 0;
    std::cout << "Enter pid to attach to: ";
    std::cin >> pId;
    ret = bridge.attachToProcess(pId);
    if (!ret) exit(-1);

    std::cout << "Enter breakpoint position: ";
    std::string bp;
    std::cin >> bp;
    ret = bridge.setBreakpoint(bp);

    if (!ret) exit(-1);

    ret = bridge.execContinue();
    ret = bridge.showLocals();

    
    std::cout << __func__ << " exiting main " << std::endl;
    return 0;
}
