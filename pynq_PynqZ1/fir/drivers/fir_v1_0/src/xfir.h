// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2021.1 (64-bit)
// Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XFIR_H
#define XFIR_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xfir_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#else
typedef struct {
    u16 DeviceId;
    u32 Control_BaseAddress;
} XFir_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XFir;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XFir_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XFir_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XFir_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XFir_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
int XFir_Initialize(XFir *InstancePtr, u16 DeviceId);
XFir_Config* XFir_LookupConfig(u16 DeviceId);
int XFir_CfgInitialize(XFir *InstancePtr, XFir_Config *ConfigPtr);
#else
int XFir_Initialize(XFir *InstancePtr, const char* InstanceName);
int XFir_Release(XFir *InstancePtr);
#endif

void XFir_Start(XFir *InstancePtr);
u32 XFir_IsDone(XFir *InstancePtr);
u32 XFir_IsIdle(XFir *InstancePtr);
u32 XFir_IsReady(XFir *InstancePtr);
void XFir_EnableAutoRestart(XFir *InstancePtr);
void XFir_DisableAutoRestart(XFir *InstancePtr);

void XFir_Set_input_r(XFir *InstancePtr, u64 Data);
u64 XFir_Get_input_r(XFir *InstancePtr);
void XFir_Set_output_r(XFir *InstancePtr, u64 Data);
u64 XFir_Get_output_r(XFir *InstancePtr);

void XFir_InterruptGlobalEnable(XFir *InstancePtr);
void XFir_InterruptGlobalDisable(XFir *InstancePtr);
void XFir_InterruptEnable(XFir *InstancePtr, u32 Mask);
void XFir_InterruptDisable(XFir *InstancePtr, u32 Mask);
void XFir_InterruptClear(XFir *InstancePtr, u32 Mask);
u32 XFir_InterruptGetEnabled(XFir *InstancePtr);
u32 XFir_InterruptGetStatus(XFir *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif