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

# Author: 
# (C) 2013 Sensomotoric Instruments 


#############################################################
#																				#
#	before running this scenario please set 						#
#	"Scenarios -> Stimulus Directory" to a path where all 	#
#	stimuli used in this scenario reside							#
#																				#
#############################################################

scenario = "Slideshow";
no_logfile = true;
active_buttons = 1; 
button_codes = 1;
default_font_size = 24;
default_font = "Times New Roman";
default_background_color = 230, 230, 230;

# pcl file 
pcl_file = "Slideshow.pcl";

begin;

picture {} default;         


#############################################################
#																				#
#		image definition													#
#																				#
#############################################################

array {
   bitmap { filename = "image01.jpg"; preload = false; };
   bitmap { filename = "image02.jpg"; preload = false; };
   bitmap { filename = "image03.jpg"; preload = false; };
} graphics;

trial {
	trial_duration = forever;
	trial_type = specific_response;
	terminator_button = 1;
   picture {  
      # placeholder - set by PCL
      box { height = 1; width = 1; color = 0,0,0; };
      x = 0; y = 0;
   } pic1;
} trial1;


#calibration bitmap
picture
{
   bitmap 
	{
		filename = "black circle.bmp"; 
		trans_src_color = 255,255,255; 
	};
   x = 0; 
	y = 0;
} et_calibration;


# show error message if connection could not be established 
picture{
	text{	
		caption = "Could not establish connection to Eye Tracker \n\n\n Check if the Eye Tracker \n is running and the \n Network Settings are set correctly"; 
		font_size = 20; 
		font_color = 20, 20, 20;
		transparent_color = 0,0,0;
	};
	x = 0;
	y = 0;
}connect_error;


# show accuracy message after the calibration has been validated 
picture { 
   text { 
			caption = "Validation Results: \n\n Accuracy X: - \n Accuracy Y: -";
			font_size = 20; 
			font_color = 20, 20, 20;
			transparent_color = 0,0,0;
			preload = false;
   }accuracy_text;   
   x = 0; 
	y = 0;
}accuracy_picture;

 
# show error message if resolution is wrong 
picture{
	text{	
		caption = "Please change \n the screen resolution \n of your computer \n to 1280 x 1024 or 1680 x 1050"; 
		font_size = 20; 
		font_color = 20, 20, 20;
		transparent_color = 0,0,0;
	};
	x = 0;
	y = 0;
}resolution_error;


# show end message if experiment has been finished 
picture{
	text{	
		caption = "End of Experiment"; 
		font_size = 20; 
		font_color = 20, 20, 20;
		transparent_color = 0,0,0;
	};
	x = 0;
	y = 0;
}end_experiment;


picture{
	text{	
		caption = "Try to acquire data..."; 
		font_size = 20; 
		font_color = 20, 20, 20;
		transparent_color = 0,0,0;
	};
	x = 0;
	y = 0;
}data_acquisition;
