# AutoArt
A computer program that generates art

AutoArt uses [stb_image](https://github.com/nothings/stb) to create images.

For an online version of AutoArt go to http://autoart.neocities.org

For a faster version of AutoArt that runs on your GPU, try [AutoArtGPU](http://github.com/pommicket/AutoArtGPU). Note that this has many more dependencies than AutoArt, so it will be harder to install.

An explanation of how AutoArt works can be found [here](http://autoart.neocities.org/explanation.html).

**AutoVideos (not AutoImages) requires avconv**

**Mac OSX is not supported. If you want to run AutoArt on a Mac, either compile the source code yourself, go to the [online version](http://autoart.neocities.org), or try [AutoArtGPU](http://github.com/pommicket/AutoArtGPU).**

**Running AutoArt on Windows:**  
AutoImages:  
An exe can be found in `AutoImages/bin/Windows`

AutoVideos:  
An exe can be found in `AutoVideos/bin/Windows`  
**Avconv installation for Windows:**  
You can find avconv [here](http://builds.libav.org/windows/release-gpl/). Just extract it to a folder and add that folder to your path (Advanced system settings -> Environment variables).

**Running AutoArt on GNU/Linux:**  
AutoImages:  
An executable can be found in `AutoImages/bin/GNULinux`

AutoVideos: 
An executable can be found in `AutoVideos/bin/GNULinux`  
**Avconv installation for GNU/Linux:**  
On Debian/Ubuntu just run the following command:  
```
sudo apt-get install libav-tools
```

AutoArt now has an [Android app](https://github.com/pommicket/AutoArtAndroid).
