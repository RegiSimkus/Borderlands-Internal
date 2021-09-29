// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <Windows.h>
#include <iostream>
#include "Borderlands.h"
#include "IncDX9.h"
#include "Drawing.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui_impl_dx9.h"
#include "math.h"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void* d3d9Device[119];
BYTE EndSceneBytes[7]{ 0 };
tEndScene oEndScene = nullptr;
extern LPDIRECT3DDEVICE9 pDevice = nullptr;

// ImGui

// Forward declare message handler from imgui_impl_win32.cpp
//extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);

bool bWndProcHooked = false;
WNDPROC oWndProc;



bool bDestroyImGui = false;
bool bInitializedImGui = false;
bool bDrawImGui = true;
LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

    if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
        return true;

    return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

void UpdateOverlayState(bool MenuOpen, HWND ownd)
{
    //We call this function only when we open or close the menu
    long style = GetWindowLong(ownd, GWL_EXSTYLE);
    if (MenuOpen)
    {
        style &= ~WS_EX_LAYERED;
        SetWindowLong(ownd,
            GWL_EXSTYLE, style);
        SetForegroundWindow(ownd);
    }
    else
    {
        style |= WS_EX_LAYERED;
        SetWindowLong(ownd,
            GWL_EXSTYLE, style);
    }
    //Credits go to someone from UC
}

void InitImGui(LPDIRECT3DDEVICE9 pDevice)
{

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
    ImGui_ImplWin32_Init(window);
    ImGui_ImplDX9_Init(pDevice);
}

void APIENTRY hkEndScene(LPDIRECT3DDEVICE9 o_pDevice) {
    if (!pDevice)
        pDevice = o_pDevice;

    DrawFilledRect(10, 10, 20, 20);

    if (!bInitializedImGui)
    {
        InitImGui(pDevice);
        bInitializedImGui = true;
    }

    if (GetAsyncKeyState(VK_INSERT) & 1)
    {
        bDrawImGui = !bDrawImGui;
        //UpdateOverlayState(bDrawImGui, window);
    }

    if (bDrawImGui && !bDestroyImGui)
    {

        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Test Window");
        ImGui::End();

        ImGui::EndFrame();
        ImGui::Render();
        ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
    }


    if (bDestroyImGui)
    {
        ImGui_ImplDX9_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();
    }

    oEndScene(pDevice);
}


Game* g_Game = new Game();
BOOL WINAPI MainThread(HMODULE hModule)
{

    //if (GetD3D9Device(d3d9Device, sizeof(d3d9Device))) {

    //    memcpy(EndSceneBytes, (char*)d3d9Device[42], 7);
    //    oEndScene = (tEndScene)TrampHook((char*)d3d9Device[42], (char*)hkEndScene, 7);
    //    oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
    //}

    
    FILE* f;
    AllocConsole();
    SetConsoleTitleA("Borderlines 2 - Debug Console");
    freopen_s(&f, "CONOUT$", "w", stdout);
    freopen_s(&f, "CONIN$", "r", stdin);


    std::cout << "=====================\n";
    std::cout << "==Initializing Hack==\n";
    std::cout << "=====================\n";


    //std::cout << "Hooked EndScene\n";
    //std::cout << "=====================\n";

    while (!(GetAsyncKeyState(VK_END)))
    {

        if (GetAsyncKeyState(VK_F1) & 1)
        {
            std::cout << "Set rifle ammo to 500\n";
            g_Game->SetRifleAmmo(500);
        }

        if (GetAsyncKeyState(VK_F2) & 1)
        {
            std::cout << "XP Addy: " << (g_Game->GetXPAddy()) << "\n" << g_Game->GetXP() << "\n"; // debugging stuff
        }

        if (GetAsyncKeyState(VK_F3) & 1)
        {
            std::cout << "Increased XP!\n";
            g_Game->SetXP(g_Game->GetXP() + 1);
            std::cout << "XP: " << (g_Game->GetXP()) << "\n";
        }

        if (GetAsyncKeyState(VK_F4) & 1)
        {
            std::cout << "Increased Health by 1000!\n";
            g_Game->SetHealth(g_Game->GetHealth() + 1000);
        }

        if (GetAsyncKeyState(VK_F5) & 1)
        {
        //    std::cout << "Cur Keys: " << g_Game->GoldenKeys->GetKeys() << "\n";
        //    std::cout << "Encrypted Value: " << g_Game->GoldenKeys->IntToKeys(g_Game->GoldenKeys->GetKeys()) << "\n";
        //    std::cout << "150 Keys Encrypted: " << g_Game->GoldenKeys->IntToKeys(150) << "\n";
        //    std::cout << "Param: " << g_Game->GoldenKeys->GetKeys() + 150 << "\n";
        //    std::cout << "Cur Encrypted Keys + 150 Encrypted: " << g_Game->GoldenKeys->IntToKeys(g_Game->GoldenKeys->GetKeys() + 150) << "\n";
            g_Game->GoldenKeys->AddKeys(1);
        }

        Sleep(50);
    }
    bDestroyImGui = true;
    std::cout << "Aborting...\n";


    //Patch((BYTE*)d3d9Device[42], EndSceneBytes, 7);

    if (f) fclose(f);
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
    return TRUE;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        while (window == NULL)
            window = GetProcessWindow();

        Sleep(20);
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, nullptr));
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

