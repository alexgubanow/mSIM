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
                float[] p1 = new float[3] { 1, 2, 0 };
                float[] p2 = new float[3] { 2, 4, 0 };
                float[] glob = new float[3] { 15, 15, 0 };
                float[] offset = new float[3] { 1, 2, 0 };
                float l = preob.getL(p1[0], p2[0], p1[1], p2[1]);
                Console.WriteLine("L= {0:F5}", l);
                float[] angles = new float[9];
                cosMatrix.getAngles(p1, p2, l, ref angles);

                Console.WriteLine("cosXx= {0:F5}\tcosXy= {1:F5}\tcosXz= {2:F5}", angles[0], angles[1], angles[2]);
                Console.WriteLine("cosYx= {0:F5}\tcosYy= {1:F5}\tcosYz= {2:F5}", angles[3], angles[4], angles[5]);
                Console.WriteLine("cosZx= {0:F5}\tcosZy= {1:F5}\tcosZz= {2:F5}", angles[6], angles[7], angles[8]);

                float[] loc = new float[3];
                preob.to_loc(glob, offset, angles, ref loc);

                Console.WriteLine("local coords:");
                Console.WriteLine("x1= {0:F5}", loc[0]);
                Console.WriteLine("y1= {0:F5}", loc[1]);
                Console.WriteLine("Transformation is done");
                

                //Console.WriteLine("again? [y/n]");
                isWork = Console.ReadKey(false).Key == ConsoleKey.Y ? true : false;
                Console.WriteLine();
            } while (isWork);
            Console.WriteLine("Enter any key to exit");
            Console.ReadKey();
        }
    }
}
