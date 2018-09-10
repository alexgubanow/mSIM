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
                //Console.WriteLine("To local or global? [l/g]");
                //bool isToLoc = Console.ReadKey(false).Key == ConsoleKey.L ? true : false;
                //Console.WriteLine();
                //if (isToLoc)
                //{
                //    float[] p1 = new float[3];
                //    float[] p2 = new float[3];
                //    float[] glob = new float[3];
                //    float[] offset = new float[3];
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
                //    //Console.WriteLine("Enter initial X1 global");
                //    //double.TryParse(Console.ReadLine().Replace(',', '.'), NumberStyles.Any, CultureInfo.InvariantCulture, out initState[0]);
                //    //Console.WriteLine("Enter initial Y1 global");
                //    //double.TryParse(Console.ReadLine().Replace(',', '.'), NumberStyles.Any, CultureInfo.InvariantCulture, out initState[1]);
                //    //Console.WriteLine("Enter initial X2 global");
                //    //double.TryParse(Console.ReadLine().Replace(',', '.'), NumberStyles.Any, CultureInfo.InvariantCulture, out initState[3]);
                //    //Console.WriteLine("Enter initial Y2 global");
                //    //double.TryParse(Console.ReadLine().Replace(',', '.'), NumberStyles.Any, CultureInfo.InvariantCulture, out initState[4]);
                //    //Console.WriteLine("Enter new X1 global");
                //    //double.TryParse(Console.ReadLine().Replace(',', '.'), NumberStyles.Any, CultureInfo.InvariantCulture, out glob[0]);
                //    //Console.WriteLine("Enter new Y1 global");
                //    //double.TryParse(Console.ReadLine().Replace(',', '.'), NumberStyles.Any, CultureInfo.InvariantCulture, out glob[1]);
                //    float[] loc1 = new float[3];
                //    float[] loc2 = new float[3];
                //    float l = preob.getL(p1[0], p2[0], p1[1], p2[1]);
                //    Console.WriteLine("L= {0:F5}", l);

                //    angles angl = new angles(p1, p2, l);

                //    Console.WriteLine("cosXx= {0:F5}", angl.Xx);
                //    Console.WriteLine("cosXy= {0:F5}", angl.Xy);
                //    Console.WriteLine("cosXz= {0:F5}", angl.Xz);
                //    Console.WriteLine("cosYx= {0:F5}", angl.Yx);
                //    Console.WriteLine("cosYx= {0:F5}", angl.Yx);
                //    Console.WriteLine("cosYx= {0:F5}", angl.Yx);


                //    preob.to_loc(p1, offset, angl, ref loc1);
                //    preob.to_loc(p2, offset, angl, ref loc2);

                //    Console.WriteLine("local coords:");
                //    Console.WriteLine("x1= {0:F5}", loc1[0]);
                //    Console.WriteLine("y1= {0:F5}", loc1[1]);
                //    Console.WriteLine("Transformation is done");
                //}
                //Console.WriteLine("again? [y/n]");
                isWork = Console.ReadKey(false).Key == ConsoleKey.Y ? true : false;
                Console.WriteLine();
            } while (isWork);
            Console.WriteLine("Enter any key to exit");
            Console.ReadKey();
        }
    }
}
