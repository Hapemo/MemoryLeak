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
#include <map>
#include <functional>
#include <string>
#include "Singleton.h"
#include "Logger.h"

#define REGISTER_SCRIPT(_base, _derived) ScriptFactory<_base, _derived> s_##_derived##Creator(#_derived);

template<class Base>
class ScriptManager : public Singleton<ScriptManager<Base>> {
public:
    typedef std::pair<std::string, std::function<Base* ()>> ScriptPair;
    typedef std::map<std::string, std::function<Base* ()>> ScriptMap;

private:
    ScriptMap mScripts;

public:
    ScriptManager() {
        LOG_ERROR("script manager constructed!!!");
    };
    ~ScriptManager() {
        LOG_ERROR("Destroying script manager!");
        for (const ScriptPair& script : mScripts)
            if(script.second())
                delete script.second();
    }

    template<class Script>
    void RegisterScript(const std::string& _name) {
        (void)_name;
        //mScripts.insert({ _name, []() -> Base* { return new Script(); } });
    }

    Base* GetScript(const std::string& _name) {
        const ScriptMap::iterator script = mScripts.find(_name);
        if (script == mScripts.end()) {
            LOG_ERROR("Error retrieving script: " + _name);
            return nullptr; // not a derived class
        } else return (script->second)();
    }

    void PrintRegisteredScripts() {
        for (const ScriptPair& script : mScripts)
            LOG_INFO(script.first.c_str());
    }

    ScriptMap GetScripts() { return mScripts; }
};

template<class Base, class Script>
class ScriptFactory {
public:
    explicit ScriptFactory(const std::string& _name) {
        ScriptManager<Base>::GetInstance()->RegisterScript<Script>(_name);
    }
};
