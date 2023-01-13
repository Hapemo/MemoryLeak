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
            Console.WriteLine(InternalCalls.GetWorldMousePosX());
        }
        public void Update()
        {
            //this.hello = "Updating...";
            Console.WriteLine("Printing from C#: " + this.hello);

            if (InternalCalls.CheckKeyPress(68))
            {
                this.hello = "PRESSED!";
            }
        }
        public void Exit()
        {
            this.hello = "Exiting...";
            Console.WriteLine("Printing from C#: " + this.hello);
        }
    }
}
