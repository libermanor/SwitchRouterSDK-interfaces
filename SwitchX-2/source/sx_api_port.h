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

#ifndef __SX_API_PORT_H__
#define __SX_API_PORT_H__

#include <sx/sdk/sx_api.h>


/************************************************
 *  API functions
 ***********************************************/

/**
 * This function sets the log verbosity level of PORT MODULE
 * @param[in]     handle                   - SX-API handle
 * @param[in]     cmd                      - SET / GET
 * @param[in]     verbosity_target         - set get verbosity of : API / MODULE / BOTH
 * @param[in,out] module_verbosity_level_p - PORT module verbosity level
 * @param[in,out] api_verbosity_level_p    - PORT API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_port_log_verbosity_level_set(
                                               const sx_api_handle_t            handle ,
                                               const sx_access_cmd_t            cmd ,
                                               const sx_log_verbosity_target_t  verbosity_target,
                                               sx_verbosity_level_t      *module_verbosity_level_p,
                                               sx_verbosity_level_t      *api_verbosity_level_p);

/**
 * 	This API Adds/Deletes a device to/from the SDK.
 *  A device may have different port width when using a single/double/quad lanes to provide 10/20/40GE.
 *  The mapping is done between the Local Port identifier & the module (cage) identifier that hosts this port.
 *  The SDK maps the device's Local Ports to (unique) logical ports that represents SDK's ports.
 *
 ************************************************************************************************************
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - ADD/DELETE.
 * @param[in] config_hw - Configure HW Flag (for native "Ethernet only" system).!!! not supported yet - always set to 0 !!!.
 * @param[in] device_id - Device ID.
 * @param[in] base_mac_addr_p - Device base MAC address pointer.
 * @param[in] port_mode_list_p - Ports Mode list.
 * @param[in] port_mapping_list_p - Ports Mapping list.
 * @param[out] log_port_list_p - Logical Port ID list.
 * @param[in] port_cnt - Lists' length.
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL: Pointer is NULL.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE: Parameters exceeds range.
 * @return SX_STATUS_CMD_UNSUPPORTED: Access Command isn't supported.
 *
 */
sx_status_t sx_api_port_device_set(
                                  const sx_api_handle_t       handle,
                                  const sx_access_cmd_t       cmd,
                                  const uint8_t               config_hw,
                                  const sx_device_id_t        device_id,
                                  const sx_mac_addr_t *       base_mac_addr_p,
                                  const sx_port_mode_t *      port_mode_list_p,
                                  const sx_port_mapping_t *   port_mapping_list_p,
                                  sx_port_log_id_t *    log_port_list_p,
                                  const length_t              port_cnt);

/** 
 ******  *  This API Retrieves a device information (port lists) from the SDK.
 *  If all optional output buffers are NULL - this API simply retrieves the number of ports.
 ************************************************************************************************************
 *
 * @param[in] handle - SX-API handle
 * @param[in] device_id - Device ID
 * @param[in] swid_id - SwID ID (use SX_SWID_ID_DONTCARE to get all ports)
 * @param[out] port_mode_list - Ports Mode list.
 * @param[out] port_mapping_list  - Ports Mapping list.
 * @param[out] log_port_list      - Logical Port ID list.
 **@param[in,out] port_cnt_p - IN: Ports Lists' length.****** 
 ********OUT:****** Ports Number. 
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL: Pointer is NULL.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE: Parameters exceeds range.
 */
sx_status_t sx_api_port_device_get(
                                  const sx_api_handle_t       handle,
                                  const sx_device_id_t        device_id,
                                  const sx_swid_id_t          swid_id,
                                  sx_port_mode_t *      port_mode_list_p,
                                  sx_port_mapping_t *   port_mapping_list_p,
                                  sx_port_log_id_t *    log_port_list_p,
                                  length_t*             port_cnt_p);

/**
 *  	This API sets a ports Mapping .
************************************************************************
 *
 * @param[in] handle - SX-API handle.
 * @param[in] log_port_list - List of local ports.
 * @param[in] port_mapping_list - Port Mapping list.
 * @param[in] port_cnt - Number of ports.
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL: Pointer is NULL.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE: Parameters exceeds range.
 */

sx_status_t
sx_api_port_mapping_set(
                       const sx_api_handle_t       handle,
                       sx_port_log_id_t     *log_port_list_p,
                       const sx_port_mapping_t    *port_mapping_list_p,
                       const length_t              port_cnt
                       );

/**
 *  	This API Retrieves a Logical Port ID Mapping from the SDK.
************************************************************************
 *
 * @param[in] handle - SX-API handle.
 * @param[in] log_port_list_p - List of local ports.
 * @param[out] port_mapping_list_p - Port Mapping list.
 * @param[in] port_cnt - Number of ports.
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL: Pointer is NULL.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE: Parameters exceeds range.
 */
sx_status_t
sx_api_port_mapping_get(
                       const sx_api_handle_t       handle,
                       sx_port_log_id_t           *log_port_list_p,
                       sx_port_mapping_t          *port_mapping_list_p,
                       const length_t              port_cnt
                       );


/**
 *  	This API Retrieves the Devices info list from the SDK.
 *  If optional output buffer is NULL - this API simply retrieves the number of devices.
 ******************************************************************************
 *
 * @param[in] handle - SX-API handle
 * @param[out] device_info_list - List of Device Info entries.
 **@param[in,out] device_info_cnt_p - In/Out: Input/Output***** 
 ******* List***** length.
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL: Pointer is NULL.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE: Parameters exceeds range.
 */
sx_status_t
sx_api_port_device_list_get(
                           const sx_api_handle_t       handle,
                           sx_device_info_t      *device_info_list_p,
                           length_t              *device_info_cnt_p
                           );

/**
 *  This API retrieves the Port lib init Params from the SDK.
 ******************************************************************************
 *
 * @param[in] handle - SX-API handle
 * @param[out] pth_bits_num_p - Number of Multipath bits in UC-Route
 * @param[out] sub_bits_num_p - Number of Sub (VEPA) bits in UC-Route
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR: Input parameters error.
 * @return SX_STATUS_MESSAGE_SIZE_ZERO: Message size error.
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT: Message size error.
 */
sx_status_t
sx_api_port_params_get(
                      const sx_api_handle_t       handle,
                      uint8_t               *pth_bits_num_p,
                      uint8_t               *sub_bits_num_p
                      );

/**
 *  	This API retrieves a UC-Route given a Logical Port ID from the SDK.
 ******************************************************************************
 *
 * @param[in] handle - SX-API handle
 * @param[in] log_port - Port Logical ID
 * @param[out] port_ucroute_id_p - Port UC-Route ID
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR: Input parameters error.
 * @return SX_STATUS_MESSAGE_SIZE_ZERO: Message size error.
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT: Message size error.
 */
sx_status_t
sx_api_port_base_ucroute_get(
                            const sx_api_handle_t       handle,
                            const sx_port_log_id_t      log_port,
                            sx_port_ucroute_id_t  *ucroute_id_p
                            );

/**
 *  	This API retrieves a Logical Port ID given a UC-Route ID from the SDK.
 ******************************************************************************
 *
 * @param[in] handle - SX-API handle
 * @param[in] uc_route - UC-Route ID
 * @param[out] log_port_p - Logical Port ID
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR: Input parameters error.
 * @return SX_STATUS_MESSAGE_SIZE_ZERO: Message size error.
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT: Message size error.
 */
sx_status_t
sx_api_port_logical_get(
                       const sx_api_handle_t       handle,
                       const sx_port_ucroute_id_t  uc_route,
                       sx_port_log_id_t      *log_port_p
                       );


/**
 *  	This API Adds/Deletes a SwID to/from the SDK.
 *   A SwID which has binded ports, cannot be deleted.
 ******************************************************************************
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - ADD/DELETE
 * @param[in] swid_id - Switch ID
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR: Input parameters error.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE: swid exceeds range or****
 ******    undefined in profile
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT: Message size error.
 * @return SX_STATUS_CMD_UNSUPPORTED: Unsupported command.
 */
sx_status_t
sx_api_port_swid_set(
                    const sx_api_handle_t       handle,
                    const sx_access_cmd_t       cmd,
                    const sx_swid_t             swid_id
                    );

/**
 *  	This API retrieves all SwIDs list from the SDK.
 *  If optional output buffer is NULL - this API simply retrieves the number of SwIDs.
 ******************************************************************************
 *
 * @param[in] handle - SX-API handle
 * @param[out] swid_list - Array of SwIDs
 **@param[in,out] swid_cnt_p - In: Array's length. Out:***** 
 ******* Number***** of***** SwIDs
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR: Input parameters error.
 * @return SX_STATUS_MESSAGE_SIZE_ZERO: Message size error.
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT: Message size error.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE: SwIDs list length is 0 (zero).
 */
sx_status_t
sx_api_port_swid_list_get(
                         const sx_api_handle_t       handle,
                         sx_swid_id_t          *swid_list_p,
                         length_t              *swid_cnt_p
                         );

/**
 *  	This API retrieves the SwID's ports list.
 *  If optional output buffer is NULL - this API simply retrieves the number of Ports.
 ******************************************************************************
 *
 * @param[in] handle - SX-API handle
 * @param[in] swid_id - Switch ID
 * @param[out] log_port_list - Array of device's Logical Port IDs range
 **@param[in,out] port_cnt_p - In: Array's length. Out:**** 
 ******  Number**** of**** Ports in array
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR: Input parameters error.
 * @return SX_STATUS_MESSAGE_SIZE_ZERO: Message size error.
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT: Message size error.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE: SwIDs out of range.
 */
sx_status_t
sx_api_port_swid_port_list_get(
                              const sx_api_handle_t       handle,
                              const sx_swid_t             swid_id,
                              sx_port_log_id_t      *log_port_list_p,
                              length_t              *port_cnt_p
                              );

/**
 *  	This API Binds/UN-binds a logical port to / from a SWID in the SDK.
 ******************************************************************************
 *
 * In order to unbind a port from swid , the swid field should be SX_SWID_ID_DISABLED
 * @param[in] handle - SX-API handle
 * @param[in] log_port - Logical Port ID
 * @param[in] swid_id - New Switch Partition ID.
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO: Message size error.
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT: Message size error.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE: SwIDs out of range.
 */
sx_status_t
sx_api_port_swid_bind_set(
                         const sx_api_handle_t       handle,
                         const sx_port_log_id_t      log_port,
                         const sx_swid_id_t          swid_id
                         );

/**
 *  	This API Retrieves a Logical Port's binded SwID.
 ******************************************************************************
 *
 * @param[in] handle - SX-API handle
 * @param[in] log_port - Logical Port ID
 * @param[out] swid_id_p - the port's swid_id
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR: Input parameters error.
 * @return SX_STATUS_MESSAGE_SIZE_ZERO: Message size error.
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT: Message size error.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE: SwIDs out of range.
 */
sx_status_t
sx_api_port_swid_bind_get(
                         const sx_api_handle_t       handle,
                         const sx_port_log_id_t      log_port,
                         sx_swid_t             *swid_id_p
                         );


/**
 *This API is not supported at the current release
 *
 *  	This API Sets the Port's Stacking Mode in the SDK.
 ******************************************************************************
 *
 * @param[in] handle - SX-API handle
 * @param[in] log_port - Logical Port ID.
 * @param[in] mode - new Port Mode.
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO: Message size error.
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT: Message size error.
 * @return SX_STATUS_INVALID_HANDLE: Invalid Handle.
 */
sx_status_t
sx_api_port_mode_set(
                    const sx_api_handle_t    handle,
                    const sx_port_log_id_t   log_port,
                    const sx_port_mode_t     mode
                    );


/**
 *This API is not supported at the current release
 *
 *  	This API Retrieves the Port's Mode from the SDK.
 ******************************************************************************
 *
 * @param[in] handle - SX-API handle
 * @param[in] log_port - Logical Port ID.
 * @param[out] mode_p - Current Port Mode.
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO: Message size error.
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT: Message size error.
 * @return SX_STATUS_INVALID_HANDLE: Invalid Handle.
 */
sx_status_t
sx_api_port_mode_get(
                    const sx_api_handle_t   handle,
                    const sx_port_log_id_t  log_port,
                    sx_port_mode_t  *mode_p
                    );


/**
 *  	This API Sets the Port MTU size in the SDK.
 ******************************************************************************
 *
 * @param[in] handle - SX-API handle
 * @param[in] log_port - Logical Port ID.
 * @param[in] mtu_size - New MTU payload size. SDK will add L2 header size bytes to this value
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO: Message size error.
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT: Message size error.
 */
sx_status_t
sx_api_port_mtu_set(
                   const sx_api_handle_t       handle,
                   const sx_port_log_id_t      log_port,
                   const sx_port_mtu_t         mtu_size
                   );


/**
 *  	This API Retrieves the Port MTU size from the SDK.
 ******************************************************************************
 *
 * @param[in] handle - SX-API handle
 * @param[in] log_port - Logical Port ID.
 * @param[out] max_mtu_size_p - Maximum MTU supported on this port (payload size).
 * @param[out] oper_mtu_size_p - Operational MTU configured on this port (payload size).
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO: Message size error.
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT: Message size error.
 * @return SX_STATUS_PARAM_ERROR: Input parameters error.
 * @return SX_STATUS_INVALID_HANDLE: Invalid Handle.
 */
sx_status_t
sx_api_port_mtu_get(
                   const sx_api_handle_t       handle,
                   const sx_port_log_id_t      log_port,
                   sx_port_mtu_t         *max_mtu_size_p,
                   sx_port_mtu_t         *oper_mtu_size_p
                   );

/**
 *  This API Sets the Port Type & Speed.
 *  It enables the application to set the port enabled mode(s).
 *  When link is up, the current active protocol is retrieved (after SET).
 *  When link is down, the supported protocols are retrieved (after SET).
 ******************************************************************************
 *
 * @param[in] handle - SX-API handle
 * @param[in] log_port - Logical Port ID
 **@param[in] admin_speed_p - New Types & Speeds (protocols)****
 ******  enabled
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO: Message size error
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT: Message size error
 * @return SX_STATUS_PARAM_ERROR: Input parameters error
 * @return SX_STATUS_PARAM_NULL: NULL pointer error
 * @return SX_STATUS_INVALID_HANDLE: Invalid Handle
 */
sx_status_t
sx_api_port_speed_admin_set(
                           const sx_api_handle_t   handle,
                           const sx_port_log_id_t  log_port,
                           const sx_port_speed_capability_t* admin_speed_p);

/**
 * This API Retrieves the Port's Admin Speed from the SDK.
 ******************************************************************************
 *
 * @param[in] handle - SX-API handle
 * @param[in] log_port - Logical Port ID
 * @param[out] admin_speed_p - Port Administrative speed
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO: Message size error
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT: Message size error
 * @return SX_STATUS_PARAM_ERROR: Input parameters error
 * @return SX_STATUS_PARAM_NULL: NULL pointer error
 * @return SX_STATUS_INVALID_HANDLE: Invalid Handle
 */
sx_status_t
sx_api_port_speed_admin_get(
                           const sx_api_handle_t       handle,
                           const sx_port_log_id_t      log_port,
                           sx_port_speed_capability_t* admin_speed_p);

/**
 * This API Retrieves the Port's Operational Speed from the SDK.
 ******************************************************************************
 *
 * @param[in] handle - SX-API handle
 * @param[in] log_port - Logical Port ID
 * @param[out] oper_speed_p - Port Operational speed
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO: Message size error
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT: Message size error
 * @return SX_STATUS_PARAM_ERROR: Input parameters error
 * @return SX_STATUS_PARAM_NULL: NULL pointer error
 * @return SX_STATUS_INVALID_HANDLE: Invalid Handle
 */
sx_status_t
sx_api_port_speed_oper_get(
                          const sx_api_handle_t   handle,
                          const sx_port_log_id_t  log_port,
                          sx_port_oper_speed_t*   oper_speed_p);


/**
 * This API Retrieves the Port's Supported Speeds from the SDK.
 ******************************************************************************
 *
 * @param[in] handle - SX-API handle
 * @param[in] log_port - Logical Port ID
 * @param[out] speed_capability_p - Port Supported speed mode(s)
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO: Message size error
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT: Message size error
 * @return SX_STATUS_PARAM_ERROR: Input parameters error
 * @return SX_STATUS_PARAM_NULL: NULL pointer error
 * @return SX_STATUS_INVALID_HANDLE: Invalid Handle
 */
sx_status_t
sx_api_port_speed_capability_get(
                                const sx_api_handle_t       handle,
                                const sx_port_log_id_t      log_port,
                                sx_port_speed_capability_t* speed_capability_p);


/**
 *  	This API Sets the Port's (base) Physical Address (MAC) from the SDK.
 ******************************************************************************
 *
 * @param[in] handle - SX-API handle
 * @param[in] log_port - Logical Port ID.
 * @param[out] base_mac_addr_p - Current base MAC address.
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO: Message size error.
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT: Message size error.
 * @return SX_STATUS_PARAM_ERROR: Input parameters error.
 * @return SX_STATUS_INVALID_HANDLE: Invalid Handle.
 */
sx_status_t
sx_api_port_phys_addr_get(
                         const sx_api_handle_t       handle,
                         const sx_port_log_id_t      log_port,
                         sx_mac_addr_t         *base_mac_addr_p
                         );

/**
 * This API is not supported at the current release
 *
 * This API sets the port's physical loopback.
 * LAG port or LAG member port cannot be loopback.
 *
 * @param[in] handle - SX-API handle
 * @param[in] log_port - Logical port ID.
 * @param[in] phys_loopback_p - New physical loopback.
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR: Input parameter error.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE: if parameter exceeds range.
 * @return SX_STATUS_INVALID_HANDLE: Invalid Handle.
 * @return SX_STATUS_PARAM_NULL: NULL parameter received.
 */
sx_status_t
sx_api_port_phys_loopback_set(
                             const sx_api_handle_t           handle,
                             const sx_port_log_id_t          log_port,
                             const sx_port_phys_loopback_t   *phys_loopback_p);

/**
 * This API is not supported at the current release
 *
 * This API retrieves the port's physical loopback.
 * LAG port or LAG member port cannot be loopback.
 *
 * @param[in] handle - SX-API handle
 * @param[in] log_port - Logical port ID.
 * @param[out] phys_loopback_p - Current physical loopback.
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR: Input parameter error.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE: if parameter exceeds range.
 * @return SX_STATUS_INVALID_HANDLE: Invalid Handle.
 * @return SX_STATUS_PARAM_NULL: NULL parameter received.
 */
sx_status_t
sx_api_port_phys_loopback_get(
                             const sx_api_handle_t           handle,
                             const sx_port_log_id_t          log_port,
                             sx_port_phys_loopback_t   *phys_loopback_p);


/**
 *  	This API Sets the Port Administrative State in the SDK.
 ******************************************************************************
 *
 * @param[in] handle - SX-API handle
 * @param[in] log_port - Logical Port ID.
 * @param[in] admin_state - New Administrative Status.
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO: Message size error.
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT: Message size error.
 * @return SX_STATUS_COMM_ERROR: Commiunication error - send fail.
 * @return SX_STATUS_INVALID_HANDLE: Invalid Handle.
 */
sx_status_t
sx_api_port_state_set(
                     const sx_api_handle_t       handle,
                     const sx_port_log_id_t      log_port,
                     const sx_port_admin_state_t admin_state
                     );

/**
 *  	This API Retrieves the Port's Administrative, Operational & Module State from the SDK.
 ******************************************************************************
 *
 * @param[in] handle - SX-API handle
 * @param[in] log_port - Logical Port ID.
 * @param[out] oper_state_p - Port operational state.
 * @param[out] admin_state_p - Port administrative state.
 * @param[out] module_state_p - Module operational state.
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL: Received parameter is NULL.
 * @return SX_STATUS_MESSAGE_SIZE_ZERO: Message size error.
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT: Message size error.
 * @return SX_STATUS_COMM_ERROR: Commiunication error - send fail.
 * @return SX_STATUS_INVALID_HANDLE: Invalid Handle.
 */
sx_status_t
sx_api_port_state_get(
                     const sx_api_handle_t       handle,
                     const sx_port_log_id_t      log_port,
                     sx_port_oper_state_t  *oper_state_p,
                     sx_port_admin_state_t *admin_state_p,
                     sx_port_module_state_t *module_state_p
                     );

/**
 * This API is not supported at the current release.
 * 
 * This API Sets the Port Module Status Change Event Generation mode.
 *
 * @param[in] handle - SX-API handle
 * @param[in] log_port - Logical Port ID.
 * @param[in] module_state_change_event_gen_mode - Do/Don't Generate Event on Module Operational Status Change.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE: event mode out of range.
 * @return SX_STATUS_MESSAGE_SIZE_ZERO: Message size error.
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT: Message size error.
 * @return SX_STATUS_COMM_ERROR: Commiunication error - send fail.
 * @return SX_STATUS_INVALID_HANDLE: Invalid Handle.
 */
sx_status_t
sx_api_port_module_state_event_set(
                                  const sx_api_handle_t           handle,
                                  const sx_port_log_id_t          log_port,
                                  const sx_event_generate_mode_t  module_state_change_event_gen_mode
                                  );

/**
 * This API is not supported at the current release.
 *
 * This API Retrieves the Port Status Change Event Generation mode from the SDK.
 *
 * @param[in] handle - SX-API handle
 * @param[in] log_port - Logical Port ID.
 * @param[out] module_state_change_event_gen_mode - Do/Don't Generate Event on Port Operational Status Change.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL: NULL parameter received.
 * @return SX_STATUS_MESSAGE_SIZE_ZERO: Message size error.
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT: Message size error.
 * @return SX_STATUS_COMM_ERROR: Commiunication error - send fail.
 * @return SX_STATUS_INVALID_HANDLE: Invalid Handle.
 */
sx_status_t
sx_api_port_module_state_event_get(
                                  const sx_api_handle_t           handle,
                                  const sx_port_log_id_t          log_port,
                                  sx_event_generate_mode_t  *module_state_change_event_gen_mode_p
                                  );

/**
 *  	This API Sets the Port Flow Control Pause Configuration
 ******************************************************************************
 *
 * @param[in] handle - SX-API handle
 * @param[in] log_port - Logical Port ID (whose flow control configuration to set)
 * @param[in] fc_mode - enum which represent tx/rx Flow Control state.
 * ENUM sets the mode of both RX & TX with one of 4 possible EN/DIS combinations
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL: NULL parameter received.
 * @return SX_STATUS_MESSAGE_SIZE_ZERO: Message size error.
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT: Message size error.
 * @return SX_STATUS_COMM_ERROR: Commiunication error - send fail.
 * @return SX_STATUS_INVALID_HANDLE: Invalid Handle.
 */
sx_status_t
sx_api_port_flow_ctrl_pause_set(
                               const sx_api_handle_t       handle,
                               const sx_port_log_id_t      log_port,
                               const sx_port_flow_ctrl_mode_t fc_mode
                               );

/**
 *  	This API Retrieves the Port Flow Control Pause Configuration from the SDK.
 ******************************************************************************
 *
 * @param[in] handle - SX-API handle
 * @param[in] log_port - Logical Port ID (whose flow control configuration to retrieve)
 * @param[out] fc_mode_p - enum which represent tx/rx Flow Control state.
 * ENUM gets the mode of both RX & TX with one of 4 possible EN/DIS combinations
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR: Input parameter error.
 * @return SX_STATUS_MESSAGE_SIZE_ZERO: Message size error.
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT: Message size error.
 * @return SX_STATUS_COMM_ERROR: Commiunication error - send fail.
 * @return SX_STATUS_INVALID_HANDLE: Invalid Handle.
 */
sx_status_t
sx_api_port_flow_ctrl_pause_get(
                               const sx_api_handle_t           handle,
                               const sx_port_log_id_t          log_port,
                               sx_port_flow_ctrl_mode_t  *fc_mode_p
                               );

/**
 *  	This API Sets the Port Priority Flow Control Configuration.
 ******************************************************************************
 *
 * @param[in] handle - SX-API handle
 * @param[in] log_port - Port ID
 * @param[in] pfc_prio - PFC priority
 * @param[in] fc_mode - enum which represent tx/rx Flow Control state.
 * ENUM sets the mode of both RX & TX with one of 4 possible EN/DIS combinations
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE: event mode out of range.
 * @return SX_STATUS_MESSAGE_SIZE_ZERO: Message size error.
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT: Message size error.
 * @return SX_STATUS_COMM_ERROR: Commiunication error - send fail.
 * @return SX_STATUS_INVALID_HANDLE: Invalid Handle.
 */
sx_status_t
sx_api_port_flow_ctrl_priority_set(
                                  const sx_api_handle_t           handle,
                                  const sx_port_log_id_t          log_port,
                                  const sx_port_flow_ctrl_prio_t  pfc_prio,
                                  const sx_port_flow_ctrl_mode_t  fc_mode
                                  );

/**
 *  	This API Retrieves the Port Priority Flow Control Configuration from the SDK.
 ******************************************************************************
 *
 * @param[in] handle - SX-API handle
 * @param[in] log_port - Port ID
 * @param[in] pfc_prio - PFC priority
 * @param[out] fc_mode_p - enum which represent tx/rx Flow Control state.
 * ENUM gets the mode of both RX & TX with one of 4 possible EN/DIS combinations
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE: event mode out of range.
 * @return SX_STATUS_MESSAGE_SIZE_ZERO: Message size error.
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT: Message size error.
 * @return SX_STATUS_COMM_ERROR: Commiunication error - send fail.
 * @return SX_STATUS_INVALID_HANDLE: Invalid Handle.
 */
sx_status_t
sx_api_port_flow_ctrl_priority_get(
                                  const sx_api_handle_t           handle,
                                  const sx_port_log_id_t          log_port,
                                  const sx_port_flow_ctrl_prio_t  pfc_prio,
                                  sx_port_flow_ctrl_mode_t  *fc_mode_p
                                  );

/**
 *  	This API Sets the Port Credit Based Flow Control Configuration .
 ******************************************************************************
 *
 * @param[in] handle - SX-API handle
 * @param[in] log_port - Port ID
 * @param[in] cbfc_prio - CBFC priority
 * @param[in] fc_mode - enum which represent tx/rx Flow Control state.
 * ENUM sets the mode of both RX & TX with one of 4 possible EN/DIS combinations
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE: event mode out of range.
 * @return SX_STATUS_MESSAGE_SIZE_ZERO: Message size error.
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT: Message size error.
 * @return SX_STATUS_COMM_ERROR: Commiunication error - send fail.
 * @return SX_STATUS_INVALID_HANDLE: Invalid Handle.
 */
sx_status_t
sx_api_port_flow_ctrl_credit_set(
                                const sx_api_handle_t           handle,
                                const sx_port_log_id_t          log_port,
                                const sx_port_flow_ctrl_prio_t  cbfc_prio,
                                const sx_port_flow_ctrl_mode_t  fc_mode
                                );

/**
 *  	This API Retrieves the Port Credit Based Flow Control Configuration from the SDK.
 ******************************************************************************
 *
 * @param[in] handle - SX-API handle
 * @param[in] log_port - Port ID
 * @param[in] cbfc_prio - CBFC priority
 * @param[out] fc_mode_p - enum which represent tx/rx Flow Control state.
 * ENUM gets the mode of both RX & TX with one of 4 possible EN/DIS combinations
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE: event mode out of range.
 * @return SX_STATUS_MESSAGE_SIZE_ZERO: Message size error.
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT: Message size error.
 * @return SX_STATUS_COMM_ERROR: Commiunication error - send fail.
 * @return SX_STATUS_PARAM_ERROR: Input parameter error.
 * @return SX_STATUS_INVALID_HANDLE: Invalid Handle.
 */
sx_status_t
sx_api_port_flow_ctrl_credit_get(
                                const sx_api_handle_t           handle,
                                const sx_port_log_id_t          log_port,
                                const sx_port_flow_ctrl_prio_t  cbfc_prio,
                                sx_port_flow_ctrl_mode_t* fc_mode_p
                                );

/**
 *  	This API Retrieves the Port IEEE 802.3 Counters from the SDK.
 ******************************************************************************
 *
 * @param[in] handle - SX-API handle
 * @param[in] log_port - Logical Port ID.
 * @param[out] cntr_ieee_802_dot_3_p - IEEE 802.3 counters entry.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO: Message size error.
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT: Message size error.
 * @return SX_STATUS_COMM_ERROR: Commiunication error - send fail.
 * @return SX_STATUS_INVALID_HANDLE: Invalid Handle.
 */
sx_status_t
sx_api_port_cntr_ieee_802_dot_3_get(
                                   const sx_api_handle_t               handle,
                                   const sx_port_log_id_t              log_port,
                                   sx_port_cntr_ieee_802_dot_3_t *cntr_ieee_802_dot_3_p
                                   );

/**
 *  	This API Retrieves the Port RFC 2863 Counters from the SDK.
 ******************************************************************************
 *
 * @param[in] handle - SX-API handle
 * @param[in] log_port - Logical Port ID.
 * @param[out] cntr_rfc_2863_p - RFC 2863 counters entry.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO: Message size error.
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT: Message size error.
 * @return SX_STATUS_COMM_ERROR: Commiunication error - send fail.
 * @return SX_STATUS_INVALID_HANDLE: Invalid Handle.
 * @return SX_STATUS_PARAM_NULL: Input NULL parameter.
 */
sx_status_t
sx_api_port_cntr_rfc_2863_get(
                             const sx_api_handle_t       handle,
                             const sx_port_log_id_t      log_port,
                             sx_port_cntr_rfc_2863_t *cntr_rfc_2863_p
                             );

/**
 *  	This API Retrieves the Port RFC 2819 Counters from the SDK.
 ******************************************************************************
 *
 * @param[in] handle - SX-API handle
 * @param[in] log_port - Logical Port ID.
 * @param[out] cntr_rfc_2819_p - RFC 2819 counters entry.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO: Message size error.
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT: Message size error.
 * @return SX_STATUS_COMM_ERROR: Commiunication error - send fail.
 * @return SX_STATUS_INVALID_HANDLE: Invalid Handle.
 * @return SX_STATUS_PARAM_NULL: Input NULL parameter.
 */
sx_status_t
sx_api_port_cntr_rfc_2819_get(
                             const sx_api_handle_t           handle,
                             const sx_port_log_id_t          log_port,
                             sx_port_cntr_rfc_2819_t   *cntr_rfc_2819_p
                             );

/**
 *  	This API Retrieves the Port RFC 3635 Counters from the SDK.
 ******************************************************************************
 *
 * @param[in] handle - SX-API handle
 * @param[in] log_port - Logical Port ID.
 * @param[out] cntr_rfc_3635_p - RFC 3635 counters entry.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO: Message size error.
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT: Message size error.
 * @return SX_STATUS_COMM_ERROR: Commiunication error - send fail.
 * @return SX_STATUS_INVALID_HANDLE: Invalid Handle.
 * @return SX_STATUS_PARAM_NULL: Input NULL parameter.
 */
sx_status_t
sx_api_port_cntr_rfc_3635_get(
                             const sx_api_handle_t handle,
                             const sx_port_log_id_t log_port,
                             sx_port_cntr_rfc_3635_t *cntr_rfc_3635_p
                             );

/**
 *  	This API Retrieves the Port CLI Counters from the SDK.
 ******************************************************************************
 *
 * @param[in] handle - SX-API handle
 * @param[in] log_port - Logical Port ID.
 * @param[out] cntr_cli_p - CLI counters entry.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO: Message size error.
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT: Message size error.
 * @return SX_STATUS_COMM_ERROR: Commiunication error - send fail.
 * @return SX_STATUS_INVALID_HANDLE: Invalid Handle.
 * @return SX_STATUS_PARAM_NULL: Input NULL parameter.
 */
sx_status_t
sx_api_port_cntr_cli_get(
                        const sx_api_handle_t handle,
                        const sx_port_log_id_t log_port,
                        sx_port_cntr_cli_t *cntr_cli_p
                        );

/**
 ****** This API Retrieves the Port Priority Counters from the SDK.
 ****** When a LAG port is given the result is the sum of all
 ****** the LAG ports counters.
 ******************************************************************************
 *
 * @param[in] handle - SX-API handle
 * @param[in] log_port - Logical Port ID.
 * @param[in] cntr_prio_id - Counters Priority ID.
 * @param[out] cntr_prio_p - Priority counters entry.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE: event mode out of range.
 * @return SX_STATUS_MESSAGE_SIZE_ZERO: Message size error.
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT: Message size error.
 * @return SX_STATUS_COMM_ERROR: Commiunication error - send fail.
 * @return SX_STATUS_INVALID_HANDLE: Invalid Handle.
 * @return SX_STATUS_PARAM_NULL: Input NULL parameter.
 */
sx_status_t
sx_api_port_cntr_prio_get(
                         const sx_api_handle_t handle,
                         const sx_port_log_id_t log_port,
                         const sx_port_cntr_prio_id_t cntr_prio_id,
                         sx_port_cntr_prio_t *cntr_prio_p
                         );


/**
 * This API gets the port's traffic class counters  
 * @param[in] handle - SX-API handle 
 * @param[in] log_port - logical port id 
 * @param[in] traffic_class - traffic class id
 * @param[out] cntr_p - per port per TC counters
 * Note: The API does not support LAG
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if Invalid parameter was supplied
 * @return SX_STATUS_INVALID_HANDLE if handle is NULL
 * @return SX_STATUS_PARAM_NULL if one of the parameter is NULL 
 * @return SX_STATUS_ERROR otherwise 
 */
sx_status_t
sx_api_port_cntr_tc_get(
                       const sx_api_handle_t            handle,
                       const sx_port_log_id_t           log_port,
                       const sx_port_tc_id_t                tc_id,
                       sx_port_traffic_cntr_t           *cntr_tc_p

                       );


/**
 ****** This API Retrieves the extended port counters from the
 ****** SDK.
 ****** LAG port is not supported.
 ******************************************************************************
 *
 * @param[in] handle - SX-API handle
 * @param[in] log_port - Logical Port ID.
 * @param[in] cntr_prio_id - Counters Priority ID.
 * @param[out] cntr_ext_p - extended counters entry.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE: event mode out of range.
 * @return SX_STATUS_MESSAGE_SIZE_ZERO: Message size error.
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT: Message size error.
 * @return SX_STATUS_COMM_ERROR: Commiunication error - send fail.
 * @return SX_STATUS_INVALID_HANDLE: Invalid Handle.
 **@return SX_STATUS_PARAM_NULL: Input NULL parameter.
 **@return SX_STATUS_PARAM_ERROR: Input parameter error.
 */
sx_status_t
sx_api_port_cntr_ext_get(
                        const sx_api_handle_t handle,
                        const sx_port_log_id_t log_port,
                        const sx_port_cntr_prio_id_t cntr_prio_id,
                        sx_port_cntr_ext_t *cntr_ext_p
                        );

/**
 *  This API clear Port Counters.
 *  The user has the following options :
 *
 *   1. clear a specific port (set log_port field with the log port ID && all_ports = FALSE) :
 *      option a. clear specific counter group (set the group in cntr_grp).
 *      option b. clear all counter groups (set cntr_grp = SX_PORT_CNTR_GRP_ALL)
 *
 *   2. clear all ports (set all_ports = TRUE) :
 *      option a. clear specific counter group (set the group in cntr_grp).
 *      option b. clear all counter groups (set cntr_grp = SX_PORT_CNTR_GRP_ALL)
 *
 ******************************************************************************
 *
 * @param[in] handle         - SX-API handle
 * @param[in] log_port       - Logical Port ID.
 * @param[in] all_ports      - Clear all ports counters
 * @param[in] cntr_grp       - Performance counter group.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO: Message size error.
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT: Message size error.
 * @return SX_STATUS_COMM_ERROR: Commiunication error - send fail.
 * @return SX_STATUS_INVALID_HANDLE: Invalid Handle.
 */
sx_status_t
sx_api_port_cntr_clear_set(
                          const sx_api_handle_t    handle,
                          const sx_port_log_id_t   log_port,
                          const boolean_t          all_ports,
                          const sx_port_cntr_grp_t cntr_grp
                          );

/**
 *  	This API Initializes the Port in the SDK.
 ******************************************************************************
 *
 * @param[in] handle - SX-API handle
 * @param[in] log_port - Logical Port ID.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO: Message size error.
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT: Message size error.
 * @return SX_STATUS_COMM_ERROR: Commiunication error - send fail.
 * @return SX_STATUS_INVALID_HANDLE: Invalid Handle.
 */
sx_status_t
sx_api_port_init(
                const sx_api_handle_t handle,
                const sx_port_log_id_t log_port
                );

/**
 *  	This API De-Initializes the Port in the SDK.
 ******************************************************************************
 *
 * @param[in] handle - SX-API handle
 * @param[in] log_port - Logical Port ID.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO: Message size error.
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT: Message size error.
 * @return SX_STATUS_COMM_ERROR: Commiunication error - send fail.
 * @return SX_STATUS_INVALID_HANDLE: Invalid Handle.
 */
sx_status_t
sx_api_port_deinit(
                  const sx_api_handle_t handle,
                  const sx_port_log_id_t log_port
                  );

/**
 * This API Binds / Un-binds a policer to / from a port
 * Cannot bind policer to LAG member port
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - SX_ACCESS_CMD_BIND: bind a policer to a port and set the flow metering map.
 * 		        	SX_ACCESS_CMD_UNBIND: unbind a policer from a port
 * @param[in] log_port - Logical Port ID
 * @param[in] policer_id - Policer ID
 * @param[in] flow_metering_p - Pointer to the flow map of a 
 *       port-policer pair
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter is invalid
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO in case of HW failure
 * @return SX_STATUS_CMD_UNSUPPORTED if unsupported command is requested
 * @return SX_STATUS_PARAM_NULL if NULL parameter received
 */
sx_status_t
sx_api_port_policer_bind_set(
                            const sx_api_handle_t       handle,
                            const sx_access_cmd_t       cmd,
                            const sx_port_log_id_t      log_port,
                            const sx_policer_id_t       policer_id,
                            const sx_port_policer_flow_metering_type_t *flow_metering_p);

/**
 * This API retrieves Bound policer flow types.
 *
 * @param[in] handle - SX-API handle
 * @param[in] log_port - Logical Port ID
 * @param[in] policer_id - policer ID.
 * @param[out] flow_metering_p - Pointer to flow map of a port-policer pair
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter is invalid
 * @return SX_STATUS_CMD_UNSUPPORTED if unsupported command is requested
 * @return SX_STATUS_PARAM_NULL if NULL parameter received
 */
sx_status_t
sx_api_port_policer_bind_get(
                            const sx_api_handle_t       handle,
                            const sx_port_log_id_t      log_port,
                            const sx_policer_id_t       policer_id,
                            sx_port_policer_flow_metering_type_t    *flow_metering_p);

/**
 * This API controls sFlow state of the port. Using access cmd 
 * CREATE a sFlow sampling is defined on port, then after it is 
 * set user may EDIT the sflow parameters  
 * of a configured port. In order to remove sFlow 
 * sampling from the port use access cmd DESTROY. 
 *  
 * @param[in] handle - SX-API handle 
 * @param[in] cmd - access cmd (CREATE/DESTROY/EDIT) 
 * @param[in] log_port - Logical Port ID. 
 * @param[in, out] sflow_params_p - sFlow related configuration 
 * params(Deviation>0); ignored when CMD=DESTROY. The api will 
 * return the sFlow params configured in practice. Deviation 
 * will be returned in percentage. 
 * 
 * It is highly recommanded to always check the deviation value returned.
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_NO_RESOURCES if out of resources for sFlow policer
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameter supplied 
 *         exceeds supported values.
 * @return SX_STATUS_PARAM_ERROR if Invalid parameter was 
 *         supplied
 * @return SX_STATUS_PARAM_NULL if one of the parameter is NULL 
 * @return SX_STATUS_CMD_UNSUPPORTED if cmd is not supported 
 * @return SX_STATUS_ERROR otherwise 
 */
sx_status_t
sx_api_port_sflow_set(
                     const sx_api_handle_t               handle,
                     const sx_access_cmd_t               cmd,
                     const sx_port_log_id_t              log_port,
                     sx_port_sflow_params_t*   sflow_params_p
                     );


/**
 * This API gets the ports sFlow state.
 *  
 * @param[in] handle - SX-API handle 
 * @param[in] log_port - Logical Port ID.
 * @param[out] sflow_params_p - sFlow related configuration 
 *       parameters
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS if operation completes successfully 
 * @return SX_STATUS_PARAM_NULL if one of the parameter is NULL 
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameter supplied 
 *         exceeds supported values.
 * @return SX_STATUS_PARAM_ERROR if Invalid parameter was 
 *         supplied
 * @return SX_STATUS_ERROR otherwise 
 */
sx_status_t
sx_api_port_sflow_get(
                     const sx_api_handle_t           handle,
                     const sx_port_log_id_t          log_port,
                     sx_port_sflow_params_t*     sflow_params_p
                     );

/**
 * This API controls loopback filter state of the port  
 * @param[in] handle - SX-API handle 
 * @param[in] log_port - Logical Port ID. 
 * @param[in] lbf_mode - loopback filter mode
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if Invalid parameter was supplied
 * @return SX_STATUS_PARAM_NULL if one of the parameter is NULL 
 * @return SX_STATUS_ERROR otherwise 
 */
sx_status_t
sx_api_port_loopback_filter_set(
                               const sx_api_handle_t               handle,
                               const sx_port_log_id_t              log_port,
                               const sx_port_loopback_filter_mode_t    lbf_mode
                               );


/**
 * This API gets the loopback filter state of the port  
 * @param[in] handle - SX-API handle 
 * @param[in] log_port - Logical Port ID. 
 * @param[out] lbf_mode_p - loopback filter mode
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if Invalid parameter was supplied
 * @return SX_STATUS_PARAM_NULL if one of the parameter is NULL 
 * @return SX_STATUS_ERROR otherwise 
 */
sx_status_t
sx_api_port_loopback_filter_get(
                               const sx_api_handle_t               handle,
                               const sx_port_log_id_t              log_port,
                               sx_port_loopback_filter_mode_t          *lbf_mode_p
                               );

/**
 * This function sets the isolation group of the port (a list of ports from which
 * traffic should not be transmitted to log_port).
 * Isolation is supported only between ports on the same device, and on the same SWID.
 * Set - add ports to isolation group (overwrites previous configuration)
 * Add - add ports to isolation group (additionally to previous configuration)
 * Delete - remove ports from isolation group
 * Delete All - empty isolation group
 * @param[in] handle - SX-API handle
 * @param[in] access_cmd - SET/ADD/DELETE/DELETE_ALL
 * @param[in] log_port - Logical Port ID.
 * @param[in] log_port_list_p - list of logical ports
 * @param[in] log_port_cnt - number of logical ports in the list
 *
 * @return SX_STATUS_SUCCESS - Operation completes successfully.
 * @return SX_STATUS_PARAM_NULL - Parameter is unexpectedly NULL.
 * @return SX_STATUS_PARAM_ERROR - Parameter is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND - Requested element is not found in DB.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE - Parameter exceeds its range.
 */
sx_status_t
sx_api_port_isolate_set(
                       const sx_api_handle_t   handle,
                       const sx_access_cmd_t   access_cmd,
                       const sx_port_log_id_t  log_port,
                       const sx_port_log_id_t *log_port_list_p,
                       const length_t          log_port_cnt
                       );

/**
 * This function retrieves the isolation group of the port (a list of ports from which
 * traffic should not be transmitted to log_port).
 * @param[in] handle - SX-API handle
 * @param[in] log_port - Logical Port ID.
 * @param[in,out] log_port_list_p - list of logical ports
 * @param[in,out] log_port_cnt_p - In: Number of Logical Ports 
 * in list, Out: Number of Logical Ports in LAG. Use 
 * log_port_num=0 to retrieve only the size of isolation group. 
 *
 * @return SX_STATUS_SUCCESS - Operation completes successfully.
 * @return SX_STATUS_PARAM_NULL - Parameter is unexpectedly NULL.
 * @return SX_STATUS_PARAM_ERROR - Parameter is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND - Requested element is not found in DB.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE - Parameter exceeds its range.
 */
sx_status_t
sx_api_port_isolate_get(
                       const sx_api_handle_t   handle,
                       const sx_port_log_id_t  log_port,
                       sx_port_log_id_t       *log_port_list_p,
                       length_t               *log_port_cnt_p
                       );

/**
 * This API returns the swid type as it was configured in the 
 * profile, at SDK init time. 
 * 
 * @param swid - Switch Partition ID.
 * @param swid_type - DISABLED/ETHERNET/INFINIBAND
 * 
 * @return SX_STATUS_SUCCESS - Operation completes successfully
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE - Parameter exceeds its
 *         range.
 */
sx_status_t
sx_api_port_swid_type_get(
                         const sx_api_handle_t   handle,
                         const sx_swid_id_t      swid,
                         sx_swid_type_t          *swid_type_p
                         );

#endif /* __SX_API_PORT_H__ */
