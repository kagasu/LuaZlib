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

protocolId = ProtoField.new("Protocol id", "test.id", ftypes.STRING)
inflatedBytes = ProtoField.new("Inflated bytes", "test.bytes", ftypes.STRING)
proto.fields = { protocolId, inflatedBytes }

function proto.dissector(buffer, pinfo, tree)
  pinfo.cols.protocol = "Test"

  local result = ZlibInflate(buffer():bytes():tohex(), buffer:len())
  local bytes = ByteArray.new(result)
  local tvb = ByteArray.tvb(bytes, "my tvb")

  local subtree = tree:add(proto, buffer())
  subtree:add(protocolId, tvb(0, 1):uint())
  subtree:add(inflatedBytes, bytes:tohex())
end

tcp_table = DissectorTable.get("tcp.port")
tcp_table:add(1234, proto)
```
![image](https://user-images.githubusercontent.com/1202244/83941478-a3e2e100-a826-11ea-9603-27382f8a1f1e.png)

# Build Requirements
- Lua 5.2
- zlib
