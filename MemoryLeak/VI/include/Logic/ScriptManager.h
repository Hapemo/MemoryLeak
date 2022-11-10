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
#include "RotateScript.h"

template<class Base>
class ScriptManager {
public:
    typedef std::pair<std::string, RotateScript*> ScriptPair;
    typedef std::map<std::string, RotateScript*> ScriptMap;

private:
    ScriptMap mScripts;
    static std::shared_ptr<ScriptManager<Base>> mInstance;

public:
    void ScriptingFree() {
        delete mScripts["RotateScript"];
        //for (const ScriptPair script : mScripts)
        //{
        //    if (script.second != nullptr)
        //    {
        //        //delete script.second;
        //        LOG_INFO("delete script");
        //    }
        //    else
        //        LOG_INFO("script null ptr");
        //}
    }

    static std::shared_ptr<ScriptManager<Base>> GetInstance() {
        if (mInstance == nullptr)
        {
            mInstance = std::make_unique<ScriptManager<Base>>();
            LOG_INFO("instanceeeeeeeeeeeeeeeeee");
        }
      return mInstance;
    }

    template<class Script>
    void RegisterScript() {
        //Base* script = new Script;
        RotateScript* script = new RotateScript;
        //mScripts.insert({ "RotateScript", script });
        mScripts["RotateScript"] = script;
       //delete mScripts["RotateScript"];
        LOG_INFO("NEWWWWWWWWWWWW Script");
    }

    Base* GetScript(const std::string _name) {
        const ScriptMap::iterator script = mScripts.find(_name);
        if (script == mScripts.end()) return nullptr; // not a derived class
        else return script->second;
    }

    void PrintRegisteredScripts() {
       /* for (const ScriptPair& script : mScripts)
            LOG_INFO(script.first.c_str());*/
    }
};

template<class Base>
std::shared_ptr<ScriptManager<Base>> ScriptManager<Base>::mInstance;

template<class Base, class Script>
class ScriptFactory {
public:
    ScriptFactory()
    {
        ScriptManager<Base>::GetInstance()->RegisterScript<Script>();
    }
    /*ScriptFactory(const std::string _name) {
        ScriptManager<Base>::GetInstance()->RegisterScript<Script>(_name);
    }*/
};
