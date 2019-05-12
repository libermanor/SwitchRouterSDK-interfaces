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
#ifndef __SX_API_TUNNEL_H__
#define __SX_API_TUNNEL_H__

#include <sx/sdk/sx_api.h>
#include <sx/sdk/sx_strings.h>

/************************************************
 *  API functions
 ***********************************************/

/**
 * This API sets the log verbosity level of TUNNEL MODULE.
 * Supported devices: Spectrum, Spectrum2.
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
 * Supported devices: Spectrum, Spectrum2.
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
 * On Spectrum2 SDK user may configure from which port (ingress or egress) he
 * want to get packet ethertype.
 * By default packet ethertype will be taken from ingress port. To change default
 * logic SDK user should create VxLAN tunnel with ethertype SX_ETHERTYPE_FROM_EGRESS_PORT.
 *
 * Supported devices: Spectrum, Spectrum2.
 *
 * @param[in] handle          - SX-API handle
 * @param[in] cmd             - CREATE / DESTROY / EDIT
 * @param[in] tunnel_attr_p   - pointer to tunnel attributes structure.
 * @param[in,out] tunnel_id_p - Tunnel ID
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_UNSUPPORTED if api is not supported for this device
 * @return SX_STATUS_CMD_UNSUPPORTED command is not supported for this api
 * @return SX_STATUS_ENTRY_NOT_FOUND if any input parameter doesn't exist
 * @return SX_STATUS_MODULE_UNINITIALIZED when tunnel module is uninitialized
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_tunnel_set(const sx_api_handle_t        handle,
                              const sx_access_cmd_t        cmd,
                              const sx_tunnel_attribute_t *tunnel_attr_p,
                              sx_tunnel_id_t              *tunnel_id_p);


/**
 * This API get Tunnels configuration.
 * Supported devices: Spectrum, Spectrum2.
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
 * Supported devices: Spectrum, Spectrum2.
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
 * This API is used to manage decap table rules.
 * The decap table is used to terminate encapsulated packets.
 *
 * The key provides packet matching mechanism.
 * so each key is mapped to one tunnel.
 *
 * Supported devices: Spectrum, Spectrum2.
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
 * Supported devices: Spectrum, Spectrum2.
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
 * This API is used to init tunneling module.
 * Please note that you should set correct parsing depth with
 * sx_api_port_parsing_depth_set accordingly to tunneling usage
 * scenarios.
 * Supported devices: Spectrum, Spectrum2.
 *
 * @param[in] handle   - SX-API handle
 * @param[in] params_p - pointer to general params structure.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_NO_RESOURCES if cannot allocate resources for tunneling.
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_tunnel_init_set(const sx_api_handle_t handle, sx_tunnel_general_params_t *params_p);

/**
 * This API is used to deinit tunneling module.
 * Supported devices: Spectrum, Spectrum2.
 *
 * @param[in] handle   - SX-API handle
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_tunnel_deinit_set(const sx_api_handle_t handle);

/**
 * This API is used to manage tunnel to bridge/VLAN mapping.
 *
 * When using command delete all, map_entries_p is deprecated.
 * Supported devices: Spectrum, Spectrum2.
 *
 * @param[in] handle             - SX-API handle
 * @param[in] cmd                - ADD / DELETE / DELETE_ALL
 * @param[in] tunnel_id          - Tunnel ID
 * @param[in] map_entries_p      - Array of map entries
 * @param[in] map_entries_cnt    - amount of entries in map_entries_p
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_ENTRY_NOT_FOUND if tunnel doesn't exists.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_ENTRY_ALREADY_EXISTS if tunnel and bridge/VLAN already bound.
 * @return SX_STATUS_UNSUPPORTED if api is not supported for this device
 * @return SX_STATUS_MODULE_UNINITIALIZED when tunnel module is uninitialized
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if try to delete more maps than configured for the tunnel
 * @return SX_STATUS_ERROR general error
 * */
sx_status_t sx_api_tunnel_map_set(const sx_api_handle_t         handle,
                                  const sx_access_cmd_t         cmd,
                                  const sx_tunnel_id_t          tunnel_id,
                                  const sx_tunnel_map_entry_t * map_entries_p,
                                  const uint32_t                map_entries_cnt);

/*
 *  This API gets the tunnel to bridge/VLAN mapping information.
 *
 *  The function can receive three types of input:
 *
 *   - 1) cmd SX_ACCESS_CMD_GET_FIRST,
 *        get a list of first n<=1000 map entries of specified tunnel id.
 *
 *   - 2) cmd SX_ACCESS_CMD_GETNEXT,
 *        get a list of n<=1000 next map entries whose value larger
 *        than the given map_entry_key of specified tunnel id.
 *
 * Supported devices: Spectrum, Spectrum2.
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
 * This API is used to set tunnel TTL parameters.
 *
 * Note for Spectrum:
 * 1. TTL behavior and values are shared between all tunnels of
 * the same type.
 * 2. For IPinIP tunnels in encap direction TTL_CMD_SET and
 * TTL_CMD_COPY are supported, default value is TTL_CMD_COPY.
 * 3. For NVE tunnels in encap direction TTL_CMD_SET is
 * supported. Default value is 255.
 *
 * Supported devices: Spectrum, Spectrum2.
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
 * This API is used to get tunnel TTL parameters.
 *
 * Supported devices: Spectrum, Spectrum2.
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
 * This API is used to set tunnel hash parameters.
 *
 * Note for Spectrum:
 * 1. Hash parameters are shared between all tunnels of the same
 * type.
 * 2. IPinIP tunnels support setting an IPV6_FLOW_LABEL. Default
 * value is 0.
 * 3. NVE tunnels support setting a UDP_SPORT. Default value is
 * 0.
 *
 * Supported devices: Spectrum, Spectrum2.
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
 * This API is used to get tunnel hash parameters.
 *
 * Supported devices: Spectrum, Spectrum2.
 *
 * @param[in] handle          - SX-API handle
 * @param[in] tunnel_id       - Tunnel ID
 * @param[in, out] hash_data_p    - pointer to tunnel hash data
 *       structure, set hash_field_type field for which you want
 *       get config.
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
 * This API is used to set tunnel CoS attributes.
 *
 * The key is the tunnel id.
 * User is capable to set a tunnel CoS behaviour per tunnel type.
 * Changes in 1 tunnel will change the CoS behaviour for all tunnels from the same type.
 *
 * The API configures QoS parameters for encapsulation and decapsulation
 * flow separately based on value in cos_data_p->param_type.
 * Next parameters can be configured with the API:
 *
 * Whether packet switch priority and color should be preserved or a new one
 * must be set (cos_data_p->update_priority_color)
 *      If update_priority_color set to TRUE, new prio and
 *      color are taken from cos_data_p->prio_color
 * DSCP rewrite can be disabled/enabled or a value that was set
 * on packet ingress port can be preserved (cos_data_p->dsc_rewrite)
 *
 * If DSCP rewrite is disabled: DSCP value can be depending on cos_data_p->dscp_action
 *       - on encap can be copied from inner header or set from cos_data_p->dscp_value
 *       - on decap can be copied from outer or preserved
 * When dscp_action is copy and there is no IP header - the value
 * from cos_data_p->dscp_value is used.
 * ECN mapping on encapsulation or decapsulation
 *
 * Supported devices: Spectrum, Spectrum2.
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
 * The user has to fill cos_data_p->param_type to specify the
 * CoS direction they would like to get (ENCAP or DECAP).
 * Supported devices: Spectrum, Spectrum2.
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
 *  Supported devices: Spectrum, Spectrum2.
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


#endif /* __SX_API_TUNNEL_H__ */
