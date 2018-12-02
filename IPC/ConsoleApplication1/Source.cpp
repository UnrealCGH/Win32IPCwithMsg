//共享内存
#include <windows.h>

#define WM_C		WM_USER + 100
typedef struct _tagCOMMUNICATIONOBJECT
{
	HWND	hWnd;
} COMMUNICATIONOBJECT, *PCOMMUNICATIONOBJECT;
TCHAR* szMappingName = TEXT("__SHARED_FILE_MAPPING__");
PCOMMUNICATIONOBJECT pCommObject = NULL;
//共享内存

int main()
{
	// TODO: Place code here.
	HWND hConsole = GetConsoleWindow();
	ShowWindow(hConsole, SW_HIDE);

	//打开共享内存，并使用其中的值
	HANDLE hMapping = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, szMappingName);
	if (hMapping == INVALID_HANDLE_VALUE)
	{
		return -1;
	}
	PCOMMUNICATIONOBJECT pCommObject = (PCOMMUNICATIONOBJECT)MapViewOfFile(hMapping,
		FILE_MAP_ALL_ACCESS, 0, 0, sizeof(COMMUNICATIONOBJECT));
	if (pCommObject == NULL)//共享内存没有被创建，那么退出去
	{
		return -1;
	}
	//向共享内存中保存的窗口句柄发送自定义消息
	//SendMessage(pCommObject->hWnd, WM_C, 0, 0);//等待响应后返回
	PostMessage(pCommObject->hWnd, WM_C, 0, 0);

	//释放共享内存
	UnmapViewOfFile(pCommObject);
	CloseHandle(hMapping);
	//system("pause");
	return 0;
}