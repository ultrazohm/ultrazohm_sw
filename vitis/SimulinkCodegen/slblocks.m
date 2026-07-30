function blkStruct = slblocks
    Browser.Library = 'mySLLib'; %.slx file
    Browser.Name = 'MSSS Bibliothek'; % name of the library in the SL browser
    blkStruct.Browser = Browser;
end