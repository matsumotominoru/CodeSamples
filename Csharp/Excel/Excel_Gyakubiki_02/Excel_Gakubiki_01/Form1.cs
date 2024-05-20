using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Excel = Microsoft.Office.Interop.Excel;

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
            
        }

        private void button1_Click( object sender, EventArgs e )
        {
            var xapp = new Excel.Application();
            //エクセルを表示
            xapp.Visible = true;
            var wb = xapp.Workbooks.Open(@"C:\Users\MatsumotoMinoru\XML構造設計書(消費-申告)Ver7x.xlsx");
            var sh = wb.Sheets[1] as Excel.Worksheet;
            int r = 5;
            var items = new List<Data>();
            while (sh.Cells[r, 1].Text != "")
            {
                var data = new Data()
                {
                    //安全のため、Textプロパティによってstring型で取得する。
                    //ValueプロパティのときはExcelに設定されているデータ型に自動で変換される。強引にキャストすると例外発生。
                    ID = sh.Cells[r, 1].Text,
                    Title = sh.Cells[r, 2].Text,
                    Price = sh.Cells[r, 3].Text
                };
                items.Add(data);
                r++;
            }
            //DataGridViewにデータソースを追加
            dataGridView1.DataSource = items;

            xapp.Quit();
        }
    }

    public class Data
    {
        public string ID { get; set; }
        public string Title { get; set; }
        public string Price { get; set; }
    }
}
