using System.Collections.Generic;
using System.ComponentModel;
using System.Windows;
using Newtonsoft.Json;

namespace ClientSide
{
    /// <summary>
    /// Interaction logic for CreateRoomWindow.xaml
    /// </summary>
    public partial class CreateRoomWindow : Window
    {
        // C'tor
        public CreateRoomWindow()
        {
            InitializeComponent();

            // for now, default vals
            this.RoomsInput.Text = "room_name";
            this.TimeInput.Text = "5";
            this.NumPlayersInput.Text = "2";
            this.NumQuestionsInput.Text = "5";
        }

        /// <summary>
        /// the user click on the back button
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Button_Click(object sender, RoutedEventArgs e)
        {
            // the func close the curr window and open the main window
            MainWindow mainWindow = new MainWindow();
            Communicator.EndCommunicate = false;
            this.Close();
            mainWindow.Show();
        }

        // the user click 'close'
        private void Window_Closing(object sender, CancelEventArgs e)
        {
            // stop the default closing
            e.Cancel = true;

            // fin communicate
            Communicator.Finish();

            // close curr window
            e.Cancel = false;
        }

        /// <summary>
        /// the func add key and val to dict and check if the val is valid
        /// </summary>
        /// <param name="dict"> json dict </param>
        /// <param name="key"> key </param>
        /// <param name="val"> val </param>
        /// <param name="b"> will be false if the val is str that not a num </param>
        /// <returns> if the val is empty </returns>
        private bool AddToJson(Dictionary<string, int> dict, string key, string val, ref bool b)
        {
            // define var
            bool good = true;

            // val is empty? b is num?
            if (val == "" || !( b &= int.TryParse(val, out int n)))
            {
                good = false;
            }
            // val is ok
            else
            {
                dict.Add(key, int.Parse(val));
            }

            return good;
        }

        /// <summary>
        /// the user click on the create room button
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void CreateButton_Click(object sender, RoutedEventArgs e)
        {
            // define vars
            Dictionary<string, string> json1 = new Dictionary<string, string>();
            Dictionary<string, int> json2 = new Dictionary<string, int>();
            bool validInput = true;
            bool num = true;

            // make two dicts of msg, because we have strings and ints...
            // json1 is <string string>
            // json2 is <string int>

            //get inputs into json
            validInput &= Helper.AddToJson(json1, "roomName", this.RoomsInput.GetLineText(0));
            validInput &= AddToJson(json2, "questionCount", this.NumQuestionsInput.GetLineText(0), ref num);
            validInput &= AddToJson(json2, "maxUsers", this.NumPlayersInput.GetLineText(0), ref num);
            validInput &= AddToJson(json2, "answerTimeout", this.TimeInput.GetLineText(0), ref num);
            validInput &= Helper.AddToJson(json1, "username", User.Username);

            // all input is valid?
            if (validInput)
            {
                // hide error label
                this.ErrorLabel.Visibility = Visibility.Hidden;

                // create msg:
                // convert the dicts into json strings 
                string jsonString1 = JsonConvert.SerializeObject(json1);
                string jsonString2 = JsonConvert.SerializeObject(json2);
                // add the two json strings
                string jsonString = Helper.AddTwoJson(jsonString1, jsonString2);
                // get byte array of json msg
                byte[] arr = Helper.SerializeMsg(jsonString, 108); // create room code

                // send and get res
                Communicator.SendMsg(arr, arr.Length);
                KeyValuePair<int, string> msg = Communicator.GetMsg();

                // error?
                if (msg.Key != 1)
                {
                    // print error msg
                    ErrorLabel.Content = "There was an error with creating this room.";
                    ErrorLabel.Visibility = Visibility.Visible;
                }
                else
                {
                    // get the room data 
                    Dictionary<string, uint> resJson = JsonConvert.DeserializeObject<Dictionary<string, uint>>(msg.Value);

                    // make the user admin and init room
                    User.Is_admin = true;
                    User.initRoom(json1["roomName"], (uint)json2["maxUsers"], (uint)json2["questionCount"], (uint)json2["answerTimeout"]);

                    // open room data window and close this
                    RoomDataWinow roomDataWinow = new RoomDataWinow();
                    Communicator.EndCommunicate = false;
                    Close();
                    roomDataWinow.Show();
                }
            }
            // invalid input
            else
            {
                // input of string and not int?
                if (!num)
                {
                    // show error label with this msg
                    this.ErrorLabel.Content = "pls make sure all is in the good type";
                    this.ErrorLabel.Visibility = Visibility.Visible;
                }
                else
                {
                    // show error label with this msg
                    this.ErrorLabel.Content = "pls fill all the filds";
                    this.ErrorLabel.Visibility = Visibility.Visible;
                }
            }
        }
    }
}
