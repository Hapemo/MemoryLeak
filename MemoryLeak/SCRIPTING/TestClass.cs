using System;

namespace SCRIPTING
{
    public class TestClass
    {
        private string hello;
        public void Update()
        {
            this.hello = "Hello World!";
            Console.WriteLine("Printing: " + this.hello);
        }

    }
}
