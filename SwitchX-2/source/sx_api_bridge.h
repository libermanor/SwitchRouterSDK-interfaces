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

#ifndef __SX_API_BRIDGE_H__
#define __SX_API_BRIDGE_H__

#include <sx/sdk/sx_api.h>


/************************************************
 *  Local Defines
 ***********************************************/

/************************************************
 *  Local Macros
 ***********************************************/

/************************************************
 *  Local Type definitions
 ***********************************************/

/************************************************
 *  Defines
 ***********************************************/

/************************************************
 *  Macros
 ***********************************************/

/************************************************
 *  Type definitions
 ***********************************************/

/************************************************
 *  Global variables
 ***********************************************/

/************************************************
 *  Function declarations
 ***********************************************/

/************************************************
 *  API functions
 ***********************************************/

/**
 * This API sets the log verbosity level of BRIDGE MODULE.
 * Supported devices: SwitchX, SwitchX2, Spectrum.
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] verbosity_target         - set verbosity of : API / MODULE / BOTH
 * @param[in] module_verbosity_level   - BRIDGE module verbosity level
 * @param[in] api_verbosity_level      - BRIDGE API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_bridge_log_verbosity_level_set(const sx_api_handle_t           handle,
                                                  const sx_log_verbosity_target_t verbosity_target,
                                                  const sx_verbosity_level_t      module_verbosity_level,
                                                  const sx_verbosity_level_t      api_verbosity_level);

/**
 * This API gets the log verbosity level of BRIDGE MODULE.
 * Supported devices: SwitchX, SwitchX2, Spectrum.
 *
 * @param[in]  handle                   - SX-API handle
 * @param[in]  verbosity_target         - get verbosity of : API / MODULE / BOTH
 * @param[out] module_verbosity_level_p - BRIDGE module verbosity level
 * @param[out] api_verbosity_level_p    - BRIDGE API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_bridge_log_verbosity_level_get(const sx_api_handle_t           handle,
                                                  const sx_log_verbosity_target_t verbosity_target,
                                                  sx_verbosity_level_t           *module_verbosity_level_p,
                                                  sx_verbosity_level_t           *api_verbosity_level_p);

/**
 *  This function is used to create/destroy a bridge.
 *  This function is supported in 802.1D mode only.
 *  Supported devices: SwitchX, SwitchX2, Spectrum.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - CREATE/DESTROY
 * @param[out] bridge_id_p - a bridge_id.
 */
sx_status_t sx_api_bridge_set(const sx_api_handle_t handle,
                              const sx_access_cmd_t cmd,
                              sx_bridge_id_t       *bridge_id_p);

/**
 *  Supported devices: switchX2
 *  This function is used to add a port and vlan to a bridge.
 *  When multiple vlan bridge support is enabled, it is possible to bind different vlans to the same bridge.
 *  When multiple vlan bridge support is disabled, you can bind only one vlan to each bridge.
 *  When cmd==DELETE_PORT the log_port will be removed from all associated bridges.
 *  This function is supported in 802.1D mode only.
 *  Supported devices: SwitchX, SwitchX2.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - ADD/DELETE/DELETE_PORT
 * @param[in] bridge_id - bridge_id.
 * @param[in] log_port - logical port ID.
 * @param[in] vlan - vlan_id.
 * @param[in] egress_mode - TAGGED/UNTAGGED.
 */
sx_status_t sx_api_bridge_port_set(const sx_api_handle_t            handle,
                                   const sx_access_cmd_t            cmd,
                                   const sx_bridge_id_t             bridge_id,
                                   const sx_port_log_id_t           log_port,
                                   const sx_vlan_id_t               vlan,
                                   const sx_untagged_member_state_t egress_mode);

/**
 *  Supported devices: switchX2
 *  This function is used to get a list of all ports and vlans associated with a bridge.
 *  When using bridge_port_cnt_p == 0, the number of existing entries will be returned.
 *  This function is supported in 802.1D mode only.
 *  Supported devices: SwitchX, SwitchX2.
 *
 * @param[in] handle - SX-API handle
 * @param[in] bridge_id - bridge_id.
 * @param[out] bridge_port_list_p log_port - a pointer to a bridge_port list.
 * @param[in/out] bridge_port_cnt_p - size of the bridge_port_list.
 */
sx_status_t sx_api_bridge_port_get(const sx_api_handle_t handle,
                                   const sx_bridge_id_t  bridge_id,
                                   sx_bridge_port_t     *bridge_port_list_p,
                                   uint32_t             *bridge_port_cnt_p);

/**
 *  Supported devices: Spectrum
 *  This function is used to add a virtual port to a bridge.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - ADD/DELETE/DELETE_ALL
 * @param[in] bridge_id - bridge_id.
 * @param[in] log_port - logical virtual port ID.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if bridge not found in DB
 * @return SX_STATUS_ERROR if unexpected behaviour occurs
 */
sx_status_t sx_api_bridge_vport_set(const sx_api_handle_t  handle,
                                    const sx_access_cmd_t  cmd,
                                    const sx_bridge_id_t   bridge_id,
                                    const sx_port_log_id_t log_port);

/**
 *  Supported devices: Spectrum
 *  This function is used to get a list of all virtual ports associated with a bridge.
 *  When using bridge_vport_cnt_p == 0, the number of existing entries will be returned.
 *
 * @param[in] handle - SX-API handle
 * @param[in] bridge_id - bridge_id.
 * @param[out] bridge_vport_list_p - a pointer to a sx_port_log_id_t list.
 * @param[in/out] bridge_vport_cnt_p - size of the bridge_vport_list.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if bridge not found in DB
 * @return SX_STATUS_ERROR if unexpected behaviour occurs
 */
sx_status_t sx_api_bridge_vport_get(const sx_api_handle_t handle,
                                    const sx_bridge_id_t  bridge_id,
                                    sx_port_log_id_t     *bridge_vport_list_p,
                                    uint32_t             *bridge_vport_cnt_p);

/**
 *  Supported devices: Spectrum
 *  This function is used to bind/unbind a flow counter to a bridge.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - BIND/UNBIND
 * @param[in] bridge_id - bridge_id.
 * @param[in] flow_counter_id - flow counter id to bind
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if bridge is not found in DB
 * @return SX_STATUS_ERROR if unexpected behaviour occurs
 */
sx_status_t sx_api_bridge_counter_bind_set(const sx_api_handle_t      handle,
                                           const sx_access_cmd_t      cmd,
                                           const sx_bridge_id_t       bridge_id,
                                           const sx_flow_counter_id_t flow_counter_id);

/**
 *  Supported devices: Spectrum
 *  This function is used to get the flow counter bound to the bridge.
 *  When no counter is bound to the bridge,
 *  flow_counter_id_p will be set to SX_FLOW_COUNTER_ID_INVALID.
 *
 * @param[in] handle - SX-API handle
 * @param[in] bridge_id - bridge_id.
 * @param[out] flow_counter_id_p - bound counter id
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if bridge is not found in DB
 * @return SX_STATUS_ERROR if unexpected behaviour occurs
 */
sx_status_t sx_api_bridge_counter_bind_get(const sx_api_handle_t handle,
                                           const sx_bridge_id_t  bridge_id,
                                           sx_flow_counter_id_t* flow_counter_id_p);

/**
 *  Supported devices: Spectrum
 *  This function sets the mirroring mode for a bridge.
 *   Currently only ingress direction is supported.
 *
 * @param[in] handle - SX-API handle
 * @param[in] bridge_id - mirror bridge.
 * @param[in] mirror_direction - ingress\egress
 * @param[in] mirror_mode - enabled\disabled
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if bridge not found in DB
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 **/
sx_status_t sx_api_bridge_mirror_set(const sx_api_handle_t       handle,
                                     const sx_bridge_id_t        bridge_id,
                                     const sx_mirror_direction_t mirror_direction,
                                     const sx_mirror_mode_t      mirror_mode);

/**
 *  Supported devices: Spectrum
 *  This function gets the mirroring mode for a bridge by direction and bridge ID
 *  Currently only ingress direction is supported.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] bridge_id - mirror bridge
 * @param[in] mirror_direction - ingress/egress
 * @param[out] mirror_mode_p - the returned mirroring mode
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if bridge is not found in DB
 * @return SX_STATUS_ERROR if unexpected behaviour occurs
 **/
sx_status_t sx_api_bridge_mirror_get(const sx_api_handle_t       handle,
                                     const sx_bridge_id_t        bridge_id,
                                     const sx_mirror_direction_t mirror_direction,
                                     sx_mirror_mode_t           *mirror_mode_p);

#endif /* __SX_API_BRIDGE_H__ */
