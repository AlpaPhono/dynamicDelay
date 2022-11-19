# dynamicDelay
<!-- omit -->
## A dynamic delay plugin created with [JUCE](https://juce.com/)

<img src="Images/Screenshot 2022-11-19 at 19.13.40.png" width="70%">

<!-- omit -->
## Contents 
<!--omit -->

## Introduction
This was the final major project submission for the Msc Music and Sound Technology (Audio Programming) at the University of Hertfordshire. The project revolved around creating a delay plugin that attenuated its feedback loop in response to the dry signal. This would create an inverse relationship between the wet and dry signal where as the dry signal was louder the wet signal would be quieter and vice versa.<br/>
The GUI is based off of [CTAG Dynamic Range Compressor](https://github.com/p-hlp/CTAGDRC#readme) which has a baisc compressor interface.<br/>
The decision to make the delay plugins interface appear like a compressors was made because it would be a clear depiction of the signal attenuation.
<br/>
## Features
- Delay Time 
- Ratio
- Threshold
- Feedback
- Metering (Feedback/ Gain Reduction)
<br/>
## Manual
### General 
- **DelayTime:** The delay time knob adjust the output of the delayed signal in ms. The further right the knob is turned the more delayed the signal will be.
- **FEEDBACK*:** Controls the amount of delay feedback

