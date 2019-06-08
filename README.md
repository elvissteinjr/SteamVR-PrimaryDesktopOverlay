# SteamVR-PrimaryDesktopOverlay
Crops the Steam Desktop overlay in SteamVR to the content of the primary display.

This is a crude but working proof-of-concept application that would love to be replaced by a highly polished and customizable solution in the future.

# What it does
- Crop the Steam Desktop overlay to your primary screen
- Do so automatically on SteamVR launch after the first use

# What it does not
- Anything else

# Usage
Make sure SteamVR is running, then execute SteamVR-PrimaryDesktopOverlay.exe.

SteamVR-PrimaryDesktopOverlay will register itself as an overlay application to SteamVR and run automatically on following SteamVR launches. If you move the files of this application you'll have to repeat the first-run steps.

## "My overlay is tiny, what do?"
Use [OpenVR-AdvancedSettings](https://github.com/OpenVR-Advanced-Settings/OpenVR-AdvancedSettings/) to scale and position the desktop overlay to your liking.

## "My overlay isn't where it's supposed to be after launching SteamVR!"
Click on the OpenVR-AdvancedSettings overlay to make it restore your desktop overlay settings once again.

## "My overlay is blocking all overlay buttons, I can't switch!"
Bringing up the System menu (bottom left button) will hide all overlays, giving you a chance to access the overlay buttons.

# Building
Just compile main.cpp and link it with openvr_api.dll

For example: g++ -o SteamVR-PrimaryDesktopOverlay.exe main.cpp openvr_api.dll

# License
SteamVR-PrimaryDesktopOverlay is licensed under WTFPL 2.0.

Do what you want with it.

For the OpenVR API header and library, see LICENSE-OpenVR.txt.