# Designing a Musical Software Synthesizer: MKUltra

![Image of MKUltra synthesizer user interface](https://chettrick.github.io/MKUltra/images/image22.png)

## Building the Project on Windows using Visual Studio 2019
Note: [Visual Studio 2019](https://visualstudio.microsoft.com/vs/) must be installed to build this project.

### [Download](https://github.com/chettrick/MKUltra/archive/master.zip) the Repository
* Click the green "Clone or download" button.
* Click "Download ZIP".
* Navigate to the downloaded file (named "MKUltra-master.zip") and
  extract the archive by right-clicking on the file and selecting "Extract All...".
  
### Open the Project in Visual Studio 2019
* Navigate to the "MKUltra" directory. This is the project's root directory.
* Navigate to the build directory "Builds\VisualStudio2019".
* Open the file "MKUltra.sln" in Visual Studio 2019.

### Debug / Run the Project
* Click on "Local Windows Debugger" or press "F5" to start running and debugging the project.

### Building a Standalone Executable
* Change the project configuration from "Debug" to "Release" in the
  dropdown menu to the left of "Local Windows Debugger".
* Press "F7" to build the project, or select it from the menu "Build -> Build Solution".
* The executable "MKUltra.exe" is found in the directory
  "...\MKUltra\Builds\VisualStudio2019\x64\Release\App".
  * This executable can be copied and pasted anywhere, and used from that location,
    i.e., put on the Desktop and ran from there.


## Developing the Project on Windows using Visual Studio 2019
Note: Installing [Git on Windows](https://git-scm.com/downloads) with Git Bash is recommended.

### Clone the Repository
``` shell
$ cd <some directory>
$ git clone https://github.com/chettrick/MKUltra
```

### Open the Project in Visual Studio 2019
* Navigate to the "MKUltra" directory. This is the project's root directory.
* Navigate to the build directory "Builds/VisualStudio2019".
* Open the file "MKUltra.sln" in Visual Studio 2019

### Debug / Run the Project
* Click on "Local Windows Debugger" or press "F5" to start running and debugging the project.


## Using the Synthesizer

### Via the GUI
* The on-screen keyboard can be used to play via a mouse.
* The computer's qwerty keyboard can be used to play. Polyphony works (multiple keys play simultaneously).
  * The top row keys are the synthesizer's black keys.
  * The middle row keys are the synthesizer's white keys.
  
### Via a Hardware MIDI Keyboard / Controller
* A MIDI card, USB MIDI interface, or a USB MIDI keyboard is needed.
  For example, something like [this](https://www.akaipro.com/mpk-mini-mkii).
* The keyboard needs to be plugged in and drivers installed, etc, before starting the synthesizer.
  The synthesizer does not yet auto-negotiate newly attached hardware.
* Select the desired MIDI keyboard from the dropdown menu on the synthesizer.

### Via a Virtual Software MIDI Keyboard / Controller
* Virtual MIDI devices on Windows need to go through a *loopback device*,
  such as [loopMIDI](http://www.tobias-erichsen.de/software/loopmidi.html).
* A virtual MIDI keyboard, such as [Virtual MIDI Piano Keyboard](http://vmpk.sourceforge.net/),
  configured to use the loopMIDI interface, is used to send MIDI commands to the synthesizer.
* Notation software, such as [MuseScore](https://musescore.org/),
  can be used to generate MIDI commands to send to the synthesizer, via VMPK and loopMIDI.
* Select the desired MIDI keyboard from the dropdown menu on the synthesizer.
