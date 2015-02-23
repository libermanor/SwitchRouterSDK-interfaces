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

#ifndef __SX_API_BRIDGE_H__
#define __SX_API_BRIDGE_H__

#include <sx/sdk/sx_api.h>


/************************************************
 *  API functions
 ***********************************************/

/**
 * This API sets the log verbosity level of BRIDGE MODULE.
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
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - CREATE/DESTROY
 * @param[out] bridge_id_p - a bridge_id.
 */
sx_status_t sx_api_bridge_set(const sx_api_handle_t handle,
                              const sx_access_cmd_t cmd,
                              sx_bridge_id_t       *bridge_id_p);

/**
 *  This function is used to add a port and vlan to a bridge.
 *  When multiple vlan bridge support is enabled, it is possible to bind different vlans to the same bridge.
 *  When multiple vlan bridge support is disabled, you can bind only one vlan to each bridge.
 *  When cmd==DELETE_PORT the log_port will be removed from all associated bridges.
 *  This function is supported in 802.1D mode only.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - ADD/DELETE/DELETE_PORT
 * @param[in] bridge_id - bridge_id.
 *  @param[in] log_port - logical port ID.
 *  @param[in] vlan - vlan_id.
 *  @param[in] egress_mode - TAGGED/UNTAGGED.
 */
sx_status_t sx_api_bridge_port_set(const sx_api_handle_t            handle,
                                   const sx_access_cmd_t            cmd,
                                   const sx_bridge_id_t             bridge_id,
                                   const sx_port_log_id_t           log_port,
                                   const sx_vlan_id_t               vlan,
                                   const sx_untagged_member_state_t egress_mode);

/**
 *  This function is used to get a list of all ports and vlans associated with a bridge.
 *  When using bridge_port_cnt_p == 0, the number of existing entries will be returned.
 *  This function is supported in 802.1D mode only.
 *
 * @param[in] handle - SX-API handle
 * @param[in] bridge_id - bridge_id.
 *  @param[out] bridge_port_list_p log_port - a pointer to a bridge_port list.
 *  @param[in/out] bridge_port_cnt_p - size of the bridge_port_list.
 */
sx_status_t sx_api_bridge_port_get(const sx_api_handle_t handle,
                                   const sx_bridge_id_t  bridge_id,
                                   sx_bridge_port_t     *bridge_port_list_p,
                                   uint32_t             *bridge_port_cnt_p);


#endif /* __SX_API_BRIDGE_H__ */
