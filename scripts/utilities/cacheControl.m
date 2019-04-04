project = simulinkproject;
projectRoot = project.RootFolder;

myCacheFolder = fullfile(projectRoot, 'cache');
myCodeFolder = fullfile(projectRoot, 'code');

Simulink.fileGenControl('set',...
    'CacheFolder', myCacheFolder,...
    'CodeGenFolder', myCodeFolder,...
    'createDir', true)

clearvars