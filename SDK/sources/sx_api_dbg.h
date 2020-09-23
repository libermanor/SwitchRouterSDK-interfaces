/*
 *  Copyright (C) 2014-2020. Mellanox Technologies, Ltd. ALL RIGHTS RESERVED.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License"); you may
 *    not use this file except in compliance with the License. You may obtain
 *    a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 *    THIS CODE IS PROVIDED ON AN  *AS IS* BASIS, WITHOUT WARRANTIES OR
 *    CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
 *    LIMITATION ANY IMPLIED WARRANTIES OR CONDITIONS OF TITLE, FITNESS
 *    FOR A PARTICULAR PURPOSE, MERCHANTABLITY OR NON-INFRINGEMENT.
 *
 *    See the Apache Version 2.0 License for specific language governing
 *    permissions and limitations under the License.
 *
 */

#ifndef __SX_API_DBG_H__
#define __SX_API_DBG_H__

#include <sx/sdk/sx_api.h>
#include <sx/sdk/sx_dbg.h>
#include <sx/sdk/sx_strings.h>


/************************************************
 *  API functions
 ***********************************************/

/**
 * This API generates debug dump of all SDK modules, SX-core and driver.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle              - SX-API handle.
 * @param[in] dump_file_path      - Full path file name.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if the path string length is greater than 256
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_dbg_generate_dump(const sx_api_handle_t handle,
                                     const char           *dump_file_path);


/**
 * This API should be used only for debug purposes.
 * It is used to access internal commands for the ATcam (SPACE) module.
 * Supported devices: Spectrum2, Spectrum3.
 *
 * @param[in] handle                    - SX-API handle
 * @param[in] sx_dbg_atcam_cmd_info_t   - One of the supported within atcam module to execute directly
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_dbg_atcam(const sx_api_handle_t handle, sx_dbg_atcam_cmd_info_t* cmd_p);

/**
 * This API generates debug dump extra info, for modules monitored by the SDK
 * Supported devices: Pelican, Eagle, Spectrum, Spectrum2, Quantum,  Spectrum3
 *
 * @param[in] handle              - SX-API handle.
 * @param[in] sx_dbg_extra_info_t dbg_params - parameters of debug dump extraction
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if any parameter exceeds range limitation
 * @return SX_STATUS_TIMEOUT in case of a timeout in synchronous mode. if the call was asynchronous this RC will be in the completion event
 * @return SX_STATUS_ERROR general error
 */

sx_status_t sx_api_dbg_generate_dump_extra(const sx_api_handle_t      handle,
                                           const sx_dbg_extra_info_t *dbg_params);

/**
 * This API is used to set the SDK debug control parameters
 * which will be enacted in case a health issue was discovered.
 * in “auto” mode the SDK will automatically collect debug information,
 * and alert the user both that the issue occurred and that collection is done
 * in “non-auto” mode the SDK will only alert the user that a “health event” has occurred
 * in both modes there is no “automatic re-arm”
 * the user must explicitly call the API with the required parameters in order to arm / re-arm the feature
 *
 * Supported devices: Pelican, Eagle, Spectrum, Spectrum2, Quantum…
 *
 * @param[in] handle              - SX-API handle.
 * @param[in] params
 *             policy              - the policy we wish to set
 *             arm                 - Should the debug reporting / extraction (according to policy) be armed/re-armed
 * @param[in] sx_dbg_policy_info policy_params: for future enhancement
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if the path string length is greater than sx_dbg_policy_e
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_dbg_control(const sx_api_handle_t handle, const sx_dbg_control_params_t *params);

#endif /* __SX_API_DBG_H__ */
