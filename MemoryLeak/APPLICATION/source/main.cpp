/*!
@file    main.cpp
@author  j.teoh@digipen.edu
@date    13/05/2022

This file uses functionality defined in types Helper and GLApp to initialize 
an OpenGL context and implement a game loop.

*//*__________________________________________________________________________*/

/*                                                                   includes
----------------------------------------------------------------------------- */
// Extension loader library's header must be included before GLFW's header!!!
#include <Helper.h>
#include "pch.h"
#include "Application.h"
#include "GameStateManager.h"
#include "SignalHandler.h"
#include "SparseSet.h"




/*                                                   type declarations
----------------------------------------------------------------------------- */


/*                                                      function definitions
----------------------------------------------------------------------------- */
/*  _________________________________________________________________________ */
/*! main

@param none

@return int

Indicates how the program existed. Normal exit is signaled by a return value of
0. Abnormal termination is signaled by a non-zero return value.
Note that the C++ compiler will insert a return 0 statement if one is missing.
*/


void real_main() {
    std::signal(SIGABRT, HandleAbort);
    std::signal(SIGTERM, HandleTerminate);
    std::signal(SIGSEGV, HandleSegFault);
    std::signal(SIGILL, HandleIllegal);
    std::signal(SIGFPE, HandleInvalidOp);

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
        GameStateManager::GetInstance()->Loop();
    }

    // Part 3
    Application::exit();
}

int main() {
    try {
        /*
        LOG_INFO("The program has started.");

        LOG_CUSTOM_CREATE("CUSTOMNAME");
        LOG_CUSTOM("CUSTOMNAME", "Testing Custom Message");

        std::string message = "Hello World!";
        int num = 1;
        LOG_INFO(("Message is: " + message + " Number is: " + std::to_string(num)).c_str());

        ASSERT(num == 2, "Test Assert!");
        */

        real_main();
    }
    catch (const std::exception& e) {
        std::string exc = e.what();
        LOG_CRASH("The program has caught an exception: " + exc);
    }
}
