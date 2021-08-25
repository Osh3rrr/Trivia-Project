using System.Collections.Generic;
using System.ComponentModel;
using System.Windows;
using Newtonsoft.Json;

namespace ClientSide
{
    /// <summary>
    /// the class is a window that registe user
    /// it get username, password, and email
    /// and send them to server
    /// </summary>
    public partial class SignupWindow : Window
    {
        // C'tor
        public SignupWindow()
        {
            InitializeComponent();
        }

        //the func close the curr window and open the main window
        private void ReturnFunc()
        {
            //return to main window
            MainWindow mainWindow = new MainWindow();
            Communicator.EndCommunicate = false;
            this.Close();
            mainWindow.Show();
        }

        //if user click the 'ok' button
        private void Ok_Button_Click(object sender, RoutedEventArgs e)
        {
            //define vars
            Dictionary<string, string> json = new Dictionary<string, string>(2);
            bool valid = true;

            //there is username?
            valid &= Helper.AddToJson(json, "username", this.UsernameText.GetLineText(0));
            valid &= Helper.AddToJson(json, "email", this.EmailText.GetLineText(0));
            valid &= Helper.AddToJson(json, "password", this.PasswordText.Password);

            //there is all three args?
            if (valid)
            {
                //hide the error label
                this.ErrorLabel.Visibility = Visibility.Hidden;

                //make a json string 
                string jsonString = JsonConvert.SerializeObject(json);
                byte[] arr = Helper.SerializeMsg(jsonString, 102); // signup code
               
                // send and get
                Communicator.SendMsg(arr, arr.Length);
                KeyValuePair<int, string> pair = Communicator.GetMsg();

                //valid request
                if (pair.Key == 0)
                {
                    User.Username = json["username"];
                    ReturnFunc();
                }
            }
            //something invalid
            else
            {
                this.ErrorLabel.Visibility = Visibility.Visible;
            }

        }

        //the user click 'back' button
        private void BackButton_Click(object sender, RoutedEventArgs e)
        {
            //return to main window
            ReturnFunc();
        }

        //the user click 'close'
        private void Window_Closing(object sender, CancelEventArgs e)
        {
            //stop the default closing
            e.Cancel = true;

            //end communicate
            Communicator.Finish();

            //close curr window
            e.Cancel = false;
        }
    }
}
