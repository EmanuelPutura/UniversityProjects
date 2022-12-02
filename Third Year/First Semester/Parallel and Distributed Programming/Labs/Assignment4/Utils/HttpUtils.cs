using System;
using System.Collections.Generic;
using System.Text;

namespace Assignment4.Utils
{
    class HttpUtils
    {
        public static string GetResponseBody(string responseContent)
        {
            var responseParts = responseContent.Split(new[] { "\r\n\r\n" }, StringSplitOptions.RemoveEmptyEntries);

            return responseParts.Length > 1 ? responseParts[1] : "";
        }

        public static bool ResponseHeaderFullyObtained(string responseContent)
        {
            return responseContent.Contains("\r\n\r\n");
        }

        public static int GetContentLength(string responseContent)
        {
            var contentLength = -1;
            var responseLines = responseContent.Split('\r', '\n');

            foreach (var responseLine in responseLines)
            {
                var headerDetails = responseLine.Split(':');

                if (headerDetails[0].CompareTo("Content-Length") == 0)
                {
                    contentLength = int.Parse(headerDetails[1]);
                }
            }

            return contentLength;
        }
    }
}
