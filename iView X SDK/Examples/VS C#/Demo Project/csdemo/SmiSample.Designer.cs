namespace csdemo
{
    partial class SmiSample
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.logger1 = new System.Windows.Forms.TextBox();
            this.logger2 = new System.Windows.Forms.TextBox();
            this.logger3 = new System.Windows.Forms.TextBox();
            this.connect = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.key = new System.Windows.Forms.Button();
            this.quit = new System.Windows.Forms.Button();
            this.start = new System.Windows.Forms.Button();
            this.license = new System.Windows.Forms.Label();
            this.licensekey = new System.Windows.Forms.TextBox();
            this.loggerstatus = new System.Windows.Forms.TextBox();
            this.disconnect = new System.Windows.Forms.Button();
            this.loggerlevel = new System.Windows.Forms.Label();
            this.receiveport = new System.Windows.Forms.TextBox();
            this.sendport = new System.Windows.Forms.TextBox();
            this.receiveip = new System.Windows.Forms.TextBox();
            this.sendip = new System.Windows.Forms.TextBox();
            this.send = new System.Windows.Forms.Label();
            this.receive = new System.Windows.Forms.Label();
            this.calibrate = new System.Windows.Forms.Button();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.loadcalibration = new System.Windows.Forms.Button();
            this.displayDeviceComboBox = new System.Windows.Forms.ComboBox();
            this.accuracay = new System.Windows.Forms.TextBox();
            this.getaccuracy = new System.Windows.Forms.Button();
            this.calibrationID = new System.Windows.Forms.TextBox();
            this.savecalibration = new System.Windows.Forms.Button();
            this.validate = new System.Windows.Forms.Button();
            this.calibrationMethodComboBox = new System.Windows.Forms.ComboBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.filename = new System.Windows.Forms.TextBox();
            this.savedata = new System.Windows.Forms.Button();
            this.stoprecording = new System.Windows.Forms.Button();
            this.startrecording = new System.Windows.Forms.Button();
            this.groupBox5 = new System.Windows.Forms.GroupBox();
            this.eyepicture = new System.Windows.Forms.PictureBox();
            this.trackingmonitorpicture = new System.Windows.Forms.PictureBox();
            this.scenepicture = new System.Windows.Forms.PictureBox();
            this.scenevideo = new System.Windows.Forms.Button();
            this.eyevideo = new System.Windows.Forms.Button();
            this.trackingmonitor = new System.Windows.Forms.Button();
            this.logger = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox5.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.eyepicture)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackingmonitorpicture)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.scenepicture)).BeginInit();
            this.groupBox4.SuspendLayout();
            this.SuspendLayout();
            // 
            // logger1
            // 
            this.logger1.Location = new System.Drawing.Point(135, 475);
            this.logger1.Name = "logger1";
            this.logger1.Size = new System.Drawing.Size(539, 20);
            this.logger1.TabIndex = 0;
            // 
            // logger2
            // 
            this.logger2.Location = new System.Drawing.Point(135, 501);
            this.logger2.Name = "logger2";
            this.logger2.Size = new System.Drawing.Size(539, 20);
            this.logger2.TabIndex = 1;
            // 
            // logger3
            // 
            this.logger3.Location = new System.Drawing.Point(135, 527);
            this.logger3.Name = "logger3";
            this.logger3.Size = new System.Drawing.Size(539, 20);
            this.logger3.TabIndex = 2;
            // 
            // connect
            // 
            this.connect.Location = new System.Drawing.Point(36, 157);
            this.connect.Name = "connect";
            this.connect.Size = new System.Drawing.Size(117, 26);
            this.connect.TabIndex = 6;
            this.connect.Text = "Connect";
            this.connect.UseVisualStyleBackColor = true;
            this.connect.Click += new System.EventHandler(this.connect_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.key);
            this.groupBox1.Controls.Add(this.quit);
            this.groupBox1.Controls.Add(this.start);
            this.groupBox1.Controls.Add(this.license);
            this.groupBox1.Controls.Add(this.licensekey);
            this.groupBox1.Controls.Add(this.loggerstatus);
            this.groupBox1.Controls.Add(this.disconnect);
            this.groupBox1.Controls.Add(this.loggerlevel);
            this.groupBox1.Controls.Add(this.receiveport);
            this.groupBox1.Controls.Add(this.sendport);
            this.groupBox1.Controls.Add(this.receiveip);
            this.groupBox1.Controls.Add(this.sendip);
            this.groupBox1.Controls.Add(this.send);
            this.groupBox1.Controls.Add(this.receive);
            this.groupBox1.Controls.Add(this.connect);
            this.groupBox1.Location = new System.Drawing.Point(12, 19);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(340, 212);
            this.groupBox1.TabIndex = 4;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Connect to iViewX";
            // 
            // key
            // 
            this.key.Location = new System.Drawing.Point(196, 93);
            this.key.Name = "key";
            this.key.Size = new System.Drawing.Size(120, 26);
            this.key.TabIndex = 16;
            this.key.Text = "Set License Key";
            this.key.UseVisualStyleBackColor = true;
            this.key.Click += new System.EventHandler(this.key_Click);
            // 
            // quit
            // 
            this.quit.Location = new System.Drawing.Point(196, 125);
            this.quit.Name = "quit";
            this.quit.Size = new System.Drawing.Size(120, 26);
            this.quit.TabIndex = 15;
            this.quit.Text = "Quit Server";
            this.quit.UseVisualStyleBackColor = true;
            this.quit.Click += new System.EventHandler(this.quit_Click);
            // 
            // start
            // 
            this.start.Location = new System.Drawing.Point(36, 125);
            this.start.Name = "start";
            this.start.Size = new System.Drawing.Size(117, 26);
            this.start.TabIndex = 14;
            this.start.Text = "Start Server";
            this.start.UseVisualStyleBackColor = true;
            this.start.Click += new System.EventHandler(this.start_Click);
            // 
            // license
            // 
            this.license.AutoSize = true;
            this.license.Location = new System.Drawing.Point(33, 100);
            this.license.Name = "license";
            this.license.Size = new System.Drawing.Size(65, 13);
            this.license.TabIndex = 13;
            this.license.Text = "License Key";
            // 
            // licensekey
            // 
            this.licensekey.Location = new System.Drawing.Point(123, 97);
            this.licensekey.Name = "licensekey";
            this.licensekey.Size = new System.Drawing.Size(67, 20);
            this.licensekey.TabIndex = 12;
            // 
            // loggerstatus
            // 
            this.loggerstatus.Location = new System.Drawing.Point(123, 71);
            this.loggerstatus.Name = "loggerstatus";
            this.loggerstatus.Size = new System.Drawing.Size(30, 20);
            this.loggerstatus.TabIndex = 5;
            this.loggerstatus.Text = "1";
            // 
            // disconnect
            // 
            this.disconnect.Location = new System.Drawing.Point(196, 157);
            this.disconnect.Name = "disconnect";
            this.disconnect.Size = new System.Drawing.Size(120, 26);
            this.disconnect.TabIndex = 7;
            this.disconnect.Text = "Disconnect";
            this.disconnect.UseVisualStyleBackColor = true;
            this.disconnect.Click += new System.EventHandler(this.disconnect_Click);
            // 
            // loggerlevel
            // 
            this.loggerlevel.AutoSize = true;
            this.loggerlevel.Location = new System.Drawing.Point(33, 74);
            this.loggerlevel.Name = "loggerlevel";
            this.loggerlevel.Size = new System.Drawing.Size(47, 13);
            this.loggerlevel.TabIndex = 11;
            this.loggerlevel.Text = "Loglevel";
            // 
            // receiveport
            // 
            this.receiveport.Location = new System.Drawing.Point(249, 19);
            this.receiveport.Name = "receiveport";
            this.receiveport.Size = new System.Drawing.Size(67, 20);
            this.receiveport.TabIndex = 2;
            this.receiveport.Text = "5555";
            // 
            // sendport
            // 
            this.sendport.Location = new System.Drawing.Point(249, 45);
            this.sendport.Name = "sendport";
            this.sendport.Size = new System.Drawing.Size(67, 20);
            this.sendport.TabIndex = 4;
            this.sendport.Text = "4444";
            // 
            // receiveip
            // 
            this.receiveip.Location = new System.Drawing.Point(123, 19);
            this.receiveip.Name = "receiveip";
            this.receiveip.Size = new System.Drawing.Size(120, 20);
            this.receiveip.TabIndex = 1;
            this.receiveip.Text = "127.0.0.1";
            // 
            // sendip
            // 
            this.sendip.Location = new System.Drawing.Point(123, 45);
            this.sendip.Name = "sendip";
            this.sendip.Size = new System.Drawing.Size(120, 20);
            this.sendip.TabIndex = 3;
            this.sendip.Text = "127.0.0.1";
            // 
            // send
            // 
            this.send.AutoSize = true;
            this.send.Location = new System.Drawing.Point(33, 48);
            this.send.Name = "send";
            this.send.Size = new System.Drawing.Size(44, 13);
            this.send.TabIndex = 5;
            this.send.Text = "Send to";
            // 
            // receive
            // 
            this.receive.AutoSize = true;
            this.receive.Location = new System.Drawing.Point(33, 22);
            this.receive.Name = "receive";
            this.receive.Size = new System.Drawing.Size(70, 13);
            this.receive.TabIndex = 4;
            this.receive.Text = "Receive from";
            // 
            // calibrate
            // 
            this.calibrate.Location = new System.Drawing.Point(196, 19);
            this.calibrate.Name = "calibrate";
            this.calibrate.Size = new System.Drawing.Size(120, 26);
            this.calibrate.TabIndex = 9;
            this.calibrate.Text = "Calibrate";
            this.calibrate.UseVisualStyleBackColor = true;
            this.calibrate.Click += new System.EventHandler(this.calibrate_Click);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.loadcalibration);
            this.groupBox2.Controls.Add(this.displayDeviceComboBox);
            this.groupBox2.Controls.Add(this.accuracay);
            this.groupBox2.Controls.Add(this.getaccuracy);
            this.groupBox2.Controls.Add(this.calibrationID);
            this.groupBox2.Controls.Add(this.savecalibration);
            this.groupBox2.Controls.Add(this.validate);
            this.groupBox2.Controls.Add(this.calibrationMethodComboBox);
            this.groupBox2.Controls.Add(this.calibrate);
            this.groupBox2.Location = new System.Drawing.Point(12, 237);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(340, 187);
            this.groupBox2.TabIndex = 6;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Calibrate Options";
            // 
            // loadcalibration
            // 
            this.loadcalibration.Location = new System.Drawing.Point(196, 116);
            this.loadcalibration.Name = "loadcalibration";
            this.loadcalibration.Size = new System.Drawing.Size(120, 26);
            this.loadcalibration.TabIndex = 14;
            this.loadcalibration.Text = "Load Calibration";
            this.loadcalibration.UseVisualStyleBackColor = true;
            this.loadcalibration.Click += new System.EventHandler(this.loadcalibration_Click);
            // 
            // displayDeviceComboBox
            // 
            this.displayDeviceComboBox.FormattingEnabled = true;
            this.displayDeviceComboBox.Items.AddRange(new object[] {
            "Primary Device",
            "Secondary Device"});
            this.displayDeviceComboBox.Location = new System.Drawing.Point(36, 55);
            this.displayDeviceComboBox.Name = "displayDeviceComboBox";
            this.displayDeviceComboBox.Size = new System.Drawing.Size(117, 21);
            this.displayDeviceComboBox.TabIndex = 13;
            this.displayDeviceComboBox.Text = "Primary Device";
            // 
            // accuracay
            // 
            this.accuracay.Location = new System.Drawing.Point(36, 152);
            this.accuracay.Name = "accuracay";
            this.accuracay.Size = new System.Drawing.Size(154, 20);
            this.accuracay.TabIndex = 11;
            // 
            // getaccuracy
            // 
            this.getaccuracy.Location = new System.Drawing.Point(196, 148);
            this.getaccuracy.Name = "getaccuracy";
            this.getaccuracy.Size = new System.Drawing.Size(120, 26);
            this.getaccuracy.TabIndex = 12;
            this.getaccuracy.Text = "Get Accuracy";
            this.getaccuracy.UseVisualStyleBackColor = true;
            this.getaccuracy.Click += new System.EventHandler(this.getaccuracy_Click);
            // 
            // calibrationID
            // 
            this.calibrationID.Location = new System.Drawing.Point(36, 88);
            this.calibrationID.Name = "calibrationID";
            this.calibrationID.Size = new System.Drawing.Size(154, 20);
            this.calibrationID.TabIndex = 9;
            // 
            // savecalibration
            // 
            this.savecalibration.Location = new System.Drawing.Point(196, 84);
            this.savecalibration.Name = "savecalibration";
            this.savecalibration.Size = new System.Drawing.Size(120, 26);
            this.savecalibration.TabIndex = 11;
            this.savecalibration.Text = "Save Calibration";
            this.savecalibration.UseVisualStyleBackColor = true;
            this.savecalibration.Click += new System.EventHandler(this.getcalibrationpoint_Click);
            // 
            // validate
            // 
            this.validate.Location = new System.Drawing.Point(196, 51);
            this.validate.Name = "validate";
            this.validate.Size = new System.Drawing.Size(120, 27);
            this.validate.TabIndex = 10;
            this.validate.Text = "Validate";
            this.validate.UseVisualStyleBackColor = true;
            this.validate.Click += new System.EventHandler(this.validate_Click);
            // 
            // calibrationMethodComboBox
            // 
            this.calibrationMethodComboBox.FormattingEnabled = true;
            this.calibrationMethodComboBox.Items.AddRange(new object[] {
            "0P Calibration",
            "1P Calibration",
            "2P Calibration",
            "5P Calibration",
            "8P Calibration",
            "9P Calibration",
            "13P Calibration"});
            this.calibrationMethodComboBox.Location = new System.Drawing.Point(36, 23);
            this.calibrationMethodComboBox.Name = "calibrationMethodComboBox";
            this.calibrationMethodComboBox.Size = new System.Drawing.Size(117, 21);
            this.calibrationMethodComboBox.TabIndex = 8;
            this.calibrationMethodComboBox.Text = "5P Calibration";
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.filename);
            this.groupBox3.Controls.Add(this.savedata);
            this.groupBox3.Controls.Add(this.stoprecording);
            this.groupBox3.Controls.Add(this.startrecording);
            this.groupBox3.Location = new System.Drawing.Point(358, 292);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(340, 132);
            this.groupBox3.TabIndex = 7;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Offline Data Recording";
            // 
            // filename
            // 
            this.filename.Location = new System.Drawing.Point(30, 87);
            this.filename.Name = "filename";
            this.filename.Size = new System.Drawing.Size(160, 20);
            this.filename.TabIndex = 17;
            this.filename.Text = "iViewData001";
            // 
            // savedata
            // 
            this.savedata.Location = new System.Drawing.Point(196, 83);
            this.savedata.Name = "savedata";
            this.savedata.Size = new System.Drawing.Size(120, 26);
            this.savedata.TabIndex = 18;
            this.savedata.Text = "Save Data";
            this.savedata.UseVisualStyleBackColor = true;
            this.savedata.Click += new System.EventHandler(this.savedata_Click);
            // 
            // stoprecording
            // 
            this.stoprecording.Location = new System.Drawing.Point(196, 51);
            this.stoprecording.Name = "stoprecording";
            this.stoprecording.Size = new System.Drawing.Size(120, 26);
            this.stoprecording.TabIndex = 16;
            this.stoprecording.Text = "Stop Recording";
            this.stoprecording.UseVisualStyleBackColor = true;
            this.stoprecording.Click += new System.EventHandler(this.stoprecording_Click);
            // 
            // startrecording
            // 
            this.startrecording.Location = new System.Drawing.Point(196, 19);
            this.startrecording.Name = "startrecording";
            this.startrecording.Size = new System.Drawing.Size(120, 26);
            this.startrecording.TabIndex = 15;
            this.startrecording.Text = "Start Recording";
            this.startrecording.UseVisualStyleBackColor = true;
            this.startrecording.Click += new System.EventHandler(this.startrecording_Click);
            // 
            // groupBox5
            // 
            this.groupBox5.Controls.Add(this.eyepicture);
            this.groupBox5.Controls.Add(this.trackingmonitorpicture);
            this.groupBox5.Controls.Add(this.scenepicture);
            this.groupBox5.Controls.Add(this.scenevideo);
            this.groupBox5.Controls.Add(this.eyevideo);
            this.groupBox5.Controls.Add(this.trackingmonitor);
            this.groupBox5.Location = new System.Drawing.Point(358, 19);
            this.groupBox5.Name = "groupBox5";
            this.groupBox5.Size = new System.Drawing.Size(340, 212);
            this.groupBox5.TabIndex = 9;
            this.groupBox5.TabStop = false;
            this.groupBox5.Text = "Observer";
            // 
            // eyepicture
            // 
            this.eyepicture.Location = new System.Drawing.Point(30, 115);
            this.eyepicture.Name = "eyepicture";
            this.eyepicture.Size = new System.Drawing.Size(126, 80);
            this.eyepicture.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.eyepicture.TabIndex = 17;
            this.eyepicture.TabStop = false;
            // 
            // trackingmonitorpicture
            // 
            this.trackingmonitorpicture.Location = new System.Drawing.Point(30, 19);
            this.trackingmonitorpicture.Name = "trackingmonitorpicture";
            this.trackingmonitorpicture.Size = new System.Drawing.Size(126, 90);
            this.trackingmonitorpicture.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.trackingmonitorpicture.TabIndex = 16;
            this.trackingmonitorpicture.TabStop = false;
            // 
            // scenepicture
            // 
            this.scenepicture.Location = new System.Drawing.Point(162, 115);
            this.scenepicture.Name = "scenepicture";
            this.scenepicture.Size = new System.Drawing.Size(154, 80);
            this.scenepicture.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.scenepicture.TabIndex = 18;
            this.scenepicture.TabStop = false;
            // 
            // scenevideo
            // 
            this.scenevideo.Location = new System.Drawing.Point(196, 51);
            this.scenevideo.Name = "scenevideo";
            this.scenevideo.Size = new System.Drawing.Size(120, 26);
            this.scenevideo.TabIndex = 15;
            this.scenevideo.Text = "Scene Video Monitor";
            this.scenevideo.UseVisualStyleBackColor = true;
            this.scenevideo.Click += new System.EventHandler(this.scenevideo_Click);
            // 
            // eyevideo
            // 
            this.eyevideo.Location = new System.Drawing.Point(196, 19);
            this.eyevideo.Name = "eyevideo";
            this.eyevideo.Size = new System.Drawing.Size(120, 26);
            this.eyevideo.TabIndex = 13;
            this.eyevideo.Text = "Eye Image Monitor";
            this.eyevideo.UseVisualStyleBackColor = true;
            this.eyevideo.Click += new System.EventHandler(this.eyevideo_Click);
            // 
            // trackingmonitor
            // 
            this.trackingmonitor.Location = new System.Drawing.Point(196, 83);
            this.trackingmonitor.Name = "trackingmonitor";
            this.trackingmonitor.Size = new System.Drawing.Size(120, 26);
            this.trackingmonitor.TabIndex = 14;
            this.trackingmonitor.Text = "Tracking Monitor";
            this.trackingmonitor.UseVisualStyleBackColor = true;
            this.trackingmonitor.Click += new System.EventHandler(this.trackingmonitor_Click);
            // 
            // logger
            // 
            this.logger.Location = new System.Drawing.Point(123, 19);
            this.logger.Name = "logger";
            this.logger.Size = new System.Drawing.Size(539, 20);
            this.logger.TabIndex = 10;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(92, 22);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(25, 13);
            this.label1.TabIndex = 11;
            this.label1.Text = "Log";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(54, 48);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(63, 13);
            this.label2.TabIndex = 12;
            this.label2.Text = "Sample Log";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(61, 74);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(56, 13);
            this.label3.TabIndex = 13;
            this.label3.Text = "Event Log";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(13, 100);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(104, 13);
            this.label4.TabIndex = 14;
            this.label4.Text = "Calibration Point Log";
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.label1);
            this.groupBox4.Controls.Add(this.label2);
            this.groupBox4.Controls.Add(this.label3);
            this.groupBox4.Controls.Add(this.label4);
            this.groupBox4.Controls.Add(this.logger);
            this.groupBox4.Location = new System.Drawing.Point(12, 430);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(685, 132);
            this.groupBox4.TabIndex = 15;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Logger";
            // 
            // SmiSample
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(717, 637);
            this.Controls.Add(this.groupBox5);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.logger3);
            this.Controls.Add(this.logger2);
            this.Controls.Add(this.logger1);
            this.Controls.Add(this.groupBox4);
            this.Name = "SmiSample";
            this.Text = "C-Sharp iView X API Sample";
            this.Load += new System.EventHandler(this.SmiSample_Load);
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.SmiSample_FormClosing);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.groupBox5.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.eyepicture)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackingmonitorpicture)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.scenepicture)).EndInit();
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox logger1;
        private System.Windows.Forms.TextBox logger2;
        private System.Windows.Forms.TextBox logger3;
        private System.Windows.Forms.Button connect;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button disconnect;
        private System.Windows.Forms.TextBox receiveport;
        private System.Windows.Forms.TextBox sendport;
        private System.Windows.Forms.TextBox receiveip;
        private System.Windows.Forms.TextBox sendip;
        private System.Windows.Forms.Label send;
        private System.Windows.Forms.Label receive;
        private System.Windows.Forms.Button calibrate;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.ComboBox calibrationMethodComboBox;
        private System.Windows.Forms.Button validate;
        private System.Windows.Forms.Button savecalibration;
        private System.Windows.Forms.TextBox calibrationID;
        private System.Windows.Forms.TextBox filename;
        private System.Windows.Forms.Button savedata;
        private System.Windows.Forms.Button stoprecording;
        private System.Windows.Forms.Button startrecording;
        private System.Windows.Forms.Button getaccuracy;
        private System.Windows.Forms.TextBox accuracay;
        private System.Windows.Forms.GroupBox groupBox5;
        private System.Windows.Forms.Button trackingmonitor;
        private System.Windows.Forms.TextBox loggerstatus;
        private System.Windows.Forms.Label loggerlevel;
        private System.Windows.Forms.TextBox logger;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button eyevideo;
        private System.Windows.Forms.ComboBox displayDeviceComboBox;
        private System.Windows.Forms.Button scenevideo;
        private System.Windows.Forms.Label license;
        private System.Windows.Forms.TextBox licensekey;
        private System.Windows.Forms.PictureBox trackingmonitorpicture;
        private System.Windows.Forms.PictureBox scenepicture;
        private System.Windows.Forms.PictureBox eyepicture;
        private System.Windows.Forms.Button loadcalibration;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.Button quit;
        private System.Windows.Forms.Button start;
        private System.Windows.Forms.Button key;
    }
}

