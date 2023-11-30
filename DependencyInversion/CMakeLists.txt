cmake_minimum_required(VERSION 3.0)

project(DependencyInversion LANGUAGES CXX)
 
add_executable(main src/main.cpp src/ui/display.cpp src/domain/StateMachine.cpp src/driver/BarrierActuatorStub.cpp)
