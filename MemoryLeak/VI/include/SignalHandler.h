#pragma once
#include <csignal>
#include "Logger.h"

void HandleSignal(int _signalNumber)
{
    switch (_signalNumber) {
    case SIGABRT:
        LOG_CRASH("The program has called an abortion.");
        break;
    case SIGTERM:
        LOG_CRASH("The program has received a termination request.");
        break;
    case SIGINT:
        LOG_CRASH("The program has been interrupted externally.");
        break;
    case SIGSEGV:
        LOG_CRASH("The program has detected an invalid access to storage.");
        break;
    case SIGILL:
        LOG_CRASH("The program has detected an illegal instruction.");
        break;
    case SIGFPE:
        LOG_CRASH("The program has detected an erroneous arithmetic operation.");
        break;
    }
}

/*
SIGTERM	termination request, sent to the program
SIGSEGV	invalid memory access(segmentation fault)
SIGINT	external interrupt, usually initiated by the user
SIGILL	invalid program image, such as illegal instruction
SIGABRT	abnormal termination condition, as is e.g.initiated by std::abort()
SIGFPE	erroneous arithmetic operation such as divide by zero or an operation resulting in overflow
*/
