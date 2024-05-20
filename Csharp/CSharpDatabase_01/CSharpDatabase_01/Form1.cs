using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.SqlClient;

namespace CSharpDatabase_01
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click( object sender, EventArgs e )
        {
            string sqlConnect = "Server=(localdb)\\MSSQLLocalDB;Database=C:\\USERS\\MATSUMOTOMINORU\\DATA\\SQLSERVERLOCAL\\TEST.MDF;Integrated Security=SSPI";
            string sqlCommand = "SELECT * FROM [dbo].[Table]";

            using (SqlConnection cn = new SqlConnection(sqlConnect))
            {
                //ログインせずに以下を行うと例外が発生する。
                cn.Open();
                SqlCommand cmd = new SqlCommand(sqlCommand, cn);
                SqlDataReader reader = cmd.ExecuteReader(CommandBehavior.CloseConnection);
                while (reader.Read())
                {
                    //2列目のデータを追加
                    listBox1.Items.Add(reader[1].ToString());
                }
            }
            

        }
    }
}
