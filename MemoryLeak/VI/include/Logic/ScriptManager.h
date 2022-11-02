/*!*****************************************************************************
\file ScriptManager.h
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 02-11-2022
\brief
This file contains the function declarations of the class ScriptManager.
The ScriptManager class manages the scripts for the engine.
*******************************************************************************/

#pragma once
#include "Singleton.h"
#include <map>
#include <functional>
#include <string>
#include <iostream>

#define REGISTER_SCRIPT(_base, _derived) ScriptFactory<_base, _derived> s_##_derived##Creator(#_derived);

template<class Base>
class ScriptManager : public Singleton<ScriptManager<Base>> {
public:
    typedef std::map<std::string, std::function<Base* ()>> ScriptMap;

private:
    ScriptMap mScripts;

public:
    template<class Script>
    void RegisterScript(const std::string& _name) {
        mScripts.insert({ _name, []() -> Base* { return new Script(); } });
    }

    Base* GetScript(const std::string& _name) {
        const ScriptMap::iterator script = mScripts.find(_name);
        if (script == mScripts.end()) return nullptr; // not a derived class
        else return (script->second)();
    }

    void PrintRegisteredScripts() {
        for (const auto& creator : mScripts)
            LOG_INFO(creator.first.c_str());
    }
};

template<class Base, class Script>
class ScriptFactory {
public:
    explicit ScriptFactory(const std::string& _name) {
        ScriptManager<Base>::GetInstance()->RegisterScript<Script>(_name);
    }
};
