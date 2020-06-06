#include <lua.hpp>
#include <zlib.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <ios>
#include <iomanip>

#pragma comment(lib, "lua52.lib")

constexpr auto BUFFER_SIZE = 0x4000;

void GetByteArary(uint8_t* src, uint8_t* dst)
{
    auto srclength = strlen(reinterpret_cast<char*>(src));
    for (auto i = 0; i < srclength; i += 2)
    {
        uint32_t x;
        sscanf_s(reinterpret_cast<char*>(src + i), "%02x", &x);
        dst[i / 2] = x;
    }
}

std::string GetByteArrayString(uint8_t* src, int length)
{
    std::stringstream ss;
    for (auto i = 0; i < length; i++)
    {
        ss << std::hex << std::right << std::setfill('0') << std::setw(2) << static_cast<int>(src[i]);
    }

    return ss.str();
}

int ZlibInflate(lua_State* L)
{
    auto str = luaL_checkstring(L, 1);
    auto srclength = strlen(const_cast<char*>(str));
    auto dstLength = srclength / 2;
    auto data = new uint8_t[dstLength];

    GetByteArary(reinterpret_cast<uint8_t*>(const_cast<char*>(str)), data);

    auto size = static_cast<unsigned int>(luaL_checkinteger(L, 2));
    auto outBuf = new unsigned char[BUFFER_SIZE]();
    std::stringstream outStream;
    z_stream zStream{ 0 };
    auto ret = inflateInit(&zStream);

    zStream.avail_in = size;
    zStream.next_in = data;
    do
    {
        zStream.next_out = outBuf;
        zStream.avail_out = BUFFER_SIZE;
        ret = inflate(&zStream, Z_NO_FLUSH);
        auto outSize = BUFFER_SIZE - zStream.avail_out;
        outStream.write(reinterpret_cast<char*>(outBuf), outSize);
    } while (zStream.avail_out == 0);

    inflateEnd(&zStream);

    auto result = GetByteArrayString(reinterpret_cast<uint8_t*>(const_cast<char*>(outStream.str().c_str())), static_cast<int>(outStream.str().size()));

    lua_pushstring(L, result.c_str());

    return 1;
}

int luaopen_LuaZlib(lua_State* L)
{
    lua_register(L, "ZlibInflate", ZlibInflate);
    return 0;
}
