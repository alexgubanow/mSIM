using calcLib;
using LiveCharts;
using LiveCharts.Wpf;
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
using System.Threading.Tasks;
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
        public MainViewModel Vm { get { return (MainViewModel)DataContext; } }

        public MainWindow()
        {
            InitializeComponent();
            var Main = new MainViewModel();
            Main.ThrDmod = new ThrDmod(new FileDialogService(), view1);
            this.DataContext = Main;
            string jsonFromFile = JSON.ReadFile("materials.mater");
            Vm.MainWin.maters = JsonConvert.DeserializeObject<ObservableCollection<Material>>(jsonFromFile);
            if(Vm.MainWin.maters.Count > 0)
            {
                Vm.MainWin.SelectedMater = Vm.MainWin.maters[0];
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
            integr.Schems CurriS = Vm.MainWin.IntegrSchem;
            srtThread = new Thread(() => calc(CurriS));
            srtThread.Start();
        }

        public mModel mModel { get; private set; }

        private void calc(integr.Schems iS)
        {
            ApplyEffect(this);
            uint counts = 100000;
            float dt = 0.0001f;
            //int elements = 5;
            ////int points = elements * 2;
            //int nodes = elements + 1;
            ////double Length = 80;
            //Material currMater = new Material();
            //Dispatcher.Invoke(new Action(() =>
            //{
            //    currMater = Vm.MainWin.SelectedMater;
            //}));
            //float l = currMater.L / elements * (float)Math.Pow(10, -3);
            ////float l = 0.5f;
            ////double b = 50 * Math.Pow(10, -3);
            ////double h = 0.1 * Math.Pow(10, -3);
            ////double massa = 0.1;
            //linearModel = new LinearModel(counts, dt, nodes, elements, currMater.ro, currMater.E, l, currMater.b, currMater.h);
            //LinearModel.initCoords(l, counts, ref linearModel.N, ref linearModel.E);
            //LinearModel.initLoad(100, (1 * (float)Math.Pow(10, -3)), linearModel.time, ref linearModel.N);
            //linearModel.calcMove();
            double[] timeD = new double[counts];
            //Parallel.For(0, counts, i => {
            //    timeD[i] = linearModel.time[i];
            //});
            float[] t = new float[counts];
            for (int i = 1; i < t.Length; i++)
            {
                t[i] = t[i - 1] + dt;
                timeD[i] = t[i - 1] + dt;
            }
            float[][][] deriv = new float[t.Length][][];
            for (int i = 0; i < t.Length; i++)
            {
                deriv[i] = new float[6][];
                for (int j = 0; j < 6; j++)
                {
                    deriv[i][j] = new float[3];
                }
            }
            for (int i = 1; i < t.Length; i++)
            {
                deriv[i][5][0] = 10 * (float)Math.Exp(-1 * t[i]) * (float)Math.Sin(t[i] * 2.0f * Math.PI * 1);
            }
            for (int i = 2; i < t.Length; i++)
            {
                switch (iS)
                {
                    case integr.Schems.euler:
                        integr.euler(ref deriv, i - 1, i, 1, 1, dt);
                        break;
                    case integr.Schems.verlet:
                        integr.verlet(ref deriv, i - 1, i, 1, 1, dt);
                        break;
                    case integr.Schems.gear:
                        float[][] derivP = deriv[i];
                        integr.gearp(ref derivP, 1, deriv[i - 1][(int)DerivEnum.a], deriv[i - 1][(int)DerivEnum.coord], 1, dt);
                        integr.gearc(ref deriv, derivP, i - 1, i, 1, 1, dt);
                        break;
                }
            }

            double[] amps = new double[counts];
            Parallel.For(0, counts, i => {
                amps[i] = deriv[i][(int)DerivEnum.force][0];
            });
            Dispatcher.Invoke(new Action(() =>
            {
                Vm.MainWin.forceAx.graphPane.AddCurve("n" + 0, timeD, amps, Color.Red, SymbolType.None);
            }));
            Parallel.For(0, counts, i => {
                amps[i] = deriv[i][(int)DerivEnum.a][0];
            });
            Dispatcher.Invoke(new Action(() =>
            {
                Vm.MainWin.acclAx.graphPane.AddCurve("n" + 0, timeD, amps, Color.Red, SymbolType.None);
            }));
            Parallel.For(0, counts, i => {
                amps[i] = deriv[i][(int)DerivEnum.v][0];
            });
            Dispatcher.Invoke(new Action(() =>
            {
                Vm.MainWin.velosAx.graphPane.AddCurve("n" + 0, timeD, amps, Color.Red, SymbolType.None);
            }));
            Parallel.For(0, counts, i => {
                amps[i] = deriv[i][(int)DerivEnum.u][0];
            });
            Dispatcher.Invoke(new Action(() =>
            {
                Vm.MainWin.displAx.graphPane.AddCurve("n" + 0, timeD, amps, Color.Red, SymbolType.None);
            }));
            Parallel.For(0, counts, i => {
                amps[i] = deriv[i][(int)DerivEnum.coord][0];
            });
            Dispatcher.Invoke(new Action(() =>
            {
                Vm.MainWin.coordAx.graphPane.AddCurve("n" + 0, timeD, amps, Color.Red, SymbolType.None);
            }));
            //for (int n = 0; n < linearModel.N.Length; n++)
            //{
            //    double[] amps = new double[counts];
            //    Parallel.For(0, counts, i => {
            //        amps[i] = linearModel.N[n].deriv[i][(int)DerivEnum.force][0];
            //    });
            //    Dispatcher.Invoke(new Action(() =>
            //    {
            //        Vm.MainWin.forceAx.graphPane.AddCurve("n" + n, timeD, amps, Color.Red, SymbolType.None);
            //    }));
            //}
            //for (int n = 0; n < linearModel.N.Length; n++)
            //{
            //    double[] amps = new double[counts];
            //    Parallel.For(0, counts, i => {
            //        amps[i] = linearModel.N[n].deriv[i][(int)DerivEnum.a][0];
            //    });
            //    Dispatcher.Invoke(new Action(() =>
            //    {
            //        Vm.MainWin.acclAx.graphPane.AddCurve("n" + n, timeD, amps, Color.Red, SymbolType.None);
            //    }));
            //}
            //for (int n = 0; n < linearModel.N.Length; n++)
            //{
            //    double[] amps = new double[counts];
            //    Parallel.For(0, counts, i => {
            //        amps[i] = linearModel.N[n].deriv[i][(int)DerivEnum.v][0];
            //    });
            //    Dispatcher.Invoke(new Action(() =>
            //    {
            //        Vm.MainWin.velosAx.graphPane.AddCurve("n" + n, timeD, amps, Color.Red, SymbolType.None);
            //    }));
            //}
            //for (int n = 0; n < linearModel.N.Length; n++)
            //{
            //    double[] amps = new double[counts];
            //    Parallel.For(0, counts, i => {
            //        amps[i] = linearModel.N[n].deriv[i][(int)DerivEnum.u][0];
            //    });
            //    Dispatcher.Invoke(new Action(() =>
            //    {
            //        Vm.MainWin.displAx.graphPane.AddCurve("n" + n, timeD, amps, Color.Red, SymbolType.None);
            //    }));
            //}
            //for (int n = 0; n < linearModel.N.Length; n++)
            //{
            //    double[] amps = new double[counts];
            //    Parallel.For(0, counts, i => {
            //        amps[i] = linearModel.N[n].deriv[i][(int)DerivEnum.coord][0];
            //    });
            //    Dispatcher.Invoke(new Action(() =>
            //    {
            //        Vm.MainWin.coordAx.graphPane.AddCurve("n" + n, timeD, amps, Color.Red, SymbolType.None);
            //    }));
            //}
            UpdZedThrd = new Thread(() => updZed(fPlot.ZedGraphPlot));
            UpdZedThrd.Start();
            //var cv = new ChartValues<float>();
            //cv.AddRange(linearModel.N[0].deriv[(int)DerivEnum.force][0]);
            //Dispatcher.Invoke(new Action(() =>
            //{
            //    Vm.MainWin.forceAxLV.SeriesCollection.Clear();
            //    Vm.MainWin.forceAxLV.SeriesCollection.Add(new LineSeries
            //    {
            //        Title = "Series 1",
            //        Values = cv,
            //        LineSmoothness = 1
            //    });
            //}));
            ClearEffect(this);
        }

        private void btn_abrt_Click(object sender, RoutedEventArgs e)
        {
            srtThread.Abort();
            GC.Collect();
            ClearEffect(this);
        }

        private void loadMaterBtn_Click(object sender, RoutedEventArgs e)
        {
            //OpenFileDialog openFileDialog = new OpenFileDialog();
            //openFileDialog.Filter = "Material file (*.mater)|*.mater";
            //if (openFileDialog.ShowDialog() == true)
            //{
            //    try
            //    {
            //        string jsonFromFile = JSON.ReadFile(openFileDialog.FileName);
            //        Vm.MainWin.SelectedMater = JsonConvert.DeserializeObject<Material>(jsonFromFile);
            //    }
            //    catch (Exception ex)
            //    {
            //        MessageBox.Show(ex.Message);
            //    }
            //}
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
            Vm.MainWin.SelectedMater = Vm.MainWin.maters[Vm.MainWin.maters.Count - 1];
            Vm.MainWin.SelectedRibbonTab = 2;
        }
        
    }
}