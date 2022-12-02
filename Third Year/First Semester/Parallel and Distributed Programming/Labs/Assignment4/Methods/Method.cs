using System;
using System.Collections.Generic;
using Assignment4.SocketHandler;
using System.Text;

using Assignment4.Utils;

namespace Assignment4.Methods
{
    abstract class Method
    {
        private List<string> Urls { get; }

        protected abstract string MethodType { get; }
        
        protected Method(List<string> urls)
        {
            Urls = urls;
            RunMethod();
        }

        protected abstract void RunMethod();

        protected void CallUrlActionsWithIndex(Action<string, int> action)
        {
            var index = 0;
            Urls.ForEach(url => action(url, index++));
        }

        protected void LogConnected(UrlsSocketHandler socket)
        {
            Console.WriteLine($"{MethodType}-{socket.Id}: Socket connected to {socket.BaseUrl} ({socket.UrlPath})");
        }

        protected void LogSent(UrlsSocketHandler socket, int numberOfSentBytes)
        {
            Console.WriteLine($"{MethodType}-{socket.Id}: Sent {numberOfSentBytes} bytes to server.");
        }

        protected void LogReceived(UrlsSocketHandler socket)
        {
            // Console.WriteLine(socket.GetResponse);

            var headerContentLength = HttpUtils.GetContentLength(socket.GetResponse);
            if (headerContentLength == -1)
            {
                Console.WriteLine($"Header Content-Length for {socket.BaseUrl}{socket.UrlPath}: not specified\n");
            }
            else
            {
                Console.WriteLine($"Header Content-Length for {socket.BaseUrl}{socket.UrlPath}: {headerContentLength} bytes\n");
            }
        }
    }
}
