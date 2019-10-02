/*
 *  Copyright (C) 2014-2019. Mellanox Technologies, Ltd. ALL RIGHTS RESERVED.
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

#ifndef __SX_API_SPAN_H__
#define __SX_API_SPAN_H__

#include <sx/sdk/sx_api.h>
#include <sx/sdk/sx_strings.h>

/************************************************
 *  API functions
 ***********************************************/

/**
 * This function sets the log verbosity level of SPAN MODULE
 * Supported devices: Spectrum, Spectrum2.
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] verbosity_target         - set verbosity of : API / MODULE / BOTH
 * @param[in] module_verbosity_level   - SPAN module verbosity level
 * @param[in] api_verbosity_level      - SPAN API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 *         SX_STATUS_PARAM_ERROR if any input parameters is invalid
 *         SX_STATUS_ERROR general error
 */
sx_status_t sx_api_span_log_verbosity_level_set(const sx_api_handle_t           handle,
                                                const sx_log_verbosity_target_t verbosity_target,
                                                const sx_verbosity_level_t      module_verbosity_level,
                                                const sx_verbosity_level_t      api_verbosity_level);

/**
 * This function gets the log verbosity level of SPAN MODULE
 * Supported devices: Spectrum, Spectrum2.
 *
 * @param[in]  handle                   - SX-API handle
 * @param[in]  verbosity_target         - get verbosity of : API / MODULE / BOTH
 * @param[out] module_verbosity_level_p - SPAN module verbosity level
 * @param[out] api_verbosity_level_p    - SPAN API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 *         SX_STATUS_PARAM_ERROR if any input parameters is invalid
 *         SX_STATUS_ERROR general error
 */
sx_status_t sx_api_span_log_verbosity_level_get(const sx_api_handle_t           handle,
                                                const sx_log_verbosity_target_t verbosity_target,
                                                sx_verbosity_level_t           *module_verbosity_level_p,
                                                sx_verbosity_level_t           *api_verbosity_level_p);

/**
 *  This function creates a SPAN session and allocate the
 *  session id. To modify the session attributes, the API should
 *  be called with cmd= EDIT, the session's ID and the new
 *  session's attributes. To delete a SPAN session the API
 *  should be called we cmd = DESTROY. In Spectrum, EDIT need another
 *  session resource as interim session, so if all session resource
 *  are already allocated, EDIT will be failed due to no resource.
 *  In case packet with encapsulation header is mirrored to analyzer
 *  port with size larger than analyzer port MTU, truncation should
 *  be enabled by user to avoid packet being discarded. User should
 *  set truncate size = MTU - encapsulation or smaller.
 *
 *  Supported devices: Spectrum, Spectrum2.
 *
 * @param[in] handle                            - SX-API handle.
 * @param[in] access_cmd                        - CREATE / EDIT / DESTROY
 * @param[in] span_session_params_p - Generic SPAN session params
 * @param[in,out] span_session_id_p - SPAN session ID
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if  pointer params is  NULL
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ACCESS_CMD_UNSUPPORTED if unsupported command is requested
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO if SxD driver function returns fail
 * @return SX_STATUS_NO_MEMORY if problems with memory allocation occurs
 * @return SX_STATUS_NO_RESOURCES if pool cannot provide object
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 */
sx_status_t sx_api_span_session_set(const sx_api_handle_t           handle,
                                    const sx_access_cmd_t           cmd,
                                    const sx_span_session_params_t *span_session_params_p,
                                    sx_span_session_id_t           *span_session_id_p);

/**
 *  This function gets the SPAN session information.
 *  Supported devices: Spectrum, Spectrum2.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] span_session_id - SPAN session ID
 * @param[out] span_session_params - session params
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 *
 */
sx_status_t sx_api_span_session_get(const sx_api_handle_t      handle,
                                    const sx_span_session_id_t span_session_id,
                                    sx_span_session_params_t  *span_session_params_p);
/**
 *  This function iteratively returns the current SPAN sessions .
 *  Supported devices: Spectrum, Spectrum2.
 *
 * @param[in] handle               - SX-API handle.
 * @param[in] cmd                  - supported commands:GET/GET_FIRST/GETNEXT
 * @param[in] span_session_key_p   - A reference span session id key
 * @param[in] filter_p             - Return only span sessions that match this filter param if enabled
 * @param[out] span_session_list_p - return list of span session ids
 * @param[in,out] span_session_cnt - [in]  number of sessions to get
 *                                   [out] number of sessions retrieved
 *
 * The following use case scenarios apply with different input parameters X = don't-care
 * - 1) cmd = SX_ACCESS_CMD_GET, key = X, Filter = X, list = X, Count = 0:
 *        In this case the API will return the total number of span session count from
 *        internal db.
 *
 * - 2) cmd = SX_ACCESS_CMD_GET, key = valid/invalid, Filter = X, list = Valid, Count = 1:
 *        In this case the API will check if the specified key exists. if it does
 *        the key will be returned in the list along with a count of 1.
 *        If the key does not exist an empty list will be returned with count = 0
 *
 * - 3) cmd = SX_ACCESS_CMD_GET, key = valid, Filter = X, list is Valid, Count > 1:
 *        A count >1 will be treated as a count of 1 and the behaviour will be same
 *        as earlier GET use cases.
 *
 * - 4) cmd = SX_ACCESS_CMD_GET_FIRST/SX_ACCESS_CMD_GETNEXT, key = X, Filter = X,
 *        list = Null, Count = 0:
 *        For either SX_ACCESS_CMD_GET_FIRST/SX_ACCESS_CMD_GETNEXT a zero count
 *        will return an empty list.
 *
 * - 5) cmd = SX_ACCESS_CMD_GET_FIRST, key = X, Filter = X, list = Valid, Count > 0:
 *        In this case the API will return the first span session IDs starting from
 *        the head of the database. The total elements fetched will be returned
 *        as the return count.  Note: return count may be less than or equal to
 *        the requested count. The key is dont-care but a non-Null return
 *        list pointer must be provided.
 *
 * - 6) cmd = SX_ACCESS_CMD_GETNEXT, key = valid/invalid, Filter = X,
 *        list = Valid, Count > 0:
 *        In this case the API will return the next set of IDs starting from
 *        the next valid span session id after the specified key. The total elements
 *        fetched will be returned as the return count. Note: return count may be less
 *        than or equal to the requested count. If no valid next counter exists
 *        in the DB (key = end of list, or invalid key specified, or key too
 *        large), an empty list will be returned.
 *
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 * @return SX_STATUS_CMD_UNSUPPORTED - if invalid cmd is passed
 * @return SX_STATUS_DB_NOT_INITIALIZED - if internal DB is not initialized
 *
 */

sx_status_t sx_api_span_session_iter_get(const sx_api_handle_t       handle,
                                         const sx_access_cmd_t       cmd,
                                         const sx_span_session_id_t *span_session_key_p,
                                         const sx_span_filter_t     *filter_p,
                                         sx_span_session_id_t       *span_session_list_p,
                                         uint32_t                   *span_session_cnt_p);
/**
 *  This function set SPAN session Admin State.
 *  Supported devices: Spectrum, Spectrum2.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] span_session_id - SPAN session ID
 * @param[in] admin_state - SPAN session Admin state (Enable/Disable).
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 */
sx_status_t sx_api_span_session_state_set(const sx_api_handle_t      handle,
                                          const sx_span_session_id_t span_session_id,
                                          const boolean_t            admin_state);

/**
 *  This function gets the SPAN session Admin State.
 *  Supported devices: Spectrum, Spectrum2.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] span_session_id - SPAN session ID
 * @param[out] admin_state - SPAN session Admin state (Enable/Disable).
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 *
 */
sx_status_t sx_api_span_session_state_get(const sx_api_handle_t      handle,
                                          const sx_span_session_id_t span_session_id,
                                          boolean_t                 *admin_state_p);

/**
 *  This function gets the analyzer port assigned to the SPAN
 *  session.
 *  Supported devices: Spectrum, Spectrum2.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] span_session_id - SPAN session ID
 * @param[out] analyzer_port - analyzer port
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 *
 */
sx_status_t sx_api_span_session_analyzer_get(const sx_api_handle_t      handle,
                                             const sx_span_session_id_t span_session_id,
                                             sx_port_log_id_t          *analyzer_port_p);

/**
 *  This function gets the mirror ports assigned to the SPAN
 *  session.
 *  Supported devices: Spectrum, Spectrum2.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] span_session_id - SPAN session ID
 * @param[out] mirror_ports_list_p - array of mirror ports
 * @param[in,out] mirror_ports_cnt_p - num of mirror ports
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 *
 */
sx_status_t sx_api_span_session_mirror_get(const sx_api_handle_t      handle,
                                           const sx_span_session_id_t span_session_id,
                                           sx_span_mirror_t          *mirror_ports_list_p,
                                           uint32_t                  *mirror_ports_cnt_p);

/**
 *  This function sets the SPAN mirror ports.
 *  Supported devices: Spectrum, Spectrum2.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - ADD / DELETE
 * @param[in] mirror_port - mirror port
 * @param[in] mirror_direction - mirror direction: ingress/
 *       egress
 * @param[in] span_session_id - SPAN session id
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ACCESS_CMD_UNSUPPORTED if unsupported command is requested
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 * @return SX_STATUS_NO_RESOURCES if pool cannot provide object
 * @return SX_STATUS_ERROR if unexpected behavior occurs*
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 */
sx_status_t sx_api_span_mirror_set(const sx_api_handle_t       handle,
                                   const sx_access_cmd_t       cmd,
                                   const sx_port_log_id_t      mirror_port,
                                   const sx_mirror_direction_t mirror_direction,
                                   const sx_span_session_id_t  span_session_id);

/**
 *  This function get the SPAN session id and direction by
 *  mirror port .
 *  Supported devices: Spectrum, Spectrum2.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] mirror_port - mirror port
 * @param[in] mirror_direction - mirror direction ingress/
 *       egress
 * @param[out] span_session_id_p - SPAN session ID
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 */
sx_status_t sx_api_span_mirror_get(const sx_api_handle_t       handle,
                                   const sx_port_log_id_t      mirror_port,
                                   const sx_mirror_direction_t mirror_direction,
                                   sx_span_session_id_t       *span_session_id_p);

/**
 *  This function sets the SPAN mirror port Admin state.
 *  Supported devices: Spectrum, Spectrum2.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] mirror_port - mirror port
 * @param[in] mirror_direction - mirror direction: ingress/
 *       egress
 * @param[in] span_session_id - SPAN session id
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ACCESS_CMD_UNSUPPORTED if unsupported command is requested
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 * @return SX_STATUS_NO_RESOURCES if pool cannot provide object
 * @return SX_STATUS_ERROR if unexpected behavior occurs*
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 */
sx_status_t sx_api_span_mirror_state_set(const sx_api_handle_t       handle,
                                         const sx_port_log_id_t      mirror_port,
                                         const sx_mirror_direction_t mirror_direction,
                                         const boolean_t             admin_state);

/**
 *  This function get the SPAN session id and direction by
 *  mirror port .
 *  Supported devices: Spectrum, Spectrum2.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] mirror_port - mirror port
 * @param[in] mirror_direction - mirror direction ingress/
 *       egress
 * @param[out] span_session_id_p - SPAN session ID
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 */
sx_status_t sx_api_span_mirror_state_get(const sx_api_handle_t       handle,
                                         const sx_port_log_id_t      mirror_port,
                                         const sx_mirror_direction_t mirror_direction,
                                         boolean_t                  *admin_state_p);

/**
 *  This function sets the SPAN analyzer ports.
 *  Supported devices: Spectrum, Spectrum2.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - ADD / DELETE
 * @param[in] log_port - analyzer port which added to SPAN
 * @param[in] port_params - analyzer port parameters
 * @param[in] span_session_id - SPAN session ID
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 */
sx_status_t sx_api_span_analyzer_set(const sx_api_handle_t                 handle,
                                     const sx_access_cmd_t                 cmd,
                                     const sx_port_log_id_t                log_port,
                                     const sx_span_analyzer_port_params_t *port_params_p,
                                     const sx_span_session_id_t            span_session_id);

/**
 *  This function gets the SPAN by analyzer ports.
 *  Supported devices: Spectrum, Spectrum2.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] log_port - analyzer port which added to SPAN
 * @param[out] port_params_p - analyzer port parameters
 * @param[out] span_session_id_list_p - SPAN session ID array
 * @param[in,out] span_session_cnt_p - SPAN sessions num
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 */
sx_status_t sx_api_span_analyzer_get(const sx_api_handle_t           handle,
                                     const sx_port_log_id_t          log_port,
                                     sx_span_analyzer_port_params_t *port_params_p,
                                     sx_span_session_id_t           *span_session_id_list_p,
                                     uint32_t                       *span_sessions_cnt_p);

/**
 *  This function initializes certain aspects of SPAN module behaviour.
 *  Currently the only data item controlled by this API is the version of
 *  headers attached to mirrored packets.  The following rules apply:
 *  - Calling it is optional in Spectrum. If not called, default
 *    module configuration is used.
 *  - Mirroring resources may be allocated without calling this function, using
 *    default settings.
 *  - The function may be called repeatedly, to change configuration, but only
 *    if a call to sx_api_span_deinit_set intervenes.
 *  - The function fails if any mirroring sessions are already allocated when it
 *    is called.
 *
 * Supported devices: Spectrum, Spectrum2.
 *
 * @param[in] handle            SX-API handle.
 * @param[in] init_params_p     module configuration parameters
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 * @return SX_STATUS_ALREADY_INITIALIZED if any mirroring resources are already
 *         allocated
 * @return SX_STATUS_ALREADY_INITIALIZED if called twice without intervening
 *         call to sx_api_span_deinit_set
 */
sx_status_t sx_api_span_init_set(sx_api_handle_t        handle,
                                 sx_span_init_params_t *init_params_p);

/**
 *  This function undoes sx_api_span_init_set by returning configured parameters
 *  to default.  The following rules apply:
 *  - Calls to this function require a prior call to sx_api_span_init_set.
 *  - The function fails if any mirroring sessions are already allocated when it
 *    is called.
 *
 * Supported devices: Spectrum, Spectrum2.
 *
 * @param[in] handle - SX-API handle.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 * @return SX_STATUS_RESOURCE_IN_USE if any mirroring resources are already
 *         allocated
 * @return SX_STATUS_DB_NOT_INITIALIZED if called without prior call to
 *         sx_api_span_init_set
 */
sx_status_t sx_api_span_deinit_set(sx_api_handle_t handle);

/**
 *  This function retrieves or clears dropped packet counters for a mirroring session.
 *
 * Supported devices: Spectrum, Spectrum2.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - READ / READ_CLEAR
 * @param[in] span_session_id - SPAN session ID
 * @param[out] counter_set_p - set of counter values
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_UNSUPPORTED if not supported on this device
 * @return SX_STATUS_CMD_UNSUPPORTED if cmd parameter is invalid
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 */
sx_status_t sx_api_span_session_counter_get(const sx_api_handle_t      handle,
                                            const sx_access_cmd_t      cmd,
                                            const sx_span_session_id_t span_session_id,
                                            sx_span_counter_set_t     *counter_set_p);


/**
 *  This function enables or disables mirroring via the MIRROR trap id, for
 *  modules whose own API does not refer to an explicit mirroring session.  When
 *  enabling, it associates the trap group to which the MIRROR trap id is mapped
 *  with the given mirroring session.  Disabling breaks that association.  It is
 *  permitted to call the function repeatedly to replace one mirroring session
 *  with another.
 *
 * Supported devices: Spectrum, Spectrum2.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - ADD / DELETE
 * @param[in] span_session_id - SPAN session ID
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_CMD_UNSUPPORTED if not supported on this device
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 */
sx_status_t sx_api_span_mirror_tables_set(const sx_api_handle_t      handle,
                                          const sx_access_cmd_t      cmd,
                                          const sx_span_session_id_t span_session_id);

/**
 *  This function retrieves the mirroring session configured for mirroring via
 *  the MIRROR trap id, for modules whose own API does not refer to an explicit
 *  mirroring session.
 *
 * Supported devices: Spectrum, Spectrum2.
 *
 * @param[in] handle - SX-API handle.
 * @param[out] span_session_id_p - SPAN session ID
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_CMD_UNSUPPORTED if not supported on this device
 * @return SX_STATUS_ENTRY_NOT_FOUND if no mirroring session exists
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 */
sx_status_t sx_api_span_mirror_tables_get(const sx_api_handle_t handle,
                                          sx_span_session_id_t *span_session_id_p);

/**
 *  This function configures mirroring to a SPAN session of dropped packets.
 *  SET: Sets the SPAN session to the new settings, overriding current configuration.
 *  ADD: Add more Drop Reasons to the existing configuration.
 *  DELETE: Remove Drop Reasons from existing configuration.
 *  DELETE_ALL: Remove all Drop Reasons from existing configuration.
 * Supported devices: Spectrum, Spectrum2.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - SET / ADD / DELETE / DELETE_ALL
 * @param[in] span_session_id - SPAN session ID
 * @param[in] drop_mirroring_attr_p - Drop Mirroring configuration, only valid for SET.
 * @param[in] drop_reason_list_p - List of Drop Reasons, ignored for DELETE_ALL.
 * @param[in] drop_reason_cnt - Count of Drop Reasons, ignored for DELETE_ALL.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_CMD_UNSUPPORTED if not supported on this device
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 */
sx_status_t sx_api_span_drop_mirror_set(const sx_api_handle_t                handle,
                                        const sx_access_cmd_t                cmd,
                                        const sx_span_session_id_t           span_session_id,
                                        const sx_span_drop_mirroring_attr_t *drop_mirroring_attr_p,
                                        const sx_span_drop_reason_t         *drop_reason_list_p,
                                        const uint32_t                       drop_reason_cnt);

/**
 *  This function retrieves the mirroring session drop reasons configured for router-drop mirroring via
 *  the trap ids for router drops.
 *  If drop_reason_list is NULL, the number of drop reasons will be returned in drop_reason_cnt.
 *
 * Supported devices: Spectrum, Spectrum2.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] span_session_id - SPAN session ID
 * @param[out] drop_mirroring_attr_p - Drop Mirroring configuration
 * @param[out] drop_reason_list_p - List of Drop Reasons
 * @param[out] drop_reason_cnt_p - Count of Drop Reasons
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_CMD_UNSUPPORTED if not supported on this device
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 */
sx_status_t sx_api_span_drop_mirror_get(const sx_api_handle_t          handle,
                                        const sx_span_session_id_t     span_session_id,
                                        sx_span_drop_mirroring_attr_t *drop_mirroring_attr_p,
                                        sx_span_drop_reason_t         *drop_reason_list_p,
                                        uint32_t                      *drop_reason_cnt_p);

/**
 *  This function binds the mirror binding point to span session
 *  with sampling rate.
 *
 *  Supported devices: Spectrum, Spectrum.
 *
 * @param[in] handle   - SX-API handle
 * @param[in] cmd      - bind/unbind
 * @param[in] key      - bind key
 * @param[in] attr     - bind attribute
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_PARAM_NULL if any input parameter is NULL
 * @return SX_STATUS_ACCESS_CMD_UNSUPPORTED if unsupported command is requested
 * @return SX_STATUS_ENTRY_ALREADY_BOUND if requested element is not found in DB
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 */

sx_status_t sx_api_span_mirror_bind_set(const sx_api_handle_t             handle,
                                        const sx_access_cmd_t             cmd,
                                        const sx_span_mirror_bind_key_t  *key_p,
                                        const sx_span_mirror_bind_attr_t *attr_p);

/**
 *  This function gets the mirror binding attribute
 *
 *  Supported devices: Spectrum, Spectrum2.
 *
 * @param[in] handle    - SX-API handle
 * @param[in] key_p     - bind key
 * @param[out] attr_p   - bind attribute
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_PARAM_NULL if any input parameter is NULL
 * @return SX_STATUS_ACCESS_CMD_UNSUPPORTED if unsupported command is requested
 * @return SX_STATUS_ENTRY_NOT_BOUND if requested element is not found in DB
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 */
sx_status_t sx_api_span_mirror_bind_get(const sx_api_handle_t            handle,
                                        const sx_span_mirror_bind_key_t *key_p,
                                        sx_span_mirror_bind_attr_t      *attr_p);

/**
 *  This function gets the mirror type bound to the SPAN
 *  session.
 *  Supported devices: Spectrum2.
 *
 * @param[in] handle                    - SX-API handle.
 * @param[in] span_session_id           - SPAN session ID
 * @param[out] mirror_bind_key_list_p   - array of mirror bind keys
 * @param[in,out] mirror_bind_key_cnt_p - num of mirror bind keys
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_PARAM_NULL if any input parameter is NULL
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 *
 */
sx_status_t sx_api_span_session_mirror_bound_get(const sx_api_handle_t      handle,
                                                 const sx_span_session_id_t span_session_id,
                                                 sx_span_mirror_bind_key_t *mirror_bind_key_list_p,
                                                 uint32_t                  *mirror_bind_key_cnt_p);

/**
 *  This function enables mirroring on mirror object which is
 *  port TC or port PG or port on different mirror enable type
 *
 *  Supported devices: Spectrum2.
 *
 * @param[in] handle   - SX-API handle
 * @param[in] cmd      - set/delete
 * @param[in] object_p - mirror enable object
 * @param[in] attr_p   - mirror enable attribute
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 */
sx_status_t sx_api_span_mirror_enable_set(const sx_api_handle_t                 handle,
                                          const sx_access_cmd_t                 cmd,
                                          const sx_span_mirror_enable_object_t *object_p,
                                          const sx_span_mirror_enable_attr_t   *attr_p);

/**
 *  This function get the enable attribute for mirror object
 *
 *  Supported devices: Spectrum2.
 *
 * @param[in]  handle     - SX-API handle
 * @param[in]  object_p   - mirror enable object
 * @param[out] attr_p     - mirror enable attribute
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_ENTRY_NOT_FOUND if input object is not found
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_PARAM_NULL if any input parameter is NULL
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 */
sx_status_t sx_api_span_mirror_enable_get(const sx_api_handle_t                 handle,
                                          const sx_span_mirror_enable_object_t *object_p,
                                          sx_span_mirror_enable_attr_t         *attr_p);

/**
 *  This function iteratively returns the objects per object type.
 *  Supported devices: Spectrum2.
 *
 * @param[in] handle               - SX-API handle.
 * @param[in] cmd                  - supported commands:GET/GET_FIRST/GETNEXT
 * @param[in] object_key_p         - A reference mirror enable object key
 * @param[in] filter_p             - Return only enabled object that match this filter param if valid
 * @param[out] object_list_p       - return list of objects
 * @param[in,out] object_cnt_p     - [in]  number of objects to get
 *                                   [out] number of objects retrieved
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_PARAM_NULL if any input parameter is NULL
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 * @return SX_STATUS_CMD_UNSUPPORTED - if invalid cmd is passed
 * @return SX_STATUS_DB_NOT_INITIALIZED - if internal DB is not initialized
 */
sx_status_t sx_api_span_mirror_enable_iter_get(const sx_api_handle_t                handle,
                                               const sx_access_cmd_t                cmd,
                                               sx_span_mirror_enable_object_t      *object_key_p,
                                               sx_span_mirror_enable_iter_filter_t *filter_p,
                                               sx_span_mirror_enable_object_t      *object_list_p,
                                               uint32_t                            *object_cnt_p);

/**
 * Set current UTC time in the device that is used to update timestamp in SPAN headers.
 * Note - This API should not be used when PTP protocol is active and running.
 * Note - UTC is also used for updating time stamp for ingress/egress packets to/from CPU.
 *
 * Supported devices: Spectrum, Spectrum2.
 *
 * Parameters:
 *     [in]    handle      - SX-API handle
 *     [in]    cmd         - SX_ACCESS_CMD_SET
 *     [in]    span_ts     - current UTC time configuration.
 *
 * Returns:
 *     SX_STATUS_SUCCESS if operation completes successfully
 *     SX_STATUS_PARAM_ERROR if input parameter is invalid
 *     SX_STATUS_ERROR general error
 */
sx_status_t sx_api_span_header_time_stamp_set(const sx_api_handle_t   handle,
                                              const sx_access_cmd_t   cmd,
                                              sx_span_hdr_ts_config_t span_ts);

#endif /* __SX_API_SPAN_H__ */
