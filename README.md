# lua_curl 🛜

![Build](https://img.shields.io/github/actions/workflow/status/MrEntrasil/luacurl/cmake-single-platform.yml?branch=main)
![License](https://img.shields.io/github/license/MrEntrasil/luacurl/blob/main/LICENSE)

### ⚠️ **under in development!**
**lua_curl** is a minimalist API that implements the curl package for lua<br>
Docs are avaible in /docs directory<br>

## Summary
- [BuildInstructions](#BuildInstructions)
- [Usage](#Usage)

## BuildInstructions

Building the source & generating a binary file(so, dll or dylib):
```bash
cmake . -B build
cmake --build build
```
You can also specify the lua/libcurl path
```bash
cmake . -B build -DLUA_LIBRARIES=/path/to/lua_lib -DLUA_INCLUDE_DIR=/path/to/lua_include
```
```bash
cmake . -B build -DCURL_LIBRARIES=/path/to/curl_lib -DCURL_INCLUDE_DIR=/path/to/curl_include
```

and **DONE!** your binary file will be in /build directory

## Usage

luacurl.* can be **require** by:
```lua
require("luacurl") -- assuming you put the file in the root directory
```

luacurl functions **always** begin with `luacurl_*`
