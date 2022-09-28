#include "GetMouseInterface.h"
#include "main.h"

HDEVINFO v2{};
DWORD v3{};
char v4{};
struct _SP_DEVICE_INTERFACE_DETAIL_DATA_W* DevInterfaceDetDataPtr{};
HDEVINFO DeviceInfoSetBuffer{};
WCHAR* v7{};
HANDLE DevHandle{};


GUID InterfaceClassGuid{};
HDEVINFO DeviceInfoSet{};
DWORD RequiredSize{};
struct _SP_DEVICE_INTERFACE_DATA DeviceInterfaceData {};
DWORD WhoKnows{};
WORD WhoKnows2{};
struct _HIDD_ATTRIBUTES Attributes {};
HANDLE HidDeviceObject{};
PHIDP_PREPARSED_DATA PreparsedData{};
struct _HIDP_CAPS Capabilities {};

int GetMouseInterface(int MouseID)
{
	RequiredSize = 0;
	HidD_GetHidGuid(&InterfaceClassGuid);
	v2 = SetupDiGetClassDevsW(&InterfaceClassGuid, 0, 0, DIGCF_ALLCLASSES);
	DeviceInterfaceData.cbSize = 32;
	v3 = 0;
	v4 = 0;

	for (DeviceInfoSet = v2; ; v2 = DeviceInfoSet)
	{
		if (SetupDiEnumDeviceInterfaces(v2, 0, &InterfaceClassGuid, v3++, &DeviceInterfaceData))
		{
			WhoKnows = 5;
			SetupDiGetDeviceInterfaceDetailW(DeviceInfoSet, &DeviceInterfaceData, 0, 0, &RequiredSize, 0);
			DevInterfaceDetDataPtr = (struct _SP_DEVICE_INTERFACE_DETAIL_DATA_W*)malloc(RequiredSize);
			DeviceInfoSetBuffer = DeviceInfoSet;
			DevInterfaceDetDataPtr->cbSize = 8;
			v7 = (WCHAR*)DevInterfaceDetDataPtr;
			SetupDiGetDeviceInterfaceDetailW(DeviceInfoSetBuffer, &DeviceInterfaceData, DevInterfaceDetDataPtr, RequiredSize, &::RequiredSize, 0);
			DevHandle = CreateFileW(v7 + 2, 0xC0000000, 3, 0, 3, 0, 0);
			Attributes.Size = 12;
			HidDeviceObject = DevHandle;
			HidD_GetAttributes(DevHandle, &Attributes);

			if (Attributes.VendorID == 8916 && Attributes.ProductID == MouseID)
			{
				HidD_GetPreparsedData(HidDeviceObject, &PreparsedData);
				HidP_GetCaps(PreparsedData, &Capabilities);
				HidD_FreePreparsedData(PreparsedData);

				if (Capabilities.UsagePage == 65281 && Capabilities.Usage == 2)
				{
					WhoKnows2 = 1;
					free(v7);
					return 1;
				}
			}
			free(v7);
		}
		else
		{
			v4 = 1;
		}
		if (v4)
			break;
	}
	SetupDiDestroyDeviceInfoList(DeviceInfoSet); 
	return 0; 
}


