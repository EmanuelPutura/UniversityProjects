using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using Assignment4.SocketHandler;

namespace Assignment4.Methods
{
    class CallbacksMethod : Method
    {
        protected override string MethodType => "Callbacks";

        protected override void RunMethod()
        {
            CallUrlActionsWithIndex((url, index) => Start(UrlsSocketHandler.Create(url, index)));
        }

        public CallbacksMethod(List<string> urls) : base(urls) {}

        private void Start(UrlsSocketHandler socket)
        {
            socket.BeginConnect(HandleConnected);
            do
            {
                Thread.Sleep(100);
            }
            while (socket.Connected);
        }

        private void HandleConnected(UrlsSocketHandler socket)
        {
            LogConnected(socket);
            socket.BeginSend(HandleSent);
        }

        private void HandleSent(UrlsSocketHandler socket, int numberOfSentBytes)
        {
            LogSent(socket, numberOfSentBytes);
            socket.BeginReceive(HandleReceived);
        }

        private void HandleReceived(UrlsSocketHandler socket)
        {
            LogReceived(socket);
            socket.ShutdownAndClose();
        }
    }
}
