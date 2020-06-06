# LuaZlib
Zlib support for lua for Wireshark.

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

# Usage(Wireshark)
```lua
require "LuaZlib"
proto = Proto("Test", "My Test Protocol")

inflatedBytes = ProtoField.new("Inflated bytes", "test.bytes", ftypes.STRING)
proto.fields = { inflatedBytes }

function proto.dissector(buffer, pinfo, tree)
  pinfo.cols.protocol = "Test"

  local result = ZlibInflate(tostring(buffer()), buffer:len())
  local subtree = tree:add(proto, buffer())
  subtree:add(inflatedBytes, result)
end

tcp_table = DissectorTable.get("tcp.port")
tcp_table:add(1234, proto)
```
![image](https://user-images.githubusercontent.com/1202244/83941478-a3e2e100-a826-11ea-9603-27382f8a1f1e.png)


# Build Requirements
- Lua 5.2
- zlib
