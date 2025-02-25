project(md VERSION 0.1)
add_executable(md)
target_sources(md PRIVATE main.cpp gdbCommand.cpp gdbBridge.cpp)
