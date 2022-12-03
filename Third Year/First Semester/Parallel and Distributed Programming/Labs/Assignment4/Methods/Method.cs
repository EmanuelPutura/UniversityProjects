using System;
using System.Collections.Generic;
using Assignment4.SocketHandler;
using System.Text;

using Assignment4.Utils;
using System.Linq;

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

        protected List<T> MapUrlActionToUrlActionWithIndex<T>(Func<string, int, T> action)
        {
            var index = 0;
            return Urls.Select(url => action(url, index++)).ToList();
        }

        protected void LogConnected(UrlsSocketHandler socket)
        {
            Console.WriteLine($"{MethodType}-{socket.Id}: Socket connected to {socket.BaseUrl} ({socket.UrlPath})");
        }

        protected void LogSent(UrlsSocketHandler socket, int numberOfSentBytes)
        {
            Console.WriteLine($"{MethodType}-{socket.Id}: Sent {numberOfSentBytes} bytes to server.");
        }

        protected string LogReceived(UrlsSocketHandler socket, bool writeToConsole=true)
        {
            // Console.WriteLine(socket.GetResponse);

            var headerContentLength = HttpUtils.GetContentLength(socket.GetResponse);
            string message = $"Header Content-Length for {socket.BaseUrl}{socket.UrlPath}: {headerContentLength} bytes\n";

            if (headerContentLength == -1)
            {
                message = $"Header Content-Length for {socket.BaseUrl}{socket.UrlPath}: not specified\n";
            }

            if (writeToConsole)
            {
                Console.WriteLine(message);
            }

            return message;
        }
    }
}
