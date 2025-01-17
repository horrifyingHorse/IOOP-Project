# Dealin' Cars
`./car-dealer`

## Prerequisite
- [cmake](https://cmake.org/download/#Binary:~:text=3.31.0%2Drc2.zip-,Binary%20distributions,-%3A)
-  `MinGW`

## Build this.Project
Clone this repository, in your terminal paste:
```bash
git clone https://github.com/horrifyingHorse/test
```
**For Windows:**

_**NOTE:**_ Dependency `ftxui` is configured for MinGW compiler and not [MSVC](https://github.com/ArthurSonzogni/FTXUI/releases/tag/v5.0.0#:~:text=ftxui%2D5.0.0%2Dwin64.zip). To configure library for MSVC extract [this](https://github.com/ArthurSonzogni/FTXUI/releases/tag/v5.0.0#:~:text=ftxui%2D5.0.0%2Dwin64.zip) zip and replace the contents of `Dependencies/win/` with it.

If you don't like powershell scripts like me, use cmake in VSCode.

Else, [Enable Scripting](https://superuser.com/questions/106360/how-to-enable-execution-of-powershell-scripts#:~:text=switch%20to%20the%20unrestricted%20mode%3A) and run the `.sh-to-.ps1` AI translated script on your computer. 
```poweshell
./build.ps1
```
_By default, `mingw32-make` is used to build MakeFiles_

After successful execution, the `./build` directory will contain the executable binary `./car-dealer.exe`

## Credits: FTXUI
TUI in this project is made with the amazing TUI library with an extremely simple API and incredibly neat implementation: [FTXUI](https://github.com/ArthurSonzogni/FTXUI) `<3`

<hr>

`Team:`<br>
- [@horrifyingHorse](https://github.com/horrifyingHorse)
- [@YuvaVarshith49](https://github.com/YuvaVarshith49)
- [@Arpitbanait](https://github.com/Arpitbanait)
- [@Nishitha-1516](https://github.com/Nishitha-1516)
