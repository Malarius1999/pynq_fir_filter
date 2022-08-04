// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2021.1 (64-bit)
// Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XFIR_FIXED_H
#define XFIR_FIXED_H

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
#include "xfir_fixed_hw.h"

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
} XFir_fixed_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XFir_fixed;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XFir_fixed_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XFir_fixed_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XFir_fixed_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XFir_fixed_ReadReg(BaseAddress, RegOffset) \
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
int XFir_fixed_Initialize(XFir_fixed *InstancePtr, u16 DeviceId);
XFir_fixed_Config* XFir_fixed_LookupConfig(u16 DeviceId);
int XFir_fixed_CfgInitialize(XFir_fixed *InstancePtr, XFir_fixed_Config *ConfigPtr);
#else
int XFir_fixed_Initialize(XFir_fixed *InstancePtr, const char* InstanceName);
int XFir_fixed_Release(XFir_fixed *InstancePtr);
#endif

void XFir_fixed_Start(XFir_fixed *InstancePtr);
u32 XFir_fixed_IsDone(XFir_fixed *InstancePtr);
u32 XFir_fixed_IsIdle(XFir_fixed *InstancePtr);
u32 XFir_fixed_IsReady(XFir_fixed *InstancePtr);
void XFir_fixed_EnableAutoRestart(XFir_fixed *InstancePtr);
void XFir_fixed_DisableAutoRestart(XFir_fixed *InstancePtr);

void XFir_fixed_Set_input_r(XFir_fixed *InstancePtr, u64 Data);
u64 XFir_fixed_Get_input_r(XFir_fixed *InstancePtr);
void XFir_fixed_Set_output_r(XFir_fixed *InstancePtr, u64 Data);
u64 XFir_fixed_Get_output_r(XFir_fixed *InstancePtr);

void XFir_fixed_InterruptGlobalEnable(XFir_fixed *InstancePtr);
void XFir_fixed_InterruptGlobalDisable(XFir_fixed *InstancePtr);
void XFir_fixed_InterruptEnable(XFir_fixed *InstancePtr, u32 Mask);
void XFir_fixed_InterruptDisable(XFir_fixed *InstancePtr, u32 Mask);
void XFir_fixed_InterruptClear(XFir_fixed *InstancePtr, u32 Mask);
u32 XFir_fixed_InterruptGetEnabled(XFir_fixed *InstancePtr);
u32 XFir_fixed_InterruptGetStatus(XFir_fixed *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
