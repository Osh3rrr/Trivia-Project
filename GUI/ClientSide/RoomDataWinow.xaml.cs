using System.Collections.Generic;
using System.ComponentModel;
using System.Threading;
using System.Windows;
using Newtonsoft.Json;

namespace ClientSide
{
    /// <summary>
    /// Interaction logic for RoomDataWinow.xaml
    /// </summary>
    public partial class RoomDataWinow : Window
    {
        private Thread timer;

        public RoomDataWinow()
        {
            InitializeComponent();
            // if the user is admin it's show him start game button
            if (User.Is_admin)
            {
                StartButton.Visibility = Visibility.Visible;
            }
            else
            {
                StartButton.Visibility = Visibility.Hidden;
            }

            // show room info list
            NameLabel.Content = "the room is - " + User.UserRoom.Name.Replace("_", "__");
            InfoList.Items.Add("num of question: " + User.UserRoom.Num_of_question);
            InfoList.Items.Add("max num of users: " + User.UserRoom.MsxPlayers);
            InfoList.Items.Add("time per question: " + User.UserRoom.TimePerQuestion);

            // and show players list
            User.UserRoom.Players = new List<string>();
            User.UserRoom.Players.Add(User.Username);
            foreach (var i in User.UserRoom.Players)
            {
                UsersList.Items.Add(i);
            }

            // start clock that refresh players in room
            timer = new Thread(Tick);
            timer.Start();
        }

        private void BackButton_Click(object sender, RoutedEventArgs e)
        {

            // create json
            Dictionary<string, int> json = new Dictionary<string, int>();
            json.Add("roomId", (int)User.UserRoom.Id);
            string jsonString = JsonConvert.SerializeObject(json);
            byte[] arr;
            if (User.Is_admin)
            {
                arr = Helper.SerializeMsg(jsonString, 111); // close room code
            }
            else
            {
                arr = Helper.SerializeMsg(jsonString, 114); // leave room code
            }
            // send and get
            Communicator.SendMsg(arr, arr.Length);
            KeyValuePair<int, string> msg = Communicator.GetMsg();

            User.Is_admin = false;

            // return to main
            MainWindow main = new MainWindow();
            Communicator.EndCommunicate = false;
            Close();
            main.Show();
        }

        private void Tick()
        {
            bool isAdmin = true;

            // while the window is open
            while (true)
            {
                // wait 3 sec
                Thread.Sleep(1000);

                // create json of get state of room
                Dictionary<string, int> json = new Dictionary<string, int>();
                json.Add("roomId", (int)User.UserRoom.Id);
                string jsonString = JsonConvert.SerializeObject(json);
                byte[] arr = Helper.SerializeMsg(jsonString, 113); // get room state code

                // send and get
                Communicator.SendMsg(arr, arr.Length);
                KeyValuePair<int, string> msg = Communicator.GetMsg();

                // get players list
                var v = JsonConvert.DeserializeObject<Dictionary<string, string>>(msg.Value);

                // for each player
                Application.Current.Dispatcher.Invoke(delegate () { UsersList.Items.Clear(); });
                User.UserRoom.Players.Clear();
                if (v["players"] == "")
                {
                    Application.Current.Dispatcher.Invoke(delegate () { UsersList.Items.Add("the room was closed"); });
                    Thread.Sleep(3000);
                    Application.Current.Dispatcher.Invoke(delegate () {
                        MainWindow main = new MainWindow();
                        Communicator.EndCommunicate = false;
                        Close();
                        main.Show();
                    });
                }
                else
                {
                    foreach (var i in v["players"].Split(' '))
                    {
                        // add to list in room class and to list in UI
                        User.UserRoom.Players.Add(i);
                        // all this stuff is because we in a thread
                        Application.Current.Dispatcher.Invoke(delegate () { UsersList.Items.Add(i); });
                    }
                }     
            }
        }

        private void StartButton_Click(object sender, RoutedEventArgs e)
        {
            // if the thread is alive, kill him
            if (timer.IsAlive)
            {
                timer.Abort();
            }
            Dictionary<string, int> json = new Dictionary<string, int>();
            json.Add("roomId", (int)User.UserRoom.Id);
            string jsonString = JsonConvert.SerializeObject(json);
            byte[] arr = Helper.SerializeMsg(jsonString, 14); //Start game code

            Communicator.SendMsg(arr, arr.Length);
            //KeyValuePair<int, string> msg = Communicator.GetMsg();

            // close this window and open game window
            GameWindow game = new GameWindow();
            Communicator.EndCommunicate = false;
            Close();
            game.Show();
        }

        //the user click 'close'
        private void Window_Closing(object sender, CancelEventArgs e)
        {

            // create json
            Dictionary<string, int> json = new Dictionary<string, int>();
            json.Add("roomId", (int)User.UserRoom.Id);
            string jsonString = JsonConvert.SerializeObject(json);

            //stop the default closing
            e.Cancel = true;

            // if the thread is alive, kill him
            if (timer.IsAlive)
            {
                timer.Abort();
            }
            // end communicate
            Communicator.Finish();

            //close curr window
            e.Cancel = false;
        }
    }
}
