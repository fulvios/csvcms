// cgo_csvcms_capi.h
// cgo_csvcms_capi.h
#pragma once

#ifndef _CGO_CSVCMS_CAPI_H
#define _CGO_CSVCMS_CAPI_H

typedef struct cgo_CMS_UserInfo
{
	// cgo_CMS_UserInfo()
	// {

	// }
	char userName[64];
}*CAPI_CMS_UserInfo;


typedef void* SERVER_HANDLE;
typedef void* NODE_HANDLE;
typedef void* cgo_sHandle;
typedef void* CAMERA_HANDLE;
typedef struct CMS_LogonInfo cgo_CMS_LogonInfo;
typedef struct CMS_NodeData CMS_NodeData;
typedef struct CMS_NodeData* cgo_CMS_NodeData;
typedef struct CSV_CMS_NodeData CSV_CMS_NodeData;


int CSV_CMS_Init(const char* s);
int cgo_CMS_Init();
void* cgo_CMS_LogonServer(const char* ip, const char* user, const char* pwd);
int cgo_CMS_GetFirstNode(SERVER_HANDLE hLID, cgo_CMS_NodeData pData);
char* cgo_CMS_NodeData_cName(cgo_CMS_NodeData pData);
int cgo_CMS_NodeData_cName_size(cgo_CMS_NodeData pData);
int cgo_CMS_GetFirstChildNode(NODE_HANDLE hNode, cgo_CMS_NodeData pData);
int cgo_CMS_GetNextNode(NODE_HANDLE hNode, cgo_CMS_NodeData pData);
// void RecursionAllCMSNode(cgo_CMS_NodeData pNode);
void RecursionAllCMSNode(SERVER_HANDLE hServer, cgo_CMS_NodeData pNode);

NODE_HANDLE cgo_Get_CMS_Node_Handle(cgo_CMS_NodeData pData);

int cgo_CMS_GetCameraStatus(CAMERA_HANDLE hCamera, int *pnStatus);

CMS_NodeData* New_CMS_NodeData();

void cgo_CMS_LiveView(CAMERA_HANDLE hCamera);

void Debug(cgo_CMS_NodeData pData);

void GetCameraStream(SERVER_HANDLE hServer, cgo_CMS_NodeData pNode);

void CMSLog(const char* msg);

#pragma pack()
#endif