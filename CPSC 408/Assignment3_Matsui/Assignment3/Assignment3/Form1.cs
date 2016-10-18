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
using System.IO;

namespace Assignment3
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
            cs = @"Database=acsm_3674c400be7e911;Data Source=us-cdbr-azure-west-c.cloudapp.net;User Id=ba1517a46d7795;Password=bc2da882;Pooling=false";
            this.InitData();
        }
        void InitData()
        {
            string stm = "SELECT * FROM Drinks";

            try
            {
                conn = new MySqlConnection(cs);
                conn.Open();
                ds = new DataSet();
                da = new MySqlDataAdapter(stm, conn);
                da.Fill(ds, "Drinks");

                dg.DataSource = ds.Tables["Drinks"];
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

        private void button2_Click(object sender, EventArgs e)
        {
            try
            {
                conn = new MySqlConnection(cs);
                conn.Open();

                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = conn;
                cmd.CommandText = "DELETE FROM Drinks";
                cmd.ExecuteNonQuery();
                cmd.CommandText = "DELETE FROM DrinkRecipe";
                cmd.ExecuteNonQuery();
                cmd.CommandText = "DELETE FROM Ratings";
                cmd.ExecuteNonQuery();
                cmd.CommandText = "DELETE FROM PeopleDrinks";
                cmd.ExecuteNonQuery();
                cmd.CommandText = "DELETE FROM PeopleStats";
                cmd.ExecuteNonQuery();
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
                    InitData();
                }
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (textBox2.Text.Length > 0)
            {
                string stm = textBox2.Text.ToString();
                try
                {
                    conn = new MySqlConnection(cs);
                    conn.Open();
                    ds = new DataSet();
                    da = new MySqlDataAdapter(stm, conn);
                    da.Fill(ds, "NewQuery");

                    dg.DataSource = ds.Tables["NewQuery"];
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

        private void button1_Click(object sender, EventArgs e)
        {
            if (textBox1.Text.Length > 0)
            {
                try
                {
                    conn = new MySqlConnection(cs);
                    conn.Open();
                    MySqlCommand cmd = new MySqlCommand();
                    cmd.Connection = conn;

                    foreach (string line in File.ReadLines(textBox1.Text.ToString(), Encoding.UTF8))
                    {
                        string strippedLine = line.Replace("'", "\\'");
                        string[] tuple = strippedLine.Split(',');
                        int ingredients = Int32.Parse(tuple[1]);

                        for (int i = 0; i < ingredients; i++)
                        {
                            cmd.CommandText = "INSERT INTO DrinkRecipe VALUES(NULL,'" + tuple[0] + "','" + tuple[2 + i] + "')";
                            cmd.ExecuteNonQuery();
                        }
                        cmd.CommandText = "INSERT INTO Drinks VALUES('" + tuple[0] + "','" + tuple[ingredients+2] + "'," + tuple[ingredients+4] + ")";
                        cmd.ExecuteNonQuery();

                        cmd.CommandText = "INSERT INTO Ratings VALUES(NULL,'" + tuple[ingredients + 5] + "','" + tuple[ingredients + 2] + "','" + tuple[ingredients + 3]+ "')";
                        cmd.ExecuteNonQuery();

                        cmd.CommandText = "INSERT INTO PeopleDrinks VALUES(NULL,'" + tuple[ingredients + 6] + " " + tuple[ingredients + 7] + "','" + tuple[ingredients + 0] + "')";
                        cmd.ExecuteNonQuery();

                        try
                        {
                            cmd.CommandText = "INSERT INTO PeopleStats VALUES('" + tuple[ingredients + 6] + " " + tuple[ingredients + 7] + "','" + tuple[ingredients + 8] + "','" + tuple[ingredients + 9] + "')";
                            cmd.ExecuteNonQuery();
                        }
                        catch (MySqlException ex)
                        {
                            Console.WriteLine("Error: {0}", ex.ToString());
                        }

                InitData();
                    }
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
            else
            {
                InitData();
            }
        }
    }
}
