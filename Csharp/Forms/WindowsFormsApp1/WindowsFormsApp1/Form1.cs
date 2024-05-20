using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;
using System.IO;

namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click( object sender, EventArgs e )
        {
            String str = "Hello";
            String str2 = String.Copy(str);
            int num = 12;

            String.ReferenceEquals(str, str2);
            //引数のsenderはこのイベントを呼び出したオブジェクトを示す。
            str = sender.ToString();
            label1.Text = str;
            //出力ウィンドウに表示する(MFCのTRACEと同じ)
            Debug.WriteLine("button1_Click");
            Debug.Print("数は{0}", num);

            textBox1.Text = str2;
            textBox1.ForeColor = Color.Red;//文字の色
            textBox1.BackColor = Color.Blue;
            textBox1.Focus();//テキストボックスにカーソルを表示
        }

        private void Form1_Load( object sender, EventArgs e )
        {//プログラムを起動したときに最初に実行される
            this.Text = "TestProgram";
            button1.Text = "実行";
            
        }

        private void button2_Click( object sender, EventArgs e )
        {
            var desktopPath = Environment.GetFolderPath(Environment.SpecialFolder.Desktop);
            DirectoryInfo di = new DirectoryInfo(desktopPath);
            FileInfo[] fiList = di.GetFiles();
            foreach (var fi in fiList)
            {
                Debug.WriteLine(fi.FullName);
            }
        }
    }
}
