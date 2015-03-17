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

#ifndef __SX_API_LAG_H__
#define __SX_API_LAG_H__

#include <sx/sdk/sx_api.h>


/************************************************
 *  API functions
 ***********************************************/

/**
 * This function sets the log verbosity level of LAG MODULE.
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] verbosity_target         - set verbosity of : API / MODULE / BOTH
 * @param[in] module_verbosity_level   - LAG module verbosity level
 * @param[in] api_verbosity_level      - LAG API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_lag_log_verbosity_level_set(const sx_api_handle_t           handle,
                                               const sx_log_verbosity_target_t verbosity_target,
                                               const sx_verbosity_level_t      module_verbosity_level,
                                               const sx_verbosity_level_t      api_verbosity_level);

/**
 * This function sets the log verbosity level of LAG MODULE.
 *
 * @param[in]  handle                   - SX-API handle
 * @param[in]  verbosity_target         - get verbosity of : API / MODULE / BOTH
 * @param[out] module_verbosity_level_p - LAG module verbosity level
 * @param[out] api_verbosity_level_p    - LAG API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_lag_log_verbosity_level_get(const sx_api_handle_t           handle,
                                               const sx_log_verbosity_target_t verbosity_target,
                                               sx_verbosity_level_t           *module_verbosity_level_p,
                                               sx_verbosity_level_t           *api_verbosity_level_p);

/**
 *  This function creates/destroys a new/existing LAG port group in the SDK.
 *  This function also adds/deletes ports to/from an existing LAG port group in the SDK.
 *
 *  Note:
 *  - All ports must be deleted from a LAG port groups before the group is destroyed.
 *  - Creating a LAG group and adding ports to it in the same api call is not supported.
 *
 * @param[in] handle             - SX-API handle
 * @param[in] cmd                - CREATE/DESTROY/ADD/DELETE
 * @param[in] swid               - switch (virtual partition) ID
 * @param[in,out] lag_log_port_p - In: Already created LAG ports group ID
 *                                 Out: Newly created LAG ports group ID
 * @param[in] log_port_list_p    - List of logical ports to ADD/DELETE to/from a LAG ports group
 * @param[in] log_port_cnt       - Number of logical ports to ADD/DELETE to/from a LAG ports group
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if a requested element is not found in the DB
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameter exceeds its range
 */
sx_status_t sx_api_lag_port_group_set(const sx_api_handle_t   handle,
                                      const sx_access_cmd_t   cmd,
                                      const sx_swid_t         swid,
                                      sx_port_log_id_t       *lag_log_port_p,
                                      const sx_port_log_id_t *log_port_list_p,
                                      const uint32_t          log_port_cnt);

/**
 *  This function retrieves an existing LAG ports group from the SDK.
 *
 *  Note: If the output ports list is NULL, only the number of ports in the LAG is retrieved.
 *
 * @param[in] handle                - SX-API handle
 * @param[in] swid                  - switch (virtual partition) ID
 * @param[in] lag_log_port          - LAG ports group ID
 * @param[in,out] log_port_list_p   - list of logical ports
 * @param[in,out] log_port_cnt_p    - In: Number of logical ports in list
 *                                    Out: Number of logical ports in LAG
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if a requested element is not found in the DB
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameter exceeds its range
 */
sx_status_t sx_api_lag_port_group_get(const sx_api_handle_t  handle,
                                      const sx_swid_t        swid,
                                      const sx_port_log_id_t lag_log_port,
                                      sx_port_log_id_t      *log_port_list_p,
                                      uint32_t              *log_port_cnt_p);


/**
 *  This function enables/disables collection on a specific LAG port.
 *
 * @param[in] handle         - SX-API handle
 * @param[in] lag_log_port   - a logical port number representing
 *                             the LAG ports group
 * @param[in] log_port       - logical port number
 * @param[in] collector_mode - collector mode
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO if SxD driver function fails
 * @return SX_STATUS_CMD_UNSUPPORTED if command is not supported
 */

sx_status_t sx_api_lag_port_collector_set(const sx_api_handle_t     handle,
                                          const sx_port_log_id_t    lag_log_port,
                                          const sx_port_log_id_t    log_port,
                                          const sx_collector_mode_t collector_mode);


/**
 *  This function returns information whether collection is enabled
 *  or disabled on a specific port in a LAG port.
 *
 * @param[in] handle            - SX-API handle.
 * @param[in] lag_log_port      - a logical port number representing
 *                                the LAG ports group
 * @param[in] log_port          - logical port number
 * @param[out] collector_mode_p - collector mode.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameter exceeds its range
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 */

sx_status_t sx_api_lag_port_collector_get(const sx_api_handle_t  handle,
                                          const sx_port_log_id_t lag_log_port,
                                          const sx_port_log_id_t log_port,
                                          sx_collector_mode_t   *collector_mode_p);

/**
 *  This function enables/disables distribution on a specific LAG port.
 *
 * @param[in] handle           - SX-API handle
 * @param[in] lag_log_port     - a logical port number representing
 *                               the LAG ports group
 * @param[in] log_port         - logical port number
 * @param[in] distributor_mode - distributor mode
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 * @return SX_STATUS_ENTRY_ALREADY_EXISTS if requested element is already exists
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO if SxD driver function fails
 * @return SX_STATUS_CMD_UNSUPPORTED if command is not supported
 */
sx_status_t sx_api_lag_port_distributor_set(const sx_api_handle_t       handle,
                                            const sx_port_log_id_t      lag_log_port,
                                            const sx_port_log_id_t      log_port,
                                            const sx_distributor_mode_t distributor_mode);


/**
 *  This function returns information whether distribution is enabled
 *  or disabled on a specific port in a LAG port.
 *
 * @param[in] handle              - SX-API handle.
 * @param[in] lag_log_port        - a logical port number representing
 *                                  the LAG ports group
 * @param[in] log_port            - logical port number
 * @param[out] distributor_mode_p - distributer mode.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameter exceeds its range
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 */

sx_status_t sx_api_lag_port_distributor_get(const sx_api_handle_t  handle,
                                            const sx_port_log_id_t lag_log_port,
                                            const sx_port_log_id_t log_port,
                                            sx_distributor_mode_t *distributor_mode_p);

/**
 *  This function configures the flow indicators that impact the
 *  LAG hash distribution function.
 *
 *  @param[in] handle               - SX-API handle
 *  @param[in] lag_hash_param_p     - hash parameters
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 * @return SX_STATUS_NO_MEMORY if memory allocation fails
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO if SxD driver function fails
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameter exceeds its range
 */
sx_status_t sx_api_lag_hash_flow_params_set(const sx_api_handle_t      handle,
                                            const sx_lag_hash_param_t *lag_hash_param_p);


/**
 *  This function retrieves the flow indicators that impact the
 *  LAG hash distribution function.
 *
 *  @param[in] handle               - SX-API handle
 *  @param[out] lag_hash_param_p    - hash parameters to be retrieved
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO if SxD driver function fails
 */
sx_status_t sx_api_lag_hash_flow_params_get(const sx_api_handle_t handle,
                                            sx_lag_hash_param_t  *lag_hash_param_p);

/**
 *  This function CREATEs/DESTROYs a redirection between a LAG and a
 *  destination LAG.
 *  Redirection doesn't align LAG configuration, only TX traffic.
 *
 *  Note:
 *  - Redirect operation is valid only between 2 LAGs. Cannot create chain of
 *    redirected LAGs.
 *  - Redirect is L2 action, and not valid for Router Port.
 *
 * @param[in] handle                - SX-API handle
 * @param[in] cmd                   - CREATE/DESTROY
 * @param[in] lag_log_port          - LAG logical ID
 * @param[in] redirect_lag_log_port - LAG logical ID which lag_log_port now
 *                                    points to. Ignored in DESTROY command.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO if SxD driver function fails
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 * @return SX_STATUS_CMD_UNSUPPORTED if command is not supported
 */
sx_status_t sx_api_lag_redirect_set(const sx_api_handle_t  handle,
                                    const sx_access_cmd_t  cmd,
                                    const sx_port_log_id_t lag_log_port,
                                    const sx_port_log_id_t redirect_lag_log_port);

/**
 *  This function returns information whether a given LAG is redirected.
 *  If so, the redirected LAG logical ID is return.
 *
 * @param[in] handle                     - SX-API handle.
 * @param[in] lag_log_port               - LAG logical ID.
 * @param[out] is_redirected_p           - is lag_port redirected.
 * @param[out] redirected_lag_log_port_p - the LAG logical ID which lag_log_port
 *                                         point to.
 *                                         Valid when the LAG is redirected.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 */
sx_status_t sx_api_lag_redirect_get(const sx_api_handle_t  handle,
                                    const sx_port_log_id_t lag_log_port,
                                    boolean_t             *is_redirected_p,
                                    sx_port_log_id_t      *redirected_lag_log_port_p);

/**
 *  This function returns all LAGs redirected to the given LAG.
 *  Call this API with lag_log_port_list_p=NULL will set to lag_log_port_cnt_p
 *  the number of LAG redirected to lag_port.
 *
 * @param[in] handle                    - SX-API handle
 * @param[in] lag_log_port              - LAG logical ID
 * @param[in,out] lag_log_port_list_p   - pointer to array of LAG port list
 * @param[in,out] lag_log_port_cnt_p    - number of LAG ports in a list retrieve
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 */
sx_status_t sx_api_lag_redirected_lags_get(const sx_api_handle_t  handle,
                                           const sx_port_log_id_t lag_log_port,
                                           sx_port_log_id_t      *lag_log_port_list_p,
                                           uint32_t              *lag_log_port_cnt_p);

#endif /* __SX_API_LAG_H__ */
