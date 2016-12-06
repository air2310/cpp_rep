clear 
close all
clc
%%

Adress = '10.16.97.13';

Port = 1972;

%%
% - open CPP server - then open this client.
!cd C:\Users\uqarento\Documents\Visual Studio 2015\Projects\DisplayLetters\x64\Debug\
!start "" "C:\Users\uqarento\Documents\Visual Studio 2015\Projects\DisplayLetters\x64\Debug\DisplayLetters.exe"
%% open client
t = tcpip(Adress,Port, 'NetworkRole', 'client');
fopen(t)
   
       
fwrite(t,11, 'int8') % 1- 40 for letters

return
%%
fclose(t);
delete(t); clear t
