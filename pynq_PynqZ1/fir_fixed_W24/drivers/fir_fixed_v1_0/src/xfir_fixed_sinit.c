// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2021.1 (64-bit)
// Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xfir_fixed.h"

extern XFir_fixed_Config XFir_fixed_ConfigTable[];

XFir_fixed_Config *XFir_fixed_LookupConfig(u16 DeviceId) {
	XFir_fixed_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XFIR_FIXED_NUM_INSTANCES; Index++) {
		if (XFir_fixed_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XFir_fixed_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XFir_fixed_Initialize(XFir_fixed *InstancePtr, u16 DeviceId) {
	XFir_fixed_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XFir_fixed_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XFir_fixed_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

