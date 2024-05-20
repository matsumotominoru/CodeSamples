using System;
using System.Drawing;
using System.Windows.Forms;

class Program
{
    [STAThread]
    static void Main()
    {
        Application.EnableVisualStyles();
        Form form = new Form1();
        form.Text = "Menu Test";  // フォームのタイトル
        Application.Run(form);
    }
}

class Form1 : Form
{
    MenuStrip menuStrip = new MenuStrip();

    public Form1()
    {
        ToolStripMenuItem menuFile = new ToolStripMenuItem();
        menuFile.Text = "ファイル(&F)";

        ToolStripMenuItem menuAcs = new ToolStripMenuItem();
        menuAcs.Text = "アクセサリ(&A)";

        ToolStripMenuItem mi1 = new ToolStripMenuItem("電卓(&C)");
        mi1.Click += new EventHandler(onClick);
        mi1.Image = Image.FromFile(@"C:\Windows\System32\WindowsSecurityIcon.png");

        ToolStripMenuItem mi2 = new ToolStripMenuItem("時計(&T)");
        mi2.Click += new EventHandler(onClick);
        mi2.Image = Image.FromFile(@"C:\Windows\System32\WindowsSecurityIcon.png");

        ToolStripSeparator tsSep = new ToolStripSeparator();

        ToolStripMenuItem miExit = new ToolStripMenuItem("終了(&X)");
        miExit.Click += new EventHandler(onExitClick);

        menuAcs.DropDownItems.AddRange(new ToolStripItem[] { mi1, mi2, tsSep, miExit });

        menuStrip.Items.AddRange(new ToolStripItem[] { menuFile, menuAcs });

        this.Controls.Add(menuStrip);
        this.MainMenuStrip = menuStrip;
 
    }

    void onClick(object sender, EventArgs e)
    {
        MessageBox.Show(((ToolStripMenuItem)sender).Text + "が選択されました", "Menu選択");
    }

    void onExitClick(object sender, EventArgs e)
    {
        this.Close();
    }
}