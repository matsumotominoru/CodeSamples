using System;
using System.IO;
using System.Net;

namespace Console_Frame_ch_12_2
{
    class Program
    {
        // ストリームからデータを読み込み、バイト配列に格納
        static public byte[] ReadBinaryData( Stream st )
        {

            byte[] buf = new byte[32768]; // 一時バッファ

            using (MemoryStream ms = new MemoryStream())
            {

                while (true)
                {
                    // ストリームから一時バッファに読み込む
                    //読み込むメモリのサイズはランダム？
                    int read = st.Read(buf, 0, buf.Length);

                    if (read > 0)
                    {
                        // 一時バッファの内容をメモリ・ストリームに書き込む
                        ms.Write(buf, 0, read);
                        Console.WriteLine(read);
                    }
                    else
                    {
                        break;
                    }
                }
                // メモリ・ストリームの内容をバイト配列に格納
                return ms.ToArray();
            }
        }

        static void Main( string[] args )
        {
            string url
              = "http://www.atmarkit.co.jp/fdotnet/images/fdotnet_m.gif";
            byte[] data;

            WebRequest req = WebRequest.Create(url);

            using (WebResponse res = req.GetResponse())
            {
                using (Stream st = res.GetResponseStream())
                {
                    data = ReadBinaryData(st);
                }
                File.WriteAllBytes("test.gif", data);
            }
        }

    }
}
