# Hw4-Plugins

This plugin consists of a pitch shift and gain. 
<br> 
Steps:
<ol>
  <li>Download the folder and in Juce open an existing project. When defining plugin formats, choose VST3 and AU.</li>
  <li>For plugin characteristics, choose Plugin Midi Input. </li>
  <li>You need VST3 plugin as well on your computer in order to run both plugins in your DAW. I used Steinberg. </li>
  <li> Change the global path for the VST in SDK to your VST3 folder. </li>
  <li>When compiling the code, compile all. In order to see the visual plugin, compile standalone plugin. You will not hear any sound or wont be able to test it. As its only the visual design. In order to test, you can compile the AudioPluginHost, however this will only test audio from your built in microphone. You can not play audio in audio plugin host.</li>
  <li> In order to have your plugin in your DAW, compile VST as well as VST helper. </li>
</ol>  
<br>
Notes: <br>
My plugin may not run in your Juce, depending on the version.
This requires updating from your end.
My paths for my files are specific to my computer as well as the modules and those need to be changed for every individual as for me Juce is located in my applications. I was having issues with the modules path and that is why it needs to be changed for each individual.
You might be wondering what a DAW (digital audio workstation) is: an electronic device or application software used for recording, editing and producing audio files.
Now what should you use: you can use any DAW you prefer, however if you are new like me and want a free DAW use waveform. They also have a very nice guide to load your plugins. 

   
