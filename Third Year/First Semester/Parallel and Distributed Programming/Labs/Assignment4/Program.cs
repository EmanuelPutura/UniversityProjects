using System;
using System.Collections.Generic;
using Assignment4.Methods;

namespace Assignment4
{
    class Program
    {
        private static readonly List<string> Urls = new List<string>
        {
            "www.cs.ubbcluj.ro/",
            "www.tradingview.com/"
        };

        static void Main(string[] args)
        {
            new CallbacksMethod(Urls);
        }
    }
}
