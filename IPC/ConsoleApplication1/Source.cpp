//�����ڴ�
#include <windows.h>

#define WM_C		WM_USER + 100
typedef struct _tagCOMMUNICATIONOBJECT
{
	HWND	hWnd;
} COMMUNICATIONOBJECT, *PCOMMUNICATIONOBJECT;
TCHAR* szMappingName = TEXT("__SHARED_FILE_MAPPING__");
PCOMMUNICATIONOBJECT pCommObject = NULL;
//�����ڴ�

int main()
{
	// TODO: Place code here.
	HWND hConsole = GetConsoleWindow();
	ShowWindow(hConsole, SW_HIDE);

	//�򿪹����ڴ棬��ʹ�����е�ֵ
	HANDLE hMapping = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, szMappingName);
	if (hMapping == INVALID_HANDLE_VALUE)
	{
		return -1;
	}
	PCOMMUNICATIONOBJECT pCommObject = (PCOMMUNICATIONOBJECT)MapViewOfFile(hMapping,
		FILE_MAP_ALL_ACCESS, 0, 0, sizeof(COMMUNICATIONOBJECT));
	if (pCommObject == NULL)//�����ڴ�û�б���������ô�˳�ȥ
	{
		return -1;
	}
	//�����ڴ��б���Ĵ��ھ�������Զ�����Ϣ
	//SendMessage(pCommObject->hWnd, WM_C, 0, 0);//�ȴ���Ӧ�󷵻�
	PostMessage(pCommObject->hWnd, WM_C, 0, 0);

	//�ͷŹ����ڴ�
	UnmapViewOfFile(pCommObject);
	CloseHandle(hMapping);
	//system("pause");
	return 0;
}