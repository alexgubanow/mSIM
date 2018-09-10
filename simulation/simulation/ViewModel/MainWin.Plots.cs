using LiveCharts;
using ZedGraph;

namespace simulation.ViewModel
{
    public class forceAxLV : nPropChanged
    {
        public forceAxLV()
        {
            SeriesCollection = new SeriesCollection();
        }

        private SeriesCollection _SeriesCollection;

        public SeriesCollection SeriesCollection
        {
            get { return _SeriesCollection; }
            set { _SeriesCollection = value; RaisePropertyChanged("SeriesCollection"); }
        }
    }

    public class forceAx : nPropChanged
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
            graphPane.XAxis.MajorGrid.IsZeroLine = false;
            graphPane.YAxis.MajorGrid.IsZeroLine = false;
            graphPane.IsBoundedRanges = false;
        }

        private GraphPane _graphPane;

        public GraphPane graphPane
        {
            get { return _graphPane; }
            set { _graphPane = value; RaisePropertyChanged("graphPane"); }
        }
    }

    public class acclAx : nPropChanged
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
            graphPane.XAxis.MajorGrid.IsZeroLine = false;
            graphPane.YAxis.MajorGrid.IsZeroLine = false;
            graphPane.IsBoundedRanges = false;
        }

        private GraphPane _graphPane;

        public GraphPane graphPane
        {
            get { return _graphPane; }
            set { _graphPane = value; RaisePropertyChanged("graphPane"); }
        }
    }

    public class velosAx : nPropChanged
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
            graphPane.XAxis.MajorGrid.IsZeroLine = false;
            graphPane.YAxis.MajorGrid.IsZeroLine = false;
            graphPane.IsBoundedRanges = false;
        }

        private GraphPane _graphPane;

        public GraphPane graphPane
        {
            get { return _graphPane; }
            set { _graphPane = value; RaisePropertyChanged("graphPane"); }
        }
    }

    public class displAx : nPropChanged
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
            graphPane.XAxis.MajorGrid.IsZeroLine = false;
            graphPane.YAxis.MajorGrid.IsZeroLine = false;
            graphPane.IsBoundedRanges = false;
        }

        private GraphPane _graphPane;

        public GraphPane graphPane
        {
            get { return _graphPane; }
            set { _graphPane = value; RaisePropertyChanged("graphPane"); }
        }
    }

    public class coordAx : nPropChanged
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
            graphPane.XAxis.MajorGrid.IsZeroLine = false;
            graphPane.YAxis.MajorGrid.IsZeroLine = false;
            graphPane.IsBoundedRanges = false;
        }

        private GraphPane _graphPane;

        public GraphPane graphPane
        {
            get { return _graphPane; }
            set { _graphPane = value; RaisePropertyChanged("graphPane"); }
        }
    }
}