/*
 *  Copyright (C) 2014-2020. Mellanox Technologies, Ltd. ALL RIGHTS RESERVED.
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
#ifndef __SX_API_TUNNEL_H__
#define __SX_API_TUNNEL_H__

#include <sx/sdk/sx_api.h>
#include <sx/sdk/sx_strings.h>

/************************************************
 *  API functions
 ***********************************************/

/**
 * This API sets the log verbosity level of TUNNEL MODULE.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] verbosity_target         - set verbosity of : API / MODULE / BOTH
 * @param[in] module_verbosity_level   - TUNNEL module verbosity level
 * @param[in] api_verbosity_level      - TUNNEL API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE when parameter exceeds range.
 */
sx_status_t sx_api_tunnel_log_verbosity_level_set(const sx_api_handle_t           handle,
                                                  const sx_log_verbosity_target_t verbosity_target,
                                                  const sx_verbosity_level_t      module_verbosity_level,
                                                  const sx_verbosity_level_t      api_verbosity_level);

/**
 * This API gets the log verbosity level of TUNNEL MODULE.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in]  handle                   - SX-API handle
 * @param[in]  verbosity_target         - get verbosity of : API / MODULE / BOTH
 * @param[out] module_verbosity_level_p - TUNNEL module verbosity level
 * @param[out] api_verbosity_level_p    - TUNNEL API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE when parameter exceeds range.
 */
sx_status_t sx_api_tunnel_log_verbosity_level_get(const sx_api_handle_t           handle,
                                                  const sx_log_verbosity_target_t verbosity_target,
                                                  sx_verbosity_level_t           *module_verbosity_level_p,
                                                  sx_verbosity_level_t           *api_verbosity_level_p);

/**
 * This API is used to create/edit/destroy tunnels.
 *
 * When destroying a tunnel, tunnel_attr_p is ignored.
 * By default tunnel is created with TTL 255.
 * On Spectrum2, Spectrum3,the SDK user can select the port(ingress or egress) that is used to determine
 * packet ethertype.
 * By default the packet ethertype is taken from ingress port. To change the default behavior, SDK
 * user should create VxLAN tunnel with ethertype SX_ETHERTYPE_FROM_EGRESS_PORT.
 *
 * Lazy delete feature is supported for VxLAN tunnels.
 * If the Lazy delete feature is disabled and the reference counter of tunnel is 0,
 * then the API call with DELETE command deletes the tunnel, otherwise the
 * SDK returns SX_STATUS_RESOURCE_IN_USE.
 *
 * If the Lazy delete feature is enabled and the reference counter of a tunnel is not 0,
 * the API call with command DELETE marks a tunnel as deleted, and the
 * SDK returns SX_STATUS_SUCCESS.
 * Once the reference counter of a tunnel becomes 0, SDK will delete the tunnel and
 * will generate a notification with the trap id(SX_TRAP_ID_OBJECT_DELETED_EVENT) and the id
 * of tunnel that was deleted.
 *
 * Given below is the list of objects that increases the reference counter of a NVE tunnel:
 * 1. each tunnel map entry;
 * 2. each MC RPF VIF of type SX_ROUTER_VINTERFACE_TYPE_VXLAN;
 * 3. each ECMP next hop of the type SX_NEXT_HOP_TYPE_TUNNEL_ENCAP;
 * 4. each MC next hop of the type SX_MC_NEXT_HOP_TYPE_TUNNEL_ENCAP_IP;
 * 5. each ACL rule with an action of the type SX_FLEX_ACL_ACTION_TUNNEL_DECAP;
 * 6. each ACL rule with an action of the type SX_FLEX_ACL_ACTION_NVE_TUNNEL_ENCAP;
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle          - SX-API handle
 * @param[in] cmd             - CREATE / DESTROY / EDIT
 * @param[in] tunnel_attr_p   - pointer to tunnel attributes structure.
 * @param[in,out] tunnel_id_p - Tunnel ID
 *
 * @return SX_STATUS_SUCCESS if the operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any of the input parameters is invalid
 * @return SX_STATUS_UNSUPPORTED if the api is not supported for this device
 * @return SX_STATUS_CMD_UNSUPPORTED if the command is not supported by the api
 * @return SX_STATUS_ENTRY_NOT_FOUND if any of the input parameters doesn't exist
 * @return SX_STATUS_MODULE_UNINITIALIZED when tunnel module is uninitialized
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_tunnel_set(const sx_api_handle_t        handle,
                              const sx_access_cmd_t        cmd,
                              const sx_tunnel_attribute_t *tunnel_attr_p,
                              sx_tunnel_id_t              *tunnel_id_p);


/**
 * This API gets the tunnel configuration.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle         - SX-API handle
 * @param[in] tunnel_id      - Tunnel ID
 * @param[out] tunnel_attr_p - pointer to tunnel attributes structure.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_UNSUPPORTED if api is not supported for this device
 * @return SX_STATUS_MODULE_UNINITIALIZED when tunnel module is uninitialized
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_tunnel_get(const sx_api_handle_t  handle,
                              const sx_tunnel_id_t   tunnel_id,
                              sx_tunnel_attribute_t *tunnel_attr_p);

/**
 * This API get/clear tunnel counters.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle        - SX-API handle
 * @param[in] cmd           - READ / READ_CLEAR
 * @param[in] tunnel_id     - Tunnel ID
 * @param[out] counter      - pointer to tunnel counters structure.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_UNSUPPORTED if api is not supported for this device
 * @return SX_STATUS_MODULE_UNINITIALIZED when tunnel module is uninitialized
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_tunnel_counter_get(const sx_api_handle_t handle,
                                      const sx_access_cmd_t cmd,
                                      const sx_tunnel_id_t  tunnel_id,
                                      sx_tunnel_counter_t  *counter);

/**
 * This API is used to manage rules in the tunnel decap table.
 * The decap table is used to terminate encapsulated packets.
 *
 * The decap key provides packet matching mechanism and  each key
 * is mapped to one tunnel.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle        - SX-API handle
 * @param[in] cmd           - CREATE / DESTROY / EDIT
 * @param[in] decap_key_p   - decap key
 * @param[in] decap_data_p  - decap data
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_UNSUPPORTED if api is not supported for this device.
 * @return SX_STATUS_ENTRY_NOT_FOUND if any input parameter doesn't exist
 * @return SX_STATUS_ENTRY_ALREADY_EXISTS if key already used for another tunnel.
 * @return SX_STATUS_MODULE_UNINITIALIZED when tunnel module is not initialized
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter exceeds valid range
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_tunnel_decap_rules_set(const sx_api_handle_t               handle,
                                          const sx_access_cmd_t               cmd,
                                          const sx_tunnel_decap_entry_key_t  *decap_key_p,
                                          const sx_tunnel_decap_entry_data_t *decap_data_p);

/**
 * This API is used to get decap rules from decap table.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in]  handle         - SX-API handle
 * @param[in]  decap_key_p    - Key to query.
 * @param[out] decap_data_p   - Data associated with key.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_UNSUPPORTED if api is not supported for this device
 * @return SX_STATUS_ENTRY_NOT_FOUND if key doesn't exists.
 * @return SX_STATUS_MODULE_UNINITIALIZED when tunnel module is uninitialized
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_tunnel_decap_rules_get(const sx_api_handle_t              handle,
                                          const sx_tunnel_decap_entry_key_t *decap_key_p,
                                          sx_tunnel_decap_entry_data_t      *decap_data_p);

/**
 * This API is used to initialize tunneling module.
 * Please note that the correct parsing depth should be set using
 * sx_api_port_parsing_depth_set API for tunneling usage scenarios.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle   - SX-API handle
 * @param[in] params_p - pointer to general params structure.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_NO_RESOURCES if sufficient resources are not available for tunneling.
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_tunnel_init_set(const sx_api_handle_t handle, sx_tunnel_general_params_t *params_p);

/**
 * This API is used to de-initialize the tunneling module.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle   - SX-API handle
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_tunnel_deinit_set(const sx_api_handle_t handle);

/**
 * This API is used to manage the mapping between tunnel and bridge/VLAN.
 * With the DELETE_ALL command, the map_entries_p parameter is ignored.
 *
 * Lazy delete feature is supported for VxLAN tunnel mappings.
 * If Lazy delete feature is disabled and the reference counter of the tunnel mapping is 0,
 * then the API call with command DELETE deletes a tunnel mapping, otherwise
 * the SDK returns SX_STATUS_RESOURCE_IN_USE.
 *
 * If the Lazy delete feature is enabled and the reference counter of the tunnel mapping is not 0,
 * then the API call with command DELETE marks a tunnel mapping as deleted, and
 * SDK returns SX_STATUS_SUCCESS.
 * Once the reference counter of the tunnel mapping becomes 0, SDK will delete the tunnel
 * mapping, unbind DECAP, ENCAP UC and ENCAP MC flow counters if they are bound and will
 * generate a notification with the trap id(SX_TRAP_ID_OBJECT_DELETED_EVENT) and the copy
 * of tunnel mapping that was deleted.
 * NOS should monitor delete notification events in order to delete the counter resource.
 * If the user tries to re-create a tunnel map entry before a notification is received,
 * then the SDK returns error SX_STATUS_RESOURCE_IN_USE.
 *
 * Given below is the list of objects that increases the reference counter of a tunnel map entry:
 * 1. a static tunnel UC FDB entry;
 * 2. a MC FDB entry (if MC container has a tunnel next hop);
 * 3. each tunnel flood vector that was bound to a FID with sx_api_fdb_flood_set;
 * 4. each ACL rule with an action of the type SX_FLEX_ACL_ACTION_NVE_MC_TUNNEL_ENCAP (if MC container has a tunnel next hop);
 *
 * The map_entries_cnt parameter is limited by TUNNEL_MAP_ENTRIES_SET_MAX_NUM.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle             - SX-API handle
 * @param[in] cmd                - ADD / DELETE / DELETE_ALL
 * @param[in] tunnel_id          - Tunnel ID
 * @param[in] map_entries_p      - Array of map entries
 * @param[in] map_entries_cnt    - amount of entries in map_entries_p
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_ENTRY_NOT_FOUND if tunnel doesn't exist.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_ENTRY_ALREADY_EXISTS if tunnel and bridge/VLAN already bound.
 * @return SX_STATUS_UNSUPPORTED if api is not supported for this device.
 * @return SX_STATUS_CMD_UNSUPPORTED if cmd is unsupported in this API.
 * @return SX_STATUS_MODULE_UNINITIALIZED when tunnel module is uninitialized.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if try to delete more maps than configured for the tunnel.
 * @return SX_STATUS_RESOURCE_IN_USE if the user tries to re-create a tunnel map entry that is marked as deleted.
 * @return SX_STATUS_ERROR general error.
 * */
sx_status_t sx_api_tunnel_map_set(const sx_api_handle_t         handle,
                                  const sx_access_cmd_t         cmd,
                                  const sx_tunnel_id_t          tunnel_id,
                                  const sx_tunnel_map_entry_t * map_entries_p,
                                  const uint32_t                map_entries_cnt);

/**
 *  This API gets the mapping information between tunnel and  bridge/VLAN.
 *  This function supports the below commands in the order mentioned below.
 *   1) cmd SX_ACCESS_CMD_GET_FIRST,
 *        get a list of first n<=1000 map entries of specified tunnel id.
 *
 *   2) cmd SX_ACCESS_CMD_GETNEXT,
 *        get a list of n<=1000 next map entries whose value larger
 *        than the given map_entry_key of specified tunnel id.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle                - SX-API handle.
 * @param[in] cmd                   - GET_FIRST/ GET_NEXT.
 * @param[in] tunnel_id             - Tunnel ID
 * @param[in] map_entry_key         - map entry, as a key to get next entries
 * @param[out] map_entries_p        - Array of map entries
 * @param[in,out] map_entries_cnt_p - amount of entries in map_entries_p
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND if neighbor was not added.
 * @return SX_STATUS_MODULE_UNINITIALIZED when tunnel module is uninitialized
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_tunnel_map_get(const sx_api_handle_t   handle,
                                  const sx_access_cmd_t   cmd,
                                  const sx_tunnel_id_t    tunnel_id,
                                  sx_tunnel_map_entry_t   map_entry_key,
                                  sx_tunnel_map_entry_t * map_entries_p,
                                  uint32_t              * map_entries_cnt_p);

/**
 * This API is used to set the tunnel TTL parameters.
 *
 * Note for Spectrum:
 * 1. TTL behavior and values are shared between all tunnels of same type.
 * 2. IPinIP tunnels support TTL_CMD_SET and TTL_CMD_COPY in the encap direction,
 * default value is TTL_CMD_COPY.
 * 3. NVE tunnels support TTL_CMD_SET in the encap direction, default TTL value is 255.
 *
 * Note for Spectrum2 and newer ASICs:
 * 1. IPinIP tunnels support only TTL_CMD_SET & TTL_CMD_COPY commands
 * 2. IPinIP tunnels only support configuring TTL command in encap direction
 * 3. NVE tunnels support TTL_CMD_SET, TTL_CMD_COPY in Encap direction.
 * 4. NVE tunnels support TTL_CMD_PRESERVE_E, TTL_CMD_COPY, TTL_CMD_MINIMUM in decap direction. Default is PRESERVE.
 * 5. For Symmetric tunnels, the TTL behavior must be set separately for encap and decap directions.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle        - SX-API handle
 * @param[in] tunnel_id     - Tunnel ID
 * @param[in] ttl_data_p    - pointer to tunnel ttl data structure.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_UNSUPPORTED if api is not supported for this device
 * @return SX_STATUS_MODULE_UNINITIALIZED when tunnel module is uninitialized
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_tunnel_ttl_set(const sx_api_handle_t       handle,
                                  const sx_tunnel_id_t        tunnel_id,
                                  const sx_tunnel_ttl_data_t *ttl_data_p);

/**
 * This API is used to get the tunnel TTL parameters.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle             - SX-API handle
 * @param[in] tunnel_id          - Tunnel ID
 * @param[in, out] ttl_data_p    - pointer to tunnel ttl data
 *       structure, set direction field for which you want get
 *       config.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_UNSUPPORTED if api is not supported for this device
 * @return SX_STATUS_MODULE_UNINITIALIZED when tunnel module is uninitialized
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_tunnel_ttl_get(const sx_api_handle_t handle,
                                  const sx_tunnel_id_t  tunnel_id,
                                  sx_tunnel_ttl_data_t *ttl_data_p);

/**
 * This API is used to set the tunnel hash parameters.
 *
 * Note for Spectrum:
 * 1. Hash parameters are shared between all tunnels of the same type.
 * 2. IPinIP tunnels support setting an IPV6_FLOW_LABEL. Default value is 0.
 * 3. NVE tunnels support setting a UDP_SPORT. Default value is 0.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle         - SX-API handle
 * @param[in] tunnel_id      - Tunnel ID
 * @param[in] hash_data_p    - pointer to tunnel hash data structure.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_UNSUPPORTED if api is not supported for this device
 * @return SX_STATUS_MODULE_UNINITIALIZED when tunnel module is uninitialized
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_tunnel_hash_set(const sx_api_handle_t        handle,
                                   const sx_tunnel_id_t         tunnel_id,
                                   const sx_tunnel_hash_data_t *hash_data_p);

/**
 * This API is used to get the tunnel hash parameters.
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle          - SX-API handle
 * @param[in] tunnel_id       - Tunnel ID
 * @param[in, out] hash_data_p    - pointer to tunnel hash data
 *       structure, hash_field_type should  be set for retrieving the correct config.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_UNSUPPORTED if api is not supported for this device
 * @return SX_STATUS_MODULE_UNINITIALIZED when tunnel module is uninitialized
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_tunnel_hash_get(const sx_api_handle_t  handle,
                                   const sx_tunnel_id_t   tunnel_id,
                                   sx_tunnel_hash_data_t *hash_data_p);

/**
 * This API is used to set the CoS attributes of tunnel.
 * CoS behaviour applies to all tunnels of a given type. Changes
 * applied to one tunnel will change the CoS behaviour of all tunnels of same type.
 *
 * The API configures QoS parameters for encapsulation and decapsulation
 * flow separately based on value in cos_data_p->param_type.
 *
 * Given below are the parameters that can be configured with this API:
 *
 * 1. cos_data_p->update_priority_color - Packet switch priority and color
 *    when it is not preserved.
 * 2. cos_data_p->prio_color - New switch priority and color for the packet
 *    when cos_data_p->update_priority_color is set to TRUE.
 * 3. cos_data_p->dsc_rewrite - Action for DSCP rewrite i.e disabled, enabled or preserved to a dscp value
 *    that was set on packet ingress port.
 *    cos_data_p->dscp_action - If DSCP rewrite is disabled then DSCP value is dependent on dscp_action.
 *      - the DSCP value on encap can be copied from inner header or set from cos_data_p->dscp_value
 *      - the DSCP value on decap can be copied from outer or preserved
 *    When dscp_action is copy and if there is no IP header, then the value from cos_data_p->dscp_value
 *     is used.
 * 4. ECN mapping on encapsulation or decapsulation
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 * @param[in] handle              - SX-API handle
 * @param[in] tunnel id           - Tunnel ID.
 * @param[in] cos_data_p          - Pointer to CoS data structure.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_UNSUPPORTED if api is not supported for this device or tunnel type/direction.
 * @return SX_STATUS_ENTRY_NOT_FOUND if tunnel doesn't exists.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_MODULE_UNINITIALIZED when tunnel module is uninitialized
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_tunnel_cos_set(const sx_api_handle_t       handle,
                                  const sx_tunnel_id_t        tunnel_id,
                                  const sx_tunnel_cos_data_t *cos_data_p);
/**
 * This API is used to retrieve CoS data.
 * CoS data retrieval for ENCAP or DECAP direction can be controlled by cos_data_p->param_type.
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in]  handle               - SX-API handle
 * @param[in]  tunnel id            - Tunnel ID.
 * @param[in/out] cos_data_p        - Pointer to CoS data structure - by CoS param type (ENCAP/DECAP).
 *
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_UNSUPPORTED if api is not supported for this device or tunnel type/direction
 * @return SX_STATUS_ENTRY_NOT_FOUND if tunnel doesn't exists.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_MODULE_UNINITIALIZED when tunnel module is uninitialized
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_tunnel_cos_get(const sx_api_handle_t handle,
                                  const sx_tunnel_id_t  tunnel_id,
                                  sx_tunnel_cos_data_t *cos_data_p);

/**
 *  This API retrieves a list of one or more Tunnel IDs.
 *  The following use case scenarios apply with different input parameters
 *  X = don't-care
 *   - 1) cmd = SX_ACCESS_CMD_GET, tunnel_id = X, filter = valid/invalid, tunnel_id_list = X,
 *        tunnel_id_cnt = 0:
 *        In this case the API will return the total number of tunnel IDs filtered by the filter
 *        parameter if present.
 *
 *   - 2) cmd = SX_ACCESS_CMD_GET, tunnel_id = valid/invalid, filter = valid/invalid,
 *        tunnel_id_list = valid, tunnel_id_cnt = 1:
 *        In this case the API will check if the specified tunnel_id exists AND it matches the
 *        filter if present.
 *        If it does, the tunnel ID will be returned in the tunnel_id_list along with
 *        a tunnel_id_cnt of 1.
 *        If the tunnel ID does not exist, an empty list will be returned with
 *        tunnel_id_cnt = 0.
 *        A non-NULL tunnel_id_list pointer must be provided in this case.
 *
 *   - 3) cmd = SX_ACCESS_CMD_GET, tunnel_id = valid/invalid, filter = valid/invalid,
 *        tunnel_id_list = valid, tunnel_id_cnt > 1:
 *        A tunnel_id_cnt > 1 will be treated as a tunnel_id_cnt of 1 and the behavior will
 *        be same as the previous GET use cases.
 *
 *   - 4) cmd = SX_ACCESS_CMD_GET_FIRST/SX_ACCESS_CMD_GETNEXT, tunnel_id = X, filter = X,
 *        tunnel_id_list = NULL, tunnel_id_cnt = 0:
 *        A zero tunnel_id_cnt and an empty tunnel_id_list will be returned.
 *
 *   - 5) cmd = SX_ACCESS_CMD_GET_FIRST, tunnel_id = X, tunnel_id_list = valid,
 *        filter =  valid/invalid, tunnel_id_cnt > 0:
 *        In this case the API will return the first tunnel_id_cnt tunnel IDs starting
 *        from the head of the database AND match the filter if present. The total
 *        number of elements fetched will be returned as tunnel_id_cnt.
 *        The input tunnel ID is ignored in this case.
 *        A non-NULL tunnel_id_list pointer must be provided in this case.
 *
 *   - 6) cmd = SX_ACCESS_CMD_GETNEXT, tunnel_id = valid/invalid, filter = valid/invalid,
 *        tunnel_id_list = valid, tunnel_id_cnt > 0:
 *        In this case the API will return the next set of tunnel IDs which matches the filter
 *        if present starting from the next tunnel ID after the specified tunnel ID.
 *        The total number of elements fetched will be returned as the tunnel_id_cnt.
 *        If no valid next tunnel ID exists in the db, an empty list will be returned.
 *        A non-NULL tunnel_id_list pointer must be provided in this case.
 *
 *  Two type of filter can be used,
 *     1) sx_tunnel_type_e: it exactly match the type defined for the tunnels
 *     2) sx_tunnel_direction_e: if tunnel direction is SX_TUNNEL_DIRECTION_SYMMETRIC, it will
 *        match any direction(ENCAP/DECAP/SYMMETRIC) of filter, otherwise, it will only match
 *        the same direction of filter.
 *
 *  Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param[in] handle               - SX-API handle
 * @param [in] cmd                 - GET/GET_FIRST/GET_NEXT
 * @param[in] tunnel_id            - tunnel ID
 * @param [in] filter_p            - specify a filter parameter
 * @param [out] tunnel_id_list_p   - return list of tunnel IDs
 * @param [in,out] tunnel_id_cnt_p - [in] number of tunnel IDs to get
 *                                 - [out] number of tunnel IDs returned
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_CMD_UNSUPPORTED if command is not supported
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_ERROR for a general error
 * @return SX_STATUS_MODULE_UNINITIALIZED for tunnel module uninitialized
 */
sx_status_t sx_api_tunnel_iter_get(const sx_api_handle_t     handle,
                                   const sx_access_cmd_t     cmd,
                                   const sx_tunnel_id_t      tunnel_id,
                                   const sx_tunnel_filter_t *filter_p,
                                   sx_tunnel_id_t           *tunnel_id_list_p,
                                   uint32_t                 *tunnel_id_cnt_p);

/**
 * This API is used to retrieve the count or a list of one or more Tunnel Decap Rules
 * The rules are essentially the Keys that the rules match on.
 * The rule's attributes(actions) can then be read using the sx_api_tunnel_decap_rules_get
 * API for each key.
 * Using the filter param, the return list can be refined. The following filters are supported
 *     1) sx_tunnel_type_e: only return the keys that match the tunnel type
 *     2) sx_tunnel_id: only return the keys that match the tunnel id
 *
 *  The following use case scenarios apply with different input parameters
 *  X = don't-care
 *   - 1) cmd = SX_ACCESS_CMD_GET, key = X, Filter = X, decap_key_list = X, Count=0:
 *        In this case the API will return the total number of Decap rules in the
 *        Internal db
 *
 *   - 2) cmd = SX_ACCESS_CMD_GET, key = valid/invalid, Filter = X, decap_key_list =
 *        Valid, Count = 1:
 *        In this case the API will check if the specified key exists. if it does
 *        the key will be returned in the decap_key_list along with a count of 1.
 *        If the key does not exist an empty list will be returned with count = 0
 *
 *   - 3) cmd = SX_ACCESS_CMD_GET, key = valid, Filter = Valid, decap_key_list is Valid, Count=1:
 *        In this case the API will check if the specified key exists. if it does exist then,
 *        it will check it against the filter parameter. If the filter matches,
 *        then the key will be returned in the decap_key_list along with a count of 1.
 *        If the key does not exist or the filter does not match an empty list
 *        will be returned with count = 0
 *
 *   - 4) cmd = SX_ACCESS_CMD_GET, key = valid, Filter = Valid/invalid,
 *        decap_key_list is Valid, Count > 1:
 *        A count >1 will be treated as a count of 1 and the behavior will be same
 *        as earlier GET use cases.
 *
 *   - 5) cmd = SX_ACCESS_CMD_GET_FIRST/SX_ACCESS_CMD_GETNEXT, key = X, Filter = X,
 *        decap_key_list = Null, Count =0:
 *        For either SX_ACCESS_CMD_GET_FIRST/SX_ACCESS_CMD_GETNEXT a zero count
 *        will return an empty list.
 *
 *   - 6) cmd = SX_ACCESS_CMD_GET_FIRST, key = X, Filter = valid/invalid, decap_key_list =
 *        Valid, Count > 0:
 *        In this case the API will return the first count decap key entries starting from
 *        the head of the database. The total elements fetched will be returned
 *        as the return count.  Note: return count may be less than or equal to
 *        the requested count. The key is dont-care.
 *        If a filter is specified only those decap key entries that match the filter will
 *        be returned. A non-Null return decap_key_list pointer must be provided.
 *
 *   - 7) cmd = SX_ACCESS_CMD_GETNEXT, key = valid/invalid, Filter = valid/invalid,
 *        decap_key_list = Valid, Count > 0:
 *        In this case the API will return the next set of decap key entries starting from
 *        the next valid decap key entry after the specified key. The total elements fetched
 *        will be returned as the return count.  If a filter is specified, then only
 *        those decap key entries that match the filter will be returned.
 *        Note: return count may be less than or equal to the requested count.
 *        If no valid next decap key entry exists in the db (key = end of list, or invalid
 *        key specified, or key too large), an empty list will be returned.
 *
 *
 * Supported devices: Spectrum, Spectrum2, Spectrum3.
 *
 * @param [in] handle               : SX-API handle
 * @param [in] cmd                  : GET/GET_FIRST/GET_NEXT.
 * @param [in] decap_key_p          : specify a Tunnel decap entry key
 * @param [in] decap_filter_p       : specify a filter parameter
 * @param [out] decap_key_list_p    : return list of decap key entries
 * @param [in,out] decap_key_cnt_p  : [in] number of decap keys to read
 *                                  : [out] number of decap keys returned
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_CMD_UNSUPPORTED if an unsupported command is passed
 * @return SX_STATUS_ENTRY_NOT_FOUND if key doesn't exists.
 * @return SX_STATUS_MODULE_UNINITIALIZED when tunnel module is uninitialized
 * @return SX_STATUS_DB_NOT_INITIALIZED if the database was not initialized
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_tunnel_decap_rule_iter_get(const sx_api_handle_t                 handle,
                                              const sx_access_cmd_t                 cmd,
                                              const sx_tunnel_decap_entry_key_t    *decap_key_p,
                                              const sx_tunnel_decap_entry_filter_t *decap_filter_p,
                                              sx_tunnel_decap_entry_key_t          *decap_key_list_p,
                                              uint32_t                             *decap_key_cnt_p);


#endif /* __SX_API_TUNNEL_H__ */
