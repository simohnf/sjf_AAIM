# sjf_AAIM
More information on this project can be found [here](https://simohnf.github.io./AAIM/)

### To download and build:
Open terminal and cd to the Max8 Packages folder
```
cd ~/Documents/Max\ 8/Packages
```
The clone the repository (use recursive to ensure it downloads all of the  submodules correctly)
```
git clone https://github.com/simohnf/sjf_AAIM --recursive
```
Then cd into the folder
```
cd sjf_AAIM
```
Then create the build folder
```
mkdir build
```
cd into the build folder
``` 
cd build
```
---------------------------------
On Mac first build the XCode file
```
cmake -G Xcode ..
```
Then build the project
```
cmake --build . --config Release 
```
---------------------------------

For Windows follow the instructions on the [Min-DevKit repository](https://github.com/Cycling74/min-devkit)

----------------------------------
# sjf_AAIM
This package was created using the Min-DevKit for Max, an API and supporting tools for writing externals in modern C++.

## Prerequisites

You can use the objects provided in this package as-is.

To code your own objects, or to re-compile existing objects, you will need a compiler:

* On the Mac this means **Xcode 9 or later** (you can get from the App Store for free). 
* On Windows this means **Visual Studio 2017** (you can download a free version from Microsoft). The installer for Visual Studio 2017 offers an option to install Git, which you should choose to do.

You will also need the Min-DevKit, available from the Package Manager inside of Max or [directly from Github](https://github.com/Cycling74/min-devkit).

## Contributors / Acknowledgements

The sjf_AAIM is the work of some amazing and creative artists, researchers, and coders.



## Support

For support, please contact the developer of this package.

---------------------------------
