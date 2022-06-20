# **POEX**
`POEX` is abbreviated from Portable Executable

- ### What is it?

<span style="color:rgba(255, 99, 71, 1)">POEX</span> describes work with the structure of executable (image) files and object files under the Windows family of operating systems. These files are referred to as Portable Executable (PE) and Common Object File Format (COFF) files, respectively.
`POEX` is a library to access, load and manipulate PE files.

- ### PE Feature Support

| PE Structures | Support Status | Description |
| :---         |     :---:      |  :---        |
| DOS Header   | Yes           |  Read, Write, Modify |
| File Header   | Yes            |  Read, Write, Modify |
| Optional Header   | Yes            |  Read, Write, Modify |
| Section Header   | Yes            |  Read, Write, Modify |
| Data Directories Header   | Yes            |  Read, Write, Modify |
| Export Table (Data Directory)   | Yes           | Read, Write, Modify |
| Import Table (Data Directory)   | Not Yet (in progress)           |   |
| Resource Table (Data Directory)   | Not Yet (in progress)          |   |
| Exception Table (Data Directory)   | Not Yet (in progress)          |   |
| Certificate Table (Data Directory)   | Not Yet (in progress)           |   |
| Base Relocation Table (Data Directory)   | Not Yet (in progress)           |   |
| Debug (Data Directory)   | Not Yet (in progress)           |   |
| Architecture (Data Directory)   | Not Yet (in progress)           |   |
| Global Ptr (Data Directory)   | Not Yet (in progress)           |   |
| TLS Table (Data Directory)   | Not Yet (in progress)          |   |
| Load Config Table (Data Directory)   | Not Yet (in progress)          |   |
| Bound Import (Data Directory)   | Not Yet (in progress)          |   |
| IAT (Data Directory)   | Not Yet (in progress)          |   |
| Delay Import Descriptor (Data Directory)   | Not Yet (in progress)          |   |
| CLR Runtime Header (Data Directory)   | Not Yet (in progress)          |   |
| Reserved (Data Directory)   | Not Yet (in progress)          |   |


- ### How to Build the Library?


1. Clone the repository

   - *git clone [https://github.com/AFP33/POEX.git](https://github.com/AFP33/POEX.git)*

2. Open Visual Studio and just Build it

   - *you need at least C++14*
   - *minimum SDK is 10.0*

 3. Use the output `POEX.lib` in your project


- ### Examples

*Open PE File:*
```C++
#include <iostream>
#include <POEX.h>  // include POEX header

int main()
{
    auto pe = POEX::PE(L"1.exe");

    // Other stuff here
    return 0;
}
```

*Access to DOS Header:*
```C++
#include <iostream>
#include <POEX.h>  // include POEX header

int main()
{
    auto pe = POEX::PE(L"1.exe");

    // Access to Image DOS Header
    auto dos = pe.GetImageDosHeader();

    // Access to 'e_magic' and 'e_lfanew' and print them in console as hex;
    std::cout << "Magic: 0x" << std::hex << dos.E_magic() << std::endl;
    std::cout << "e_lfanew: 0x" << std::hex << dos.E_lfanew() << std::endl << std::endl;

    // Change 'e_magic' and 'e_lfanew' values
    dos.E_magic(23118);
    dos.E_lfanew(249);

    /// Try to print again 'e_magic' and 'e_lfanew' field the structure
    std::cout << "Magic: 0x" << std::hex << dos.E_magic() << std::endl;
    std::cout << "e_lfanew: 0x" << std::hex << dos.E_lfanew() << std::endl;

    return 0;
}
```

*Save change as original file or new one:*
```C++
#include <iostream>
#include <POEX.h> // include POEX header

int main()
{
    auto pe = POEX::PE(L"1.exe");

    // Access to Image DOS Header
    auto dos = pe.GetImageDosHeader();

    // ******** some stuff here **********

    // If you want save change on Original file
    pe.SaveFile();

    // Else, you want save change on another file
    pe.SaveFile("another.exe");

    return 0;
}
```

* You can access other part of PE Structures as you see in here DOS Header example.
* More detail see [Wiki](https://github.com/AFP33/POEX/wiki).
