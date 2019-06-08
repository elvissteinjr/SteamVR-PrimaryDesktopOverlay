/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ for more details. */

#include <cstdio>   //Could use iostream, but I want to the keep the executable small for no reason
#include <string>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "openvr.h"

int main()
{
    //Calculate UV for the primary screen

    //Primary Screen is always at virtual 0,0
    //If a screen is above or to the left of it, their coordinates are negative
    float primary_x = GetSystemMetrics(SM_XVIRTUALSCREEN) * -1;
    float primary_y = GetSystemMetrics(SM_YVIRTUALSCREEN) * -1;
    float primary_w = GetSystemMetrics(SM_CXSCREEN);
    float primary_h = GetSystemMetrics(SM_CYSCREEN);
    float total_w   = GetSystemMetrics(SM_CXVIRTUALSCREEN);
    float total_h   = GetSystemMetrics(SM_CYVIRTUALSCREEN);

    vr::VRTextureBounds_t tex_bounds;

    tex_bounds.uMin = primary_x / total_w;
    tex_bounds.vMin = primary_y / total_h;
    tex_bounds.uMax = tex_bounds.uMin + (primary_w / total_w);
    tex_bounds.vMax = tex_bounds.vMin + (primary_h / total_h);

    //Init OpenVR
    vr::EVRInitError vr_error;
    vr::IVRSystem* vr_system = vr::VR_Init(&vr_error, vr::VRApplication_Overlay);

    if (!vr_system)
    {
        printf("Failed to load OpenVR: %i", (int)vr_error);
        return -1;
    }

    //Register application so it will be launched automagically next time
    if (!vr::VRApplications()->IsApplicationInstalled("elvissteinjr.PrimaryDesktopOverlay"))
    {
        //This is supposed to be just a simple crude application, so we'll make due with this for getting the application path (this likely won't work on unicode paths)
        DWORD length = GetCurrentDirectory(0, NULL);
        char* path   = new char[length];
        length       = GetCurrentDirectory(length, path);

        if (length != 0)
        {
            std::string path_str(path);
            path_str.append("\\manifest.vrmanifest");

            vr::EVRApplicationError app_error;
            app_error = vr::VRApplications()->AddApplicationManifest(path_str.c_str());

            if (app_error == vr::VRApplicationError_None)
            {
                vr::VRApplications()->SetApplicationAutoLaunch("elvissteinjr.PrimaryDesktopOverlay", true);
            }
        }

        delete[] path;
    }

    //Look for Steam's Desktop overlay
    int tries = 0;
    vr::VROverlayHandle_t overlay_handle;
    vr::EVROverlayError overlay_error;
    overlay_error = vr::VROverlay()->FindOverlay("valve.steam.desktop", &overlay_handle);

    //If we can't find the overlay yet, keep trying for a minute every second
    while ( (overlay_error != vr::VROverlayError_None) && (tries < 60) )
    {
        Sleep(1000);
        tries++;
        overlay_error = vr::VROverlay()->FindOverlay("valve.steam.desktop", &overlay_handle);
    }

    if (overlay_error == vr::VROverlayError_None)
    {
        //Set the previously calculated UV coordinates and hope it works
        vr::VROverlay()->SetOverlayTextureBounds(overlay_handle, &tex_bounds);

        if (overlay_error != vr::VROverlayError_None)
        {
            //Guess it didn't...
            printf("Error setting bounds: %i", (int)overlay_error);
        }
    }

    vr::VR_Shutdown();

    return 0;
}
