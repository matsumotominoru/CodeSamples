using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Section01 {
    class Program {
        static void Main(string[] args) {
            Product karinto = new Product(123, "karinto", 180);
            Product daifuku = new Product(235, "daifukumochi", 160);
            int karintoTax = karinto.GetTax();
            int daifukuTax = daifuku.GetTax();

            Console.WriteLine("{0} {1} {2}", karinto.Name, karinto.Price, karintoTax);
            Console.WriteLine("{0} {1} {2}", daifuku.Name, daifuku.Price, daifukuTax);

        }
    }
    // List 1-1
    public class Product {
        public int Code { get; private set; }
        public string Name { get; private set; }
        public int Price { get; private set; }

        // コンストラクタ
        public Product(int code, string name, int price) {
            this.Code = code;
            this.Name = name;
            this.Price = price;
        }

        // 消費税額を求める
        public int GetTax() {
            return (int)(Price * 0.08);
        }

        // 税込価格を求める
        public int GetPriceIncludingTax() {
            return Price + GetTax();
        }

    }
}
