using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using Newtonsoft.Json;

namespace ClientSide
{
    /// <summary>
    /// Interaction logic for MyStatusWindow.xaml
    /// </summary>
    public partial class MyStatusWindow : Window
    {
        // C'tor
        public MyStatusWindow(string name)
        {
            InitializeComponent();
            this.UsernameLabel.Content = name;
            GetStatus();
        }

        /// <summary>
        /// the user click in the back button
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void BackButton_Click(object sender, RoutedEventArgs e)
        {
            //the func close the curr window and open the main window
            MainWindow mainWindow = new MainWindow();
            Communicator.EndCommunicate = false;
            this.Close();
            mainWindow.Show();
        }

        private void GetStatus()
        {
            GamesLabel.Content = " ";
            RightLabel.Content = " ";
            WrongLabel.Content = " ";
            TimeLabel.Content = " ";
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
