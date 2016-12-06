workingDir = 'C:\Users\uqarento\Documents\Visual Studio 2015\Projects\Spaceship_release\sfml_network\screenshots3\';

imageNames = dir(fullfile(workingDir,'*.bmp'));
imageNames = {imageNames.name}';

outputVideo = VideoWriter(fullfile(workingDir,'spaceshipmovie.avi'));
outputVideo.FrameRate = 30;
open(outputVideo)

for ii = 1:length(imageNames)
   img = imread(fullfile(workingDir,imageNames{ii}));
   writeVideo(outputVideo,img)
end
close(outputVideo)

%% play video
% 
% shuttleAvi = VideoReader(fullfile(workingDir,'shuttle_out.avi'));
% 
% ii = 1;
% while hasFrame(shuttleAvi)
%    mov(ii) = im2frame(readFrame(shuttleAvi));
%    ii = ii+1;
% end
% 
% f = figure;
% f.Position = [150 150 shuttleAvi.Width shuttleAvi.Height];
% 
% ax = gca;
% ax.Units = 'pixels';
% ax.Position = [0 0 shuttleAvi.Width shuttleAvi.Height];
% 
% image(mov(1).cdata,'Parent',ax)
% axis off
% 
% movie(mov,1,shuttleAvi.FrameRate)
