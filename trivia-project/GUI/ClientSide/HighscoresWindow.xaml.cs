using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Windows;
using Newtonsoft.Json;

namespace ClientSide
{
    /// <summary>
    /// Interaction logic for HighscoresWindow.xaml
    /// </summary>
    public partial class HighscoresWindow : Window
    {
        // C'tor
        public HighscoresWindow()
        {
            InitializeComponent();
            ThirdPlace.Content = "";
            SecondPlace.Content = "";
            FirstPlace.Content = "";
        }

        /// <summary>
        /// the user click on the back button
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
