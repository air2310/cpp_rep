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
% 
% formatString.m
%
% Description: 
% Due to the fact the iView X API functions are expecting a char array with a specific length it 
% is needed to format the char arrays before handing them over to the iView X API functions. The 
% formatString function will format the string which will be handed over to iView X API functions. 
% 
% input parameter: 
% StringLength - String length which is expected by the iView X API. See the iView X SDK manual for further information. 
% UnformattedString - The string which should be hand over to iView X API function 
% 
% output / return: 
% FormattedString - The string which will be hand over to iView X API function 
% 
% Author: SMI GmbH, 2013

function [ FormattedString ] = formatString( StringLength, UnformattedString )

    UnformattedStringLength = length(UnformattedString);
    zero = 1:StringLength - UnformattedStringLength;
    zero(:) = 0;

    FormattedString = [UnformattedString int8(zero)];

    
    