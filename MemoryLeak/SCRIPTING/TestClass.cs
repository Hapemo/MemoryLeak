using System;
using System.Runtime.CompilerServices;

namespace BonVoyage
{
    public class TestClass
    {
        //[MethodImplAttribute(MethodImplOptions.InternalCall)]
       // internal extern static void RegisterMonoScript(string _namespace, string _class);
        //internal extern static string GetWorldMousePos();

        private string hello = "Hello World!";
        public void Init()
        {
            this.hello = "Initing...";
            Console.WriteLine("Printing from C#: " + this.hello);
            //Console.WriteLine(GetWorldMousePos());
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
