/*
 *                  - Mellanox Proprietary -
 *
 *  Copyright (C) January 2010, Mellanox Technologies Ltd.  ALL RIGHTS RESERVED.
 *
 *  Except as specifically permitted herein, no portion of the information,
 *  including but not limited to object code and source code, may be reproduced,
 *  modified, distributed, republished or otherwise exploited in any form or by
 *  any means for any purpose without the prior written permission of Mellanox
 *  Technologies Ltd. Use of software subject to the terms and conditions
 *  detailed in the file "LICENSE.txt".
 */

#ifndef __SX_API_SPAN_H__
#define __SX_API_SPAN_H__

#include <sx/sdk/sx_api.h>

/************************************************
 *  API functions
 ***********************************************/

/**
 * This function sets the log verbosity level of SPAN MODULE
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
 *  should be called we cmd = DESTROY.
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
 *  This function set SPAN session Admin State.
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

#endif /* __SX_API_SPAN_H__ */
