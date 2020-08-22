# S4ModApi Build Instructions

To build the S4ModApi project, you will need Visual Studio 2019 and the build tools v141_xp and v142 installed.

It is also sufficient to only have build tools v142 installed if you only want to create debug builds. The release is build using the v141_xp build tools.



## IDE Setup

1. Choose and download a Version of Visual Studio from [here](https://visualstudio.microsoft.com/de/downloads/). If you need help installing it, follow [these instructions](https://docs.microsoft.com/en-us/visualstudio/install/install-visual-studio?view=vs-2019).
2. Choose the following workloads during installation: 
   * **Desktop development with C++**
   * **C++ Windows XP support for VS 2017**

This will install the latest MSVC Buildtools for x64/x86 v142 and v141_xp. 



## Build Configurations

The project can be build using one of the following configurations.

| Configuration | Description                                                  |
| ------------- | ------------------------------------------------------------ |
| Release       | Create a release build using the v141_xp build tools. Logging and console is disabled. |
| Debug         | Create a debug build using the v141_xp build tools. Logging and console is enabled. |
| Debug142      | Create a debug build using the v142 build tools. Logging and console is enabled. |

Note: If you only have the build tools v142 installed, make sure to change the configuration to Debug142. 

To build all configurations in one step do the following.

1. Open the **S4ModApi.sln** in Visual Studio 2019.
2. In the top menu select **Build** and click **Batch build**.
3. Make sure all configurations are selected and click **Build**.



## Deployment

You can create a deploy script in the Release, Debug, Debug142 output directories. It will be automatically called when a build finished. You can use it to copy the S4ModApi.dll to your game installation.

Example of a deploy.bat:

```shell
copy %0\..\S4ModApi.dll "G:\Programme\The Settlers History Collection\The Settlers IV\"
exit 0
```



## Packaging

Run the PackageRelease.bat script to create a zip file containing the following files.

| File         | Description                                                  |
| ------------ | ------------------------------------------------------------ |
| LICENSE.md   | MIT license file for the binary distribution.                |
| S4ModApi.dll | The S4ModApi library that players must install.              |
| S4ModApi.h   | The header that mod developers must install.                 |
| S4ModApi.lib | An import library that modders can use to link against S4ModApi.dll. |



