// -----------------------------------------------------------------------
//
// (c) Copyright 1997-2013, SensoMotoric Instruments GmbH
// 
// Permission  is  hereby granted,  free  of  charge,  to any  person  or
// organization  obtaining  a  copy  of  the  software  and  accompanying
// documentation  covered  by  this  license  (the  "Software")  to  use,
// reproduce,  display, distribute, execute,  and transmit  the Software,
// and  to  prepare derivative  works  of  the  Software, and  to  permit
// third-parties to whom the Software  is furnished to do so, all subject
// to the following:
// 
// The  copyright notices  in  the Software  and  this entire  statement,
// including the above license  grant, this restriction and the following
// disclaimer, must be  included in all copies of  the Software, in whole
// or  in part, and  all derivative  works of  the Software,  unless such
// copies   or   derivative   works   are   solely   in   the   form   of
// machine-executable  object   code  generated  by   a  source  language
// processor.
// 
// THE  SOFTWARE IS  PROVIDED  "AS  IS", WITHOUT  WARRANTY  OF ANY  KIND,
// EXPRESS OR  IMPLIED, INCLUDING  BUT NOT LIMITED  TO THE  WARRANTIES OF
// MERCHANTABILITY,   FITNESS  FOR  A   PARTICULAR  PURPOSE,   TITLE  AND
// NON-INFRINGEMENT. IN  NO EVENT SHALL  THE COPYRIGHT HOLDERS  OR ANYONE
// DISTRIBUTING  THE  SOFTWARE  BE   LIABLE  FOR  ANY  DAMAGES  OR  OTHER
// LIABILITY, WHETHER  IN CONTRACT, TORT OR OTHERWISE,  ARISING FROM, OUT
// OF OR IN CONNECTION WITH THE  SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// -----------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Threading;
using System.Runtime.Remoting.Messaging;
using System.IO;
using System.Drawing.Imaging;
using EyeTrackingController;
using System.Drawing.Drawing2D;

namespace csdemo
{
    public partial class SmiSample : Form
    {


        EyeTrackingController.EyeTrackingController ETDevice;
        EyeTrackingController.EyeTrackingController.CalibrationStruct m_CalibrationData;
        EyeTrackingController.EyeTrackingController.AccuracyStruct m_AccuracyData;


        // callback routine declaration
        private delegate void CalibrationCallback(EyeTrackingController.EyeTrackingController.CalibrationPointStruct calibrationPointData);
        private delegate void GetSampleCallback(EyeTrackingController.EyeTrackingController.SampleStruct sampleData);
        private delegate void GetEventCallback(EyeTrackingController.EyeTrackingController.EventStruct eventData);
        private delegate void GetEyeImageCallback(EyeTrackingController.EyeTrackingController.ImageStruct imageData);
        private delegate void GetSceneVideoCallback(EyeTrackingController.EyeTrackingController.ImageStruct imageData);
        private delegate void GetTrackingMonitorCallback(EyeTrackingController.EyeTrackingController.ImageStruct imageData);


        // callback function instances
        CalibrationCallback m_CalibrationCallback;
        GetSampleCallback m_SampleCallback;
        GetEventCallback m_EventCallback;
        GetEyeImageCallback m_EyeImageCallback;
        GetSceneVideoCallback m_SceneVideoCallback;
        GetTrackingMonitorCallback m_TrackingMonitorCallback;


        // delegates which will be used by invoking functions 
        public delegate void DisplayTrackingMonitor();
        public delegate void DisplayEyeImage();
        public delegate void DisplaySceneVideo();
        public delegate void DisplayLog1();
        public delegate void DisplayLog2();
        public delegate void DisplayLog3();


        #region InvokeFunctions

        // invoke functions to log output from different threads to GUI
        public void UpdateTrackingMonitor(Bitmap trackingMonitorBmp)
        {
            try
            {
                if (trackingmonitorpicture.InvokeRequired)
                {
                    trackingmonitorpicture.BeginInvoke((DisplayTrackingMonitor)delegate
                    {
                        var lastImg = trackingmonitorpicture.Image;
                            trackingmonitorpicture.Image = trackingMonitorBmp;
                        if(lastImg is IDisposable)
                        {
                            lastImg.Dispose();
                        }
                    });
                }
            }
            catch (System.Exception exc)
            {
                logger1.Text = "Exception: " + exc.Message;
            }
        }


        public void UpdateEyeImage(Bitmap eyeImageBmp)
        {
            try
            {
                if (eyepicture.InvokeRequired)
                {
                    // create gray scale color table
                    ColorPalette pal = eyeImageBmp.Palette;
                    for (int i = 0; i < 256; i++)
                    {
                        pal.Entries[i] = Color.FromArgb(i, i, i);
                    }
                    eyeImageBmp.Palette = pal;

                    eyepicture.BeginInvoke((DisplayEyeImage)delegate
                    {
                        var lastImg = eyepicture.Image;
                        eyepicture.Image = eyeImageBmp;
                        if (lastImg is IDisposable)
                        {
                            lastImg.Dispose();
                        }
                    });
                }
            }
            catch (System.Exception exc)
            {
                logger1.Text = "Exception: " + exc.Message;
            }
        }

        public void UpdateSceneVideo(Bitmap sceneVideoBmp)
        {
            try
            {
                if (scenepicture.InvokeRequired)
                {
                    scenepicture.BeginInvoke((DisplaySceneVideo)delegate
                    {
                        var lastImg = scenepicture.Image;
                        scenepicture.Image = sceneVideoBmp;
                        if (lastImg is IDisposable)
                        {
                            lastImg.Dispose();
                        }
                    });
                }
            }
            catch (System.Exception exc)
            {
                logger1.Text = "Exception: " + exc.Message;
            }

        }
        
        public void UpdateLog1(string dataLogger)
        {
            try
            {
                if (logger1.InvokeRequired)
                {
                    logger1.BeginInvoke((DisplayLog1)delegate
                    {
                        logger1.Text = dataLogger;
                    });
                }
            }
            catch (Exception exc)
            {
                logger1.Text = "Exception: " + exc.Message;
            }
        }

        public void UpdateLog2(string DataLog)
        {
            try
            {
                if (logger2.InvokeRequired)
                {
                    logger2.BeginInvoke((DisplayLog2)delegate
                    {
                        logger2.Text = DataLog;
                    });
                }
            }
            catch (System.Exception exc)
            {
                logger2.Text = "Exception: " + exc.Message;
            }
        }

        public void UpdateLog3(string dataLogger)
        {
            try
            {
                if (logger3.InvokeRequired)
                {
                    logger3.BeginInvoke((DisplayLog3)delegate
                    {
                        logger3.Text = dataLogger;
                    });
                }
            }
            catch (System.Exception exc)
            {
                logger3.Text = "Exception: " + exc.Message;
            }
        }

        #endregion

        #region CallbackFunctions

        void GetTrackingMonitorCallbackFunction(EyeTrackingController.EyeTrackingController.ImageStruct image)
        {
            // generate a new bitmap 
            var img = new Bitmap(image.imageWidth, image.imageHeight, PixelFormat.Format24bppRgb);
            try
            {
                var bufferLock = img.LockBits(new Rectangle(Point.Empty, img.Size), ImageLockMode.ReadWrite, img.PixelFormat);

                try
                {
                    // copy the image buffer 
                    EyeTrackingController.EyeTrackingController.CopyMemory(bufferLock.Scan0, image.imageBuffer, (uint)image.imageSize);
                }
                finally
                {
                    img.UnlockBits(bufferLock);
                }

                // update GUI 
                UpdateTrackingMonitor(img);
            }
            catch(Exception ex) 
            {
                img.Dispose();
            }
        }

        void GetEyeImageCallbackFunction(EyeTrackingController.EyeTrackingController.ImageStruct image)
        {
            // generate a new bitmap 
            var img = new Bitmap(image.imageWidth, image.imageHeight, PixelFormat.Format8bppIndexed);
            try
            {

                var bufferLock = img.LockBits(new Rectangle(Point.Empty, img.Size), ImageLockMode.ReadWrite, img.PixelFormat);
                // copy the image buffer 
                try
                {
                    EyeTrackingController.EyeTrackingController.CopyMemory(bufferLock.Scan0, image.imageBuffer, (uint)image.imageSize);
                }
                finally
                {
                    img.UnlockBits(bufferLock);
                }

                // update GUI 
                UpdateEyeImage(img);
            }
            catch (Exception ex)
            {
                // log...
                img.Dispose();
            }
        }

        void GetSceneVideoCallbackFunction(EyeTrackingController.EyeTrackingController.ImageStruct image)
        {
            // generate a new bitmap 
            var img = new Bitmap(image.imageWidth, image.imageHeight, PixelFormat.Format24bppRgb);
            try
            {
                var bufferLock = img.LockBits(new Rectangle(Point.Empty, img.Size), ImageLockMode.ReadWrite, img.PixelFormat);

                try
                {
                    // copy the image buffer 
                    EyeTrackingController.EyeTrackingController.CopyMemory(bufferLock.Scan0, image.imageBuffer, (uint)image.imageSize);
                }
                finally
                {
                    img.UnlockBits(bufferLock);
                }

                // update GUI 
                UpdateSceneVideo(img);
            }
            catch (Exception ex)
            {
                img.Dispose();
            }

        }
        
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

        void CalibrationCallbackFunction(EyeTrackingController.EyeTrackingController.CalibrationPointStruct calibrationPoint)
        {
            UpdateLog3("Data from CalibrationCallback - Number:" + calibrationPoint.number + " PosX:" + calibrationPoint.positionX + " PosY:" + calibrationPoint.positionY);
        }

        #endregion


        public SmiSample()
        {
            InitializeComponent();
        }

        private void SmiSample_Load(object sender, EventArgs e)
        {
            ETDevice = new EyeTrackingController.EyeTrackingController();

            m_CalibrationCallback = new CalibrationCallback(CalibrationCallbackFunction);
            m_SampleCallback = new GetSampleCallback(GetSampleCallbackFunction);
            m_EventCallback = new GetEventCallback(GetEventCallbackFunction);
            m_EyeImageCallback = new GetEyeImageCallback(GetEyeImageCallbackFunction);
            m_SceneVideoCallback = new GetSceneVideoCallback(GetSceneVideoCallbackFunction);
            m_TrackingMonitorCallback = new GetTrackingMonitorCallback(GetTrackingMonitorCallbackFunction);
        }

        private void SmiSample_FormClosing(object sender, FormClosingEventArgs e)
        {
            disconnecting();
        }


        private void disconnecting()
        {
            int ret = 0;

            try
            {
                ret = ETDevice.iV_Disconnect();
                if (ret == 1) logger.Text = "iV_Disconnect: disconnected successfully";
                if (ret != 1) logger.Text = "iV_Disconnect: failed to disconnect: " + ret;
            }
            catch (System.Exception exc)
            {
                logger.Text = "Exception during iV_Disconnect: " + exc.Message;
            }
        }

        private void key_Click(object sender, EventArgs e)
        {
            int ret = 0;

            try
            {
                // setting license 
                ETDevice.iV_SetLicense(new StringBuilder(licensekey.Text));
                if (ret == 1) logger.Text = "iV_SetLicense: license set successfully";
                if (ret != 1) logger.Text = "iV_SetLicense: failed to set license: " + ret;
            }
            catch (Exception exc)
            {
                logger1.Text = "Exception during iV_SetLicense: " + exc.Message;
            }
        }


        private void start_Click(object sender, EventArgs e)
        {
            int ret = 0;

            try
            {
                // start RED-m eyetracking-server 
                ret = ETDevice.iV_Start(1);
                if (ret == 1) logger.Text = "iV_Start: server started successfully";
                if (ret != 1) logger.Text = "iV_Start: failed to start server: " + ret;
            }
            catch (Exception exc)
            {
                logger1.Text = "Exception during iV_Start: " + exc.Message;
            }
        }

        private void quit_Click(object sender, EventArgs e)
        {
            int ret = 0;

            try
            {
                // shutdown eyetracking-server 
                ret = ETDevice.iV_Quit();
                if (ret == 1) logger.Text = "iV_Quit: server shut down";
                if (ret != 1) logger.Text = "iV_Quit: failed to shut down server: " + ret;
            }
            catch (Exception exc)
            {
                logger1.Text = "Exception during iV_Quit: " + exc.Message;
            }
        }

        private void connect_Click(object sender, EventArgs e)
        {
            int ret = 0;

            try
            {
                ETDevice.iV_SetLogger(Convert.ToInt32(loggerstatus.Text), new StringBuilder("iViewXSDK_cs_Demo.txt"));

                if (licensekey.Text != string.Empty)
                {
                    ETDevice.iV_SetLicense(new StringBuilder(licensekey.Text));
                }

                // set all callbacks 
                ETDevice.iV_SetCalibrationCallback(m_CalibrationCallback);
                ETDevice.iV_SetSampleCallback(m_SampleCallback);
                ETDevice.iV_SetEventCallback(m_EventCallback);
                ETDevice.iV_SetEyeImageCallback(m_EyeImageCallback);
                ETDevice.iV_SetSceneVideoCallback(m_SceneVideoCallback);
                ETDevice.iV_SetTrackingMonitorCallback(m_TrackingMonitorCallback);

                // connect to server 
                ret = ETDevice.iV_Connect(new StringBuilder(sendip.Text), Convert.ToInt32(sendport.Text), new StringBuilder(receiveip.Text), Convert.ToInt32(receiveport.Text));
                if (ret == 1) logger.Text = "iV_Connect: connection established";
                if (ret != 1) logger.Text = "iV_Connect: failed to establish connection: " + ret;
            }
            catch (Exception exc)
            {
                logger1.Text = "Exception during iV_Connect: " + exc.Message;
            }

        }

        private void disconnect_Click(object sender, EventArgs e)
        {
            disconnecting();
        }

        private void calibrate_Click(object sender, EventArgs e)
        {
            int ret = 0;
            int calibrationPoints = 5;
            int displayDevice = 0;
            int targetSize = 20;

            try
            {
                switch(displayDeviceComboBox.Text)
                {
                    default:
                    case "Primary Device":
                        displayDevice = 0;
                        break;
                    case "Secondary Device":
                        displayDevice = 1;
                        break;
                }

                switch (calibrationMethodComboBox.Text)
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
                m_CalibrationData.visualization = 1;
                m_CalibrationData.speed = 0;
                m_CalibrationData.targetShape = 2;
                m_CalibrationData.backgroundColor = 230;
                m_CalibrationData.foregroundColor = 250;
                m_CalibrationData.targetSize = targetSize;
                m_CalibrationData.targetFilename = "";

                ret = ETDevice.iV_SetupCalibration(ref m_CalibrationData);
                if (ret == 1) logger.Text = "iV_SetupCalibration: calibration set up successfully";
                if (ret != 1) logger.Text = "iV_SetupCalibration: failed to setup calibration: " + ret;

                if (ret != 1)
                    return;

                ret = ETDevice.iV_Calibrate();
                if (ret == 1) logger.Text = "iV_Calibrate: calibration finished successfully";
                if (ret != 1) logger.Text = "iV_Calibrate: failed to calibrate: " + ret;

            }
            catch (System.Exception exc)
            {
                logger.Text = "Calibration Exception: " + exc.Message;
            }

        }

        private void validate_Click(object sender, EventArgs e)
        {
            int ret = 0;

            try
            {
                ret = ETDevice.iV_Validate();
                if (ret == 1) logger.Text = "iV_Validate: validation finished successfully";
                if (ret != 1) logger.Text = "iV_Validate: failed to validate: " + ret;

            }
            catch (System.Exception exc)
            {
                logger.Text = "iV_Validate Exception: " + exc.Message;
            }
        }

        private void getcalibrationpoint_Click(object sender, EventArgs e)
        {
            int ret = 0;

            try
            {
                ret = ETDevice.iV_SaveCalibration(new StringBuilder(calibrationID.Text));
                if (ret == 1) logger.Text = "iV_SaveCalibration: calibration successfully saved";
                if (ret != 1) logger.Text = "iV_SaveCalibration: failed to save calibration: " + ret; 
            }
            catch (System.Exception exc)
            {
                logger.Text = "iV_SaveCalibration Exception: " + exc.Message;
            }
        }

        private void startrecording_Click(object sender, EventArgs e)
        {
            int ret = 0;

            try
            {
                ret = ETDevice.iV_StartRecording();
                if (ret == 1) logger.Text = "iV_StartRecording: recording started";
                if (ret != 1) logger.Text = "iV_StartRecording: failed to start recording: " + ret;
            }
            catch (System.Exception exc)
            {
                logger.Text = "iV_StartRecording Exception: " + exc.Message;
            }
        }

        private void stoprecording_Click(object sender, EventArgs e)
        {
            int ret = 0;

            try
            {
                ret = ETDevice.iV_StopRecording();
                if (ret == 1) logger.Text = "iV_StopRecording: recording stopped";
                if (ret != 1) logger.Text = "iV_StopRecording: failed to stop recording: " + ret;
            }
            catch (System.Exception exc)
            {
                logger.Text = "iV_StopRecording Exception: " + exc.Message;
            }
        }

        private void savedata_Click(object sender, EventArgs e)
        {
            int ret = 0;

            try
            {
                ret = ETDevice.iV_SaveData(new StringBuilder(filename.Text), new StringBuilder("Description"), new StringBuilder("User"), 1);
                if (ret == 1) logger.Text = "iV_SaveData: saved data successfully";
                if (ret != 1) logger.Text = "iV_SaveData: failed to save recorded data: " + ret;
            }
            catch (System.Exception exc)
            {
                logger.Text = "iV_SaveData Exception: " + exc.Message;
            } 
        }

        private void getaccuracy_Click(object sender, EventArgs e)
        {
            int ret = 0;

            try
            {
                ret = ETDevice.iV_GetAccuracy(ref m_AccuracyData, 1);
                if (ret == 1) accuracay.Text = "Dev X: " + m_AccuracyData.deviationXLeft + " Dev Y: " + m_AccuracyData.deviationYLeft;
                if (ret != 1) accuracay.Text = "iV_GetAccuracy: faile to get accuracy data: " + ret;
            }
            catch (System.Exception exc)
            {
                accuracay.Text = "iV_GetAccuracy Exception: " + exc.Message;
            }
        }

        private void trackingmonitor_Click(object sender, EventArgs e)
        {
            int ret = 0;

            try
            {
                ret = ETDevice.iV_ShowTrackingMonitor();
                if (ret == 1) logger.Text = "iV_ShowTrackingMonitor: shown tracking monitor successfully";
                if (ret != 1) logger.Text = "iV_ShowTrackingMonitor: failed to show tracking monitor: " + ret;
            }
            catch (System.Exception exc)
            {
                logger.Text = "iV_ShowTrackingMonitor Exception: " + exc.Message;
            }
        }

        private void eyevideo_Click(object sender, EventArgs e)
        {
            int ret = 0;
            try
            {
                ret = ETDevice.iV_ShowEyeImageMonitor();
                if (ret == 1) logger.Text = "iV_ShowEyeImageMonitor: shown eye image monitor successfully";
                if (ret != 1) logger.Text = "iV_ShowEyeImageMonitor: failed to show eye image monitor: " + ret;
            }
            catch (System.Exception exc)
            {
                logger.Text = "iV_ShowEyeImageMonitor Exception: " + exc.Message;
            }
        }

        private void scenevideo_Click(object sender, EventArgs e)
        {
            int ret = 0;
            try
            {
                ret = ETDevice.iV_ShowSceneVideoMonitor();
                if (ret == 1) logger.Text = "iV_ShowSceneVideoMonitor: shown scene video monitor successfully";
                if (ret != 1) logger.Text = "iV_ShowSceneVideoMonitor: failed to show scene video monitor: " + ret;
            }
            catch (System.Exception exc)
            {
                logger.Text = "iV_ShowSceneVideoMonitor Exception: " + exc.Message;
            }
        }

        private void loadcalibration_Click(object sender, EventArgs e)
        {
            int ret = 0;
            try
            {
                ret = ETDevice.iV_LoadCalibration(new StringBuilder(calibrationID.Text));
                if (ret == 1) logger.Text = "iV_LoadCalibration: loaded calibration successfully";
                if (ret != 1) logger.Text = "iV_LoadCalibration: failed to load calibration: " + ret;
            }
            catch (System.Exception exc)
            {
                logger.Text = "iV_LoadCalibration Exception: " + exc.Message;
            }
        }

    }
}
