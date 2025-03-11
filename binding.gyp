{
  "targets": [
    {
      "target_name": "system_monitor",
      "sources": [],
      "include_dirs": [
        "<!(node -p \"require('node-addon-api').include_dir\")"
      ],
      "dependencies": ["<!(node -p \"require('node-addon-api').gyp\")"],
      "cflags!": ["-fno-exceptions"],
      "cflags_cc!": ["-fno-exceptions"],
      "conditions": [
        ["'<(BUILD_OS)'=='linux'", { "sources": ["native/system_monitor_linux.cc"] }],
        ["'<(BUILD_OS)'=='mac'", {
          "sources": ["native/system_monitor_mac.cc"],
          "xcode_settings": {
            "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
            "CLANG_CXX_LIBRARY": "libc++",
            "MACOSX_DEPLOYMENT_TARGET": "10.14"
          }
        }],
        ["'<(BUILD_OS)'=='win'", { "sources": ["native/system_monitor_windows.cc"] }]
      ]
    }
  ]
}
