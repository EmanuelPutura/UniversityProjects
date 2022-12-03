using System;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace Assignment4.SocketHandler
{
    class UrlsSocketHandler : System.Net.Sockets.Socket
    {
        private const int DefaultHttpPort = 80;

        private const int BufferSize = 1024;

        private StringBuilder Response { get; } = new StringBuilder();

        public int Id { get; }

        public string BaseUrl { get; }

        public string UrlPath { get; }

        private IPEndPoint EndPoint { get; }

        public string GetResponse => Response.ToString();

        public static UrlsSocketHandler Create(string url, int id)
        {
            var index = url.IndexOf('/');
            var baseUrl = index < 0 ? url : url[..index];
            var urlPath = index < 0 ? "/" : url[index..];

            var ipHostInformation = Dns.GetHostEntry(baseUrl);
            var ipAddress = ipHostInformation.AddressList[0];

            return new UrlsSocketHandler(baseUrl, urlPath, ipAddress, id);
        }

        private UrlsSocketHandler(string baseUrl, string urlPath, IPAddress ipAddress, int id) :
            base(ipAddress.AddressFamily, SocketType.Stream, ProtocolType.Tcp)
        {
            Id = id;
            BaseUrl = baseUrl;
            UrlPath = urlPath;
            EndPoint = new IPEndPoint(ipAddress, DefaultHttpPort);
        }

        public void BeginConnect(Action<UrlsSocketHandler> onConnected)
        {
            BeginConnect(EndPoint, result => {
                EndConnect(result);
                onConnected(this);
            }, null);
        }

        public void BeginSend(Action<UrlsSocketHandler, int> onSent)
        {
            var getRequest = $"GET {UrlPath} HTTP/1.1\r\n" +
                $"Host: {BaseUrl}\r\n" +
                "Content-Length: 0\r\n\r\n";
            var encodedGetRequest = Encoding.ASCII.GetBytes(getRequest);

            BeginSend(encodedGetRequest, 0, encodedGetRequest.Length, SocketFlags.None, result => {
                var numberOfSentBytes = EndSend(result);
                onSent(this, numberOfSentBytes);
            }, null);
        }

        public void BeginReceive(Action<UrlsSocketHandler> onReceived)
        {
            var buffer = new byte[BufferSize];
            Response.Clear();

            BeginReceive(buffer, 0, BufferSize, SocketFlags.None, result =>
                HandleReceiveAsyncResult(result, buffer, onReceived), null);
        }

        private void HandleReceiveAsyncResult(
            IAsyncResult asyncResult,
            byte[] buffer,
            Action<UrlsSocketHandler> onReceived)
        {
            var numberOfBytes = EndReceive(asyncResult);
            Response.Append(Encoding.ASCII.GetString(buffer, 0, numberOfBytes));
            if (!Response.ToString().Contains("</html>"))
            {
                BeginReceive(buffer, 0, BufferSize, SocketFlags.None, result =>
                    HandleReceiveAsyncResult(result, buffer, onReceived), null);
                return;
            }

            onReceived(this);
        }

        public void ShutdownAndClose()
        {
            Shutdown(SocketShutdown.Both);
            Close();
        }

        public Task BeginConnectAsync() => Task.Run(() =>
        {
            var taskCompletion = new TaskCompletionSource<bool>();

            BeginConnect(_ => {
                bool tmp = true;
                taskCompletion.TrySetResult(tmp); 
            });

            return taskCompletion.Task;
        });

        public Task<int> BeginSendAsync() => Task.Run(() =>
        {
            var taskCompletion = new TaskCompletionSource<int>();

            BeginSend((_, numberOfSentBytes) =>
                taskCompletion.TrySetResult(numberOfSentBytes));

            return taskCompletion.Task;
        });

        public Task BeginReceiveAsync() => Task.Run(() =>
        {
            var taskCompletion = new TaskCompletionSource<bool>();

            BeginReceive(_ => {
                bool tmp = true;
                taskCompletion.TrySetResult(tmp);
            });

            return taskCompletion.Task;
        });
    }
}
