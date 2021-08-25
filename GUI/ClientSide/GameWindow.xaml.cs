using System;
using System.Windows;
using System.Threading;
using System.ComponentModel;

namespace ClientSide
{
    /// <summary>
    /// Interaction logic for GameWindow.xaml
    /// </summary>
    public partial class GameWindow : Window
    {
        private Thread timer;
        private int quesCounter = 0;
        private int scoreCounter = 0;

        public GameWindow()
        {
            InitializeComponent();
            RoomName.Content = User.UserRoom.Name;
            Username.Content = User.Username;
            SetQusetion();
            StartGame();
        }

        public void SetQusetion()
        {
            QuestNum.Content = "Question number: " + quesCounter + "/" + User.UserRoom.Num_of_question;
            Score.Content = "Score: " + scoreCounter + "/" + quesCounter;
            Counter.Content = "10";

            Question.Content = "question";
            Ans1.Content = "ans1";
            Ans2.Content = "ans2";
            Ans3.Content = "ans3";
            Ans4.Content = "ans4";
            timer = new Thread(new ThreadStart(Tick));
        }

        private void Exit_Click(object sender, RoutedEventArgs e)
        {
            MainWindow main = new MainWindow();
            Communicator.EndCommunicate = false;
            Close();
            main.Show();
        }

        private void Tick()
        {
            while (!Counter.Dispatcher.Invoke(delegate { return Convert.ToInt32(Counter.Content); }).Equals(0))
            {
                Thread.Sleep(1000);
                Counter.Dispatcher.Invoke(delegate { Counter.Content = (Convert.ToInt16(Counter.Content) - 1).ToString(); });
            }
            Counter.Dispatcher.Invoke(delegate { Answer_Clicked(); });
        }

        private void GetQuestion()
        {
        }

        private void StartGame()
        {
            timer.Start();
        }

        //the user click 'close'
        private void Window_Closing(object sender, CancelEventArgs e)
        {
            //stop the default closing
            e.Cancel = true;

            if (timer.IsAlive)
            {
                timer.Abort();
            }
            //return to main window
            Communicator.Finish();

            //close curr window
            e.Cancel = false;
        }

        private void Ans_Click(object sender, RoutedEventArgs e)
        {
            Answer_Clicked();
        }

        //private delegate void defaultAns();
        private void defaultAns()
        {
            timer.Abort();
            Question.Content = "asa";
            if (quesCounter < User.UserRoom.Num_of_question)
            {
                quesCounter++;
                SetQusetion();
                StartGame();
            }
        }

        private void Answer_Clicked()
        {
            timer.Abort();
            Question.Content = "asa";
            if (quesCounter < User.UserRoom.Num_of_question)
            {
                quesCounter++;
                SetQusetion();
                StartGame();
            }
        }
    }
}
