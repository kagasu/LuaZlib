# LuaZlib
Zlib support for lua for Wireshark.

# Build Requirements
- Lua 5.2
- zlib

# Download
https://github.com/kagasu/LuaZlib/releases

# Install
```
copy LuaZlib.dll "C:\Program Files\Wireshark\LuaZlib.dll"
```

# Usage
```lua
-- "C:\Program Files\Wireshark\plugins\test.lua"
require "LuaZlib"

-- Zlib deflated "abc"
local result = ZlibInflate("789c05c081100000000231d63e7f87dd3a024d0127", 21)
-- "616263"
print(result)
```
