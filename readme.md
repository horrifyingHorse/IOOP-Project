# Test
`./car-dealer`

## Prerequisite
- [cmake](https://cmake.org/download/#Binary:~:text=3.31.0%2Drc2.zip-,Binary%20distributions,-%3A)
- for windows `MinGW`

## Build this.Project
Clone this repository, in your terminal paste:
```bash
git clone https://github.com/horrifyingHorse/test
```
**For Linux:**
```bash
chmod +x ./build.sh
./build.sh
```
If you don't have `cmake` installed, the build script will `apt install` it.
After successful execution, the `./build` directory will contain the executable binary `./car-dealer`

**For Windows:**

_**NOTE:**_ Dependency `ftxui` is configured for MinGW compiler and not [MSVC](https://github.com/ArthurSonzogni/FTXUI/releases/tag/v5.0.0#:~:text=ftxui%2D5.0.0%2Dwin64.zip). To configure library for MSVC extract [this](https://github.com/ArthurSonzogni/FTXUI/releases/tag/v5.0.0#:~:text=ftxui%2D5.0.0%2Dwin64.zip) zip and replace the contents of `Dependencies/win/` with it.

If you don't like powershell scripts like me, use cmake in VSCode.

Else, [Enable Scripting](https://superuser.com/questions/106360/how-to-enable-execution-of-powershell-scripts#:~:text=switch%20to%20the%20unrestricted%20mode%3A) and run the `.sh-to-.ps1` AI translated script on your computer. 
```poweshell
./build.ps1
```
_By default, `mingw32-make` is used to build MakeFiles_

After successful execution, the `./build` directory will contain the executable binary `./car-dealer.exe`

### build.* flags
-b: build only
