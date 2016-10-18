using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net;
using System.Net.Sockets;
using System.Threading;

namespace CommQuestBeta2
{
    public partial class form1 : Form
    {
        int i;
        int turnPhase;
        int gameTime;
        TcpListener server;
        NetworkStream stream; //Creats a NetworkStream (used for sending and receiving data)
        TcpClient client; // Creates a TCP Client
        byte[] datalength = new byte[4]; // creates a new byte with length 4 ( used for receivng data's lenght)

        Point preTurn;
        char preTurnOrientation;
        char directionOpponent = 'l';
        string turnStr;
        string opponentTurnStr;
        Boolean running = false;
        Bitmap shipDown = Properties.Resources.shipDown;
        Bitmap shipDownExploded = Properties.Resources.shipDownEXPLODED;
        Bitmap shipLeft = Properties.Resources.shipLeft;
        Bitmap shipLeftExploded = Properties.Resources.shipLeftEXPLODED;
        Bitmap shipUp = Properties.Resources.shipUp;
        Bitmap shipUpExploded = Properties.Resources.shipUpEXPLODED;
        Bitmap shipRight = Properties.Resources.shipRight;
        Bitmap shipRightExploded = Properties.Resources.shipRightEXPLODED;
        char directionPlayer = 'r';
        Boolean isServer = false;
        Boolean showingTurn = false;
        Boolean sentTurnStr = false;
        Boolean playAgain = false;
        public form1()
        {

            InitializeComponent();
            startBtn.Location = new Point(325, 270);
            player1.Location = new Point(10, 150);
            player2.Location = new Point(660, 150);

            player1.Visible = false;
            player1.BackColor = Color.Blue;
            player2.BackColor = Color.Red;
            player2.Visible = false;
            leftBtn.Visible = false;
            rightBtn.Visible = false;
            button1.Visible = false;
            button2.Visible = false;
            preTurn = player1.Location;

            timer1.Interval = 500;
            timer1.Enabled = false;
            gameTime = 0;
            timePB.Value = 60;

            //gameStartTB.Enabled = false;
            //gameStartTB.Visible = false;
            turnStr = "0:0";
            opponentTurnStr = "0:0";
            preTurnOrientation = directionPlayer;
            debugTB.Visible = false;
            winLoseTB.Visible = false;

            turnPhase = 0;
        }

        public void ClientReceive()
        {

            stream = client.GetStream(); //Gets The Stream of The Connection
            new Thread(() => // Thread (like Timer)
            {
                while ((i = stream.Read(datalength, 0, 4)) != 0)//Keeps Trying to Receive the Size of the Message or Data
                {
                    // how to make a byte E.X byte[] examlpe = new byte[the size of the byte here] , i used BitConverter.ToInt32(datalength,0) cuz i received the length of the data in byte called datalength :D
                    byte[] data = new byte[BitConverter.ToInt32(datalength, 0)]; // Creates a Byte for the data to be Received On
                    stream.Read(data, 0, data.Length); //Receives The Real Data not the Size
                    this.Invoke((MethodInvoker)delegate // To Write the Received data
                    { 
                        gameStartTB.Text = Encoding.Default.GetString(data);
                        if(gameStartTB.Text[1] == ':')
                        {
                            opponentTurnStr = gameStartTB.Text;
                        }
                        //gameStartTB.Text = System.Environment.NewLine + "" + Encoding.Default.GetString(data); // Encoding.Default.GetString(data); Converts Bytes Received to String
                    });
                }
            }).Start(); // Start the Thread
        }
        public void ClientSend(string msg)
        {
            stream = client.GetStream(); //Gets The Stream of The Connection
            byte[] data; // creates a new byte without mentioning the size of it cuz its a byte used for sending
            data = Encoding.Default.GetBytes(msg); // put the msg in the byte ( it automaticly uses the size of the msg )
            int length = data.Length; // Gets the length of the byte data
            byte[] datalength = new byte[4]; // Creates a new byte with length of 4
            datalength = BitConverter.GetBytes(length); //put the length in a byte to send it
            stream.Write(datalength, 0, 4); // sends the data's length
            stream.Write(data, 0, data.Length); //Sends the real data
        }
        public void ServerReceive()
        {
            stream = client.GetStream(); //Gets The Stream of The Connection
            new Thread(() => // Thread (like Timer)
            {
                while ((i = stream.Read(datalength, 0, 4)) != 0)//Keeps Trying to Receive the Size of the Message or Data
                {
                    // how to make a byte E.X byte[] examlpe = new byte[the size of the byte here] , i used BitConverter.ToInt32(datalength,0) cuz i received the length of the data in byte called datalength :D
                    byte[] data = new byte[BitConverter.ToInt32(datalength, 0)]; // Creates a Byte for the data to be Received On
                    stream.Read(data, 0, data.Length); //Receives The Real Data not the Size
                    this.Invoke((MethodInvoker)delegate // To Write the Received data
                    {
                        gameStartTB.Text = Encoding.Default.GetString(data); // Encoding.Default.GetString(data); Converts Bytes Received to String
                                                if(gameStartTB.Text[1] == ':')
                        {
                            opponentTurnStr = gameStartTB.Text;
                        }
                        //gameStartTB.Text = System.Environment.NewLine + "" + Encoding.Default.GetString(data); // Encoding.Default.GetString(data); Converts Bytes Received to String
                    });
                }
            }).Start(); // Start the Thread

        }

        public void ServerSend(string msg)
        {
            stream = client.GetStream(); //Gets The Stream of The Connection
            byte[] data; // creates a new byte without mentioning the size of it cuz its a byte used for sending
            data = Encoding.Default.GetBytes(msg); // put the msg in the byte ( it automaticly uses the size of the msg )
            int length = data.Length; // Gets the length of the byte data
            byte[] datalength = new byte[4]; // Creates a new byte with length of 4
            datalength = BitConverter.GetBytes(length); //put the length in a byte to send it
            stream.Write(datalength, 0, 4); // sends the data's length
            stream.Write(data, 0, data.Length); //Sends the real data
        }

        private void startBtn_Click(object sender, EventArgs e)
        {
            if (playAgain)
            {
                winLoseTB.Text = "You Lose!";
                player1.Location = new Point(10, 150);
                player2.Location = new Point(660, 150);

                directionPlayer = 'r';
                directionOpponent = 'l';

                player1.BackgroundImage = shipRight;
                player2.BackgroundImage = shipLeft;

                showingTurn = false;
                sentTurnStr = false;

                turnStr = "0:0";
                opponentTurnStr = "0:0";
                preTurnOrientation = directionPlayer;
                debugTB.Visible = false;
                winLoseTB.Visible = false;

                gameTime = 0;
                turnPhase = 0;
                timePB.Value = 60;
                try
                {
                    if (isServer && client.Connected) // if the client is connected
                    {
                        ServerSend("RDY"); // uses the Function ClientSend and the msg as txtSend.Text
                    }
                    if (!isServer && client.Connected) // if the client is connected
                    {
                        ClientSend("RDY"); // uses the Function ClientSend and the msg as txtSend.Text
                    }
                }
                catch (Exception ex)
                {
                    gameStartTB.Text = "Waiting for Player 2..";
                }
                startBtn.Enabled = false;
                startBtn.Visible = false;
                running = true;

                timer1.Enabled = true;
            }
            else
            {
                if (!isServer)
                {
                    try
                    {
                        client = new TcpClient(gameStartTB.Text, 1980); //Trys to Connect
                        ClientReceive(); //Starts Receiving When Connected
                                         //timer1.Enabled = true;
                    }
                    catch (Exception ex)
                    {
                        isServer = true;
                        gameStartTB.Text = "";
                        //MessageBox.Show(ex.Message); // Error handler :D
                    }
                }
                if (isServer && gameStartTB.Text.Equals(""))
                {
                    try
                    {
                        //System.Net.IPAddress ipAddress = IPAddress.Parse("10.103.147.24");
                        server = new TcpListener(1980); // Creates a TCP Listener To Listen to Any IPAddress trying to connect to the program with port 1980
                        server.Start(); // Starts Listening to Any IPAddress trying to connect to the program with port 1980
                                        //MessageBox.Show("Waiting For Connection");
                        new Thread(() => // Creates a New Thread (like a timer)
                        {
                            client = server.AcceptTcpClient(); //Waits for the Client To Connect
                        if (client.Connected) // If you are connected
                        {
                                ServerReceive(); //Start Receiving
                        }
                        }).Start();

                        startBtn.Visible = false;
                        startBtn.Enabled = false;
                    }
                    catch (Exception ex)
                    {
                        isServer = false;
                        debugTB.Text = "Failed to make server";
                    }
                }

                try
                {
                    if (isServer && client.Connected) // if the client is connected
                    {
                        ServerSend("RDY"); // uses the Function ClientSend and the msg as txtSend.Text
                    }
                    if (!isServer && client.Connected) // if the client is connected
                    {
                        ClientSend("RDY"); // uses the Function ClientSend and the msg as txtSend.Text
                    }
                }
                catch (Exception ex)
                {
                    //gameStartTB.Text = "Waiting for Player 2..";
                }
            }
        }

        private void leftBtn_Click(object sender, EventArgs e)
        {
            Boolean canTurn = false;
            if (turnStr[0] == '0')
            {
                turnStr = "1" + turnStr.Substring(1);
                canTurn = true;
            }
            else if (turnStr[2] == '0')
            {
                turnStr = turnStr.Substring(0, 2) + "1";
                canTurn = true;
            }
            if (canTurn) {
                switch (directionPlayer)
                {
                    case 'r':
                        player1.BackgroundImage = shipUp;
                        directionPlayer = 'u';
                        break;
                    case 'u':
                        player1.BackgroundImage = shipLeft;
                        directionPlayer = 'l';
                        break;
                    case 'l':
                        player1.BackgroundImage = shipDown;
                        directionPlayer = 'd';
                        break;
                    case 'd':
                        player1.BackgroundImage = shipRight;
                        directionPlayer = 'r';
                        break;
                }
            }
        }

        private void rightBtn_Click(object sender, EventArgs e)
        {
            Boolean canTurn = false;
            if (turnStr[0] == '0')
            {
                turnStr = "3" + turnStr.Substring(1);
                canTurn = true;
            }
            else if (turnStr[2] == '0')
            {
                turnStr = turnStr.Substring(0, 2) + "3";
                canTurn = true;
            }
            if (canTurn)
            {
                switch (directionPlayer)
                {
                    case 'l':
                        player1.BackgroundImage = shipUp;
                        directionPlayer = 'u';
                        break;
                    case 'd':
                        player1.BackgroundImage = shipLeft;
                        directionPlayer = 'l';
                        break;
                    case 'r':
                        player1.BackgroundImage = shipDown;
                        directionPlayer = 'd';
                        break;
                    case 'u':
                        player1.BackgroundImage = shipRight;
                        directionPlayer = 'r';
                        break;
                }
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Boolean canTurn = false;
            if (turnStr[0] == '0')
            {
                turnStr = "2" + turnStr.Substring(1);
                canTurn = true;
            }
            else if (turnStr[2] == '0')
            {
                turnStr = turnStr.Substring(0, 2) + "2";
                canTurn = true;
            }
            if (canTurn)
            {
                switch (directionPlayer)
                {
                    case 'r':
                        if (player1.Location.X <= 610)
                        {
                            player1.Location = new Point(player1.Location.X + 50, player1.Location.Y);
                        }
                        break;
                    case 'l':
                        if (player1.Location.X >= 60)
                        {
                            player1.Location = new Point(player1.Location.X - 50, player1.Location.Y);
                        }
                        break;
                    case 'u':
                        if (player1.Location.Y >= 10)
                        {
                            player1.Location = new Point(player1.Location.X, player1.Location.Y - 50);
                        }
                        break;
                    case 'd':
                        if (player1.Location.Y <= 260)
                        {
                            player1.Location = new Point(player1.Location.X, player1.Location.Y + 50);
                        }
                        break;
                }
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            gameTime++;
            if (!showingTurn && gameTime > 4)
            {
                leftBtn.Enabled = true;
                rightBtn.Enabled = true;
                button1.Enabled = true;
                button2.Enabled = true;
                timePB.Value = timePB.Value - 10;
                if (timePB.Value == 0)
                {
                    leftBtn.Enabled = false;
                    rightBtn.Enabled = false;
                    button1.Enabled = false;
                    button2.Enabled = false;

                    turnPhase = 4;
                    player1.Location = preTurn;
                    switch (preTurnOrientation)
                    {
                        case 'u':
                            player1.BackgroundImage = shipUp;
                            break;
                        case 'l':
                            player1.BackgroundImage = shipLeft;
                            break;
                        case 'd':
                            player1.BackgroundImage = shipDown;
                            break;
                        case 'r':
                            player1.BackgroundImage = shipRight;
                            break;
                    }
                    sentTurnStr = false;
                    showingTurn = true;
                }
            }
            else if(showingTurn)
            {

                if (!sentTurnStr)
                {
                    if (isServer && client.Connected) // if the client is connected
                    {
                        ServerSend(turnStr); // uses the Function ClientSend and the msg as txtSend.Text
                    }
                    if (!isServer && client.Connected) // if the client is connected
                    {
                        ClientSend(turnStr); // uses the Function ClientSend and the msg as txtSend.Text
                    }
                    sentTurnStr = true;
                }
                playTurn();
            }
            if(gameTime < 5)
            {
                gameStartTB.Enabled = true;
                gameStartTB.Visible = true;

                gameStartTB.Text = (4 - gameTime).ToString();
            }
            else
            {
                gameStartTB.Enabled = false;
                gameStartTB.Visible = false;
            }
        }

        private void endGame()
        {
            debugTB.Text += "\r\nPlayer1 : " + turnStr + " player 2 : " + gameStartTB.Text;
            if (player1.Location.X == (player2.Location.X) && player1.Location.Y == (player2.Location.Y))
            { 
                timer1.Enabled = false;

                winLoseTB.Visible = true;

                switch (preTurnOrientation)
                {
                    case 'l':
                        player1.BackgroundImage = shipLeftExploded;
                        break;
                    case 'd':
                        player1.BackgroundImage = shipDownExploded;
                        break;
                    case 'r':
                        player1.BackgroundImage = shipRightExploded;
                        break;
                    case 'u':
                        player1.BackgroundImage = shipUpExploded;
                        break;
                }
                switch (directionOpponent)
                {
                    case 'l':
                        player2.BackgroundImage = shipLeftExploded;
                        break;
                    case 'd':
                        player2.BackgroundImage = shipDownExploded;
                        break;
                    case 'r':
                        player2.BackgroundImage = shipRightExploded;
                        break;
                    case 'u':
                        player2.BackgroundImage = shipUpExploded;
                        break;
                }
            }
            if (turnStr[0] == '4' && turnPhase == 2)
            {
                switch (preTurnOrientation)
                {
                    case 'r':
                        if (player1.Location.X == (player2.Location.X))
                        {
                            timer1.Enabled = false;
                            winLoseTB.Text = "You Win!";
                            winLoseTB.Visible = true;
                        }
                        break;
                    case 'u':
                        if (player1.Location.Y == (player2.Location.Y))
                        {
                            timer1.Enabled = false;
                            winLoseTB.Text = "You Win!";
                            winLoseTB.Visible = true;
                        }
                        break;
                    case 'l':
                        if (player1.Location.X == (player2.Location.X))
                        {
                            timer1.Enabled = false;
                            winLoseTB.Text = "You Win!";
                            winLoseTB.Visible = true;
                        }
                        break;
                    case 'd':
                        if (player1.Location.Y == (player2.Location.Y))
                        {
                            timer1.Enabled = false;
                            winLoseTB.Text = "You Win!";
                            winLoseTB.Visible = true;
                        }
                        break;
                }
                if(timer1.Enabled == false)
                {
                    switch (directionOpponent)
                    {
                        case 'l':
                            player2.BackgroundImage = shipLeftExploded;
                            break;
                        case 'd':
                            player2.BackgroundImage = shipDownExploded;
                            break;
                        case 'r':
                            player2.BackgroundImage = shipRightExploded;
                            break;
                        case 'u':
                            player2.BackgroundImage = shipUpExploded;
                            break;
                    }
                }
            }
            if (turnStr[2] == '4' && turnPhase == 0)
            {
                switch (preTurnOrientation)
                {
                    case 'r':
                        if (player1.Location.X == (player2.Location.X))
                        {
                            timer1.Enabled = false;
                            winLoseTB.Text = "You Win!";
                            winLoseTB.Visible = true;
                        }
                        break;
                    case 'u':
                        if (player1.Location.Y == (player2.Location.Y))
                        {
                            timer1.Enabled = false;
                            winLoseTB.Text = "You Win!";
                            winLoseTB.Visible = true;
                        }
                        break;
                    case 'l':
                        if (player1.Location.X == (player2.Location.X))
                        {
                            timer1.Enabled = false;
                            winLoseTB.Text = "You Win!";
                            winLoseTB.Visible = true;
                        }
                        break;
                    case 'd':
                        if (player1.Location.Y == (player2.Location.Y))
                        {
                            timer1.Enabled = false;
                            winLoseTB.Text = "You Win!";
                            winLoseTB.Visible = true;
                        }
                        break;
                }
                if (timer1.Enabled == false)
                {
                    switch (directionOpponent)
                    {
                        case 'l':
                            player2.BackgroundImage = shipLeftExploded;
                            break;
                        case 'd':
                            player2.BackgroundImage = shipDownExploded;
                            break;
                        case 'r':
                            player2.BackgroundImage = shipRightExploded;
                            break;
                        case 'u':
                            player2.BackgroundImage = shipUpExploded;
                            break;
                    }
                }
            }
            if (opponentTurnStr[0] == '4' && turnPhase == 2)
            {
                switch (directionOpponent)
                {
                    case 'r':
                        if (player1.Location.X == (player2.Location.X))
                        {
                            timer1.Enabled = false;
                            winLoseTB.Visible = true;
                        }
                        break;
                    case 'u':
                        if (player1.Location.Y == (player2.Location.Y))
                        {
                            timer1.Enabled = false;
                            winLoseTB.Visible = true;
                        }
                        break;
                    case 'l':
                        if (player1.Location.X == (player2.Location.X))
                        {
                            timer1.Enabled = false;
                            winLoseTB.Visible = true;
                        }
                        break;
                    case 'd':
                        if (player1.Location.Y == (player2.Location.Y))
                        {
                            timer1.Enabled = false;
                            winLoseTB.Visible = true;
                        }
                        break;
                }
                if (timer1.Enabled == false)
                {
                    switch (preTurnOrientation)
                    {
                        case 'l':
                            player1.BackgroundImage = shipLeftExploded;
                            break;
                        case 'd':
                            player1.BackgroundImage = shipDownExploded;
                            break;
                        case 'r':
                            player1.BackgroundImage = shipRightExploded;
                            break;
                        case 'u':
                            player1.BackgroundImage = shipUpExploded;
                            break;
                    }
                }
            }
            if (opponentTurnStr[2] == '4' && turnPhase == 0)
            {
                switch (directionOpponent)
                {
                    case 'r':
                        if (player1.Location.X == (player2.Location.X))
                        {
                            timer1.Enabled = false;
                            winLoseTB.Visible = true;
                        }
                        break;
                    case 'u':
                        if (player1.Location.Y == (player2.Location.Y))
                        {
                            timer1.Enabled = false;
                            winLoseTB.Visible = true;
                        }
                        break;
                    case 'l':
                        if (player1.Location.X == (player2.Location.X))
                        {
                            timer1.Enabled = false;
                            winLoseTB.Visible = true;
                        }
                        break;
                    case 'd':
                        if (player1.Location.Y == (player2.Location.Y))
                        {
                            timer1.Enabled = false;
                            winLoseTB.Visible = true;
                        }
                        break;
                }
                switch (preTurnOrientation)
                {
                    case 'l':
                        player1.BackgroundImage = shipLeftExploded;
                        break;
                    case 'd':
                        player1.BackgroundImage = shipDownExploded;
                        break;
                    case 'r':
                        player1.BackgroundImage = shipRightExploded;
                        break;
                    case 'u':
                        player1.BackgroundImage = shipUpExploded;
                        break;
                }
            }
            if (timer1.Enabled == false)
            {
                startBtn.Enabled = true;
                startBtn.Visible = true;
                startBtn.Text = "Again?";
                preTurnOrientation = directionPlayer = 'r';
                directionOpponent = 'l';
                playAgain = true;
            }
        }
        private void playTurn()
        {
            if(turnPhase == 3)
            {
                playTurnPhase(player1, turnStr, ref preTurnOrientation);
                playTurnPhase(player2, opponentTurnStr, ref directionOpponent);
            }
            if(turnPhase == 2)
            {
                endGame();
            }
            if (turnPhase == 1)
            {
                debugTB.Text += ("\r\n" + gameStartTB.Text.Length.ToString());
                playTurnPhase(player1, turnStr, ref preTurnOrientation);
                playTurnPhase(player2, opponentTurnStr, ref directionOpponent);
            }
            if(turnPhase == 0)
            {
                endGame();
                preTurn = player1.Location;
                preTurnOrientation = directionPlayer;
                showingTurn = false;
                turnStr = "0:0";
                opponentTurnStr = "0:0";
                timePB.Value = 60;
            }
            turnPhase--;
        }

        private void playTurnPhase(PictureBox passedPlayer, string passedTurnStr, ref char passedOrientation)
        {
            if (passedPlayer.Location.Equals(player1.Location))
            {
                if (turnPhase == 3)
                {
                    if (passedTurnStr[0] == '2')
                    {
                        switch (passedOrientation)
                        {
                            case 'r':
                                if (passedPlayer.Location.X <= 610)
                                {
                                    passedPlayer.Location = new Point(passedPlayer.Location.X + 50, passedPlayer.Location.Y);
                                }
                                break;
                            case 'l':
                                if (passedPlayer.Location.X >= 60)
                                {
                                    passedPlayer.Location = new Point(passedPlayer.Location.X - 50, passedPlayer.Location.Y);
                                }
                                break;
                            case 'u':
                                if (passedPlayer.Location.Y >= 10)
                                {
                                    passedPlayer.Location = new Point(passedPlayer.Location.X, passedPlayer.Location.Y - 50);
                                }
                                break;
                            case 'd':
                                if (passedPlayer.Location.Y <= 260)
                                {
                                    passedPlayer.Location = new Point(passedPlayer.Location.X, passedPlayer.Location.Y + 50);
                                }
                                break;
                        }
                    }
                    else if (passedTurnStr[0] == '3')
                    {
                        switch (passedOrientation)
                        {
                            case 'l':
                                passedPlayer.BackgroundImage = shipUp;
                                passedOrientation = 'u';
                                break;
                            case 'd':
                                passedPlayer.BackgroundImage = shipLeft;
                                passedOrientation = 'l';
                                break;
                            case 'r':
                                passedPlayer.BackgroundImage = shipDown;
                                passedOrientation = 'd';
                                break;
                            case 'u':
                                passedPlayer.BackgroundImage = shipRight;
                                passedOrientation = 'r';
                                break;
                        }
                    }
                    else if (passedTurnStr[0] == '1')
                    {
                        switch (passedOrientation)
                        {
                            case 'r':
                                passedPlayer.BackgroundImage = shipUp;
                                passedOrientation = 'u';
                                break;
                            case 'u':
                                passedPlayer.BackgroundImage = shipLeft;
                                passedOrientation = 'l';
                                break;
                            case 'l':
                                passedPlayer.BackgroundImage = shipDown;
                                passedOrientation = 'd';
                                break;
                            case 'd':
                                passedPlayer.BackgroundImage = shipRight;
                                passedOrientation = 'r';
                                break;
                        }
                    }
                }
                else if (turnPhase == 1)
                {
                    if (passedTurnStr[2] == '2')
                    {
                        switch (passedOrientation)
                        {
                            case 'r':
                                if (passedPlayer.Location.X <= 610)
                                {
                                    passedPlayer.Location = new Point(passedPlayer.Location.X + 50, passedPlayer.Location.Y);
                                }
                                break;
                            case 'l':
                                if (passedPlayer.Location.X >= 60)
                                {
                                    passedPlayer.Location = new Point(passedPlayer.Location.X - 50, passedPlayer.Location.Y);
                                }
                                break;
                            case 'u':
                                if (passedPlayer.Location.Y >= 10)
                                {
                                    passedPlayer.Location = new Point(passedPlayer.Location.X, passedPlayer.Location.Y - 50);
                                }
                                break;
                            case 'd':
                                if (passedPlayer.Location.Y <= 260)
                                {
                                    passedPlayer.Location = new Point(passedPlayer.Location.X, passedPlayer.Location.Y + 50);
                                }
                                break;
                        }
                    }
                    else if (passedTurnStr[2] == '3')
                    {
                        switch (passedOrientation)
                        {
                            case 'l':
                                passedPlayer.BackgroundImage = shipUp;
                                passedOrientation = 'u';
                                break;
                            case 'd':
                                passedPlayer.BackgroundImage = shipLeft;
                                passedOrientation = 'l';
                                break;
                            case 'r':
                                passedPlayer.BackgroundImage = shipDown;
                                passedOrientation = 'd';
                                break;
                            case 'u':
                                passedPlayer.BackgroundImage = shipRight;
                                passedOrientation = 'r';
                                break;
                        }
                    }
                    else if (passedTurnStr[2] == '1')
                    {
                        switch (passedOrientation)
                        {
                            case 'r':
                                passedPlayer.BackgroundImage = shipUp;
                                passedOrientation = 'u';
                                break;
                            case 'u':
                                passedPlayer.BackgroundImage = shipLeft;
                                passedOrientation = 'l';
                                break;
                            case 'l':
                                passedPlayer.BackgroundImage = shipDown;
                                passedOrientation = 'd';
                                break;
                            case 'd':
                                passedPlayer.BackgroundImage = shipRight;
                                passedOrientation = 'r';
                                break;
                        }
                    }
                }
            }
            else
            {
                if (turnPhase == 3)
                {
                    if (passedTurnStr[0] == '2')
                    {
                        switch (passedOrientation)
                        {
                            case 'r':
                                if (passedPlayer.Location.X <= 610)
                                {
                                    passedPlayer.Location = new Point(passedPlayer.Location.X + 50, passedPlayer.Location.Y);
                                }
                                break;
                            case 'l':
                                if (passedPlayer.Location.X >= 60)
                                {
                                    passedPlayer.Location = new Point(passedPlayer.Location.X - 50, passedPlayer.Location.Y);
                                }
                                break;
                            case 'u':
                                if (passedPlayer.Location.Y >= 10)
                                {
                                    passedPlayer.Location = new Point(passedPlayer.Location.X, passedPlayer.Location.Y - 50);
                                }
                                break;
                            case 'd':
                                if (passedPlayer.Location.Y <= 260)
                                {
                                    passedPlayer.Location = new Point(passedPlayer.Location.X, passedPlayer.Location.Y + 50);
                                }
                                break;
                        }
                    }
                    else if (passedTurnStr[0] == '1')
                    {
                        switch (passedOrientation)
                        {
                            case 'l':
                                passedPlayer.BackgroundImage = shipUp;
                                passedOrientation = 'u';
                                break;
                            case 'd':
                                passedPlayer.BackgroundImage = shipLeft;
                                passedOrientation = 'l';
                                break;
                            case 'r':
                                passedPlayer.BackgroundImage = shipDown;
                                passedOrientation = 'd';
                                break;
                            case 'u':
                                passedPlayer.BackgroundImage = shipRight;
                                passedOrientation = 'r';
                                break;
                        }
                    }
                    else if (passedTurnStr[0] == '3')
                    {
                        switch (passedOrientation)
                        {
                            case 'r':
                                passedPlayer.BackgroundImage = shipUp;
                                passedOrientation = 'u';
                                break;
                            case 'u':
                                passedPlayer.BackgroundImage = shipLeft;
                                passedOrientation = 'l';
                                break;
                            case 'l':
                                passedPlayer.BackgroundImage = shipDown;
                                passedOrientation = 'd';
                                break;
                            case 'd':
                                passedPlayer.BackgroundImage = shipRight;
                                passedOrientation = 'r';
                                break;
                        }
                    }
                }
                else if (turnPhase == 1)
                {
                    if (passedTurnStr[2] == '2')
                    {
                        switch (passedOrientation)
                        {
                            case 'r':
                                if (passedPlayer.Location.X <= 610)
                                {
                                    passedPlayer.Location = new Point(passedPlayer.Location.X + 50, passedPlayer.Location.Y);
                                }
                                break;
                            case 'l':
                                if (passedPlayer.Location.X >= 60)
                                {
                                    passedPlayer.Location = new Point(passedPlayer.Location.X - 50, passedPlayer.Location.Y);
                                }
                                break;
                            case 'u':
                                if (passedPlayer.Location.Y >= 10)
                                {
                                    passedPlayer.Location = new Point(passedPlayer.Location.X, passedPlayer.Location.Y - 50);
                                }
                                break;
                            case 'd':
                                if (passedPlayer.Location.Y <= 260)
                                {
                                    passedPlayer.Location = new Point(passedPlayer.Location.X, passedPlayer.Location.Y + 50);
                                }
                                break;
                        }
                    }
                    else if (passedTurnStr[2] == '1')
                    {
                        switch (passedOrientation)
                        {
                            case 'l':
                                passedPlayer.BackgroundImage = shipUp;
                                passedOrientation = 'u';
                                break;
                            case 'd':
                                passedPlayer.BackgroundImage = shipLeft;
                                passedOrientation = 'l';
                                break;
                            case 'r':
                                passedPlayer.BackgroundImage = shipDown;
                                passedOrientation = 'd';
                                break;
                            case 'u':
                                passedPlayer.BackgroundImage = shipRight;
                                passedOrientation = 'r';
                                break;
                        }
                    }
                    else if (passedTurnStr[2] == '3')
                    {
                        switch (passedOrientation)
                        {
                            case 'r':
                                passedPlayer.BackgroundImage = shipUp;
                                passedOrientation = 'u';
                                break;
                            case 'u':
                                passedPlayer.BackgroundImage = shipLeft;
                                passedOrientation = 'l';
                                break;
                            case 'l':
                                passedPlayer.BackgroundImage = shipDown;
                                passedOrientation = 'd';
                                break;
                            case 'd':
                                passedPlayer.BackgroundImage = shipRight;
                                passedOrientation = 'r';
                                break;
                        }
                    }
                }
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Boolean canTurn = false;
            if (turnStr[0] == '0')
            {
                turnStr = "4" + turnStr.Substring(1);
                canTurn = true;
            }
            else if (turnStr[2] == '0')
            {
                turnStr = turnStr.Substring(0, 2) + "4";
                canTurn = true;
            }
            if (canTurn)
            {
                //visual?
            }
        }

        private void gameStartTB_TextChanged(object sender, EventArgs e)
        {
            if (isServer && timer1.Enabled == false)
            {
                try
                {
                    if (isServer && client.Connected) // if the client is connected
                    {
                        ServerSend("RDY"); // uses the Function ClientSend and the msg as txtSend.Text
                        debugTB.Text = "this is bad";
                    }
                    if (!isServer && client.Connected) // if the client is connected
                    {
                        ClientSend("RDY"); // uses the Function ClientSend and the msg as txtSend.Text
                    }
                }
                catch (Exception ex)
                {
                    //gameStartTB.Text = "Waiting for Player 2..";
                }
            }
            if (gameStartTB.Text.Contains("RDY"))
            {
                if (playAgain)
                {
                    winLoseTB.Text = "You Lose!";
                    player1.Location = new Point(10, 150);
                    player2.Location = new Point(660, 150);

                    directionPlayer = 'r';
                    directionOpponent = 'l';

                    player1.BackgroundImage = shipRight;
                    player2.BackgroundImage = shipLeft;

                    showingTurn = false;
                    sentTurnStr = false;

                    turnStr = "0:0";
                    opponentTurnStr = "0:0";
                    preTurnOrientation = directionPlayer;
                    debugTB.Visible = false;
                    winLoseTB.Visible = false;

                    gameTime = 0;
                    turnPhase = 0;
                    timePB.Value = 60;
                }

                player1.Visible = true;
                player2.Visible = true;
                leftBtn.Visible = true;
                rightBtn.Visible = true;
                button1.Visible = true;
                button2.Visible = true;
                startBtn.Enabled = false;
                startBtn.Visible = false;
                running = true;

                timer1.Enabled= true;
            }
        }

        private void gameStartTB_Enter(object sender, EventArgs e)
        {
            gameStartTB.Text = "";
        }
    }
}


/*

    using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Net;
using System.Net.Sockets;
using System.Threading;

namespace CommQuestBeta
{
    public partial class Form1 : Form
    {
        int i;
        TcpListener server = new TcpListener(IPAddress.Any, 1980); // Creates a TCP Listener To Listen to Any IPAddress trying to connect to the program with port 1980
        NetworkStream stream; //Creats a NetworkStream (used for sending and receiving data)
        TcpClient client; // Creates a TCP Client
        byte[] datalength = new byte[4]; // creates a new byte with length 4 ( used for receivng data's lenght)

        public Form1()
        {
            InitializeComponent();
        }

        public void ServerReceive()
        {
            stream = client.GetStream(); //Gets The Stream of The Connection
            new Thread(() => // Thread (like Timer)
            {
                while ((i = stream.Read(datalength, 0, 4)) != 0)//Keeps Trying to Receive the Size of the Message or Data
                {
                    // how to make a byte E.X byte[] examlpe = new byte[the size of the byte here] , i used BitConverter.ToInt32(datalength,0) cuz i received the length of the data in byte called datalength :D
                    byte[] data = new byte[BitConverter.ToInt32(datalength, 0)]; // Creates a Byte for the data to be Received On
                    stream.Read(data, 0, data.Length); //Receives The Real Data not the Size
                    this.Invoke((MethodInvoker)delegate // To Write the Received data
                    {
                        txtLog.Text += System.Environment.NewLine + "Client : " + Encoding.Default.GetString(data); // Encoding.Default.GetString(data); Converts Bytes Received to String
                    });
                }
            }).Start(); // Start the Thread

        }

        public void ServerSend(string msg)
        {
            stream = client.GetStream(); //Gets The Stream of The Connection
            byte[] data; // creates a new byte without mentioning the size of it cuz its a byte used for sending
            data = Encoding.Default.GetBytes(msg); // put the msg in the byte ( it automaticly uses the size of the msg )
            int length = data.Length; // Gets the length of the byte data
            byte[] datalength = new byte[4]; // Creates a new byte with length of 4
            datalength = BitConverter.GetBytes(length); //put the length in a byte to send it
            stream.Write(datalength, 0, 4); // sends the data's length
            stream.Write(data, 0, data.Length); //Sends the real data
        }

        private void btnListen_Click(object sender, EventArgs e)
        {
            server.Start(); // Starts Listening to Any IPAddress trying to connect to the program with port 1980
            MessageBox.Show("Waiting For Connection");
            new Thread(() => // Creates a New Thread (like a timer)
            {
                client = server.AcceptTcpClient(); //Waits for the Client To Connect
                MessageBox.Show("Connected To Client");
                if (client.Connected) // If you are connected
                {
                    ServerReceive(); //Start Receiving
                }
            }).Start();
        }

        private void btnSend_Click(object sender, EventArgs e)
        {
            if (client.Connected) // if the client is connected
            {
                ServerSend(txtSend.Text); // uses the Function ClientSend and the msg as txtSend.Text
            }
        }
    }
}


    using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Net;
using System.Net.Sockets;
using System.Threading;

namespace commQuestTester
{
    public partial class Form1 : Form
    {
        int i;
        TcpClient client; // Creates a TCP Client
        NetworkStream stream; //Creats a NetworkStream (used for sending and receiving data)
        byte[] datalength = new byte[4]; // creates a new byte with length 4 ( used for receivng data's lenght)

        public Form1()
        {
            InitializeComponent();
        }
        private void btnConnect_Click(object sender, EventArgs e)
        {
            try
            {
                client = new TcpClient("127.0.0.1", 1980); //Trys to Connect
                ClientReceive(); //Starts Receiving When Connected
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message); // Error handler :D
            }
        }

        public void ClientReceive()
        {

            stream = client.GetStream(); //Gets The Stream of The Connection
            new Thread(() => // Thread (like Timer)
            {
                while ((i = stream.Read(datalength, 0, 4)) != 0)//Keeps Trying to Receive the Size of the Message or Data
                {
                    // how to make a byte E.X byte[] examlpe = new byte[the size of the byte here] , i used BitConverter.ToInt32(datalength,0) cuz i received the length of the data in byte called datalength :D
                    byte[] data = new byte[BitConverter.ToInt32(datalength, 0)]; // Creates a Byte for the data to be Received On
                    stream.Read(data, 0, data.Length); //Receives The Real Data not the Size
                    this.Invoke((MethodInvoker)delegate // To Write the Received data
                    {
                        txtLog.Text += System.Environment.NewLine + "Server : " + Encoding.Default.GetString(data); // Encoding.Default.GetString(data); Converts Bytes Received to String
                    });
                }
            }).Start(); // Start the Thread
        }

        public void ClientSend(string msg)
        {
            stream = client.GetStream(); //Gets The Stream of The Connection
            byte[] data; // creates a new byte without mentioning the size of it cuz its a byte used for sending
            data = Encoding.Default.GetBytes(msg); // put the msg in the byte ( it automaticly uses the size of the msg )
            int length = data.Length; // Gets the length of the byte data
            byte[] datalength = new byte[4]; // Creates a new byte with length of 4
            datalength = BitConverter.GetBytes(length); //put the length in a byte to send it
            stream.Write(datalength, 0, 4); // sends the data's length
            stream.Write(data, 0, data.Length); //Sends the real data
        }

        private void btnSend_Click(object sender, EventArgs e)
        {
            if (client.Connected) // if the client is connected
            {
                ClientSend(txtSend.Text); // uses the Function ClientSend and the msg as txtSend.Text
            }
        }
    }
}

    */
