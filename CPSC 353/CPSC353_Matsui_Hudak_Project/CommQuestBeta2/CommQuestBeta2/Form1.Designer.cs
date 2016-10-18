namespace CommQuestBeta2
{
    partial class form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(form1));
            this.startBtn = new System.Windows.Forms.Button();
            this.player1 = new System.Windows.Forms.PictureBox();
            this.leftBtn = new System.Windows.Forms.Button();
            this.rightBtn = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.player2 = new System.Windows.Forms.PictureBox();
            this.debugTB = new System.Windows.Forms.TextBox();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.timePB = new System.Windows.Forms.ProgressBar();
            this.gameStartTB = new System.Windows.Forms.TextBox();
            this.winLoseTB = new System.Windows.Forms.TextBox();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            ((System.ComponentModel.ISupportInitialize)(this.player1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.player2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // startBtn
            // 
            this.startBtn.BackColor = System.Drawing.Color.Blue;
            this.startBtn.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.startBtn.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.startBtn.Location = new System.Drawing.Point(320, 456);
            this.startBtn.Name = "startBtn";
            this.startBtn.Size = new System.Drawing.Size(100, 50);
            this.startBtn.TabIndex = 0;
            this.startBtn.Text = "START";
            this.startBtn.UseVisualStyleBackColor = false;
            this.startBtn.Click += new System.EventHandler(this.startBtn_Click);
            // 
            // player1
            // 
            this.player1.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.player1.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("player1.BackgroundImage")));
            this.player1.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.player1.Location = new System.Drawing.Point(12, 302);
            this.player1.Name = "player1";
            this.player1.Size = new System.Drawing.Size(50, 50);
            this.player1.TabIndex = 1;
            this.player1.TabStop = false;
            // 
            // leftBtn
            // 
            this.leftBtn.Location = new System.Drawing.Point(116, 399);
            this.leftBtn.Name = "leftBtn";
            this.leftBtn.Size = new System.Drawing.Size(50, 50);
            this.leftBtn.TabIndex = 3;
            this.leftBtn.Text = "Left";
            this.leftBtn.UseVisualStyleBackColor = true;
            this.leftBtn.Click += new System.EventHandler(this.leftBtn_Click);
            // 
            // rightBtn
            // 
            this.rightBtn.Location = new System.Drawing.Point(284, 399);
            this.rightBtn.Name = "rightBtn";
            this.rightBtn.Size = new System.Drawing.Size(50, 50);
            this.rightBtn.TabIndex = 4;
            this.rightBtn.Text = "Right";
            this.rightBtn.UseVisualStyleBackColor = true;
            this.rightBtn.Click += new System.EventHandler(this.rightBtn_Click);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(172, 399);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(106, 50);
            this.button1.TabIndex = 5;
            this.button1.Text = "Move Forward";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(340, 399);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(50, 50);
            this.button2.TabIndex = 6;
            this.button2.Text = "Fire!";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // player2
            // 
            this.player2.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.player2.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("player2.BackgroundImage")));
            this.player2.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.player2.Location = new System.Drawing.Point(672, 302);
            this.player2.Name = "player2";
            this.player2.Size = new System.Drawing.Size(50, 50);
            this.player2.TabIndex = 7;
            this.player2.TabStop = false;
            // 
            // debugTB
            // 
            this.debugTB.Location = new System.Drawing.Point(418, 38);
            this.debugTB.Multiline = true;
            this.debugTB.Name = "debugTB";
            this.debugTB.Size = new System.Drawing.Size(201, 288);
            this.debugTB.TabIndex = 9;
            // 
            // timer1
            // 
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // timePB
            // 
            this.timePB.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(64)))), ((int)(((byte)(0)))));
            this.timePB.Location = new System.Drawing.Point(12, 9);
            this.timePB.Maximum = 60;
            this.timePB.Name = "timePB";
            this.timePB.Size = new System.Drawing.Size(710, 23);
            this.timePB.TabIndex = 10;
            // 
            // gameStartTB
            // 
            this.gameStartTB.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.gameStartTB.Font = new System.Drawing.Font("Microsoft Sans Serif", 26.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.gameStartTB.Location = new System.Drawing.Point(172, 198);
            this.gameStartTB.Name = "gameStartTB";
            this.gameStartTB.Size = new System.Drawing.Size(382, 40);
            this.gameStartTB.TabIndex = 11;
            this.gameStartTB.Text = "Enter Server IP";
            this.gameStartTB.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.gameStartTB.TextChanged += new System.EventHandler(this.gameStartTB_TextChanged);
            this.gameStartTB.Enter += new System.EventHandler(this.gameStartTB_Enter);
            // 
            // winLoseTB
            // 
            this.winLoseTB.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.winLoseTB.Font = new System.Drawing.Font("Microsoft Sans Serif", 26.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.winLoseTB.Location = new System.Drawing.Point(418, 399);
            this.winLoseTB.Name = "winLoseTB";
            this.winLoseTB.Size = new System.Drawing.Size(188, 40);
            this.winLoseTB.TabIndex = 12;
            this.winLoseTB.Text = "You Lose!";
            this.winLoseTB.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // pictureBox1
            // 
            this.pictureBox1.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("pictureBox1.BackgroundImage")));
            this.pictureBox1.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.pictureBox1.Location = new System.Drawing.Point(-1, 0);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(741, 464);
            this.pictureBox1.TabIndex = 13;
            this.pictureBox1.TabStop = false;
            // 
            // form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.ClientSize = new System.Drawing.Size(734, 461);
            this.Controls.Add(this.debugTB);
            this.Controls.Add(this.winLoseTB);
            this.Controls.Add(this.gameStartTB);
            this.Controls.Add(this.timePB);
            this.Controls.Add(this.player2);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.rightBtn);
            this.Controls.Add(this.leftBtn);
            this.Controls.Add(this.player1);
            this.Controls.Add(this.startBtn);
            this.Controls.Add(this.pictureBox1);
            this.MaximizeBox = false;
            this.MaximumSize = new System.Drawing.Size(750, 500);
            this.MinimizeBox = false;
            this.MinimumSize = new System.Drawing.Size(750, 500);
            this.Name = "form1";
            this.Text = "Pirate Showdown Time";
            ((System.ComponentModel.ISupportInitialize)(this.player1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.player2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button startBtn;
        private System.Windows.Forms.PictureBox player1;
        private System.Windows.Forms.Button leftBtn;
        private System.Windows.Forms.Button rightBtn;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.PictureBox player2;
        private System.Windows.Forms.TextBox debugTB;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.ProgressBar timePB;
        private System.Windows.Forms.TextBox gameStartTB;
        private System.Windows.Forms.TextBox winLoseTB;
        private System.Windows.Forms.PictureBox pictureBox1;
    }
}

