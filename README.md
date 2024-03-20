# Hw4-Plugins

There are two folders for the plugins. 
1. PlugHw4 is the gain plugin.
2. Pitch Shift is the pitch shifter plugin. <br>
*Professor said I could have two seperate plugins aka the gain and pitch shifter.      
Steps:
1. Download the folders and in Juce open an existing project. When defining plugin formats, choose VST3 and AU.
2. For plugin characteristics, choose Plugin Midi Input. 
3. You need VST3 plugin as well on your computer in order to run both plugins in your DAW. I used Steinberg. 
4. Each plugin requires its own project in Juce.
5. For each project change the global path for the VST in SDK to your VST3 folder.
6. When compiling the code, compile all. In order to see the visual plugin, compile standalone plugin. You will not hear any sound or will be able to test it. As its only the visual design. In order to test, you can compile the AudioPluginHost however this will only test audio from your built in microphone. You can not run audio in audio plugin host.
7. In order to have your plugin in your DAW, compile VST as well as VST helper. 
Notes: <br>
My plugins may not run in your Juce, depending on the version. This requires updating from your end.
My paths for my files are specific to my computer as well as the modules and those need to be changed for every individual.
You might be wondering what a DAW (digital audio workstation) is: an electronic device or application software used for recording, editing and producing audio files.
Now what should you use: you can use any DAW you prefer, however if you are new like me and want a free DAW use waveform. They also have a very nice guide to load your plugins. 

   
