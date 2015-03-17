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

#ifndef __SX_API_COS_H__
#define __SX_API_COS_H__

#include <sx/sdk/sx_api.h>


/************************************************
 *  API functions
 ***********************************************/

/**
 * This API sets the log verbosity level of COS MODULE.
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] verbosity_target         - set verbosity of : API / MODULE / BOTH
 * @param[in] module_verbosity_level   - COS module verbosity level
 * @param[in] api_verbosity_level      - COS API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_log_verbosity_level_set(const sx_api_handle_t           handle,
                                               const sx_log_verbosity_target_t verbosity_target,
                                               const sx_verbosity_level_t      module_verbosity_level,
                                               const sx_verbosity_level_t      api_verbosity_level);

/**
 * This API gets the log verbosity level of COS MODULE.
 *
 * @param[in]  handle                   - SX-API handle
 * @param[in]  verbosity_target         - get verbosity of : API / MODULE / BOTH
 * @param[out] module_verbosity_level_p - COS module verbosity level
 * @param[out] api_verbosity_level_p    - COS API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_log_verbosity_level_get(const sx_api_handle_t           handle,
                                               const sx_log_verbosity_target_t verbosity_target,
                                               sx_verbosity_level_t           *module_verbosity_level_p,
                                               sx_verbosity_level_t           *api_verbosity_level_p);

/**
 * This function sets the port default priority value.
 * Packets arriving to port 'log_port' without a priority
 * are handled according to the value of 'priority'.
 *
 * @param[in] handle       - SX-API handle
 * @param[in] log_port     - logical port ID
 * @param[in] priority     - port priority [0..7 , default is 0]
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 * @return SX_STATUS_MEMORY_ERROR error handling memory
 */
sx_status_t sx_api_cos_port_default_prio_set(const sx_api_handle_t   handle,
                                             const sx_port_log_id_t  log_port,
                                             const sx_cos_priority_t priority);

/**
 * This function retrieves the default port priority value.
 *
 * @param[in]  handle          - SX-API handle
 * @param[in]  log_port        - logical port ID
 * @param[out] priority_p      - port priority [0..7]
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_port_default_prio_get(const sx_api_handle_t  handle,
                                             const sx_port_log_id_t log_port,
                                             sx_cos_priority_t     *priority_p);

/**
 * This function sets the port ingress priority map values.
 * Packets arriving to 'log_port' with the priority 'source_priority'
 * are handled according to the priority 'regenerated_priority'.
 *
 * @param[in] handle               - SX-API handle
 * @param[in] log_port             - logical port ID
 * @param[in] source_priority      - original priority [0..7]
 * @param[in] regenerated_priority - regenerated priority [0..7]
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 * @return SX_STATUS_MEMORY_ERROR error handling memory
 */
sx_status_t sx_api_cos_port_prio_ingress_regen_set(const sx_api_handle_t   handle,
                                                   const sx_port_log_id_t  log_port,
                                                   const sx_cos_priority_t source_priority,
                                                   const sx_cos_priority_t regenerated_priority);

/**
 * This function retrieves the port ingress priority regen values.
 *
 * @param[in]  handle            - SX-API handle
 * @param[in]  log_port          - logical port ID
 * @param[in]  source_priority   - original priority [0..7]
 * @param[out] regen_priority_p  - regenerated priority [0..7]
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_port_prio_ingress_regen_get(const sx_api_handle_t   handle,
                                                   const sx_port_log_id_t  log_port,
                                                   const sx_cos_priority_t source_priority,
                                                   sx_cos_priority_t      *regen_priority_p);

/**
 *  This function adds or deletes a priority from a traffic
 *  class (TC). When a priority is added to a TC, it is
 *  automatically re-mapped from its previous allocation. When
 *  a priority is deleted from a TC, it is reallocated
 *  according to default settings.
 *
 *  Each packet has an assigned priority. The priority of the packet
 *  is mapped to one of eight traffic classes (egress queue)
 *  according to prio -> traffic class map.
 *  Each packet is dequeued on the egress port based on its
 *  traffic class.
 *
 *
 *  Note: Multiple priorities can be mapped to a single TC.
 *  Default settings :
 *
 *  Priority 0 -> Traffic Class 0;
 *  Priority 1 -> Traffic Class 0;
 *  Priority 2 -> Traffic Class 1;
 *  Priority 3 -> Traffic Class 1;
 *  Priority 4 -> Traffic Class 2;
 *  Priority 5 -> Traffic Class 2;
 *  Priority 6 -> Traffic Class 3;
 *  Priority 7 -> Traffic Class 3;
 *
 * @param[in] handle        - SX-API handle
 * @param[in] cmd           - Add/Delete
 * @param[in] log_port      - logical port ID (egress port)
 * @param[in] priority      - priority
 * @param[in] traffic_class - traffic class
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 * @return SX_STATUS_MEMORY_ERROR error handling memory
 * @return SX_STATUS_CMD_ERROR if an unsupported command is requested
 */
sx_status_t sx_api_cos_port_tc_prio_map_set(const sx_api_handle_t        handle,
                                            const sx_access_cmd_t        cmd,
                                            const sx_port_log_id_t       log_port,
                                            const sx_cos_priority_t      priority,
                                            const sx_cos_traffic_class_t traffic_class);

/**
 *  This function retrieves the traffic class of a specific
 *  priority.
 *
 * @param[in]  handle          - SX-API handle
 * @param[in]  log_port        - logical port ID
 * @param[in]  priority        - priority
 * @param[out] traffic_class_p - traffic class
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_port_tc_prio_map_get(const sx_api_handle_t   handle,
                                            const sx_port_log_id_t  log_port,
                                            const sx_cos_priority_t priority,
                                            sx_cos_traffic_class_t *traffic_class_p);

/**
 * This function sets the port trust level value. SwitchX
 * assigns the user priority based on the following modes:
 * Trust port user priority - ignore packets priority and assign
 * priority based on the port configuration.
 * Trust packet user priority - tagged L2 packets are assigned with
 * packets priority, untagged packets are assigned with port's priority.
 * Trust DSCP - IP packets are assigned with a priority based on
 * the DSCP to UP mapping. Non-IP packets are assigned with
 * port's priority.
 * Trust both - IP packets are assigned with a priority based on the
 * DSCP to UP mapping. Else, tagged L2 packets are assigned with
 * packets priority, untagged packets are assigned with port's priority.
 *
 * @param[in] handle      - SX-API handle
 * @param[in] log_port    - logical port id
 * @param[in] trust_level - trust level  [trust port user priority,
 *                                        trust packet user priority ,
 *                                        trust DSCP ,
 *                                        trust both]
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 * @return SX_STATUS_MEMORY_ERROR error handling memory
 */
sx_status_t sx_api_cos_port_trust_set(const sx_api_handle_t      handle,
                                      const sx_port_log_id_t     log_port,
                                      const sx_cos_trust_level_t trust_level);

/**
 * This function retrieves the port trust level value.
 *
 * @param[in]  handle        - SX-API handle
 * @param[in]  log_port      - logical port id
 * @param[out] trust_level_p - trust level  [trust port ,
 *                                           trust user priority ,
 *                                           trust DSCP ,
 *                                           trust both]
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_port_trust_get(const sx_api_handle_t  handle,
                                      const sx_port_log_id_t log_port,
                                      sx_cos_trust_level_t  *trust_level_p);

/**
 * This API is not supported in the current release.
 *
 * This function sets the map between DSCP and port priority.
 * This table is used when the port trust mode is set to 'dscp'.
 *
 * @param[in] handle     - SX-API handle
 * @param[in] dscp       - DSCP [0..63]
 * @param[in] priority   - priority [0..7]
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_ip_dscp_to_prio_set(const sx_api_handle_t   handle,
                                           const sx_cos_dscp_t     dscp,
                                           const sx_cos_priority_t priority);

/**
 *
 * This function retrieves the map between DSCP and priority.
 *
 * @param[in]  handle           - SX-API handle
 * @param[in]  dscp             - DSCP [0..63]
 * @param[out] priority_p       - priority [0..7]
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_ip_dscp_to_prio_get(const sx_api_handle_t handle,
                                           const sx_cos_dscp_t   dscp,
                                           sx_cos_priority_t    *priority_p);


/**
 * This function binds a traffic class (TC) to a TC group,
 * sets MAX bandwidth allocation (%), and sets MAX band width
 * allowed for the TC.
 *
 * @param[in]  handle          - SX-API handle
 * @param[in]  log_port        - logical port
 * @param[in]  tc_config_p     - pointer to array of TC structures
 * @param[in]  tc_config_cnt   - number of elements in the array
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_port_ets_set(const sx_api_handle_t            handle,
                                    const sx_port_log_id_t           log_port,
                                    const sx_cos_tc_config_params_t *tc_config_p,
                                    const uint32_t                   tc_config_cnt);

/**
 * This function retrieves the traffic class (TC) group for TC.
 *
 * @param[in]  handle        - SX-API handle
 * @param[in]  log_port      - logical port
 * @param[out] tc_config_p   - pointer to array of 8 structures
 * @param[in]  tc_config_cnt - number of elements in the array
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_port_ets_get(const sx_api_handle_t      handle,
                                    const sx_port_log_id_t     log_port,
                                    sx_cos_tc_config_params_t *tc_config_p,
                                    const uint32_t             tc_config_cnt);


/**
 * This function sets the ETS a general configuration of a log port.
 *
 * @param[in] handle        - SX-API handle
 * @param[in] log_port      - logical port ID
 * @param[in] port_config_p - pointer to port ETS structure
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_port_ets_general_configuration_set(const sx_api_handle_t                      handle,
                                                          const sx_port_log_id_t                     log_port,
                                                          const sx_cos_port_ets_gen_config_params_t *port_config_p);


/**
 * This function retrieves the ETS general configuration of log port.
 *
 * @param[in] handle         - SX-API handle
 * @param[in] log_port       - logical port ID
 * @param[out] port_config_p - pointer to port ETS structure
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_port_ets_general_configuration_get(const sx_api_handle_t                handle,
                                                          const sx_port_log_id_t               log_port,
                                                          sx_cos_port_ets_gen_config_params_t *port_config_p);


/**
 * This API sets a port's buffer management control in the SDK.
 *
 * Note:
 * Allocation of buffers 0-7 is under the following restrictions:
 * On global pause mode, only a single buffer (buffer 1) can be configured.
 * All traffic goes to buffer 1
 * Buffer 0 must be used for lossy traffic (no pause should be used).
 *
 * @param[in] handle          - SX-API handle
 * @param[in] cmd             - CMD SX_ACCESS_CMD_SET or SX_ACCESS_CMD_DELETE
 * @param[in] log_port        - logical port ID
 * @param[in] xof_timer_value - SwitchX pause frame: Pause timer
 * @param[in] xof_refresh     - send pause frame interval
 * @param[in] buffer_list_p  - array of 8 buffer parameters structures
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 * @return SX_STATUS_CMD_UNSUPPORTED if command is not supported
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if the total buffer sizes exceeds the max for this port
 */
sx_status_t sx_api_cos_port_buff_set(const sx_api_handle_t            handle,
                                     const sx_access_cmd_t            cmd,
                                     const sx_port_log_id_t           log_port,
                                     const sx_cos_timer_value_t       xof_timer_value,
                                     const sx_cos_timer_value_t       xof_refresh,
                                     const sx_cos_port_buff_params_t *buffer_list_p);

/**
 * This API retrieves the port's buffer management control from the SDK.
 *
 * @param[in]  handle              - SX-API handle
 * @param[in]  log_port            - logical port ID
 * @param[out] xof_timer_value_p   - pause timer field
 * @param[out] xof_refresh_p       - send pause frame interval
 * @param[out] total_buffer_size_p - total packet buffer array available for the port
 * @param[out] buffer_list_p       - array of 8 buffer parameters structures
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_port_buff_get(const sx_api_handle_t      handle,
                                     const sx_port_log_id_t     log_port,
                                     sx_cos_timer_value_t      *xof_timer_value_p,
                                     sx_cos_timer_value_t      *xof_refresh_p,
                                     sx_cos_port_buff_size_t   *total_buffer_size_p,
                                     sx_cos_port_buff_params_t *buffer_list_p);

/**
 * This API sets the port's priority to buffer map in the SDK.
 *
 * Note:
 * Untagged frames must use a buffer used by one of the prios.
 * SwitchX cannot allocate a buffer for untagged frames only.
 *
 * @param[in] handle          - SX-API handle
 * @param[in] cmd             - access command SX_ACCESS_CMD_SET
 * @param[in] log_port        - logical port ID
 * @param[in] prio_to_buff_p  - mapping between a priority and the buffer
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 * @return SX_STATUS_CMD_UNSUPPORTED command is not supported
 */
sx_status_t sx_api_cos_port_prio_buff_map_set(const sx_api_handle_t    handle,
                                              const sx_access_cmd_t    cmd,
                                              const sx_port_log_id_t   log_port,
                                              sx_cos_port_prio_buff_t *prio_to_buff_p);

/**
 * This API retrieves the port's priority to buffer mapping from the SDK.
 *
 * @param[in] handle          - SX-API handle
 * @param[in] log_port        - logical port ID
 * @param[out] prio_to_buff_p - mapping between a priority and the buffer
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_port_prio_buff_map_get(const sx_api_handle_t    handle,
                                              const sx_port_log_id_t   log_port,
                                              sx_cos_port_prio_buff_t *prio_to_buff_p);

/**
 * This API sets the port priority QCN mode (interior / interior ready).
 *
 * @param[in] handle            - SX-API handle
 * @param[in] log_port          - logical port ID
 * @param[in] priority          - port priority
 * @param[in] qcn_mode          - QCN mode (interior / interior ready)
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_cos_qcn_port_prio_mode_set(const sx_api_handle_t        handle,
                                              const sx_port_log_id_t       log_port,
                                              const sx_cos_priority_t      priority,
                                              const sx_cos_port_qcn_mode_t qcn_mode);

/**
 *  This API retrieves the port priority QCN mode (interior / interior ready).
 *
 * @param[in] handle            - SX-API handle
 * @param[in] log_port          - logical port ID
 * @param[in] priority          - port priority
 * @param[out] qcn_mode_p       - QCN mode (interior / interior ready)
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_cos_qcn_port_prio_mode_get(const sx_api_handle_t   handle,
                                              const sx_port_log_id_t  log_port,
                                              const sx_cos_priority_t priority,
                                              sx_cos_port_qcn_mode_t *qcn_mode_p);

/**
 * This API enable / disable the port priority QCN.
 *
 * @param[in] handle            - SX-API handle
 * @param[in] log_port          - logical port ID
 * @param[in] priority          - port priority
 * @param[in] qcn_enable        - enable / disable the generation of CNM message
 *                                from the port & priority VOQ toward the ports
 *                                where the traffic came from
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_cos_qcn_port_prio_enable_set(const sx_api_handle_t   handle,
                                                const sx_port_log_id_t  log_port,
                                                const sx_cos_priority_t priority,
                                                const boolean_t         qcn_enable);

/**
 *  This API retrieves the port priority QCN configuration.
 *
 * @param[in] handle            - SX-API handle
 * @param[in] log_port          - logical port ID
 * @param[in] priority          - port priority
 * @param[out] qcn_enable_p     - generation of CNM message
 *                                from the port & priority VOQ toward the ports
 *                                where the traffic came from (enable / disable)
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_cos_qcn_port_prio_enable_get(const sx_api_handle_t   handle,
                                                const sx_port_log_id_t  log_port,
                                                const sx_cos_priority_t priority,
                                                boolean_t              *qcn_enable_p);

/**
 * This API retrieves the CPID (Congestion Point Identifier) value per priority per port.
 *
 * @param[in] handle    - SX-API handle
 * @param[in] log_port  - logical port ID
 * @param[in] priority  - port priority [0..7 , default is 0]
 * @param[out] cpid_p   - The Congestion Point Identifier per priority per port
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_cos_qcn_port_prio_cpid_get(const sx_api_handle_t   handle,
                                              const sx_port_log_id_t  log_port,
                                              const sx_cos_priority_t priority,
                                              sx_cos_qcn_cpid_t      *cpid_p);

/**
 * This API create / destroy a QCN profile ID according to params.
 *
 * @param[in] handle            - SX-API handle
 * @param[in] cmd               - CREATE / EDIT / DESTROY
 * @param[in] params_p          - pointer to QCN profile parameters
 * @param[in,out] profile_id_p  - profile ID
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_cos_qcn_profile_set(const sx_api_handle_t              handle,
                                       const sx_access_cmd_t              cmd,
                                       const sx_cos_qcn_profile_params_t *params_p,
                                       sx_cos_qcn_profile_id_t           *profile_id_p);

/**
 * This API retrieves the QCN profile params per profile ID.
 *
 * @param[in] handle        - SX-API handle
 * @param[in] profile_id    - profile ID
 * @param[out] params_p     - pointer to QCN profile parameters
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_cos_qcn_profile_get(const sx_api_handle_t         handle,
                                       const sx_cos_qcn_profile_id_t profile_id,
                                       sx_cos_qcn_profile_params_t  *params_p);

/**
 * This API bind / unbind port to / from QCN profile ID.
 *
 * @param[in] handle        - SX-API handle
 * @param[in] cmd           - BIND / UNBIND
 * @param[in] log_port      - logical port ID
 * @param[in] profile_id    - profile ID
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_cos_qcn_port_profile_bind_set(const sx_api_handle_t         handle,
                                                 const sx_access_cmd_t         cmd,
                                                 const sx_port_log_id_t        log_port,
                                                 const sx_cos_qcn_profile_id_t profile_id);

/**
 * This API retrieves the profile ID bound to a given port.
 *
 * @param[in] handle        - SX-API handle
 * @param[in] log_port      - logical port ID
 * @param[out] profile_id_p - profile ID
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_cos_qcn_port_profile_bind_get(const sx_api_handle_t    handle,
                                                 const sx_port_log_id_t   log_port,
                                                 sx_cos_qcn_profile_id_t *profile_id_p);

/**
 * This API sets the QCN general parameters.
 *
 * @param[in] handle   - SX-API handle
 * @param[in] swid     - switch ID
 * @param[in] params_p - pointer to QCN params structure:
 *                       cnm_priority - the CNM packet PCP priority to be used
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_cos_qcn_general_param_set(const sx_api_handle_t      handle,
                                             const sx_swid_t            swid,
                                             const sx_cos_qcn_params_t *params_p);

/**
 * This API retrieves the QCN general parameters.
 *
 * @param[in] handle    - SX-API handle
 * @param[in] swid      - switch ID
 * @param[out] params_p - pointer to QCN params structure:
 *                        cnm_priority - the CNM packet PCP priority
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_cos_qcn_general_param_get(const sx_api_handle_t handle,
                                             const sx_swid_t       swid,
                                             sx_cos_qcn_params_t  *params_p);

/**
 * This API is exposing Switch-EN functionality and is not supported in the current release.
 *
 * This API sets the Egress Pool parameters.
 *
 * @param[in] handle              - SX-API handle
 * @param[in] cmd                 - CMD SX_ACCESS_CMD_SET or SX_ACCESS_CMD_DELETE
 * @param[out] pool_id             - Pool ID pointer
 * @param[in] pool_size           - Pool size
 * @param[in] mode                - Pool working mode (Static/ Dynamic (Alpha))
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */

sx_status_t sx_api_cos_egress_pool_set(const sx_api_handle_t    handle,
                                       const sx_access_cmd_t    cmd,
                                       const sx_cos_pool_size_t pool_size,
                                       const sx_cos_pool_mode_t mode,
                                       sx_cos_pool_id_t        *pool_id);

/**
 * This API is exposing Switch-EN functionality and is not supported in the current release.
 *
 * This API sets the Ingress Pool parameters.
 *
 * @param[in] handle              - SX-API handle
 * @param[in] cmd                 - CMD SX_ACCESS_CMD_SET or SX_ACCESS_CMD_DELETE
 * @param[out] pool_id             - Pool ID pointer
 * @param[in] pool_size           - Pool size
 * @param[in] mode                - Pool working mode (Static/ Dynamic (Alpha))
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */

sx_status_t sx_api_cos_ingress_pool_set(const sx_api_handle_t    handle,
                                        const sx_access_cmd_t    cmd,
                                        const sx_cos_pool_size_t pool_size,
                                        const sx_cos_pool_mode_t mode,
                                        sx_cos_pool_id_t        *pool_id);


/**
 * This API is exposing Switch-EN functionality and is not supported in the current release.
 *
 * This API gets the Pool parameters.
 *
 * @param[in] handle              - SX-API handle
 * @param[in] pool_id             - Pool ID
 * @param[in/out] pool_size       - Pool size pointer
 * @param[in/out] mode            - Pool mode pointer
 * @param[in/out] direction       - Pool direction pointer
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_cos_pool_get(const sx_api_handle_t    handle,
                                const sx_cos_pool_id_t   pool_id,
                                sx_cos_pool_size_t      *pool_size,
                                sx_cos_pool_mode_t      *mode,
                                sx_cos_pool_direction_t *direction);

/**
 * This API is exposing Switch-EN functionality and is not supported in the current release.
 *
 * This API sets the port Ingress shared buffers parameters.
 *
 * @param[in] handle    - SX-API handle
 * @param[in] cmd       - CMD SX_ACCESS_CMD_SET or SX_ACCESS_CMD_DELETE
 * @param[in] log_port_p- logical port ID list
 * @param[in] port_cnt  - Number of ports in the list
 * @param[in] port_pool_params_p - pointer to a list of 4 ingress pool parameters
 * @param[in] port_pool_cnt - Number of pools in the list
 * @param[in] buffer_list_p - pointer to a list of 8 PRIOs buffers params:
 *                               pool size and pool ID
 * @param[in] buffer_cnt - Number of buffers in the list
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_cos_port_ing_shared_buff_set(const sx_api_handle_t                  handle,
                                                const sx_access_cmd_t                  cmd,
                                                const sx_port_log_id_t                *log_port_list_p,
                                                const uint32_t                         port_cnt,
                                                const sx_cos_buffer_properties_t      *port_pool_params_p,
                                                const uint32_t                         port_pool_cnt,
                                                const sx_cos_port_share_buff_params_t *buffer_list_p,
                                                const uint32_t                         buffer_cnt);

/**
 * This API is exposing Switch-EN functionality and is not supported in the current release.
 *
 * This API gets the port Ingress shared buffers parameters.
 *
 * @param[in] handle    - SX-API handle
 * @param[in] log_port  - logical port ID
 * @param[out] port_pool_params_p - pointer to a list of 4 ingress pool parameters
 * @param[in] port_pool_cnt - Number of pools in the list
 * @param[out] buffer_list_p - pointer to a list of 8 PRIOs buffers params:
 *                             pool size and pool ID
 * @param[in] buffer_cnt - Number of buffers in the list
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */

sx_status_t sx_api_cos_port_ing_shared_buff_get(const sx_api_handle_t            handle,
                                                const sx_port_log_id_t           log_port,
                                                sx_cos_buffer_properties_t      *port_pool_params_p,
                                                const uint32_t                   port_pool_cnt,
                                                sx_cos_port_share_buff_params_t *buffer_list_p,
                                                const uint32_t                   buffer_cnt);

/**
 * This API is exposing Switch-EN functionality and is not supported in the current release.
 *
 * This API sets the port Egress shared buffers parameters.
 *
 * @param[in] handle    - SX-API handle
 * @param[in] cmd       - CMD SX_ACCESS_CMD_SET or SX_ACCESS_CMD_DELETE
 * @param[in] log_port_p- logical port ID list
 * @param[in] port_cnt  - Number of ports in the list
 * @param[in] port_pool_params_p - pointer to a list of 4 ingress pool parameters
 * @param[in] port_pool_cnt - Number of pools in the list
 * @param[in] buffer_list_p - pointer to a list of 8 PRIOs buffers params:
 *                               pool size and pool ID
 * @param[in] buffer_cnt - Number of buffers in the list
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_cos_port_egr_shared_buff_set(const sx_api_handle_t                  handle,
                                                const sx_access_cmd_t                  cmd,
                                                const sx_port_log_id_t                *log_port_list_p,
                                                const uint32_t                         port_cnt,
                                                const sx_cos_buffer_properties_t      *port_pool_params_p,
                                                const uint32_t                         port_pool_cnt,
                                                const sx_cos_port_share_buff_params_t *buffer_list_p,
                                                const uint32_t                         buffer_cnt);

/**
 * This API is exposing Switch-EN functionality and is not supported in the current release.
 *
 * This API gets the port Egress shared buffers parameters.
 *
 * @param[in] handle    - SX-API handle
 * @param[in] log_port  - logical port ID
 * @param[out] port_pool_params_p - pointer to a list of 4 ingress pool parameters
 * @param[in] port_pool_cnt - Number of pools in the list
 * @param[out] buffer_list_p - pointer to a list of 8 PRIOs buffers params:
 *                             pool size and pool ID
 * @param[in] buffer_cnt - Number of buffers in the list
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */

sx_status_t sx_api_cos_port_egr_shared_buff_get(const sx_api_handle_t            handle,
                                                const sx_port_log_id_t           log_port,
                                                sx_cos_buffer_properties_t      *port_pool_params_p,
                                                const uint32_t                   port_pool_cnt,
                                                sx_cos_port_share_buff_params_t *buffer_list_p,
                                                const uint32_t                   buffer_cnt);


#endif /* __SX_API_COS_H__ */
