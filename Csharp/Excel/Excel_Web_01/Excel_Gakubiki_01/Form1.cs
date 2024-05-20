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
            var xlApp = new Microsoft.Office.Interop.Excel.Application();
            var xlBooks = xlApp.Workbooks;
            var xlBook = xlBooks.Open(
            textBox1.Text, Type.Missing, Type.Missing,
            Type.Missing, Type.Missing, Type.Missing,
            Type.Missing, Type.Missing, Type.Missing,
            Type.Missing, Type.Missing, Type.Missing,
            Type.Missing, Type.Missing, Type.Missing
            );

            // シートを選択
            var sheet = xlBook.Sheets["メンバー一覧"];

            // セルの領域を選択
            var TableRange = sheet.Range["A1", "B15"];

            // 選択した領域の値をメモリー上に格納
            object[,] values = TableRange.Value;

            // 配列アクセスができるので、それぞれをDictionaryに追加
            string str = "";
            for (int i = 1; i <= values.GetLength(0); i++)
            {
                //セルに数値が入っている場合、valueはdouble型となり、string型にキャストすると例外が発生する。
                str = string.Format("{0}:{1}", (string)values[i, 1], values[i, 2]);
                MessageBox.Show(str);
            }

            // 使用したCOMオブジェクトを解放
            System.Runtime.InteropServices.Marshal.ReleaseComObject(TableRange);
            System.Runtime.InteropServices.Marshal.ReleaseComObject(sheet);

            // Excelのクローズ
            xlBook.Close();
            xlApp.Quit();

            // 使用したCOMオブジェクトを解放その２
            System.Runtime.InteropServices.Marshal.FinalReleaseComObject(xlBook);
            System.Runtime.InteropServices.Marshal.FinalReleaseComObject(xlBooks);
            System.Runtime.InteropServices.Marshal.FinalReleaseComObject(xlApp);
        }
    }
}
