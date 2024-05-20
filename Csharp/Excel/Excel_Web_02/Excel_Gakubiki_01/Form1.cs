using Excel = Microsoft.Office.Interop.Excel;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

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
            textBox1.Text = @"C:\Users\MatsumotoMinoru\OneDrive\ドキュメント\VBA\取り消し線\SHA010(7.0).xlsx";
        }

        private void button1_Click( object sender, EventArgs e )
        {
            var xapp = new Excel.Application();

            //パスは必ず絶対パスで指定。相対パスだと例外が発生。
            //バックグラウンドで開く
            var wb = xapp.Workbooks.Open(textBox1.Text);

            //シートを開く(indexは1から始まる)
            var sh = wb.Sheets[1] as Excel.Worksheet;

            string xmlValue = "";
            int nRow;
            if(int.TryParse(textBox2.Text, out nRow))
            {

            }
            else
            {
                return;
            }

            int nColumn;
            if(int.TryParse(textBox3.Text, out nColumn))
            {

            }
            else
            {
                return;
            }

            string headerStr = "";
            headerStr = string.Format("Cell({0},{1})", nRow, nColumn);

            //セルの値をxml形成で取得する。
            xmlValue = sh.Cells[nRow, nColumn].Value[Excel.XlRangeValueDataType.xlRangeValueXMLSpreadsheet];
            wb.Close();
            xapp.Quit();

            string textFileName = headerStr + ".xml";

            using (var writer = new StreamWriter(textFileName))
            {
                writer.Write(xmlValue);
            }
        }

        private void button2_Click( object sender, EventArgs e )
        {
            var xapp = new Excel.Application();

            var wb = xapp.Workbooks.Open(textBox1.Text);

            var sh = wb.Sheets[1] as Excel.Worksheet;

            string xmlValue = "";
            int nRow;
            if (int.TryParse(textBox2.Text, out nRow))
            {

            }
            else
            {
                return;
            }

            string headerStr = "";
            headerStr = string.Format("Row({0})", nRow);

            //セルの値をxml形成で取得する。
            xmlValue = sh.Cells[nRow, 1].EntireRow.Value[Excel.XlRangeValueDataType.xlRangeValueXMLSpreadsheet];
            wb.Close();
            xapp.Quit();

            string textFileName = headerStr + ".xml";

            using (var writer = new StreamWriter(textFileName))
            {
                writer.Write(xmlValue);
            }

        }

        private void button3_Click( object sender, EventArgs e )
        {
            var xapp = new Excel.Application();
            var wb = xapp.Workbooks.Open(textBox1.Text);
            var sh = wb.Sheets[1] as Excel.Worksheet;

            //値がある一番下のセルの行番号
            int lastRow = sh.Cells.SpecialCells(Excel.XlCellType.xlCellTypeLastCell, Type.Missing).Row;
            string xmlValue = "";

            for (int i = 5; i <= lastRow; i++)
            {
                xmlValue = sh.Cells[i, 1].EntireRow.Value[Excel.XlRangeValueDataType.xlRangeValueXMLSpreadsheet];
                if (xmlValue.Contains("#FF0000"))//赤色
                {
                    //Textプロパティで値の設定はできない。
                    sh.Cells[i, 22].Value = "更新候補";
                }
            }

            //readOnlyモードだと例外発生
            //すでにあると確認のメッセージが出る。
            wb.SaveAs(textBox1.Text+"_01");
            xapp.Quit();
        }

        private void button4_Click( object sender, EventArgs e )
        {
            var xapp = new Excel.Application();

            var wb = xapp.Workbooks.Open(textBox1.Text);

            var sh = wb.Sheets[1] as Excel.Worksheet;

            string xmlValue = "";
            int nColumn;
            if (int.TryParse(textBox3.Text, out nColumn))
            {

            }
            else
            {
                return;
            }

            string headerStr = "";
            headerStr = string.Format("Column({0})", nColumn);

            //セルの値をxml形成で取得する。
            xmlValue = sh.Cells[1, nColumn].EntireColumn.Value[Excel.XlRangeValueDataType.xlRangeValueXMLSpreadsheet];
            wb.Close();
            xapp.Quit();

            string textFileName = headerStr + ".xml";

            using (var writer = new StreamWriter(textFileName))
            {
                writer.Write(xmlValue);
            }
        }
    }
}
