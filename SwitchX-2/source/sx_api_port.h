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

#ifndef __SX_API_PORT_H__
#define __SX_API_PORT_H__

#include <sx/sdk/sx_api.h>


/************************************************
 *  API functions
 ***********************************************/

/**
 * This API sets the log verbosity level of PORT MODULE.
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] verbosity_target         - set verbosity of : API / MODULE / BOTH
 * @param[in] module_verbosity_level   - PORT module verbosity level
 * @param[in] api_verbosity_level      - PORT API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_port_log_verbosity_level_set(const sx_api_handle_t           handle,
                                                const sx_log_verbosity_target_t verbosity_target,
                                                const sx_verbosity_level_t      module_verbosity_level,
                                                const sx_verbosity_level_t      api_verbosity_level);

/**
 * This API gets the log verbosity level of PORT MODULE.
 *
 * @param[in]  handle                   - SX-API handle
 * @param[in]  verbosity_target         - get verbosity of : API / MODULE / BOTH
 * @param[out] module_verbosity_level_p - PORT module verbosity level
 * @param[out] api_verbosity_level_p    - PORT API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_port_log_verbosity_level_get(const sx_api_handle_t           handle,
                                                const sx_log_verbosity_target_t verbosity_target,
                                                sx_verbosity_level_t           *module_verbosity_level_p,
                                                sx_verbosity_level_t           *api_verbosity_level_p);

/**
 *  This API adds/deletes a device to/from the SDK.
 *  A device may have a different port width when using a single/double/quad lanes to provide 10/20/40GE.
 *  The mapping is done between the local port identifier and the module (cage) identifier that hosts this port.
 *  The SDK maps the device's local ports to (unique) logical ports that represent the SDK's ports.
 *
 * @param[in] handle                     - SX-API handle
 * @param[in] cmd                        - ADD/DELETE
 * @param[in] device_id                  - device ID
 * @param[in] base_mac_addr_p            - device base MAC address pointer
 * @param[in,out] port_attributes_list_p - IN: port_mode, port_mapping
 *                                         OUT: log_port
 * @param[in] port_cnt                   - port attributes lists length
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameter exceed its range
 * @return SX_STATUS_CMD_UNSUPPORTED if command is not supported
 *
 */
sx_status_t sx_api_port_device_set(const sx_api_handle_t handle,
                                   const sx_access_cmd_t cmd,
                                   const sx_device_id_t  device_id,
                                   const sx_mac_addr_t  *base_mac_addr_p,
                                   sx_port_attributes_t *port_attributes_list_p,
                                   const uint32_t        port_cnt);

/**
 *  This API retrieves a device information (port lists) from the SDK.
 *  If all optional output buffers are NULL, this API retrieves the number of ports.
 *
 * @param[in] handle                  - SX-API handle
 * @param[in] device_id               - device ID
 * @param[in] swid                    - switch ID (use SX_SWID_ID_DONTCARE to get all ports)
 * @param[out] port_attributes_list_p - port attributes list
 * @param[in,out] port_cnt_p          - IN: port attributes list length
 *                                      OUT:port attributes number
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameter exceed its range
 */
sx_status_t sx_api_port_device_get(const sx_api_handle_t handle,
                                   const sx_device_id_t  device_id,
                                   const sx_swid_t       swid,
                                   sx_port_attributes_t *port_attributes_list_p,
                                   uint32_t             *port_cnt_p);

/**
 *  This API sets a ports mapping.
 *
 * @param[in] handle                - SX-API handle
 * @param[in] log_port_list_p       - list of local ports
 * @param[in] port_mapping_list_p   - port mapping list
 * @param[in] port_cnt              - number of ports
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameter exceed its range
 */
sx_status_t sx_api_port_mapping_set(const sx_api_handle_t    handle,
                                    const sx_port_log_id_t  *log_port_list_p,
                                    const sx_port_mapping_t *port_mapping_list_p,
                                    const uint32_t           port_cnt);

/**
 *  This API retrieves logical port ID mapping from the SDK.
 *
 * @param[in] handle                - SX-API handle
 * @param[in] log_port_list_p       - list of local ports
 * @param[out] port_mapping_list_p  - port mapping list
 * @param[in] port_cnt              - number of ports
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameter exceed its range
 */
sx_status_t sx_api_port_mapping_get(const sx_api_handle_t   handle,
                                    const sx_port_log_id_t *log_port_list_p,
                                    sx_port_mapping_t      *port_mapping_list_p,
                                    const uint32_t          port_cnt);


/**
 *  This API retrieves the devices info list from the SDK.
 *  If optional output buffer is NULL, this API  retrieves the number of devices.
 *
 * @param[in] handle                - SX-API handle
 * @param[out] device_info_list_p   - list of device info entries
 * @param[in,out] device_info_cnt_p - In/Out: Input/output list length
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameter exceed its range
 */
sx_status_t sx_api_port_device_list_get(const sx_api_handle_t handle,
                                        sx_device_info_t     *device_info_list_p,
                                        uint32_t             *device_info_cnt_p);

/**
 *  This API adds/deletes a SWID to/from the SDK.
 *  A SWID which has bound ports cannot be deleted.
 *
 * @param[in] handle  - SX-API handle
 * @param[in] cmd     - ADD/DELETE
 * @param[in] swid    - switch ID
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if SWID exceeds its range or is undefined in profile
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_CMD_UNSUPPORTED if command is not supported
 */
sx_status_t sx_api_port_swid_set(const sx_api_handle_t handle,
                                 const sx_access_cmd_t cmd,
                                 const sx_swid_t       swid);

/**
 *  This API retrieves all SWIDs lists from the SDK.
 *  If optional output buffer is NULL, this API retrieves the number of SWIDs.
 *
 * @param[in] handle         - SX-API handle
 * @param[out] swid_list_p   - array of SWIDs
 * @param[in,out] swid_cnt_p - In: Array's length
 *                             Out: Number of SWIDs
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE: SwIDs list length is 0 (zero)
 */
sx_status_t sx_api_port_swid_list_get(const sx_api_handle_t handle,
                                      sx_swid_t            *swid_list_p,
                                      uint32_t             *swid_cnt_p);

/**
 *  This API binds/unbinds a logical port to/from a SWID in the SDK.
 *  To unbind a port from a SWID, the SWID field should be SX_SWID_ID_DISABLED.
 *
 * @param[in] handle   - SX-API handle
 * @param[in] log_port - logical port ID
 * @param[in] swid     - new switch partition ID
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if SWID is out of range
 */
sx_status_t sx_api_port_swid_bind_set(const sx_api_handle_t  handle,
                                      const sx_port_log_id_t log_port,
                                      const sx_swid_t        swid);

/**
 *  This API retrieves a logical port's binded SWID.
 *
 * @param[in] handle     - SX-API handle
 * @param[in] log_port   - logical port ID
 * @param[out] swid_p    - the port's swid
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if SWID is out of range
 */
sx_status_t sx_api_port_swid_bind_get(const sx_api_handle_t  handle,
                                      const sx_port_log_id_t log_port,
                                      sx_swid_t             *swid_p);

/**
 *  This API retrieves the SwID's ports list.
 *  If optional output buffer is NULL - this API simply retrieves the number of Ports.
 *
 * @param[in] handle         - SX-API handle
 * @param[in] swid           - switch ID
 * @param[out] log_port_list - array of device's logical port IDs range
 * @param[in,out] port_cnt_p - In: Array's length
 *                             Out: Number of Ports in array
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if SWID is out of range
 */
sx_status_t sx_api_port_swid_port_list_get(const sx_api_handle_t handle,
                                           const sx_swid_t       swid,
                                           sx_port_log_id_t     *log_port_list_p,
                                           uint32_t             *port_cnt_p);

/**
 *  This API sets the port's stacking mode in the SDK.
 *
 * @param[in] handle   - SX-API handle
 * @param[in] log_port - logical port ID
 * @param[in] mode     - new port mode
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 */
sx_status_t sx_api_port_mode_set(const sx_api_handle_t  handle,
                                 const sx_port_log_id_t log_port,
                                 const sx_port_mode_t   mode);

/**
 *  This API retrieves the port's mode from the SDK.
 *
 * @param[in] handle   - SX-API handle
 * @param[in] log_port - logical port ID
 * @param[out] mode_p  - current port mode
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 */
sx_status_t sx_api_port_mode_get(const sx_api_handle_t  handle,
                                 const sx_port_log_id_t log_port,
                                 sx_port_mode_t        *mode_p);


/**
 *  This API sets the port MTU size in the SDK.
 *
 * @param[in] handle   - SX-API handle
 * @param[in] log_port - logical Port ID
 * @param[in] mtu_size - new MTU payload size. SDK adds L2 header size bytes to this value.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 */
sx_status_t sx_api_port_mtu_set(const sx_api_handle_t  handle,
                                const sx_port_log_id_t log_port,
                                const sx_port_mtu_t    mtu_size);


/**
 *  This API retrieves the port MTU size from the SDK.
 *  Note: for Ethernet, maximum MTU and operational MTU are the same.
 *
 * @param[in] handle           - SX-API handle
 * @param[in] log_port         - logical port ID
 * @param[out] max_mtu_size_p  - maximum MTU supported on this port (payload size)
 * @param[out] oper_mtu_size_p - operational MTU configured on this port (payload size)
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 */
sx_status_t sx_api_port_mtu_get(const sx_api_handle_t  handle,
                                const sx_port_log_id_t log_port,
                                sx_port_mtu_t         *max_mtu_size_p,
                                sx_port_mtu_t         *oper_mtu_size_p);

/**
 *  This API sets the port type & speed.
 *  It enables the application to set the port enabled mode(s).
 *  When the link is up, the current active protocol is retrieved (after SET).
 *  When the link is down, the supported protocols are retrieved (after SET).
 *
 * @param[in] handle        - SX-API handle
 * @param[in] log_port      - logical port ID
 * @param[in] admin_speed_p - new types and speeds (protocols) enabled
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 */
sx_status_t sx_api_port_speed_admin_set(const sx_api_handle_t             handle,
                                        const sx_port_log_id_t            log_port,
                                        const sx_port_speed_capability_t *admin_speed_p);

/**
 * This API retrieves the port's admin and operational speed from the SDK.
 *
 * @param[in] handle         - SX-API handle
 * @param[in] log_port       - logical port ID
 * @param[out] admin_speed_p - port administrative speed
 * @param[out] oper_speed_p  - Port Operational speed
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 */
sx_status_t sx_api_port_speed_get(const sx_api_handle_t       handle,
                                  const sx_port_log_id_t      log_port,
                                  sx_port_speed_capability_t *admin_speed_p,
                                  sx_port_oper_speed_t       *oper_speed_p);

/**
 * This API retrieves the port's supported capabilities from the SDK.
 *
 * @param[in] handle        - SX-API handle
 * @param[in] log_port      - logical port ID
 * @param[out] capability_p - port capabilities
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 */
sx_status_t sx_api_port_capability_get(const sx_api_handle_t  handle,
                                       const sx_port_log_id_t log_port,
                                       sx_port_capability_t  *capability_p);


/**
 *  This API Retrieves the port's physical address (MAC) from the SDK.
 *
 * @param[in] handle           - SX-API handle
 * @param[in] log_port         - logical lort ID
 * @param[out] port_mac_addr_p - current base MAC address
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 */
sx_status_t sx_api_port_phys_addr_get(const sx_api_handle_t  handle,
                                      const sx_port_log_id_t log_port,
                                      sx_mac_addr_t         *port_mac_addr_p);

/**
 *  This API sets the port's physical loopback.
 *  LAG port or LAG-member port cannot be loopback.
 *
 * @param[in] handle          - SX-API handle
 * @param[in] log_port        - logical port ID
 * @param[in] phys_loopback   - new physical loopback
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameter exceeds its range
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 */
sx_status_t sx_api_port_phys_loopback_set(const sx_api_handle_t         handle,
                                          const sx_port_log_id_t        log_port,
                                          const sx_port_phys_loopback_t phys_loopback);

/**
 *  This API retrieves the port's physical loopback.
 *  LAG port or LAG member port cannot be loopback.
 *
 * @param[in] handle           - SX-API handle
 * @param[in] log_port         - logical port ID
 * @param[out] phys_loopback_p - current physical loopback
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameter exceeds its range
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 */
sx_status_t sx_api_port_phys_loopback_get(const sx_api_handle_t    handle,
                                          const sx_port_log_id_t   log_port,
                                          sx_port_phys_loopback_t *phys_loopback_p);


/**
 *  This API sets the port administrative state in the SDK.
 *
 * @param[in] handle      - SX-API handle
 * @param[in] log_port    - logical port ID
 * @param[in] admin_state - new administrative status
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_COMM_ERROR if client communication fails
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 */
sx_status_t sx_api_port_state_set(const sx_api_handle_t       handle,
                                  const sx_port_log_id_t      log_port,
                                  const sx_port_admin_state_t admin_state);

/**
 *  This API retrieves the port's administrative, operational & module state from the SDK.
 *
 * @param[in] handle          - SX-API handle
 * @param[in] log_port        - logical port ID
 * @param[out] oper_state_p   - port operational state
 * @param[out] admin_state_p  - port administrative state
 * @param[out] module_state_p - module operational state
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_COMM_ERROR if client communication fails
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 */
sx_status_t sx_api_port_state_get(const sx_api_handle_t   handle,
                                  const sx_port_log_id_t  log_port,
                                  sx_port_oper_state_t   *oper_state_p,
                                  sx_port_admin_state_t  *admin_state_p,
                                  sx_port_module_state_t *module_state_p);

/**
 *  This API sets the port flow control pause configuration.
 *  ENUM sets the mode of both RX & TX with one of 4 possible EN/DIS combinations.
 *
 *  NOTE: When changing the port flow control configuration between the following states
 *  GLOBAL ON/GLOBAL OFF/PFC} the port administrative and operation state must be down.
 ******************************************************************************
 *
 * @param[in] handle   - SX-API handle
 * @param[in] log_port - logical port ID (whose flow control configuration to set)
 * @param[in] fc_mode  - ENUM which represents the Tx/Rx flow control state
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_COMM_ERROR if client communication fails
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 */
sx_status_t sx_api_port_global_fc_enable_set(const sx_api_handle_t          handle,
                                             const sx_port_log_id_t         log_port,
                                             const sx_port_flow_ctrl_mode_t fc_mode);

/**
 *  This API retrieves the port flow control pause configuration from the SDK.
 *  ENUM gets the mode of both RX & TX with one of 4 possible EN/DIS combinations.
 *
 * @param[in] handle     - SX-API handle
 * @param[in] log_port   - logical port ID (whose flow control configuration to retrieve)
 * @param[out] fc_mode_p - ENUM which represents the Tx/Rx flow control state
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_COMM_ERROR if client communication fails
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 */
sx_status_t sx_api_port_global_fc_enable_get(const sx_api_handle_t     handle,
                                             const sx_port_log_id_t    log_port,
                                             sx_port_flow_ctrl_mode_t *fc_mode_p);

/**
 *  This API sets the port priority flow control (PFC) configuration.
 *  ENUM sets the mode of both RX & TX with one of 4 possible EN/DIS combinations.
 *
 *  NOTE: When changing the port flow control configuration between the following states
 *  {GLOBAL ON/GLOBAL OFF/PFC} the port administrative and operation state must be down.
 ******************************************************************************
 *
 * @param[in] handle   - SX-API handle
 * @param[in] log_port - port ID
 * @param[in] pfc_prio - PFC priority
 * @param[in] fc_mode  - ENUM which represents Tx/Rx flow control states
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameters exceeds its range
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_COMM_ERROR if client communication fails
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 */
sx_status_t sx_api_port_pfc_enable_set(const sx_api_handle_t          handle,
                                       const sx_port_log_id_t         log_port,
                                       const sx_port_flow_ctrl_prio_t pfc_prio,
                                       const sx_port_flow_ctrl_mode_t fc_mode);

/**
 *  This API retrieves the port priority flow control (PFC) configuration the SDK.
 *  ENUM gets the mode of both RX & TX with one of 4 possible EN/DIS combinations.
 *
 * @param[in] handle     - SX-API handle
 * @param[in] log_port   - port ID
 * @param[in] pfc_prio   - PFC priority
 * @param[out] fc_mode_p - ENUM which represents Tx/Rx flow control state
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameters exceeds its range
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_COMM_ERROR if client communication fails
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 */
sx_status_t sx_api_port_pfc_enable_get(const sx_api_handle_t          handle,
                                       const sx_port_log_id_t         log_port,
                                       const sx_port_flow_ctrl_prio_t pfc_prio,
                                       sx_port_flow_ctrl_mode_t      *fc_mode_p);

/**
 *  This API retrieves the port IEEE 802.3 counters from the SDK.
 *
 * @param[in] handle                 - SX-API handle
 * @param[in] cmd                    - SX_ACCESS_CMD_READ | SX_ACCESS_CMD_READ_CLEAR
 * @param[in] log_port               - logical port ID
 * @param[out] cntr_ieee_802_dot_3_p - IEEE 802.3 counters entry
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_COMM_ERROR if client communication fails
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 */
sx_status_t sx_api_port_counter_ieee_802_dot_3_get(const sx_api_handle_t          handle,
                                                   const sx_access_cmd_t          cmd,
                                                   const sx_port_log_id_t         log_port,
                                                   sx_port_cntr_ieee_802_dot_3_t *cntr_ieee_802_dot_3_p);

/**
 *  This API retrieves the port RFC 2863 counters from the SDK.
 *
 * @param[in] handle           - SX-API handle
 * @param[in] cmd              - SX_ACCESS_CMD_READ | SX_ACCESS_CMD_READ_CLEAR
 * @param[in] log_port         - logical port ID
 * @param[out] cntr_rfc_2863_p - RFC 2863 counters entry
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_COMM_ERROR if client communication fails
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 */
sx_status_t sx_api_port_counter_rfc_2863_get(const sx_api_handle_t    handle,
                                             const sx_access_cmd_t    cmd,
                                             const sx_port_log_id_t   log_port,
                                             sx_port_cntr_rfc_2863_t *cntr_rfc_2863_p);

/**
 *  This API retrieves the port RFC 2819 counters from the SDK.
 *
 * @param[in] handle           - SX-API handle
 * @param[in] cmd              - SX_ACCESS_CMD_READ | SX_ACCESS_CMD_READ_CLEAR
 * @param[in] log_port         - logical port ID
 * @param[out] cntr_rfc_2819_p - RFC 2819 counters entry
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_COMM_ERROR if client communication fails
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 */
sx_status_t sx_api_port_counter_rfc_2819_get(const sx_api_handle_t    handle,
                                             const sx_access_cmd_t    cmd,
                                             const sx_port_log_id_t   log_port,
                                             sx_port_cntr_rfc_2819_t *cntr_rfc_2819_p);

/**
 *  This API retrieves the port RFC 3635 counters from the SDK.
 *
 * @param[in] handle           - SX-API handle
 * @param[in] cmd              - SX_ACCESS_CMD_READ | SX_ACCESS_CMD_READ_CLEAR
 * @param[in] log_port         - logical port ID
 * @param[out] cntr_rfc_3635_p - RFC 3635 counters entry
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_COMM_ERROR if client communication fails
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 */
sx_status_t sx_api_port_counter_rfc_3635_get(const sx_api_handle_t    handle,
                                             const sx_access_cmd_t    cmd,
                                             const sx_port_log_id_t   log_port,
                                             sx_port_cntr_rfc_3635_t *cntr_rfc_3635_p);

/**
 *  This API retrieves the port CLI counters from the SDK.
 *
 * @param[in] handle      - SX-API handle
 * @param[in] cmd         - SX_ACCESS_CMD_READ | SX_ACCESS_CMD_READ_CLEAR
 * @param[in] log_port    - logical port ID
 * @param[out] cntr_cli_p - CLI counters entry
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_COMM_ERROR if client communication fails
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 */
sx_status_t sx_api_port_counter_cli_get(const sx_api_handle_t  handle,
                                        const sx_access_cmd_t  cmd,
                                        const sx_port_log_id_t log_port,
                                        sx_port_cntr_cli_t    *cntr_cli_p);

/**
 *  This API retrieves the port priority counters from the SDK.
 *  When a LAG port is given, the result is the sum of all the
 *  LAG ports counters.
 *
 * @param[in] handle       - SX-API handle
 * @param[in] cmd          - SX_ACCESS_CMD_READ | SX_ACCESS_CMD_READ_CLEAR
 * @param[in] log_port     - logical port ID
 * @param[in] prio_id      - priority ID
 * @param[out] cntr_prio_p - priority counters entry
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameters exceeds its range
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_COMM_ERROR if client communication fails
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 */
sx_status_t sx_api_port_counter_prio_get(const sx_api_handle_t   handle,
                                         const sx_access_cmd_t   cmd,
                                         const sx_port_log_id_t  log_port,
                                         const sx_port_prio_id_t prio_id,
                                         sx_port_cntr_prio_t    *cntr_prio_p);

/**
 *  This API retrieves the port's traffic class counters.
 *  Note: The API does not support LAG.
 *
 * @param[in] handle        - SX-API handle
 * @param[in] cmd           - READ
 * @param[in] log_port      - logical port ID
 * @param[in] tc_id         - traffic class ID
 * @param[out] cntr_tc_p    - per port per TC counters
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_port_counter_tc_get(const sx_api_handle_t   handle,
                                       const sx_access_cmd_t   cmd,
                                       const sx_port_log_id_t  log_port,
                                       const sx_port_tc_id_t   tc_id,
                                       sx_port_traffic_cntr_t *cntr_tc_p);


/**
 *  This API Retrieves the performance port counters from the SDK.
 *  Note: This API does not support LAG.
 *
 * @param[in] handle       - SX-API handle
 * @param[in] cmd          - SX_ACCESS_CMD_READ | SX_ACCESS_CMD_READ_CLEAR
 * @param[in] log_port     - logical port ID
 * @param[in] prio_id      - counters priority ID
 * @param[out] cntr_perf_p - performance counters entry
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameters exceeds its range
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_COMM_ERROR if client communication fails
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 */
sx_status_t sx_api_port_counter_perf_get(const sx_api_handle_t   handle,
                                         const sx_access_cmd_t   cmd,
                                         const sx_port_log_id_t  log_port,
                                         const sx_port_prio_id_t prio_id,
                                         sx_port_cntr_perf_t    *cntr_perf_p);

/**
 *  This API Retrieves the port discard counters from the SDK.
 *  The user has the following options:
 *
 *   1. Read the discard counters (set the cmd to SX_ACCESS_CMD_READ)
 *   2. Read and clear the discard counters (set the cmd to SX_ACCESS_CMD_READ_CLEAR)
 *
 * @param[in] handle          - SX-API handle
 * @param[in] cmd             - SX_ACCESS_CMD_READ | SX_ACCESS_CMD_READ_CLEAR
 * @param[in] log_port        - logical port ID
 * @param[out] cntr_discard_p - discard counters entry
 *
 * @return sx_status_t :
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_COMM_ERROR if client communication fails
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 * @return SX_STATUS_PARAM_ERROR if a parameter is NULL or not supported
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in the DB
 */
sx_status_t sx_api_port_counter_discard_get(const sx_api_handle_t   handle,
                                            const sx_access_cmd_t   cmd,
                                            const sx_port_log_id_t  log_port,
                                            sx_port_cntr_discard_t *cntr_discard_p);

/**
 *  This API clears port counters.
 *  The user has the following options:
 *
 *   1. Clear a specific port (set log_port field with the log port ID && all_ports = FALSE):
 *      option a. clear specific counter group (set the group in cntr_grp)
 *      option b. clear all counter groups (set cntr_grp = SX_PORT_CNTR_GRP_ALL)
 *
 *   2. Clear all ports (set all_ports = TRUE):
 *      option a. clear specific counter group (set the group in cntr_grp)
 *      option b. clear all counter groups (set cntr_grp = SX_PORT_CNTR_GRP_ALL)
 *
 * @param[in] handle         - SX-API handle
 * @param[in] log_port       - logical port ID.
 * @param[in] all_ports      - clear all ports counters
 * @param[in] cntr_grp       - performance counter group
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_COMM_ERROR if client communication fails
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 */
sx_status_t sx_api_port_counter_clear_set(const sx_api_handle_t    handle,
                                          const sx_port_log_id_t   log_port,
                                          const boolean_t          all_ports,
                                          const sx_port_cntr_grp_t cntr_grp);

/**
 *  This API initializes the port in the SDK.
 *
 * @param[in] handle   - SX-API handle
 * @param[in] log_port - logical port ID
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_COMM_ERROR if client communication fails
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 */
sx_status_t sx_api_port_init_set(const sx_api_handle_t  handle,
                                 const sx_port_log_id_t log_port);

/**
 *  This API de-initializes the port in the SDK.
 *
 * @param[in] handle   - SX-API handle
 * @param[in] log_port - logical port ID
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO if message size is zero
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT if message size exceeds limit
 * @return SX_STATUS_COMM_ERROR if client communication fails
 * @return SX_STATUS_INVALID_HANDLE if a NULL handle is received
 */
sx_status_t sx_api_port_deinit_set(const sx_api_handle_t  handle,
                                   const sx_port_log_id_t log_port);

/**
 *  This API sets storm control parameters of a port.
 *
 * @param[in] handle                 - SX-API handle
 * @param[in] cmd                    - SX_ACCESS_CMD_ADD, SX_ACCESS_CMD_EDIT, SX_ACCESS_CMD_DELETE
 * @param[in] log_port               - logical port ID
 * @param[in] storm_control_id       - Storm Control ID
 * @param[in] storm_control_param_p  - Storm Control parameters
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameters exceeds its range
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO if HW fails
 * @return SX_STATUS_CMD_UNSUPPORTED if command is not supported
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 */
sx_status_t sx_api_port_storm_control_set(const sx_api_handle_t                 handle,
                                          const sx_access_cmd_t                 cmd,
                                          const sx_port_log_id_t                log_port,
                                          const sx_port_storm_control_id_t      storm_control_id,
                                          const sx_port_storm_control_params_t *storm_control_params_p);

/**
 *  This API retrieves storm control parameters of a port.
 *
 * @param[in] handle                  - SX-API handle
 * @param[in] log_port                - logical port ID
 * @param[in] storm_control_id        - Storm Control ID
 * @param[out] storm_control_param_p  - Storm Control parameters
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameters exceeds its range
 * @return SX_STATUS_CMD_UNSUPPORTED if command is not supported
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 */
sx_status_t sx_api_port_storm_control_get(const sx_api_handle_t            handle,
                                          const sx_port_log_id_t           log_port,
                                          const sx_port_storm_control_id_t storm_control_id,
                                          sx_port_storm_control_params_t  *storm_control_params_p);

/**
 *  This API controls sFlow configuration. Using the access command
 *  ADD, an sFlow sampling is defined on port. Then after it is
 *  set, the user may EDIT the sFlow parameters of a configured
 *  port. To remove sFlow sampling from the port use access command
 *  DELETE.
 *  The API returns the sFlow params configured in practice. Deviation is returned in percentage.
 *  It is highly recommended to always check the deviation value returned.
 *
 * @param[in] handle              - SX-API handle
 * @param[in] cmd                 - access command (ADD/DELETE/EDIT)
 * @param[in] log_port            - logical port ID
 * @param[in, out] sflow_params_p - sFlow related configuration params (Deviation>0); ignored when CMD=DESTROY
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_NO_RESOURCES if there are not enough resources for sFlow policer
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameters exceeds its range
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_CMD_UNSUPPORTED if command is not supported
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_port_sflow_set(const sx_api_handle_t   handle,
                                  const sx_access_cmd_t   cmd,
                                  const sx_port_log_id_t  log_port,
                                  sx_port_sflow_params_t *sflow_params_p);


/**
 *  This API gets the ports sFlow state.
 *
 * @param[in] handle          - SX-API handle
 * @param[in] log_port        - logical port ID
 * @param[out] sflow_params_p - sFlow related configuration parameters
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameters exceeds its range
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_port_sflow_get(const sx_api_handle_t   handle,
                                  const sx_port_log_id_t  log_port,
                                  sx_port_sflow_params_t *sflow_params_p);

/**
 *  This API controls loopback filter state of the port.
 *
 * @param[in] handle   - SX-API handle
 * @param[in] log_port - logical port ID
 * @param[in] lbf_mode - loopback filter mode
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_port_loopback_filter_set(const sx_api_handle_t                handle,
                                            const sx_port_log_id_t               log_port,
                                            const sx_port_loopback_filter_mode_t lbf_mode);

/**
 *  This API retrieves the loopback filter state of the port.
 *
 * @param[in] handle    - SX-API handle
 * @param[in] log_port  - logical port ID
 * @param[out] lbf_mode_p - loopback filter mode
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_port_loopback_filter_get(const sx_api_handle_t           handle,
                                            const sx_port_log_id_t          log_port,
                                            sx_port_loopback_filter_mode_t *lbf_mode_p);

/**
 *  This function sets the isolation group of the port (a list of ports from which
 *  traffic should not be transmitted to log_port).
 *  Isolation is supported only between ports on the same device, and on the same SWID.
 *   Set - add ports to isolation group (overwrites previous configuration)
 *   Add - add ports to isolation group (additionally to previous configuration)
 *   Delete - remove ports from isolation group
 *   Delete All - empty isolation group
 *
 * @param[in] handle            - SX-API handle
 * @param[in] cmd               - SET/ADD/DELETE/DELETE_ALL
 * @param[in] log_port          - logical port ID
 * @param[in] log_port_list_p   - list of logical ports
 * @param[in] log_port_cnt      - number of logical ports in the list
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in the DB
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameters exceeds its range
 */
sx_status_t sx_api_port_isolate_set(const sx_api_handle_t   handle,
                                    const sx_access_cmd_t   cmd,
                                    const sx_port_log_id_t  log_port,
                                    const sx_port_log_id_t *log_port_list_p,
                                    const uint32_t          log_port_cnt);

/**
 *  This function retrieves the isolation group of the port (a list of ports from which
 *  traffic should not be transmitted to log_port).
 *  Use log_port_cnt_p=0 to retrieve only the size of isolation group.
 *
 * @param[in] handle              - SX-API handle
 * @param[in] log_port            - logical port ID
 * @param[in,out] log_port_list_p - list of logical ports
 * @param[in,out] log_port_cnt_p  - In: Number of logical ports in list
 *                                  Out: Number of logical ports in LAG
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if a parameter is NULL
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in the DB
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameters exceeds its range
 */
sx_status_t sx_api_port_isolate_get(const sx_api_handle_t  handle,
                                    const sx_port_log_id_t log_port,
                                    sx_port_log_id_t      *log_port_list_p,
                                    uint32_t              *log_port_cnt_p);

/**
 *  This API returns the SWID type as it was configured in the
 *  profile, at SDK init time.
 *
 * @param[in] handle    - SX-API handle
 * @param swid          - switch partition ID
 * @param swid_type_p   - DISABLED/ETHERNET/INFINIBAND
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if a parameters exceeds its range
 */
sx_status_t sx_api_port_swid_type_get(const sx_api_handle_t handle,
                                      const sx_swid_t       swid,
                                      sx_swid_type_t       *swid_type_p);

#endif /* __SX_API_PORT_H__ */
