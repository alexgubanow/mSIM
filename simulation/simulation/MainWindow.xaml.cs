using simulation.ViewModel;
using System.Windows;
using System.Windows.Controls;

namespace simulation
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow
    {
        public MainViewModel Vm { get { return (MainViewModel)DataContext; } }

        public MainWindow()
        {
            InitializeComponent();
            var Main = new MainViewModel();
            Main.ThrDmod.modelView = this.view;
            this.DataContext = Main;
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