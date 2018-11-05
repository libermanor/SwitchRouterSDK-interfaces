/*
 *  Copyright (C) 2014-2018. Mellanox Technologies, Ltd. ALL RIGHTS RESERVED.
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

#ifndef __SX_API_ISSU_H__
#define __SX_API_ISSU_H__

#include <sx/sdk/sx_api.h>

/************************************************
 *  API functions
 ***********************************************/

/**
 *  This function sets the log verbosity level of ISSU MODULE.
 *  Supported devices: SwitchX, SwitchX2, Spectrum.
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] verbosity_target         - set verbosity of : API / MODULE / BOTH
 * @param[in] module_verbosity_level   - ISSU module verbosity level
 * @param[in] api_verbosity_level      - ISSU API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_issu_log_verbosity_level_set(const sx_api_handle_t           handle,
                                                const sx_log_verbosity_target_t verbosity_target,
                                                const sx_verbosity_level_t      module_verbosity_level,
                                                const sx_verbosity_level_t      api_verbosity_level);

/**
 * This API gets the log verbosity level of ISSU MODULE.
 * Supported devices: Spectrum.
 *
 * @param[in]  handle                   - SX-API handle
 * @param[in]  verbosity_target         - get verbosity of : API / MODULE / BOTH
 * @param[out] module_verbosity_level_p - ISSU module verbosity level
 * @param[out] api_verbosity_level_p    - ISSU API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE when parameter exceeds range.
 */
sx_status_t sx_api_tunnel_log_verbosity_level_get(const sx_api_handle_t           handle,
                                                  const sx_log_verbosity_target_t verbosity_target,
                                                  sx_verbosity_level_t           *module_verbosity_level_p,
                                                  sx_verbosity_level_t           *api_verbosity_level_p);
/**
 * Used for "fast-fast" boot mode to trigger the preparation for ISSU before
 * SDK shut down. This API also switches the active FW to the new one in case
 * such exists.
 * Supported devices: Spectrum.
 *
 * @param[in] handle                   - SX-API handle
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_issu_start_set(const sx_api_handle_t handle);

/**
 * Used for "fast-fast" boot mode to notify the SDK that the
 * configuration stage of the ISSU process has ended.
 * Supported devices: Spectrum.
 *
 * @param[in] handle                   - SX-API handle
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_issu_end_set(const sx_api_handle_t handle);

/**
 * Used for "Warm" boot mode to prepare the SDK for CRIU hibernation
 * Supported devices: Spectrum.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] pause_params_p - pause params.
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS - Operation completes successfully
 * @return SX_STATUS_PARAM_ERROR - Input parameters error - NULL
 *         handle
 * @return SX_STATUS_COMM_ERROR - Input parameters error -
 *         Invalid handle
 */
sx_status_t sx_api_issu_pause_set(const sx_api_handle_t  handle,
                                  const sx_issu_pause_t *pause_params_p);

/**
 * Used for "Warm" boot mode to "resume" the SDK from CRIU hibernation
 * Supported devices: Spectrum.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] resume_params_p - resume params.
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS - Operation completes successfully
 * @return SX_STATUS_PARAM_ERROR - Input parameters error - NULL
 *         handle
 * @return SX_STATUS_COMM_ERROR - Input parameters error -
 *         Invalid handle
 */
sx_status_t sx_api_issu_resume_set(const sx_api_handle_t   handle,
                                   const sx_issu_resume_t *resume_params_p);

#endif /* __SX_API_ISSU_H__ */
