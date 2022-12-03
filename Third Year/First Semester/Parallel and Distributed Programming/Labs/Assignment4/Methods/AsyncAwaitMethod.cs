using System;
using System.Collections.Generic;
using System.Text;
using System.Threading.Tasks;
using Assignment4.SocketHandler;

namespace Assignment4.Methods
{
    class AsyncAwaitMethod : Method
    {
        protected override string MethodType => "Tasks";

        protected override void RunMethod()
        {
            var tasks = MapUrlActionToUrlActionWithIndex((url, index) => Task.Run(() =>
               Start(UrlsSocketHandler.Create(url, index))));

            var results = Task.WhenAll(tasks).Result;
            foreach (var str in results)
            {
                Console.WriteLine(str);
            }
        }

        private async Task<string> Start(UrlsSocketHandler socket)
        {
            await socket.BeginConnectAsync();
            // LogConnected(socket);

            var numberOfSentBytes = await socket.BeginSendAsync();
            // LogSent(socket, numberOfSentBytes);

            await socket.BeginReceiveAsync();
            socket.ShutdownAndClose();

            return LogReceived(socket, false);
        }

        public AsyncAwaitMethod(List<string> urls) : base(urls) { }
    }
}
