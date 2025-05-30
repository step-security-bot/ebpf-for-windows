// Copyright (c) eBPF for Windows contributors
// SPDX-License-Identifier: MIT

// Do not alter this generated file.
// This file was generated from test_sample_perf_event_array.o

#define NO_CRT
#include "bpf2c.h"

#include <guiddef.h>
#include <wdm.h>
#include <wsk.h>

DRIVER_INITIALIZE DriverEntry;
DRIVER_UNLOAD DriverUnload;
RTL_QUERY_REGISTRY_ROUTINE static _bpf2c_query_registry_routine;

#define metadata_table test_sample_perf_event_array##_metadata_table

static GUID _bpf2c_npi_id = {/* c847aac8-a6f2-4b53-aea3-f4a94b9a80cb */
                             0xc847aac8,
                             0xa6f2,
                             0x4b53,
                             {0xae, 0xa3, 0xf4, 0xa9, 0x4b, 0x9a, 0x80, 0xcb}};
static NPI_MODULEID _bpf2c_module_id = {sizeof(_bpf2c_module_id), MIT_GUID, {0}};
static HANDLE _bpf2c_nmr_client_handle;
static HANDLE _bpf2c_nmr_provider_handle;
extern metadata_table_t metadata_table;

static NTSTATUS
_bpf2c_npi_client_attach_provider(
    _In_ HANDLE nmr_binding_handle,
    _In_ void* client_context,
    _In_ const NPI_REGISTRATION_INSTANCE* provider_registration_instance);

static NTSTATUS
_bpf2c_npi_client_detach_provider(_In_ void* client_binding_context);

static const NPI_CLIENT_CHARACTERISTICS _bpf2c_npi_client_characteristics = {
    0,                                  // Version
    sizeof(NPI_CLIENT_CHARACTERISTICS), // Length
    _bpf2c_npi_client_attach_provider,
    _bpf2c_npi_client_detach_provider,
    NULL,
    {0,                                 // Version
     sizeof(NPI_REGISTRATION_INSTANCE), // Length
     &_bpf2c_npi_id,
     &_bpf2c_module_id,
     0,
     NULL}};

static NTSTATUS
_bpf2c_query_npi_module_id(
    _In_ const wchar_t* value_name,
    unsigned long value_type,
    _In_ const void* value_data,
    unsigned long value_length,
    _Inout_ void* context,
    _Inout_ void* entry_context)
{
    UNREFERENCED_PARAMETER(value_name);
    UNREFERENCED_PARAMETER(context);
    UNREFERENCED_PARAMETER(entry_context);

    if (value_type != REG_BINARY) {
        return STATUS_INVALID_PARAMETER;
    }
    if (value_length != sizeof(_bpf2c_module_id.Guid)) {
        return STATUS_INVALID_PARAMETER;
    }

    memcpy(&_bpf2c_module_id.Guid, value_data, value_length);
    return STATUS_SUCCESS;
}

NTSTATUS
DriverEntry(_In_ DRIVER_OBJECT* driver_object, _In_ UNICODE_STRING* registry_path)
{
    NTSTATUS status;
    RTL_QUERY_REGISTRY_TABLE query_table[] = {
        {
            NULL,                      // Query routine
            RTL_QUERY_REGISTRY_SUBKEY, // Flags
            L"Parameters",             // Name
            NULL,                      // Entry context
            REG_NONE,                  // Default type
            NULL,                      // Default data
            0,                         // Default length
        },
        {
            _bpf2c_query_npi_module_id,  // Query routine
            RTL_QUERY_REGISTRY_REQUIRED, // Flags
            L"NpiModuleId",              // Name
            NULL,                        // Entry context
            REG_NONE,                    // Default type
            NULL,                        // Default data
            0,                           // Default length
        },
        {0}};

    status = RtlQueryRegistryValues(RTL_REGISTRY_ABSOLUTE, registry_path->Buffer, query_table, NULL, NULL);
    if (!NT_SUCCESS(status)) {
        goto Exit;
    }

    status = NmrRegisterClient(&_bpf2c_npi_client_characteristics, NULL, &_bpf2c_nmr_client_handle);

Exit:
    if (NT_SUCCESS(status)) {
        driver_object->DriverUnload = DriverUnload;
    }

    return status;
}

void
DriverUnload(_In_ DRIVER_OBJECT* driver_object)
{
    NTSTATUS status = NmrDeregisterClient(_bpf2c_nmr_client_handle);
    if (status == STATUS_PENDING) {
        NmrWaitForClientDeregisterComplete(_bpf2c_nmr_client_handle);
    }
    UNREFERENCED_PARAMETER(driver_object);
}

static NTSTATUS
_bpf2c_npi_client_attach_provider(
    _In_ HANDLE nmr_binding_handle,
    _In_ void* client_context,
    _In_ const NPI_REGISTRATION_INSTANCE* provider_registration_instance)
{
    NTSTATUS status = STATUS_SUCCESS;
    void* provider_binding_context = NULL;
    void* provider_dispatch_table = NULL;

    UNREFERENCED_PARAMETER(client_context);
    UNREFERENCED_PARAMETER(provider_registration_instance);

    if (_bpf2c_nmr_provider_handle != NULL) {
        return STATUS_INVALID_PARAMETER;
    }

    status = NmrClientAttachProvider(
        nmr_binding_handle, client_context, &metadata_table, &provider_binding_context, &provider_dispatch_table);
    if (status != STATUS_SUCCESS) {
        goto Done;
    }
    _bpf2c_nmr_provider_handle = nmr_binding_handle;

Done:
    return status;
}

static NTSTATUS
_bpf2c_npi_client_detach_provider(_In_ void* client_binding_context)
{
    _bpf2c_nmr_provider_handle = NULL;
    UNREFERENCED_PARAMETER(client_binding_context);
    return STATUS_SUCCESS;
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
    {{0, 0},
     {
         1,  // Current Version.
         80, // Struct size up to the last field.
         80, // Total struct size including padding.
     },
     {
         BPF_MAP_TYPE_PERF_EVENT_ARRAY, // Type of map.
         0,                             // Size in bytes of a map key.
         0,                             // Size in bytes of a map value.
         65536,                         // Maximum number of entries allowed in the map.
         0,                             // Inner map index.
         LIBBPF_PIN_NONE,               // Pinning type for the map.
         7,                             // Identifier for a map template.
         0,                             // The id of the inner map template.
     },
     "test_map"},
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

static helper_function_entry_t test_program_entry_helpers[] = {
    {
        {1, 40, 40}, // Version header.
        32,
        "helper_id_32",
    },
};

static GUID test_program_entry_program_type_guid = {
    0xf788ef4a, 0x207d, 0x4dc3, {0x85, 0xcf, 0x0f, 0x2e, 0xa1, 0x07, 0x21, 0x3c}};
static GUID test_program_entry_attach_type_guid = {
    0xf788ef4b, 0x207d, 0x4dc3, {0x85, 0xcf, 0x0f, 0x2e, 0xa1, 0x07, 0x21, 0x3c}};
static uint16_t test_program_entry_maps[] = {
    0,
};

#pragma code_seg(push, "sample~1")
static uint64_t
test_program_entry(void* context, const program_runtime_context_t* runtime_context)
#line 31 "sample/undocked/test_sample_perf_event_array.c"
{
#line 31 "sample/undocked/test_sample_perf_event_array.c"
    // Prologue.
#line 31 "sample/undocked/test_sample_perf_event_array.c"
    uint64_t stack[(UBPF_STACK_SIZE + 7) / 8];
#line 31 "sample/undocked/test_sample_perf_event_array.c"
    register uint64_t r0 = 0;
#line 31 "sample/undocked/test_sample_perf_event_array.c"
    register uint64_t r1 = 0;
#line 31 "sample/undocked/test_sample_perf_event_array.c"
    register uint64_t r2 = 0;
#line 31 "sample/undocked/test_sample_perf_event_array.c"
    register uint64_t r3 = 0;
#line 31 "sample/undocked/test_sample_perf_event_array.c"
    register uint64_t r4 = 0;
#line 31 "sample/undocked/test_sample_perf_event_array.c"
    register uint64_t r5 = 0;
#line 31 "sample/undocked/test_sample_perf_event_array.c"
    register uint64_t r10 = 0;

#line 31 "sample/undocked/test_sample_perf_event_array.c"
    r1 = (uintptr_t)context;
#line 31 "sample/undocked/test_sample_perf_event_array.c"
    r10 = (uintptr_t)((uint8_t*)stack + sizeof(stack));

    // EBPF_OP_LDXDW pc=0 dst=r4 src=r1 offset=0 imm=0
#line 31 "sample/undocked/test_sample_perf_event_array.c"
    r4 = *(uint64_t*)(uintptr_t)(r1 + OFFSET(0));
    // EBPF_OP_LDXDW pc=1 dst=r5 src=r1 offset=8 imm=0
#line 31 "sample/undocked/test_sample_perf_event_array.c"
    r5 = *(uint64_t*)(uintptr_t)(r1 + OFFSET(8));
    // EBPF_OP_JGE_REG pc=2 dst=r4 src=r5 offset=9 imm=0
#line 31 "sample/undocked/test_sample_perf_event_array.c"
    if (r4 >= r5) {
#line 31 "sample/undocked/test_sample_perf_event_array.c"
        goto label_1;
#line 31 "sample/undocked/test_sample_perf_event_array.c"
    }
    // EBPF_OP_SUB64_REG pc=3 dst=r5 src=r4 offset=0 imm=0
#line 33 "sample/undocked/test_sample_perf_event_array.c"
    r5 -= r4;
    // EBPF_OP_MOV64_REG pc=4 dst=r3 src=r5 offset=0 imm=0
#line 34 "sample/undocked/test_sample_perf_event_array.c"
    r3 = r5;
    // EBPF_OP_LSH64_IMM pc=5 dst=r3 src=r0 offset=0 imm=32
#line 34 "sample/undocked/test_sample_perf_event_array.c"
    r3 <<= (IMMEDIATE(32) & 63);
    // EBPF_OP_LDDW pc=6 dst=r2 src=r0 offset=0 imm=-1
#line 34 "sample/undocked/test_sample_perf_event_array.c"
    r2 = (uint64_t)4294967295;
    // EBPF_OP_OR64_REG pc=8 dst=r3 src=r2 offset=0 imm=0
#line 34 "sample/undocked/test_sample_perf_event_array.c"
    r3 |= r2;
    // EBPF_OP_LDDW pc=9 dst=r2 src=r1 offset=0 imm=1
#line 35 "sample/undocked/test_sample_perf_event_array.c"
    r2 = POINTER(runtime_context->map_data[0].address);
    // EBPF_OP_CALL pc=11 dst=r0 src=r0 offset=0 imm=32
#line 35 "sample/undocked/test_sample_perf_event_array.c"
    r0 = runtime_context->helper_data[0].address(r1, r2, r3, r4, r5, context);
#line 35 "sample/undocked/test_sample_perf_event_array.c"
    if ((runtime_context->helper_data[0].tail_call) && (r0 == 0)) {
#line 35 "sample/undocked/test_sample_perf_event_array.c"
        return 0;
#line 35 "sample/undocked/test_sample_perf_event_array.c"
    }
label_1:
    // EBPF_OP_MOV64_IMM pc=12 dst=r0 src=r0 offset=0 imm=0
#line 39 "sample/undocked/test_sample_perf_event_array.c"
    r0 = IMMEDIATE(0);
    // EBPF_OP_EXIT pc=13 dst=r0 src=r0 offset=0 imm=0
#line 39 "sample/undocked/test_sample_perf_event_array.c"
    return r0;
#line 31 "sample/undocked/test_sample_perf_event_array.c"
}
#pragma code_seg(pop)
#line __LINE__ __FILE__

#pragma data_seg(push, "programs")
static program_entry_t _programs[] = {
    {
        0,
        {1, 144, 144}, // Version header.
        test_program_entry,
        "sample~1",
        "sample_ext",
        "test_program_entry",
        test_program_entry_maps,
        1,
        test_program_entry_helpers,
        1,
        14,
        &test_program_entry_program_type_guid,
        &test_program_entry_attach_type_guid,
    },
};
#pragma data_seg(pop)

static void
_get_programs(_Outptr_result_buffer_(*count) program_entry_t** programs, _Out_ size_t* count)
{
    *programs = _programs;
    *count = 1;
}

static void
_get_version(_Out_ bpf2c_version_t* version)
{
    version->major = 0;
    version->minor = 21;
    version->revision = 0;
}

static void
_get_map_initial_values(_Outptr_result_buffer_(*count) map_initial_values_t** map_initial_values, _Out_ size_t* count)
{
    *map_initial_values = NULL;
    *count = 0;
}

metadata_table_t test_sample_perf_event_array_metadata_table = {
    sizeof(metadata_table_t),
    _get_programs,
    _get_maps,
    _get_hash,
    _get_version,
    _get_map_initial_values,
    _get_global_variable_sections,
};
