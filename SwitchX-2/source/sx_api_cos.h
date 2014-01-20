/*
 *                  - Mellanox Proprietary -
 *
 *  Copyright (C) January 2010 , Mellanox Technologies Ltd.  ALL RIGHTS RESERVED.
 *
 *  Except as specifically permitted herein , no portion of the information ,
 *  including but not limited to object code and source code , may be reproduced ,
 *  modified , distributed , republished or otherwise exploited in any form or by
 *  any means for any purpose without the prior written permission of Mellanox
 *  Technologies Ltd. Use of software subject to the terms and conditions
 *  detailed in the file "LICENSE.txt".
 */

#ifndef __SX_API_COS_H__
#define __SX_API_COS_H__

#include <sx/sdk/sx_api.h>


/************************************************
 *  API functions
 ***********************************************/

/**
 * This function sets the log verbosity level of COS MODULE
 * @param[in]     handle                   - SX-API handle
 * @param[in]     cmd                      - SET / GET
 * @param[in]     verbosity_target         - set get verbosity of : API / MODULE / BOTH
 * @param[in,out] module_verbosity_level_p - COS module verbosity level
 * @param[in,out] api_verbosity_level_p    - COS API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t
sx_api_cos_log_verbosity_level_set(
		const    sx_api_handle_t            handle,
		const    sx_access_cmd_t            cmd,
		const    sx_log_verbosity_target_t  verbosity_target,
		  sx_verbosity_level_t      *module_verbosity_level_p,
		  sx_verbosity_level_t      *api_verbosity_level_p
		);

/**
 * This function sets the port default priority value.
 * Packet which arrives to 'port_log_id' port without a priority
 * will be handled according to 'port_priority' value.
 *
 * @param[in] handle       - SX-API handle
 * @param[in] port_log_id  - logical port id
 * @param[in] priority     - port priority [0..7 , default is 0]
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_MEMORY_ERROR error handling memory
 */
sx_status_t
sx_api_cos_port_default_prio_set(
		const sx_api_handle_t   handle,
		const sx_port_log_id_t  port_log_id,
		const sx_cos_priority_t priority
		);

/**
 * This function get the port default priority value.
 *
 * @param[in]  handle          - SX-API handle
 * @param[in]  port_log_id     - logical port id
 * @param[out] priority_p      - port priority [0..7]
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t
sx_api_cos_port_default_prio_get(
		const sx_api_handle_t     handle,
		const sx_port_log_id_t    port_log_id,
		  sx_cos_priority_t *priority_p
		);

/**
 * This function sets the port ingress priority map values.
 * Packet which arrives to 'port_log_id' with 'source_priority' priority
 * Will be handled according to 'mapped_priority' priority
 *
 * @param[in] handle               - SX-API handle
 * @param[in] port_log_id          - logical port id
 * @param[in] source_priority      - original priority [0..7]
 * @param[in] regenerated_priority - regenerated priority [0..7]
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_MEMORY_ERROR error handling memory
 */
sx_status_t
sx_api_cos_port_prio_ingress_regen_set(
		const sx_api_handle_t   handle,
		const sx_port_log_id_t  port_log_id,
		const sx_cos_priority_t source_priority,
		const sx_cos_priority_t regenerated_priority
		);

/**
 * This function retrieves the port ingress priority regen values.
 *
 * @param[in]  handle            - SX-API handle
 * @param[in]  port_log_id       - logical port id
 * @param[in]  source_priority   - original priority [0..7]
 * @param[out] regen_priority_p  - regenerated priority [0..7]
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t
sx_api_cos_port_prio_ingress_regen_get(
		const  sx_api_handle_t    handle,
		const  sx_port_log_id_t   port_log_id,
		const  sx_cos_priority_t  source_priority,
		  sx_cos_priority_t *regen_priority_p
		);

/**
 *  This function adds or deletes a priority from a Traffic
 *  Class. When a priority is added to a TC , it is automatically
 *  re-mapped from its previous allocation. When a priority is
 *  deleted from a TC , it is reallocated according to default
 *  settings.
 *
 *  Each packet has an assign priority. The priority of the packet
 *  is mapped to one of eight traffic classes
 * (egress queue) according to prio -> traffic class map
 *  Each packet is dequeued on the egress port based on its
 *  traffic class
 *
 *
 *  Note: Multiple priorities can be mapped to a
 *  single TC. Default settings :
 *
 *  Priority 0 -> Traffic Class 0;
 *  Priority 1 -> Traffic Class 0;
 *  Priority 2 -> Traffic Class 1;
 *  Priority 3 -> Traffic Class 1 ;
 *  Priority 4 -> Traffic Class 2;
 *  Priority 5 -> Traffic Class 2;
 *  Priority 6 -> Traffic Class 3;
 *  Priority 7 -> Traffic Class 3;
 *
 * @param[in] handle        - SX-API handle
 * @param[in] cmd    - Add/ Delete
 * @param[in] port_log_id   - logical port id (egress port)
 * @param[in] priority      - priority
 * @param[in] traffic_class - traffic class 
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_MEMORY_ERROR error handling memory
 * @return SX_STATUS_CMD_ERROR if unsupported command is requested
 */
sx_status_t
sx_api_cos_port_tc_prio_map_set(
		const sx_api_handle_t        handle,
		const sx_access_cmd_t               cmd,
		const sx_port_log_id_t       port_log_id,
		const sx_cos_priority_t      priority,
		const sx_cos_traffic_class_t traffic_class
		);

/**
 *  This function retrieves the Traffic class of a specific
 *  priority.
 *
 * @param[in]  handle          - SX-API handle
 * @param[in]  port_log_id     - logical port id
 * @param[in]  priority        - priority
 * @param[out] traffic_class_p - traffic class
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t
sx_api_cos_port_tc_prio_map_get(
		const sx_api_handle_t          handle,
		const sx_port_log_id_t         port_log_id,
		const sx_cos_priority_t        priority,
		  sx_cos_traffic_class_t *traffic_class_p
		);

/**
 * This function sets the port trust level value. The Switch X assigns the user priority based on the following modes:
 * Trust port user priority - ignore packets priority and assign
 * priority based on the port configuration Trust packet user
 * priority - tagged L2 packets are assigned with packets
 * priority, untagged packets are assigned with port's priority
 * Trust DSCP - IP packets are assigned with a priority based on
 * the DSCP to UP mapping, Non IP packets are assigned with
 * port's priority Trust both - IP packets are assigned with a
 * priority based on the DSCP to UP mapping, else tagged L2
 * packets are assigned with packets priority, untagged packets
 * are assigned with port's priority
 *
 * @param[in] handle      - SX-API handle
 * @param[in] port_log_id - logical port id
 * @param[in] trust_level - trust level  [0 - trust port user priority,
 *                                        1 - trust packet user priority ,
 *                                        2 - trust DSCP ,
 *                                        3 - trust both]
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_MEMORY_ERROR error handling memory
 */
sx_status_t
sx_api_cos_port_trust_set(
		const sx_api_handle_t      handle,
		const sx_port_log_id_t     port_log_id,
		const sx_cos_trust_level_t trust_level
		);

/**
 * This function get the port trust level value.
 *
 * @param[in]  handle        - SX-API handle
 * @param[in]  port_log_id   - logical port id
 * @param[out] trust_level_p - trust level  [0 - trust port ,
 *                                           1 - trust user priority ,
 *                                           2 - trust DSCP ,
 *                                           3 - trust both]
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t
sx_api_cos_port_trust_get(
		const sx_api_handle_t        handle,
		const sx_port_log_id_t       port_log_id,
		  sx_cos_trust_level_t *trust_level_p
		);

/**
 *
 * This function sets the map between dscp and port priority.
 * This table is used when the port trust mode is set to 'trust DSCP'
 *
 * @param[in] handle     - SX-API handle
 * @param[in] dscp       - DSCP [0..63]
 * @param[in] priority   - priority [0..7]
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t
sx_api_cos_ip_dscp_to_prio_set(
		const sx_api_handle_t   handle,
		const sx_cos_dscp_t     dscp,
		const sx_cos_priority_t priority
		);

/**
 *
 * This function get the map between DSCP and priority
 *
 * @param[in]  handle           - SX-API handle
 * @param[in]  dscp             - DSCP [0..63]
 * @param[out] priority_p       - priority [0..7]
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t
sx_api_cos_ip_dscp_to_prio_get(
		const  sx_api_handle_t    handle,
		const  sx_cos_dscp_t      dscp,
		  sx_cos_priority_t *priority_p
		);

/**
 *
 * This function retrieves the global HW cos capabilities.
 *
 * @param[in]   handle                    - SX-API handle
 * @param[out]  cos_capabilities_p        - cos capabilities struct :
 * [max_policers_per_port - maximum number of policers bound to a single port]
 * [max_policers_global   - maximum number of active global
 * policers         ]
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t
sx_api_cos_capabilities_get(
		const sx_api_handle_t         handle,
		  sx_cos_capabilities_t *cos_capabilities_p
		);


/**
 * This function binds a traffic class to a traffic class group,
 * Sets MAX bandwidth allocation (%),
 * Sets MAX band width allowed for the traffic class
 *
 * @param[in]  handle          - SX-API handle
 * @param[in]  port_log_id     - logical port
 * @param[in]  tc_config_p     - pointer to array of TC structures
 * @param[in]  tc_config_num   - number of elements in the array
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * 	   SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * 	   SX_STATUS_ERROR general error
 */
sx_status_t
sx_api_cos_port_ets_set(
		const sx_api_handle_t            handle,
		const sx_port_log_id_t           port_log_id,
		const sx_cos_tc_config_params_t *tc_config_p,
		const uint8_t                    tc_config_num
		);

/**
 * This function retrieve the traffic class group for traffic class.
 *
 * @param[in]  handle        - SX-API handle
 * @param[in]  port_log_id   - logical port
 * @param[in]  tc_config_num - number of elements in the array
 * @param[out] tc_config_p   - pointer to array of 8 structures
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * 	   SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * 	   SX_STATUS_ERROR general error
 */
sx_status_t
sx_api_cos_port_ets_get(
		const  sx_api_handle_t            handle,
		const  sx_port_log_id_t           port_log_id,
		const uint8_t                     tc_config_num,
		  sx_cos_tc_config_params_t *tc_config_p
		);


/**
* This function sets the ETS general configuration of log port
*
* @param[in] handle        - SX-API handle
* @param[in] port_log_id   - logical port id
* @param[in] port_config_p - pointer to port ETS structure
*
* @return SX_STATUS_SUCCESS if operation completes successfully
*     SX_STATUS_PARAM_ERROR if any input parameters is invalid
*     SX_STATUS_ERROR general error
*/
sx_status_t
sx_api_cos_port_ets_general_configuration_set(
                const sx_api_handle_t      handle ,
                const sx_port_log_id_t     port_log_id ,
				const sx_cos_port_ets_gen_config_params_t  *port_config_p
                );


/**
* This function retrieves the ETS general configuration of log port
*
* @param[in] handle         - SX-API handle
* @param[in] port_log_id    - logical port id
* @param[out] port_config_p - pointer to port ETS structure
*
* @return SX_STATUS_SUCCESS if operation completes successfully
*     SX_STATUS_PARAM_ERROR if any input parameters is invalid
*     SX_STATUS_ERROR general error
*/
sx_status_t
sx_api_cos_port_ets_general_configuration_get(
		const sx_api_handle_t      handle,
		const sx_port_log_id_t     port_log_id,
		  sx_cos_port_ets_gen_config_params_t  *port_config_p
		);


/**
 * This API Sets the Port's Buffer Management Control in the SDK.
 *
 * Note:
 * Buffers 0 - 7 allocation is under the below restrictions:
 * On global pause mode, only a single buffer (buffer 1) can be configured.
 * All traffic will go to buffer 1
 * Buffer 0 must be used for lossy traffic (no Pause should be used).
 *
 * @param[in] handle          - SX-API handle
 * @param[in] cmd      - CMD SX_ACCESS_CMD_SET or SX_ACCESS_CMD_DELETE.
 * @param[in] log_port        - Logical Port ID.
 * @param[in] xof_timer_value - SX Pause frame: Pause timer.
 * @param[in] xof_refresh     - send pause frame interval.
 * @param[out] buffer_list    - Array of 8 buffer parameters structures.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_CMD_UNSUPPORTED command is not supported
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if the total buffer sizes exceeds the max for this port
 */
sx_status_t
sx_api_cos_port_buff_set(
		const sx_api_handle_t handle,
		const sx_access_cmd_t cmd,
		const sx_port_log_id_t log_port,
		const sx_cos_timer_value_t xof_timer_value,
		const sx_cos_timer_value_t xof_refresh,
		const sx_cos_port_buff_params_t *buffer_list_p
		);

/**
 * This API Retrieves the Port's Buffer Management Control from the SDK.
 *
 * @param[in]  handle            - SX-API handle
 * @param[in]  log_port          - Logical Port ID.
 * @param[out] xof_timer_value   - Pause timer field.
 * @param[out] xof_refresh       - send pause frame interval.
 * @param[out] total_buffer_size - Total packet buffer array available for the port..
 * @param[out] buffer_list       - Array of 8 buffer parameters structures.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t
sx_api_cos_port_buff_get(
		const sx_api_handle_t handle,
		const sx_port_log_id_t log_port,
		  sx_cos_timer_value_t *xof_timer_value_p,
		  sx_cos_timer_value_t *xof_refresh_p,
		  sx_cos_port_buff_size_t *total_buffer_size_p,
		  sx_cos_port_buff_params_t *buffer_list_p
		);

/**
 * This API Sets the Port's Priority to Buffer Map in the SDK.
 *
 * Note:
 * Untagged frames must use a buffer used by one of the prios.
 * SwitchX can not allocate a buffer for untagged frames only.
 *
 * @param[in] handle          - SX-API handle
 * @param[in] cmd      - access command SX_ACCESS_CMD_SET or SX_ACCESS_CMD_DELETE.
 * @param[in] log_port        - Logical Port ID.
 * @param[in] prio_to_buff    - Array of 8 buffers, this is the mapping between a priority and the buffer.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_CMD_UNSUPPORTED command is not supported
 */
sx_status_t
sx_api_cos_port_buff_map_set(
		const sx_api_handle_t handle,
		const sx_access_cmd_t cmd,
		const sx_port_log_id_t log_port,
		sx_cos_port_buff_t *prio_to_buff_p
		);

/**
 * This API Retrieves the Port's Priority to Buffer Mapping from the SDK.
 *
 * @param[in] handle          - SX-API handle
 * @param[in] log_port        - Logical Port ID.
 * @param[out] prio_to_buff   - Array of 8 buffers, this is the mapping between a priority and the buffer.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t
sx_api_cos_port_buff_map_get(
		const sx_api_handle_t handle,
		const sx_port_log_id_t log_port,
		  sx_cos_port_buff_t *prio_to_buff_p
		);

#endif /* __SX_API_COS_H__ */
