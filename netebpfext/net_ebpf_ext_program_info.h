// Copyright (c) eBPF for Windows contributors
// SPDX-License-Identifier: MIT
#pragma once

#include "ebpf_extension.h"
#include "ebpf_nethooks.h"
#include "ebpf_program_types.h"
#include "ebpf_shared_framework.h"
#include "net_ebpf_ext_xdp_hooks.h"

#define XDP_EXT_HELPER_FUNCTION_START EBPF_MAX_GENERAL_HELPER_FUNCTION

#define HELPER_FUNCTION_REALLOCATE_PACKET TRUE

enum _xdp_test_helper_functions
{
    XDP_TEST_HELPER_ADJUST_HEAD,
};

// XDP_TEST helper function prototype descriptors.
static const ebpf_helper_function_prototype_t _xdp_test_ebpf_extension_helper_function_prototype[] = {
    {EBPF_HELPER_FUNCTION_PROTOTYPE_HEADER,
     XDP_EXT_HELPER_FUNCTION_START + 1,
     "bpf_xdp_adjust_head",
     EBPF_RETURN_TYPE_INTEGER,
     {EBPF_ARGUMENT_TYPE_PTR_TO_CTX, EBPF_ARGUMENT_TYPE_ANYTHING},
     // Flags.
     {HELPER_FUNCTION_REALLOCATE_PACKET}}};

// XDP_TEST program information.
static const ebpf_context_descriptor_t _ebpf_xdp_test_context_descriptor = {
    sizeof(xdp_md_t),
    EBPF_OFFSET_OF(xdp_md_t, data),
    EBPF_OFFSET_OF(xdp_md_t, data_end),
    EBPF_OFFSET_OF(xdp_md_t, data_meta)};

static const ebpf_program_type_descriptor_t _ebpf_xdp_test_program_type_descriptor = {
    EBPF_PROGRAM_TYPE_DESCRIPTOR_HEADER,
    "xdp_test",
    &_ebpf_xdp_test_context_descriptor,
    EBPF_PROGRAM_TYPE_XDP_TEST_GUID,
    BPF_PROG_TYPE_XDP_TEST,
    0};
static const ebpf_program_info_t _ebpf_xdp_test_program_info = {
    EBPF_PROGRAM_INFORMATION_HEADER,
    &_ebpf_xdp_test_program_type_descriptor,
    EBPF_COUNT_OF(_xdp_test_ebpf_extension_helper_function_prototype),
    _xdp_test_ebpf_extension_helper_function_prototype};

static const ebpf_program_section_info_t _ebpf_xdp_test_section_info[] = {
    {{EBPF_PROGRAM_SECTION_INFORMATION_CURRENT_VERSION, EBPF_PROGRAM_SECTION_INFORMATION_CURRENT_VERSION_SIZE},
     L"xdp_test",
     &EBPF_PROGRAM_TYPE_XDP_TEST,
     &EBPF_ATTACH_TYPE_XDP_TEST,
     BPF_PROG_TYPE_XDP_TEST,
     BPF_XDP_TEST}};

// Bind program information.
static const ebpf_context_descriptor_t _ebpf_bind_context_descriptor = {
    sizeof(bind_md_t), EBPF_OFFSET_OF(bind_md_t, app_id_start), EBPF_OFFSET_OF(bind_md_t, app_id_end), -1};

static const ebpf_program_type_descriptor_t _ebpf_bind_program_type_descriptor = {
    EBPF_PROGRAM_TYPE_DESCRIPTOR_HEADER,
    "bind",
    &_ebpf_bind_context_descriptor,
    EBPF_PROGRAM_TYPE_BIND_GUID,
    BPF_PROG_TYPE_BIND,
    0};
static const ebpf_program_info_t _ebpf_bind_program_info = {
    EBPF_PROGRAM_INFORMATION_HEADER, &_ebpf_bind_program_type_descriptor, 0, NULL, 0, NULL};

static const ebpf_program_section_info_t _ebpf_bind_section_info[] = {
    {{EBPF_PROGRAM_SECTION_INFORMATION_CURRENT_VERSION, EBPF_PROGRAM_SECTION_INFORMATION_CURRENT_VERSION_SIZE},
     L"bind",
     &EBPF_PROGRAM_TYPE_BIND,
     &EBPF_ATTACH_TYPE_BIND,
     BPF_PROG_TYPE_BIND,
     BPF_ATTACH_TYPE_BIND}};

enum _sock_addr_helper_functions
{
    SOCK_ADDR_HELPER_SET_REDIRECT_CONTEXT,
};

// CGROUP_SOCK_ADDR extension specific helper function prototypes.
static const ebpf_helper_function_prototype_t _sock_addr_ebpf_extension_helper_function_prototype[] = {
    {EBPF_HELPER_FUNCTION_PROTOTYPE_HEADER,
     BPF_FUNC_sock_addr_set_redirect_context,
     "bpf_sock_addr_set_redirect_context",
     EBPF_RETURN_TYPE_INTEGER,
     {EBPF_ARGUMENT_TYPE_PTR_TO_CTX, EBPF_ARGUMENT_TYPE_PTR_TO_READABLE_MEM, EBPF_ARGUMENT_TYPE_CONST_SIZE}}};

enum _sock_addr_global_helper_functions
{
    SOCK_ADDR_GLOBAL_HELPER_GET_CURRENT_PID_TGID,
    SOCK_ADDR_GLOBAL_HELPER_GET_CURRENT_LOGON_ID,
    SOCK_ADDR_GLOBAL_HELPER_IS_CURRENT_ADMIN,
    SOCK_ADDR_GLOBAL_HELPER_GET_SOCKET_COOKIE,
};

// CGROUP_SOCK_ADDR global helper function prototypes.
static const ebpf_helper_function_prototype_t _ebpf_sock_addr_global_helper_function_prototype[] = {
    {.header = EBPF_HELPER_FUNCTION_PROTOTYPE_HEADER,
     .helper_id = BPF_FUNC_get_current_pid_tgid,
     .name = "bpf_get_current_pid_tgid",
     .return_type = EBPF_RETURN_TYPE_INTEGER,
     .arguments = {},
     .implicit_context = true},
    {EBPF_HELPER_FUNCTION_PROTOTYPE_HEADER,
     BPF_FUNC_get_current_logon_id,
     "bpf_get_current_logon_id",
     EBPF_RETURN_TYPE_INTEGER,
     {EBPF_ARGUMENT_TYPE_PTR_TO_CTX}},
    {EBPF_HELPER_FUNCTION_PROTOTYPE_HEADER,
     BPF_FUNC_is_current_admin,
     "bpf_is_current_admin",
     EBPF_RETURN_TYPE_INTEGER,
     {EBPF_ARGUMENT_TYPE_PTR_TO_CTX}},
    {EBPF_HELPER_FUNCTION_PROTOTYPE_HEADER,
     BPF_FUNC_get_socket_cookie,
     "bpf_get_socket_cookie",
     EBPF_RETURN_TYPE_INTEGER,
     {EBPF_ARGUMENT_TYPE_PTR_TO_CTX}}};

// CGROUP_SOCK_ADDR program information.
static const ebpf_context_descriptor_t _ebpf_sock_addr_context_descriptor = {
    sizeof(bpf_sock_addr_t),
    -1, // Offset into ctx struct for pointer to data, or -1 if none.
    -1, // Offset into ctx struct for pointer to data, or -1 if none.
    -1, // Offset into ctx struct for pointer to metadata, or -1 if none.
};

static const ebpf_program_type_descriptor_t _ebpf_sock_addr_program_type_desciptor = {
    EBPF_PROGRAM_TYPE_DESCRIPTOR_HEADER,
    "sock_addr",
    &_ebpf_sock_addr_context_descriptor,
    EBPF_PROGRAM_TYPE_CGROUP_SOCK_ADDR_GUID,
    BPF_PROG_TYPE_CGROUP_SOCK_ADDR,
    0};
static const ebpf_program_info_t _ebpf_sock_addr_program_info = {
    EBPF_PROGRAM_INFORMATION_HEADER,
    &_ebpf_sock_addr_program_type_desciptor,
    EBPF_COUNT_OF(_sock_addr_ebpf_extension_helper_function_prototype),
    _sock_addr_ebpf_extension_helper_function_prototype,
    EBPF_COUNT_OF(_ebpf_sock_addr_global_helper_function_prototype),
    _ebpf_sock_addr_global_helper_function_prototype};

static const ebpf_program_section_info_t _ebpf_sock_addr_section_info[] = {
    {{EBPF_PROGRAM_SECTION_INFORMATION_CURRENT_VERSION, EBPF_PROGRAM_SECTION_INFORMATION_CURRENT_VERSION_SIZE},
     L"cgroup/connect4",
     &EBPF_PROGRAM_TYPE_CGROUP_SOCK_ADDR,
     &EBPF_ATTACH_TYPE_CGROUP_INET4_CONNECT,
     BPF_PROG_TYPE_CGROUP_SOCK_ADDR,
     BPF_CGROUP_INET4_CONNECT},
    {{EBPF_PROGRAM_SECTION_INFORMATION_CURRENT_VERSION, EBPF_PROGRAM_SECTION_INFORMATION_CURRENT_VERSION_SIZE},
     L"cgroup/connect6",
     &EBPF_PROGRAM_TYPE_CGROUP_SOCK_ADDR,
     &EBPF_ATTACH_TYPE_CGROUP_INET6_CONNECT,
     BPF_PROG_TYPE_CGROUP_SOCK_ADDR,
     BPF_CGROUP_INET6_CONNECT},
    {{EBPF_PROGRAM_SECTION_INFORMATION_CURRENT_VERSION, EBPF_PROGRAM_SECTION_INFORMATION_CURRENT_VERSION_SIZE},
     L"cgroup/recv_accept4",
     &EBPF_PROGRAM_TYPE_CGROUP_SOCK_ADDR,
     &EBPF_ATTACH_TYPE_CGROUP_INET4_RECV_ACCEPT,
     BPF_PROG_TYPE_CGROUP_SOCK_ADDR,
     BPF_CGROUP_INET4_RECV_ACCEPT},
    {{EBPF_PROGRAM_SECTION_INFORMATION_CURRENT_VERSION, EBPF_PROGRAM_SECTION_INFORMATION_CURRENT_VERSION_SIZE},
     L"cgroup/recv_accept6",
     &EBPF_PROGRAM_TYPE_CGROUP_SOCK_ADDR,
     &EBPF_ATTACH_TYPE_CGROUP_INET6_RECV_ACCEPT,
     BPF_PROG_TYPE_CGROUP_SOCK_ADDR,
     BPF_CGROUP_INET6_RECV_ACCEPT}};

// SOCK_OPS program information.
static const ebpf_context_descriptor_t _ebpf_sock_ops_context_descriptor = {
    sizeof(bpf_sock_ops_t),
    -1, // Offset into ctx struct for pointer to data, or -1 if none.
    -1, // Offset into ctx struct for pointer to data, or -1 if none.
    -1, // Offset into ctx struct for pointer to metadata, or -1 if none.
};

static const ebpf_program_type_descriptor_t _ebpf_sock_ops_program_type_descriptor = {
    EBPF_PROGRAM_TYPE_DESCRIPTOR_HEADER,
    "sockops",
    &_ebpf_sock_ops_context_descriptor,
    EBPF_PROGRAM_TYPE_SOCK_OPS_GUID,
    BPF_PROG_TYPE_SOCK_OPS,
    0};

enum _sock_ops_global_helper_functions
{
    SOCK_OPS_GLOBAL_HELPER_GET_CURRENT_PID_TGID,
};

// SOCK_OPS global helper function prototypes.
static const ebpf_helper_function_prototype_t _ebpf_sock_ops_global_helper_function_prototype[] = {
    {.header = EBPF_HELPER_FUNCTION_PROTOTYPE_HEADER,
     .helper_id = BPF_FUNC_get_current_pid_tgid,
     .name = "bpf_get_current_pid_tgid",
     .return_type = EBPF_RETURN_TYPE_INTEGER,
     .arguments = {},
     .implicit_context = true}};
static const ebpf_program_info_t _ebpf_sock_ops_program_info = {
    EBPF_PROGRAM_INFORMATION_HEADER,
    &_ebpf_sock_ops_program_type_descriptor,
    0,
    NULL,
    EBPF_COUNT_OF(_ebpf_sock_ops_global_helper_function_prototype),
    _ebpf_sock_ops_global_helper_function_prototype};

static const ebpf_program_section_info_t _ebpf_sock_ops_section_info[] = {
    {{EBPF_PROGRAM_SECTION_INFORMATION_CURRENT_VERSION, EBPF_PROGRAM_SECTION_INFORMATION_CURRENT_VERSION_SIZE},
     L"sockops",
     &EBPF_PROGRAM_TYPE_SOCK_OPS,
     &EBPF_ATTACH_TYPE_CGROUP_SOCK_OPS,
     BPF_PROG_TYPE_SOCK_OPS,
     BPF_CGROUP_SOCK_OPS}};
