// Copyright (c) eBPF for Windows contributors
// SPDX-License-Identifier: MIT

// Do not alter this generated file.
// This file was generated from tail_call_multiple.o

#include "bpf2c.h"

#include <stdio.h>
#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
#include <windows.h>

#define metadata_table tail_call_multiple##_metadata_table
extern metadata_table_t metadata_table;

bool APIENTRY
DllMain(_In_ HMODULE hModule, unsigned int ul_reason_for_call, _In_ void* lpReserved)
{
    UNREFERENCED_PARAMETER(hModule);
    UNREFERENCED_PARAMETER(lpReserved);
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

__declspec(dllexport) metadata_table_t*
get_metadata_table()
{
    return &metadata_table;
}

#include "bpf2c.h"

static void
_get_hash(_Outptr_result_buffer_maybenull_(*size) const uint8_t** hash, _Out_ size_t* size)
{
    *hash = NULL;
    *size = 0;
}

#pragma data_seg(push, "maps")
static map_entry_t _maps[] = {
    {
     {0, 0},
     {
         1,                       // Current Version.
         80,                      // Struct size up to the last field.
         80,                      // Total struct size including padding.
     },
     {
         BPF_MAP_TYPE_PROG_ARRAY, // Type of map.
         4,                       // Size in bytes of a map key.
         4,                       // Size in bytes of a map value.
         10,                      // Maximum number of entries allowed in the map.
         0,                       // Inner map index.
         LIBBPF_PIN_NONE,         // Pinning type for the map.
         10,                      // Identifier for a map template.
         0,                       // The id of the inner map template.
     },
     "map"},
};
#pragma data_seg(pop)

static void
_get_maps(_Outptr_result_buffer_maybenull_(*count) map_entry_t** maps, _Out_ size_t* count)
{
    *maps = _maps;
    *count = 1;
}

static void
_get_global_variable_sections(
    _Outptr_result_buffer_maybenull_(*count) global_variable_section_info_t** global_variable_sections,
    _Out_ size_t* count)
{
    *global_variable_sections = NULL;
    *count = 0;
}

static helper_function_entry_t callee0_helpers[] = {
    {
     {1, 40, 40}, // Version header.
     5,
     "helper_id_5",
    },
};

static GUID callee0_program_type_guid = {0xf788ef4a, 0x207d, 0x4dc3, {0x85, 0xcf, 0x0f, 0x2e, 0xa1, 0x07, 0x21, 0x3c}};
static GUID callee0_attach_type_guid = {0xf788ef4b, 0x207d, 0x4dc3, {0x85, 0xcf, 0x0f, 0x2e, 0xa1, 0x07, 0x21, 0x3c}};
static uint16_t callee0_maps[] = {
    0,
};

#pragma code_seg(push, "sample~2")
static uint64_t
callee0(void* context, const program_runtime_context_t* runtime_context)
#line 41 "sample/undocked/tail_call_multiple.c"
{
#line 41 "sample/undocked/tail_call_multiple.c"
    // Prologue.
#line 41 "sample/undocked/tail_call_multiple.c"
    uint64_t stack[(UBPF_STACK_SIZE + 7) / 8];
#line 41 "sample/undocked/tail_call_multiple.c"
    register uint64_t r0 = 0;
#line 41 "sample/undocked/tail_call_multiple.c"
    register uint64_t r1 = 0;
#line 41 "sample/undocked/tail_call_multiple.c"
    register uint64_t r2 = 0;
#line 41 "sample/undocked/tail_call_multiple.c"
    register uint64_t r3 = 0;
#line 41 "sample/undocked/tail_call_multiple.c"
    register uint64_t r4 = 0;
#line 41 "sample/undocked/tail_call_multiple.c"
    register uint64_t r5 = 0;
#line 41 "sample/undocked/tail_call_multiple.c"
    register uint64_t r10 = 0;

#line 41 "sample/undocked/tail_call_multiple.c"
    r1 = (uintptr_t)context;
#line 41 "sample/undocked/tail_call_multiple.c"
    r10 = (uintptr_t)((uint8_t*)stack + sizeof(stack));

    // EBPF_OP_LDDW pc=0 dst=r2 src=r1 offset=0 imm=1
#line 41 "sample/undocked/tail_call_multiple.c"
    r2 = POINTER(runtime_context->map_data[0].address);
    // EBPF_OP_MOV64_IMM pc=2 dst=r3 src=r0 offset=0 imm=9
#line 41 "sample/undocked/tail_call_multiple.c"
    r3 = IMMEDIATE(9);
    // EBPF_OP_CALL pc=3 dst=r0 src=r0 offset=0 imm=5
#line 41 "sample/undocked/tail_call_multiple.c"
    r0 = runtime_context->helper_data[0].address(r1, r2, r3, r4, r5, context);
#line 41 "sample/undocked/tail_call_multiple.c"
    if ((runtime_context->helper_data[0].tail_call) && (r0 == 0)) {
#line 41 "sample/undocked/tail_call_multiple.c"
        return 0;
#line 41 "sample/undocked/tail_call_multiple.c"
    }
    // EBPF_OP_MOV64_IMM pc=4 dst=r0 src=r0 offset=0 imm=2
#line 44 "sample/undocked/tail_call_multiple.c"
    r0 = IMMEDIATE(2);
    // EBPF_OP_EXIT pc=5 dst=r0 src=r0 offset=0 imm=0
#line 44 "sample/undocked/tail_call_multiple.c"
    return r0;
#line 41 "sample/undocked/tail_call_multiple.c"
}
#pragma code_seg(pop)
#line __LINE__ __FILE__

static GUID callee1_program_type_guid = {0xf788ef4a, 0x207d, 0x4dc3, {0x85, 0xcf, 0x0f, 0x2e, 0xa1, 0x07, 0x21, 0x3c}};
static GUID callee1_attach_type_guid = {0xf788ef4b, 0x207d, 0x4dc3, {0x85, 0xcf, 0x0f, 0x2e, 0xa1, 0x07, 0x21, 0x3c}};
#pragma code_seg(push, "sample~1")
static uint64_t
callee1(void* context, const program_runtime_context_t* runtime_context)
#line 47 "sample/undocked/tail_call_multiple.c"
{
#line 47 "sample/undocked/tail_call_multiple.c"
    // Prologue.
#line 47 "sample/undocked/tail_call_multiple.c"
    uint64_t stack[(UBPF_STACK_SIZE + 7) / 8];
#line 47 "sample/undocked/tail_call_multiple.c"
    register uint64_t r0 = 0;
#line 47 "sample/undocked/tail_call_multiple.c"
    register uint64_t r1 = 0;
#line 47 "sample/undocked/tail_call_multiple.c"
    register uint64_t r10 = 0;

#line 47 "sample/undocked/tail_call_multiple.c"
    r1 = (uintptr_t)context;
#line 47 "sample/undocked/tail_call_multiple.c"
    r10 = (uintptr_t)((uint8_t*)stack + sizeof(stack));
#line 47 "sample/undocked/tail_call_multiple.c"
    UNREFERENCED_PARAMETER(runtime_context);

    // EBPF_OP_MOV64_IMM pc=0 dst=r0 src=r0 offset=0 imm=3
#line 47 "sample/undocked/tail_call_multiple.c"
    r0 = IMMEDIATE(3);
    // EBPF_OP_EXIT pc=1 dst=r0 src=r0 offset=0 imm=0
#line 47 "sample/undocked/tail_call_multiple.c"
    return r0;
#line 47 "sample/undocked/tail_call_multiple.c"
}
#pragma code_seg(pop)
#line __LINE__ __FILE__

static helper_function_entry_t caller_helpers[] = {
    {
     {1, 40, 40}, // Version header.
     5,
     "helper_id_5",
    },
};

static GUID caller_program_type_guid = {0xf788ef4a, 0x207d, 0x4dc3, {0x85, 0xcf, 0x0f, 0x2e, 0xa1, 0x07, 0x21, 0x3c}};
static GUID caller_attach_type_guid = {0xf788ef4b, 0x207d, 0x4dc3, {0x85, 0xcf, 0x0f, 0x2e, 0xa1, 0x07, 0x21, 0x3c}};
static uint16_t caller_maps[] = {
    0,
};

#pragma code_seg(push, "sample~3")
static uint64_t
caller(void* context, const program_runtime_context_t* runtime_context)
#line 30 "sample/undocked/tail_call_multiple.c"
{
#line 30 "sample/undocked/tail_call_multiple.c"
    // Prologue.
#line 30 "sample/undocked/tail_call_multiple.c"
    uint64_t stack[(UBPF_STACK_SIZE + 7) / 8];
#line 30 "sample/undocked/tail_call_multiple.c"
    register uint64_t r0 = 0;
#line 30 "sample/undocked/tail_call_multiple.c"
    register uint64_t r1 = 0;
#line 30 "sample/undocked/tail_call_multiple.c"
    register uint64_t r2 = 0;
#line 30 "sample/undocked/tail_call_multiple.c"
    register uint64_t r3 = 0;
#line 30 "sample/undocked/tail_call_multiple.c"
    register uint64_t r4 = 0;
#line 30 "sample/undocked/tail_call_multiple.c"
    register uint64_t r5 = 0;
#line 30 "sample/undocked/tail_call_multiple.c"
    register uint64_t r10 = 0;

#line 30 "sample/undocked/tail_call_multiple.c"
    r1 = (uintptr_t)context;
#line 30 "sample/undocked/tail_call_multiple.c"
    r10 = (uintptr_t)((uint8_t*)stack + sizeof(stack));

    // EBPF_OP_LDDW pc=0 dst=r2 src=r1 offset=0 imm=1
#line 30 "sample/undocked/tail_call_multiple.c"
    r2 = POINTER(runtime_context->map_data[0].address);
    // EBPF_OP_MOV64_IMM pc=2 dst=r3 src=r0 offset=0 imm=0
#line 30 "sample/undocked/tail_call_multiple.c"
    r3 = IMMEDIATE(0);
    // EBPF_OP_CALL pc=3 dst=r0 src=r0 offset=0 imm=5
#line 30 "sample/undocked/tail_call_multiple.c"
    r0 = runtime_context->helper_data[0].address(r1, r2, r3, r4, r5, context);
#line 30 "sample/undocked/tail_call_multiple.c"
    if ((runtime_context->helper_data[0].tail_call) && (r0 == 0)) {
#line 30 "sample/undocked/tail_call_multiple.c"
        return 0;
#line 30 "sample/undocked/tail_call_multiple.c"
    }
    // EBPF_OP_MOV64_IMM pc=4 dst=r0 src=r0 offset=0 imm=1
#line 33 "sample/undocked/tail_call_multiple.c"
    r0 = IMMEDIATE(1);
    // EBPF_OP_EXIT pc=5 dst=r0 src=r0 offset=0 imm=0
#line 33 "sample/undocked/tail_call_multiple.c"
    return r0;
#line 30 "sample/undocked/tail_call_multiple.c"
}
#pragma code_seg(pop)
#line __LINE__ __FILE__

#pragma data_seg(push, "programs")
static program_entry_t _programs[] = {
    {
        0,
        {1, 144, 144}, // Version header.
        callee0,
        "sample~2",
        "sample_ext/0",
        "callee0",
        callee0_maps,
        1,
        callee0_helpers,
        1,
        6,
        &callee0_program_type_guid,
        &callee0_attach_type_guid,
    },
    {
        0,
        {1, 144, 144}, // Version header.
        callee1,
        "sample~1",
        "sample_ext/1",
        "callee1",
        NULL,
        0,
        NULL,
        0,
        2,
        &callee1_program_type_guid,
        &callee1_attach_type_guid,
    },
    {
        0,
        {1, 144, 144}, // Version header.
        caller,
        "sample~3",
        "sample_ext",
        "caller",
        caller_maps,
        1,
        caller_helpers,
        1,
        6,
        &caller_program_type_guid,
        &caller_attach_type_guid,
    },
};
#pragma data_seg(pop)

static void
_get_programs(_Outptr_result_buffer_(*count) program_entry_t** programs, _Out_ size_t* count)
{
    *programs = _programs;
    *count = 3;
}

static void
_get_version(_Out_ bpf2c_version_t* version)
{
    version->major = 0;
    version->minor = 22;
    version->revision = 0;
}

static void
_get_map_initial_values(_Outptr_result_buffer_(*count) map_initial_values_t** map_initial_values, _Out_ size_t* count)
{
    *map_initial_values = NULL;
    *count = 0;
}

metadata_table_t tail_call_multiple_metadata_table = {
    sizeof(metadata_table_t),
    _get_programs,
    _get_maps,
    _get_hash,
    _get_version,
    _get_map_initial_values,
    _get_global_variable_sections,
};
