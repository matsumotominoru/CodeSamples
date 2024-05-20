using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;
namespace Section01 {
    class Program {        
        static void Main(string[] args) {
            if (args.Length >= 1){
                var xdoc = XDocument.Load(args[0]);
                xdoc.Save(args[0]);
            }
            else{
                Console.Write("supply")
            }
        }
    }
}
