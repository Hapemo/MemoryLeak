using System;
using System.Runtime.CompilerServices;

namespace BonVoyage
{
    public class TestMonoScript
    {
        private string hello = "Hello World!";
        public void Init()
        {
            this.hello = "Initing...";
            Console.WriteLine("Printing from C#: " + this.hello);

            // Getting C++ int
            Console.WriteLine(InternalCalls.GetWorldMousePosX());

            // Passing C# string to C++
            InternalCalls.TestArgString("Passed in from C#!");

            // Getting C++ string to print in C#
            Console.WriteLine(InternalCalls.TestReturnString());

            // Loading dialogue file
            InternalCalls.LoadDialogs("Dialogue LittleGirl 0");
        }
        public void Update()
        {
            this.hello = "Updating...";

            // Press D to print
            if (InternalCalls.CheckKeyPress(68)) {
                this.hello = "PRESSED!";
                Console.WriteLine("Printing from C#: " + this.hello);

                // Printing dialogue index 1 of loaded dialogue file
                Console.WriteLine(InternalCalls.GetDialogue(1));
            }
        }
        public void Exit()
        {
            this.hello = "Exiting...";
            Console.WriteLine("Printing from C#: " + this.hello);
        }
    }
}
