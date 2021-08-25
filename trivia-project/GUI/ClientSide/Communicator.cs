using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using Newtonsoft.Json;


namespace ClientSide
{
    /// <summary>
    /// the class do all the communication stuff
    /// </summary>
    class Communicator
    {
        // define vars
        static private int port;
        static private string ip;
        static private TcpClient client = new TcpClient();
        static private IPEndPoint serverEndPoint;
        static private NetworkStream clientStream;
        static private bool endCommunicate = true;

        // get and set
        public static bool EndCommunicate { get => endCommunicate; set => endCommunicate = value; }

        static public void Connect()
        {
            // becuase all the reopen main window
            // check if there is connection
            if (!client.Connected)
            {
                // connect to server
                client = new TcpClient();
                serverEndPoint = new IPEndPoint(IPAddress.Parse(ip), port);
                client.Connect(serverEndPoint);
                clientStream = client.GetStream();
            }
        }

        /// <summary>
        /// the func send a msg
        /// </summary>
        /// <param name="arr"> the msg to send encoded </param>
        /// <param name="arr_size"> the msg len </param>
        static public void SendMsg(byte[] arr, int arr_size)
        {
            clientStream.Write(arr, 0, arr_size);
            clientStream.Flush();
        }

        /// <summary>
        /// the func get msg from server
        /// </summary>
        /// <returns> pair: the key is the msg code and the val is string of json </returns>
        static public KeyValuePair<int, string> GetMsg()
        {
            // read five bytes of msg, first is the code and other four is size of json
            byte[] sizeBuffer = new byte[5];
            int bytesRead = clientStream.Read(sizeBuffer, 0, 5);

            // get size
            IEnumerable<byte> a = sizeBuffer.Reverse().Take(4); // reverse the arr and take four bytes of size
            byte[] arr = a.ToArray(); // make the four bytes array again
            uint size = BitConverter.ToUInt32(arr, 0); // convert to int

            // read the num of bytes like the size (that only the json)
            byte[] buffer = new byte[size * 2];
            bytesRead = clientStream.Read(buffer, 0, (int)size * 2);

            // decode the json from byte to string
            string str = Encoding.UTF8.GetString(buffer, 0, (int)size);
            if(str == "{\"rooms\":[[0,\"room_name\"]]}")
            {
                return new KeyValuePair<int, string>(0, str);
            }
            var json = JsonConvert.DeserializeObject<Dictionary<string, string>>(str);
            // return pair: key = msgCode, val = jsonString
            return new KeyValuePair<int, string>(int.Parse(json["status"]), str);
        }

        /// <summary>
        /// the func close the communication
        /// and send the logout msg
        /// </summary>
        static public void Finish()
        {
            // because we close a lots of windows with command Close
            // we need to know if the window closed with command or with X button
            // so, if endCommunicate = true: the user press on X button
            if (endCommunicate)
            {
                // define json msg
                string jsonString = "{\"username\": \"" + User.Username + "\"}";

                // make the json string into byte array
                byte[] arr = Helper.SerializeMsg(jsonString, 104); // Logout code
                Communicator.SendMsg(arr, arr.Length); // send
                client.Close(); // close socket
            }
            endCommunicate = true; // the endCommunicate default val is true
        }

        /// <summary>
        /// the function get ip and port from text file
        /// </summary>
        /// <param name="path"> path to file </param>
        static public void Init(string path)
        {
            // Read the file as one string.
            string[] text = System.IO.File.ReadAllLines(path);

            // get ip and port
            ip = text[0].Split('=')[1];
            port = Convert.ToInt32(text[1].Split('=')[1]);
        }
    }

}
