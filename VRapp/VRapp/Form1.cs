using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Speech.Recognition;
using System.Speech.Synthesis;
using System.Diagnostics;
using System.Runtime.InteropServices;

namespace VRapp
{
    public partial class Form1 : Form
    {
        private String name = "ydb";
        SpeechRecognitionEngine sre = new SpeechRecognitionEngine();
        SpeechSynthesizer sSynth = new SpeechSynthesizer();
        String[] command_list = new String[] { "say hello", "whose your daddy", "open google", "open facebook", 
                                "wake up sleepy head", "go to sleep" , "open hearthstone", "close hearthstone",
                                "see you later q", "kappa", "open reddit", "open g mail", "open eight tracks",
                                "turn on essay mode", "volume up", "volume down", "show yourself", "let me be",
                                "shutup and dance with me"};
        bool awake = true;
        bool close = false;

        private const int APPCOMMAND_VOLUME_MUTE = 0x80000;
        private const int APPCOMMAND_VOLUME_UP = 0xA0000;
        private const int APPCOMMAND_VOLUME_DOWN = 0x90000;
        private const int WM_APPCOMMAND = 0x319;

        [DllImport("user32.dll")]
        public static extern IntPtr SendMessageW(IntPtr hWnd, int Msg,
            IntPtr wParam, IntPtr lParam);
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            Choices commands = new Choices();
            commands.Add(command_list);
            GrammarBuilder gb = new GrammarBuilder();
            gb.Append(commands);
            Grammar grammar = new Grammar(gb);

            sSynth.SpeakCompleted += new EventHandler<SpeakCompletedEventArgs>(synth_SpeakCompleted);
            sSynth.SelectVoiceByHints(VoiceGender.Female, VoiceAge.Adult);
            sSynth.Rate = 2;

            sre.LoadGrammarAsync(grammar);
            sre.SetInputToDefaultAudioDevice();
            sre.SpeechRecognized += sre_SpeechRecognized;
            sre.RecognizeAsync(RecognizeMode.Multiple);
        }


        void sre_SpeechRecognized(object sender, SpeechRecognizedEventArgs e)
        {
            if (awake)
            {
                switch (e.Result.Text)
                {
                    case "turn on essay mode":
                        open_links("http://www.pandora.com/station/play/481015845961129437");
                        Process.Start("C:\\Users\\dontetz\\Desktop\\School\\essay.doc");
                        break;
                    case "open google":
                        open_links("http://www.google.com");
                        break;
                    case "open facebook":
                        open_links("http://www.facebook.com");
                        break;
                    case "open reddit":
                        open_links("http://www.reddit.com");
                        break;
                    case "open g mail":
                        open_links("http://www.gmail.com");
                        break;
                    case "open eight tracks":
                        open_links("http://www.8tracks.com");
                        break;
                    case "whose your daddy":

                        break;
                    case "go to sleep":
                        sre.RecognizeAsyncStop();
                        sSynth.SpeakAsync("Good night!");
                        awake = false;
                        break;
                    case "open hearthstone":
                        Process.Start("C:\\Program Files (x86)\\Hearthstone\\Hearthstone Beta Launcher.exe");
                        break;
                    case "close hearthstone":
                        close_app("Battle.net");
                        break;
                    case "see you later q":
                        sre.RecognizeAsyncStop();
                        sSynth.SpeakAsync("Good-bye " + name);
                        close = true;
                        break;
                    case "say hello":
                        sre.RecognizeAsyncStop();
                        sSynth.SpeakAsync("What's up " + name);
                        break;
                    case "shutup and dance with me":
                        System.Media.SoundPlayer sound = new System.Media.SoundPlayer(@"shutupanddance.wav");
                        sound.Play();
                        break;
                    case "show yourself":
                        this.TopMost = true;
                        this.FormBorderStyle = FormBorderStyle.None;
                        this.WindowState = FormWindowState.Maximized;
                        break;
                    case "let me be":
                        this.WindowState = FormWindowState.Minimized;
                        break;
                    case "volume down":
                        for (int i = 0; i < 10; i++ )
                            SendMessageW(this.Handle, WM_APPCOMMAND, this.Handle, (IntPtr)APPCOMMAND_VOLUME_DOWN);
                        break;
                    case "volume up":
                        for (int i = 0; i < 10; i++)
                            SendMessageW(this.Handle, WM_APPCOMMAND, this.Handle, (IntPtr)APPCOMMAND_VOLUME_UP);
                        break;
                    default:
                        sre.RecognizeAsyncStop();
                        sSynth.SpeakAsync("unknown command");
                        break;
                }
            }
            else if (e.Result.Text.Equals("wake up sleepy head"))
            {
                sre.RecognizeAsyncStop();
                sSynth.SpeakAsync("Good morning!");
                awake = true;
            }
        }

        private void btnDisable_Click(object sender, EventArgs e)
        {
            sre.RecognizeAsyncStop();
        }

        private void open_links(String link){
            sre.RecognizeAsyncStop();
            try
            {
                System.Diagnostics.Process.Start(link);
            }
            catch { }
            sSynth.SpeakAsync("opening");
        }

        private void close_app(String app)
        {
            Process[] processes;
            string procName = app;
            processes = Process.GetProcessesByName(procName);
            try
            {
                foreach (Process proc in processes)
                {
                    proc.CloseMainWindow();
                }
            }
            catch (System.NullReferenceException)
            {
                MessageBox.Show("No instances of application running.");
            }
        }
         void synth_SpeakCompleted(object sender, SpeakCompletedEventArgs e)
        {
            if (close)
                Environment.Exit(0);
            sre.RecognizeAsync(RecognizeMode.Multiple);
        }
    }
}
