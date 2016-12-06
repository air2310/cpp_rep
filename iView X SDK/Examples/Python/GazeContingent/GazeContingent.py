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

from iViewXAPI import  *            			#iViewX library
from numpy import *                   			#many different maths functions
from numpy.random import *       				#maths randomisation functions
import os                                   	#handy system and path functions
from psychopy import core, data, event, visual, gui
import psychopy.logging                   		#import like this so it doesn't interfere with numpy.log


# ---------------------------------------------
#---- store info about the experiment
# ---------------------------------------------

expName = 'GazeContingent'
expInfo={'participant':'', 'session':'001'}
dlg=gui.DlgFromDict(dictionary=expInfo,title=expName)
if dlg.OK==False: core.quit() #user pressed cancel
expInfo['date']=data.getDateStr()#add a simple timestamp
expInfo['expName']=expName


# ---------------------------------------------
#---- connect to iView
# ---------------------------------------------

res = iViewXAPI.iV_SetLogger(c_int(1), c_char_p("iViewXSDK_Python_GazeContingent_Demo.txt"))
res = iViewXAPI.iV_Connect(c_char_p('127.0.0.1'), c_int(4444), c_char_p('127.0.0.1'), c_int(5555))

res = iViewXAPI.iV_GetSystemInfo(byref(systemData))
print "iV_GetSystemInfo: " + str(res)
print "Samplerate: " + str(systemData.samplerate)
print "iViewX Verion: " + str(systemData.iV_MajorVersion) + "." + str(systemData.iV_MinorVersion) + "." + str(systemData.iV_Buildnumber)
print "iViewX API Verion: " + str(systemData.API_MajorVersion) + "." + str(systemData.API_MinorVersion) + "." + str(systemData.API_Buildnumber)


# ---------------------------------------------
#---- configure and start calibration
# ---------------------------------------------

displayDevice = 0
calibrationData = CCalibration(5, 1, displayDevice, 0, 1, 20, 239, 1, 10, b"")

res = iViewXAPI.iV_SetupCalibration(byref(calibrationData))
print "iV_SetupCalibration " + str(res)
res = iViewXAPI.iV_Calibrate()
print "iV_Calibrate " + str(res)


# ---------------------------------------------
#---- setup the Window
# ---------------------------------------------

window = visual.Window(size = [1680, 1050],
    pos = [0, 0],
    units = u'pix',
    fullscr = True,
    screen = 0,
    allowGUI = False,
    monitor = 'PrimaryMonitor')
    

# ---------------------------------------------
# ---- Initialise components for routine: trial
# ---------------------------------------------
directory = os.getcwd()

Image = visual.ImageStim(window)
Image.setPos((0, 0))

images = [] 
path = directory + "\\1680"
for file in os.listdir(path):
    for i in range (1, 4):
        if file.lower().endswith("image0" + str(i) + ".jpg"):
            images.append(file)

trialClock=core.Clock()
Shape01 = visual.Circle(win=window, edges=64, radius=8, opacity=1)


# ---------------------------------------------
#---- run the trial
# ---------------------------------------------
size = 10.0
index = 0
while True:

	# update gaze event 
    #res = iViewXAPI.iV_GetEvent(byref(eventData))
    
	# update gaze data sample
    res = iViewXAPI.iV_GetSample(byref(sampleData))
    if res == 1:
        Image.setImage(images[index])
        Image.draw(window)
        Shape01.setFillColor([0, 0, 0])
        sampleData.leftEye.gazeX = sampleData.leftEye.gazeX - 640
        sampleData.leftEye.gazeY = -1 * (sampleData.leftEye.gazeY - 512)
        Shape01.setPos([sampleData.leftEye.gazeX - size, sampleData.leftEye.gazeY - size])
        Shape01.draw()

    #refresh the screen
    window.flip()
    
    #check for quit (the [Esc] key)
    if event.getKeys(["escape"]):
        event.clearEvents()
        core.quit()
    
    # check for next images (the [Space] key)     
    elif event.getKeys(["space"]):
        index = index +1
        if index == len(images):
            event.clearEvents()
            core.quit()
        
    #clear event
    event.clearEvents()



# ---------------------------------------------
#---- stop recording and disconnect from iViewX
# ---------------------------------------------

res = iViewXAPI.iV_Disconnect()


#end of this routine
window.close()
core.quit()
