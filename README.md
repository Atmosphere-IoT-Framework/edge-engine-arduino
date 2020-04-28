Edge Engine
=================
### Table of contents
- [Overview](https://github.com/lucalazzaroni/edge-edgine#Introduction)
- [Installation](https://github.com/lucalazzaroni/edge-edgine#Installation)
    - [Prerequisites](https://github.com/lucalazzaroni/edge-edgine#Prerequisites)
        - [Windows](https://github.com/lucalazzaroni/edge-edgine#Windows)
        - [Arduino](https://github.com/lucalazzaroni/edge-edgine#Arduino)
    - [Windows installation](https://github.com/lucalazzaroni/edge-edgine#Windows-installation)
    - [Arduino installation](https://github.com/lucalazzaroni/edge-edgine#Arduino-installation)
- [Usage](https://github.com/lucalazzaroni/edge-edgine#Usage)
    - [PC example](https://github.com/lucalazzaroni/edge-edgine#PC-example)
    - [Arduino example](https://github.com/lucalazzaroni/edge-edgine#Arduino-example)
## Overview
The idea behind this project is to create a generic runtime system and therefore compatible in various circumstances, independent of the hardware and suitable for simple devices such as integrated boards.
This engine can process data flows from sensors through scripts or execute commands using the actuators connected to it.
Scripts are made up of a set of known operations which can also be used together to perform even complex calculations on each measurement flow. The Edge Engine can be configured to retrieve scripts online (from a cloud) to be run locally and periodically check whether these have changed or if there are new scripts to be executed.
In order to work and to exploit all its potential, the engine needs therefore an online endpoint through which it can be programmed. It is not tied to any proprietary platform, the provider can choose the cloud service to which the engine will be connected. 
In this specific project, Atmosphere will be used: a cloud-based, measurement-oriented platform created by the Elios Lab of the University of Genoa to manage intelligent objects in IoT ecosystems.
## Installation
### Prerequisites
##### Windows
- A C++14 compiler (GCC 8.1.0 or newer suggested)
- [MINGW64](http://www.mingw.org/)
- [MSYS2](https://www.msys2.org/)
- [POCO](https://pocoproject.org/) headers and libraries 
##### Arduino
- [Arduino IDE](https://www.arduino.cc/en/main/software) or [VSCode](https://code.visualstudio.com/) + [Arduino extension](https://marketplace.visualstudio.com/items?itemName=vsciot-vscode.vscode-arduino)
- [Adafruit IO](https://github.com/adafruit/Adafruit_IO_Arduino)
- [ArduinoHttpClient](https://github.com/arduino-libraries/ArduinoHttpClient)
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
If you intend to use another compiler different from the GCC one, you can use other package manager such as [VCPKG](https://github.com/microsoft/vcpkg) for windows, or [Conan](https://conan.io/).
### Arduino installation
All the required libraries must be inside the libraries folder which can be found by looking at the IDE settings (sketches folder path).
Also the Edge Engine library needs to be inside the same folder. If you encounter any problem regarding the _connection_windows_ class or the _APIRest_windows_ class, delete them together with their headers from the aforementioned folder since if you compile for Arduino you do not need them.
## Usage
Inside this repository you can find two examples relative to the Edge Engine library under the _examples_ folder. One of them is for the Arduino board ESP32 and the other is for PCs.
In this section you will learn how to make both of them work correctly.
Both examples have a common base.
First, they check if there is an internet connection, then, if yes, they proceed with the authentication phase: a POST request containing username and password is sent and, if the process is successful, a JWT is received. This JWT is needed to send the future HTTP requests.
Then _samples_ are created, containing the parameters read by the sensors taken into consideration. These samples, characterized by a feature name, a date, and a value are finally sent to Atmosphere.
### PC example
The PC example simulates a temperature sensor behavior and it uses the Atmosphere platform as online server.
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
-lPocoFoundation -lPocoUtil -lPocoNet
```
### Arduino example
The Arduino example is slightly different from the PC one. Since the program is supposed to be used with an ESP32 board, the Wi-Fi connection is supported so that the board itself connects to a given SSID and, if the connection is lost, it also tries to reconnect.
Besides, this example uses three real sensors retrieving motion, light and temperature.
The interfacing with Atmosphere is the same as the PC example.
In order to have the ESP32 development kit you have to install it form the Arduino IDE board manager. If you don't find it you will probably have to set an additional URL for the board manager: <https://dl.espressif.com/dl/package_esp32_index.json>





