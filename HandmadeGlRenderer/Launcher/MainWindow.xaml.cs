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
using System.Diagnostics;
using System.ComponentModel;

namespace Launcher
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            Process.Start("E:/handmade/build/win32_startfile.exe");
            
        }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            Process.Start("E:/HandmadeXEngine/HandmadeGlRenderer/bin/Debug_x64/HandmadeGlRenderer.exe");
        }

        private void Button_Click_2(object sender, RoutedEventArgs e)
        {
            //Process.Start();
        }
    }
}
