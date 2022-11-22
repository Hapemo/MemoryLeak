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
#include <string>
#include "Logger.h"

#define REGISTER_SCRIPT(_base, _derived) ScriptRegisterer<_base, _derived> s_##_derived##Creator(#_derived)

template<class Base>
class ScriptManager {
public:
    typedef std::pair<std::string, Base*> ScriptPair;
    typedef std::map<std::string, Base*> ScriptMap;

private:
    ScriptMap mScripts;
    static std::shared_ptr<ScriptManager<Base>> mInstance;

public:
    ScriptManager() = default;
    ~ScriptManager() = default;

    void UnloadScripts() {
#ifdef NDEBUG
#else
        std::cout << "Unloading scripts\n";
#endif
        for (const ScriptPair& script : mScripts) {
            if (script.second != nullptr) {
                delete script.second;
#ifdef NDEBUG
#else
                std::cout << "Deleting script: " << script.first << "\n";
#endif
                //LOG_INFO("Deleting script: " + script.first);
            } //else LOG_ERROR("Null pointer to script: " + script.first);
            else {
#ifdef NDEBUG
#else
                std::cout << "Null pointer to script: " << script.first << "\n";
#endif
            }
        }
        mScripts.clear();
    }

    static std::shared_ptr<ScriptManager<Base>> GetInstance() {
        if (mInstance == nullptr)
            mInstance = std::make_unique<ScriptManager<Base>>();
        return mInstance;
    }

    template<class Script>
    bool RegisterScript(const std::string _name) {
        Base* script = new Script;
        mScripts.insert({_name, script});
#ifdef NDEBUG
#else
        std::cout << "Registering script: " << _name << "\n";
#endif
        //LOG_INFO("Registering script: " + _name);
        return true;
    }

    Base* GetScript(const std::string _name) {
        const ScriptMap::iterator script = mScripts.find(_name);
        if (script == mScripts.end()) {
            //LOG_ERROR(("Script '" + _name + "' does not exist.").c_str());
#ifdef NDEBUG
#else
            std::cout << "Script '" << _name << "' does not exist." << "\n";
#endif
            return nullptr; // not a derived class
        }
        else return script->second;
    }

    void PrintRegisteredScripts() {
        //for (const ScriptPair& script : mScripts) LOG_INFO(script.first.c_str());
#ifdef NDEBUG
#else
        for (const ScriptPair& script : mScripts) std::cout << script.first.c_str() << "\n";
#endif
    }
};

template<class Base>
std::shared_ptr<ScriptManager<Base>> ScriptManager<Base>::mInstance;

template<class Base, class Script>
class ScriptRegisterer {
public:
    ScriptRegisterer() = default;
    ~ScriptRegisterer() = default;
    ScriptRegisterer(const std::string _name) {
        ScriptManager<Base>::GetInstance()->RegisterScript<Script>(_name);
    }
};
