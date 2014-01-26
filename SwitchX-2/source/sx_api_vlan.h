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

#ifndef __SX_API_VLAN_H__
#define __SX_API_VLAN_H__

#include <sx/sdk/sx_api.h>


/************************************************
 *  API functions
 ***********************************************/

/**
 * This function sets the log verbosity level of VLAN MODULE
 * @param[in]     handle                   - SX-API handle
 * @param[in]     cmd                      - SET / GET
 * @param[in]     verbosity_target         - set get verbosity of : API / MODULE / BOTH
 * @param[in,out] module_verbosity_level_p - VLAN module verbosity level
 * @param[in,out] api_verbosity_level_p    - VLAN API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 *         SX_STATUS_PARAM_ERROR if any input parameters is invalid
 *         SX_STATUS_ERROR general error
 */
sx_status_t sx_api_vlan_log_verbosity_level_set(
                                               const sx_api_handle_t            handle ,
                                               const sx_access_cmd_t            cmd ,
                                               const sx_log_verbosity_target_t  verbosity_target,
                                               sx_verbosity_level_t      *module_verbosity_level_p,
                                               sx_verbosity_level_t      *api_verbosity_level_p);

/**
 *  This function sets the VLAN member ports.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - ADD / DELETE / DELETE_ALL
 * @param[in] swid - virtual switch partition id
 * @param[in] vid - VLAN id
 * @param[in] port_num - number of ports in a port list
 * @param[in] vlan_port_list_p - a pointer to array of port list
 *       structure. Each port in the list has its logical port
 *       number and the egress filter mode (tagged/ untagged and
 *       priority tagged member). In case of "delete all" command,
 *       port_num = 0, vlan_port_list_p = NULL are applicable
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ACCESS_CMD_UNSUPPORTED if unsupported command is requested
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO if SxD driver function returns fail
 * @return SX_STATUS_NO_MEMORY if problems with memory allocation occurs
 * @return SX_STATUS_NO_RESOURCES if pool cannot provide object
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 */
sx_status_t sx_api_vlan_ports_set(
                                 const sx_api_handle_t     handle,
                                 const sx_access_cmd_t     cmd,
                                 const sx_swid_t           swid,
                                 const sx_vid_t            vid,
                                 const sx_vlan_ports_t *   vlan_port_list_p,
                                 const uint16_t            port_cnt);


/**
*  This function sets the VLANs list to a port in a single
*  command.
* @param[in] handle - SX-API handle
* @param[in] cmd -  SX_ACCESS_CMD_ADD - Add list of VLANs to port
*                          SX_ACCESS_CMD_DELETE - Remove a list VLANs from port
*
* @param[in] swid - virtual switch partition id
* @param[in] log_port - logical port
* @param[in] vlan_list_p - pointer to a VLANs list
* @param[in] vlan_cnt - size of VLANs list 
*  
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_CMD_UNSUPPORTED if unsupported command is requested
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO if SxD driver function returns fail
 * @return SX_STATUS_NO_MEMORY if problems with memory allocation occurs
 * @return SX_STATUS_NO_RESOURCES if pool cannot provide object
 * @return SX_STATUS_ERROR if unexpected behavior occurs
*/
sx_status_t sx_api_vlan_port_multi_vlan_set(
                                           const sx_api_handle_t   handle,
                                           const sx_access_cmd_t   cmd,
                                           const sx_port_log_id_t  log_port,
                                           const sx_port_vlans_t*  vlan_list_p,
                                           const uint16_t          vlan_cnt);

/**
 *This function sets the priority tagged attribute per port.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] log_port - logical port
 * @param[in] untagged_prio_state - untagged packets will be sent
 * 	          priority-tagged or not.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE When any input
 *         parameter exceeds its allowedrange
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO if SxD driver function returns fail
 * @return SX_STATUS_NO_MEMORY if problems with memory allocation occurs
 * @return SX_STATUS_NO_RESOURCES if pool cannot provide object
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 */
sx_status_t sx_api_vlan_port_prio_tagged_set(
                                            const sx_api_handle_t           handle,
                                            const sx_port_log_id_t          log_port,
                                            const sx_untagged_prio_state_t  untagged_prio_state);

/**
 *This function gets the priority tagged attribute per port.
 *
 * @param[in] handle - SX-API handle
 * @param[in] log_port - logical port
 * @param[OUT] untagged_prio_state_p - untagged packets will be
 *            sent priority-tagged or not.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO if SxD driver function returns fail
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 */
sx_status_t sx_api_vlan_port_prio_tagged_get(
                                            const sx_api_handle_t       handle,
                                            const sx_port_log_id_t      log_port,
                                            sx_untagged_prio_state_t *  untagged_prio_state_p);

/**
 *  This function gets the VLAN member ports.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] swid - virtual switch partition id
 * @param[in] vid - VLAN id
 * @param[in,out] port_num_p - number of ports in a list that you want to retrieve
 * @param[in,out] vlan_port_list_p - a pointer to array of vlan port list
 *       structure. If it is NULL, the port_num variable will be filled out
 *       with numbers of ports that could be retrieved. If pointer is valid,
 *       vlan ports will be placed there and port_num will take actual
 *       number ports in array.
 * NOTE: if you put port_num is less than actual number of ports, you will get
 *       the first port_num elements in array and Successful result as output.

 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO if SxD driver function returns fail
 * @return SX_STATUS_NO_MEMORY if problems with memory allocation occurs
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 */

sx_status_t sx_api_vlan_ports_get(
                                 const sx_api_handle_t     handle,
                                 const sx_swid_t           swid,
                                 const sx_vid_t            vid,
                                 uint16_t *          port_num_p,
                                 sx_vlan_ports_t *   vlan_port_list_p);

/**
 *   This function enables/ disables ingress VLAN filtering on a
 *   port. The VLAN membership is defined in sx_vlan_ports_set
 *   API
 *  @param[in] handle - SX-API handle.
 *  @param[in] log_port - logical port number
 *  @param[in] ingress_filter_state      - port ingress vlan
 *        filter state (enable/disable)
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ACCESS_CMD_UNSUPPORTED if unsupported command is requested
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 * @return SX_STATUS_NO_MEMORY if problems with memory allocation occurs
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO if SxD driver function returns fail
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 */
sx_status_t sx_api_vlan_ingr_filter_ports_set(
                                             const sx_api_handle_t         handle,
                                             const sx_port_log_id_t        log_port,
                                             const sx_ingr_filter_mode_t   ingress_filter_state);

/**
 *   This function retrieves ingress VLAN filtering on a port.
 *  @param[in] handle - SX-API handle.
 *  @param[in] log_port - logical port number
 *  @param[out] ingress_filter_state_p - a pointer to port
 *          ingress vlan filter state (enable/disable)
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_PARAM_NULL if parameter is NULL.
 * @return SX_STATUS_CMD_ERROR if invalid command is requested
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 */
sx_status_t sx_api_vlan_ingr_filter_ports_get(
                                             const sx_api_handle_t         handle,
                                             const sx_port_log_id_t        log_port,
                                             sx_ingr_filter_mode_t * ingress_filter_state_p);

/**
 *  This function sets port's default VLAN ID. The PVID is set
 *  to untagged packets that ingress on the port.
 *  Note: When the PVID is deleted from the port, it is assigned
 *  with the default VLAN ID
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - ADD / DELETE
 * @param[in] log_port - logical port number
 * @param[in] pvid - Port VLAN ID
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ACCESS_CMD_UNSUPPORTED if unsupported command is requested
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO if SxD driver function returns fail
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 */
sx_status_t sx_api_vlan_port_pvid_set(
                                     const sx_api_handle_t     handle,
                                     const sx_access_cmd_t     cmd,
                                     const sx_port_log_id_t    log_port,
                                     const sx_vid_t            pvid);

/**
 *  This function retrieves port's default VLAN ID.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] log_port - logical port number
 * @param[out] pvid_p - Port VLAN ID
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO if SxD driver function returns fail
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 */
sx_status_t sx_api_vlan_port_pvid_get(
                                     const sx_api_handle_t     handle,
                                     const sx_port_log_id_t    log_port,
                                     sx_vid_t*           pvid_p);

/**
 *  This function sets port's accepted frame types.
 *  Note1: By default, all ports are configured to accept all
 *  frame types
 *  Note2: Priority tagged packets are considered as untagged
 *  packets
 *
 * @param[in] handle - SX-API handle.
 * @param[in] log_port - logical port number
 * @param[in] accptd_frm_types_p - struct holding the
 *  	 following values: allow_tagged, allow_untagged,
 *  	 allow_prio_tagged 
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO if SxD driver function returns fail
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 */
sx_status_t sx_api_vlan_port_accptd_frm_types_set(
                                                 const sx_api_handle_t             handle,
                                                 const sx_port_log_id_t            log_port,
                                                 const sx_vlan_frame_types_t *     accptd_frm_types_p);

/**
 *  This function retrieves port's accepted frame types.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] log_port - logical port number
 * @param[in/out] accptd_frm_types_p - a pointer to struct 
 *       holding the following values: allow_tagged,
 *       allow_untagged, allow_prio_tagged
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_PARAM_NULL if parameter is NULL.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameter is out of range
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO if SxD driver function returns fail
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 */
sx_status_t sx_api_vlan_port_accptd_frm_types_get(
                                                 const sx_api_handle_t             handle,
                                                 const sx_port_log_id_t            log_port,
                                                 sx_vlan_frame_types_t*      accptd_frm_types_p);

/**
 *  This function sets the virtual switch default VLAN ID. This
 *  VID is set by default as the PVID of all switch ports. If
 *  not called, the default VID for all virtual switches is 1.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] swid - virtual switch partition id
 * @param[in] vid - switch default VLAN id
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ACCESS_CMD_UNSUPPORTED if unsupported command is requested
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 * @return SX_STATUS_NO_MEMORY if problems with memory allocation occurs
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO if SxD driver function returns fail
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 */
sx_status_t sx_api_vlan_default_vid_set(
                                       const sx_api_handle_t   handle,
                                       const sx_swid_t         swid,
                                       const sx_vid_t          vid);

/**
 *  This function set unregister MC flood mode
 *  
 * @param[in] handle 	- SX-API handle
 * @param[in] swid 	- virtual switch partition id
 * @param[in] vid 	- filtering DB id
 * @param[in] unreg_mc_type - unregister MC type: BC, MC_IPv4, ..
 *
 * @return SX_STATUS_CMD_UNSUPPORTED command isn't supported yet.
 */
sx_status_t sx_api_vlan_unreg_mc_flood_mode_set(
                                               const sx_api_handle_t                 handle,
                                               const sx_swid_t                       swid,
                                               const sx_vid_t                        vid,
                                               const sx_vlan_unreg_flood_mode_t      urmc_flood_mode);

/**
 *  This function get unregister MC flood mode
 *  
 * @param[in] handle 	- SX-API handle
 * @param[in] swid 	- virtual switch partition id
 * @param[in] vid 	- filtering DB id
 * @param[out] unreg_mc_type_p - unregister MC type: BC, 
 *       MC_IPv4, ..
 *
 * @return SX_STATUS_CMD_UNSUPPORTED command isn't supported yet.
 */
sx_status_t sx_api_vlan_unreg_mc_flood_mode_get(
                                               const sx_api_handle_t                 handle,
                                               const sx_swid_t                       swid,
                                               const sx_vid_t                        vid,
                                               sx_vlan_unreg_flood_mode_t *    urmc_flood_mode_p);

/**
 *  This function set unregister MC flood ports
 *  
 * @param[in] handle 	- SX-API handle
 * @param[in] swid 	- virtual switch partition id
 * @param[in] vid 	- filtering DB id
 * @param[in] port_num - sizeof port list
 * @param[in] dist_log_port_list_p - a pointer to a port list, port can be LAG or physical port.
 *
 * @return SX_STATUS_CMD_UNSUPPORTED command isn't supported yet.
 */
sx_status_t sx_api_vlan_unreg_mc_flood_ports_set(
                                                const sx_api_handle_t       handle,
                                                const sx_swid_t             swid,
                                                const sx_vid_t              vid,
                                                const uint16_t              port_num,
                                                const sx_port_log_id_t *    log_port_list_p );

/**
 *  This function get unregister MC flood ports
 *  
 * @param[in] hadle 	- SX-API handle
 * @param[in] swid 	- virtual switch partition id
 * @param[in] vid 	- filtering DB id
 * @param[in,out] num_ports_p - sizeof port list
 * @param[out] dist_log_port_list_p - a pointer to a port list, port can be LAG or physical port.
 *
 * @return SX_STATUS_CMD_UNSUPPORTED command isn't supported yet. 
 * @return SX_STATUS_PARAM_NULL if a required parameter is NULL 
 * @return SX_STATUS_NO_MEMORY if an error occured in memory 
 *         allocation
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if any parameter is out 
 *         of allowed value range
 * @return SX_STATUS_CMD_UNPERMITTED if flood mode is FLOOD 
 */ 
sx_status_t sx_api_vlan_unreg_mc_flood_ports_get(
                                                const sx_api_handle_t             handle,
                                                const sx_swid_t                   swid,
                                                const sx_vid_t                    vid,
                                                uint16_t *                  num_ports_p,
                                                sx_port_log_id_t *          log_port_list_p);

/**
 * This API controls the profile for uc & broadcast flooding on 
 * VLAN 
 * @param[in] handle - SX-API handle 
 * @param[in] sx_fid_t - fid 
 * @param[in] vlan_profile - DISCARD/FORWARDING
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if Invalid parameter was supplied
 * @return SX_STATUS_INVALID_HANDLE if handle is NULL
 * @return SX_STATUS_PARAM_NULL if one of the parameter is NULL 
 * @return SX_STATUS_ERROR otherwise 
 */

sx_status_t sx_api_vlan_profile_set(
                                   const sx_api_handle_t                   handle,
                                   const sx_swid_t                         swid,
                                   const sx_fid_t                          fid,
                                   const sx_vlan_profile_broadcast_flood_t vlan_profile);

/**
 * This API gets the profile for uc & broadcast flooding on VLAN
 * @param[in] handle - SX-API handle 
 * @param[in] sx_fid_t  - fid
 * @param[out] vlan_profile - DISCARD/FORWARDING
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if Invalid parameter was supplied
 * @return SX_STATUS_INVALID_HANDLE if handle is NULL
 * @return SX_STATUS_PARAM_NULL if one of the parameter is NULL 
 * @return SX_STATUS_ERROR otherwise 
 */

sx_status_t sx_api_vlan_profile_get(
                                   const sx_api_handle_t                       handle,
                                   const sx_swid_t                             swid,
                                   const sx_fid_t                              fid,
                                   sx_vlan_profile_broadcast_flood_t *   vlan_profile);

/**
 *  This function set Q-in-Q mode of port
 *
 * @param[in] hadle     - SX-API handle
 * @param[in] log_port  - logical port id
 * @param[in] quiq_mode - mode: Q-in-Q enabled/disabled
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if any parameter is out of allowed value range
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO if SxD driver function returns fail
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 */
sx_status_t sx_api_vlan_qinq_mode_set(
                                     const sx_api_handle_t   handle,
                                     const sx_port_log_id_t  log_port,
                                     const sx_qinq_mode_t    qinq_mode);

/**
 *  This function retrieves Q-in-Q mode of port
 *
 * @param[in] hadle      - SX-API handle
 * @param[in] log_port   - logical port id
 * @param[out] quiq_mode - the retrieved mode
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 */
sx_status_t sx_api_vlan_qinq_mode_get(
                                     const sx_api_handle_t       handle,
                                     const sx_port_log_id_t      log_port,
                                     sx_qinq_mode_t *      qinq_mode_p);

/**
 * The function sets which priority should be taken for the outer tag (when Q-in-Q is enabled):
 * The port's default priority, or the inner tag's priority
 *
 * @param[in] hadle     - SX-API handle
 * @param[in] log_port  - logical port id
 * @param[in] prio_mode - mode: default/inner priority
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if any parameter is out of allowed value range
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO if SxD driver function returns fail
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 */
sx_status_t sx_api_vlan_qinq_outer_prio_mode_set(
                                                const sx_api_handle_t         handle,
                                                const sx_port_log_id_t        log_port,
                                                const sx_qinq_outer_prio_mode_t prio_mode);

/**
 * This function retrieves port's Q-in-Q outer tag priority mode
 *
 * @param[in] hadle     - SX-API handle
 * @param[in] log_port  - logical port id
 * @param[out] prio_mode_p - the retrieved mode
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_INVALID_HANDLE if handle is invalid
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 * @return SX_STATUS_ERROR if unexpected behavior occurs
 */
sx_status_t sx_api_vlan_qinq_outer_prio_mode_get(
                                                const sx_api_handle_t         handle,
                                                const sx_port_log_id_t        log_port,
                                                sx_qinq_outer_prio_mode_t *prio_mode_p);


#endif /* __SX_API_VLAN_H__ */

