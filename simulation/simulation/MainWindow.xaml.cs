using simulation.ViewModel;
using System;
using System.Drawing;
using System.Linq;
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
        static extern int ColorHLSToRGB(int H, int L, int S);

        public MainWindow()
        {
            InitializeComponent();
            var Main = new MainViewModel();
            //Main.ThrDmod.modelView = this.view;
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
            Dispatcher.BeginInvoke(new Action(() => {
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
            Dispatcher.BeginInvoke(new Action(() => {
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
        int isad = 0;
        private Random rnd = new Random();
        Thread UpdZedThrd;
        private void addFORCE_Click(object sender, RoutedEventArgs e)
        {// Создадим список точек
            PointPairList list = new PointPairList();

            double xmin = -50-isad;
            double xmax = 50+ isad;

            // Заполняем список точек
            for (double x = xmin; x <= xmax; x += 0.01+(isad/10))
            {
                // добавим в список точку
                list.Add(x, f(x));
            }
            isad+=10;
            UpdZedThrd = new Thread(() => updZed(fPlot.ZedGraphPlot));
            Vm.MainWin.forceAx.graphPane.AddCurve("Cosc", list, Color.FromArgb(rnd.Next(256), rnd.Next(256), rnd.Next(256)), SymbolType.None);
            UpdZedThrd.Start();
        }
        Thread srtThread;
        private void startFluentbtn_Click(object sender, RoutedEventArgs e)
        {
            Vm.MainWin.SelectedPlot = 0;
            srtThread = new Thread(calc);
            srtThread.Start();
        }

        private void calc()
        {
            ApplyEffect(this);
            Thread.Sleep(10000);
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