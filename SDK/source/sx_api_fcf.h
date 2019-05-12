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


#ifndef __SX_API_FCF_H__
#define __SX_API_FCF_H__

#include <sx/sdk/sx_api.h>
#include <sx/sdk/sx_strings.h>

/**
 * This function sets the log verbosity level of FCF MODULE
 * Supported devices: Not Supported
 * \deprecated This API is deprecated and will be removed in the future
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - SET / GET
 * @param[in] verbosity_target - set get verbosity of : API / MODULE / BOTH
 * @param[in,out] module_verbosity_level_p - FCF module verbosity level
 * @param[in,out] api_verbosity_level_p - FCF API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_fcf_log_verbosity_level(sx_api_handle_t           handle,
                                           sx_access_cmd_t           cmd,
                                           sx_log_verbosity_target_t verbosity_target,
                                           sx_verbosity_level_t     *module_verbosity_level_p,
                                           sx_verbosity_level_t     *api_verbosity_level_p);

/**
 * This function Initiates the FCF module in SDK.
 * Supported devices: Not Supported
 * \deprecated This API is deprecated and will be removed in the future
 *
 * @param[in] handle - SX-API handle.
 * @param[in] params - FCF parameters.
 *
 * @return SX_STATUS_SUCCESS - if operation completes
 *         successfully.
 * @return SX_STATUS_ALREADY_INITIALIZED - When FCF is
 *         already initialized.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE - When calling with bad
 *         parameters.
 */
sx_status_t sx_api_fcf_init(const sx_api_handle_t handle,
                            const sx_fcf_param_t *params);

/**
 * This api deinitializes the FCF in the sdk.
 * Supported devices: Not Supported
 * \deprecated This API is deprecated and will be removed in the future
 *
 * @param[in] handle - SX-API handle.
 *
 * @return SX_STATUS_SUCCESS if operation completes
 *         successfully.
 * @return SX_STATUS_RESOURCE_IN_USE When FCF is still
 *         active.
 */
sx_status_t sx_api_fcf_deinit(const sx_api_handle_t handle);

/**
 *
 *  This function adds/modifies/deletes a FCF.
 *  The FCF ID is allocated and returned to the caller when
 *  cmd is ADD, otherwise it is given by the caller. All
 *  v_ports and forwarding rules associated with a FCF must be
 *  deleted and deallocated before the FCF can be deleted as well.
 *  Supported devices: Not Supported
 *  \deprecated This API is deprecated and will be removed in the future
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - ADD/EDIT/DELETE.
 * @param[in] fcf_attr - FCF attributes.
 * @param[in,out] fcf - FCF ID
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_NULL if parameter is NULL.
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND if FCF was not added.
 * @return SX_STATUS_NO_RESOURCES if there are no resources to
 *         create another FCF
 * @return SX_STATUS_RESOURCE_IN_USE if FCF has v_ports or forwarding rules.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_fcf_set(const sx_api_handle_t      handle,
                           const sx_access_cmd_t      cmd,
                           const sx_fcf_attributes_t *fcf_attr,
                           sx_fcf_id_t               *fcf);

/**
 *
 *  This function gets a FCF information.
 *  Supported devices: Not Supported
 *  \deprecated This API is deprecated and will be removed in the future
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd -  get, get_next, get first
 * @param[in,out] fcf - FCF ID.
 * @param[out] fcf_attr - FCF attributes.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_NULL if parameter is NULL.
 * @return SX_STATUS_ENTRY_NOT_FOUND if FCF was not added.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_fcf_get(const sx_api_handle_t handle,
                           const sx_access_cmd_t cmd,
                           sx_fcf_id_t          *fcf,
                           sx_fcf_attributes_t  *fcf_attr);

/**
 *
 *  This function adds/deletes a v_port from a FCF. If the type if VE_port a MAC should be given.
 *  If the type is VF_port, a mac should not be given as it is calculated by the fabric.
 *  Supported devices: Not Supported
 *  \deprecated This API is deprecated and will be removed in the future
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - ADD/DELETE/DELETE_ALL.
 * @param[in] fcf - FCF ID.
 * @param[in] v_port_attr - v port attributes, can be NULL in case of delete
 * @param[in,out] v_port_handle - A pointer to the added/deleted v_port object.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_ENTRY_NOT_FOUND if FCF v_port was not added.
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_fcf_v_port_interface_set(const sx_api_handle_t             handle,
                                            const sx_access_cmd_t             cmd,
                                            const sx_fcf_id_t                 fcf,
                                            const sx_fcf_v_port_attributes_t *v_port_attr,
                                            sx_fcf_v_port_handle_t          * v_port_handle);

/**
 *
 *  This function defines the IPL (Ingress Port List) in the SDK.
 *  SET = Discard the previous list and use the given list
 *  DEFAULT = Return all the ports to the IPL (by default, all the ports are in the IPL).
 *  DELETE_ALL = Remove all the ports from the IPL.
 *  In addition, it can also ADD/DELETE ports to/from the IPL.
 *  Supported devices: Not Supported
 *  \deprecated This API is deprecated and will be removed in the future
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - DEFAULT/SET/DELETE_ALL/ADD/DELETE.
 * @param[in] port_list - List of Logical Ports to ADD/DELETE to/from an IPL.
 * @param[in] port_num - Number of Logical Ports to ADD/DELETE to/from an IPL.
 *
 * @return SX_STATUS_SUCCESS - Operation completes successfully.
 * @return SX_STATUS_CMD_UNSUPPORTED if unsupported command is requested
 * @return SX_STATUS_INVALID_HANDLE: Invalid Handle
 * @return SX_STATUS_MESSAGE_SIZE_ZERO: Message size error
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT: Message size error
 * @return SX_STATUS_PARAM_NULL - Parameter is unexpectedly NULL.
 * @return SX_STATUS_PARAM_ERROR - Parameter is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND - Requested element is not found in DB.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE - Parameter exceeds its range.
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO - Error status returned from Firmware
 */
sx_status_t sx_api_fcf_ipl_set(const sx_api_handle_t  handle,
                               const sx_access_cmd_t  cmd,
                               const sx_port_log_id_t port_list[],
                               const length_t         log_port_num);

/**
 *
 *  This function retrieves the IPL (Ingress Port List) from the SDK.
 *  Supported devices: Not Supported
 *  \deprecated This API is deprecated and will be removed in the future
 *
 * @param[in] handle - SX-API handle.
 * @param[out] port_list - List of Logical Ports in the IPL.
 * @param[out] port_num - Number of Logical Ports in the IPL.
 *
 * @return SX_STATUS_SUCCESS - Operation completes successfully.
 * @return SX_STATUS_CMD_UNSUPPORTED if unsupported command is requested
 * @return SX_STATUS_INVALID_HANDLE: Invalid Handle
 * @return SX_STATUS_MESSAGE_SIZE_ZERO: Message size error
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT: Message size error
 * @return SX_STATUS_PARAM_NULL - Parameter is unexpectedly NULL.
 * @return SX_STATUS_PARAM_ERROR - Parameter is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND - Requested element is not found in DB.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE - Parameter exceeds its range.
 */
sx_status_t sx_api_fcf_ipl_get(const sx_api_handle_t handle,
                               sx_port_log_id_t      port_list[],
                               length_t            * log_port_num);

/**
 *
 *  This function gets a v_port of a FCF.
 *  Supported devices: Not Supported
 *  \deprecated This API is deprecated and will be removed in the future
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd -  get, get_next, get first
 * @param[in,out] v_port_handle - A pointer to the queried v_port object.
 * @param[out] fcf - FCF ID to which the v_port belongs.
 * @param[out] v_port_attr - The attributes of the queried v_port.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_NULL if parameter is NULL.
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND if FCF was not added.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_fcf_v_port_interface_get(const sx_api_handle_t       handle,
                                            const sx_access_cmd_t       cmd,
                                            sx_fcf_v_port_handle_t    * v_port_handle,
                                            sx_fcf_id_t               * fcf,
                                            sx_fcf_v_port_attributes_t *v_port_attr);

/**
 *
 *  This function adds/modifies/deletes a forwarding entry into the forwarding table.
 *  The forwarding entry is composed of sid, sid mask, did, did mask mapped to a V_port
 *  Supported devices: Not Supported
 *  \deprecated This API is deprecated and will be removed in the future
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - ADD/EDIT/DELETE/DELETE_ALL.
 * @param[in] fcf - FCF ID.
 * @param[in] did - FC destination address
 * @param[in] did_mask - bits from the DID that are used for LPM
 * @param[in] sid - FC source address
 * @param[in] sid_mask - bits from the DID that are used for LPM
 * @param[in] v_port_handle - The v_port the forwarding rule is mapped to.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid.
 * @return SX_STATUS_NO_RESOURCES if no forwarding entry is available to create.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_fcf_forwarding_set(const sx_api_handle_t        handle,
                                      const sx_access_cmd_t        cmd,
                                      const sx_fcf_id_t            fcf,
                                      const sx_fc_addr_t          *did,
                                      const sx_fc_addr_t          *did_mask,
                                      const sx_fc_addr_t          *sid,
                                      const sx_fc_addr_t          *sid_mask,
                                      const sx_fcf_v_port_handle_t v_port_handle);

/**
 *
 *  This function gets a forwarding entry from the forwarding table.
 *  The forwarding entry is composed of sid, sid mask, did, did mask mapped to a V_port
 *  Supported devices: Not Supported
 *  \deprecated This API is deprecated and will be removed in the future
 *
 * @param[in] handle - SX-API handle.
 * @param[in] access_cmd -  get, get_next, get first
 * @param[in] fcf - FCF ID.
 * @param[in] did - FC destination address
 * @param[in] did_mask - bits from the DID that are used for LPM
 * @param[in] sid - FC source address
 * @param[in] sid_mask - bits from the DID that are used for LPM
 * @param[out] v_port_handle - The v_port the forwarding rule is mapped to.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid.
 * @return SX_STATUS_NO_RESOURCES if no forwarding entry is available to create.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_fcf_forwarding_get(const sx_api_handle_t   handle,
                                      sx_access_cmd_t         access_cmd,
                                      const sx_fcf_id_t       fcf,
                                      sx_fc_addr_t           *did,
                                      sx_fc_addr_t           *did_mask,
                                      sx_fc_addr_t           *sid,
                                      sx_fc_addr_t           *sid_mask,
                                      sx_fcf_v_port_handle_t *v_port_handle);

/**
 *
 *  This function allocates/deallocates a FCF counter. A FCF counter
 *  should be bound later to a FCF v_port.
 *  Supported devices: Not Supported
 *  \deprecated This API is deprecated and will be removed in the future
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - ADD/DELETE.
 * @param[in,out] cntr - FCF counter ID.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported.
 * @return SX_STATUS_PARAM_NULL if parameter is NULL.
 * @return SX_STATUS_NO_RESOURCES if no counter is available to create.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_fcf_cntr_alloc_set(const sx_api_handle_t handle,
                                      const sx_access_cmd_t cmd,
                                      sx_fcf_cntr_id_t     *cntr);

/**
 *
 *  This function binds/unbinds a FCF counter to a FCF v_port.
 *  Supported devices: Not Supported
 *  \deprecated This API is deprecated and will be removed in the future
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - ADD/DELETE.
 * @param[in] cntr - FCF counter ID.
 * @param[in] v_port_handle - The v_port the counter should be bound/unbound from.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND if counter was not added.
 * @return SX_STATUS_RESOURCE_IN_USE if interface is already bound.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_fcf_cntr_bind_set(const sx_api_handle_t        handle,
                                     const sx_access_cmd_t        cmd,
                                     const sx_fcf_cntr_id_t       cntr,
                                     const sx_fcf_v_port_handle_t v_port_handle);

/**
 *  \deprecated This API is deprecated and will be removed in the future
 *
 *  This function gets a FCF counter bind of a FCF v_port.
 *  Supported devices: Not Supported
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cntr - FCF counter ID.
 * @param[out] v_port_handle - The v_port the counter is bound to.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_ENTRY_NOT_FOUND if counter was not added.
 * @return SX_STATUS_ENTRY_NOT_BOUND if counter was not bound.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_fcf_cntr_bind_get(const sx_api_handle_t   handle,
                                     const sx_fcf_cntr_id_t  cntr,
                                     sx_fcf_v_port_handle_t *v_port_handle);

/**
 *
 *  This function gets FCF counter set of a FCF counter.
 *  Supported devices: Not Supported
 *  \deprecated This API is deprecated and will be removed in the future
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cntr - FCF counter ID.
 * @param[out] cntr_set - FCF counter set values.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_NULL if parameter is NULL.
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND if counter was not added.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_fcf_cntr_get(const sx_api_handle_t  handle,
                                const sx_fcf_cntr_id_t cntr,
                                sx_fcf_cntr_set_t     *cntr_set);

/**
 *
 *  This function clears fcf counter set of a fcf counter.
 *  Supported devices: Not Supported
 *  \deprecated This API is deprecated and will be removed in the future
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cntr - FCF counter ID.
 * @param[in] all - Clear all FCF counters.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_NULL if parameter is NULL.
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND if counter was not added.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_fcf_cntr_clear_set(const sx_api_handle_t  handle,
                                      const sx_fcf_cntr_id_t cntr,
                                      const boolean_t        all);

#endif /* __SX_API_FCF_H__ */
