            byte[] src = new byte[] { 1, 2, 3 };
            byte[] dest;

            using (MemoryStream memoryStream = new MemoryStream())
            {
                // 書き込む
                memoryStream.Write(src, 0, src.Length);

                // ストリームの位置を先頭へ戻す
                memoryStream.Seek(0, SeekOrigin.Begin);

                // 読み込む
                dest = new byte[memoryStream.Length];
                int count = memoryStream.Read(dest, 0, dest.Length);
            }


            string str = "シフトJISへ変換";

            Encoding sjisEnc = Encoding.GetEncoding("Shift_JIS");
            byte[] bytes = sjisEnc.GetBytes(str);

            Console.WriteLine(BitConverter.ToString(bytes));
            // 出力：83-56-83-74-83-67-4A-49-53-82-D6-95-CF-8A-B7

            //2バイト文字は二つに分ける。例えばシは0x83,0x56の二つからなる。1バイト文字は一つでよい。
            byte[] bytes = new byte[] {
      0x83, 0x56, 0x83, 0x74, 0x83, 0x67, 0x4A, 0x49,
      0x53, 0x82, 0xD6, 0x95, 0xCF, 0x8A, 0xB7};

            Encoding sjisEnc = Encoding.GetEncoding("Shift_JIS");
            string str = sjisEnc.GetString(bytes);

            // 出力：シフトJISへ変換
            Console.WriteLine(str);


            string text = "文字列";

            //System.Textを省略してEncodingからはじめてよい。using System.Textが追加されていれば問題なく動く。
            //ASCII エンコード
            byte[] data = System.Text.Encoding.ASCII.GetBytes(text);

            //string text = System.Text.Encoding.ASCII.GetString(data);

            //データがShift-JISの場合
            //byte[] data = System.Text.Encoding.GetEncoding("shift_jis").GetBytes(text);

            //データがEUCの場合
            //byte[] data = System.Text.Encoding.GetEncoding("euc-jp").GetBytes(text);

            //データがunicodeの場合
            //byte[] data = System.Text.Encoding.Unicode.GetBytes(text);

            //データがutf-8の場合
            //byte[] data = System.Text.Encoding.UTF8.GetBytes(text);

            
