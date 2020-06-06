# LuaZlib
Zlib support for lua for Wireshark.

# Build Requirements
- Lua 5.2
- zlib

# Usage
```lua
require "LuaZlib"

-- Zlib deflated "abc"
local result = ZlibInflate("789c05c081100000000231d63e7f87dd3a024d0127", 21)
-- "616263"
print(result)
```
