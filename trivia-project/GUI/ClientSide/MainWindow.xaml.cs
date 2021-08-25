using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Windows;
using Newtonsoft.Json;

namespace ClientSide
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        // C'tor
        public MainWindow()
        {
            InitializeComponent();

            Communicator.Init(@"../../../config.txt");

            // try to connect
            try
            {
                Communicator.Connect();
            }
            // open the error connection window
            catch (Exception)
            {
                // open error window and close this
                ConnectionErrorWindow errorWindow = new ConnectionErrorWindow();
                Communicator.EndCommunicate = false;
                Close();
                errorWindow.Show();
            }

            // there is logged user?
            if (User.Username != "")
            {
                LoggedUser();
            }
        }

        /// <summary>
        /// the func log a user into sys
        /// </summary>
        private void LoggedUser()
        {
            // change all the UI
            LoginGrid.Visibility = Visibility.Hidden;
            Logout_Button.Visibility = Visibility.Visible;
            User_Label.Content = "Welcome " + User.Username + "!";
            User_Label.Visibility = Visibility.Visible;
            Join_Button.IsEnabled = true;
            Create_Button.IsEnabled = true;
            Status_Button.IsEnabled = true;
            Best_Button.IsEnabled = true;
        }

        /// <summary>
        /// the user click on the signup button
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Signup_Button_Click(object sender, RoutedEventArgs e)
        {
            // open signup window and close this
            try
            {
                SignupWindow signupWindow = new SignupWindow();
                Communicator.EndCommunicate = false;
                Close();
                signupWindow.Show();
            }
            catch (Exception)
            {
                ErrorLabel.Content = "some error in signup";
                ErrorLabel.Visibility = Visibility.Visible;
            }
        }

        /// <summary>
        /// the user click on the login button
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Ok_Button_Click(object sender, RoutedEventArgs e)
        {
            // define vars
            Dictionary<string, string> json = new Dictionary<string, string>(2);
            bool valid = true;

            // create msg dict
            valid &= Helper.AddToJson(json, "username", this.UsernameText.GetLineText(0));
            valid &= Helper.AddToJson(json, "password", this.PasswordText.Password);

            if (valid)
            {
                if (json["password"].IndexOf('\'') != -1 || json["password"].IndexOf('\"') != -1)
                {
                    ErrorLabel.Content = "can't use ' or \", U try sqli (;...";
                    valid = false;
                }
            }

            // valid msg?
            if (valid)
            {
                // encode msg
                this.ErrorLabel.Visibility = Visibility.Hidden;
                string jsonString = JsonConvert.SerializeObject(json);
                byte[] arr = Helper.SerializeMsg(jsonString, 101); //login code

                // send msg and get res
                Communicator.SendMsg(arr, arr.Length);
                KeyValuePair<int, string> msg = Communicator.GetMsg();

                // the user is valid
                if (msg.Key == 1)
                {
                    // log user
                    User.Username = json["username"];
                    LoggedUser();
                }
                else
                {
                    ErrorLabel.Content = "username or password incorrect, or user connected";
                    ErrorLabel.Visibility = Visibility.Visible;
                }
            }
            else
            {
                ErrorLabel.Visibility = Visibility.Visible;
            }

        }

        /// <summary>
        /// the user exit the app
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Quit_Button_Click(object sender, RoutedEventArgs e)
        {
            Close();
        }

        /// <summary>
        /// the user click on the join button
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Join_Button_Click(object sender, RoutedEventArgs e)
        {
            // open join room window and close this
            try
            {
                JoinRoomsWindow joinRoomsWindow = new JoinRoomsWindow();
                Communicator.EndCommunicate = false;
                Close();
                joinRoomsWindow.Show();
            }
            catch (Exception)
            {
                ErrorLabel.Content = "some error in join";
                ErrorLabel.Visibility = Visibility.Visible;
            }
        }

        /// <summary>
        /// the user click on the logout button
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Logout_Button_Click(object sender, RoutedEventArgs e)
        {
            // close communication
            Communicator.Finish();

            // change th UI
            LoginGrid.Visibility = Visibility.Visible;
            Logout_Button.Visibility = Visibility.Hidden;
            User_Label.Visibility = Visibility.Hidden;
            PasswordText.Clear();
            Join_Button.IsEnabled = false;
            Create_Button.IsEnabled = false;
            Status_Button.IsEnabled = false;
            Best_Button.IsEnabled = false;
            User.Username = "";

            // reconnect server
            Communicator.Connect();
        }

        /// <summary>
        /// the user click on the create button
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Create_Button_Click(object sender, RoutedEventArgs e)
        {
            // open create room window and close this
            try
            {
                CreateRoomWindow createRoomWindow = new CreateRoomWindow();
                Communicator.EndCommunicate = false;
                Close();
                createRoomWindow.Show();
            }
            catch (Exception)
            {
                ErrorLabel.Content = "some error in create";
                ErrorLabel.Visibility = Visibility.Visible;
            }
        }

        /// <summary>
        /// the user click on the status button
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Status_Button_Click(object sender, RoutedEventArgs e)
        {
            // open status window and close this
            try
            {
                MyStatusWindow myStatusWindow = new MyStatusWindow(User.Username);
                Communicator.EndCommunicate = false;
                Close();
                myStatusWindow.Show();
            }
            catch (Exception)
            {
                ErrorLabel.Content = "some error in status";
                ErrorLabel.Visibility = Visibility.Visible;
            }
        }

        /// <summary>
        /// the user click on the highscore button
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Best_Button_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                // open highscores window and close this
                HighscoresWindow highscores = new HighscoresWindow();
                Communicator.EndCommunicate = false;
                Close();
                highscores.Show();
            }
            catch (Exception)
            {
                ErrorLabel.Content = "some error in highscores";
                ErrorLabel.Visibility = Visibility.Visible;
            }
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
