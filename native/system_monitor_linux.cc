#include <napi.h>
#include <sys/sysinfo.h>

Napi::Object GetMemoryInfo(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::Object result = Napi::Object::New(env);

    struct sysinfo memInfo;
    sysinfo(&memInfo);

    long totalMemory = memInfo.totalram * memInfo.mem_unit;
    long freeMemory = memInfo.freeram * memInfo.mem_unit;
    long usedMemory = totalMemory - freeMemory;

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
