#include "gdbBridge.h"
#include <iostream>
#include <cstdlib>

int main(int argc, char ** argv)
{
    GdbBridge bridge;
    bool ret = bridge.spawnGdb();
    int pId = 0;
    std::cout << "Enter pid to attach to > ";
    std::cin >> pId;
    std::cout << "INFO: Attaching to process " << pId << " ..." << std::endl;
    ret = bridge.attachToProcess(pId);
    if (!ret) exit(-1);
    std::cout << "INFO: Attached." << std::endl;

  //std::vector<std::string> bpList;
    std::string bp;
    std::cin.ignore();

    while (1) { // read breakpoints till eol
        std::cout << "Enter breakpoint position > ";
        std::getline(std::cin, bp);
        if (bp.empty()) break;
        ret = bridge.setBreakpoint(bp);

        if (!ret) {
            std::cout << "ERROR: Breakpoint not set (" << bp << ")" << std::endl;
            continue;
        } else std::cout << "INFO: Breakpoint set successfully" << std::endl;

      //bpList.append(bp);
    }


    while (1) {
        ret = bridge.execContinue();
        std::cout << "INFO: Waiting for breakpoint hits..." << std::endl;
        ret = bridge.pollBreakpointHit();

        if (ret) {
            std::cout << "INFO: Breakpoint hit." << std::endl;
            ret = bridge.showLocals();
        }
    }

    std::cout << "INFO: Exit." << std::endl;
    return 0;
}
