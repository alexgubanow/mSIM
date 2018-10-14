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
                //    p1[0] = 25;
                //    p1[1] = 22.5f;
                //    p1[2] = 0;
                //    p2[0] = 100;
                //    p2[1] = 47.5f;
                //    p2[2] = 0;
                //    glob[0] = 35;
                //    glob[1] = 40;
                //    offset[0] = 25;
                //    offset[1] = 22.5f;
                //    offset[2] = 0;
                float[] p1 = new float[3] { 15, 15, 0 };
                float[] p2 = new float[3] { 25, 25, 0 };
                float[] loc = new float[3] { 14, 0, 0 };
                float[] glob = new float[3] { 15, 20, 0 };
                float[] offset = new float[3] { 25, 22.5f, 0 };
                float l = preob.getL(p1[0], p2[0], p1[1], p2[1]);
                Console.WriteLine("L= {0:F5}", l);
                float[][] angles = new float[3][];
                for (int i = 0; i < 3; i++)
                {
                    angles[i] = new float[3];
                }
                cosMatrix.getAngles(p1, p2, l, ref angles);

                Console.WriteLine("cosXx= {0:F5}\tcosXy= {1:F5}\tcosXz= {2:F5}", angles[0][0], angles[0][1], angles[0][2]);
                Console.WriteLine("cosYx= {0:F5}\tcosYy= {1:F5}\tcosYz= {2:F5}", angles[1][0], angles[1][1], angles[1][2]);
                Console.WriteLine("cosZx= {0:F5}\tcosZy= {1:F5}\tcosZz= {2:F5}", angles[2][0], angles[2][1], angles[2][2]);

                preob.to_loc(glob, offset, angles, ref loc);

                Console.WriteLine("local coords:");
                Console.WriteLine("x= {0:F5}", loc[0]);
                Console.WriteLine("y= {0:F5}", loc[1]);
                Console.WriteLine("z= {0:F5}", loc[2]);

                //preob.to_glob(loc, offset, angles, ref glob);

                //Console.WriteLine("global coords:");
                //Console.WriteLine("x= {0:F5}", glob[0]);
                //Console.WriteLine("y= {0:F5}", glob[1]);
                //Console.WriteLine("z= {0:F5}", glob[2]);
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
