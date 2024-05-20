using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Excel_Gakubiki_01
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load( object sender, EventArgs e )
        {
            textBox1.Text = @"C:\Users\MatsumotoMinoru\test1.xlsx";
        }

        private void button1_Click( object sender, EventArgs e )
        {
            var xapp = new Microsoft.Office.Interop.Excel.Application();

            //パスは必ず絶対パスで指定。相対パスだと例外が発生。
            //バックグラウンドで開く
            var wb = xapp.Workbooks.Open(textBox1.Text);

            //シートを開く(indexは1から始まる)
            var sh = wb.Sheets[1] as Microsoft.Office.Interop.Excel.Worksheet;

            //セルの値を取得
            //Valueの場合、日付や数値を変換して取得する
            //Textの場合、テキストのまま取得
            label1.Text = sh.Range["A1"].Value;
            wb.Close();
            xapp.Quit();
            //本来はCOMのメモリを解放するコードを書く必要があるが、
            //書かなくても異常が出なかった場合、アプリを終了すると自動でメモリが解放される。
        }
    }
}
