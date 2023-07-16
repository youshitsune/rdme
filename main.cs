using System;
using System.IO;

class App{
    static void Main(string[] args){
        if (args.Length == 1) {
            if (args[0].Equals("-h") || args[0].Equals("--help")) {
                Console.WriteLine("usage: rdme FILE");
            } else {
                string[] ctx = File.ReadAllLines(args[0]);
                
                foreach (var str in ctx){
                    try{
                        if (str[0].Equals('#')) {
                            Console.ForegroundColor = ConsoleColor.Red;
                            Console.WriteLine(str);
                            Console.ResetColor();
                        }
                        else{
                            Console.WriteLine(str);
                        }
                    }
                    catch (Exception e){
                        Console.WriteLine(str);
                    }
                }
            }
        } else {
            Console.WriteLine("usage: rdme FILE");
        }
    }
}

