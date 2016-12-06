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
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;
using System.Windows.Controls.Primitives;
using System.ComponentModel;
using System.Data;
using System.Runtime.InteropServices;
using System.Threading;
using System.Runtime.Remoting.Messaging;
using System.IO;
using EyeTrackingController;

namespace wpfdemo
{
    /// <summary>
    /// Interaction logic for SmiSample.xaml
    /// </summary>
    public partial class SmiSample : Window
    {
        public EyeTrackingController.EyeTrackingController ETDevice;
        public EyeTrackingController.EyeTrackingController.CalibrationStruct m_CalibrationData;
        public EyeTrackingController.EyeTrackingController.AccuracyStruct m_AccuracyData;
        public EyeTrackingController.EyeTrackingController.SampleStruct m_SampleData;
        public EyeTrackingController.EyeTrackingController.EventStruct m_EventData;
        
        
        // callback routine declaration
        public delegate void CalibrationCallback(EyeTrackingController.EyeTrackingController.CalibrationPointStruct calibrationPointData);
        public delegate void GetSampleCallback(EyeTrackingController.EyeTrackingController.SampleStruct sampleData);
        public delegate void GetEventCallback(EyeTrackingController.EyeTrackingController.EventStruct eventData);


        // callback function instances
        CalibrationCallback m_CalibrationCallback;
        GetSampleCallback m_SampleCallback;
        GetEventCallback m_EventCallback;


        // definition for calibration window 
        CalibrationSample m_CalibrationWindow;


        // delegates which will be used by invoking functions 
        public delegate void DisplayLog1();
        public delegate void DisplayLog2();
        public delegate void DisplayLog3();

        #region InvokeFunctions

        public void UpdateLog1(string dataLog)
        {
            try
            {
                Dispatcher.Invoke(System.Windows.Threading.DispatcherPriority.Normal, (DisplayLog1)
                delegate()
                {
                    logger1.Text = dataLog;
                });
            }
            catch (Exception exc)
            {
                logger1.Text = "Invoke Exception: " + exc.Message;
            }
        }

        public void UpdateLog2(string dataLog)
        {
            try
            {
                Dispatcher.Invoke(System.Windows.Threading.DispatcherPriority.Normal, (DisplayLog2)
                delegate()
                {
                    logger2.Text = dataLog;
                });
            }
            catch (Exception exc)
            {
                logger1.Text = "Invoke Exception: " + exc.Message;
            }
        }

        public void UpdateLog3(string dataLog)
        {
            try
            {
                Dispatcher.Invoke(System.Windows.Threading.DispatcherPriority.Normal, (DisplayLog3)
                delegate()
                {
                    logger3.Text = dataLog;
                });
            }
            catch (Exception exc)
            {
                logger1.Text = "Invoke Exception: " + exc.Message;
            }
        }

        #endregion

        #region CallbackFunctions

        // callback functions
        void GetSampleCallbackFunction(EyeTrackingController.EyeTrackingController.SampleStruct sampleData)
        {
            UpdateLog1("Data from SampleCallback - timestamp: " + sampleData.timestamp.ToString() +
                " - GazeRX: " + sampleData.rightEye.gazeX.ToString() +
                " - GazeRY: " + sampleData.rightEye.gazeY.ToString() +
                " - GazeLX: " + sampleData.leftEye.gazeX.ToString() +
                " - GazeLY: " + sampleData.leftEye.gazeY.ToString() +
                " - DiamRX: " + sampleData.rightEye.diam.ToString() +
                " - DiamLX: " + sampleData.leftEye.diam.ToString() +
                " - DistanceR: " + sampleData.rightEye.eyePositionZ.ToString() +
                " - DistanceL: " + sampleData.leftEye.eyePositionZ.ToString());
            
        }


        void GetEventCallbackFunction(EyeTrackingController.EyeTrackingController.EventStruct eventData)
        {
            UpdateLog2("Data from EventCallback - eye: " + eventData.eye.ToString() +
                " Event: " + eventData.eventType + " startTime: " + eventData.startTime.ToString() +
                " End:" + eventData.endTime.ToString() + " duration:" + eventData.duration.ToString() +
                " PosX:" + eventData.positionX.ToString() + " PosY:" + eventData.positionY.ToString());
        }

        void CalibrationCallbackFunction(EyeTrackingController.EyeTrackingController.CalibrationPointStruct calibrationPointData)
        {
            m_CalibrationWindow.ShowPoint(calibrationPointData);
            UpdateLog3("Data from CalibrationCallback - Number:" + calibrationPointData.number + " PosX:" + calibrationPointData.positionX + " PosY:" + calibrationPointData.positionY);
        }

        #endregion


        // init main window
        public SmiSample()
        {
            InitializeComponent();
        }
        
        private void Window_Initialized(object sender, EventArgs e)
        {
            try
            {
                ETDevice = new EyeTrackingController.EyeTrackingController();
                m_CalibrationWindow = new CalibrationSample();

                m_CalibrationCallback = new CalibrationCallback(CalibrationCallbackFunction);
                m_SampleCallback = new GetSampleCallback(GetSampleCallbackFunction);
                m_EventCallback = new GetEventCallback(GetEventCallbackFunction);
            }
            catch (System.Exception exc)
            {
                logger4.Text = "Exception: " + exc.Message;
            }

        }

        private void Window_Closed(object sender, EventArgs e)
        {
            disconnecting();

        }


        private void disconnecting()
        {
            int ret = 0;

            try
            {
                if (m_CalibrationWindow != null)
                    m_CalibrationWindow.Close();
                ret = ETDevice.iV_Disconnect();
                if (ret == 1) logger4.Text = "iV_Disconnect: successfully";
                if (ret != 1) logger4.Text = "iV_Disconnect failed: " + ret;
            }
            catch (System.Exception exc)
            {
                logger4.Text = "Exception during iV_Disconnect: " + exc.Message;
            }

        }

        // button event handling 
        private void Connect_Click(object sender, RoutedEventArgs e)
        {
            int ret = 0;

            try
            {
                if (licensekey.Text != string.Empty)
                {
                    ETDevice.iV_SetLicense(new StringBuilder(licensekey.Text));
                }
                ETDevice.iV_SetLogger(Convert.ToInt32(loglevel.Text), new StringBuilder("iViewXAPI_wpf_Demo.txt"));

                
                ETDevice.iV_SetCalibrationCallback(m_CalibrationCallback);
                ETDevice.iV_SetSampleCallback(m_SampleCallback);
                ETDevice.iV_SetEventCallback(m_EventCallback);

                ret = ETDevice.iV_Connect(new StringBuilder(sendip.Text), Convert.ToInt32(sendport.Text), new StringBuilder(receiveip.Text), Convert.ToInt32(receiveport.Text));
                if (ret == 1) logger4.Text = "iV_Connect: connection established";
                if (ret != 1) logger4.Text = "iV_Connect failed: " + ret;
            }
            catch (Exception exc)
            {
                logger1.Text = "Exception during iV_Connect: " + exc.Message;
            }

        }


        private void Disconnect_Click(object sender, RoutedEventArgs e)
        {
            int ret = 0;

            try
            {
                disconnecting();
            }
            catch (System.Exception exc)
            {
                logger1.Text = "Exception during iV_Disconnect: " + exc.Message;

            }
        }
        
        private void Calibrate_Click(object sender, RoutedEventArgs e)
        {
            int ret = 0;
            int targetSize = 20;
            int calibrationPoints = 5;
            int displayDevice = 0;

            try
            {
                switch (comboBox2.Text)
                {
                    default:
                    case "Primary Device":
                        displayDevice = 0;
                        break;
                    case "Secondary Device":
                        displayDevice = 1;
                        break;
                } 
                switch (comboBox1.Text)
                {
                    case "0P Calibration":
                        calibrationPoints = 0;
                        break;
                    case "1P Calibration":
                        calibrationPoints = 1;
                        break;
                    case "2P Calibration":
                        calibrationPoints = 2;
                        break;
                    default:
                    case "5P Calibration":
                        calibrationPoints = 5;
                        break;
                    case "8P Calibration":
                        calibrationPoints = 8;
                        break;
                    case "9P Calibration":
                        calibrationPoints = 9;
                        break;
                    case "13P Calibration":
                        calibrationPoints = 13;
                        break;
                }

                m_CalibrationData.displayDevice = displayDevice;
                m_CalibrationData.autoAccept = 1;
                m_CalibrationData.method = calibrationPoints;
                m_CalibrationData.visualization = 0;
                m_CalibrationData.speed = 0;
                m_CalibrationData.targetShape = 1;
                m_CalibrationData.backgroundColor = 220;
                m_CalibrationData.foregroundColor = 250;
                m_CalibrationData.targetSize = targetSize;
                m_CalibrationData.targetFilename = "";

                ret = ETDevice.iV_SetupCalibration(ref m_CalibrationData);
                if (ret == 1) logger4.Text = "iV_SetupCalibration: successfully";
                if (ret != 1) logger4.Text = "iV_SetupCalibration failed: " + ret;

                ret = ETDevice.iV_Calibrate();
                if (ret == 1) logger4.Text = "iV_Calibrate: calibration started successfully";
                if (ret != 1) logger4.Text = "iV_Calibrate failed: " + ret;


                if (ret == 1)
                {
                    // own validation visualization, with callbacks
                    m_CalibrationWindow.WindowStyle = WindowStyle.None;

                    switch (comboBox2.Text)
                    {
                        default:
                        case "Primary Device":
                            // calibrate on primary window
                            m_CalibrationWindow.Left = 0;
                            m_CalibrationWindow.Top = 0;
                            m_CalibrationWindow.Width = System.Windows.SystemParameters.PrimaryScreenWidth;
                            m_CalibrationWindow.Height = System.Windows.SystemParameters.PrimaryScreenHeight;
                            break;

                        case "Secondary Device":
                            // calibrate on secondary window
                            // change the following settings to your setup and resolution
                            m_CalibrationWindow.Left = System.Windows.SystemParameters.PrimaryScreenWidth;
                            m_CalibrationWindow.Top = 0;
                            m_CalibrationWindow.Width = 1680;
                            m_CalibrationWindow.Height = 1050;                          
                            break;
                        
                    }

                    m_CalibrationWindow.ShowDialog();
                }


            }
            catch (System.Exception exc)
            {
                logger3.Text = "Calibration Exception: " + exc.Message;
            }

        }

        private void Validate_Click(object sender, RoutedEventArgs e)
        {
            int ret = 0;

            try
            {
                ret = ETDevice.iV_Validate();
                if (ret == 1) logger4.Text = "iV_Validate: calibration started successfully";
                if (ret != 1) logger4.Text = "iV_Validate failed: " + ret;

                if (ret == 1)
                {

                    // own validation visualization, with callbacks
                    m_CalibrationWindow.WindowStyle = WindowStyle.None;

                    switch (comboBox2.Text)
                    {
                        default:
                        case "Primary Device":
                            // validate on primary window
                            m_CalibrationWindow.Left = 0;
                            m_CalibrationWindow.Top = 0;
                            m_CalibrationWindow.Width = System.Windows.SystemParameters.PrimaryScreenWidth;
                            m_CalibrationWindow.Height = System.Windows.SystemParameters.PrimaryScreenHeight;
                            break;

                        case "Secondary Device":
                            // validate on secondary window
                            // change the following settings to your setup and resolution
                            m_CalibrationWindow.Left = System.Windows.SystemParameters.PrimaryScreenWidth;
                            m_CalibrationWindow.Top = 0;
                            m_CalibrationWindow.Width = 1680;
                            m_CalibrationWindow.Height = 1050;
                            break;

                    }

                    m_CalibrationWindow.ShowDialog();
                }
            }
            catch (System.Exception exc)
            {
                logger3.Text = "Validation Exception: " + exc.Message;
            }

        }

        private void GetAccuracy_Click(object sender, RoutedEventArgs e)
        {
            int ret = 0;

            try
            {
                ret = ETDevice.iV_GetAccuracy(ref m_AccuracyData, 1);
                if (ret == 1) deviation.Text = "Dev X: " + m_AccuracyData.deviationXLeft + " Dev Y: " + m_AccuracyData.deviationYLeft;
                if (ret != 1) deviation.Text = "iV_GetAccuracy failed: " + ret;
            }
            catch (System.Exception exc)
            {
                deviation.Text = "iV_GetAccuracy Exception: " + exc.Message;
            }
        }
         
        private void EyeMonitor_Click(object sender, RoutedEventArgs e)
        {
            int ret = 0;

            try
            {
                ret = ETDevice.iV_ShowEyeImageMonitor();
                if (ret == 1) logger4.Text = "iV_ShowEyeImageMonitor: successfully";
                if (ret != 1) logger4.Text = "iV_ShowEyeImageMonitor failed: " + ret;
            }
            catch (System.Exception exc)
            {
                logger4.Text = "iV_ShowEyeImageMonitor Exception: " + exc.Message;
            }
        }

        private void TrackingMonitor_Click(object sender, RoutedEventArgs e)
        {
            int ret = 0;

            try
            {
                ret = ETDevice.iV_ShowTrackingMonitor();
                if (ret == 1) logger4.Text = "iV_ShowTrackingMonitor: successfully";
                if (ret != 1) logger4.Text = "iV_ShowTrackingMonitor failed: " + ret;
            }
            catch (System.Exception exc)
            {
                logger4.Text = "iV_ShowTrackingMonitor Exception: " + exc.Message;
            }
        }

        private void StartRecording_Click(object sender, RoutedEventArgs e)
        {
            int ret = 0;

            try
            {
                ret = ETDevice.iV_StartRecording();
                if (ret == 1) logger4.Text = "iV_StartRecording: successfully";
                if (ret != 1) logger4.Text = "iV_StartRecording failed: " + ret;
            }
            catch (System.Exception exc)
            {
                logger4.Text = "iV_StartRecording Exception: " + exc.Message;
            }
        }

        private void StopRecording_Click(object sender, RoutedEventArgs e)
        {
            int ret = 0;

            try
            {
                ret = ETDevice.iV_StopRecording();
                if (ret == 1) logger4.Text = "iV_StopRecording: successfully";
                if (ret != 1) logger4.Text = "iV_StopRecording failed: " + ret;
            }
            catch (System.Exception exc)
            {
                logger4.Text = "iV_StopRecording Exception: " + exc.Message;
            }
        }

        private void SaveData_Click(object sender, RoutedEventArgs e)
        {
            int ret = 0;

            try
            {
                ret = ETDevice.iV_SaveData(new StringBuilder(filename.Text), new StringBuilder("Description"), new StringBuilder("User"), 1);
                if (ret == 1) logger4.Text = "iV_SaveData: successfully";
                if (ret != 1) logger4.Text = "iV_SaveData failed: " + ret;
            }
            catch (System.Exception exc)
            {
                logger4.Text = "iV_SaveData Exception: " + exc.Message;
            } 
        }


        private void scenevideobutton_Click(object sender, RoutedEventArgs e)
        {
            int ret = 0;

            try
            {
                ret = ETDevice.iV_ShowSceneVideoMonitor();
                if (ret == 1) logger4.Text = "iV_ShowSceneVideoMonitor: successfully";
                if (ret != 1) logger4.Text = "iV_ShowSceneVideoMonitor failed: " + ret;
            }
            catch (System.Exception exc)
            {
                logger1.Text = "iV_ShowSceneVideoMonitor Exception: " + exc.Message;
            }
        }

    }
}
