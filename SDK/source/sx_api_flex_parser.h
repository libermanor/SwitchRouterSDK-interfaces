/*
 *  Copyright (C) 2014-2018. Mellanox Technologies, Ltd. ALL RIGHTS RESERVED.
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

#ifndef __SX_API_FLEX_PARSER_H__
#define __SX_API_FLEX_PARSER_H__

#include <sx/sdk/sx_api.h>
#include <sx/sdk/sx_strings.h>


/************************************************
 *  API functions
 ***********************************************/
/**
 * This API sets the log verbosity level of FLEX_PARSER MODULE.
 * Supported devices: Spectrum.
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] verbosity_target         - set verbosity of : API / MODULE / BOTH
 * @param[in] module_verbosity_level   - FLEX_PARSER module verbosity level
 * @param[in] api_verbosity_level      - FLEX_PARSER API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */


sx_status_t sx_api_flex_parser_log_verbosity_level_set(const sx_api_handle_t           handle,
                                                       const sx_log_verbosity_target_t verbosity_target,
                                                       const sx_verbosity_level_t      module_verbosity_level,
                                                       const sx_verbosity_level_t      api_verbosity_level);


/**
 * This API gets the log verbosity level of FLEX_PARSER MODULE.
 * Supported devices: Spectrum.
 *
 * @param[in]  handle                   - SX-API handle
 * @param[in]  verbosity_target         - get verbosity of : API / MODULE / BOTH
 * @param[out] module_verbosity_level_p - FLEX_PARSER module verbosity level
 * @param[out] api_verbosity_level_p    - FLEX_PARSER API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_ERROR for a general error
 * @return SX_STATUS_PARAM_NULL if an input parameter is invalid
 */

sx_status_t sx_api_flex_parser_log_verbosity_level_get(const sx_api_handle_t           handle,
                                                       const sx_log_verbosity_target_t verbosity_target,
                                                       sx_verbosity_level_t           *module_verbosity_level_p,
                                                       sx_verbosity_level_t           *api_verbosity_level_p);


/**
 * Initialize the flex parser API.
 * Supported devices: Spectrum.
 * Parameters:
 * @param[in]    handle     - SX-API handle
 * @param[in]    params     - Configuration parameters for the initial state of the flex parser
 *                          - params is don't-care for Spectrum.
 *
 * Returns:
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_UNSUPPORTED if the module is not supported by platform
 * @return SX_STATUS_NO_RESOURCES if configuration fails due to a lack of HW resources
 * @return SX_STATUS_ALREADY_INITIALIZED if module is already initialized.
 */

sx_status_t sx_api_flex_parser_init_set(const sx_api_handle_t         handle,
                                        const sx_flex_parser_param_t *params);


/**
 * De-initialize the flex parser API
 * Supported devices: Spectrum.
 * Parameters:
 * @param[in]    handle     - SX-API handle
 *
 * Returns:
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_MODULE_UNINITIALIZED if de-initialization is invoked without initialization
 * @return SX_STATUS_UNSUPPORTED if module is not supported by platform.
 */
sx_status_t sx_api_flex_parser_deinit_set(const sx_api_handle_t handle);


/**
 * Configure enable/disable for the transition between two existing flex parser headers in the parse
 * graph. Caller must specify the header to enable the transition "From" and "To" nodes.
 * Depending on the "To" (next protocol field) definition, the actual size of the value
 * used may be less than 32 bits.
 * Note that some combinations may be unsupported and will return SX_STATUS_UNSUPPORTED
 * Supported devices: Spectrum.
 * Spectrum supports only Fixed header type.
 * Spectrum supports only transition from UDP to VxLAN with outer encapsulation level
 * Parameters:
 * @param[in]    handle            - SX-API handle
 * @param[in]    cmd               - SX_ACCESS_CMD_SET / SX_ACCESS_CMD_UNSET
 * @param[in]    from              - the flex parser header to transition from
 * @param[in]    to                - the flex parser next transition header information
 * Returns:
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_UNSUPPORTED if configuration is not supported by the platform.
 * @return SX_STATUS_NO_RESOURCES if configuration fails due to a lack of HW resources
 * @return SX_STATUS_MODULE_UNINITIALIZED if API is called without initialization.
 * @return SX_STATUS_CMD_UNSUPPORTED - if invalid cmd is passed
 */

sx_status_t sx_api_flex_parser_transition_set(const sx_api_handle_t             handle,
                                              const sx_access_cmd_t             cmd,
                                              const sx_flex_parser_header_t     from,
                                              const sx_flex_parser_transition_t to);


/**
 * Get the configuration of a transition from a given node in the parse graph.
 * Caller can start at the root and iterate over the results to traverse
 * the entire parse graph.
 * Supported devices: Spectrum
 * Spectrum supports only UDP as current header.
 * Parameters:
 * @param [in]  handle     - SX-API handle
 * @param [in]  curr_ph    - the current flex parser header to transition from
 * @param [out] next_trans_p - a pointer to array of node transition structure.
 *                                If it is NULL, the next_trans_cnt variable is filled out
 *                                with numbers of transitions that could be retrieved. If
 *                                the pointer is valid, node transition info is placed
 *                                and next_trans_cnt takes actual number ports in array.
 * @param [out] next_trans_cnt - Specifies the number of items in the next_trans_p array
 *
 * Returns:
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_UNSUPPORTED if configuration is not supported by the platform
 * @return SX_STATUS_NO_RESOURCES if configuration fails due to a lack of HW resources
 * @return SX_STATUS_MODULE_UNINITIALIZED if API called without init
 * @return SX_STATUS_PARAM_NULL if next_trans_cnt parameter is NULL
 */
sx_status_t sx_api_flex_parser_transition_get(const sx_api_handle_t         handle,
                                              const sx_flex_parser_header_t curr_ph,
                                              sx_flex_parser_transition_t  *next_trans_p,
                                              uint32_t                     *next_trans_cnt);

#endif /* __SX_API_FLEX_PARSER_H__ */
