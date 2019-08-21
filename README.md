# INITIAL DELAY

**DO YOU LIKE ANIME? DO YOU LIKE MEMES? DO YOU OCCASSIONALLY PARTAKE IN AUDIO CREATION WHERE YOU DESPERATELY NEED AN ANIME-THEMED PLUGIN???** 

**DON’T LIE MY FELLOW ~~WEEBS~~ ANIME ENTHUSIASTS, WE KNOW YOU DO AND _BOY OH BOY_ DO WE HAVE THE PRODUCT FOR YOU!**

![alt text](https://i.imgur.com/oncXwbO.jpg?1 "Drift")

### /// INTRODUCING ///
### /// INITIAL DELAY ///

![alt text](https://i.imgur.com/aKIrEBF.png "Coming Soon")

## Table of Contents  
[Initial Delay Demostration Videos](#initialdelaydemonstrationvideos)

[Initial Delay TLDR](#initialdelaytldr)

[Installation Guide](#installation-guide)

[Initial Delay In-depth](#initial-delay-in-depth)

[Contributing](#contributing)

[License](#license)

<a name="initialdelaydemonstrationvideos"/>
<a name="initialdelaytldr"/>
<a name="installationguide"/>
<a name="initialdelayindepth"/>

## Initial Delay Demonstration Videos

### Song Demonstration (WORK IN PROGRESS)

![alt text](https://i.imgur.com/aKIrEBF.png "Coming Soon")

### White Noise Demonstration (WORK IN PROGRESS)

![alt text](https://i.imgur.com/aKIrEBF.png "Coming Soon")

## Initial Delay TLDR (WORK IN PROGRESS)

Initial Delay is a simple and intuitive VST plugin with an anime aesthetic. It utilises a 2-parameter IIR Filter and a single-parameter Delay. Initial Delay was designed for use with a multitude of different instruments in mind, such as
* Synths
* Baritone Electric Guitars
* 7/8 String Electric Guitars
* Bass Guitars
* And anything else you want to put through it, it's completely up to you!

Initial Delay has full automation and save state capabilities for easy use within your favourite DAW! Currently Initial Delay only has a Mac DMG installer, but can be used in Windows via the instructions detailed in the Installation Guide section.

Initial Delay was inspired by the anime "Initial D" and it's internet memes, click the link to the Youtube video below to **_witness the majesty that is Initial D_** 

[![IMAGE ALT TEXT HERE](http://img.youtube.com/vi/fWhZWX3FnXg/0.jpg)](https://www.youtube.com/watch?v=fWhZWX3FnXg)

We created the plugin with the mindset of making a great-sounding plugin first and foremost, with a visually-appealing aesthetic following that. 

We wanted to release Initial Delay for free, but if you wish to donate it would be hugely appreciated! We are two university students from Wellington, New Zealand in our final year of a Bachelor of Commercial Music at Massey University. We will always keep this plug-in free, but feel free to throw us a nickel or two via the Paypal button below if you enjoy our work!


[![paypal](https://www.paypalobjects.com/en_US/i/btn/btn_donateCC_LG.gif)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=YP29EFC3QEU4L)

Additionally, if you want to get in contact with us our email is angryayaya@gmail.com

We'd love to hear from you about our plug-in, whether it be recommendations, issues or just a nice message to us!

From the team behind **_Initial Delay_**, we really hope that you enjoy our plugin and make some awesome tunes with it!
Thank you!

-- Team Angry Ayaya --

## Installation Guide

For Mac users, we recommend cloning/downloading the repository to your computer and installing the plugin through the easy-to-use DMG installer

**Step 1: Open This!**

![alt text](https://i.imgur.com/aKIrEBF.png "Coming Soon")

**Step 2: Open the .pkg found inside for quick and easy installation!**

![alt text](https://i.imgur.com/aKIrEBF.png "Coming Soon")

For Windows users, you will need to setup and run the plugin on your computer. For this you will need
* [Projucer](https://juce.com/ "https://juce.com/")
* [Microsoft Visual Studio](https://visualstudio.microsoft.com/ "https://visualstudio.microsoft.com/")

Please refer to a youtube guide or the JUCE website if you are unsure on how to begin! We recommend this [video by Miskat Music](https://www.youtube.com/watch?v=rGzSSNjbXlA "https://www.youtube.com/watch?v=rGzSSNjbXlA") or the [JUCE Tutorials Page](https://juce.com/learn/tutorials "https://juce.com/learn/tutorials").

Another great source of help we can recommend is [The Audio Programmer Youtube Page](https://www.youtube.com/channel/UCpKb02FsH4WH4X_2xhIoJ1A "https://www.youtube.com/channel/UCpKb02FsH4WH4X_2xhIoJ1A") 

## Initial Delay In-depth (WORK IN PROGRESS)

Initial Delay was primarily built with [Projucer](https://juce.com/ "https://juce.com/")/[XCode](https://developer.apple.com/xcode/ "https://developer.apple.com/xcode/") as a plugin suited specifically to those who maybe don’t know their way round plugins, but are wanting something cool and intuitive to add that extra “oomph!” to their work.

It utilises an always-active low-pass IIR filter and an optional delay. IIR filter stands for an Infinite Impulse Response filter, which is unique with how the decay never really reaches zero (to put it simply!). We choose to use this as we personally thought it sounded the best out of the different kinds of filters that we tested. 

The IIR filter has two parameters that you can change; the frequency Cutoff and the Q-Factor. 
* The Cuttoff knob changes the maximum frequency that the filter will let through (as a low-pass filter)
* The Q-Factor knob changes the resonance or **Q** of the filter

The Delay feature has one parameter that you can change; the Time value. 
* The Time knob changes the overall length of the Delay (ie how long it delays)

If you want to essentially “turn off” the delay, just turn the delay Time knob to its lowest value. 

Here is a setup that we recommend to get you started with the plugin. It creates a really subtle distortion with just the low frequencies coming through, creating a nice rumble or pulse depending on what you are putting through it.

![alt text](https://i.imgur.com/aKIrEBF.png "Coming Soon")

## Contributing and Inspiration

Currently Initial Delay is not open to contribution, but this could change in the future!

Taylor Govers: Processor Editor, Repository/README/License Management, Assistant GUI Editor

Ethan Punter: GUI Editor, Repository Management, Photoshop Editor

For this project, we had inspiration and were helped with code by this youtuber. They make awesome work so please check them out and support them!

[The Audio Programmer](https://www.youtube.com/channel/UCpKb02FsH4WH4X_2xhIoJ1A "https://www.youtube.com/channel/UCpKb02FsH4WH4X_2xhIoJ1A")

And of course, huge inspiration from the anime behind the meme [Initial D](https://myanimelist.net/anime/185/Initial_D_First_Stage "https://myanimelist.net/anime/185/Initial_D_First_Stage"), the creator [Shigeno Shuuichi](https://myanimelist.net/people/2357/Shuuichi_Shigeno "https://myanimelist.net/people/2357/Shuuichi_Shigeno") and the studio that created it [Gallop](https://myanimelist.net/anime/producer/36/Gallop "https://myanimelist.net/anime/producer/36/Gallop")  

## License (WORK IN PROGRESS)

[GNU GPLv3](https://github.com/TGovers/Angry_Ayaya_Release/blob/master/LICENSE.txt)
