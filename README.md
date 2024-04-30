# Hext
## Usage:
hext [Options]
#### Options:
- `-w<1 | 2 | 4 | 8>`: Byte Width of the Hex Values (Default: 1)
- `-h`: Print This Text
#### REPL Commands:
- `q | quit`: Quit
- `w<1 | 2 | 4 | 8>`: Change Hex Value Byte Width
- `h`: Print This Text

## Example Session:
User Input Indicated by '>'
```
hext
0x5A
>90
  Correct
0x12
>18
  Correct
0x27
>7
  Wrong, Correct: 39
0xA6
>w2
0x5AA6
>w8
0xB67340B8C0875AA6
>quit
```
## How to Build:

With Clang:
```
build\win32\llvm.bat release
```
With MSVC:
```
build\win32\msvc.bat release
```
With GCC:
```
build\win32\mingw.bat release
```

You May Also Use Any Other C11 Compliant Compiler like this:
```
cc src/build.c -o hext.exe
```



