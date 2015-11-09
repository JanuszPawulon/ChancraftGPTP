#pragma once

//Helper macro for converting #defined constants to C-strings
#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

//Helper macro for retrieving the size of an array
//Taken from http://blogs.msdn.com/b/the1/archive/2004/05/07/128242.aspx
template <typename T, size_t N>
char(&_ArraySizeHelper(T(&array)[N]))[N];
#define countof( array ) (sizeof( _ArraySizeHelper( array ) ))

//What is the plugin's ID?
//Plugin ID generated by MakeID.HTA (based on CRC32)
#define PLUGIN_ID 0x1B4D69B6

//What is the plugin's name (and version)?
#define PLUGIN_NAME "Chancraft QDP Plugin v1.0"
