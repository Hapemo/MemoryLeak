using System;
using System.Runtime.CompilerServices;

namespace SCRIPTING
{
    public class TestClass
    {
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        internal extern static string TestFunction();

        private string hello = "Hello World!";
        public void Init()
        {
            this.hello = "Initing...";
            Console.WriteLine("Printing from C#: " + this.hello);
            TestFunction();
        }
        public void Update()
        {
            this.hello = "Updating...";
            Console.WriteLine("Printing from C#: " + this.hello);
        }
        public void Exit()
        {
            this.hello = "Exiting...";
            Console.WriteLine("Printing from C#: " + this.hello);
        }
    }
}
