using System;
using System.IO;
namespace Section
{
    class Program
    {
        static void Main( string[] args )
        {
            if (args.Length >= 2)
            {
                var fi = new FileInfo(args[0]);
                DateTime dt1;
                if (DateTime.TryParse(args[1], out dt1))
                {
                    fi.LastWriteTime = dt1;
                    Console.WriteLine("Success!");
                    Console.WriteLine(dt1);
                }
                else
                {
                    Console.WriteLine("Date Time parse failed.");
                }
            }
            else
            {
                Console.WriteLine("supply arg1(file path) and arg2(date time 2023/6/21 10:41:38)");
            }
        }
    }
}
