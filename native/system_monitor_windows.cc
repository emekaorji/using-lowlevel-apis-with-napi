#include <napi.h>
#include <windows.h>

Napi::Object GetMemoryInfo(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::Object result = Napi::Object::New(env);

    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);

    int64_t totalMemory = memInfo.ullTotalPhys;
    int64_t freeMemory = memInfo.ullAvailPhys;
    int64_t usedMemory = totalMemory - freeMemory;

    result.Set("total", Napi::Number::New(env, totalMemory));
    result.Set("free", Napi::Number::New(env, freeMemory));
    result.Set("used", Napi::Number::New(env, usedMemory));

    return result;
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set(Napi::String::New(env, "getMemoryInfo"),
                Napi::Function::New(env, GetMemoryInfo));
    return exports;
}

NODE_API_MODULE(system_monitor, Init)
