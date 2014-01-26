/*
 *      	    - Mellanox Proprietary -
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

#ifndef __SX_API_FDB_H__
#define __SX_API_FDB_H__

#include <sx/sdk/sx_api.h>


/***********************************************
 *  API functions
 ***********************************************/

/**
 * This function sets the log verbosity level of FDB MODULE
 * @param[in]     handle		   - SX-API handle
 * @param[in]     cmd   		   - SET / GET
 * @param[in]     verbosity_target         - set get verbosity of : API / MODULE / BOTH
 * @param[in,out] module_verbosity_level_p - FDB module verbosity level
 * @param[in,out] api_verbosity_level_p    - FDB API verbosity level
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS - Operation completes successfully
 * @return SX_STATUS_CMD_UNSUPPORTED - Unsupported access command
 * @return SX_STATUS_INVALID_HANDLE - NULL handle received
 * @return SX_STATUS_COMM_ERROR - Client communication channel open failed
 * @return SX_STATUS_PARAM_ERROR - Unsupported verbosity_target
 */
sx_status_t sx_api_fdb_log_verbosity_level_set(
                                              const sx_api_handle_t           handle ,
                                              const sx_access_cmd_t           cmd ,
                                              const sx_log_verbosity_target_t  verbosity_target,
                                              sx_verbosity_level_t* module_verbosity_level_p,
                                              sx_verbosity_level_t* api_verbosity_level_p);

/**
 *  This function sets the FDB age time, in seconds. Age time is
 *  the time after which auto learned addresses are deleted from
 *  the FDB if they receive no traffic.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] swid - Switch ID.
 * @param[in] age_time - Time in seconds.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_INVALID_HANDLE if NULL handle received.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_ENTRY_NOT_FOUND if switch was not added.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_fdb_age_time_set(
                                   const sx_api_handle_t   handle,
                                   const sx_swid_t         swid,
                                   const sx_fdb_age_time_t age_time);

/**
 *  This function gets the FDB age time, in seconds. Age time is
 *  the time after which auto learned addresses are deleted from
 *  the FDB if they receive no traffic.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] swid - Switch ID.
 * @param[out] age_time_p - Time in seconds.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_INVALID_HANDLE if NULL handle received.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_ENTRY_NOT_FOUND if switch was not added.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_fdb_age_time_get(
                                   const sx_api_handle_t handle,
                                   const sx_swid_t       swid,
                                   sx_fdb_age_time_t*    age_time_p);

/**
 *  This function set the FDB poll for mac entries notifications
 *
 * @param[in] handle - SX-API handle
 * @param[in] swid - virtual switch partition id
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_INVALID_HANDLE if NULL handle received.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_ENTRY_NOT_FOUND if switch was not added.
 * @return SX_STATUS_NO_RESOURCES if there is no place in jobs buffer.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_fdb_poll_set(
                               const sx_api_handle_t handle,
                               const sx_swid_t       swid);

/**
 *  This function sets the FDB polling interval from HW in 0.1
 *  seconds.
 * @param[in] handle - SX-API handle
 * @param[in] swid - virtual switch partition id
 * @param[in] interval - polling interval in 0.1 seconds
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_INVALID_HANDLE if NULL handle received.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_ENTRY_NOT_FOUND if switch was not added.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_fdb_polling_interval_set(
                                           const sx_api_handle_t           handle,
                                           const sx_swid_t                 swid,
                                           const sx_fdb_polling_interval_t interval);

/**
 *  This function adds/deletes UC MAC and UC LAG MAC entries to/from the FDB.
 *  In case the operation failed on one entry (or more), an error will be
 *  returned, mac_list will store those entries, and their quantity
 *  will be stored in data_cnt.
 *  If the operation finished successfully: SUCCESS will be returned, and
 *  data_cnt and mac_list won't be changed.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - ADD/DELETE
 * @param[in] swid - virtual switch partition id
 * @param[in,out] mac_list - list of mac record parameters. On deletion,
 *       entry_type is DONT_CARE
 * @param[in,out] data_cnt_p - number of mac records to 
 *       ADD/DELETE
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_INVALID_HANDLE if NULL handle received.
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_ENTRY_NOT_FOUND if switch was not added.
 * @return SX_STATUS_NO_RESOURCES if FDB hash bin is full.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_fdb_uc_mac_addr_set(
                                      const   sx_api_handle_t handle,
                                      const   sx_access_cmd_t cmd,
                                      const   sx_swid_t swid,
                                      sx_fdb_uc_mac_addr_params_t *mac_list_p,
                                      uint16_t *data_cnt_p);

/**
 * This function reads MAC entries from the SW FDB table, which
 * is exact copy of HW DB on any device. The output supports up
 * to SX_FDB_MAX_GET_ENTRIES entries which is currently 64
 *
 * The function can receive three types of input:
 *
 *   - 1) get information for current mac + vlan - you should
 *      insert mac+vlan data in the key variable, data_cnt
 *      should be equal to 1. cmd should be
 *      SX_ACCESS_CMD_GET
 *
 *   - 2) get a list of first n<=64 macs - you should
 *      insert mac+vlan data in the key variable, data_cnt
 *      should be equal to n, mac_type is a type you want to
 *      receive,key_filter is the filter types you want to filter the results by,
 *      cmd should be  SX_ACCESS_CMD_GET_FIRST
 *
 *   - 3) get a list of n<=64 macs which comes after certain
 *      mac record (it does not have to exist) you should insert
 *      mac+vlan data in the key variable, data_cnt should be
 *      equal to n, mac_type is a type you want to receive,
 *      key_filter is the filter types you want to filter the results by,
 *      cmd should be SX_ACCESS_CMD_GETNEXT
 *
 *  mac_list will return the records info and their quantity in
 *  data_cnt for all types of requests.
 *
 *
 * @param[in] handle -      SX-API handle
 * @param[in] swid -        virtual switch partition id
 * @param[in] cmd -  get, get_next, get first
 * @param[in] mac_type -    static, dynamic, all
 * @param[in] key_p -         mac entry with information for
 *       search (mac + vlan)
 * @param[in] key_filter_p -  filter types used on the mac_list
 *       - fid / mac / logical port
 * @param[out] mac_list_p -    pointer to list
 * @param[in,out] data_cnt_p -number of entries to retrieve,
 *       also retrieved number of entries
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_INVALID_HANDLE if NULL handle received.
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_NULL if parameter is NULL.
 * @return SX_STATUS_ENTRY_NOT_FOUND if switch wa		const sx_api_handle_t handle,
        const sx_swid_t swid,
        uint32_t *max_mc_group_cnt_p
s not added.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_fdb_uc_mac_addr_get(
                                      const sx_api_handle_t               handle,
                                      const sx_swid_id_t                  swid,
                                      const sx_access_cmd_t               cmd,
                                      const sx_fdb_uc_mac_entry_type_t    mac_type,
                                      const sx_fdb_uc_mac_addr_params_t*  key_p,
                                      const sx_fdb_uc_key_filter_t*       key_filter_p,
                                      sx_fdb_uc_mac_addr_params_t*        mac_list_p,
                                      uint16_t*                           data_cnt_p);

/**
 *  This function counts all MAC entries in SW FDB table (static + dynamic).
 *
 * @param[in] handle - SX-API handle
 * @param[in] swid - virtual switch partition id
 * @param[out] data_cnt_p - retrieved number of entries
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_INVALID_HANDLE if NULL handle received.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if swid is out of range.
 * @return SX_STATUS_PARAM_NULL if parameter is NULL.
 * @return SX_STATUS_ENTRY_NOT_FOUND if switch was not added.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_fdb_uc_count_get(
                                   const sx_api_handle_t handle,
                                   const sx_swid_id_t    swid,
                                   uint32_t*             data_cnt_p);

/**
 * This function returns the amount of MACs learned on port (static + dynamic).
 *
 * @param[in] handle - SX-API handle
 * @param[in] log_port - logical port ID
 * @param[out] data_cnt_p - retrieved number of entries
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO: Message size error
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT: Message size error
 * @return SX_STATUS_INVALID_HANDLE: Invalid Handle
 * @return SX_STATUS_ENTRY_NOT_FOUND if port does not exist
 * @return SX_STATUS_ERROR general error
 */

sx_status_t sx_api_fdb_uc_port_count_get(
                                        const sx_api_handle_t   handle,
                                        const sx_port_log_id_t  log_port,
                                        uint32_t*               data_cnt_p);

/**
 * This function returns the amount of MACs learned on fid (static + dynamic).
 *
 * @param[in] handle - SX-API handle
 * @param[in] swid - virtual switch partition id
 * @param[in] fid - filtering DB id
 * @param[out] data_cnt_p - retrieved number of entries
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO: Message size error
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT: Message size error
 * @return SX_STATUS_INVALID_HANDLE: Invalid Handle
 * @return SX_STATUS_ENTRY_NOT_FOUND if swid does not exist
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if fid/swid is out of range
 * @return SX_STATUS_PARAM_NULL if parameter is NULL
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_fdb_uc_fid_count_get(
                                       const sx_api_handle_t   handle,
                                       const sx_swid_id_t      swid,
                                       const sx_fid_t          fid,
                                       uint32_t*               data_cnt_p);

/**
 * This function sets/removes limit on the amount of dynamic MACs learned on port.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - SET/DELETE
 * @param[in] log_port - logical port ID
 * @param[in] limit - When SET command is used, this is the new limit to set
 *                    (between 0 and SX_FDB_MAX_ENTRIES)
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO: Message size error.
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT: Message size error
 * @return SX_STATUS_INVALID_HANDLE: Invalid Handle
 * @return SX_STATUS_ENTRY_NOT_FOUND if port does not exist
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if limit is out of range
 * @return SX_STATUS_CMD_UNSUPPORTED if unsupported command is requested
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_fdb_uc_limit_port_set(
                                        const sx_api_handle_t   handle,
                                        const sx_access_cmd_t   cmd,
                                        const sx_port_log_id_t  log_port,
                                        const uint32_t          limit);

/**
 * This function sets/removes limit on the amount of dynamic MACs learned on FID.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - SET/DELETE
 * @param[in] swid - virtual switch partition id
 * @param[in] fid - filtering DB id
 * @param[in] limit - When SET command is used, this is the new limit to set
 *                    (between 0 and SX_FDB_MAX_ENTRIES)
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO: Message size error
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT: Message size error
 * @return SX_STATUS_INVALID_HANDLE: Invalid Handle
 * @return SX_STATUS_ENTRY_NOT_FOUND if swid does not exist
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if swid/fid/limit is out of range
 * @return SX_STATUS_CMD_UNSUPPORTED if unsupported command is requested
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_fdb_uc_limit_fid_set(
                                       const sx_api_handle_t   handle,
                                       const sx_access_cmd_t   cmd,
                                       const sx_swid_id_t      swid,
                                       const sx_fid_t          fid,
                                       const uint32_t          limit);

/**
 * This function returns the maximum amount of dynamic MACs that can be learned on port.
 *
 * @param[in] handle - SX-API handle
 * @param[in] log_port - logical port ID
 * @param[out] limit_p - The result limit. If no limit is set 
 *       SX_FDB_MAX_ENTRIES is returned
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO: Message size error
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT: Message size error
 * @return SX_STATUS_INVALID_HANDLE: Invalid Handle
 * @return SX_STATUS_ENTRY_NOT_FOUND if port does not exist
 * @return SX_STATUS_PARAM_NULL if parameter is NULL
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_fdb_uc_limit_port_get(
                                        const sx_api_handle_t   handle,
                                        const sx_port_log_id_t  log_port,
                                        uint32_t*               limit_p);

/**
 * This function returns the maximum amount of dynamic MACs that can be learned on FID.
 *
 * @param[in] handle - SX-API handle
 * @param[in] swid - virtual switch partition id
 * @param[in] fid - filtering DB id
 * @param[out] limit_p - The result limit. If no limit is set 
 *       SX_FDB_MAX_ENTRIES is returned
 *
 * @return sx_status_t:
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO: Message size error
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT: Message size error
 * @return SX_STATUS_INVALID_HANDLE: Invalid Handle
 * @return SX_STATUS_ENTRY_NOT_FOUND if swid does not exist
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if fid/swid is out of range
 * @return SX_STATUS_PARAM_NULL if parameter is NULL
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_fdb_uc_limit_fid_get(
                                       const sx_api_handle_t   handle,
                                       const sx_swid_id_t      swid,
                                       const sx_fid_t          fid,
                                       uint32_t*               limit_p);

/**
 *      This function adds, deletes MC MAC entries from the FDB.
 *      Please Note: MC entry cannot be created and associated with Ports at the same time
 *
 *      NOTE The log_port_list_p list should not contain
 *             the logical port items which are specified as Ethernet Port
 *             and which are members of LAG port at same time.
 *
 *      When ADD command is requested this function does the following:
 *      - check if MC groups is already created and returns FAILURE if yes;
 *      - allocates and stores the MC group;
 *
 *      When DELETE command is requested this function does the following:
 *      - for each LEAF device:
 *      - deletes Multicast FDB Records;
 *      - deletes FDB Multicast ID Records;
 *      - deletes SPGT record;
 *
 *      - deletes MC group from MCDB;
 *      - returns pgi into the pool.
 *
 *      When Edit(add_port) command is requested this function does
 *       the following:
 *      - updates MCDB for adding logical ports and LAG ports;
 *      - for each LEAF device:
 *      	- gets list of LAG member logical ports from LAGLib for
 *      	  all LAG logical ports which are belongs to this MC group;
 *      	- updates SPGT record for adding spine, MC members and
 *      	  LAGs member ports;
 *      	- adds local ports to FDB Multicast ID Records (if FDB look
 *      	  up by MC ID is allowed on LEAF devices).
 *
 *      When Edit(delete_port) command is requested this function does
 *       the following:
 *      - updates MCDB for deleting logical ports and LAG ports.
 *      - for each LEAF device:
 *      - updates SPGT record for deleting requested ports
 *        (if logical port is a LAG port then all LAG members logical ports
 *        will be removed);
 *      - removes local ports from FDB Multicast ID Records
 *        (if FDB look up by MC ID is allowed on LEAF devices)
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - add/ delete/ add port/ delete port/
 *       test
 * @param[in] swid - virtual switch partition id
 * @param[in] vid - filtering DB id
 * @param[in] group_addr - MAC group address
 * @param[in] log_port_list_p - a pointer to a port list
 * @param[in] port_cnt - sizeof port list 
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_INVALID_HANDLE if NULL handle received.
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_NULL if parameter is NULL.
 * @return SX_STATUS_NO_MEMORY if memory allocation failed.
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND if switch was not added.
 * @return SX_STATUS_ENTRY_ALREADY_EXISTS if group_addr alreadey added.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_fdb_mc_mac_addr_set(
                                      const sx_api_handle_t   handle,
                                      const sx_access_cmd_t   cmd,
                                      const sx_swid_t         swid,
                                      const sx_vid_t          vid,
                                      const sx_mac_addr_t     group_addr,
                                      const sx_port_log_id_t* log_port_list_p,
                                      const uint16_t          port_cnt);

/**
 *  This function returns MC MAC entries data.
 *
 *  NOTE The log_port_list_p list will contain LAG ports id
 *  only and not contains LAG members logical ports IDs.
 *
 * @param[in] handle - SX-API handle
 * @param[in] swid - virtual switch partition id
 * @param[in] vid - filtering DB id
 * @param[in] group_addr - MAC group address
 * @param[out] log_port_list_p - a pointer to a port list
 * @param[out] port_cnt_p - sizeof port list 
 *  
 * @return SX_STATUS_SUCCESS if operation completes 
 *         successfully.
 * @return SX_STATUS_INVALID_HANDLE if NULL handle received.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_NULL if parameter is NULL.
 * @return SX_STATUS_NO_MEMORY if memory allocation failed.
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND if group_addr was not added.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_fdb_mc_mac_addr_get(
                                      const sx_api_handle_t   handle,
                                      const sx_swid_t         swid,
                                      const sx_vid_t          vid,
                                      const sx_mac_addr_t     group_addr,
                                      sx_port_log_id_t*       log_port_list_p,
                                      uint16_t*               port_cnt_p);

/**
 *  This function returns MC max group count.
 *
 * @param[in] handle - SX-API handle
 * @param[in] swid - virtual switch partition id
 * @param[out] max_mc_group_cnt_p - maximum mc group
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_INVALID_HANDLE if NULL handle received.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_NULL if parameter is NULL.
 * @return SX_STATUS_ENTRY_NOT_FOUND if switch was not added.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_fdb_mc_max_group_cnt_get(
                                           const sx_api_handle_t   handle,
                                           const sx_swid_t         swid,
                                           uint32_t*               max_mc_group_cnt_p);

/**
 *  This function deletes all FDB table on a switch partition.
 *
 * @param[in] handle - SX-API handle
 * @param[in] swid - virtual switch partition id
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_INVALID_HANDLE if NULL handle received.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_ENTRY_NOT_FOUND if switch was not added.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_fdb_uc_flush_all_set(
                                       const sx_api_handle_t   handle,
                                       const sx_swid_t         swid);

/**
 *  This function deletes the FDB table entries that are related
 *  to a flushed port.
 *
 * @param[in] handle - SX-API handle
 * @param[in] swid - virtual switch partition id
 * @param[in] log_port - logical port.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_INVALID_HANDLE if NULL handle received.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_ENTRY_NOT_FOUND if switch was not added.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_fdb_uc_flush_port_set(
                                        const sx_api_handle_t   handle,
                                        const sx_swid_t         swid,
                                        const sx_port_log_id_t  log_port);

/**
 *  This function deletes all FDB table entries that were learned
 *  on the flushed FID
 *
 * @param[in] handle - SX-API handle
 * @param[in] swid - virtual switch partition id
 * @param[in] fid filtering DB id
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_INVALID_HANDLE if NULL handle received.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_ENTRY_NOT_FOUND if switch was not added.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_fdb_uc_flush_fid_set(
                                       const sx_api_handle_t   handle,
                                       const sx_swid_t         swid,
                                       const sx_fid_t          fid);

/**
 *  This function deletes all FDB table entries that were learned
 *  on the flushed FID and port.
 *
 * @param[in] handle - SX-API handle
 * @param[in] swid - virtual switch partition id
 * @param[in] log_port - logical port.
 * @param[in] fid - filtering DB id
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_INVALID_HANDLE if NULL handle received.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_ENTRY_NOT_FOUND if switch was not added.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_fdb_uc_flush_port_fid_set(
                                            const sx_api_handle_t   handle,
                                            const sx_swid_t         swid,
                                            const sx_port_log_id_t  log_port,
                                            const sx_fid_t          fid);

/**const 
*  const This function deletes all FDB MC tables on a switch
*  partition.
*
* @param[in] handle - SX-API handle
* @param[in] swid - virtual switch partition id
*
* @return SX_STATUS_SUCCESS if operation completes successfully.
* @return SX_STATUS_INVALID_HANDLE if NULL handle received.
* @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
* @return SX_STATUS_ENTRY_NOT_FOUND if switch was not added.
* @return SX_STATUS_ERROR general error.
*/
sx_status_t sx_api_fdb_mc_flush_all_set(
                                       const sx_api_handle_t   handle,
                                       const sx_swid_t         swid);

/**
*  This function deletes all FDB MC table entries that were
*  learned on the flushed FID, on a switch partition.
*
* @param[in] handle - SX-API handle
* @param[in] swid - virtual switch partition id
* @param[in] fid filtering DB id
*
* @return SX_STATUS_SUCCESS if operation completes successfully.
* @return SX_STATUS_INVALID_HANDLE if NULL handle received.
* @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
* @return SX_STATUS_ENTRY_NOT_FOUND if switch was not added.
* @return SX_STATUS_ERROR general error.
*/
sx_status_t sx_api_fdb_mc_flush_fid_set(
                                       const sx_api_handle_t   handle,
                                       const sx_swid_t         swid,
                                       const sx_fid_t          fid);

/**
 *  This function maps VLANs to filtering databases for shared
 *  vlan learning (SVL) between VLANs. If independent vlan
 *  learning is desired, a single VLAN should be mapped to a
 *  single FID.
 *
 *  When cmd=add This function adds FID to VID mapping record
 *      for selected SWID.
 *  When cmd=delete This function deletes FID to VID mapping
 *      record from selected SWID.
 *      The DEF_FID value will be added to the corresponding VLAN.

 *  NOTE this API performs FDB flushing by FID
 *         before FID to VID mapping changing
 *
 *  NOTE only independent learning is supported in the current release.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - add/ delete
 * @param[in] swid - virtual switch partition id
 * @param[in] fid - filtering DB id
 * @param[in] vid - VLAN id
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_INVALID_HANDLE if NULL handle received.
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_ENTRY_NOT_FOUND if switch was not added.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_fdb_fid_vlan_member_set(
                                          const sx_api_handle_t   handle,
                                          const sx_access_cmd_t   cmd,
                                          const sx_swid_t         swid,
                                          const sx_fid_t          fid,
                                          const sx_vid_t          vid);

/**
 *  This function sets the FDB learning mode per swid
 *  It affects all ports and vlans in the swid.
 *
 * @param[in] handle - SX-API handle
 * @param[in] swid - virtual switch partition id
 * @param[in] learn_mode - new swid's learn mode
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_INVALID_HANDLE if NULL handle received.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_NO_MEMORY if memory allocation failed.
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND if switch was not added.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_fdb_learn_mode_set(
                                     const sx_api_handle_t handle,
                                     const sx_swid_t swid,
                                     const sx_fdb_learn_mode_t learn_mode);

/**
 *  This function gets the FDB learning mode per swid
 *
 * @param[in] handle - SX-API handle
 * @param[in] swid - virtual switch partition id
 * @param[out] learn_mode - swid's learn mode
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_INVALID_HANDLE if NULL handle received.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_NO_MEMORY if memory allocation failed.
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND if switch was not added.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_fdb_learn_mode_get(
                                     const sx_api_handle_t handle,
                                     const sx_swid_t swid,
                                     sx_fdb_learn_mode_t *learn_mode);

/** 
 * This API is not supported at the current release 
 *  
 *  This function sets the rate that the driver informs
 *  application on new address events
 *
 *  If learn_limit_cmd = limit_vlan then the learning rate limit
 *      will be updated on all LEAF devices.
 *  If limit_port = limit_port then the learning rate limit will be updated
 *      on device for which log_port is belonged to.
 *
 * @param[in] handle - SX-API handle
 * @param[in] learn_limit_cmd - limit_vlan, limit_port,
 * @param[in] swid - virtual switch partition id - should be set
 *       to 0 when 'limit_port' command param is set
 * @param[in] vid - VLAN id - should be set
 *       to 0 when 'limit_port' command param is set
 * @param[in] log_port - logical port - should be set
 *       to 0 when 'limit_vlan' command param is set
 * @param[in] rate_limit - number of learning events per second
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_INVALID_HANDLE if NULL handle received.
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_NO_MEMORY if memory allocation failed.
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND if switch was not added.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_fdb_learn_rate_limit_set(
                                           const sx_api_handle_t           handle,
                                           const sx_fdb_learn_limit_cmd_t  learn_limit_cmd,
                                           const sx_swid_t                 swid,
                                           const sx_vid_t                  vid,
                                           const sx_port_log_id_t          log_port,
                                           const uint16_t                  rate_limit);

/**
 *  This API Sets the SwID's Learning parameters into the system's Database.
 *
 *  NOTE only independent learning is supported in the current release.
 *
 * @param[in] handle - SX-API handle
 * @param[in] swid_id - Switch (virtual) ID (whose parameters to set).
 * @param[in] learn_ctrl - Is Independent/Shared Learning & is Roaming Enabled/Disabled.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_INVALID_HANDLE if NULL handle received.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND if switch was not added.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_fdb_swid_global_learning_mode_set(
                                                    const sx_api_handle_t       handle,
                                                    const sx_swid_id_t          swid_id,
                                                    const sx_fdb_learn_ctrl_t   learn_ctrl);

/**
 *  This API Retrieves the SwID's Learning parameters from the system's Database.
 *
 * @param[in] handle - SX-API handle
 * @param[in] swid_id - Switch (virtual) ID (whose parameters to retrieve).
 * @param[out] learn_ctrl_p - Is Independent/Shared Learning & is Roaming Enabled/Disabled.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_INVALID_HANDLE if NULL handle received.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_NULL if parameter is NULL.
 * @return SX_STATUS_ENTRY_NOT_FOUND if switch was not added.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_fdb_swid_global_learning_mode_get(
                                                    const sx_api_handle_t       handle,
                                                    const sx_swid_id_t          swid_id,
                                                    sx_fdb_learn_ctrl_t*  learn_ctrl_p);

/**
*  This function sets fid's learn mode.
* @param[in] handle - SX-API handle
* @param[in] swid - switch id.
* @param[in] fid - filtering identifier
* @param[in] learn mode- fid's learn mode
*
**/
sx_status_t sx_api_fdb_fid_learn_mode_set (
                                          const sx_api_handle_t handle,
                                          const sx_swid_t swid,
                                          const sx_fid_t fid,
                                          const sx_fdb_learn_mode_t learn_mode);

/**
*  This function gets fid's learn mode.
* @param[in] handle - SX-API handle
* @param[in] swid - switch id.
* @param[in] fid - filtering identifier
* @param[out] learn mode- fid's learn mode
*
* @return SX_STATUS_SUCCESS if operation completes successfully
* @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
* @return SX_STATUS_SXD_RETURNED_NON_ZERO if SxD driver function returns fail
* @return SX_STATUS_ERROR if unexpected behavior occurs
*/
sx_status_t sx_api_fdb_fid_learn_mode_get (
                                          const sx_api_handle_t handle,
                                          const sx_swid_t swid,
                                          const sx_fid_t fid,
                                          sx_fdb_learn_mode_t *learn_mode_p);

/**
*  This function sets port's learn mode.
* @param[in] handle - SX-API handle
* @param[in] log_port - logical port number
* @param[in] learn mode- port's learn mode
*
* @return SX_STATUS_SUCCESS if operation completes successfully
* @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
* @return SX_STATUS_SXD_RETURNED_NON_ZERO if SxD driver function returns fail
* @return SX_STATUS_ERROR if unexpected behavior occurs
*/
sx_status_t sx_api_fdb_port_learn_mode_set(
                                          const sx_api_handle_t       handle,
                                          const sx_port_log_id_t      log_port,
                                          const sx_fdb_learn_mode_t   learn_mode);

/**
*  This function gets port's learn mode.
* @param[in] handle - SX-API handle
* @param[in] log_port - logical port number
* @param[out] learn mode- port's learn mode
*
* @return SX_STATUS_SUCCESS if operation completes successfully
* @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
* @return SX_STATUS_SXD_RETURNED_NON_ZERO if SxD driver function returns fail
* @return SX_STATUS_ERROR if unexpected behavior occurs
*/
sx_status_t sx_api_fdb_port_learn_mode_get(
                                          const sx_api_handle_t   handle,
                                          const sx_port_log_id_t  log_port,
                                          sx_fdb_learn_mode_t*    learn_mode_p);

/**
 *  This function sets FDB notify parameters.
 *  This only affects when controlled learn mode is set.
 *
 * @param[in] handle - SX-API handle
 * @param[in] swid - virtual switch partition id
 * @param[in] params_p - new notify params
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_INVALID_HANDLE if NULL handle received.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_ENTRY_NOT_FOUND if switch was not added.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_fdb_notify_params_set(
                                        const sx_api_handle_t handle,
                                        const sx_swid_id_t swid,
                                        const sx_fdb_notify_params_t *notify_params_p);

/**
 *  This function gets FDB notify parameters.
 *
 * @param[in] handle - SX-API handle
 * @param[in] swid - virtual switch partition id
 * @param[out] params - swid's notify params
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_INVALID_HANDLE if NULL handle received.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_ENTRY_NOT_FOUND if switch was not added.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_fdb_notify_params_get(
                                        const sx_api_handle_t handle,
                                        const sx_swid_id_t swid,
                                        sx_fdb_notify_params_t *notify_params_p);

#endif /* __SX_API_FDB_H__ */
