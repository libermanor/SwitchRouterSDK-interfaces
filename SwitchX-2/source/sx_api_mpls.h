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
#ifndef __SX_API_MPLS_H__
#define __SX_API_MPLS_H__

#include <sx/sdk/sx_api.h>
#include <sx/sdk/sx_mpls.h>

/************************************************
 *  API functions
 ***********************************************/

/* This API sets the log verbosity level of MPLS MODULE.
 * Supported devices: Spectrum.
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] verbosity_target         - set verbosity of : API / MODULE / BOTH
 * @param[in] module_verbosity_level   - MPLS module verbosity level
 * @param[in] api_verbosity_level      - MPLS API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE when parameter exceeds range.
 */

sx_status_t sx_api_mpls_log_verbosity_level_set(const sx_api_handle_t           handle,
                                                const sx_log_verbosity_target_t verbosity_target,
                                                const sx_verbosity_level_t      module_verbosity_level,
                                                const sx_verbosity_level_t      api_verbosity_level);

/* This API gets the log verbosity level of MPLS MODULE.
 * Supported devices: Spectrum.
 *
 * @param[in]  handle                   - SX-API handle
 * @param[in]  verbosity_target         - get verbosity of : API / MODULE / BOTH
 * @param[out] module_verbosity_level_p - MPLS module verbosity level
 * @param[out] api_verbosity_level_p    - MPLS API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE when parameter exceeds range.
 */

sx_status_t sx_api_mpls_log_verbosity_level_get(const sx_api_handle_t           handle,
                                                const sx_log_verbosity_target_t verbosity_target,
                                                sx_verbosity_level_t           *module_verbosity_level_p,
                                                sx_verbosity_level_t           *api_verbosity_level_p);

/* This function initiates the MPLS module in SDK.
 * Supported devices: Spectrum.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] general_params - MPLS general parameters
 *
 *
 * @return SX_STATUS_SUCCESS - if operation completes
 *         successfully.
 * @return SX_STATUS_ALREADY_INITIALIZED - When router is
 *         already initialized.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE - When calling with bad
 *         parameters.
 */

sx_status_t sx_api_mpls_init_set(const sx_api_handle_t          handle,
                                 const sx_mpls_general_params_t general_params);

/* This function de-initiates the MPLS block in the SDK
 * Supported devices: Spectrum.
 *
 * @param[in] handle - SX-API handle.
 *
 * @return SX_STATUS_SUCCESS if operation completes
 *         successfully.
 * @return SX_STATUS_RESOURCE_IN_USE When router is still
 *         active.
 */

sx_status_t sx_api_mpls_deinit_set(const sx_api_handle_t handle);

/* This function creates ILM table
 * Supported devices: Spectrum.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - CREATE/ADD/DELETE/DESTROY
 * @param[in] ilm_table - MPLS ILM table ID
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported.
 * @return SX_STATUS_PARAM_NULL if parameter is NULL.
 * @return SX_STATUS_NO_RESOURCES if no ILM tables is available to create.
 * @return SX_STATUS_ERROR general error.
 */

sx_status_t sx_api_mpls_ilm_init_set(const sx_api_handle_t        handle,
                                     const sx_access_cmd_t        cmd,
                                     const sx_mpls_ilm_table_id_t ilm_table);

/* This function sets an in-segment
 * Supported devices: Spectrum.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - CREATE/EDIT/DESTROY
 * @param[in] in_segment_key_p -  in-segment incoming label
 * @param[in] in_segment_params_p - parameters for in-segment
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported.
 * @return SX_STATUS_PARAM_ERROR if parameter is wrong
 * @return SX_STATUS_NO_RESOURCES if no resources are available
 * @return SX_STATUS_ERROR general error.
 */

sx_status_t sx_api_mpls_in_segment_set(const sx_api_handle_t              handle,
                                       const sx_access_cmd_t              cmd,
                                       const sx_mpls_in_segment_key_t    *in_segment_key_p,
                                       const sx_mpls_in_segment_params_t *in_segment_params_p);

/* This function gets an in-segment parameters
 * Supported devices: Spectrum.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - GET/GET_FIRST/ GET_NEXT.
 * @param[in] in_segment_key_p - in-segment identificator
 * @param[out] in_segment_params_p - parameters for in-segment
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND if in_segment does not exist.
 * @return SX_STATUS_ERROR general error.
 */

sx_status_t sx_api_mpls_in_segment_get(const sx_api_handle_t           handle,
                                       const sx_access_cmd_t           cmd,
                                       const sx_mpls_in_segment_key_t *in_segment_key_p,
                                       sx_mpls_in_segment_params_t    *in_segment_params_p);

/* This function sets the MPLS attributes of the interface
 * Supported devices: Spectrum.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] rif_p - router interface ID
 * @param[in] rif_mpls_attr_p - the MPLS attributes of the interface
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported.
 * @return SX_STATUS_PARAM_ERROR if parameter is NULL.
 * @return SX_STATUS_NO_RESOURCES if no ILM tables is available to create.
 * @return SX_STATUS_ERROR general error.
 */

sx_status_t sx_api_mpls_router_interface_attributes_set(const sx_api_handle_t                  handle,
                                                        const sx_router_interface_t           *rif_p,
                                                        const sx_mpls_router_interface_attr_t *rif_mpls_attr_p);

/* This function gets the MPLS attributes of the interface
 * Supported devices: Spectrum.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] rif_p - router interface ID
 * @param[out] rif_mpls_attr_p - the MPLS attributes of the interface
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported.
 * @return SX_STATUS_PARAM_ERROR if parameter is NULL.
 * @return SX_STATUS_NO_RESOURCES if no ILM tables is available to create.
 * @return SX_STATUS_ERROR general error.
 */

sx_status_t sx_api_mpls_router_interface_attributes_get(const sx_api_handle_t            handle,
                                                        const sx_router_interface_t     *rif_p,
                                                        sx_mpls_router_interface_attr_t *rif_mpls_attr_p);

#endif /* __SX_API_MPLS_H__ */
