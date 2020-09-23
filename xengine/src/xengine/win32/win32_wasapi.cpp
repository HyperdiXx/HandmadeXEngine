
#define WAUDIO_DLL_NAME "ole32.dll"

static const GUID IID_IAudioClient = { 0x1CB9AD4C, 0xDBFA, 0x4c32, 0xB1, 0x78, 0xC2, 0xF5, 0x68, 0xA7, 0x03, 0xB2 };
static const GUID IID_IAudioRenderClient = { 0xF294ACFC, 0x3146, 0x4483, 0xA7, 0xBF, 0xAD, 0xDC, 0xA7, 0xC2, 0x60, 0xE2 };
static const GUID CLSID_MMDeviceEnumerator = { 0xBCDE0395, 0xE52F, 0x467C, 0x8E, 0x3D, 0xC4, 0x57, 0x92, 0x91, 0x69, 0x2E };
static const GUID IID_IMMDeviceEnumerator = { 0xA95664D2, 0x9614, 0x4F35, 0xA7, 0x46, 0xDE, 0x8D, 0xB6, 0x36, 0x17, 0xE6 };
static const GUID PcmSubformatGuid = { STATIC_KSDATAFORMAT_SUBTYPE_PCM };

#ifndef AUDCLNT_STREAMFLAGS_AUTOCONVERTPCM
#define AUDCLNT_STREAMFLAGS_AUTOCONVERTPCM 0x80000000
#endif

#ifndef AUDCLNT_STREAMFLAGS_SRC_DEFAULT_QUALITY
#define AUDCLNT_STREAMFLAGS_SRC_DEFAULT_QUALITY 0x08000000
#endif

typedef struct Win32SoundDevice
{
    IMMDeviceEnumerator *device_enum;
    IMMDevice *device;

    IAudioClient *audio_client;
    IAudioRenderClient *audio_render_client;
    REFERENCE_TIME sound_buffer_duration;
    uint32 buffer_frame_count;
    uint32 channels;
    uint32 samples_per_second;
    uint32 latency_frame_count;

    bool32 is_initialized;
} Win32SoundDevice;

typedef struct Win32SoundBuffer
{



} Win32SoundBuffer;

#define CO_CREATE_INSTANCE(name) HRESULT name(REFCLSID rclsid, LPUNKNOWN *pUnkOuter, DWORD dwClsContext, REFIID riid, LPVOID *ppv)
typedef CO_CREATE_INSTANCE(CoCreateInstance_);
CO_CREATE_INSTANCE(CoCreateInstanceStub)
{
    return 1;
}

global CoCreateInstance_ *CoCreateInstanceProc = CoCreateInstanceStub;

#define CO_INITIALIZE_EX(name) HRESULT name(LPVOID pvReserved, DWORD dwCoInit)
typedef CO_INITIALIZE_EX(CoInitializeEx_);
CO_INITIALIZE_EX(CoInitializeExStub)
{
    return 1;
}
global CoInitializeEx_ *CoInitializeExProc = CoInitializeExStub;

internal bool32 Win32LoadWASAPIDLL()
{
    HMODULE dll = LoadLibraryA(WAUDIO_DLL_NAME);

    if (dll)
    {
        CoCreateInstanceProc = (CoCreateInstance_ *)GetProcAddress(dll, "CoCreateInstance");
        CoInitializeExProc = (CoInitializeEx_ *)GetProcAddress(dll, "CoInitializeEx");
    }
}

internal bool32 Win32InitWASAPI(Win32SoundDevice *device_out)
{
    CoInitializeExProc(0, COINIT_SPEED_OVER_MEMORY);
    
    HRESULT result = CoCreateInstanceProc(CLSID_MMDeviceEnumerator,
                                          0,
                                          CLSCTX_ALL,
                                          IID_IMMDeviceEnumerator,
                                          (LPVOID *)(&device_out->device_enum));
    
    if (!FAILED(result))
    {

        //device_out->device_enum->lpVtbl->GetDefaultAudioEndpoint(device_out->device_enum,
        //                                                     eRender,
        //                                                     eConsole,
        //                                                     &device_out->device);
    }
    else
    {

    }
}