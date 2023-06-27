{
  "targets": [
    {
      "target_name": "myObject",
      "sources": [
        "src/myObject/myObject.cpp",
        "src/myObject/addon.cpp",
      ],
      "cflags_cc!": [
        "-fno-exceptions"
      ],
    },
    {
      "target_name": "map",
      "sources": [
        "src/map/map.cpp",
      ],
      "cflags_cc!": [
        "-fno-exceptions"
      ],
    },
    {
      "target_name": "get",
      "sources": [
        "src/try_catch/get.cpp",
      ],
      "cflags_cc!": [
        "-fno-exceptions"
      ],
    },
    {
      "target_name": "hello",
      "sources": [
        "src/helloworld/hello.cpp",
      ],
    },
    {
      "target_name": "add",
      "sources": [
        "src/add/add.cpp",
      ],
    },
    {
      "target_name": "runCallback",
      "sources": [
        "src/callback/callback.cpp",
      ],
    },
    {
      "target_name": "createObj",
      "sources": [
        "src/createObj/createObj.cpp",
      ],
    },
    {
      "target_name": "createFunc",
      "sources": [
        "src/createFunc/createFunc.cpp",
      ],
    },
    {
      "target_name": "echo",
      "sources": [
        "src/echo/echo.cc",
      ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ]
    },
    {
      "target_name": "nmap",
      "sources": [
        "src/map/nmap.cpp",
      ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ]
    }
  ]
}
