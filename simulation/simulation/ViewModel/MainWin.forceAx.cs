using System;
using System.ComponentModel;
using System.Drawing;
using ZedGraph;

namespace simulation.ViewModel
{
    public class forceAx : INotifyPropertyChanged
    {
        private double f1(double x)
        {
            if (x == 0)
            {
                return 1;
            }

            return Math.Sin(x) / x;
        }

        private double f2(double x)
        {
            return Math.Sin(x / 2) / 2;
        }

        public forceAx()
        {
            graphPane = new GraphPane();
            graphPane.Border.IsVisible = false;
            // Установим размеры шрифтов для меток вдоль осей
            graphPane.XAxis.Scale.FontSpec.Size = 15;
            graphPane.YAxis.Scale.FontSpec.Size = 15;

            // Установим размеры шрифтов для подписей по осям
            graphPane.XAxis.Title.FontSpec.Size = 15;
            graphPane.YAxis.Title.FontSpec.Size = 15;

            // Установим размеры шрифта для легенды
            graphPane.Legend.FontSpec.Size = 15;

            // Установим размеры шрифта для общего заголовка
            graphPane.Title.FontSpec.Size = 15;
            graphPane.IsFontsScaled = false;
            Title = "Frco";

            //// Создадим список точек для кривой f1(x)
            //PointPairList f1_list = new PointPairList();

            //// Создадим список точек для кривой f2(x)
            //PointPairList f2_list = new PointPairList();

            //double xmin = -50;
            //double xmax = 50;

            //// !!!
            //// Заполним массив точек для кривой f1(x)
            //for (double x = xmin; x <= xmax; x += 0.01)
            //{
            //    f1_list.Add(x, f1(x));
            //}

            //// !!!
            //// Заполним массив точек для кривой f2(x)
            //// Интервал и шаги по X могут не совпадать на разных кривых
            //for (double x = 0; x <= xmax; x += 0.5)
            //{
            //    f2_list.Add(x, f2(x));
            //}
            ////plotList = new CurveList();
            ////LineItem fg = new LineItem("Sinc", f1_list, Color.Blue, SymbolType.None);
            ////plotList.Add(fg);
            ////plotList.Add(new LineItem("Sin", f2_list, Color.Red, SymbolType.Plus));
            //graphPane.AddCurve("Sinc", f1_list, Color.Blue, SymbolType.Plus);
            //graphPane.AddCurve("Sin", f2_list, Color.Red, SymbolType.Plus);
        }

        private GraphPane _graphPane;
        public GraphPane graphPane
        {
            get { return _graphPane; }
            set { _graphPane = value; RaisePropertyChanged("graphPane"); }
        }


        //private CurveList _plotList;
        //public CurveList plotList { get => _plotList; set {
        //        _plotList = value;
        //        RaisePropertyChanged("plotList"); } }

        private int _SelectedPlot;
        public int SelectedPlot { get => _SelectedPlot; set { _SelectedPlot = value; RaisePropertyChanged("SelectedPlot"); } }

        private string _Title;

        public string Title
        {
            get => _Title;
            set { graphPane.Title.Text = value; _Title = value; RaisePropertyChanged("Title"); }
        }

        public event PropertyChangedEventHandler PropertyChanged;

        public void RaisePropertyChanged(string propertyName)
        {
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}