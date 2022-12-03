using System;
using System.Collections.Generic;
using System.Text;
using System.Threading.Tasks;
using Assignment4.SocketHandler;

namespace Assignment4.Methods
{
    class TasksMethod : Method
    {
        protected override string MethodType => "Tasks";

        protected override void RunMethod()
        {
            var tasks = MapUrlActionToUrlActionWithIndex((url, index) => Task.Run(() =>
               Start(UrlsSocketHandler.Create(url, index))));

            var results = Task.WhenAll(tasks).Result;
            foreach(var str in results)
            {
                Console.WriteLine(str);
            }
        }

        private string Start(UrlsSocketHandler socket)
        {
            socket.BeginConnectAsync().Wait();
            // LogConnected(socket);

            var sendTask = socket.BeginSendAsync();
            sendTask.Wait();

            var numberOfSentBytes = sendTask.Result;
            // LogSent(socket, numberOfSentBytes);

            socket.BeginReceiveAsync().Wait();
            socket.ShutdownAndClose();

            return LogReceived(socket, false);
        }

        public TasksMethod(List<string> urls) : base(urls) { }

    }
}
