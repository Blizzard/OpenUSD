//
// Copyright 2016 Pixar
//
// Licensed under the Apache License, Version 2.0 (the "Apache License")
// with the following modification; you may not use this file except in
// compliance with the Apache License and the following modification to it:
// Section 6. Trademarks. is deleted and replaced with:
//
// 6. Trademarks. This License does not grant permission to use the trade
//    names, trademarks, service marks, or product names of the Licensor
//    and its affiliates, except as required to comply with Section 4(c) of
//    the License and to reproduce the content of the NOTICE file.
//
// You may obtain a copy of the Apache License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the Apache License with the above modification is
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied. See the Apache License for the specific
// language governing permissions and limitations under the Apache License.
//

#include "pxr/pxr.h"
#include "pxr/base/vt/array.h"
#include "pxr/base/vt/typeHeaders.h"
#include "pxr/base/tf/envSetting.h"
#include "pxr/base/tf/stackTrace.h"
#include "pxr/base/tf/stringUtils.h"

PXR_NAMESPACE_OPEN_SCOPE

TF_DEFINE_ENV_SETTING(
    VT_LOG_STACK_ON_ARRAY_DETACH_COPY, false,
    "Log a stack trace when a VtArray is copied to detach it from shared "
    "storage, to help track down unintended copies.");

void
Vt_ArrayBase::_DetachCopyHook(char const *funcName) const
{
    static bool log = TfGetEnvSetting(VT_LOG_STACK_ON_ARRAY_DETACH_COPY);
    if (ARCH_UNLIKELY(log)) {
        TfLogStackTrace(TfStringPrintf("Detach/copy VtArray (%s)", funcName));
    }
}

// Instantiate basic array templates.
#define VT_ARRAY_EXPLICIT_INST(r, unused, elem) \
    template class VT_API VtArray< VT_TYPE(elem) >;
BOOST_PP_SEQ_FOR_EACH(VT_ARRAY_EXPLICIT_INST, ~, VT_SCALAR_VALUE_TYPES)


PXR_NAMESPACE_CLOSE_SCOPE
