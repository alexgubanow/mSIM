using calcLib;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Windows;

namespace simulation.ViewModel
{
    public partial class MainWin : INotifyPropertyChanged
    {
        public MainWin()
        {
            MaterialsVis = Visibility.Collapsed;
            IntegrSchems = new List<integr.Schems>() { integr.Schems.euler, integr.Schems.gear, integr.Schems.verlet };
            mModels = new List<models>() { models.linear, models.nonlinear, models.particles };
            forceAx = new forceAx();
            acclAx = new acclAx();
            velosAx = new velosAx();
            displAx = new displAx();
            coordAx = new coordAx();
        }

        public forceAx forceAx { get; set; }
        public acclAx acclAx { get; set; }
        public velosAx velosAx { get; set; }
        public displAx displAx { get; set; }
        public coordAx coordAx { get; set; }

        private int _SelectedPlot;
        public int SelectedPlot { get => _SelectedPlot; set { _SelectedPlot = value; RaisePropertyChanged("SelectedPlot"); } }

        private Material _SelectedMater;
        public Material SelectedMater { get => _SelectedMater; set { _SelectedMater = value; RaisePropertyChanged("SelectedMater"); } }

        private int _selectedRibbonTab;
        public int SelectedRibbonTab { get => _selectedRibbonTab; set { _selectedRibbonTab = value; RaisePropertyChanged("selectedRibbonTab"); } }

        private List<integr.Schems> _integrSchems;

        public List<integr.Schems> IntegrSchems { get => _integrSchems; set { _integrSchems = value; RaisePropertyChanged("IntegrSchems"); } }

        private List<models> _mModels;

        public List<models> mModels { get => _mModels; set { _mModels = value; RaisePropertyChanged("mModels"); } }

        private ObservableCollection<Material> _maters;

        public ObservableCollection<Material> maters { get => _maters; set { _maters = value; RaisePropertyChanged("maters"); }  }

        private Visibility _MaterialsVis;

        public Visibility MaterialsVis { get { return _MaterialsVis; } set { _MaterialsVis = value; RaisePropertyChanged("MaterialsVis"); } }

        public event PropertyChangedEventHandler PropertyChanged;

        public void RaisePropertyChanged(string propertyName)
        {
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}