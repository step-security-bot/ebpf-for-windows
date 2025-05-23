// Copyright (c) eBPF for Windows contributors
// SPDX-License-Identifier: MIT

#include "api_common.hpp"
#include "ebpf_program_types.h"
#include "ebpf_result.h"
#include "ebpf_shared_framework.h"
#include "platform.h"
#include "platform.hpp"
#include "windows_platform_common.hpp"

#include <map>
#include <stdexcept>
#include <vector>

static const ebpf_helper_function_prototype_t*
_get_helper_function_prototype(const ebpf_program_info_t* info, unsigned int n)
{
    for (uint32_t i = 0; i < info->count_of_program_type_specific_helpers; i++) {
        if (n == info->program_type_specific_helper_prototype[i].helper_id) {
            return &info->program_type_specific_helper_prototype[i];
        }
    }
    return nullptr;
}

// Check whether a given integer is a valid helper ID.
bool
is_helper_usable_windows(int32_t n)
{
    const ebpf_program_info_t* info = nullptr;
    ebpf_result_t result = get_program_type_info_from_tls(&info);
    if (result != EBPF_SUCCESS) {
        throw std::runtime_error(std::string("helper not usable: ") + std::to_string(n));
    }
    return _get_helper_function_prototype(info, n) != nullptr;
}

// Get the prototype for the helper with a given ID.
prevail::EbpfHelperPrototype
get_helper_prototype_windows(int32_t n)
{
    const ebpf_program_info_t* info = nullptr;
    ebpf_result_t result = get_program_type_info_from_tls(&info);
    if (result != EBPF_SUCCESS) {
        throw std::runtime_error(std::string("program type info not found."));
    }
    prevail::EbpfHelperPrototype verifier_prototype = {0};

    if (info->program_type_descriptor == nullptr) {
        throw std::runtime_error(std::string("program type descriptor not found."));
    }
    verifier_prototype.context_descriptor = info->program_type_descriptor->context_descriptor;

    // Helper ID needs to be non-negative for Windows.
    if (n < 0) {
        throw std::runtime_error(std::string("helper ID is negative: ") + std::to_string(n));
    }

    const ebpf_helper_function_prototype_t* raw_prototype = _get_helper_function_prototype(info, n);
    if (raw_prototype == nullptr) {
        throw std::runtime_error(std::string("helper prototype not found: ") + std::to_string(n));
    }
    verifier_prototype.name = raw_prototype->name;

    verifier_prototype.return_type = raw_prototype->return_type;

    for (int i = 0; i < 5; i++) {
        verifier_prototype.argument_type[i] = raw_prototype->arguments[i];
    }

    verifier_prototype.reallocate_packet = raw_prototype->flags.reallocate_packet == TRUE;

    return verifier_prototype;
}
