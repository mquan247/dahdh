#include <windows.h>
#include <psapi.h>
#include <tchar.h>
#include <stdio.h>
#include <fstream>
using namespace std;
// To ensure correct resolution of symbols, add Psapi.lib to TARGETLIBS
// and compile with -DPSAPI_VERSION=1

#define ARRAY_SIZE 1024

int main(void)
{
    LPVOID drivers[ARRAY_SIZE];
    DWORD cbNeeded;
    int cDrivers, i;
    ofstream fo("output.txt");  //open file to write
    if (EnumDeviceDrivers(drivers, sizeof(drivers), &cbNeeded) && cbNeeded < sizeof(drivers))
    {
        TCHAR szDriver[ARRAY_SIZE];

        cDrivers = cbNeeded / sizeof(drivers[0]);

        _tprintf(TEXT("There are %d drivers:\n"), cDrivers);

        fo << "There are " << cDrivers << " drivers" << endl;
        for (i = 0; i < cDrivers; i++)
        {
            if (GetDeviceDriverBaseName(drivers[i], szDriver, sizeof(szDriver) / sizeof(szDriver[0])))
            {
                _tprintf(TEXT("%d: %s\n"), i + 1, szDriver);
                //fo << szDriver << endl;
            }
        }
    }
    else
    {
        _tprintf(TEXT("EnumDeviceDrivers failed; array size needed is %d\n"), cbNeeded / sizeof(LPVOID));
        return 1;
    }

    fo.close();	//close file
    return 0;
}