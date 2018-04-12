using System.ComponentModel;
using ZedGraph;

namespace simulation.ViewModel
{
    public class forceAx : INotifyPropertyChanged
    {
        public forceAx()
        {
            graphPane = new GraphPane();
            graphPane.Title.Text = "Force";
            graphPane.XAxis.Title.Text = "time";
            graphPane.YAxis.Title.Text = "Y";
            graphPane.XAxis.Scale.FontSpec.Size = 15;
            graphPane.YAxis.Scale.FontSpec.Size = 15;
            graphPane.XAxis.Title.FontSpec.Size = 15;
            graphPane.YAxis.Title.FontSpec.Size = 15;
            graphPane.Legend.FontSpec.Size = 15;
            graphPane.Title.FontSpec.Size = 15;
            graphPane.IsFontsScaled = false;
            graphPane.Border.IsVisible = false;
        }

        private GraphPane _graphPane;

        public GraphPane graphPane
        {
            get { return _graphPane; }
            set { _graphPane = value; RaisePropertyChanged("graphPane"); }
        }

        public event PropertyChangedEventHandler PropertyChanged;

        public void RaisePropertyChanged(string propertyName)
        {
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
        }
    }

    public class acclAx : INotifyPropertyChanged
    {
        public acclAx()
        {
            graphPane = new GraphPane();
            graphPane.Title.Text = "accl";
            graphPane.XAxis.Title.Text = "time";
            graphPane.YAxis.Title.Text = "Y";
            graphPane.XAxis.Scale.FontSpec.Size = 15;
            graphPane.YAxis.Scale.FontSpec.Size = 15;
            graphPane.XAxis.Title.FontSpec.Size = 15;
            graphPane.YAxis.Title.FontSpec.Size = 15;
            graphPane.Legend.FontSpec.Size = 15;
            graphPane.Title.FontSpec.Size = 15;
            graphPane.IsFontsScaled = false;
            graphPane.Border.IsVisible = false;
        }

        private GraphPane _graphPane;

        public GraphPane graphPane
        {
            get { return _graphPane; }
            set { _graphPane = value; RaisePropertyChanged("graphPane"); }
        }

        public event PropertyChangedEventHandler PropertyChanged;

        public void RaisePropertyChanged(string propertyName)
        {
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
        }
    }

    public class velosAx : INotifyPropertyChanged
    {
        public velosAx()
        {
            graphPane = new GraphPane();
            graphPane.Title.Text = "velos";
            graphPane.XAxis.Title.Text = "time";
            graphPane.YAxis.Title.Text = "Y";
            graphPane.XAxis.Scale.FontSpec.Size = 15;
            graphPane.YAxis.Scale.FontSpec.Size = 15;
            graphPane.XAxis.Title.FontSpec.Size = 15;
            graphPane.YAxis.Title.FontSpec.Size = 15;
            graphPane.Legend.FontSpec.Size = 15;
            graphPane.Title.FontSpec.Size = 15;
            graphPane.IsFontsScaled = false;
            graphPane.Border.IsVisible = false;
        }

        private GraphPane _graphPane;

        public GraphPane graphPane
        {
            get { return _graphPane; }
            set { _graphPane = value; RaisePropertyChanged("graphPane"); }
        }

        public event PropertyChangedEventHandler PropertyChanged;

        public void RaisePropertyChanged(string propertyName)
        {
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
        }
    }

    public class displAx : INotifyPropertyChanged
    {
        public displAx()
        {
            graphPane = new GraphPane();
            graphPane.Title.Text = "displ";
            graphPane.XAxis.Title.Text = "time";
            graphPane.YAxis.Title.Text = "Y";
            graphPane.XAxis.Scale.FontSpec.Size = 15;
            graphPane.YAxis.Scale.FontSpec.Size = 15;
            graphPane.XAxis.Title.FontSpec.Size = 15;
            graphPane.YAxis.Title.FontSpec.Size = 15;
            graphPane.Legend.FontSpec.Size = 15;
            graphPane.Title.FontSpec.Size = 15;
            graphPane.IsFontsScaled = false;
            graphPane.Border.IsVisible = false;
        }

        private GraphPane _graphPane;

        public GraphPane graphPane
        {
            get { return _graphPane; }
            set { _graphPane = value; RaisePropertyChanged("graphPane"); }
        }

        public event PropertyChangedEventHandler PropertyChanged;

        public void RaisePropertyChanged(string propertyName)
        {
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
        }
    }

    public class coordAx : INotifyPropertyChanged
    {
        public coordAx()
        {
            graphPane = new GraphPane();
            graphPane.Title.Text = "coord";
            graphPane.XAxis.Title.Text = "time";
            graphPane.YAxis.Title.Text = "Y";
            graphPane.XAxis.Scale.FontSpec.Size = 15;
            graphPane.YAxis.Scale.FontSpec.Size = 15;
            graphPane.XAxis.Title.FontSpec.Size = 15;
            graphPane.YAxis.Title.FontSpec.Size = 15;
            graphPane.Legend.FontSpec.Size = 15;
            graphPane.Title.FontSpec.Size = 15;
            graphPane.IsFontsScaled = false;
            graphPane.Border.IsVisible = false;
        }

        private GraphPane _graphPane;

        public GraphPane graphPane
        {
            get { return _graphPane; }
            set { _graphPane = value; RaisePropertyChanged("graphPane"); }
        }

        public event PropertyChangedEventHandler PropertyChanged;

        public void RaisePropertyChanged(string propertyName)
        {
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}