#include <mach/mach.h>
#include <napi.h>
#include <sys/sysctl.h>

Napi::Object GetMemoryInfo(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::Object result = Napi::Object::New(env);

    int64_t totalMemory = 0;
    size_t size = sizeof(totalMemory);
    sysctlbyname("hw.memsize", &totalMemory, &size, NULL, 0);

    vm_size_t page_size;
    mach_port_t mach_port = mach_host_self();
    vm_statistics64_data_t vm_stats;
    mach_msg_type_number_t count = sizeof(vm_stats) / sizeof(natural_t);

    if (host_page_size(mach_port, &page_size) == KERN_SUCCESS &&
        host_statistics64(mach_port, HOST_VM_INFO, (host_info64_t)&vm_stats,
                          &count) == KERN_SUCCESS) {
        int64_t freeMemory = (int64_t)vm_stats.free_count * (int64_t)page_size;
        int64_t usedMemory = totalMemory - freeMemory;

        result.Set("total", Napi::Number::New(env, totalMemory));
        result.Set("free", Napi::Number::New(env, freeMemory));
        result.Set("used", Napi::Number::New(env, usedMemory));
    }

    return result;
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set(Napi::String::New(env, "getMemoryInfo"),
                Napi::Function::New(env, GetMemoryInfo));
    return exports;
}

NODE_API_MODULE(system_monitor, Init)
