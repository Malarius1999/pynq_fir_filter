// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2021.1 (64-bit)
// Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xfir_fixed.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XFir_fixed_CfgInitialize(XFir_fixed *InstancePtr, XFir_fixed_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XFir_fixed_Start(XFir_fixed *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XFir_fixed_ReadReg(InstancePtr->Control_BaseAddress, XFIR_FIXED_CONTROL_ADDR_AP_CTRL) & 0x80;
    XFir_fixed_WriteReg(InstancePtr->Control_BaseAddress, XFIR_FIXED_CONTROL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XFir_fixed_IsDone(XFir_fixed *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XFir_fixed_ReadReg(InstancePtr->Control_BaseAddress, XFIR_FIXED_CONTROL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XFir_fixed_IsIdle(XFir_fixed *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XFir_fixed_ReadReg(InstancePtr->Control_BaseAddress, XFIR_FIXED_CONTROL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XFir_fixed_IsReady(XFir_fixed *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XFir_fixed_ReadReg(InstancePtr->Control_BaseAddress, XFIR_FIXED_CONTROL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XFir_fixed_EnableAutoRestart(XFir_fixed *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XFir_fixed_WriteReg(InstancePtr->Control_BaseAddress, XFIR_FIXED_CONTROL_ADDR_AP_CTRL, 0x80);
}

void XFir_fixed_DisableAutoRestart(XFir_fixed *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XFir_fixed_WriteReg(InstancePtr->Control_BaseAddress, XFIR_FIXED_CONTROL_ADDR_AP_CTRL, 0);
}

void XFir_fixed_Set_input_r(XFir_fixed *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XFir_fixed_WriteReg(InstancePtr->Control_BaseAddress, XFIR_FIXED_CONTROL_ADDR_INPUT_R_DATA, (u32)(Data));
    XFir_fixed_WriteReg(InstancePtr->Control_BaseAddress, XFIR_FIXED_CONTROL_ADDR_INPUT_R_DATA + 4, (u32)(Data >> 32));
}

u64 XFir_fixed_Get_input_r(XFir_fixed *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XFir_fixed_ReadReg(InstancePtr->Control_BaseAddress, XFIR_FIXED_CONTROL_ADDR_INPUT_R_DATA);
    Data += (u64)XFir_fixed_ReadReg(InstancePtr->Control_BaseAddress, XFIR_FIXED_CONTROL_ADDR_INPUT_R_DATA + 4) << 32;
    return Data;
}

void XFir_fixed_Set_output_r(XFir_fixed *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XFir_fixed_WriteReg(InstancePtr->Control_BaseAddress, XFIR_FIXED_CONTROL_ADDR_OUTPUT_R_DATA, (u32)(Data));
    XFir_fixed_WriteReg(InstancePtr->Control_BaseAddress, XFIR_FIXED_CONTROL_ADDR_OUTPUT_R_DATA + 4, (u32)(Data >> 32));
}

u64 XFir_fixed_Get_output_r(XFir_fixed *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XFir_fixed_ReadReg(InstancePtr->Control_BaseAddress, XFIR_FIXED_CONTROL_ADDR_OUTPUT_R_DATA);
    Data += (u64)XFir_fixed_ReadReg(InstancePtr->Control_BaseAddress, XFIR_FIXED_CONTROL_ADDR_OUTPUT_R_DATA + 4) << 32;
    return Data;
}

void XFir_fixed_InterruptGlobalEnable(XFir_fixed *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XFir_fixed_WriteReg(InstancePtr->Control_BaseAddress, XFIR_FIXED_CONTROL_ADDR_GIE, 1);
}

void XFir_fixed_InterruptGlobalDisable(XFir_fixed *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XFir_fixed_WriteReg(InstancePtr->Control_BaseAddress, XFIR_FIXED_CONTROL_ADDR_GIE, 0);
}

void XFir_fixed_InterruptEnable(XFir_fixed *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XFir_fixed_ReadReg(InstancePtr->Control_BaseAddress, XFIR_FIXED_CONTROL_ADDR_IER);
    XFir_fixed_WriteReg(InstancePtr->Control_BaseAddress, XFIR_FIXED_CONTROL_ADDR_IER, Register | Mask);
}

void XFir_fixed_InterruptDisable(XFir_fixed *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XFir_fixed_ReadReg(InstancePtr->Control_BaseAddress, XFIR_FIXED_CONTROL_ADDR_IER);
    XFir_fixed_WriteReg(InstancePtr->Control_BaseAddress, XFIR_FIXED_CONTROL_ADDR_IER, Register & (~Mask));
}

void XFir_fixed_InterruptClear(XFir_fixed *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XFir_fixed_WriteReg(InstancePtr->Control_BaseAddress, XFIR_FIXED_CONTROL_ADDR_ISR, Mask);
}

u32 XFir_fixed_InterruptGetEnabled(XFir_fixed *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XFir_fixed_ReadReg(InstancePtr->Control_BaseAddress, XFIR_FIXED_CONTROL_ADDR_IER);
}

u32 XFir_fixed_InterruptGetStatus(XFir_fixed *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XFir_fixed_ReadReg(InstancePtr->Control_BaseAddress, XFIR_FIXED_CONTROL_ADDR_ISR);
}

