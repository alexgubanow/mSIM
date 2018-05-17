using calcLib;
using Microsoft.Win32;
using Newtonsoft.Json;
using simulation.ViewModel;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Drawing;
using System.IO;
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

        private Thread UpdZedThrd;
        public MainViewModel Vm;

        public MainWindow()
        {
            InitializeComponent();
            Vm = new MainViewModel();
            Vm.ThrDmod = new ThrDmod(new FileDialogService(), view1);
            this.DataContext = Vm;
            string jsonFromFile = JSON.ReadFile("materials.mater");
            Vm.MainWin.maters = JsonConvert.DeserializeObject<ObservableCollection<Material>>(jsonFromFile);
            if(Vm.MainWin.maters.Count > 0)
            {
                Vm.MainWin.currProj.Mater = Vm.MainWin.maters[0];
            }
        }


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
                mainPanel.IsEnabled = false;
            }));
        }

        private void ClearEffect(Window win)
        {
            Dispatcher.BeginInvoke(new Action(() =>
            {
                mainPanel.IsEnabled = true;
                mainPanel.Effect = null;
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

        private void materGroupBox_GotFocus(object sender, RoutedEventArgs e)
        {
            Vm.MainWin.MaterialsVis = Visibility.Visible;
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
            int nodes = Vm.MainWin.currProj.elems + 1;
            double l = Vm.MainWin.currProj.Mater.L / Vm.MainWin.currProj.elems * Math.Pow(10, -3);
            linearModel = new Linear.Model(Vm.MainWin.currProj.counts, Vm.MainWin.currProj.dT, nodes, Vm.MainWin.currProj.elems,
                Vm.MainWin.currProj.Mater.ro, Vm.MainWin.currProj.Mater.E, l, Vm.MainWin.currProj.Mater.b, Vm.MainWin.currProj.Mater.h);
            Linear.Model.init.Load(100, (1 * Math.Pow(10, -2)), linearModel.time, ref linearModel.N);
            Linear.Model.init.Coords(l, ref linearModel.N, ref linearModel.E);
            linearModel.calcMove();
            plotData();
            ClearEffect(this);
        }

        private void plotData()
        {
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
        }

        private void btn_abrt_Click(object sender, RoutedEventArgs e)
        {
            srtThread.Abort();
            GC.Collect();
            ClearEffect(this);
        }

        private void loadMaterBtn_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "Material file (*.mater)|*.mater";
            if (openFileDialog.ShowDialog() == true)
            {
                try
                {
                    string jsonFromFile = JSON.ReadFile(openFileDialog.FileName);
                    Vm.MainWin.currProj.Mater = JsonConvert.DeserializeObject<Material>(jsonFromFile);
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }
        }
        

        private void exportMaterBtn_Click(object sender, RoutedEventArgs e)
        {
            SaveFileDialog saveFileDialog = new SaveFileDialog();
            saveFileDialog.Filter = "Material file (*.mater)|*.mater";
            if (saveFileDialog.ShowDialog() == true)
            {
                string json = JsonConvert.SerializeObject(Vm.MainWin.maters);
                Console.WriteLine(json);
                JSON.SaveInFile(json, saveFileDialog.FileName);
            }
        }

        private void addMaterBtn_Click(object sender, RoutedEventArgs e)
        {
            Vm.MainWin.maters.Add(new Material());
            Vm.RaisePropertyChanged("maters");
            Vm.MainWin.currProj.Mater = Vm.MainWin.maters[Vm.MainWin.maters.Count - 1];
            Vm.MainWin.SelectedRibbonTab = 2;
        }

        private void openFluentBtn_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "Load file (*.lod)|*.lod";
            if (openFileDialog.ShowDialog() == true)
            {
                try
                {
                    string jsonFromFile = JSON.ReadFile(openFileDialog.FileName);
                    Vm.MainWin.currProj.l = JsonConvert.DeserializeObject<Load>(jsonFromFile);
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }
        }

        private void exportLoadBtn_Click(object sender, RoutedEventArgs e)
        {
            SaveFileDialog saveFileDialog = new SaveFileDialog();
            saveFileDialog.Filter = "Load file (*.lod)|*.lod";
            if (saveFileDialog.ShowDialog() == true)
            {
                string json = JsonConvert.SerializeObject(Vm.MainWin.currProj.l);
                Console.WriteLine(json);
                JSON.SaveInFile(json, saveFileDialog.FileName);
            }
        }
    }
}