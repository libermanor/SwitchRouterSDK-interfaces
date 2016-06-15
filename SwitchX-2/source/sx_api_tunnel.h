/*
 *  Copyright (C) 2014-2016. Mellanox Technologies, Ltd. ALL RIGHTS RESERVED.
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

/************************************************
 *  API functions
 ***********************************************/

/**
 * This API sets the log verbosity level of TUNNEL MODULE.
 * Supported devices: Spectrum.
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
 * Supported devices: Spectrum.
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
 * This API is used to create/destroy tunnels.
 *
 * When destroying a tunnel, tunnel_attr_p is ignored.
 * Supported devices: Spectrum.
 *
 * @param[in] handle          - SX-API handle
 * @param[in] cmd             - CREATE / DESTROY
 * @param[in] tunnel_attr_p   - pointer to tunnel attributes structure.
 * @param[in,out] tunnel_id_p - Tunnel ID
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_UNSUPPORTED if api is not supported for this device
 * @return SX_STATUS_CMD_UNSUPPORTED command is not supported for this api
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_tunnel_set(const sx_api_handle_t        handle,
                              const sx_access_cmd_t        cmd,
                              const sx_tunnel_attribute_t *tunnel_attr_p,
                              sx_tunnel_id_t              *tunnel_id_p);


/**
 * This API get Tunnels configuration.
 * Supported devices: Spectrum.
 *
 * @param[in] handle         - SX-API handle
 * @param[in] tunnel_id      - Tunnel ID
 * @param[out] tunnel_attr_p - pointer to tunnel attributes structure.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_UNSUPPORTED if api is not supported for this device
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_tunnel_get(const sx_api_handle_t  handle,
                              const sx_tunnel_id_t   tunnel_id,
                              sx_tunnel_attribute_t *tunnel_attr_p);

/**
 * This API get/clear tunnel counters.
 * Supported devices: Spectrum.
 *
 * @param[in] handle        - SX-API handle
 * @param[in] cmd           - READ / READ_CLEAR
 * @param[in] tunnel_id     - Tunnel ID
 * @param[out] counter      - pointer to tunnel counters structure.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_UNSUPPORTED if api is not supported for this device
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_tunnel_counter_get(const sx_api_handle_t handle,
                                      const sx_access_cmd_t cmd,
                                      const sx_tunnel_id_t  tunnel_id,
                                      sx_tunnel_counter_t  *counter);

/**
 * This API is used to manage tunnel to bridge mapping.
 *
 * When using command delete all, map_entries_p is deprecated.
 * Supported devices: Spectrum.
 *
 * @param[in] handle             - SX-API handle
 * @param[in] cmd				 - ADD / DELETE / DELETE_ALL
 * @param[in] tunnel_id          - Tunnel ID
 * @param[in] map_entries_p      - Array of map entries
 * @param[in] map_entries_cnt    - amount of entries in map_entries_p
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_ENTRY_NOT_FOUND if tunnel or bridge doesn't exists.
 * @return SX_STATUS_ENTRY_ALREADY_BOUND if tunnel and bridge already bound.
 * @return SX_STATUS_UNSUPPORTED if api is not supported for this device
 * @return SX_STATUS_ERROR general error
 * */
static inline sx_status_t sx_api_tunnel_map_set(const sx_api_handle_t        handle,
                                                const sx_access_cmd_t        cmd,
                                                const sx_tunnel_id_t         tunnel_id,
                                                const sx_tunnel_map_entry_t *map_entries_p,
                                                const uint32_t               map_entries_cnt)
{
    UNUSED_PARAM(handle);
    UNUSED_PARAM(cmd);
    UNUSED_PARAM(tunnel_id);
    UNUSED_PARAM(map_entries_p);
    UNUSED_PARAM(map_entries_cnt);
    return SX_STATUS_UNSUPPORTED;
}

/**
 * This API is used to get tunnel to bridge mapping.
 *
 * Supported devices: Spectrum.
 *
 * @param[in] handle                - SX-API handle
 * @param[in] tunnel_id             - Tunnel ID
 * @param[out] map_entries_p        - Array of map entries
 * @param[in,out] map_entries_cnt_p - amount of entries in map_entries_p
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_ENTRY_NOT_FOUND if tunnel doesn't exists.
 * @return SX_STATUS_UNSUPPORTED if api is not supported for this device
 * @return SX_STATUS_ERROR general error
 * */
static inline sx_status_t sx_api_tunnel_map_get(const sx_api_handle_t  handle,
                                                const sx_tunnel_id_t   tunnel_id,
                                                sx_tunnel_map_entry_t *map_entries_p,
                                                uint32_t              *map_entries_cnt_p)
{
    UNUSED_PARAM(handle);
    UNUSED_PARAM(tunnel_id);
    UNUSED_PARAM(map_entries_p);
    UNUSED_PARAM(map_entries_cnt_p);
    return SX_STATUS_UNSUPPORTED;
}

/**
 * This API is used to manage decap table rules.
 * The decap table is used to terminate encapsulated packets.
 *
 * The key provides packet matching mechanism.
 * so each key is mapped to one tunnel.
 *
 * Supported devices: Spectrum.
 *
 * @param[in] handle        - SX-API handle
 * @param[in] cmd           - CREATE / DESTROY / EDIT
 * @param[in] decap_key_p   - decap key
 * @param[in] decap_data_p  - decap data
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_UNSUPPORTED if api is not supported for this device.
 * @return SX_STATUS_ENTRY_NOT_FOUND if tunnel doesn't exists.
 * @return SX_STATUS_RESOURCE_IN_USE if key already used for another tunnel.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_tunnel_decap_rules_set(const sx_api_handle_t               handle,
                                          const sx_access_cmd_t               cmd,
                                          const sx_tunnel_decap_entry_key_t  *decap_key_p,
                                          const sx_tunnel_decap_entry_data_t *decap_data_p);

/**
 * This API is used to get decap rules from decap table.
 *
 * Supported devices: Spectrum.
 *
 * @param[in]  handle         - SX-API handle
 * @param[in]  decap_key_p    - Key to query.
 * @param[out] decap_data_p   - Data assoicated with key.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_UNSUPPORTED if api is not supported for this device
 * @return SX_STATUS_ENTRY_NOT_FOUND if key doesn't exists.
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_tunnel_decap_rules_get(const sx_api_handle_t              handle,
                                          const sx_tunnel_decap_entry_key_t *decap_key_p,
                                          sx_tunnel_decap_entry_data_t      *decap_data_p);

/**
 * This API is used to init tunneling module.
 * Supported devices: Spectrum.
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
 * Supported devices: Spectrum.
 *
 * @param[in] handle   - SX-API handle
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_tunnel_deinit_set(const sx_api_handle_t handle);

#endif /* __SX_API_TUNNEL_H__ */
