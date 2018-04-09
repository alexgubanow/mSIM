using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace simulation
{
    /// <summary>
    /// Interaction logic for numPowTen.xaml
    /// </summary>
    public partial class numPowTen : UserControl
    {
        public numPowTen()
        {
            InitializeComponent();
        }
        
        public string Clabel { get { return (string)GetValue(ClabelProperty); } set { SetValue(ClabelProperty, value); } }

        public static readonly DependencyProperty ClabelProperty = DependencyProperty.Register("Clabel", typeof(string), typeof(numPowTen), new UIPropertyMetadata(""));

        public int PowTen { get { return (int)GetValue(PowTenProperty); } set { SetValue(PowTenProperty, value); } }

        public static readonly DependencyProperty PowTenProperty = DependencyProperty.Register("PowTen", typeof(int), typeof(numPowTen), new UIPropertyMetadata(0));

        public int num { get { return (int)GetValue(numProperty); } set { SetValue(numProperty, value); } }

        public static readonly DependencyProperty numProperty = DependencyProperty.Register("num", typeof(int), typeof(numPowTen), new UIPropertyMetadata(0));
    }
}
