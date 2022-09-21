#pragma once
#include <csignal>
#include "Logger.h"

void HandleAbort(int signal_number)
{
    LOG_CRASH("The program has called an abortion.");
}

void HandleTerminate(int signal_number)
{
    LOG_CRASH("The program has received a termination request.");
}

void HandleSegFault(int signal_number)
{
    LOG_CRASH("The program has detected an invalid access to storage.");
}

void HandleIllegal(int signal_number)
{
    LOG_CRASH("The program has detected an illegal instruction.");
}

void HandleInvalidOp(int signal_number)
{
    LOG_CRASH("The program has detected an erroneous arithmetic operation.");
}

/*
SIGTERM	termination request, sent to the program
SIGSEGV	invalid memory access(segmentation fault)
SIGINT	external interrupt, usually initiated by the user
SIGILL	invalid program image, such as illegal instruction
SIGABRT	abnormal termination condition, as is e.g.initiated by std::abort()
SIGFPE	erroneous arithmetic operation such as divide by zero or an operation resulting in overflow
*/
