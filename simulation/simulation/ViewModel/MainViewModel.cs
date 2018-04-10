using calcLib;
using GalaSoft.MvvmLight;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using HelixToolkit.Wpf.SharpDX;
using Microsoft.Win32;
using System.Windows.Input;
using System.IO;
using System.ComponentModel;
using System.Windows;

namespace simulation.ViewModel
{
    /// <summary>
    /// This class contains properties that the main View can data bind to.
    /// <para>
    /// Use the <strong>mvvminpc</strong> snippet to add bindable properties to this ViewModel.
    /// </para>
    /// <para>
    /// You can also use Blend to data bind with the tool's support.
    /// </para>
    /// <para>
    /// See http://www.galasoft.ch/mvvm
    /// </para>
    /// </summary>
    public class MainViewModel : ViewModelBase
    {
        /// <summary>
        /// Initializes a new instance of the MainViewModel class.
        /// </summary>
        public MainViewModel()
        {
            ////if (IsInDesignMode)
            ////{
            ////    // Code runs in Blend --> create design time data.
            ////}
            ////else
            ////{
            ////    // Code runs "for real"
            ////}
            MainWin = new MainWin();
            ThrDmod = new ThrDmod();
        }

        public MainWin MainWin { get; set; }
        public ThrDmod ThrDmod { get; set; }
    }

    public class MainWin : INotifyPropertyChanged
    {
        public MainWin()
        {
            MaterialsVis = Visibility.Collapsed;
            IntegrSchems = new List<integr.Schems>() { integr.Schems.euler, integr.Schems.gear, integr.Schems.verlet };
            mModels = new List<models>() { models.linear, models.nonlinear, models.particles };
            Objs = new List<string>() { "blank", "metal", "chorda", "artChorda", "glassPart" };
        }

        private int _selectedRibbonTab;
        public int SelectedRibbonTab { get => _selectedRibbonTab; set { _selectedRibbonTab = value; RaisePropertyChanged("selectedRibbonTab"); } }

        private List<integr.Schems> _integrSchems;

        public List<integr.Schems> IntegrSchems { get => _integrSchems; set { _integrSchems = value; RaisePropertyChanged("IntegrSchems"); } }

        private List<models> _mModels;

        public List<models> mModels { get => _mModels; set { _mModels = value; RaisePropertyChanged("mModels"); } }

        private List<string> _Objs;

        public List<string> Objs { get => _Objs; set { _Objs = value; RaisePropertyChanged("Objs"); } }

        private Visibility _MaterialsVis;

        public Visibility MaterialsVis
        {
            get
            {
                return _MaterialsVis;
            }

            set
            {
                _MaterialsVis = value;
                RaisePropertyChanged("MaterialsVis");
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;

        public void RaisePropertyChanged(string propertyName)
        {
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
        }
    }

}