# S4ModApi [![GitHub release (latest by date)](https://img.shields.io/github/v/release/nyfrk/S4ModApi)](https://github.com/nyfrk/S4ModApi/releases/latest)
A modding library for Bluebyte's The Settlers 4. The goal of this project is to provide a API to mod developers such that they do not have to resort to reverse engineer the game themselves. 



## Features

* Create custom UI elements that the player can interact with
* Create player events programmatically
* Run code on specific events
* Dispatch access to common hooks fairly to mods thus reducing conflicts between them
* Simplify ASI mod creation by providing common functions for modding
* Manages a backward compatible ABI for the API
* Single header file
* Open Source



## Installation for Players

[Download a release](https://github.com/nyfrk/S4ModApi/releases) and unpack the S4ModApi.dll next to your S4_Main.exe. 



## Remarks for Modders

Note: The ABI is stable and backward compatible only if you link against the latest release. **Do not distribute your mod linking to a prerelease** (labeled with RC) since the ABI is not stable and not backward compatible. Your mod will break with upcoming releases. 

See the [hello world sample mod](https://github.com/nyfrk/S4ModApi/wiki/HelloWorldPlugin) on how to configure your project with the S4ModApi.

[The **reference** of the API is available in the Wiki](https://github.com/nyfrk/S4ModApi/wiki)

Please consider contributing features that that we currently do not offer back to this project. You can make sure that your mod stays compatible with upcoming and past releases of The Settlers 4, if you link to the S4ModApi.dll instead of directly linking to the S4_Main.exe. Moreover does it reduce the risk of conflicts between plugins. 



## Contribute

We are open for pull requests! 

Follow the [build instructions](BUILD.md) if you want to build the S4ModApi.dll and it's import library. 

Some source files are only provided as precompiled obj files. This is due to the following reasons.

* I do not have the license to make the hLib open source. 
* Some key features like the frame and mouse hook are closed source to encourage people to dynamically link to the S4ModApi.dll instead of reusing our hooks and making it private. This would defeat the purpose of the library whose goal is to ensure compatibility between mods. These source files will be released in the future when the use of the S4ModApi is more widely accepted. 



## Acknowledgments

Special thanks to the following contributors. Without their work this project would not be as far as it is today.

- [**MuffinMario**](https://github.com/MuffinMario) for the creation of [s4.muffinmar.io](https://s4.muffinmar.io/scripts/) and the reversal / documentation of the Lua interface including all function names, their parameters and many enumerations.
- [**Viciten**](https://github.com/Viciten) for the support of [alpha blended bitmaps](https://github.com/nyfrk/S4ModApi/commit/134d532b83d201f43f18b699d877021f512411d3).



## License

The S4ModApi project is licensed under the GNU Lesser General Public License version 3 (LGPLv3). See [COPYING.LESSER](COPYING.LESSER) file for details. 

