Edge Engine
=================
### Table of contents
- [Overview](https://github.com/Measurify/edge#overview)
- [Installation](https://github.com/Measurify/edge#installation)
    - [Prerequisites](https://github.com/Measurify/edge#prerequisites)
        - [Windows](https://github.com/Measurify/edge#windows)
        - [Arduino/ESP](https://github.com/Measurify/edge#arduinoesp)
		- [Arduino/ESP optional libraries](https://github.com/Measurify/edge#arduinoesp-optional-libraries)
    - [Windows installation](https://github.com/Measurify/edge#windows-installation)
    - [Arduino installation](https://github.com/Measurify/edge#arduino-installation)
- [Library building](https://github.com/Measurify/edge#library-building)
	- [g++](https://github.com/Measurify/edge#g)
	- [MSVC](https://github.com/Measurify/edge#MSVC)
- [Usage](https://github.com/Measurify/edge#Usage)
    - [PC example](https://github.com/Measurify/edge#PC-example)
    - [Arduino example](https://github.com/Measurify/edge#Arduino-example)
- [Implementation for other devices](https://github.com/Measurify/edge#Implementation-for-other-devices)
## Overview
The idea behind this project is to create a generic runtime system and therefore compatible in various circumstances, independent of the hardware and suitable for simple devices such as integrated boards.
This engine can process data flows from sensors through scripts or execute commands using the actuators connected to it.
Scripts are made up of a set of known operations which can also be used together to perform even complex calculations on each measurement flow. The Edge Engine can be configured to retrieve scripts online (from a cloud) to be run locally and periodically check whether these have changed or if there are new scripts to be executed.
In order to work and to exploit all its potential, the engine needs therefore an online endpoint through which it can be programmed. It is not tied to any proprietary platform, the provider can choose the cloud service to which the engine will be connected. 
In this specific project, Measurify will be used: a cloud-based, measurement-oriented platform created by the Elios Lab of the University of Genoa to manage intelligent objects in IoT ecosystems.
## Installation
Download or clone this repo. Remember to check the myDefines.h file, which allows to switch from Arduino, ESP and PC platforms through preprocessor defines as follows:
- **ARDUINO** for Arduino boards
- **ESP_WROVER and ARDUINO** for ESP boards

If none are defined, compilation will be for PC. It should also work on MacOS or Ubuntu, but it has only been tested on Windows.
### Prerequisites
Here are listed the prerequisites for the tree aforementioned platforms.
##### Windows
- A C++14 or higher compiler (GCC 8.1.0 or newer suggested)
- [MINGW64](http://www.mingw.org/)
- [MSYS2](https://www.msys2.org/)
- [POCO](https://pocoproject.org/) headers and libraries 
##### Arduino/ESP
- [Arduino IDE](https://www.arduino.cc/en/main/software) or [VSCode](https://code.visualstudio.com/) + [Arduino extension](https://marketplace.visualstudio.com/items?itemName=vsciot-vscode.vscode-arduino)
- [WiFiNINA](https://github.com/arduino-libraries/WiFiNINA) (only for Arduino boards)
##### Arduino/ESP optional libraries
- [Adafruit IO](https://github.com/adafruit/Adafruit_IO_Arduino)
- [AUnit](https://github.com/bxparks/AUnit)
- [DHT Sensor Library](https://github.com/adafruit/DHT-sensor-library)
- [DHT Sensor Library for ESPx](https://www.arduinolibraries.info/libraries/dht-sensor-library-for-es-px)
- [Sparkfun TSL2561](https://github.com/sparkfun/SparkFun_TSL2561_Arduino_Library)
### Windows installation
In order to install the POCO libraries (required for the HTTP requests) we suggest using the MSYS2 package manager for MINGW64.
Once the installation is completed, open the MSYS2 prompt and install the POCO libraries:
```
$ pacman -S mingw64/mingw-w64-x86_64-poco
```
If you intend to use another compiler different from the GCC one, you can use other package manager such as [VCPKG](https://github.com/microsoft/vcpkg) for Windows, or [Conan](https://conan.io/).
### Arduino installation
All the required libraries must be inside the libraries folder which can be found by looking at the IDE settings (sketches folder path).
Also the Edge Engine library needs to be inside the same folder. If you encounter any problem regarding the _connection_windows_ class or the _APIRest_windows_ class, delete them together with their headers from the aforementioned folder since if you compile for Arduino you do not need them.
For the Arduino installation, not the ESP, it is necessary to have part of the stdlib, which can be added by moving the include folder (available in this repository as the include.rar archive, to be extracted) inside the Arduino installation folder. In Windows it should be placed in `C:\Program Files (x86)\Arduino\hardware\tools\avr\avr\` replacing the existing *include* folder. Also, only for Arduino boards, you will need to add the SSL certificate of Measurify to the board. In order to do so you need to update the WiFiNINA firmware to at least version 1.4.3 and add the certificate of *students.atmosphere.tools* (the Measurify URL) by following [this post](https://support.arduino.cc/hc/en-us/articles/360016119219-How-to-add-certificates-to-Wifi-Nina-Wifi-101-Modules-).
## Library building
In this section the instructions for building .lib files from the source code are specified.
### g++
If you are using the g++ compiler here there are the istructions for creating the .lib file:
```
g++ -c APIRest_windows.cpp -IC:\Edgine\EdgeEngine_library\src -IC:\msys64\mingw64\include 
g++ -c average.cpp -IC:\Edgine\EdgeEngine_library\src -IC:\msys64\mingw64\include 
g++ -c connection_windows.cpp -IC:\Edgine\EdgeEngine_library\src -IC:\msys64\mingw64\include 
g++ -c edgine.cpp -IC:\Edgine\EdgeEngine_library\src -IC:\msys64\mingw64\include
g++ -c filter.cpp -IC:\Edgine\EdgeEngine_library\src -IC:\msys64\mingw64\include
g++ -c mapVal.cpp -IC:\Edgine\EdgeEngine_library\src -IC:\msys64\mingw64\include
g++ -c maxVal.cpp -IC:\Edgine\EdgeEngine_library\src -IC:\msys64\mingw64\include
g++ -c median.cpp -IC:\Edgine\EdgeEngine_library\src -IC:\msys64\mingw64\include
g++ -c minVal.cpp -IC:\Edgine\EdgeEngine_library\src -IC:\msys64\mingw64\include
g++ -c operation.cpp -IC:\Edgine\EdgeEngine_library\src -IC:\msys64\mingw64\include 
g++ -c postVal.cpp -IC:\Edgine\EdgeEngine_library\src -IC:\msys64\mingw64\include 
g++ -c reception.cpp -IC:\Edgine\EdgeEngine_library\src -IC:\msys64\mingw64\include 
g++ -c sample.cpp -IC:\Edgine\EdgeEngine_library\src -IC:\msys64\mingw64\include 
g++ -c script.cpp -IC:\Edgine\EdgeEngine_library\src -IC:\msys64\mingw64\include 
g++ -c slidingWindow.cpp -IC:\Edgine\EdgeEngine_library\src -IC:\msys64\mingw64\include 
g++ -c stdDeviation.cpp -IC:\Edgine\EdgeEngine_library\src -IC:\msys64\mingw64\include 
g++ -c window.cpp -IC:\Edgine\EdgeEngine_library\src -IC:\msys64\mingw64\include 
ar rcs Edgine.lib APIRest_windows.o average.o connection_windows.o edgine.o filter.o mapVal.o maxVal.o median.o minVal.o operation.o postVal.o reception.o sample.o script.o slidingWindow.o stdDeviation.o window.o
```
### MSVC
If you are using the MSVC compiler we suggest to create a new Visual Studio project, then set the output file to .lib, add to the include directories the source code files and give the linker the location of your POCO libraries .lib files. Remember that, in this case, the POCO libraries need to be compiled with the MSVC compiler. In order to do that, we suggest to use [VCPKG](https://github.com/microsoft/vcpkg). Here there are the commands you should execute:
```
vcpkg install POCO:x64-windows
vcpkg integrate install
```
If an integrate installation is performed, it will not be necessary to give the linker the POCO libraries' path.
## Usage
Inside this repository you can find two examples relative to the Edge Engine library under the _examples_ folder. One of them is for the Arduino board ESP32 and the other is for PCs.
In this section you will learn how to make both of them work correctly.
Both examples have a common base.
First, they check if there is an internet connection, then, if yes, they proceed with the authentication phase: a POST request containing username and password is sent and, if the process is successful, a JWT is received. This JWT is needed to send the future HTTP requests.
Then _samples_ are created, containing the parameters read by the sensors taken into consideration. These samples, characterized by a feature name, a date, and a value are finally sent to Measurify.
It is possible to switch between versions by modifying the _myDefines.h_ file.
### PC example
The PC example simulates a temperature sensor behavior and it uses the Measurify platform as online server.
In order to make it work it is necessary to give the compiler some directives, so it can find the POCO libraries and link the sub-libraries correctly.
Here you have a sample compile command:
```
path/to/mingw64/bin/g++.exe 
-g 
path\to\EdgeEngine_library\examples\CC\EdgeEdgine\EdgineExample.cpp
path\to\EdgeEngine_library\src\connection_windows.cpp
path\to\EdgeEngine_library\src\sample.cpp
path\to\EdgeEngine_library\src\APIRest_windows.cpp
path\to\EdgeEngine_library\src\average.cpp
path\to\EdgeEngine_library\src\edgine.cpp
path\to\EdgeEngine_library\src\filter.cpp
path\to\EdgeEngine_library\src\mapVal.cpp
path\to\EdgeEngine_library\src\maxVal.cpp
path\to\EdgeEngine_library\src\median.cpp
path\to\EdgeEngine_library\src\minVal.cpp
path\to\EdgeEngine_library\src\operation.cpp
path\to\EdgeEngine_library\src\postVal.cpp
path\to\EdgeEngine_library\src\reception.cpp
path\to\EdgeEngine_library\src\script.cpp
path\to\EdgeEngine_library\src\slidingWindow.cpp
path\to\EdgeEngine_library\src\stdDeviation.cpp
path\to\EdgeEngine_library\src\window.cpp
-o
path\to\EdgeEngine_library\examples\CC\EdgeEdgine\EdgineExample.exe
-Ipath\to\msys64\mingw64\include
-Ipath\to\EdgeEngine\edge-engine\EdgeEngine_library\src
-Lpath\to\msys64\mingw64\bin
-Lpath\to\msys64\mingw64\lib
-lPocoFoundation -lPocoUtil -lPocoNet -lPocoNetSSL
```
The code is mainly divided in two parts: a **setup** one and an **action** one. Both are represented by two function sequentially called by the _main_.
The **setup** phase consists of _options_ setup. These are the fields necessary to the establish a connection with the given database:
```
options opts;
    //login
    opts.username = "riccardo-office-temperature-sensor-username";
    opts.password =  "riccardo-office-temperature-sensor-password";
    //route
    opts.url = "http://students.atmosphere.tools";
    opts.ver = "v1";
    opts.login = "login";
    opts.devs = "devices";
    opts.scps = "scripts";
    opts.measurements = "measurements";
    opts.info= "info";
    opts.issues="issues";
    //Edgine identifiers
    opts.thing = "riccardo-office";
    opts.device = "environment-riccardo-office";
    opts.id = "environment-riccardo-office";
```
Then, Edge engine is initialized with the given _options_:
```
Edge = edgine::getInstance();
Edge->init(opts);
```
The **action** phase is the one which is needed for the samples' measurements upload.
First, the necessary sample is created:
```
temperature = new sample("temperature");
temperature->startDate = Edge->Api->getActualDate();
temperature->endDate = temperature->startDate;
testTemp = !testTemp;
temperature->value = getTemperature();
samples.push_back(temperature);
```
Then, they are sent to the database:
```
Edge->evaluate(samples);
samples.clear(); // after evaluated all samples delete them
```
Keep in mind that in this example the _getTemperature_ function is only a placeholder to show a possible Edge Engine usage. You can modify it for your own purpose.
### Arduino example
The Arduino example is slightly different from the PC one. Since the program is supposed to be used with an ESP32 board, the Wi-Fi connection is supported so that the board itself connects to a given SSID and, if the connection is lost, it also tries to reconnect.
Besides, this example uses three real sensors retrieving motion, light and temperature.
The interfacing with Measurify is the same as the PC example.
In order to have the ESP32 development kit you have to install it form the Arduino IDE board manager. If you don't find it you will probably have to set an additional URL for the board manager: <https://dl.espressif.com/dl/package_esp32_index.json>
### Implementation for other devices
If you want to use Edge Engine for your personal device, first you need to manage HTTP requests, so we suggest the use of a dedicated library.
Regarding the code, you need to add your device name to the _myDefines.h_ file and add your own implementation of the code everywhere there is an #ifdef directive. Those directives are used to manage different implementations of many code parts, such as the HTTP requests ones.
The files involved in this process should be the following ones:
- **PostVal.cpp**
- **PostVal.h**
- **edgine.h**
- **edgine.cpp**
- **script.cpp**
- **script.h**
- **window.h**
- **EdgeEngineLibrary.h**
- **myDefines.h**




