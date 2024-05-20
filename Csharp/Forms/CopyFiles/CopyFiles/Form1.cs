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
using System.Diagnostics;

namespace CopyFiles
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click( object sender, EventArgs e )
        {
            if (string.IsNullOrWhiteSpace(textBox1.Text))
            {
                MessageBox.Show("Input file extension.");
                return;
            }

            if (string.IsNullOrWhiteSpace(textBox2.Text))
            {
                MessageBox.Show("Input source directory name.");
                return;
            }

            if (string.IsNullOrWhiteSpace(textBox3.Text))
            {
                MessageBox.Show("Input destination directory name.");
            }

            if (!Directory.Exists(textBox2.Text))
            {
                MessageBox.Show("Not exists source directory.");
                return;
            }

            var extList = textBox1.Text.Split(',');
            var copyFromDi = new DirectoryInfo(textBox2.Text);
            var copyToDi = new DirectoryInfo(textBox3.Text);

            FileInfo destfi;
            DirectoryInfo tempdi;
            string destFileName;
            string nowStr = DateTime.Now.ToString();

            foreach (var extension in extList)
            {
                FileInfo[] files = copyFromDi.GetFiles("*." + extension, SearchOption.AllDirectories);

                var logFileName = Path.Combine(copyFromDi.FullName, "copyFiles.log");

                using (var writer = new StreamWriter(logFileName, append: true))
                {
                    writer.WriteLine(nowStr + ",extension:{0}",extension);
                    foreach (var file in files)
                    {
                        destFileName = file.FullName.Replace(copyFromDi.FullName, copyToDi.FullName);
                        destfi = new FileInfo(destFileName);

                        if (!destfi.Exists)
                        {
                            tempdi = destfi.Directory;
                            //If destFileName's directory doesn't exist, Exception occur.
                            if (!tempdi.Exists)
                            {
                                tempdi.Create();
                            }

                            file.CopyTo(destFileName, overwrite: true);
                            writer.WriteLine("NewFile,source:" + file.FullName + ",dest:" + destFileName);
                        }
                        else
                        {
                            
                            TimeSpan dateTimeDiff = file.LastWriteTime - destfi.LastWriteTime;
                            var diffTotalSecondsAbs = Math.Abs(dateTimeDiff.TotalSeconds);
                            //変更日時の差が3秒以内
                            if (diffTotalSecondsAbs <= 3)
                            {
                                //上書きしない
                                writer.WriteLine("NotCopiedTimeStampIsSame,source:" + file.FullName + ",dest:" + destFileName);
                            }
                            //書き込み先の方が新しいとき
                            else if(dateTimeDiff.TotalSeconds < 0)
                            {
                                //上書きしない
                                writer.WriteLine("NotCopiedDistinationIsNewer,source:" + file.FullName + ",dest:" + destFileName);
                            }
                            else
                            {
                                //上書きする
                                file.CopyTo(destFileName, overwrite: true);
                                writer.WriteLine("OverWrote,source:" + file.FullName + ",dest:" + destFileName);
                            }
                        }
                    }
                }
            }

            var memoFileName = Path.Combine(copyToDi.FullName, "backupMemo.txt");
            if (!string.IsNullOrWhiteSpace(textBox4.Text))
            {
                using (var writer = new StreamWriter(memoFileName, append:true))
                {
                    writer.WriteLine(nowStr);
                    writer.Write(textBox4.Text);
                }
            }

            MessageBox.Show("Finished");
        }

        private void button3_Click( object sender, EventArgs e )
        {
            textBox3.Text = textBox2.Text.Replace(@"C:\Users\MatsumotoMinoru\Desktop\Visual Studio 2019", @"C:\Users\MatsumotoMinoru\OneDrive\ドキュメント\Visual Studio 2019");
            
        }

        private void Form1_Load( object sender, EventArgs e )
        {
            textBox1.Text = "lnk,c,hlsl,asm,md,cpp,h,rc,cs,txt,pdf,bmp,config,csproj,csv,ico,json,png,reg,resx,settings,sln,sql,url,vcxproj,xml,filters,rc2,def,user";
        }
    }
}
