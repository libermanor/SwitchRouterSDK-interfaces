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


#ifndef __SX_API_HOST_IFC_H__
#define __SX_API_HOST_IFC_H__

#include <sx/sdk/sx_api.h>

/**
 * This function sets the log verbosity level of HOST INTERFACE MODULE
 * @param[in] handle                   - SX-API handle
 * @param[in] verbosity_target         - set verbosity of : API / MODULE / BOTH
 * @param[in] module_verbosity_level   - HOST INTERFACE module verbosity level
 * @param[in] api_verbosity_level      - HOST INTERFACE API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 *         SX_STATUS_PARAM_ERROR if any input parameters is invalid
 *         SX_STATUS_ERROR general error
 */
sx_status_t sx_api_host_ifc_log_verbosity_level_set(const sx_api_handle_t           handle,
                                                    const sx_log_verbosity_target_t verbosity_target,
                                                    const sx_verbosity_level_t      module_verbosity_level,
                                                    const sx_verbosity_level_t      api_verbosity_level);

/**
 * This function gets the log verbosity level of HOST INTERFACE MODULE
 *
 * @param[in]  handle                   - SX-API handle
 * @param[in]  verbosity_target         - get verbosity of : API / MODULE / BOTH
 * @param[out] module_verbosity_level_p - HOST INTERFACE module verbosity level
 * @param[out] api_verbosity_level_p    - HOST INTERFACE API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 *         SX_STATUS_PARAM_ERROR if any input parameters is invalid
 *         SX_STATUS_ERROR general error
 */
sx_status_t sx_api_host_ifc_log_verbosity_level_get(const sx_api_handle_t           handle,
                                                    const sx_log_verbosity_target_t verbosity_target,
                                                    sx_verbosity_level_t           *module_verbosity_level_p,
                                                    sx_verbosity_level_t           *api_verbosity_level_p);

/**
 * This function retrieves the file descriptor of the current open channel
 * used for receiving a packet
 *
 * @param[in]     handle        - SX-API handle.
 * @param[out]    fd_p            - file descriptor
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if any input parameters is null
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_MEMORY_ERROR error handling memory
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO error closing channel to the sx driver
 */
sx_status_t sx_api_host_ifc_open(const sx_api_handle_t handle,
                                 sx_fd_t              *fd_p);

/**
 * This function closes the file descriptor of the current open channel
 * used for receiving a packet
 *
 * @param[in]     handle        - SX-API handle.
 * @param[in]    fd_p           - file descriptor
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if any input parameters is null
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO error closing channel to the sx driver
 */
sx_status_t sx_api_host_ifc_close(const sx_api_handle_t handle,
                                  sx_fd_t              *fd_p);

/**
 * Create / Edit a trap group
 *   Allows creating a new trap group with certain attributes,
 *   and editing an existing trap group with new attributes.
 *
 * @param[in]     handle             - SX-API handle.
 * @param[in]     swid           - Switch ID.
 * @param[in]     trap_group         - The trap group, must be between 0-63.
 * @param[in]     trap_group_attributes_p  - Trap group
 *       attributes.
 *
 * @return  SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if any input parameters is null
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_MEMORY_ERROR error handling memory
 * @return SX_STATUS_NO_RESOURCES device was not opened
 */
sx_status_t sx_api_host_ifc_trap_group_set(const sx_api_handle_t             handle,
                                           const sx_swid_id_t                swid,
                                           const sx_trap_group_t             trap_group,
                                           const sx_trap_group_attributes_t* trap_group_attributes_p);

/**
 * Get Trap group attributes:
 *
 * @param[in]     handle         - SX-API handle.
 * @param[in]     swid           - Switch ID.
 * @param[in]     trap_group         - The trap group, must be between 0-63.
 * @param[out]    trap_group_attributes_p  - Trap group
 *       attributes.
 *
 * @return  SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if any input parameters is null
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_MEMORY_ERROR error handling memory
 * @return SX_STATUS_NO_RESOURCES device was not opened
 */
sx_status_t sx_api_host_ifc_trap_group_get(const sx_api_handle_t        handle,
                                           const sx_swid_id_t           swid,
                                           const sx_trap_group_t        trap_group,
                                           sx_trap_group_attributes_t * trap_group_attributes_p);

/**
 * Configure traps / event properties for each device in the system:
 *       Map Trap ID / Event ID to 1 of the 3 Priority groups: HIGH, MEDIUM, LOW.
 *       Configure trap action (for traps only)
 *
 * @param[in]     handle        - SX-API handle.
 * @param[in]     swid          - Switch ID.
 * @param[in]     trap_id       - Trap ID.
 * @param[in]     trap_group    - Trap group handle.
 * @param[in]     trap_action   - Trap action.
 *
 *@return    SX_STATUS_SUCCESS if operation completes successfully
 *    @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 *    @return SX_STATUS_ERROR general error
 *    @return SX_STATUS_MEMORY_ERROR error handling memory
 *    @return SX_STATUS_NO_RESOURCES device was not opened
 *
 * Note:  when configuring trap_id of SX_TRAP_ID_ETH_L2_PACKET_SAMPLING /SX_TRAP_ID_GENERAL_FDB /SX_TRAP_ID_ACL/SX_TRAP_ID_IPTRAP,
 *       trap_action field is ignored.
 *       Instead, the action should be configured in each module.
 */
sx_status_t sx_api_host_ifc_trap_id_set(const sx_api_handle_t  handle,
                                        const sx_swid_t        swid,
                                        const sx_trap_id_t     trap_id,
                                        const sx_trap_group_t  trap_group,
                                        const sx_trap_action_t trap_action);

/**
 * Register / DeRegister Traps (STP , LACP)  or Events (Port up /
 * down , Temperature event) in the driver. Configure the driver
 * to pass packets matching this trap ID / Event ID, criteria &
 * SWID to the client (according to hw_p).
 *
 * @param[in]     handle        - SX-API handle.
 * @param[in]     cmd           - REGISTER    - register to trap trap_id
 *                DEREGISTER    - de-register to trap trap_id
 * @param[in]     trap_id       - Trap ID.
 * @param[in]     user_channel_p  - The channel for the packets
 *       to be trapped.
 *
 * @return  SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if any input parameters is null
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_MEMORY_ERROR error handling memory
 * @return SX_STATUS_NO_RESOURCES device was not opened
 */

sx_status_t sx_api_host_ifc_trap_id_register_set(const sx_api_handle_t    handle,
                                                 const sx_access_cmd_t    cmd,
                                                 const sx_swid_t          swid,
                                                 const sx_trap_id_t       trap_id,
                                                 const sx_user_channel_t *user_channel_p);

/**
 * This function configures the switch to filter packets received from certain ports/LAGs.
 * If cmd is ADD, the given ports are added to the filter list.
 * If the cmd is DELETE the given ports are removed from the trap filter list.
 * If the cmd is DELETE_ALL all ports and LAGs which were previously added to the filter
 * are removed. In this case log_port_num and log_port_list parameters are ignored.
 *
 * @param[in] handle        - SX-API handle.
 * @param[in] cmd           - ADD / DELETE /DELETE_ALL
 * @param[in] swid          - Switch ID.
 * @param[in] trap_id       - Trap ID to filter on.
 * @param[in,out] log_port_list - List of Logical Ports to ADD/DELETE to/from the trap's filter list.
 *               If the API returns an error the list will contain the ports/LAGs which were
 *               not added successfully to the filter list.
 * @param[in,out] log_port_num  - Number of Logical Ports to ADD/DELETE to/from the trap's filter list.
 *               If the API returns and error it will hold the number of ports/LAGs which were
 *               not added successfully to the filter list.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if any input parameters is null
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_CMD_UNSUPPORTED if the command is not supported
 * @return SX_STATUS_ERROR if a general error has occurred
 */
sx_status_t sx_api_host_ifc_trap_filter_set(const sx_api_handle_t handle,
                                            const sx_access_cmd_t cmd,
                                            const sx_swid_t       swid,
                                            const sx_trap_id_t    trap_id,
                                            sx_port_log_id_t     *log_port_list_p,
                                            uint32_t             *log_port_cnt_p);

/**
 *  This function binds/unbinds a policer to a trap priority.
 *  The policer type must be a global slow policer.
 *
 * @param[in] handle           - SX-API handle.
 * @param[in] cmd              - BIND/UNBIND.
 * @param[in] swid             - Switch ID.
 * @param[in] trap_group    - Trap group .
 * @param[in] policer_id       - Policer ID.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if any input parameters is null
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_MEMORY_ERROR error handling memory
 * @return SX_STATUS_NO_RESOURCES device was not opened
 */
sx_status_t sx_api_host_ifc_policer_bind_set(const sx_api_handle_t handle,
                                             const sx_access_cmd_t cmd,
                                             const sx_swid_t       swid,
                                             const sx_trap_group_t trap_group,
                                             const sx_policer_id_t policer_id);

#endif /* __SX_API_HOST_IFC_H__ */
