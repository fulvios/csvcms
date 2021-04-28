// cgo_csvcms_capi.cpp
#include "stdafx.h"
#include "csvcms.h"

extern "C" {
	#include "cgo_csvcms_capi.h"
}
#pragma comment(lib, "csvcms.lib")

int CSV_CMS_Init(const char* s)
{
	CSVCMSMsgOutput(s);
	
	return 1;
}

int cgo_CMS_Init()
{
	return CMS_Init();
}

void* cgo_CMS_LogonServer(const char* ip, const char* user, const char* pwd /*LPCMS_LogonInfo pInfo*/)
{
	CMS_LogonInfo logonInfo;
	
	strcpy_s(logonInfo.cSvrIP, ip);
	strcpy_s(logonInfo.cUser, user);
	strcpy_s(logonInfo.cPwd, pwd);

	SERVER_HANDLE serv = CMS_LogonServer(&logonInfo);

	return serv;
}

int cgo_CMS_GetFirstNode(SERVER_HANDLE hLID, cgo_CMS_NodeData pData){
	return CMS_GetFirstNode(hLID, pData);
}

int cgo_CMS_GetFirstChildNode(NODE_HANDLE hNode, cgo_CMS_NodeData pData)
{
	return CMS_GetFirstChildNode(hNode, pData);
}

int cgo_CMS_GetNextNode(NODE_HANDLE hNode, cgo_CMS_NodeData pData)
{
	return CMS_GetNextNode(hNode, pData);
}

char* cgo_CMS_NodeData_cName(cgo_CMS_NodeData pData)
{
	printf("%s\n", pData->cName);
	return (char*)pData->cName;
}

int cgo_CMS_NodeData_cName_size(cgo_CMS_NodeData pData)
{
	return strlen(pData->cName);
}

CMS_NodeData* New_CMS_NodeData()
{
	return new CMS_NodeData;
}

struct CSV_CMS_NodeData : CMS_NodeData
{
	~CSV_CMS_NodeData() {}
};

NODE_HANDLE cgo_Get_CMS_Node_Handle(cgo_CMS_NodeData pData)
{
	printf("%s\n", pData->cName);
	return pData->hNode;
}

int cgo_CMS_GetCameraStatus(CAMERA_HANDLE hCamera, int *pnStatus)
{
	return  CMS_GetCameraStatus(hCamera, pnStatus);
}

void RecursionAllCMSNode(cgo_CMS_NodeData pNode)
{
	CMS_NodeData node;

	if(CMS_GetFirstChildNode(pNode->hNode, &node))
	{
		Debug(&node);
		RecursionAllCMSNode(&node);
	}

	if(CMS_GetNextNode(pNode->hNode, &node))
	{
		Debug(&node);
		RecursionAllCMSNode(&node);
	}
}

void GetCameraStream(SERVER_HANDLE hServer, cgo_CMS_NodeData pNode)
{
	CMS_StringQuerySet cSet;

	cSet.szDstString = pNode->cName;
	cSet.nMatchMode = 0;
	cSet.pHCamera = new CAMERA_HANDLE[100];
	cSet.nBufferSize = 100;

	if (CMS_GetCameraHandlesByName(hServer, &cSet))
	{
		if (cSet.nCount > 0)
		{
			char cName[64];
			CMS_GetCameraName(cSet.pHCamera[0], cName, 64);
			CMSLog(cName);
		}
		CMSLog("Success get Camera handle");
		/* code */
	} else {
		CMSLog("Failed get Camera handle");
	}
}

void Debug(cgo_CMS_NodeData pData)
{
	printf("Node name is: %s\n", pData->cName);
}

void CMSLog(const char* msg)
{
	printf("%s\n", msg);
}