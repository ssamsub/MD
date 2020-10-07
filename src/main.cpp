#include "gdbBridge.h"
#include <iostream>
#include <cstdlib>

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
    if (ret) std::cout << "Breakpoint set successfully" << std::endl;
    else {
        std::cout << "Error in setting breakpoint" << std::endl;
        exit(-1);
    }

    std::cout << " Press enter to show local variables" << std::endl;
    std::string anyString;
    std::cin >> anyString;
    bridge.flush();
    ret = bridge.showLocals();
    std::cout << " ret of showLocals " << ret << std::endl;

    
    std::cout << __func__ << ": exiting main " << std::endl;
    return 0;
}
