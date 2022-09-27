/*!*****************************************************************************
\file main.cpp
\author Jazz Teoh Yu Jue
\par DP email: j.teoh\@digipen.edu
\par Group: Memory Leak Studios
\date 24-09-2022
\brief
main file of the whole program
*******************************************************************************/

// Extension loader library's header must be included before GLFW's header!!!
#include <Helper.h>
#include "pch.h"
#include "Application.h"
#include "GameStateManager.h"
#include "SignalHandler.h"
#include "SparseSet.h"

/*  _________________________________________________________________________ */
/*! main

@param none

@return int

Indicates how the program existed. Normal exit is signaled by a return value of
0. Abnormal termination is signaled by a non-zero return value.
Note that the C++ compiler will insert a return 0 statement if one is missing.
*/

/*!*****************************************************************************
 \brief
 child main file that runs the application
*******************************************************************************/
void real_main() {
    std::signal(SIGABRT, HandleSignal);
    std::signal(SIGTERM, HandleSignal);
    std::signal(SIGINT, HandleSignal);
    std::signal(SIGSEGV, HandleSignal);
    std::signal(SIGILL, HandleSignal);
    std::signal(SIGFPE, HandleSignal);

    // Part 1
    Application::init();

#if 0 // Testing SparseSet
    SparseSet<double> set(20);
    int count1{ 15 };
    while (count1--) set.AddData(10 * count1 + 1, count1);
    set.PrintSet();

    set.RemoveData(2);
    set.RemoveData(4);
    set.RemoveData(7);
    set.RemoveData(9);
    set.RemoveData(13);
    set.RemoveData(1);

    set.PrintSet();

    set.AddData(999, 2);
    set.AddData(999, 4);
    set.AddData(999, 7);
    set.PrintSet();

    count1 = 15;
    while (count1--) {
      if (count1 == 9 || count1 == 13 || count1 == 1) continue;
      std::cout << "index: " << count1 << " | data: " << set[count1] << '\n';
    }

#endif

    // Part 2
    while (!glfwWindowShouldClose(Application::getWindow())) {
        GameStateManager::GetInstance()->Update();
    }

    // Part 3
    Application::exit();
}

/*!*****************************************************************************
 \brief
 The master main file that runs a child main file and catches exceptions that it
 throws
 
 \int main int
*******************************************************************************/
int main() {
    try {
        /*
        //logging strings
        LOG_INFO("The program has started.");

        //logging integers/floats etc
        float f = 0.1f;
        LOG_INFO(f);

        //creating and using custom log type
        LOG_CUSTOM_CREATE("CUSTOMNAME");
        LOG_CUSTOM("CUSTOMNAME", "Testing Custom Message");

        //logging strings and integers/floats etc
        std::string message = "Hello World!";
        int num = 1;
        LOG_INFO(("Message is: " + message + " Number is: " + std::to_string(num)).c_str());

        //asserting
        ASSERT(num == 1, "Test Assert!");

        //throwing exception
        THROW(Logger::E_EXCEPTION::RUNTIME_ERR, "File for vertex shader not found!");
        */

        Util::EnableMemoryLeakChecking(); //dialog manager
        //Util::EnableMemoryLeakChecking(22390); //dialog manager
        //Util::EnableMemoryLeakChecking(22388); //audio memleak

        real_main();
    }
    catch (const std::exception& e) {
        std::string exc = e.what();
        LOG_CRASH("The program has caught an exception: " + exc);
    }
}
