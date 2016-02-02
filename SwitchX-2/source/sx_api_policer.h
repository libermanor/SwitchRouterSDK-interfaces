/*
 *  Copyright (C) 2014-2015. Mellanox Technologies, Ltd. ALL RIGHTS RESERVED.
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

#ifndef __SX_API_POLICER_H__
#define __SX_API_POLICER_H__

#include <sx/sdk/sx_api.h>


/************************************************
 *  API functions
 ***********************************************/

/**
 * This function sets the log verbosity level of POLICER MODULE
 * Supported devices: SwitchX, SwitchX2, Spectrum.
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] verbosity_target         - set verbosity of : API / MODULE / BOTH
 * @param[in] module_verbosity_level   - POLICER module verbosity level
 * @param[in] api_verbosity_level      - POLICER API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 *         SX_STATUS_PARAM_ERROR if any input parameters is invalid
 *         SX_STATUS_ERROR general error
 */
sx_status_t sx_api_policer_log_verbosity_level_set(const sx_api_handle_t           handle,
                                                   const sx_log_verbosity_target_t verbosity_target,
                                                   const sx_verbosity_level_t      module_verbosity_level,
                                                   const sx_verbosity_level_t      api_verbosity_level);

/**
 * This function gets the log verbosity level of POLICER MODULE
 * Supported devices: SwitchX, SwitchX2, Spectrum.
 *
 * @param[in]  handle                   - SX-API handle
 * @param[in]  verbosity_target         - get verbosity of : API / MODULE / BOTH
 * @param[out] module_verbosity_level_p - POLICER module verbosity level
 * @param[out] api_verbosity_level_p    - POLICER API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 *         SX_STATUS_PARAM_ERROR if any input parameters is invalid
 *         SX_STATUS_ERROR general error
 */
sx_status_t sx_api_policer_log_verbosity_level_get(const sx_api_handle_t           handle,
                                                   const sx_log_verbosity_target_t verbosity_target,
                                                   sx_verbosity_level_t           *module_verbosity_level_p,
                                                   sx_verbosity_level_t           *api_verbosity_level_p);

/**
 * This function creates/destroy/edit a policer in the system.
 * Supported devices: SwitchX, SwitchX2, Spectrum.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - SX_ACCESS_CMD_CREATE: create a new policer and returns a policer ID in policer_id_p
 *                  SX_ACCESS_CMD_DESTROY: destroy an existing policer (according to policer_id_p)
 *                  SX_ACCESS_CMD_EDIT: edit configuration parameters of an existing policer.
 *                  only CIR, EIR, EBS, CBS, yellow action and red action can be edited
 * @param[in] policer_attr_p - policer attributes. Ignored when cmd is DESTROY.
 * @param[in,out] policer_id_p - policer ID
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_CMD_UNSUPPORTED if cmd is SX_ACCESS_CMD_DESTROY or any other unsupported command
 * @return SX_STATUS_PARAM_ERROR if any of the input parameters is invalid
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_NO_RESOURCES if there are no more resources
 * @return SX_STATUS_RESOURCE_IN_USE if trying to destroy a binded policer
 * @return SX_STATUS_WRONG_POLICER_TYPE if wrong policer_type was supplied
 */
sx_status_t sx_api_policer_set(const sx_api_handle_t          handle,
                               const sx_access_cmd_t          cmd,
                               const sx_policer_attributes_t *policer_attr_p,
                               sx_policer_id_t               *policer_id_p);

/**
 * This function gets policer attributes.
 * Supported devices: SwitchX, SwitchX2, Spectrum.
 *
 * @param[in] handle - SX-API handle
 * @param[in] policer_id - policer ID
 * @param[out] policer_attr_p - pointer to policer attributes
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any other input error
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_policer_get(const sx_api_handle_t    handle,
                               const sx_policer_id_t    policer_id,
                               sx_policer_attributes_t *policer_attr_p);

/**
 * This function clears policer counters values.
 * Supported devices: Spectrum.
 * @param[in] handle - SX-API handle
 * @param[in] policer_id - policer ID
 * @param[in] clear_counters - which counters to clear
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any other input error
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_policer_counters_clear_set(const sx_api_handle_t              handle,
                                              const sx_policer_id_t              policer_id,
                                              const sx_policer_counters_clear_t *clear_counters_p);

/**
 * This function retrieves policer counters values.
 * Supported devices: Spectrum.
 *
 * @param[in] handle - SX-API handle
 * @param[in] policer_id - policer ID
 * @param[out] policer_counters_p - pointer to a policer counter struct.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any other input error
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_policer_counters_get(const sx_api_handle_t  handle,
                                        const sx_policer_id_t  policer_id,
                                        sx_policer_counters_t *policer_counters_p);

#endif /* __SX_API_POLICER_H__ */
