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

#ifndef __SX_API_MSTP_H__
#define __SX_API_MSTP_H__

#include <sx/sdk/sx_api.h>


/************************************************
 *  API functions
 ***********************************************/

/**
 * This function sets the log verbosity level of MSTP MODULE
 * @param[in]     handle                   - SX-API handle
 * @param[in]     cmd                      - SET / GET
 * @param[in]     verbosity_target         - set get verbosity of : API / MODULE / BOTH
 * @param[in,out] module_verbosity_level_p - MSTP module verbosity level
 * @param[in,out] api_verbosity_level_p    - MSTP API verbosity level
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS - Operation completes successfully
 * @return SX_STATUS_CMD_UNSUPPORTED - Unsupported access command
 * @return SX_STATUS_INVALID_HANDLE - NULL handle received
 * @return SX_STATUS_COMM_ERROR - Client communication channel open failed
 * @return SX_STATUS_PARAM_ERROR - Unsupported verbosity_target
 */
sx_status_t
sx_api_mstp_log_verbosity_level_set(
                                   sx_api_handle_t            handle ,
                                   sx_access_cmd_t            cmd ,
                                   sx_log_verbosity_target_t  verbosity_target,
                                   sx_verbosity_level_t      *module_verbosity_level_p,
                                   sx_verbosity_level_t      *api_verbosity_level_p
                                   );

/**
 *  	This API Sets the Switch STP Activation mode (RSTP/MSTP) in the SDK.
 *  As a result, the mapping between Instance(s) to VLAN(s) is deleted.
 ************************************************************************************************************
 *
 * @param[in] handle - SX-API handle
 * @param[in] swid_id - Switch ID.
 * @param[in] mode - STP Activation mode.
 * 			Can take any of the following:
 * 			SX_MSTP_MODE_MSTP,	(default)
 * 			SX_MSTP_MODE_RSTP
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS - Operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE - Parameters out of range
 * @return SX_STATUS_MESSAGE_SIZE_ZERO - Message size is Zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT - Message size out of range
 * @return SX_STATUS_INVALID_HANDLE - Invalid handle
 * @return SX_STATUS_COMM_ERROR - Message send fail
 */
sx_status_t
sx_api_mstp_mode_set(
                    const sx_api_handle_t handle,
                    const sx_swid_id_t swid_id,
                    const sx_mstp_mode_t mode
                    );

/**
 *  	This API Retrieves the Switch STP Activation state (RSTP/MSTP) from the SDK.
 ************************************************************************************************************
 *
 * @param[in] handle - SX-API handle
 * @param[in] swid_id - Switch ID.
 * @param[out] mode_p - MSTP Activation state.
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS - Operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE - Parameters out of range
 * @return SX_STATUS_MESSAGE_SIZE_ZERO - Message size is Zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT - Message size out of range
 * @return SX_STATUS_INVALID_HANDLE - Invalid handle
 * @return SX_STATUS_COMM_ERROR - Message send fail
 * @return SX_STATUS_PARAM_NULL - state_p pointer in NULL
 */
sx_status_t
sx_api_mstp_mode_get(
                    const sx_api_handle_t handle,
                    const sx_swid_id_t swid_id,
                    sx_mstp_mode_t *mode_p
                    );

/**
 *  	This API Adds/Deletes an MSTP Instance to/from the Switch in the SDK.
 ************************************************************************************************************
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - ADD/DELETE
 * @param[in] swid_id - Switch ID.
 * @param[in] inst_id - MSTP Instance ID to add/delete. Ranges <1-64>.
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS - Operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE - Parameters out of range
 * @return SX_STATUS_MESSAGE_SIZE_ZERO - Message size is Zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT - Message size out of range
 * @return SX_STATUS_INVALID_HANDLE - Invalid handle
 * @return SX_STATUS_COMM_ERROR - Message send fail
 */
sx_status_t
sx_api_mstp_inst_set(
                    const sx_api_handle_t handle,
                    const sx_access_cmd_t cmd,
                    const sx_swid_id_t swid_id,
                    const sx_mstp_inst_id_t inst_id
                    );

/**
 *  	This API Adds/Deletes a mapping between a list of VLANs to the MSTP Instance in the SDK.
 ************************************************************************************************************
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - ADD/DELTE
 * @param[in] swid_id - Switch ID.
 * @param[in] inst_id - MSTP Instance ID. Ranges <1-64>.
 * @param[in] vlan_list - List of VLANs to Map/Unmap.
 * @param[in] vlan_num - Number of VLANs to Map/Unmap. Ranges <1-4094>.
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS - Operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE - Parameters out of range
 * @return SX_STATUS_MESSAGE_SIZE_ZERO - Message size is Zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT - Message size out of range
 * @return SX_STATUS_INVALID_HANDLE - Invalid handle
 * @return SX_STATUS_COMM_ERROR - Message send fail
 * @return SX_STATUS_PARAM_NULL - Parameter vlan_list is NULL
 * @return SX_STATUS_CMD_UNSUPPORTED - Unsupported command
 */
sx_status_t
sx_api_mstp_inst_vlan_list_set(
                              const sx_api_handle_t handle,
                              const sx_access_cmd_t cmd,
                              const sx_swid_id_t swid_id,
                              const sx_mstp_inst_id_t inst_id,
                              const sx_vlan_id_t *vlan_list_p,
                              const length_t vlan_num
                              );

/**
 *  	This API Retrieves a list of VLANs in the MSTP Instance from the SDK.
 *  If the output list (array) is NULL, only the number of VLANs is retrieved.
 ************************************************************************************************************
 *
 * @param[in] handle - SX-API handle
 * @param[in] swid_id - Switch ID.
 * @param[in] inst_id - MSTP Instance ID. Ranges <1-64>.
 * @param[out] vlan_list - VLANs array.
 * @param[in,out] vlan_num_p - In: Size of VLANs array. Ranges <1-4094>.
 * 			  Out: Number of VLANs retrieved successfully.
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS - Operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE - Parameters out of range
 * @return SX_STATUS_MESSAGE_SIZE_ZERO - Message size is Zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT - Message size out of range
 * @return SX_STATUS_INVALID_HANDLE - Invalid handle
 * @return SX_STATUS_COMM_ERROR - Message send fail
 * @return SX_STATUS_PARAM_NULL - Parameter vlan_list is NULL
 * @return SX_STATUS_CMD_UNSUPPORTED - Unsupported command
 */
sx_status_t
sx_api_mstp_inst_vlan_list_get(
                              const sx_api_handle_t handle,
                              const sx_swid_id_t swid_id,
                              const sx_mstp_inst_id_t inst_id,
                              sx_vlan_id_t *vlan_list_p,
                              length_t *vlan_num_p
                              );

/**
 *  	This API Sets the MSTP Port State for a given Instance in the SDK.
 ************************************************************************************************************
 *
 * @param[in] handle - SX-API handle
 * @param[in] swid_id - Switch ID.
 * @param[in] inst_id - MSTP Instance ID. Ranges <1-64>.
 * @param[in] port_id - Port ID (whose STP state to set).
 * @param[in] port_state - MSTP Port State.
 * 			   Can take any of the following:
 * 			   SX_MSTP_INST_PORT_STATE_DISCARDING,
 * 			   SX_MSTP_INST_PORT_STATE_LEARNING,
 *			   SX_MSTP_INST_PORT_STATE_FORWARDING,
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS - Operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE - Parameters out of range
 * @return SX_STATUS_MESSAGE_SIZE_ZERO - Message size is Zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT - Message size out of range
 * @return SX_STATUS_INVALID_HANDLE - Invalid handle
 * @return SX_STATUS_COMM_ERROR - Message send fail
 */
sx_status_t
sx_api_mstp_inst_port_state_set(
                               const sx_api_handle_t handle,
                               const sx_swid_id_t swid_id,
                               const sx_mstp_inst_id_t inst_id,
                               const sx_port_id_t port_id,
                               const sx_mstp_inst_port_state_t port_state
                               );

/**
 *  	This API Retrieves the MSTP Port State for a given Instance from the SDK.
 ************************************************************************************************************
 *
 * @param[in] handle - SX-API handle
 * @param[in] swid_id - Switch ID.
 * @param[in] inst_id - MSTP Instance ID. Ranges <1-64>.
 * @param[in] port_id - Port ID (whose STP state to retrieve).
 * @param[out] port_state_p - MSTP Port State.
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS - Operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE - Parameters out of range
 * @return SX_STATUS_MESSAGE_SIZE_ZERO - Message size is Zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT - Message size out of range
 * @return SX_STATUS_INVALID_HANDLE - Invalid handle
 * @return SX_STATUS_COMM_ERROR - Message send fail
 * @return SX_STATUS_PARAM_NULL - Parameter port_state_p is NULL
 */
sx_status_t
sx_api_mstp_inst_port_state_get(
                               const sx_api_handle_t handle,
                               const sx_swid_id_t swid_id,
                               const sx_mstp_inst_id_t inst_id,
                               const sx_port_id_t port_id,
                               sx_mstp_inst_port_state_t* port_state_p
                               );

/**
 *  	This API Sets the RSTP Port State in the SDK.
 ************************************************************************************************************
 *
 * @param[in] handle - SX-API handle
 * @param[in] swid_id - Switch ID.
 * @param[in] port_id - Port ID.
 * @param[in] port_state - MSTP Port state.
 * 				Can take any of the following:
 * 				SX_MSTP_INST_PORT_STATE_DISCARDING,
 * 				SX_MSTP_INST_PORT_STATE_LEARNING,
 *				SX_MSTP_INST_PORT_STATE_FORWARDING,
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS - Operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE - Parameters out of range
 * @return SX_STATUS_MESSAGE_SIZE_ZERO - Message size is Zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT - Message size out of range
 * @return SX_STATUS_INVALID_HANDLE - Invalid handle
 * @return SX_STATUS_COMM_ERROR - Message send fail
 */
sx_status_t
sx_api_rstp_port_state_set(
                          const sx_api_handle_t handle,
                          const sx_swid_id_t swid_id,
                          const sx_port_id_t port_id,
                          const sx_mstp_inst_port_state_t port_state
                          );

/**
 *  	This API Retrieves the RSTP Port State from the SDK.
 ************************************************************************************************************
 *
 * @param[in] handle - SX-API handle
 * @param[in] swid_id - Switch ID.
 * @param[in] port_id - Port ID.
 * @param[out] port_state_p - MSTP Port State.
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS - Operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE - Parameters out of range
 * @return SX_STATUS_MESSAGE_SIZE_ZERO - Message size is Zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT - Message size out of range
 * @return SX_STATUS_INVALID_HANDLE - Invalid handle
 * @return SX_STATUS_COMM_ERROR - Message send fail
 * @return SX_STATUS_PARAM_NULL - Parameter port_state_p is NULL
 */
sx_status_t
sx_api_rstp_port_state_get(
                          const sx_api_handle_t handle,
                          const sx_swid_id_t swid_id,
                          const sx_port_id_t port_id,
                          sx_mstp_inst_port_state_t *port_state_p
                          );

#endif /* __SX_API_MSTP_H__ */
