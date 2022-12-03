using System;
using System.Collections.Generic;
using Assignment4.Methods;

namespace Assignment4
{
    class Program
    {
        private static readonly List<string> Urls = new List<string>
        {
            "www.leetcode.com/",
            "www.tradingview.com/",
            "www.cs.ubbcluj.ro/~rlupsa/",
        };

        static void Main(string[] args)
        {
            Console.WriteLine("1. Callbacks Method");
            Console.WriteLine("2. Tasks Method");
            Console.WriteLine("3. Async Await Method");

            string choice = Console.ReadLine();
            switch (choice)
            {
                case "1":
                    new CallbacksMethod(Urls);
                    break;
                case "2":
                    new TasksMethod(Urls);
                    break;
                case "3":
                    new AsyncAwaitMethod(Urls);
                    break;
                default:
                    Console.WriteLine("Invalid command!");
                    break;
            }
        }
    }
}
