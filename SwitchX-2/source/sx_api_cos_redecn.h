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

#ifndef __SX_API_REDECN_H__
#define __SX_API_REDECN_H__


#include <sx/sdk/sx_api.h>
#include <sx/sdk/sx_cos_redecn.h>

/************************************************
 *  API functions
 ***********************************************/
/**
 * This API sets the log verbosity level of REDECN MODULE.
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
sx_status_t sx_api_cos_redecn_verbosity_level_set(const sx_api_handle_t           handle,
                                                  const sx_log_verbosity_target_t verbosity_target,
                                                  const sx_verbosity_level_t      module_verbosity_level,
                                                  const sx_verbosity_level_t      api_verbosity_level);

/**
 * This API gets the log verbosity level of REDECN MODULE.
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
sx_status_t sx_api_cos_redecn_log_verbosity_level_get(const sx_api_handle_t           handle,
                                                      const sx_log_verbosity_target_t verbosity_target,
                                                      sx_verbosity_level_t           *module_verbosity_level_p,
                                                      sx_verbosity_level_t           *api_verbosity_level_p);
/**
 * This function sets global configuration of ECN and RED
 * Supported devices: Spectrum.
 *
 * @param[in] handle    - SX-API handle
 * @param[in] configuration_p	- configuration parameters @see sx_cos_redecn_global_t
 *
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 *
 */
sx_status_t sx_api_cos_redecn_general_param_set(const sx_api_handle_t         handle,
                                                const sx_cos_redecn_global_t *configuration_p);


/**
 * This function gets global configuration of ECN and RED
 * Supported devices: Spectrum.
 *
 * @param[in] handle                    - SX-API handle
 * @param[out] configuration_p	- configuration parameters @see sx_cos_redecn_global_t
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 *
 */
sx_status_t sx_api_cos_redecn_general_param_get(const sx_api_handle_t   handle,
                                                sx_cos_redecn_global_t *configuration_p);


/**
 * This function creates a single RED/ECN profile
 * Supported devices: Spectrum.
 *
 * @param[in]       handle -            SX-API handle
 * @param[in]       cmd -                       SX_ACCESS_CMD_ADD - create a new profile - profile_p is the output
 *                                                                      SX_ACCESS_CMD_EDIT - edit a profile
 *                                                                      SX_ACCESS_CMD_DELETE - delete a profile (params_p is ignored)
 * @param[in]		params_p -	        parameter of redecn profile attributes
 * @param[in/out]	profile_p -     configured or profile to reconfigure/delete
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 * @return SX_STATUS_NO_RESOURCES no available
 *
 */
sx_status_t sx_api_cos_redecn_profile_set(const sx_api_handle_t                     handle,
                                          const sx_access_cmd_t                     cmd,
                                          const sx_cos_redecn_profile_attributes_t *params_p,
                                          sx_cos_redecn_profile_t                  *profile_p);


/**
 * This function gets RED/ECN profile configuration for given profile
 * Supported devices: Spectrum.
 *
 * @param[in]   handle -        SX-API handle
 * @param[in]	profile -       redecn profile to get
 * @param[out]	params_p -      structure of retrieved profile attributes
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 *
 */
sx_status_t sx_api_cos_redecn_profile_get(const sx_api_handle_t               handle,
                                          const sx_cos_redecn_profile_t       profile,
                                          sx_cos_redecn_profile_attributes_t *params_p);


/**
 * This function enables/disables RED and ECN for traffic classes
 * Supported devices: Spectrum.
 *
 * @param[in] handle -                          SX-API handle
 * @param[in] log_port -                egress port to set
 * @param[in] traffic_classes_p -       list of traffic classes this configuration applies to
 * @param[in] traffic_classes_cnt - num of traffic classes
 * @param[in] params_p -                        enable parameters
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_redecn_tc_enable_set(const sx_api_handle_t                handle,
                                            const sx_port_log_id_t               log_port,
                                            const sx_cos_traffic_class_t        *traffic_classes_p,
                                            const uint8_t                        traffic_classes_cnt,
                                            const sx_cos_redecn_enable_params_t *params_p);


/**
 * This function gets RED and ECN enabled parameters of a traffic class
 * Supported devices: Spectrum.
 *
 * @param[in] handle - SX-API handle
 * @param[in] log_port - egress port to query
 * @param[in] traffic_class - traffic class to get
 * @param[in] params_p - enable parameters
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_redecn_tc_enable_get(const sx_api_handle_t          handle,
                                            const sx_port_log_id_t         log_port,
                                            const sx_cos_traffic_class_t   traffic_class,
                                            sx_cos_redecn_enable_params_t *params_p);


/**
 * This function binds RED and ECN profiles to the traffic class and traffic type (TCP/non-TCP, color).
 * Supported devices: Spectrum.
 *
 * @param[in] handle - SX-API handle
 * @param[in] log_port - egress port to bind/unbind
 * @param[in] cmd - SX_ACCESS_CMD_BIND - bind a port+tc+flow to a profile
 *                                      SX_ACCESS_CMD_UNBIND - unbind a port+tc+flow from a profile
 * @param[in] traffic_classes_p - traffic classes affected by this command
 * @param[in] traffic_classes_cnt - number of traffic classes in the above array
 * @param[in] flow_type - flow type to bind/unbind
 * @param[in] params_p - profile to bind to this flow type
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_redecn_profile_tc_bind_set(const sx_api_handle_t              handle,
                                                  const sx_port_log_id_t             log_port,
                                                  const sx_access_cmd_t              cmd,
                                                  const sx_cos_traffic_class_t      *traffic_classes_p,
                                                  const uint8_t                      traffic_classes_cnt,
                                                  const sx_cos_redecn_flow_type_e    flow_type,
                                                  const sx_cos_redecn_bind_params_t *params_p);


/**
 * This function retrieves the binding of RED/ECN profiles configuration for given egress port and traffic class.
 * Supported devices: Spectrum.
 *
 * @param[in]  handle - SX-API handle
 * @param[in]  log_port - egress port to query
 * @param[in]  traffic_class - traffic class to retrieve
 * @param[in]  flow_type - flow type to bind/unbind
 * @param[out] params_p - profile to bind to this flow type
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 *
 */
sx_status_t sx_api_cos_redecn_profile_tc_bind_get(const sx_api_handle_t           handle,
                                                  const sx_port_log_id_t          log_port,
                                                  const sx_cos_traffic_class_t    traffic_class,
                                                  const sx_cos_redecn_flow_type_e flow_type,
                                                  sx_cos_redecn_bind_params_t    *params_p);


/**
 * This function sets the rate based configuration for RED/ECN
 * Supported devices: Spectrum.
 *
 * @param[in] handle		-  SX-API handle
 * @param[in] enabled        - enable/disable
 * @param[in] log_port	- egress port to configure
 * @param[in] params_p		- parameters - used only when enabling
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_redecn_rate_based_set(const sx_api_handle_t              handle,
                                             const boolean_t                    enabled,
                                             const sx_port_log_id_t             log_port,
                                             sx_cos_redecn_rate_based_params_t *params_p);

/**
 * This function gets the rate based configuration for RED/ECN
 * Supported devices: Spectrum.
 *
 * @param[in] handle		-  SX-API handle
 * @param[in] log_port	- egress port to configure
 * @param[out] params_p		- configured parameters
 * @param[out] enabled_p		- is rate based enabled
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_redecn_rate_based_get(const sx_api_handle_t              handle,
                                             const sx_port_log_id_t             log_port,
                                             sx_cos_redecn_rate_based_params_t *params_p,
                                             boolean_t                         *enabled_p);


/**
 * This function sets the mirroring binding for packets that are discarded (due to tail drop or RED) in the egress port.
 * Supported devices: Spectrum.
 *
 * @param[in] handle    -  SX-API handle
 * @param[in] cmd   - SX_ACCESS_CMD_ADD or SX_ACCESS_CMD_DELETE
 * @param[in] ingress_port - port to mirror to
 * @param[in] span_session_id - session id to use
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_redecn_mirroring_set(const sx_api_handle_t      handle,
                                            const sx_access_cmd_t      cmd,
                                            const sx_port_log_id_t     ingress_port,
                                            const sx_span_session_id_t span_session_id);


/**
 * This function gets the mirroring binding for packets that are discarded (due to tail drop or RED) in the egress port.
 * Supported devices: Spectrum.
 *
 * @param[in]   handle                  - SX-API handle
 * @param[out]  ingress_port_p  -               port to test
 * @param[out]  enabled_p           - enabled/disabled for the port
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_redecn_mirroring_get(const sx_api_handle_t  handle,
                                            const sx_port_log_id_t ingress_port,
                                            boolean_t             *enabled_p);

/**
 *	This function get the RED/ECN counter for a specific egress_port
 * Supported devices: Spectrum.
 *
 * @param[in] handle		-  SX-API handle
 * @param[in] cmd           - SX_ACCESS_CMD_READ or SX_ACCESS_CMD_READ_CLEAR
 * @param[in] log_port	-       egress port to query
 * @param[out] counters_p		- counters structure
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_redecn_counters_get(const sx_api_handle_t          handle,
                                           const sx_access_cmd_t          cmd,
                                           const sx_port_log_id_t         log_port,
                                           sx_cos_redecn_port_counters_t *counters_p);

/**
 * This function is used to configure whether ecn marking should be counted
 * Supported devices: Spectrum.
 *
 * @param[in] handle SX-API handle
 * @param[in] enabled true for counting, false to not count
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 * @return SX_STATUS_CMD_UNSUPPORTED if the function is being called in an unsupported chip
 */
sx_status_t sx_api_cos_redecn_counters_count_marked_set(const sx_api_handle_t handle,
                                                        const boolean_t       enabled);

/**
 * This function is used to get whether ecn marking should be counted
 * Supported devices: Spectrum.
 *
 * @param[in] handle SX-API handle
 * @param[in] enabled_p true for counting, false to not count
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_redecn_counters_count_marked_get(const sx_api_handle_t handle,
                                                        const boolean_t      *enabled_p);


#endif /* ifndef __SX_API_REDECN_H__ */
