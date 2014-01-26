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

#ifndef __SX_API_LAG_H__
#define __SX_API_LAG_H__

#include <sx/sdk/sx_api.h>


/************************************************
 *  API functions
 ***********************************************/

/**
 * This function sets the log verbosity level of LAG MODULE
 * @param[in]     handle                   - SX-API handle
 * @param[in]     cmd                      - SET / GET
 * @param[in]     verbosity_target         - set get verbosity of : API / MODULE / BOTH
 * @param[in,out] module_verbosity_level_p - FDB module verbosity level
 * @param[in,out] api_verbosity_level_p    - fdb API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t
sx_api_lag_log_verbosity_level_set(
                                  const sx_api_handle_t            handle ,
                                  const sx_access_cmd_t            cmd ,
                                  const sx_log_verbosity_target_t  verbosity_target,
                                  sx_verbosity_level_t *     module_verbosity_level_p,
                                  sx_verbosity_level_t *     api_verbosity_level_p);

/**
 *  This function CREATEs/DESTROYs a new/existing LAG ports group in the SDK.
 *  Plus, it ADDs/DELETEs ports to/from an existing LAG ports group in the SDK.
 *
 *  Note:
 *  - All ports must be DELETEd from LAG ports group before the group is DESTROYed.
 *  - Cannot create a lag group and add ports to it in the same api call.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - CREATE/DESTROY/ADD/DELETE.
 * @param[in] swid - SWitch (virtual partition) ID.
 * @param[in,out] lag_port_p -	In: Already created LAG ports 
 *              group ID. Out: Newly created LAG ports group ID.
 * @param[in] log_port_num - Number of Logical Ports to ADD/DELETE to/from a LAG ports group.
 * @param[in] log_port_list_p - List of Logical Ports to 
 *       ADD/DELETE to/from a LAG ports group.
 *
 * @return SX_STATUS_SUCCESS - Operation completes successfully.
 * @return SX_STATUS_PARAM_NULL - Parameter is unexpectedly NULL.
 * @return SX_STATUS_PARAM_ERROR - Parameter is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND - Requested element is not found in DB.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE - Parameter exceeds its range.
 */
sx_status_t sx_api_lag_port_group_set(
                                     const sx_api_handle_t   handle,
                                     const sx_access_cmd_t   cmd,
                                     const sx_swid_t         swid,
                                     sx_port_lag_id_t* lag_port_p,
                                     const sx_port_log_id_t* log_port_list_p,
                                     const length_t          log_port_num);

/**
 *  This function retrieves an existing LAG's ports group from the SDK.
 *
 *  Note:
 *  If the output ports list is NULL, only the number of ports in the LAG's retrieved.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] swid - SWitch (virtual partition) ID.
 * @param[in] lag_port - LAG ports group ID.
 * @param[in,out] log_port_list_p - List of Logical Ports.
 * @param[in,out] log_port_num_p - In: Number of Logical Ports in list, Out: Number of Logical Ports in LAG.
 *
 * @return SX_STATUS_SUCCESS - Operation completes successfully.
 * @return SX_STATUS_PARAM_NULL - Parameter is unexpectedly NULL.
 * @return SX_STATUS_PARAM_ERROR - Parameter is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND - Requested element is not found in DB.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE - Parameter exceeds its range.
 */
sx_status_t sx_api_lag_port_group_get(
                                     const sx_api_handle_t       handle,
                                     const sx_swid_t             swid,
                                     const sx_port_lag_id_t      lag_port,
                                     sx_port_log_id_t *    log_port_list_p,
                                     length_t *            log_port_num_p);


/**
 *  This function enables/disables collection on a specific LAG port.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] lag_log_port - A logical port number representing
 *       the LAG ports group
 * @param[in] log_port - logical port number
 * @param[in] collector_mode collector mode
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is
 *         invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested
 *  element is not found in DB
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO if SxD driver
 *  function returns fail
 * @return SX_STATUS_CMD_UNSUPPORTED if unsupported command is
 *  requested
 */

sx_status_t sx_api_lag_port_collector_set(
                                         const sx_api_handle_t       handle,
                                         const sx_port_log_id_t      lag_log_port,
                                         const sx_port_log_id_t      log_port,
                                         const sx_collector_mode_t   collector_mode);

/**
 *  This function enables/disables distribution on a specific LAG port.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] lag_log_port - A logical port number representing
 *       the LAG ports group
 * @param[in] log_port - logical port number
 * @param[in] distributor_mode distributor mode
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return 	SX_STATUS_PARAM_ERROR if any input parameter is
 *  invalid
 *  @return SX_STATUS_ENTRY_NOT_FOUND if requested element is
 *  not found in DB
 *  @return SX_STATUS_ENTRY_ALREADY_EXISTS if requested element
 *  is found in DB
 *  @return SX_STATUS_SXD_RETURNED_NON_ZERO if SxD driver
 *  function returns fail
 *  @return SX_STATUS_CMD_UNSUPPORTED if unsupported command is
 *  requested
 */
sx_status_t sx_api_lag_port_distributor_set(
                                           const sx_api_handle_t       handle,
                                           const sx_port_log_id_t      lag_log_port,
                                           const sx_port_log_id_t      log_port,
                                           const sx_distributor_mode_t distributor_mode);

/**
 *  This function configures the flow indicators that impact the
 *  LAG hash distribution function.
 *  @param[in] handle - SX-API handle.
 *  @param[in] sx_lag_hash_param - Hash parameters
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 * @return SX_STATUS_NO_MEMORY if problems with memory allocation occurs
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO if SxD driver function returns fail
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameter exceeds its range
 */
sx_status_t sx_api_lag_hash_flow_params_set(
                                           const sx_api_handle_t       handle,
                                           const sx_lag_hash_param_t * lag_hash_param_p);



/**
 *  This function retrieves the flow indicators that impact the
 *  LAG hash distribution function.
 *  @param[in] handle - SX-API handle.
 *  @param[out] sx_lag_hash_param - Hash parameters to be
 *        retrieved
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO if SxD driver function returns fail
 */
sx_status_t sx_api_lag_hash_flow_params_get(
                                           const sx_api_handle_t       handle,
                                           sx_lag_hash_param_t * lag_hash_param_p);

#endif /* __SX_API_LAG_H__ */
