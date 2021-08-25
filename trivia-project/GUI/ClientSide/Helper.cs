using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClientSide
{
    /// <summary>
    /// the class help with some stuff
    /// </summary>
    class Helper
    {
        static public String FormatMsgLen(int msg_len)
        {
            String formatted_len = msg_len.ToString();
            if (formatted_len.Length < 5)
                for (int i = 0; i < 5 - formatted_len.Length; i++)
                    formatted_len = "0" + formatted_len;

            return formatted_len;
        }

        /// <summary>
        /// the func make byte array from json string and msg code
        /// </summary>
        /// <param name="msg"> json str </param>
        /// <param name="code"> msg code </param>
        /// <returns> byte arr (encoded msg) </returns>
        static public byte[] SerializeMsg(string msg, int code)
        {
            // define vars
            List<Byte> l = new List<byte>();
            byte b = (byte)code;
            // make byte list 
            l.Add(b); // add code
            l.AddRange(Encoding.UTF8.GetBytes(FormatMsgLen(msg.Length))); // add size and reverse because little endian
            l.AddRange(Encoding.UTF8.GetBytes(msg)); // add json string

            // return byte arr
            return l.ToArray();
        }

        /// <summary>
        /// the func add two json strings into one
        /// </summary>
        /// <param name="json1"> one json </param>
        /// <param name="json2"> othe json </param>
        /// <returns> one json str </returns>
        static public string AddTwoJson(string json1, string json2)
        {
            // {....}{....}
            string res = json1.Replace("}", ","); // {....,{....}
            res += json2.Replace("{", " "); // {...., ....}
            return res;
        }

        /// <summary>
        /// the func add key and val into dict 
        /// and check if the val is good
        /// 
        /// the func used most where i get 
        /// input from user and need to check if
        /// there is any input
        /// 
        /// </summary>
        /// <param name="dict"> the dict to add </param>
        /// <param name="key"> the key </param>
        /// <param name="val"> the val </param>
        /// <returns> the key is good or not </returns>
        public static bool AddToJson(Dictionary<string, string> dict, string key, string val)
        {
            //define var
            bool good = true;

            // the val is empty
            if (val == "")
            {
                good = false;
            }
            // add
            else
            {
                dict.Add(key, val);
            }

            return good;
        }
    }    
}
