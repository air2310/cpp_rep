tdfread('C:\Users\uqarento\Documents\angela_renton_local\working_memory\WM_CDA\WM_CDA\data.txt','\t')

%%
FileID = fopen('C:\Users\uqarento\Documents\angela_renton_local\working_memory\WM_CDA\WM_CDA\xcoorddata.txt');

C = textscan(FileID, '%d %d %d %d %d %d %d %d', 'Headerlines', 1)

fclose(FileID);

%%
FileID = fopen('C:\Users\uqarento\Documents\angela_renton_local\working_memory\WM_CDA\WM_CDA\data\Cuedside.txt');

C = textscan(FileID, '%d' , 'Headerlines', 1)

fclose(FileID);