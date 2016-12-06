% -----------------------------------------------------------------------
%
% (c) Copyright 1997-2013, SensoMotoric Instruments GmbH
% 
% Permission  is  hereby granted,  free  of  charge,  to any  person  or
% organization  obtaining  a  copy  of  the  software  and  accompanying
% documentation  covered  by  this  license  (the  "Software")  to  use,
% reproduce,  display, distribute, execute,  and transmit  the Software,
% and  to  prepare derivative  works  of  the  Software, and  to  permit
% third-parties to whom the Software  is furnished to do so, all subject
% to the following:
% 
% The  copyright notices  in  the Software  and  this entire  statement,
% including the above license  grant, this restriction and the following
% disclaimer, must be  included in all copies of  the Software, in whole
% or  in part, and  all derivative  works of  the Software,  unless such
% copies   or   derivative   works   are   solely   in   the   form   of
% machine-executable  object   code  generated  by   a  source  language
% processor.
% 
% THE  SOFTWARE IS  PROVIDED  "AS  IS", WITHOUT  WARRANTY  OF ANY  KIND,
% EXPRESS OR  IMPLIED, INCLUDING  BUT NOT LIMITED  TO THE  WARRANTIES OF
% MERCHANTABILITY,   FITNESS  FOR  A   PARTICULAR  PURPOSE,   TITLE  AND
% NON-INFRINGEMENT. IN  NO EVENT SHALL  THE COPYRIGHT HOLDERS  OR ANYONE
% DISTRIBUTING  THE  SOFTWARE  BE   LIABLE  FOR  ANY  DAMAGES  OR  OTHER
% LIABILITY, WHETHER  IN CONTRACT, TORT OR OTHERWISE,  ARISING FROM, OUT
% OF OR IN CONNECTION WITH THE  SOFTWARE OR THE USE OR OTHER DEALINGS IN
% THE SOFTWARE.
%
% -----------------------------------------------------------------------
% DataStreaming.m
%
% This script shows how to connect to SMI eye tracking application, 
% calibrate the eye tracker and receive numerical eye tracking data in Matlab 
%
%
% Author: SMI GmbH, 2013

%===========================
%Initialisation
%===========================

%clear all variables, connections, ...
clear all
clc
warning('off', 'all');
   
connected = 0;
   
% load the iViewX API library
loadlibrary('iViewXAPI.dll', 'iViewXAPI.h');


[pSystemInfoData, pSampleData, pEventData, pAccuracyData, CalibrationData] = InitiViewXAPI();

CalibrationData.method = int32(5);
CalibrationData.visualization = int32(1);
CalibrationData.displayDevice = int32(0);
CalibrationData.speed = int32(0);
CalibrationData.autoAccept = int32(1);
CalibrationData.foregroundBrightness = int32(250);
CalibrationData.backgroundBrightness = int32(230);
CalibrationData.targetShape = int32(2);
CalibrationData.targetSize = int32(20);
CalibrationData.targetFilename = int8('');
pCalibrationData = libpointer('CalibrationStruct', CalibrationData);


disp('Define Logger')
calllib('iViewXAPI', 'iV_SetLogger', int32(1), 'iViewXSDK_Matlab_DataStreaming_Demo.txt')


disp('Connect to iViewX')
ret = calllib('iViewXAPI', 'iV_Connect', '127.0.0.1', int32(4444), '127.0.0.1', int32(5555))
switch ret
    case 1
        connected = 1;
    case 104
         msgbox('Could not establish connection. Check if Eye Tracker is running', 'Connection Error', 'modal');
    case 105
         msgbox('Could not establish connection. Check the communication Ports', 'Connection Error', 'modal');
    case 123
         msgbox('Could not establish connection. Another Process is blocking the communication Ports', 'Connection Error', 'modal');
    case 200
         msgbox('Could not establish connection. Check if Eye Tracker is installed and running', 'Connection Error', 'modal');
    otherwise
         msgbox('Could not establish connection', 'Connection Error', 'modal');
end


if connected

	disp('Get System Info Data')
	calllib('iViewXAPI', 'iV_GetSystemInfo', pSystemInfoData)
	get(pSystemInfoData, 'Value')


	disp('Calibrate iViewX')
	calllib('iViewXAPI', 'iV_SetupCalibration', pCalibrationData)
	calllib('iViewXAPI', 'iV_Calibrate')


	disp('Validate Calibration')
	calllib('iViewXAPI', 'iV_Validate')


	disp('Show Accuracy')
	calllib('iViewXAPI', 'iV_GetAccuracy', pAccuracyData, int32(0))
	get(pAccuracyData, 'Value')

	exitLoop = 0;
	try 

		for i = 1:1000
			
			ret = calllib('iViewXAPI', 'iV_GetSample', pSampleData);
			if (ret == 1)

				% get sample
				Smp = libstruct('SampleStruct', pSampleData);
				[int2str(Smp.timestamp) ' - GazeX: ' int2str(Smp.leftEye.gazeX) ' - GazeY: ' int2str(Smp.leftEye.gazeY)]
				pause(0.01);

			end

		end

	catch
		s = lasterror
	end
end

disp('Disconnect')

% disconnect from iViewX 
calllib('iViewXAPI', 'iV_Disconnect')

pause(1);
clear all

% unload iViewX API libraray
unloadlibrary('iViewXAPI');

