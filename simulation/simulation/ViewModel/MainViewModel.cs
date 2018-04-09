using GalaSoft.MvvmLight;
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
        }

        public MainWin MainWin { get; set; }
    }

    public class MainWin : INotifyPropertyChanged
    {
        public MainWin()
        {
            MaterialsVis = Visibility.Collapsed;
        }


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