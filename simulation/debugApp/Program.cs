using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using calcLib;

namespace debugApp
{
    class Program
    {
        static void Main(string[] args)
        {
            bool isWork = true;
            do
            {
                Console.WriteLine("To local or global? [l/g]");
                bool isToLoc = Console.ReadKey(false).Key == ConsoleKey.L ? true : false;
                Console.WriteLine();
                if (isToLoc)
                {
                    double[] initState = new double[6];
                    double[] glob = new double[3];
                    double[] offset = new double[3];
                    initState[0] = 25;
                    initState[1] = 22.5;
                    initState[2] = 0;
                    initState[3] = 100;
                    initState[4] = 47.5;
                    initState[5] = 0;
                    glob[0] = 35;
                    glob[1] = 40;
                    offset[0] = 25;
                    offset[1] = 22.5;
                    //Console.WriteLine("Enter initial X1 global");
                    //double.TryParse(Console.ReadLine().Replace(',', '.'), NumberStyles.Any, CultureInfo.InvariantCulture, out initState[0]);
                    //Console.WriteLine("Enter initial Y1 global");
                    //double.TryParse(Console.ReadLine().Replace(',', '.'), NumberStyles.Any, CultureInfo.InvariantCulture, out initState[1]);
                    //Console.WriteLine("Enter initial X2 global");
                    //double.TryParse(Console.ReadLine().Replace(',', '.'), NumberStyles.Any, CultureInfo.InvariantCulture, out initState[3]);
                    //Console.WriteLine("Enter initial Y2 global");
                    //double.TryParse(Console.ReadLine().Replace(',', '.'), NumberStyles.Any, CultureInfo.InvariantCulture, out initState[4]);
                    //Console.WriteLine("Enter new X1 global");
                    //double.TryParse(Console.ReadLine().Replace(',', '.'), NumberStyles.Any, CultureInfo.InvariantCulture, out glob[0]);
                    //Console.WriteLine("Enter new Y1 global");
                    //double.TryParse(Console.ReadLine().Replace(',', '.'), NumberStyles.Any, CultureInfo.InvariantCulture, out glob[1]);
                    double[] loc = new double[6];
                    double L = preob.getL(initState[0], initState[3], initState[1], initState[4]);
                    Console.WriteLine("L= {0:F5}", L);
                    double sina = preob.getSina(L, initState[1], initState[4]);
                    Console.WriteLine("sina= {0:F5}", sina);
                    double cosa = preob.getCosa(L, initState[0], initState[3]);
                    Console.WriteLine("cosa= {0:F5}", cosa);
                    preob.to_loc(offset, glob, sina, cosa, L, ref loc);
                    Console.WriteLine("local coords:");
                    Console.WriteLine("x1= {0:F5}", loc[0]);
                    Console.WriteLine("y1= {0:F5}", loc[1]);
                    Console.WriteLine("Transformation is done");
                }
                Console.WriteLine("again? [y/n]");
                isWork = Console.ReadKey(false).Key == ConsoleKey.Y ? true : false;
                Console.WriteLine();
            } while (isWork);
            Console.WriteLine("Enter any key to exit");
            Console.ReadKey();
        }
    }
}
