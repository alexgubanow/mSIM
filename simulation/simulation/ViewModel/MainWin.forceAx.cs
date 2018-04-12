using System.ComponentModel;

namespace simulation.ViewModel
{
    public class forceAx : INotifyPropertyChanged
    {
        public forceAx()
        {

        }

        private int _SelectedPlot;
        public int SelectedPlot { get => _SelectedPlot; set { _SelectedPlot = value; RaisePropertyChanged("SelectedPlot"); } }


        public event PropertyChangedEventHandler PropertyChanged;

        public void RaisePropertyChanged(string propertyName)
        {
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}