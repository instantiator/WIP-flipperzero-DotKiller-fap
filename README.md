# flipperzero-dotkiller-fap
(WIP - BUILT FOR ROGUEMASTER CUSTOM FIRMWARE) Clean .dotfiles left behind after plugging FLIPPER SD into macOS system directly from you Flipper Zero

This FAP (Flipper APplication) do the same work that the "dotclean" shell's command do on macOS.      
It cleans up all the useless ".dotfiles" that apps such as "Time Machine" creates on a external drive, everytime you put stuffs from macOS to the external drive. (These files will be visibles in the Flipper Zero's browser and various archives as e ".copy" of every files you dragged and dropped on your FLIPPER SD.       
To avoid deleting important configuration and settings files, for now the fap has been developed keeping in mind the ROGUEMASTER FileSystem. So if you want to use it on another FW or CFW, you just need to make a simple change and specify in the `macos_dotkiller.c` file which paths to exclude from elimination, simply adding `strcmp(filepath, "/ext/apps_data/snake/.FILETOKEEP") == 0` in the list of paths to keep.

Since i am not a C developer and I'm doing this also to learn how to interface me with embedded devices, and C programming WHOEVER want to help me modifying the Fap, implemnting stuff and expanding his main goal, IS WELCOME and it would be very appreciate.

That's it that's all. Thank you very much!!

47lecoste a.k.a. grugnoymeme

