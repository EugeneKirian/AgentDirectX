[![ko-fi](https://ko-fi.com/img/githubbutton_sm.svg)](https://ko-fi.com/C0C619KV5Z)
## Agent DirectX

### Project
Agent DirectX is a set of light-weight DirectX wrappers to be used as a foundation for development of other software. The further and separate development might include, but not limited to:

1. Development of loggers.
2. Development of compatibility wrappers for particular software/games.
3. Development of debugging and observation tools, and
4. Development of helpers and analysis tools for reverse engineering.

### Scope
Agent DirectX consists of DirectX wrappers for the following:
* [ ] DirectX 1-7
	* [x] Direct3D (Immediate Mode)
	- [ ] Direct3D (Retained Mode)
	* [x] DirectDraw
	* [ ] DirectInput
	* [ ] DirectMusic
	* [ ] DirectPlay
	* [ ] DirectSetup
	* [x] DirectSound
* [ ] DirectX 8
	* [x] Direct3D
	* [ ] DirectInput
	* [ ] DirectMusic
	* [ ] DirectPlay
	* [ ] DirectSetup
	* [ ] DirectShow
	* [x] DirectSound
* [ ] DirectX 9
	* [ ] Direct3D
	* [ ] DirectInput
	* [ ] DirectSetup
	* [x] DirectSound
	* [ ] XAudio2
	* [ ] XInput

### Requirements & Dependencies
Development Environment:
1. [Microsoft Visual Studio](https://visualstudio.microsoft.com/downloads/)

DirectX SDKs:
1. [Microsoft DirectX 7.0 SDK](https://archive.org/details/dx7sdk-7001)
2. [Microsoft DirectX 8.1 SDK](https://archive.org/details/dx81sdk_full)
3. [Microsoft DirectX SDK 9.0 (June 2010)](https://www.microsoft.com/en-us/download/details.aspx?id=6812)

Other:
1. [DXGUID](https://github.com/EugeneKirian/DXGUID)

### Derivatives
1. [Log Agent DirectX](https://github.com/EugeneKirian/LogAgentDirectX)

### Code Style & Compatibility
The code written in a way to contain the minimum of external dependencies, and to compile with Microsoft Visual Studio 6.0 C/C++ Compiler for legacy compatibility with Microsoft Windows XP. The repository has the corresponding projects to compile for the old platforms.

### Legal
DirectX, Direct3D, DirectDraw, DirectSound, and others are trademarks of their respective owners.
