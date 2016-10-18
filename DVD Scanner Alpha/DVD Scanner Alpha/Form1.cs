using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using HtmlAgilityPack;
using System.Collections;
using System.Xml.Serialization;
using System.IO;

//API key: AIzaSyC9GuuTSwrqI3XO40-hOCJbRGgfHHL_j6Q
//query url: https://www.googleapis.com/customsearch/v1?key=AIzaSyC9GuuTSwrqI3XO40-hOCJbRGgfHHL_j6Q&cx=017576662512468239146:omuauf_lfve&q=blood

namespace DVD_Scanner_Alpha
{
    public partial class Form1 : Form
    {
        HtmlWeb web;
        HtmlAgilityPack.HtmlDocument document;

        bool normalQuery = true;

        List<string[]> list = new List<string[]>();
        public Form1()
        {
            InitializeComponent();
            normalQuery = true;
            textBox2.Enabled = false;
            webBrowser1.ScriptErrorsSuppressed = true;

            try {
                var serializer = new XmlSerializer(typeof(List<string[]>));
                using (FileStream stream = File.OpenRead("DVD_database.xml"))
                {
                    list = (List<string[]>)serializer.Deserialize(stream);
                }
            }
            catch(Exception e)
            {

            }

            foreach (String[] i in list)
            {
                listView1.Items.Add(i[0]);
                listBox2.Items.Add(i[1]);
            }
        }

        private void textBox1_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                String serial = "INVALID_SERIAL";
                if(textBox1.Text.Length > 0)
                {
                    serial = textBox1.Text;
                }
                try
                {
                    webBrowser1.AllowNavigation = true;
                    string parsedHTML = "";
                    string movieTitle = "UNKNOWN";
                    string imgSrc = "UNKNOWN";
                    //string html = new WebClient().DownloadString("https://www.google.com/search?q=" + serial);

                    //parsedHTML = parseHTML(html);

                    //richTextBox1.Text = html;
                    //webBrowser1.DocumentText = html;

                    HtmlWeb web = new HtmlWeb();
                    document = web.Load("https://www.google.com/search?q=" + serial);

                    HtmlAgilityPack.HtmlNode bodyNode = document.DocumentNode.SelectSingleNode("//td[@id='rhs_block']");
                    richTextBox1.Text = document.DocumentNode.InnerHtml;

                    if (bodyNode.InnerText.Length > 1)
                    {
                        webBrowser1.DocumentText = bodyNode.InnerHtml;
                        foreach (var image in bodyNode.SelectNodes(".//img"))
                        {
                            var src = image.GetAttributeValue("src", null);

                            if (src != null)
                            {
                                imgSrc = src;
                                break;
                            }
                        }

                        textBox2.Enabled = false;
                        normalQuery = true;

                        try
                        {
                            movieTitle = bodyNode.SelectSingleNode("//div[@class='_B5d']").InnerText;
                        }
                        catch (Exception ex)
                        {
                            textBox2.Enabled = true;
                        }
                    }
                    else
                    {
                        normalQuery = false;
                        textBox2.Enabled = true;
                        webBrowser1.Navigate("https://www.google.com/search?q=" + serial);// = new WebClient().DownloadString("https://www.google.com/search?q=" + serial);                    }
                        if (list.Count == 0)
                        {
                            list.Add(new String[] { serial + " (1)", movieTitle, imgSrc });
                            listView1.Items.Add(serial + " (1)");
                            listBox2.Items.Add(movieTitle);
                        }
                        else
                        {
                            for (int i = 0; i < list.Count; ++i)
                            {
                                if (list[i][0].ToString().Contains(serial))
                                {
                                    int count = Int32.Parse(list[i][0].ToString().Substring(list[i][0].ToString().IndexOf('(')).Substring(1, list[i][0].ToString().Substring(list[i][0].ToString().IndexOf('(')).Length - 2));
                                    list[i][0] = list[i][0].ToString().Substring(0, list[i][0].ToString().IndexOf('(')) + "(" + ++count + ")";
                                    listView1.Items.Clear();
                                    listBox2.Items.Clear();
                                    foreach (String[] j in list)
                                    {
                                        listView1.Items.Add(j[0]);
                                        listBox2.Items.Add(j[1]);
                                    }
                                    i = list.Count;
                                    break;
                                }
                                else if (i == list.Count - 1)
                                {
                                    list.Add(new String[] { serial + " (1)", movieTitle, imgSrc });
                                    listView1.Items.Add(serial + " (1)");
                                    listBox2.Items.Add(movieTitle);
                                    i = list.Count;
                                    break;
                                }
                            }
                        }
                    }
                }
                catch(Exception ex)
                {
                    textBox1.Text = "INVALID SERIAL";
                }
                textBox1.Text = "";
                e.SuppressKeyPress = true;
            }
        }

        private String parseHTML(String passedHTML)
        {

            /*
            String returnHTML = "<html><head></head><body>INVALID SERIAL</body></html>";
            int divCount = 1;
            int startInd = passedHTML.IndexOf("<div id=\"rhs_block\"");
            int endInd = 0;
            if(startInd != -1)
            {
                richTextBox1.Text += " start I is: " + startInd;
                for (int i = startInd; i < passedHTML.Length - 5; i++)
                {
                    richTextBox1.Text += " substr is: " + passedHTML.Substring(i, 4);
                    if (passedHTML.Substring(i, 4).Equals("<div"))
                    {
                        divCount++;
                    }
                    if (passedHTML.Substring(i, 5).Equals("</div"))
                    {
                        divCount--;
                        richTextBox1.Text += " divs : " + divCount;
                    }
                    if (divCount == 0)
                    {
                        endInd = i + 4;
                        break;
                    }
                }
                if (startInd < endInd)
                {
                    returnHTML = "<html><head></head><body>" + passedHTML.Substring(startInd, endInd - (startInd-1)) + "</body></html>";
                }
            }
            else
            {
                richTextBox1.Text += "can't find ind";
            }
            return returnHTML; */
            return "oof";
        }

        private void webBrowser1_Navigated(object sender, WebBrowserNavigatedEventArgs e)
        {
            if(normalQuery)
                webBrowser1.AllowNavigation = false;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            var serializer = new XmlSerializer(typeof(List<string[]>));
            using (var writer = new StreamWriter("DVD_database.xml"))
                serializer.Serialize(writer, list);
            MessageBox.Show("Database Saved.");
            textBox1.Focus();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            DialogResult result1 = MessageBox.Show("Are you sure you would like to Permanently delete the database?",
            "Important Question",
            MessageBoxButtons.YesNo);
            if(result1 == DialogResult.Yes)
            {
                listView1.Items.Clear();
                listBox2.Items.Clear();
                list.Clear();
                var serializer = new XmlSerializer(typeof(List<string[]>));
                using (var writer = new StreamWriter("DVD_database.xml"))
                    serializer.Serialize(writer, list);
            }
            textBox1.Focus();
        }

        private void textBox2_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                list[list.Count - 1][1] = textBox2.Text;
                listBox2.Items.Clear();
                foreach (String[] j in list)
                {
                    listBox2.Items.Add(j[1]);
                }
                textBox2.Text = "";
                textBox2.Enabled = false;
                textBox1.Focus();
                e.SuppressKeyPress = true;
            }
        }

        private void listView1_DoubleClick(object sender, EventArgs e)
        {
            String item_to_delete = listView1.SelectedItem.ToString();

            for (int i = 0; i < list.Count; ++i)
            {
                if (list[i][0].ToString().Equals(item_to_delete))
                {
                    list.RemoveAt(i);
                    i = list.Count;
                }
            }
            listView1.Items.Clear();
            listBox2.Items.Clear();
            foreach (String[] j in list)
            {
                listView1.Items.Add(j[0]);
                listBox2.Items.Add(j[1]);

            }
            textBox1.Focus();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            MessageBox.Show("To begin, click the 'Serial Number' entry field, then scan an item.\n\nIf the item's information can be found, it will auto-populate.\nIf not, a google search for the serial will be made.You may then\ntype the correct movie title into the 'Movie Title' entry field\nand press enter.\nTo delete a recent query, double click it.\n\nIMPORTANT: Make sure to click save before exiting, or changes will be lost.");
        }
    }
}
