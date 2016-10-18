using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using MySql.Data.MySqlClient;

namespace Assignment2
{
    public partial class Form1 : Form
    {
        MySqlTransaction tr = null;
        private DataGridView dg = null;
        private MySqlConnection conn = null;
        private MySqlDataAdapter da = null;
        private DataSet ds = null;
        private string cs;
        public Form1()
        {
            InitializeComponent();
            this.dg = dataGridView1;
            this.InitData();
            comboBox1.SelectedIndex = 0;
        }


        void InitData()
        {
            cs = @"Database=acsm_3674c400be7e911;Data Source=us-cdbr-azure-west-c.cloudapp.net;User Id=ba1517a46d7795;Password=bc2da882";

            string stm = "SELECT * FROM Student";

            try
            {
                conn = new MySqlConnection(cs);
                conn.Open();
                ds = new DataSet();
                da = new MySqlDataAdapter(stm, conn);
                da.Fill(ds, "Student");

                dg.DataSource = ds.Tables["Student"];
            }
            catch (MySqlException ex)
            {
                Console.WriteLine("Error: " + ex.ToString());

            }
            finally
            {
                if (conn != null)
                {
                    conn.Close();
                }
            }
        }

        private void trackBar1_ValueChanged(object sender, EventArgs e)
        {
            label5.Text = "GPA: " + ((double)trackBar1.Value)/10;
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            enableButtons();
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {
            enableButtons();
        }

        private void textBox3_TextChanged(object sender, EventArgs e)
        {
            enableButtons();
        }

        private void textBox4_TextChanged(object sender, EventArgs e)
        {
            enableButtons();
        }
        private void textBox6_TextChanged(object sender, EventArgs e)
        {
            enableButtons();
        }

        private void enableButtons()
        {
            if(textBox1.Text.Length > 0 && textBox2.Text.Length > 0 && textBox3.Text.Length > 0 && textBox4.Text.Length > 0)
            {
                button1.Enabled = true;
            }
            else
            {
                button1.Enabled = false;
            }
            if (textBox6.Text.Length > 0)
            {
                button2.Enabled = true;
                button4.Enabled = true;
            }
            else
            {
                button2.Enabled = false;
                button4.Enabled = false;
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                conn = new MySqlConnection(cs);
                conn.Open();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;
                cmd.CommandText = "INSERT INTO Student VALUES(NULL,'"+textBox1.Text+"','" + textBox2.Text + "','" + ((double)trackBar1.Value) / 10.0 + "','" + textBox4.Text + "','" + textBox3.Text +"')";

                cmd.ExecuteNonQuery();
                InitData();
            }
            catch (MySqlException ex)
            {
                Console.WriteLine("Error: {0}", ex.ToString());

            }
            finally
            {
                if (conn != null)
                {
                    conn.Close();
                }
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            try
            {
                conn = new MySqlConnection(cs);
                conn.Open();
                tr = conn.BeginTransaction();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;
                cmd.Transaction = tr;

                if(textBox3.Text.Length > 0)
                {
                    cmd.CommandText = "UPDATE Student SET FacultyAdvisor='"+textBox3.Text+"' WHERE StudentId="+textBox6.Text;
                    cmd.ExecuteNonQuery();
                }
                if (textBox4.Text.Length > 0)
                {
                    cmd.CommandText = "UPDATE Student SET Major='" + textBox4.Text + "' WHERE StudentId=" + textBox6.Text;
                    cmd.ExecuteNonQuery();
                }

                tr.Commit();
                InitData();
            }
            catch (MySqlException ex)
            {
                try
                {
                    tr.Rollback();

                }
                catch (MySqlException ex1)
                {
                    Console.WriteLine("Error: {0}", ex1.ToString());
                }
                Console.WriteLine("Error: {0}", ex.ToString());

            }
            finally
            {
                if (conn != null)
                {
                    conn.Close();
                }
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            try
            {
                conn = new MySqlConnection(cs);
                conn.Open();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;
                cmd.CommandText = "DELETE FROM Student WHERE StudentId=" +textBox6.Text;

                cmd.ExecuteNonQuery();
                InitData();
            }
            catch (MySqlException ex)
            {
                Console.WriteLine("Error: {0}", ex.ToString());

            }
            finally
            {
                if (conn != null)
                {
                    conn.Close();
                }
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (textBox5.Text.Length > 0)
            {
                string stm = "SELECT * FROM Student WHERE " + comboBox1.SelectedItem.ToString() + "='" + textBox5.Text+"'";
                try
                {
                    conn = new MySqlConnection(cs);
                    conn.Open();
                    ds = new DataSet();
                    da = new MySqlDataAdapter(stm, conn);
                    da.Fill(ds, "Student");

                    dg.DataSource = ds.Tables["Student"];
                }
                catch (MySqlException ex)
                {
                    Console.WriteLine("Error: " + ex.ToString());

                }
                finally
                {
                    if (conn != null)
                    {
                        conn.Close();
                    }
                }
            }
            else
            {
                InitData();
            }
        }
    }
}
