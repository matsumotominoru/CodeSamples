using System;

namespace tga_to_bmp
{
    static class Program
    {
        [STAThread]
        static void Main( string[] args )
        {
            if (args.Length >= 1)
            {
                MtoLib.Pict.RESULT ret;
                MtoLib.Pict.TGA tga = new MtoLib.Pict.TGA();

                var file_name = args[0];
                ret = tga.Create(file_name + ".tga");
                System.Console.WriteLine("Create result:" + ret.ToString());
                if (ret != MtoLib.Pict.RESULT.ERROR_NONE) return;

                tga.ConvertBitType(MtoLib.Pict.TGA.LINE.IMAGE_LINE_LRDU);
                ret = tga.OutputBMP(file_name + ".bmp");
                System.Console.WriteLine("OutputBMP result:" + ret.ToString());
            }
            else
            {
                System.Console.WriteLine("Supply tga file name without extension.");
            }
        }
    }
}
