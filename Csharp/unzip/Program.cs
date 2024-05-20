using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;
using System.IO.Compression;
namespace Section01 {
    class Program {        
        static void Main(string[] args) {
            if (args.Length >= 2){

                string zipPath = args[0];
                string extractBasePath = args[1];
                string zipEntry = "docProps/core.xml";
                var extractedPath = ExtractZip(zipPath, extractBasePath, zipEntry);
                if (extractedPath.Length != 0)
                {
                    Console.WriteLine("Unzip succeeded!");
                }
                else
                {
                    Console.WriteLine("Unzip Failed");
                    return;
                }
                XNamespace cp = "http://schemas.openxmlformats.org/package/2006/metadata/core-properties";
                var xdoc = XDocument.Load(extractedPath);
                var name_string = "lastModifiedBy";
                var xname = xdoc.Root.Element(cp + name_string);
                Console.WriteLine(name_string + "=" +xname.Value);
                xdoc.Save(extractedPath);
            }
            else
            {
                Console.Write("Supply args");
            }
        }

        static string ExtractZip(string zipPath, string extractBasePath, string zipEntry)
        {
            var extractedPath = "";
            using (var archive = ZipFile.OpenRead(zipPath))
            {
                var fileEntry = archive.GetEntry(zipEntry);
                extractedPath = zipEntry.Replace("/", "_");
                extractedPath = Path.Combine(extractBasePath, extractedPath);
                fileEntry.ExtractToFile(extractedPath, true);
            }
            return extractedPath;
        }
    }
}
