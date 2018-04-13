using calcLib;
using simulation.ViewModel;
using System;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Threading;
using System.Windows;
using System.Windows.Controls;
using ZedGraph;

namespace simulation
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow
    {
        [DllImport("shlwapi.dll")]
        private static extern int ColorHLSToRGB(int H, int L, int S);

        public MainWindow()
        {
            InitializeComponent();
            var Main = new MainViewModel();
            Main.ThrDmod = new ThrDmod(new FileDialogService(), view1);
            this.DataContext = Main;
        }

        public MainViewModel Vm { get { return (MainViewModel)DataContext; } }

        private void updZed(ZedGraphControl zedGraph)
        {
            zedGraph.AxisChange();
            zedGraph.Invalidate();
        }

        private void ApplyEffect(Window win)
        {
            Dispatcher.BeginInvoke(new Action(() =>
            {
                System.Windows.Media.Effects.BlurEffect objBlur = new System.Windows.Media.Effects.BlurEffect();
                objBlur.Radius = 4;
                //mngr.Visibility = Visibility.Collapsed;
                btn_abrt.Visibility = Visibility.Visible;
                overlayrect.Visibility = Visibility.Visible;
                overlayring.Visibility = Visibility.Visible;
                mainPanel.Effect = objBlur;
            }));
        }

        private void ClearEffect(Window win)
        {
            Dispatcher.BeginInvoke(new Action(() =>
            {
                mainPanel.Effect = null;
                //mngr.Visibility = Visibility.Visible;
                btn_abrt.Visibility = Visibility.Collapsed;
                overlayrect.Visibility = Visibility.Collapsed;
                overlayring.Visibility = Visibility.Collapsed;
            }));
        }

        private void Ribbon_SelectedTabChanged(object sender, SelectionChangedEventArgs e)
        {
            if (Vm.MainWin.SelectedRibbonTab != 2)
            {
                Vm.MainWin.MaterialsVis = Visibility.Collapsed;
            }
        }

        private void objGroupBox_GotFocus(object sender, RoutedEventArgs e)
        {
            Vm.MainWin.MaterialsVis = Visibility.Visible;
        }

        private double f(double x)
        {
            if (x == 0)
            {
                return 1;
            }

            return Math.Sin(x) / x;
        }

        private int isad = 0;
        private Random rnd = new Random();
        private Thread UpdZedThrd;

        private void addFORCE_Click(object sender, RoutedEventArgs e)
        {// Создадим список точек
            PointPairList list = new PointPairList();

            double xmin = -50 - isad;
            double xmax = 50 + isad;

            // Заполняем список точек
            for (double x = xmin; x <= xmax; x += 0.01 + (isad / 10))
            {
                // добавим в список точку
                list.Add(x, f(x));
            }
            isad += 10;
            Vm.MainWin.forceAx.graphPane.AddCurve("Cosc", list, Color.FromArgb(rnd.Next(256), rnd.Next(256), rnd.Next(256)), SymbolType.None);
            UpdZedThrd = new Thread(() => updZed(fPlot.ZedGraphPlot));
            UpdZedThrd.Start();
        }

        private Thread srtThread;

        private void startFluentbtn_Click(object sender, RoutedEventArgs e)
        {
            Vm.MainWin.SelectedPlot = 0;
            srtThread = new Thread(calc);
            srtThread.Start();
        }

        public Linear.Model linearModel { get; private set; }

        private void calc()
        {
            ApplyEffect(this);
            int counts = 20000;
            double dt = 0.000001;
            int elements = 5;
            //int points = elements * 2;
            int nodes = elements + 1;
            double Length = 50;
            double l = Length / elements * Math.Pow(10, -3);
            double b = 50 * Math.Pow(10, -3);
            double h = 0.1 * Math.Pow(10, -3);
            double massa = 0.1;
            linearModel = new Linear.Model(counts, dt, nodes, elements, massa, l, b, h);
            Linear.Model.init.Load(100, (1 * Math.Pow(10, -2)), linearModel.time, ref linearModel.N);
            Linear.Model.init.Coords(l,ref linearModel.N);
            linearModel.calcMove();

            for (int j = 0; j < linearModel.N[j].Length; j++)
            {
                double[] amps = new double[linearModel.N.Length];
                for (int i = 0; i < linearModel.N.Length; i++)
                {
                    amps[i] = linearModel.N[i][j].deriv.force[0];
                }
                Dispatcher.Invoke(new Action(() =>
                {
                    Vm.MainWin.forceAx.graphPane.AddCurve("n" + j, linearModel.time, amps, Color.Red, SymbolType.None);
                }));
            }
            for (int j = 0; j < linearModel.N[j].Length; j++)
            {
                double[] amps = new double[linearModel.N.Length];
                for (int i = 0; i < linearModel.N.Length; i++)
                {
                    amps[i] = linearModel.N[i][j].deriv.accl[0];
                }
                Dispatcher.Invoke(new Action(() =>
                {
                    Vm.MainWin.acclAx.graphPane.AddCurve("n" + j, linearModel.time, amps, Color.Red, SymbolType.None);
                }));
            }
            for (int j = 0; j < linearModel.N[j].Length; j++)
            {
                double[] amps = new double[linearModel.N.Length];
                for (int i = 0; i < linearModel.N.Length; i++)
                {
                    amps[i] = linearModel.N[i][j].deriv.velos[0];
                }
                Dispatcher.Invoke(new Action(() =>
                {
                    Vm.MainWin.velosAx.graphPane.AddCurve("n" + j, linearModel.time, amps, Color.Red, SymbolType.None);
                }));
            }
            for (int j = 0; j < linearModel.N[j].Length; j++)
            {
                double[] amps = new double[linearModel.N.Length];
                for (int i = 0; i < linearModel.N.Length; i++)
                {
                    amps[i] = linearModel.N[i][j].deriv.displ[0];
                }
                Dispatcher.Invoke(new Action(() =>
                {
                    Vm.MainWin.displAx.graphPane.AddCurve("n" + j, linearModel.time, amps, Color.Red, SymbolType.None);
                }));
            }
            for (int j = 0; j < linearModel.N[j].Length; j++)
            {
                double[] amps = new double[linearModel.N.Length];
                for (int i = 0; i < linearModel.N.Length; i++)
                {
                    amps[i] = linearModel.N[i][j].deriv.coord[0];
                }
                Dispatcher.Invoke(new Action(() =>
                {
                    Vm.MainWin.coordAx.graphPane.AddCurve("n" + j, linearModel.time, amps, Color.Red, SymbolType.None);
                }));
            }
            UpdZedThrd = new Thread(() => updZed(fPlot.ZedGraphPlot));
            UpdZedThrd.Start();
            ClearEffect(this);
        }

        private void btn_abrt_Click(object sender, RoutedEventArgs e)
        {
            srtThread.Abort();
            GC.Collect();
            ClearEffect(this);
        }
    }
}