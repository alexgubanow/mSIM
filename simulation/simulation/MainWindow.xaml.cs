using simulation.ViewModel;
using System;
using System.Linq;
using System.Runtime.InteropServices;
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
        public MainWindow()
        {
            InitializeComponent();
            var Main = new MainViewModel();
            //Main.ThrDmod.modelView = this.view;
            this.DataContext = Main;
            // Получим панель для рисования
            //GraphPane pane = forcePlot.GraphPane;
            forcePlot.GraphPane.Title.Text = "Force";
            acclPlot.GraphPane.Title.Text = "accl";
            velosPlot.GraphPane.Title.Text = "velos";
            displPlot.GraphPane.Title.Text = "displ";
            coordsPlot.GraphPane.Title.Text = "coords";
        }
        public MainViewModel Vm { get { return (MainViewModel)DataContext; } }

        [DllImport("shlwapi.dll")]
        static extern int ColorHLSToRGB(int H, int L, int S);
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
        
    }
}