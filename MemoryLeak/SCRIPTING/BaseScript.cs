﻿/*!*****************************************************************************
\file BaseScript.cs
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Group: Memory Leak Studios
\date 15-02-2023
\brief
Base script to be inherited by other scripts.
*******************************************************************************/
using System;
using System.Runtime.CompilerServices;

namespace BonVoyage
{
    public class BaseScript
    {
        int EntityID;
        public virtual void PreInit(int _id)
        {
            Console.Write("ID FROM PARAMS:");
            Console.Write(_id);
            Console.Write("\n---\n");
        }
    }
}
