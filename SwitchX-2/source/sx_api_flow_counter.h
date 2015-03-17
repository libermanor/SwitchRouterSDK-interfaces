/*
 *  Copyright (C) 2014. Mellanox Technologies, Ltd. ALL RIGHTS RESERVED.
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

#ifndef __SX_API_FLOW_COUNTER_H__
#define __SX_API_FLOW_COUNTER_H__

#include <sx/sdk/sx_api.h>

/**
 * This function sets the log verbosity level of FLOW COUNTER MODULE
 * @param[in] handle                   - SX-API handle
 * @param[in] verbosity_target         - set verbosity of : API / MODULE / BOTH
 * @param[in] module_verbosity_level   - FLOW COUNTER module verbosity level
 * @param[in] api_verbosity_level      - FLOW COUNTER API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 *         SX_STATUS_PARAM_ERROR if any input parameters is invalid
 *         SX_STATUS_ERROR general error
 */
sx_status_t sx_api_flow_counter_log_verbosity_level_set(const sx_api_handle_t           handle,
                                                        const sx_log_verbosity_target_t verbosity_target,
                                                        const sx_verbosity_level_t      module_verbosity_level,
                                                        const sx_verbosity_level_t      api_verbosity_level);

/**
 * This function gets the log verbosity level of FLOW COUNTER MODULE
 *
 * @param[in]  handle                   - SX-API handle
 * @param[in]  verbosity_target         - get verbosity of : API / MODULE / BOTH
 * @param[out] module_verbosity_level_p - FLOW COUNTER module verbosity level
 * @param[out] api_verbosity_level_p    - FLOW COUNTER API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 *         SX_STATUS_PARAM_ERROR if any input parameters is invalid
 *         SX_STATUS_ERROR general error
 */
sx_status_t sx_api_flow_counter_log_verbosity_level_get(const sx_api_handle_t           handle,
                                                        const sx_log_verbosity_target_t verbosity_target,
                                                        sx_verbosity_level_t           *module_verbosity_level_p,
                                                        sx_verbosity_level_t           *api_verbosity_level_p);

/**
 *  This function is used to create packets/bytes counter.
 *  for creation use command CREATE and supply counter_type.
 *  flow_counter_id is returned on successful creation.
 *  for destroying an flow counter it is required that the flow
 *  counter is not bound to an ACL and the flow_counter_id should be
 *  provided.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - CREATE / DESTROY
 * @param[in] counter_type - counter type used
 * @param[in,out] counter_id_p - Flow counter ID as described above
 *
 *  @return SX_STATUS_SUCCESS if operation completes successfully
 *  @return SX_STATUS_PARAM_NULL or SX_STATUS_PARAM_EXCEEDS_RANGE if any input
 *  parameter is invalid
 *  @return SX_STATUS_NO_RESOURCES if no Flow counter is available to
 *  create
 *  @return SX_STATUS_CMD_UNSUPPORTED if unsupported command is
 *  requested
 *  @return SX_STATUS_INVALID_HANDLE if called Invalid Handle
 *  @return SX_STATUS_ENTRY_NOT_FOUND if called with DESTROY command and counter
 *  does not exist
 */
sx_status_t sx_api_flow_counter_set(const sx_api_handle_t        handle,
                                    const sx_access_cmd_t        cmd,
                                    const sx_flow_counter_type_t counter_type,
                                    sx_flow_counter_id_t        *counter_id_p);

/**
 *  This function retrieves the Flow Counter.
 *
 * @param[in] handle - SX-API handle
 * @param[in] counter_id - Flow counter ID
 * @param[out] counter_val_p - counter value.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE: event mode out of range.
 * @return SX_STATUS_MESSAGE_SIZE_ZERO: Message size error.
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT: Message size error.
 * @return SX_STATUS_COMM_ERROR: Commiunication error - send fail.
 * @return SX_STATUS_INVALID_HANDLE: Invalid Handle.
 */
sx_status_t sx_api_flow_counter_get(const sx_api_handle_t      handle,
                                    const sx_access_cmd_t      cmd,
                                    const sx_flow_counter_id_t counter_id,
                                    sx_flow_counter_val_t     *counter_val_p);

/**
 *  This function clear a specific Flow Counter.
 *
 * @param[in] handle - SX-API handle
 * @param[in] counter_id - Flow counter ID to clear
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE: event mode out of range.
 * @return SX_STATUS_MESSAGE_SIZE_ZERO: Message size error.
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT: Message size error.
 * @return SX_STATUS_COMM_ERROR: Commiunication error - send fail.
 * @return SX_STATUS_INVALID_HANDLE: Invalid Handle.
 * @return SX_STATUS_ENTRY_NOT_FOUND: Clear an invalid counter.
 */
sx_status_t sx_api_flow_counter_clear_set(const sx_api_handle_t      handle,
                                          const sx_flow_counter_id_t counter_id);

#endif
