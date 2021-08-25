using System.Collections.Generic;

namespace ClientSide
{
    /// <summary>
    /// this is class that represent a room
    /// </summary>
    public class Room
    {
        // vars
        private string name;
        private uint id;
        private uint num_of_question;
        private uint timePerQuestion;
        private uint msxPlayers;
        private List<string> players;

        // getters and setters
        public uint Id { get => id; set => id = value; }
        public string Name { get => name; set => name = value; }
        public uint Num_of_question { get => num_of_question; set => num_of_question = value; }
        public uint TimePerQuestion { get => timePerQuestion; set => timePerQuestion = value; }
        public uint MsxPlayers { get => msxPlayers; set => msxPlayers = value; }
        public List<string> Players { get => players; set => players = value; }
    }

    /// <summary>
    /// that class represent user
    /// </summary>
    public static class User
    {
        // vars
        private static string username = "";
        private static bool is_admin = false;
        private static Room userRoom = new Room();

        // getters and setters
        public static bool Is_admin { get => is_admin; set => is_admin = value; }
        public static string Username { get => username; set => username = value; }
        public static Room UserRoom { get => userRoom; set => userRoom = value; }

        //init a room
        public static void initRoom(string rname, uint unum, uint qnum, uint time)
        {
            //define vars
            userRoom.Name = rname;
            userRoom.Num_of_question = qnum;
            userRoom.MsxPlayers = unum;
            userRoom.Id = 1;
            userRoom.TimePerQuestion = time;
            userRoom.Players = new List<string>();
        }
    }
}
