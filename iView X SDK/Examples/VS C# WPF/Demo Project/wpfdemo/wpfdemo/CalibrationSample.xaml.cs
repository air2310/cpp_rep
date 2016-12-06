using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using EyeTrackingController;

namespace wpfdemo
{
    /// <summary>
    /// Interaction logic for Window2.xaml
    /// </summary>
    public partial class CalibrationSample : Window
    {
        EyeTrackingController.EyeTrackingController ETDevice;

        public CalibrationSample()
        {
            InitializeComponent();
        }


        // key down event handling 
        private void Window_KeyDown(object sender, KeyEventArgs e)
        {
            try
            {
                // accept calibration point
                if (e.Key == Key.Space)
                {
                    ETDevice.iV_AcceptCalibrationPoint();
                }

                // end calibration / validation
                if (e.Key == Key.Escape)
                {
                    ETDevice.iV_AbortCalibration();
                    Hide();
                }

            }
            catch (System.Exception exc)
            {

            }

        }

        // show current calibration / validation point
        // this function will be called from calibration callback in main window
        public delegate void DisplayPoint();
        public void ShowPoint(EyeTrackingController.EyeTrackingController.CalibrationPointStruct calibrationPointData)
        {
            Ellipse calibrationTarget;
            double targetSize = 20;
            double targetThickness = 6;

            // due to call from different threads, the visualization needs to be invoked 
            Dispatcher.Invoke(System.Windows.Threading.DispatcherPriority.Normal, (DisplayPoint)
            delegate()
            {

                // if calibration / validation point is valid
                if (calibrationPointData.number > 0)
                {

                    calibrationTarget = new Ellipse();
                    calibrationTarget.Fill = Brushes.Red;
                    calibrationTarget.Stroke = Brushes.White;
                    calibrationTarget.StrokeThickness = targetThickness;
                    calibrationTarget.Width = targetSize;
                    calibrationTarget.Height = targetSize;

                    calCanvas.Arrange(new Rect(calibrationPointData.positionX - targetSize, calibrationPointData.positionY - targetSize, targetSize, targetSize));
                    calCanvas.Children.Add(calibrationTarget);
                   
                }
                else
                {
                    // if calibration / validation has ended
                    Hide();
                }
            });
        }

        private void Window_Initialized(object sender, EventArgs e)
        {

        }

        private void Window_Activated(object sender, EventArgs e)
        {
            ETDevice = new EyeTrackingController.EyeTrackingController();

        }
    }
}
