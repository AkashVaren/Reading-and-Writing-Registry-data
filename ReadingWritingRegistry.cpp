
#include <windows.h>
#include <iostream>

void registry_read(LPCTSTR subkey, LPCTSTR name, DWORD type)
{
	HKEY key;
	DWORD value;
	DWORD value_length = 255;
	RegOpenKeyEx(HKEY_LOCAL_MACHINE, subkey,NULL, KEY_ALL_ACCESS | KEY_WOW64_64KEY, &key);
	char* err;
	
	LONG rep=RegQueryValueEx(key, name, NULL, NULL, (LPBYTE)&value, &value_length);
	/*FormatMessage(
		// use system message tables to retrieve error text
		FORMAT_MESSAGE_FROM_SYSTEM
		// allocate buffer on local heap for error text
		| FORMAT_MESSAGE_ALLOCATE_BUFFER
		// Important! will fail otherwise, since we're not 
		// (and CANNOT) pass insertion parameters
		| FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,    // unused with FORMAT_MESSAGE_FROM_SYSTEM
		value,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&err,  // output 
		0, // minimum size for output buffer
		NULL);   // arguments - see note 
	*/
	std::cout << value << std::endl;
	RegCloseKey(key);
}

void registry_write(LPCTSTR subkey, LPCTSTR name, DWORD type, const char* value)
{
	HKEY key;
	RegOpenKey(HKEY_LOCAL_MACHINE, subkey, &key);
	RegSetValueEx(key, name, 0, type, (LPBYTE)value, strlen(value) * sizeof(char));
	RegCloseKey(key);
}

int main()
{
	registry_read((LPCTSTR)"SOFTWARE\\Test\\Product\\NewOne", (LPCTSTR)"Value", REG_DWORD);
	registry_write((LPCTSTR)"SOFTWARE\\Test\\Product\\NewOne",(LPCTSTR)"Value", REG_DWORD, "Content");
	return 0;
}