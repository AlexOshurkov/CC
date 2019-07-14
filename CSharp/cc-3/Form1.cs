using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using MySql.Data;
using MySql.Data.MySqlClient;

namespace cc_3
{
    public partial class Form1 : Form
    {
        Object syncRoot = new Object();
        MySqlConnection dbconn;

        public Form1()
        {
            InitializeComponent();
        }

        private String BuildConnectionString(String server, String user, String database, int port, String password)
        {
            if (String.IsNullOrEmpty(server) || String.IsNullOrEmpty(database) || String.IsNullOrEmpty(user) || String.IsNullOrEmpty(password))
            {
                throw new Exception("DBFactory Error: Invalid connection requested, check app config");
            }
            else
            {
                return String.Format("server={0};port={1};database={2};uid={3};password={4};", server, port, database, user, password);
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            string sdb  = "kmrms.c3yz6dco9eld.us-west-2.rds.amazonaws.com";
            int    port = 3306;
            string user = "root";
            string pass = "konicaminoltarmsmysql1234";

            string connstr = BuildConnectionString(sdb, user, "alexdb", port, pass);

            dbconn = new MySqlConnection(connstr);
            dbconn.Open();
        }

        private enum QueryType
        {
            Reader,
            NonQuery,
            Scalar,
        }

        private void Encrypt(string pass, byte[] arr)
        {
            if (arr == null)
                return;

            if (arr.Length == 0)
                return;

            for (int i = 0; i < arr.Length; i++)
                arr[i] =  (byte)(arr[i] ^ pass[i % pass.Length] ^ (i + 1) ^ (arr.Length - i));
        }

        private void Decrypt(string pass, byte[] arr)
        {
            Encrypt(pass, arr);
        }

        private byte[] GetBlobData(MySqlDataReader reader, int col)
        {
            long DataSize = reader.GetBytes(col, 0, null, 0, int.MaxValue);

            if (DataSize == 0)
                return null;

            byte[] Data = new byte[DataSize];
            reader.GetBytes(col, 0, Data, 0, Data.Length);
            return Data;
        }

        private MySqlDataReader ExecuteRQuery(String sqlQuery)
        {
            lock (syncRoot)
            {
                if (dbconn  == null || String.IsNullOrEmpty(sqlQuery))
                    throw new Exception("DB Connection or SQL Query are invalid!");

                MySqlConnection conn = dbconn as MySqlConnection;

                // ensure any previous connection is closed before opening a new one
                if (conn.State.ToString().Equals("Open", StringComparison.InvariantCultureIgnoreCase))
                    conn.Close();

                conn.Open();

                MySqlCommand cmd = new MySqlCommand(sqlQuery, conn);
                return cmd.ExecuteReader(); 
            }
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            dbconn.Close();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            MySqlDataReader ret = ExecuteReadQuery("SELECT * FROM alexdb.table1;");
            string sout = "";
        }



        private void button3_Click(object sender, EventArgs e)
        {
            RMSCrypt.LightCrypt crypt = new RMSCrypt.LightCrypt("password");
            byte[] msg = System.Text.Encoding.Default.GetBytes(textout.Text);
            byte[] compr = RMSCrypt.Compressor.Compress(msg);
            byte[] decompr = RMSCrypt.Compressor.Decompress(compr);
            string msg2 = System.Text.Encoding.Default.GetString(decompr);
        }
    }
}
