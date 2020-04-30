#include "gdbBridge.h"
#include <stdlib>
#include <iostream>

GdbBridge::GdbBridge()
{
}

void GdbBridge::spawnGdb()
{
    pipe(_pipeDescritor);
    std::cout << "_pipeDescritor[" << _pipeDescritor[0] << " : " << _pipeDescritor[1];

    if (fork()) {
    } else {
    }

}

