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
            // Вызываем метод AxisChange (), чтобы обновить данные об осях. 
            zedGraph.AxisChange();
            // Обновляем график
            zedGraph.Invalidate();
        }
        private void Button_Click(object sender, RoutedEventArgs e)
        {

        }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
        }

        private void objComboBox_GotFocus(object sender, RoutedEventArgs e)
        {
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
        Thread UpdZedThrd;
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
    }
}