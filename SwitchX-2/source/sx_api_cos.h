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

#ifndef __SX_API_COS_H__
#define __SX_API_COS_H__

#include <sx/sdk/sx_api.h>


/************************************************
 *  API functions
 ***********************************************/

/**
 * This API sets the log verbosity level of COS MODULE.
 * Supported devices: SwitchX, SwitchX2, Spectrum.
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
 * Supported devices: SwitchX, SwitchX2, Spectrum.
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
 * This function sets the port default switch priority value.
 * Used for "trust port" configuration or for packets with the relevant
 * priority field is unavailable.
 * Not supported per VPORT.
 * Supported devices: SwitchX, SwitchX2, Spectrum.
 * In SwitchX the function sets the default switch-priority and the default PCP together.
 * In Spectrum the function sets the default switch-priority.
 *
 * @param[in] handle       - SX-API handle
 * @param[in] log_port     - logical port ID
 * @param[in] priority     - switch priority [0..cos_port_prio_max
 *                              (see resource manager) , default is 0]
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
 * This function retrieves the default port switch priority value.
 * Supported devices: SwitchX, SwitchX2, Spectrum.
 *
 * @param[in]  handle          - SX-API handle
 * @param[in]  log_port        - logical port ID
 * @param[out] priority_p      - switch priority [0..cos_port_prio_max
 *                              (see resource manager) , default is 0]
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
 * Packets arriving to 'log_port' with the priority (PCP) 'source_priority'
 * are handled according to the switch-priority 'regenerated_priority'.
 * Supported devices: SwitchX, SwitchX2, Spectrum.
 * For Spectrum recommended to use sx_api_cos_port_pcpdei_to_prio_set.
 *
 * @param[in] handle               - SX-API handle
 * @param[in] log_port             - logical port ID
 * @param[in] source_priority      - original priority (PCP)
 * @param[in] regenerated_priority - regenerated priority(switch-priority)
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 * @return SX_STATUS_MEMORY_ERROR error handling memory
 * @return SX_STATUS_CMD_UNSUPPORTED if being called in Spectrum
 */
sx_status_t sx_api_cos_port_prio_ingress_regen_set(const sx_api_handle_t   handle,
                                                   const sx_port_log_id_t  log_port,
                                                   const sx_cos_priority_t source_priority,
                                                   const sx_cos_priority_t regenerated_priority);

/**
 * This function retrieves the port ingress priority regen values.
 * Supported devices: SwitchX, SwitchX2, Spectrum.
 * For Spectrum recommended to use sx_api_cos_port_pcpdei_to_prio_get.
 *
 * @param[in]  handle            - SX-API handle
 * @param[in]  log_port          - logical port ID
 * @param[in]  source_priority   - original priority (PCP)
 * @param[out] regen_priority_p  - regenerated priority (switch-priority)
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 * @return SX_STATUS_CMD_UNSUPPORTED if being called in Spectrum
 */
sx_status_t sx_api_cos_port_prio_ingress_regen_get(const sx_api_handle_t   handle,
                                                   const sx_port_log_id_t  log_port,
                                                   const sx_cos_priority_t source_priority,
                                                   sx_cos_priority_t      *regen_priority_p);

/**
 *  This function adds or deletes a priority from a traffic
 *  class (TC). When a switch priority is added to a TC, it is
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
 * Supported devices: SwitchX, SwitchX2, Spectrum.
 *
 *  Note: Multiple priorities can be mapped to a single TC.
 *  SwitchX default settings:
 *  Priority 0 -> Traffic Class 0;
 *  Priority 1 -> Traffic Class 0;
 *  Priority 2 -> Traffic Class 1;
 *  Priority 3 -> Traffic Class 1;
 *  Priority 4 -> Traffic Class 2;
 *  Priority 5 -> Traffic Class 2;
 *  Priority 6 -> Traffic Class 3;
 *  Priority 7 -> Traffic Class 3;
 *
 *  Spectrum default settings:
 *  for i = [0,7]: switch priority i -> traffic class i.
 *  for i = [8,14]: switch priority i -> traffic class 7.
 *
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
 *  switch priority.
 * Supported devices: SwitchX, SwitchX2, Spectrum.
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
 * Trust packet user priority/Trust L2 - tagged L2 packets are assigned with
 * packets priority, untagged packets are assigned with port's priority.
 * Trust DSCP/Trust L3 - IP packets are assigned with a priority based on
 * the DSCP to UP mapping. Non-IP packets are assigned with
 * port's priority.
 * Trust both - IP packets are assigned with a priority based on the
 * DSCP to UP mapping. Else, tagged L2 packets are assigned with
 * packets priority, untagged packets are assigned with port's priority.
 * In Spectrum for MPLS packets EXP field is used instead of DSCP.
 * Supported devices: SwitchX, SwitchX2, Spectrum.
 *
 * @param[in] handle      - SX-API handle
 * @param[in] log_port    - logical port id
 * @param[in] trust_level - trust level  [trust port user priority,
 *                                        trust L2,
 *                                        trust L3,
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
 * Supported devices: SwitchX, SwitchX2, Spectrum.
 *
 * @param[in]  handle        - SX-API handle
 * @param[in]  log_port      - logical port id
 * @param[out] trust_level_p - trust level  [trust port,
 *                                           trust L2,
 *                                           trust L3,
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
 *
 * This function sets the map from DSCP to switch-priority.
 * This table is used when the port trust mode is set to 'L3'.
 * The configuration is global.
 *
 * The mapping from dscp to prio is global on SwitchX.
 * Supported devices: SwitchX, SwitchX2, Spectrum.
 *
 * @param[in] handle     - SX-API handle
 * @param[in] dscp       - DSCP [0..63]
 * @param[in] priority   - switch priority [0..cos_port_prio_max
 *                              (see resource manager) , default is 0]
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
 * This function retrieves the map between DSCP and switch priority.
 *
 * Supported devices: SwitchX, SwitchX2, Spectrum.
 *
 * @param[in]  handle           - SX-API handle
 * @param[in]  dscp             - DSCP [0..63]
 * @param[out] priority_p       - switch priority [0..cos_port_prio_max
 *                              (see resource manager) , default is 0]
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
 * sets MAX bandwidth allocation (%), and sets MAX bandwidth
 * allowed for the TC.
 * For Spectrum it is recommended to use sx_api_cos_port_ets_element_set.
 * Supported devices: SwitchX, SwitchX2, Spectrum.
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
 * Supported devices: SwitchX, SwitchX2, Spectrum.
 *
 * @param[in]  handle         - SX-API handle
 * @param[in]  log_port       - logical port
 * @param[in/out] tc_config_p - pointer to array of 8 structures. the tc number
 *                              in the struct is an in param.
 * @param[in]  tc_config_cnt  - number of elements in the array
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
 * For Spectrum it is recommended to use sx_api_cos_port_ets_element_set.
 * Supported devices: SwitchX, SwitchX2, Spectrum.
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
 * Supported devices: SwitchX, SwitchX2, Spectrum.
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
 * Supported devices: SwitchX, SwitchX2, Spectrum.
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
 * Supported devices: SwitchX, SwitchX2, Spectrum.
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
 * Supported devices: SwitchX, SwitchX2, Spectrum.
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
 * Supported devices: SwitchX, SwitchX2, Spectrum.
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
 * Supported devices: SwitchX, SwitchX2.
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
 * Supported devices: SwitchX, SwitchX2.
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
 * Supported devices: SwitchX, SwitchX2.
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
 * Supported devices: SwitchX, SwitchX2.
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
 * Supported devices: SwitchX, SwitchX2.
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
 * Supported devices: SwitchX, SwitchX2.
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
 * Supported devices: SwitchX, SwitchX2.
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
 * Supported devices: SwitchX, SwitchX2.
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
 * Supported devices: SwitchX, SwitchX2.
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
 * Supported devices: SwitchX, SwitchX2.
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
 * Supported devices: SwitchX, SwitchX2.
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
 * This API sets the pool parameters.
 * User Pool#7 (Egress Pool#3) cannot be deleted as it is bound to CPU port buffers
 * User Pool#4 (Egress Pool#0) can be deleted when all MC buffers are unbinded from this pool
 * Supported devices: Spectrum
 *
 * @param[in] handle              - SX-API handle
 * @param[in] cmd                 - CMD SX_ACCESS_CMD_CREATE /SX_ACCESS_CMD_DESTROY/ SX_ACCESS_CMD_EDIT
 * @param[in] sx_cos_pool_attr    - Pool attributes pointer (Direction, Size (in Cells), Mode (dynamic/static))
 * @param[in/out] pool_id         - Pool ID pointer - use CMD SX_ACCESS_CMD_CREATE command will return the user pool_id
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_cos_shared_buff_pool_set(const sx_api_handle_t handle,
                                            const sx_access_cmd_t cmd,
                                            sx_cos_pool_attr_t   *sx_cos_pool_attr,
                                            uint32_t             *pool_id);

/**
 * This API gets the Pool parameters.
 * Supported devices: Spectrum
 *
 * @param[in] handle              - SX-API handle
 * @param[in] pool_id             - Pool ID
 * @param[out] sx_cos_pool_attr_p - Pool attributes (Direction, Size, Shared size, Mode (dynamic/static))
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_cos_shared_buff_pool_get(const sx_api_handle_t handle,
                                            const uint32_t        pool_id,
                                            sx_cos_pool_attr_t  * sx_cos_pool_attr_p);

/**
 * This API sets the port buffers size and threshold (Xon/Xoff) according to their types
 * With command SX_ACCESS_CMD_SET and attribute size non-zero, the API allocates the specific port buffer with attribute size (configures specific buffer entry)
 * With command SX_ACCESS_CMD_SET and attribute size zero, the API releases the size of specific port buffer (delete specific buffer entry)
 * With command SX_ACCESS_CMD_DELETE, the API releases all the port buffers configured on specific logical port (deletes all buffer entries on logical port)
 * Supported devices: Spectrum
 *
 * @param[in] handle                    - SX-API handle
 * @param[in] cmd                       - CMD SX_ACCESS_CMD_SET or SX_ACCESS_CMD_DELETE
 * @param[in] log_port                  - logical port ID
 * @param[in] port_buffer_attr_list_p   - pointer to list of port buffers attributes
 * @param[in] port_buffer_attr_cnt      - Number of port buffer attributes in the list
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_cos_port_buff_type_set(const sx_api_handle_t            handle,
                                          const sx_access_cmd_t            cmd,
                                          const sx_port_log_id_t           log_port,
                                          const sx_cos_port_buffer_attr_t *port_buffer_attr_list_p,
                                          const uint32_t                   port_buffer_attr_cnt);

/**
 * This API gets the port buffers size and threshold (Xon/Xoff) according to their types
 * Supported devices: Spectrum
 *
 * @param[in] handle                    - SX-API handle
 * @param[in] log_port                  - logical port ID
 * @param[out] port_buffer_attr_list_p  - pointer to list of port buffers attributes
 * @param[in/out] port_buffer_attr_cnt  - Number of port buffer attributes in the list
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_cos_port_buff_type_get(const sx_api_handle_t      handle,
                                          const sx_port_log_id_t     log_port,
                                          sx_cos_port_buffer_attr_t *port_buffer_attr_list_p,
                                          uint32_t                  *port_buffer_attr_cnt);

/**
 * This API sets the port shared buffers attributes according to their types
 * Supported devices: Spectrum
 *
 * @param[in] handle                            - SX-API handle
 * @param[in] cmd                               - CMD SX_ACCESS_CMD_SET or SX_ACCESS_CMD_DELETE
 * @param[in] log_port                          - logical port ID
 * @param[in] port_shared_buffer_attr_list_p    - pointer to list of port shared buffer attributes
 * @param[in] port_shared_buffer_attr_cnt       - Number of port shared buffer attributes in the list
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_cos_port_shared_buff_type_set(const sx_api_handle_t                   handle,
                                                 const sx_access_cmd_t                   cmd,
                                                 const sx_port_log_id_t                  log_port,
                                                 const sx_cos_port_shared_buffer_attr_t *port_shared_buffer_attr_list_p,
                                                 const uint32_t                          port_shared_buffer_attr_cnt);

/**
 * This API gets the port shared buffers attributes according to their types
 * Supported devices: Spectrum
 *
 * @param[in] handle                            - SX-API handle
 * @param[in] log_port                          - logical port ID
 * @param[out] port_shared_buffer_attr_list_p   - pointer to list of port shared buffer attributes
 * @param[in/out] port_shared_buffer_attr_cnt   - Number of port shared buffer attributes in the list
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_cos_port_shared_buff_type_get(const sx_api_handle_t             handle,
                                                 const sx_port_log_id_t            log_port,
                                                 sx_cos_port_shared_buffer_attr_t *port_shared_buffer_attr_list_p,
                                                 uint32_t                         *port_shared_buffer_attr_cnt);

/**
 * This API gets the buffer status.
 * Supported devices: Spectrum
 *
 * @param[in] handle    - SX-API handle
 * @param[out] status   - the buffer global status
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_cos_buff_status_get(const sx_api_handle_t handle,
                                       sx_buffer_status_t   *status);

/**
 * This API returns the list of initialized pools
 * Supported devices: SwitchEN
 *
 * @param[in] handle    - SX-API handle
 * @param[in/out] pool_cnt   - the number of pools in the list
 * @param[out] pool_list_p - list of pool ids
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_cos_pools_list_get(const sx_api_handle_t handle,
                                      uint32_t             *pool_cnt,
                                      sx_cos_pool_id_t     *pool_list_p);

/**
 * This API gets the port buffers occupancy parameters.
 * Supported devices: Spectrum
 *
 * @param[in] handle                 - SX-API handle
 * @param[in] cmd                    - CMD SX_ACCESS_CMD_READ /SX_ACCESS_CMD_READ_CLEAR
 * @param[in] statistic_param_list_p - Pointer to a list of statistics input structure (Port, PG, Direction)
 * @param[in] statistic_cnt          - Number of input parameters in the list
 * @param[out] usage_list_p          - Pointer to a list of usage params
 * @param[in/out] usage_cnt          - Number of output parameters in the list (if zero - number of elements will be returned)
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_cos_port_buff_type_statistic_get(const sx_api_handle_t                   handle,
                                                    const sx_access_cmd_t                   cmd,
                                                    const sx_port_statistic_usage_params_t *statistic_param_list_p,
                                                    const uint32_t                          statistics_cnt,
                                                    sx_port_occupancy_statistics_t        * usage_list_p,
                                                    uint32_t                              * usage_cnt);

/**
 * This API gets the port pools occupancy parameters.
 * Supported devices: Spectrum
 *
 * @param[in] handle             - SX-API handle
 * @param[in] cmd                - SX_ACCESS_CMD_READ /SX_ACCESS_CMD_READ_CLEAR
 * @param[in] pool_id_list_p     - Pointer to a list of Pool IDs (size - in units of cells)
 * @param[in] pool_id_cnt        - Number of parameters in the list
 * @param[out] usage_list_p      - Pointer to a list of usage params
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_cos_pool_statistic_get(const sx_api_handle_t               handle,
                                          const sx_access_cmd_t               cmd,
                                          const sx_cos_pool_id_t             *pool_id_list_p,
                                          const uint32_t                      pool_id_cnt,
                                          sx_cos_pool_occupancy_statistics_t *usage_list_p);

/**
 * This function sets the port default color value. Used for "trust port"
 * configuration or for packets with the relevant priority field is unavailable.
 * Not supported per VPORT.
 * Supported devices: Spectrum.
 *
 * @param[in]  handle      - SX-API handle
 * @param[in]  log_port    - logical port ID
 * @param[in]  color       - color
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_port_default_color_set(const sx_api_handle_t  handle,
                                              const sx_port_log_id_t log_port,
                                              const sx_cos_color_t   color);

/**
 * This function retrieves the default port color value.
 * Supported devices: Spectrum.
 * Not supported per VPORT.
 *
 * @param[in]  handle     - SX-API handle
 * @param[in]  log_port   - logical port ID
 * @param[out] color_p    - color
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_port_default_color_get(const sx_api_handle_t  handle,
                                              const sx_port_log_id_t log_port,
                                              sx_cos_color_t        *color_p);

/**
 * This API sets the default PCP,DEI for arriving untagged packets.
 * Not supported per VPORT.
 * In SwitchX the default switch prio will be used as default PCP.
 * See sx_api_cos_port_default_prio_set.
 * Supported devices: Spectrum.
 *
 * @param[in]  handle      - SX-API handle
 * @param[in]  log_port    - logical port ID
 * @param[in] pcp_dei      - PCP,DEI
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_port_default_pcpdei_set(const sx_api_handle_t  handle,
                                               const sx_port_log_id_t log_port,
                                               const sx_cos_pcp_dei_t pcp_dei);

/**
 * This function retrieves the default PCP,DEI for arriving untagged packets.
 * Supported devices: Spectrum.
 * Not supported per VPORT.
 *
 * @param[in]  handle     - SX-API handle
 * @param[in]  log_port   - logical port ID
 * @param[out] pcp_dei_p  - PCP,DEI
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_port_default_pcpdei_get(const sx_api_handle_t  handle,
                                               const sx_port_log_id_t log_port,
                                               sx_cos_pcp_dei_t      *pcp_dei_p);

/**
 * This function sets the mapping from PCP,DEI to switch-priority and color.
 * This table is used when the port trust mode is set to 'trust L2'.
 * In SwitchX the mapping from PCP to switch prio is PCP[i]->Switch prio[i].
 * Supported devices: Spectrum.
 *
 * @param[in] handle   - SX-API handle
 * @param[in] log_port - logical port ID
 * @param[in] pcp_dei_p  - a list of PCP's and DEI's
 * @param[in] switch_priority - a list of switch priorities
 * @param[in] element_cnt - num of elements in PCP, DEI and Switch Prio lists
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_port_pcpdei_to_prio_set(const sx_api_handle_t          handle,
                                               const sx_port_log_id_t         log_port,
                                               const sx_cos_pcp_dei_t        *pcp_dei_p,
                                               const sx_cos_priority_color_t *switch_priority_color_p,
                                               const uint32_t                 element_cnt);

/**
 * This function retrieves the mapping from PCP,DEI to switch-priority and color.
 * Supported devices: Spectrum.
 *
 * @param[in] handle   - SX-API handle
 * @param[in] log_port - logical port ID
 * @param[out] pcp_dei_p  - a list of PCP's and DEI's
 * @param[out] switch_priority_color_p - a list of switch priorities and colors
 * @param[out] element_cnt_p - num of elements in PCP, DEI and Switch Prio lists
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_port_pcpdei_to_prio_get(const sx_api_handle_t    handle,
                                               const sx_port_log_id_t   log_port,
                                               sx_cos_pcp_dei_t        *pcp_dei_p,
                                               sx_cos_priority_color_t *switch_priority_color_p,
                                               uint32_t                *element_cnt_p);

/**
 * This function sets the mapping from switch-priority to IEEE priority.
 * This IEEE priority value is used in the switch for several functions:
 * pause flow control, per priority counters and QCN.
 * The device maps the switch-priority into IEEE priority value using
 * device global Switch Priority to IEEE Priority Table (not per port).
 *
 * Supported devices: Spectrum.
 *
 * @param[in] handle          - SX-API handle
 * @param[in] switch_priority_p - a list of switch priorities
 * @param[in] ieee_priority_p   - a list of IEEE priorities
 * @param[in] element_cnt - num of elements in switch priorities and ieee priorities lists
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_prio_to_ieeeprio_set(const sx_api_handle_t     handle,
                                            const sx_cos_priority_t  *switch_priority_p,
                                            const sx_cos_ieee_prio_t *ieee_priority_p,
                                            const uint32_t            element_cnt);

/**
 * This function retrieves the mapping from switch-priority to IEEE priority.
 * Supported devices: Spectrum.
 *
 * @param[in] handle             - SX-API handle
 * @param[out] switch_priority_p - switch priorities list
 * @param[out] ieee_priority_p   - IEEE priorities list
 * @param[out] element_cnt_p   - num of elements in switch priorities and ieee priorities lists
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_prio_to_ieeeprio_get(const sx_api_handle_t handle,
                                            sx_cos_priority_t    *switch_priority_p,
                                            sx_cos_ieee_prio_t   *ieee_priority_p,
                                            uint32_t             *element_cnt_p);

/**
 * This function sets the mapping from EXP to switch-priority, color and ECN value.
 * This table is used for MPLS packets when the port trust mode is set to 'L3'
 * Supported devices: Spectrum.
 *
 * @param[in] handle   - SX-API handle
 * @param[in] log_port - logical port ID
 * @param[in] exp_p           - a list of EXP's
 * @param[in] switch_priority_color_p - a list of switch priorities and colors
 * @param[in] ecn_p    - a list of ECN's
 * @param[in] element_cnt - num of elements in EXP's, ECN's and switch priorities lists
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_port_exp_to_prio_set(const sx_api_handle_t          handle,
                                            const sx_port_log_id_t         log_port,
                                            const sx_cos_exp_t            *exp_p,
                                            const sx_cos_priority_color_t *switch_priority_color_p,
                                            const sx_cos_ecn_t            *ecn_p,
                                            const uint32_t                 element_cnt);

/**
 * This function retrieves the mapping from EXP to switch-priority, color and ECN value.
 * Supported devices: Spectrum.
 *
 * @param[in] handle   - SX-API handle
 * @param[in] log_port - logical port ID
 * @param[out] exp_p           - a list of EXP's
 * @param[out] switch_priority_color_p -  an array of switch priorities and colors
 * @param[out] ecn_p           - a list of ECN's
 * @param[out] element_cnt_p - num of elements in EXP's and switch priorities lists
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_port_exp_to_prio_get(const sx_api_handle_t    handle,
                                            const sx_port_log_id_t   log_port,
                                            sx_cos_exp_t            *exp_p,
                                            sx_cos_priority_color_t *switch_priority_color_p,
                                            sx_cos_ecn_t            *ecn_p,
                                            uint32_t                *element_cnt_p);

/**
 * This function sets the mapping from DSCP to switch-priority and color.
 * This table is used when the port trust mode is set to 'L3'.
 * The mapping from DSCP to switch prio is per port only in Spectrum.
 * Supported devices: Spectrum.
 *
 * @param[in] handle                - SX-API handle
 * @param[in] log_port              - logical port ID
 * @param[in] dscp_p                - a list of DSCP's
 * @param[in] switch_priority_color - a list of switch priorities and colors
 * @param[in] element_cnt           - num of elements in DSCP's and switch priorities lists
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_port_dscp_to_prio_set(const sx_api_handle_t          handle,
                                             const sx_port_log_id_t         log_port,
                                             const sx_cos_dscp_t           *dscp_p,
                                             const sx_cos_priority_color_t *switch_priority_color_p,
                                             const uint32_t                 element_cnt);

/**
 * This function retrieves the mapping from DSCP to switch-priority and color.
 * Supported devices: Spectrum.
 *
 * @param[in] handle               - SX-API handle
 * @param[in] log_port             - logical port ID
 * @param[out] dscp_p              - a list of DSCP's
 * @param[out] switch_priority_color_p   - a list of switch priorities and colors
 * @param[out] element_cnt_p  - num of elements in DSCP's and switch priorities lists
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_port_dscp_to_prio_get(const sx_api_handle_t    handle,
                                             const sx_port_log_id_t   log_port,
                                             sx_cos_dscp_t           *dscp_p,
                                             sx_cos_priority_color_t *switch_priority_color_p,
                                             uint32_t                *element_cnt_p);

/**
 * This function defines rewrite enable option setting of PCP, DEI, DSCP and EXP
 * bits in packet header. The values of rewriting are defined by mapping
 * in the following functions.
 * Supported devices: Spectrum.
 *
 * @param[in] handle  - SX-API handle
 * @param[in] log_port - logical port ID
 * @param[in] rewrite  - should rewrite PCP/DEI, DSCP, EXP
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_port_rewrite_enable_set(const sx_api_handle_t         handle,
                                               const sx_port_log_id_t        log_port,
                                               const sx_cos_rewrite_enable_t rewrite);

/**
 * This function retrieves rewrite enable option setting of PCP, DEI, DSCP and EXP
 * bits in packet header.
 * Supported devices: Spectrum.
 *
 * @param[in] handle    - SX-API handle
 * @param[in] log_port   - logical port ID
 * @param[out] rewrite_p - should rewrite PCP/DEI, DSCP, EXP
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_port_rewrite_enable_get(const sx_api_handle_t    handle,
                                               const sx_port_log_id_t   log_port,
                                               sx_cos_rewrite_enable_t *rewrite_p);

/**
 * This function defines the mapping from switch-priority, color to PCP, DEI for PCP and DEI rewrite,
 * in packet header.
 * The mapping will change the PCP, DEI values only if PCP, DEI rewrite was enabled in
 * sx_api_cos_port_rewrite_enable_set
 * Supported devices: Spectrum.
 *
 * @param[in] handle    - SX-API handle
 * @param[in] log_port - logical port ID
 * @param[in] switch_priority_color_p   - a list of switch priorities, and colors
 * @param[in] pcp_dei_p   - a list of PCP's and DEI's
 * @param[in] element_cnt - switch priorities and PCP's, DEI's lists elements count
 *
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_port_prio_to_pcpdei_rewrite_set(const sx_api_handle_t          handle,
                                                       const sx_port_log_id_t         log_port,
                                                       const sx_cos_priority_color_t *switch_priority_color_p,
                                                       const sx_cos_pcp_dei_t        *pcp_dei_p,
                                                       const uint32_t                 element_cnt);


/**
 * This function retrieves the mapping from switch-priority, color to PCP, DEI for PCP and DEI
 * rewrite, in packet header.
 * Supported devices: Spectrum.
 *
 * @param[in] handle    - SX-API handle
 * @param[in] log_port   - logical port ID
 * @param[out] switch_priority_color_p - a list of switch priorities and colors
 * @param[out] pcp_dei_p      - a list of PCP's and DEI's
 * @param[out] element_cnt_p - switch priorities and DSCP lists elements count
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_port_prio_to_pcpdei_rewrite_get(const sx_api_handle_t    handle,
                                                       const sx_port_log_id_t   log_port,
                                                       sx_cos_priority_color_t *switch_priority_color_p,
                                                       sx_cos_pcp_dei_t        *pcp_dei_p,
                                                       uint32_t                *element_cnt_p);

/**
 * This function defines the mapping from switch-priority, color to DSCP, for DSCP rewrite,
 * in packet header.
 * The mapping will change the DSCP values only if DSCP rewrite was enabled in
 * sx_api_cos_port_rewrite_enable_set
 * Supported devices: Spectrum.
 *
 * @param[in] handle    - SX-API handle
 * @param[in] log_port - logical port ID
 * @param[in] switch_priority_color_p   - list of switch priorities, and colors
 * @param[in] dscp_p   - a list of DSCP's
 * @param[in] element_cnt - switch priorities and DSCP's lists elements count
 *
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_port_prio_to_dscp_rewrite_set(const sx_api_handle_t          handle,
                                                     const sx_port_log_id_t         log_port,
                                                     const sx_cos_priority_color_t *switch_priority_color_p,
                                                     const sx_cos_dscp_t           *dscp_p,
                                                     const uint32_t                 element_cnt);

/**
 * This function retrieves the mapping from switch-priority, color to DSCP, for DSCP
 * rewrite, in packet header.
 * Supported devices: Spectrum.
 *
 * @param[in] handle    - SX-API handle
 * @param[in] log_port   - logical port ID
 * @param[out] switch_priority_color_p - a list of switch priorities and colors
 * @param[out] dscp_p      - a list of DSCP's
 * @param[out] element_cnt_p - switch priorities and DSCP lists elements count
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_port_prio_to_dscp_rewrite_get(const sx_api_handle_t    handle,
                                                     const sx_port_log_id_t   log_port,
                                                     sx_cos_priority_color_t *switch_priority_color_p,
                                                     sx_cos_dscp_t           *dscp_p,
                                                     uint32_t                *element_cnt_p);

/**
 * This function defines the mapping from switch-priority, color and ECN to EXP, for EXP rewrite,
 * in packet header.
 * The mapping will change the EXP values only if EXP rewrite was enabled in
 * sx_api_cos_port_rewrite_enable_set
 * Supported devices: Spectrum.
 *
 * @param[in] handle                  - SX-API handle
 * @param[in] log_port                - logical port ID
 * @param[in] switch_priority_color_p - list of switch priorities, colors
 * @param[in] ecn_p                   - list of ECN's
 * @param[in] exp_p                   - list of EXP's
 * @param[in] element_cnt             - switch priorities, EXP's and ECN's lists elements count
 *
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_port_prio_to_exp_rewrite_set(const sx_api_handle_t          handle,
                                                    const sx_port_log_id_t         log_port,
                                                    const sx_cos_priority_color_t *switch_priority_color_p,
                                                    const sx_cos_ecn_t            *ecn_p,
                                                    const sx_cos_exp_t            *exp_p,
                                                    const uint32_t                 element_cnt);

/**
 * This function retrieves rewriting of EXP bits setting.
 * Supported devices: Spectrum.
 *
 * @param[in] handle                       - SX-API handle
 * @param[in] log_port                     - logical port ID
 * @param[out] switch_priority_color_ecn_p - a list of switch priorities, colors
 * @param[out] ecn_p                       - a list of ECN's
 * @param[out] exp_p                       - a list of EXP's
 * @param[out] element_cnt_p               - switch priorities, ECN's and EXP's lists elements count
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_port_prio_to_exp_rewrite_get(const sx_api_handle_t    handle,
                                                    const sx_port_log_id_t   log_port,
                                                    sx_cos_priority_color_t *switch_priority_color_p,
                                                    sx_cos_ecn_t            *ecn_p,
                                                    sx_cos_exp_t            *exp_p,
                                                    uint32_t                *element_cnt_p);

/**
 * This function binds a traffic class (TC) to a TC queue and group,
 * and sets shapers and rate-based ECN threshold.
 * Supported devices: Spectrum.
 *
 * @param[in] handle            - SX-API handle
 * @param[in] cmd - SX_ACCESS_CMD_CREATE: create a queuing structure
 *                  SX_ACCESS_CMD_ADD: add an element to an existing queuing structure
 *                  SX_ACCESS_CMD_EDIT: edit an element in an existing queuing structure
 *                  SX_ACCESS_CMD_DESTROY: destory the queuing structure (return to default)
 * @param[in] log_port          - egress port ID
 * @param[in] ets_element       - ETS element array
 * @param[in] ets_element_cnt - num of ETS elements
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_port_ets_element_set(const sx_api_handle_t              handle,
                                            const sx_access_cmd_t              cmd,
                                            const sx_port_log_id_t             log_port,
                                            const sx_cos_ets_element_config_t *ets_element_p,
                                            const uint32_t                     element_cnt);

/**
 * This function retrieves all elements of the queuing system.
 * Supported devices: Spectrum.
 *
 * @param[in]  handle             - SX-API handle
 * @param[in]  log_port           - egress port ID
 * @param[out]  ets_element       - ETS element array
 * @param[in/out] ets_element_cnt - num of ETS elements
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_port_ets_element_get(const sx_api_handle_t        handle,
                                            const sx_port_log_id_t       log_port,
                                            sx_cos_ets_element_config_t *ets_element_p,
                                            uint32_t                    *element_cnt_p);

/**
 * This function sets the port MC awareness mode.
 * If mc_aware==TRUE then the MC traffic will be mapped to the higher TC's (8-15)
 * and the UC traffic will be mapped to the lower TC's (0-7).
 * If there is a mapping configured to TC 8-15 the function will return SX_STATUS_ERROR
 * Supported devices: Spectrum.
 *
 * @param[in] handle   - SX-API handle
 * @param[in] log_port - egress port ID
 * @param[in] mc_aware - MC aware TC mode
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_port_tc_mcaware_set(const sx_api_handle_t  handle,
                                           const sx_port_log_id_t log_port,
                                           const boolean_t        mc_aware);

/**
 * This function retrieves the port MC awareness mode.
 * Supported devices: Spectrum.
 *
 * @param[in] handle    - SX-API handle
 * @param[in] log_port - egress port ID
 * @param[out] mc_aware   - MC aware TC mode
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_cos_port_tc_mcaware_get(const sx_api_handle_t  handle,
                                           const sx_port_log_id_t log_port,
                                           boolean_t             *mc_aware_p);


#endif /* __SX_API_COS_H__ */
