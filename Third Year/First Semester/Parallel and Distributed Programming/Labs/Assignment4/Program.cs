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
            new AsyncAwaitMethod(Urls);
        }
    }
}
