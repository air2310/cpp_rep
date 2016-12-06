# -----------------------------------------------------------------------
#
# (c) Copyright 1997-2013, SensoMotoric Instruments GmbH
# 
# Permission  is  hereby granted,  free  of  charge,  to any  person  or
# organization  obtaining  a  copy  of  the  software  and  accompanying
# documentation  covered  by  this  license  (the  "Software")  to  use,
# reproduce,  display, distribute, execute,  and transmit  the Software,
# and  to  prepare derivative  works  of  the  Software, and  to  permit
# third-parties to whom the Software  is furnished to do so, all subject
# to the following:
# 
# The  copyright notices  in  the Software  and  this entire  statement,
# including the above license  grant, this restriction and the following
# disclaimer, must be  included in all copies of  the Software, in whole
# or  in part, and  all derivative  works of  the Software,  unless such
# copies   or   derivative   works   are   solely   in   the   form   of
# machine-executable  object   code  generated  by   a  source  language
# processor.
# 
# THE  SOFTWARE IS  PROVIDED  "AS  IS", WITHOUT  WARRANTY  OF ANY  KIND,
# EXPRESS OR  IMPLIED, INCLUDING  BUT NOT LIMITED  TO THE  WARRANTIES OF
# MERCHANTABILITY,   FITNESS  FOR  A   PARTICULAR  PURPOSE,   TITLE  AND
# NON-INFRINGEMENT. IN  NO EVENT SHALL  THE COPYRIGHT HOLDERS  OR ANYONE
# DISTRIBUTING  THE  SOFTWARE  BE   LIABLE  FOR  ANY  DAMAGES  OR  OTHER
# LIABILITY, WHETHER  IN CONTRACT, TORT OR OTHERWISE,  ARISING FROM, OUT
# OF OR IN CONNECTION WITH THE  SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
# -----------------------------------------------------------------------

#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""This experiment was created using PsychoPy2 Experiment Builder
If you publish work using this script please cite the relevant PsychoPy publications
  Peirce (2007) Journal of Neuroscience Methods 162:8-1
  Peirce (2009) Frontiers in Neuroinformatics, 2: 10"""

import os                                   #handy system and path functions
import sys                                 #handy system and path functions

from iViewXAPI import  *            #iViewX library
from iViewXAPIReturnCodes import * 
from numpy import *                   #many different maths functions
from numpy.random import *       #maths randomisation functions
from psychopy import core, data, event, visual, gui
import psychopy.logging              #import like this so it doesn't interfere with numpy.log


# ---------------------------------------------
#---- store info about the experiment
# ---------------------------------------------

expName = 'SlideShow'
expInfo={'participant':'', 'session':'001', 'user':''}
dlg=gui.DlgFromDict(dictionary=expInfo,title=expName)
if dlg.OK==False: core.quit() #user pressed cancel
expInfo['date']=data.getDateStr()#add a simple timestamp
expInfo['expName']=expName


# ---------------------------------------------
#---- setup files for saving
# ---------------------------------------------

if not os.path.isdir('data'):
    os.makedirs('data')
    #if this fails (e.g. permissions) we will get error

psychopy.logging.console.setLevel(psychopy.logging.warning)
#this outputs to the screen, not a file

path = os.getcwd() + "\\data\\"
filename='%s_%s' %(expInfo['participant'], expInfo['date'])
logFile=psychopy.logging.LogFile(path+filename+'.log', level=psychopy.logging.EXP)
description = expInfo['session']
user = expInfo['user']
print "filename: " + filename
print "user: " + user
print "description: " + description


# ---------------------------------------------
#---- connect to iViewX 
# ---------------------------------------------

res = iViewXAPI.iV_SetLogger(c_int(1), c_char_p("iViewXSDK_Python_Slideshow_Demo.txt"))
res = iViewXAPI.iV_Connect(c_char_p('127.0.0.1'), c_int(4444), c_char_p('127.0.0.1'), c_int(5555))
if res != 1:
    HandleError(res)
    exit(0)
    
res = iViewXAPI.iV_GetSystemInfo(byref(systemData))
print "iV_GetSystemInfo: " + str(res)
print "Samplerate: " + str(systemData.samplerate)
print "iViewX Version: " + str(systemData.iV_MajorVersion) + "." + str(systemData.iV_MinorVersion) + "." + str(systemData.iV_Buildnumber)
print "iViewX API Version: " + str(systemData.API_MajorVersion) + "." + str(systemData.API_MinorVersion) + "." + str(systemData.API_Buildnumber)


# ---------------------------------------------
#---- configure and start calibration
# ---------------------------------------------

calibrationData = CCalibration(5, 1, 0, 0, 1, 250, 220, 2, 20, b"")

res = iViewXAPI.iV_SetupCalibration(byref(calibrationData))
print "iV_SetupCalibration " + str(res)
res = iViewXAPI.iV_Calibrate()
print "iV_Calibrate " + str(res)

res = iViewXAPI.iV_Validate()
print "iV_Validate " + str(res)

res = iViewXAPI.iV_GetAccuracy(byref(accuracyData), 1)
print "iV_GetAccuracy " + str(res)
print "deviationXLeft " + str(accuracyData.deviationLX) + " deviationYLeft " + str(accuracyData.deviationLY)
print "deviationXRight " + str(accuracyData.deviationRX) + " deviationYRight " + str(accuracyData.deviationRY)

res = iViewXAPI.iV_ShowTrackingMonitor()
print "iV_ShowTrackingMonitor " + str(res)


# ---------------------------------------------
#---- setup the Window
# ---------------------------------------------

window = visual.Window(size = [1680, 1050],
    pos = [0, 0],
    units = u'pix',
    fullscr = True,
    screen = 0,
    allowGUI = False,
    monitor = 'PrimaryMonitor',
    color = [239, 239, 239])

	
# ---------------------------------------------
# --- set correct image path here
# ---------------------------------------------

image_path = "1680\\"


# ---------------------------------------------
#---- Initialise components for routine: trial
# ---------------------------------------------

trialClock=core.Clock()
image = image_path + "image01.jpg"
Trial01=visual.PatchStim(win=window, tex=image, mask=u'None',
    ori=0, pos=[0, 0], size=[1680,1050], sf=None, phase=0.0,
    color=[1,1,1], colorSpace=u'rgb',
    texRes=128, units=u'pix', interpolate=False)

image = image_path + "image02.jpg"
Trial02=visual.PatchStim(win=window, tex=image, mask=u'None',
    ori=0, pos=[0, 0], size=[1680,1050], sf=None, phase=0.0,
    color=[1,1,1], colorSpace=u'rgb',
    texRes=128, units=u'pix', interpolate=False)

image = image_path + "image03.jpg"
Trial03=visual.PatchStim(win=window, tex=image, mask=u'None',
    ori=0, pos=[0, 0], size=[1680,1050], sf=None, phase=0.0,
    color=[1,1,1], colorSpace=u'rgb',
    texRes=128, units=u'pix', interpolate=False)

	
# ---------------------------------------------
#---- run the trial
# ---------------------------------------------

iViewXAPI.iV_StartRecording()
image01drawn = False
image02drawn = False
image03drawn = False
continueTrial=True
t=0; trialClock.reset()
while continueTrial and (t<9.0000):

    #get current time
    t=trialClock.getTime()
    #update/draw components on each frame
    if (0.0 <= t < (0.0+3.0)):
        Trial01.draw()
        if image01drawn is False:
            iViewXAPI.iV_SendImageMessage(c_char_p("image01.jpg"))
            image01drawn = True
            
    if (3.0 <= t < (3.0+6.0)):
        Trial02.draw()
        if image02drawn is False:
            iViewXAPI.iV_SendImageMessage(c_char_p("image02.jpg"))
            image02drawn = True
            
    if (6.0 <= t < (6.0+9.0)):
        Trial03.draw()
        if image03drawn is False:
            iViewXAPI.iV_SendImageMessage(c_char_p("image03.jpg"))
            image03drawn = True

    #check for quit (the [Esc] key)
    if event.getKeys(["escape"]): core.quit()

    #clear event
    event.clearEvents()

    #refresh the screen
    window.flip()


# ---------------------------------------------
#---- stop recording and disconnect from iViewX
# ---------------------------------------------

iViewXAPI.iV_StopRecording()
outputfile = path + filename
res = iViewXAPI.iV_SaveData(str(outputfile), str(description), str(user), 1)
print 'iV_SaveData ' + str(res)
print "data saved to: " + outputfile

iViewXAPI.iV_Disconnect()

#end of this routine
window.close()
core.quit()
