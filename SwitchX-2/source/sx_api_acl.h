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

#ifndef __SX_API_ACL_H__
#define __SX_API_ACL_H__

#include <sx/sdk/sx_api.h>
#include <sx/sdk/sx_acl.h>


/************************************************
 *  API functions
 ***********************************************/

/**
 * This function sets the log verbosity level of ACL MODULE
 * Supported devices: SwitchX, SwitchX2, Spectrum.
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] verbosity_target         - set verbosity of : API / MODULE / BOTH
 * @param[in] module_verbosity_level   - ACL module verbosity level
 * @param[in] api_verbosity_level      - ACL API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter is invalid
 *         SX_STATUS_ERROR general error
 */
sx_status_t sx_api_acl_log_verbosity_level_set(const sx_api_handle_t           handle,
                                               const sx_log_verbosity_target_t verbosity_target,
                                               const sx_verbosity_level_t      module_verbosity_level,
                                               const sx_verbosity_level_t      api_verbosity_level);

/**
 * This function gets the log verbosity level of ACL MODULE
 * Supported devices: SwitchX, SwitchX2, Spectrum.
 *
 * @param[in]  handle                   - SX-API handle
 * @param[in]  verbosity_target         - get verbosity of : API / MODULE / BOTH
 * @param[out] module_verbosity_level_p - ACL module verbosity level
 * @param[out] api_verbosity_level_p    - ACL API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter is invalid
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_acl_log_verbosity_level_get(const sx_api_handle_t           handle,
                                               const sx_log_verbosity_target_t verbosity_target,
                                               sx_verbosity_level_t           *module_verbosity_level_p,
                                               sx_verbosity_level_t           *api_verbosity_level_p);

/**
 *  This function is used to create ACL region (rules list).
 *  for creation use command CREATE and supply key_type and
 *  size. acl_region_id is returned on successful creation.
 *  for destroying an ACL region it is required that the ACL
 *  region is not bound and the acl_region_id should be
 *  provided. EDIT command is used for resizing an existing ACL
 *  region. acl_region_id and new size should be provided.
 *  Supported devices: SwitchX, SwitchX2, Spectrum.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - CREATE / DESTROY / EDIT
 * @param[in] key_type - key type used in this ACL
 * @param[in] action_type - type of actions to be used in this
 *       ACL block
 * @param[in] acl_size - maximal number of rules in this ACL
 * @param[in,out] region_id_p - ACL region ID as described above
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 * @return SX_STATUS_NO_RESOURCES if no ACL is available to create
 * @return SX_STATUS_CMD_UNSUPPORTED if unsupported command is requested
 */
sx_status_t sx_api_acl_region_set(const sx_api_handle_t      handle,
                                  const sx_access_cmd_t      cmd,
                                  const sx_acl_key_type_t    key_type,
                                  const sx_acl_action_type_t action_type,
                                  const sx_acl_size_t        region_size,
                                  sx_acl_region_id_t        *region_id_p);

/**
 *  This function is used to get ACL region properties .
 *  Supported devices: SwitchX, SwitchX2, Spectrum.
 *
 * @param[in] handle - SX-API handle
 * @param[in] region_id - ACL region ID
 * @param[out] key_type_p - key type used in this ACL region
 * @param[out] action_type_p - type of actions used in this ACL
 *       region
 * @param[out] region_size_p - maximal number of rules in this
 *       ACL region
 *
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is
 *                             not found in DB
 */
sx_status_t sx_api_acl_region_get(const sx_api_handle_t    handle,
                                  const sx_acl_region_id_t region_id,
                                  sx_acl_key_type_t       *key_type_p,
                                  sx_acl_action_type_t    *action_type_p,
                                  sx_acl_size_t           *region_size_p);

/**
 *
 *  This function is used to create a single region ACL.
 *  Use CREATE access command for creating a new ACL,
 *  it will return an ACL id. DESTROY command may be used when
 *  the ACL is not bound to HW.
 *  Packet sensitive ACL is currently NOT supported.
 *  Supported devices: SwitchX, SwitchX2, Spectrum.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - CREATE / DESTROY
 * @param[in] acl_type - ACL type of this ACL (AGNOSTIC).
 * @param[in] acl_direction - ACL direction (ingress or egress port or
 *       ingress or egress RIF ACL)
 * @param[in] acl_region_group_p - ACL region group matching ACL type
 * @param[in,out] acl_id_p - ACL ID as described above
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 * @return SX_STATUS_NO_RESOURCES if no ACL is available to create
 * @return SX_STATUS_CMD_UNSUPPORTED if unsupported command is requested
 */
sx_status_t sx_api_acl_set(const sx_api_handle_t        handle,
                           const sx_access_cmd_t        cmd,
                           const sx_acl_type_t          acl_type,
                           const sx_acl_direction_t     acl_direction,
                           const sx_acl_region_group_t *acl_region_group_p,
                           sx_acl_id_t                 *acl_id_p);

/**
 *  This function is used to get ACL attributes . The ACL id is
 *  given and the function returns ACL attributes : type and a
 *  list of attached regions. the length of the regions list
 *  depends on the ACL type
 *  Supported devices: SwitchX, SwitchX2, Spectrum.
 *
 * @param[in] handle - SX-API handle
 * @param[in] acl_id - ACL ID
 * @param[out] acl_type_p - ACL type (packet agnostic or packet sensitive)
 * @param[out] acl_direction_p - ACL direction (ingress or egress ACL)
 * @param[out] acl_region_group_p - ACL region group attached to the ACL
 *
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 *  @return SX_STATUS_PARAM_NULL or SX_STATUS_PARAM_EXCEEDS_RANGE if any input
 *  parameter is invalid
 *  @return SX_STATUS_ENTRY_NOT_FOUND if requested element is
 *  not found in DB
 */
sx_status_t sx_api_acl_get(const sx_api_handle_t  handle,
                           const sx_acl_id_t      acl_id,
                           sx_acl_type_t         *acl_type_p,
                           sx_acl_direction_t    *acl_direction_p,
                           sx_acl_region_group_t *acl_region_group_p);

/**
 *  This function gets a list of valid ACL Ids.
 *  Supported devices: Spectrum.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd    GET/GET_NEXT/GET_FIRST
 * @param[in] acl_id_key - ACL ID to use and key.
 * @param[in] acl_filter_p - Filter to use (not supported yet)
 * @param[out] acl_id_list_p - pointer to the list of ACL IDs returned.
 * @param[in,out] acl_id_cnt_p [in] number of entries to retrieve (max 400); [out] retrieved  number of entries.
 *
 * Input/Output types
 *      - Get first - Get a list of first n entries.  Cmd should be SX_ACCESS_CMD_GET_FIRST and
 *           count should be equal to n. key is irrelevant in this case. Returns number of
 *           entries retrieved as count
 *      -  Get next  - Get n entries after a specified key (it does not have to exist).
 *           Cmd should be SX_ACCESS_CMD_GETNEXT. count should be equal to n.
 *           Returns number of entries retrieved as count
 *      - Get - Gets a specific entry. Cmd should be SX_ACCESS_CMD_GET and count should be 1.
 *       If input count is 0, then returns a count of ACL Ids as output instead.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_ERROR if any paramter is in error.
 * @return SX_STATUS_CMD_UNSUPPORTED if command is not supported
 * @return SX_STATUS_INVALID_HANDLE if handle in invalid
 * @return SX_STATUS_ERROR general error.
 */

sx_status_t sx_api_acl_iter_get(const sx_api_handle_t  handle,
                                const sx_access_cmd_t  cmd,
                                const sx_acl_id_t      acl_id_key,
                                const sx_acl_filter_t *acl_filter_p,
                                sx_acl_id_t           *acl_id_list_p,
                                uint32_t              *acl_id_cnt_p);

/**
 *
 *  This function is used for controlling a group of ACL or in
 *  other words cascaded ACL blocks up to the size of
 *  SX_ACL_MAX_ACL_GROUP_SIZE. When using CREATE command user
 *  must supply the ACL group direction. A new group is
 *  allocated and a free group ID is returned. Use SET
 *  command to define an ordered cascaded ACLs group (ACLs must
 *  be in the same direction as the group). SET Can be also used for editing an ACL group.
 *  DESTROY command will free the list resource. It is allowed only when the ACL list
 *  is not bound in HW.
 *  Supported devices: SwitchX, SwitchX2, Spectrum.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - CREATE / SET / DESTROY
 * @param[in] acl_direction - ACL group direction (ingress or
 *       egress ACLs). All ACLs in this group must have the same
 *       direction
 * @param[in] acl_id_list_p - ordered list of ACL IDs. Ignored when CMD=CREATE or CMD=DESTROY.
 * @param[in] acl_id_cnt - number of elements in the list of ACL IDs. Ignored when CMD=CREATE or CMD=DESTROY.
 * @param[in,out] group_id - ACL group ID
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 * @return SX_STATUS_NO_RESOURCES if no group is available to create
 * @return SX_STATUS_CMD_UNSUPPORTED if unsupported command is requested
 */
sx_status_t sx_api_acl_group_set(const sx_api_handle_t    handle,
                                 const sx_access_cmd_t    cmd,
                                 const sx_acl_direction_t acl_direction,
                                 const sx_acl_id_t       *acl_id_list_p,
                                 const uint32_t           acl_id_cnt,
                                 sx_acl_id_t             *group_id_p);

/**
 *
 *  This function is used to get ACL group attributes . the ACL
 *  group id is given and the function returns ACL group
 *  attributes : direction and a list of attached ACLs.
 *  Supported devices: SwitchX, SwitchX2, Spectrum.
 *
 * @param[in] handle - SX-API handle
 * @param[in] group_id - ACL group ID
 * @param[out] acl_direction - ACL direction (ingress or egress
 *       ACL)
 * @param[out] acl_id_list_p - list of the group ACL IDs.
 * @param[in,out] acl_id_cnt_p - In - size of the ACL IDs array,
 *       OUT - number of valid ACL IDs.
 *
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 *
 */
sx_status_t sx_api_acl_group_get(const sx_api_handle_t handle,
                                 const sx_acl_id_t     group_id,
                                 sx_acl_direction_t   *acl_direction_p,
                                 sx_acl_id_t          *acl_id_list_p,
                                 uint32_t             *acl_id_cnt_p);

/**
 *  This function gets a list of valid ACL Group Ids.
 *  Supported devices: Spectrum.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd    GET/GET_NEXT/GET_FIRST
 * @param[in] group_id_key - ACL Group ID to use as Key for GET and GET_NEXT commands.
 * @param[in] acl_filter_p - Filter to use (not supported yet)
 * @param[out] acl_id_list_p - pointer to the list of valid ACL Group IDs returned.
 * @param[in,out] acl_id_cnt_p [in] number of entries to retrieve (max 400); [out] retrieved  number of entries.
 *
 * Input/Output types
 *      - Get first - Get a list of first n entries.  Cmd should be SX_ACCESS_CMD_GET_FIRST and
 *           count should be equal to n. key is irrelevant in this case. Returns number of
 *           entries retrieved as count
 *      -  Get next  - Get n entries after a specified key (it does not have to exist).
 *           Cmd should be SX_ACCESS_CMD_GETNEXT. count should be equal to n.
 *           Returns number of entries retrieved as count
 *      - Get - Gets a specific entry. Cmd should be SX_ACCESS_CMD_GET and count should be 1.
 *       If input count is 0, then returns a count of ACL Group Ids as output instead.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_ERROR if any paramter is in error.
 * @return SX_STATUS_CMD_UNSUPPORTED if command is not supported
 * @return SX_STATUS_INVALID_HANDLE if handle in invalid
 * @return SX_STATUS_ERROR general error.
 */

sx_status_t sx_api_acl_group_iter_get(const sx_api_handle_t  handle,
                                      const sx_access_cmd_t  cmd,
                                      const sx_acl_id_t      group_id_key,
                                      const sx_acl_filter_t *acl_filter_p,
                                      sx_acl_id_t           *acl_id_list_p,
                                      uint32_t              *acl_id_cnt_p);

/**
 *  This function adds/edits/deletes a policy based switching
 *  (PBS) set . Policy based switching entry can be later bound
 *  to an ACL rule in order to specify destination port/port
 *  group (multicast) or send the frame to the router block / fcf block. Use
 *  ADD command to create a PBS entry, note that this operation
 *  may fail if no HW resources are available. PBS entry can be
 *  created without ports in order to ensure future HW resource
 *  availability. Use ADD_PORTS and DELETE_PORTS access command
 *  to edit the entry
 *  - unicast entry can have up to 1 port only. Use DELETE
 *  command to clear a PBS record (not allowed when this record
 *  is in use by ACL rules)
 *  Supported devices: SwitchX, SwitchX2, Spectrum.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - ADD / ADD_PORTS / DELETE_PORTS / DELETE
 * @param[in] pbs_entry - struct for PBS attributes
 * @param[in,out] pbs_id - Port range comparison ID
 *
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if element is not found in DB
 * @return  SX_STATUS_NO_RESOURCES if there are no HW resources for PBS creation
 * @return SX_STATUS_RESOURCE_IN_USE if the PBS record is in use
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO in case of HW failure
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_CMD_UNSUPPORTED if unsupported command is requested
 * @return SX_STATUS_INVALID_HANDLE: Invalid Handle
 */
sx_status_t sx_api_acl_policy_based_switching_set(const sx_api_handle_t     handle,
                                                  const sx_access_cmd_t     cmd,
                                                  const sx_swid_t           swid,
                                                  const sx_acl_pbs_entry_t *pbs_entry_p,
                                                  sx_acl_pbs_id_t          *pbs_id_p);

/**
 *  This function is used to get a PBS set or to count ports of
 *  a PBS set. note that for GET command the pbs_entry should be
 *  pre-allocated and pbs_entry port_num should be updated to
 *  maximal port count to get.
 *  Supported devices: SwitchX, SwitchX2, Spectrum.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - COUNT / GET
 * @param[in] swid - SWID of the PBS entry
 * @param[in] pbs_id - Port based switching entry ID
 * @param[in,out] pbs_entry - struct for Policy based switching
 *       entry attributes. IN - max port number to retrieve. OUT
 *       - actual number of ports retrieved.
 *
 * @return SX_STATUS_SUCCESS if operation completes
 *          successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if ACL element is not found in DB
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO in case of HW failure
 * @return SX_STATUS_CMD_UNSUPPORTED if unsupported command is
 *         requested
 * @return SX_STATUS_INVALID_HANDLE: Invalid Handle
 */
sx_status_t sx_api_acl_policy_based_switching_get(const sx_api_handle_t handle,
                                                  const sx_access_cmd_t cmd,
                                                  const sx_swid_t       swid,
                                                  const sx_acl_pbs_id_t pbs_id,
                                                  sx_acl_pbs_entry_t   *pbs_entry_p);

/**
 *  This function adds/edits/deletes a Layer 4 port range comparison set (up to SX_ACL_MAX_PORT_RANGES).
 *  Use this comparison set for ACL IPv4 IPv6 full key.
 *  When ADD command is used the given ranges are written into a group and its ID is returned.
 *  When EDIT command is used the given range is written into a group of range_index.
 *  When DELETE command is used the given range_index configuration is cleared.
 *  Port range comparison set cannot be deleted if it is applied to an acl rule.
 *  Supported devices: SwitchX, SwitchX2, Spectrum.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - ADD / EDIT / DELETE
 * @param[in] l4_port_range - struct for Layer 4 port range comparison
 * @param[in, out] range_id - Port range comparison ID
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO: Message size error
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT: Message size error
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if ACL element is not found in DB
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO in case of HW failure
 * @return SX_STATUS_CMD_UNSUPPORTED if unsupported command is requested
 * @return SX_STATUS_INVALID_HANDLE: Invalid Handle
 */
sx_status_t sx_api_acl_l4_port_range_set(const sx_api_handle_t            handle,
                                         const sx_access_cmd_t            cmd,
                                         const sx_acl_port_range_entry_t *l4_port_range_p,
                                         sx_acl_port_range_id_t          *range_id_p);

/**
 *  This function is used to get a Layer 4 port range comparison set.
 *  Supported devices: SwitchX, SwitchX2, Spectrum.
 *
 * @param[in] handle - SX-API handle
 * @param[in] range_id - Port range comparison ID
 * @param[out] l4_port_range - struct for Layer 4 port range comparison
 *
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO: Message size error
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT: Message size error
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if ACL element is not found in DB
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO in case of HW failure
 * @return SX_STATUS_INVALID_HANDLE: Invalid Handle
 */

sx_status_t sx_api_acl_l4_port_range_get(const sx_api_handle_t        handle,
                                         const sx_acl_port_range_id_t range_id,
                                         sx_acl_port_range_entry_t   *l4_port_range_p);

/**
 *  This function gets a list of ACL L4 Port Range IDs
 *  Supported devices: Spectrum.
 * @param[in] handle - SX-API handle.
 * @param[in] cmd    GET/GET_NEXT/GET_FIRST
 * @param[in] range_id_key -Range ID to use as Key for GET and GET_NEXT commands.
 * @param[in] range_id_filter_p - Filter to use (not supported yet)
 * @param[out] range_id_list_p - pointer to the list of Range IDs returned.
 * @param[in,out] range_id_cnt_p [in] number of entries to retrieve (max 16); [out] retrieved  number of entries.
 *
 * Input/Output types
 *      - Get first - Get a list of first n entries.  Cmd should be SX_ACCESS_CMD_GET_FIRST and
 *           count should be equal to n. key is irrelevant in this case. Returns number of
 *           entries retrieved as count
 *      -  Get next  - Get n entries after a specified key (it does not have to exist).
 *           Cmd should be SX_ACCESS_CMD_GETNEXT. count should be equal to n.
 *           Returns number of entries retrieved as count
 *      - Get - Gets a specific entry. Cmd should be SX_ACCESS_CMD_GET and count should be 1.
 *       If input count is 0, then returns a count of Range Ids as output instead.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_ERROR if any paramter is in error.
 * @return SX_STATUS_CMD_UNSUPPORTED if command is not supported
 * @return SX_STATUS_INVALID_HANDLE if handle in invalid
 * @return SX_STATUS_ERROR general error.
 */

sx_status_t sx_api_acl_l4_port_range_iter_get(const sx_api_handle_t             handle,
                                              const sx_access_cmd_t             cmd,
                                              const sx_acl_port_range_id_t      range_id_key,
                                              const sx_acl_port_range_filter_t *range_id_filter_p,
                                              sx_acl_port_range_id_t           *range_id_list_p,
                                              uint32_t                         *range_id_cnt_p);

/**
 *  This function is used for inserting rules into an ACL
 *  region. Inserting rules is allowed before and after bind
 *  operation. Rule is inserted to an explicit offset,
 *  overriding existing rule on that offset. Rules must have the
 *  same key type as the ACL region.
 *  Supported devices: SwitchX, SwitchX2, Spectrum.
 *
 *  When in 802.1D mode, instead of providing a vid(Vlan ID) in
 *  rules[].key.fields.key_type.vid (if present in the key_type) and
 *  rules[].mask.fields.key_type.vid (if present) and
 *  rules[].action.basic_action.vid (if present),
 *  you should provide a bridge_id.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - SET / DELETE
 * @param[in] region_id - ACL region ID
 * @param[in] rules_p - array of structs representing rule
 *       content. should be in size of num_of_rules
 * @param[in] num_of_rules - number of rules to configure
 *       (number of elements in the array)
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if ACL element is not found in DB
 * @return SX_STATUS_NO_RESOURCES if there is no more space for rules
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO in case of HW failure
 * @return SX_STATUS_CMD_UNSUPPORTED if unsupported command is requested
 */
sx_status_t sx_api_acl_rules_set(const sx_api_handle_t    handle,
                                 const sx_access_cmd_t    cmd,
                                 const sx_acl_region_id_t region_id,
                                 const sx_acl_rule_t     *rules_list_p,
                                 const uint32_t           rules_cnt);

/**
 *  This function is used for getting rules of an ACL block.
 *
 *  When in 802.1D mode, instead of receiving a vid(Vlan ID),
 *  on rules[].key.fields.key_type.vid, rules[].mask.fields.key_type.vid and
 *  rules[].action.basic_action.vid, a bridge_id's are provided.
 *  Supported devices: SwitchX, SwitchX2, Spectrum.
 *
 * @param[in] handle - SX-API handle
 * @param[in] region_id - ACL region ID
 * @param[in] start_offset - Start offset within the region
 * @param[out] rules_p - pointer to array of structs
 *       representing rule content. should be in size of
 *       num_of_rules.
 * @param[in,out] num_of_rules - IN - number of rules to
 *       get (number of elements in the array), OUT - number of
 *       rules that were actually read from ACL table
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if ACL element is not found in DB
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO in case of HW failure requested
 */
sx_status_t sx_api_acl_rules_get(const sx_api_handle_t      handle,
                                 const sx_acl_region_id_t   region_id,
                                 const sx_acl_rule_offset_t start_offset,
                                 sx_acl_rule_t             *rules_list_p,
                                 uint32_t                  *rules_cnt_p);

/**
 *  This function is used for getting the activity of a specific rule.
 *  If the region is not bound, activity_p is invalid.
 *  Supported devices: SwitchX, SwitchX2, Spectrum.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - READ / READ_CLEAR
 * @param[in] region_id - ACL region ID
 * @param[in] rule_offset - ACL Rule offset within the region
 * @param[out] activity_p - ACL Rule activity
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if ACL element is not found in DB
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO in case of HW failure requested
 */
sx_status_t sx_api_acl_rule_activity_get(const sx_api_handle_t      handle,
                                         const sx_access_cmd_t      cmd,
                                         const sx_acl_region_id_t   region_id,
                                         const sx_acl_rule_offset_t rule_offset,
                                         boolean_t                 *activity_p);

/**
 *  This function is used for moving a block of rules within an
 *  ACL region. Moving is allowed before and after ACL bind.
 *  Moving a block does not affect search hits, but may override
 *  existing rules if such exist on the new block location.
 *  Non-valid rules within the block are moved as well.
 *  Supported devices: SwitchX, SwitchX2, Spectrum.
 *
 * @param[in] handle - SX-API handle
 * @param[in] region_id - ACL region ID
 * @param[in] block_start - Rules block start offset within the
 *       ACL block
 * @param[in] block_size - Number of rules to move within the
 *       block
 * @param[in] new_block_start - New offset of the first rule of
 *       the given rules block
 *
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if ACL element is not found in DB
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO in case of HW failure
 */
sx_status_t sx_api_acl_rule_block_move_set(const sx_api_handle_t      handle,
                                           const sx_acl_region_id_t   region_id,
                                           const sx_acl_rule_offset_t block_start,
                                           const sx_acl_size_t        block_size,
                                           const sx_acl_rule_offset_t new_block_start);

/**
 *  This function is used to bind/unbind ACL or ACL group to a
 *  port (or LAG). Binding more than one ACL to port may be
 *  achieved by using ACL groups.
 *  Binding may fail if there is no place for the ACL in HW
 *  Supported devices: SwitchX, SwitchX2, Spectrum.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - BIND / UNBIND
 * @param[in] log_port - logical port ID to bind
 * @param[in] acl_id - ACL ID given for ACL or ACL group
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if ACL element is not found in DB
 * @return SX_STATUS_NO_RESOURCES if no ACL is available to create
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO in case of HW failure
 * @return SX_STATUS_CMD_UNSUPPORTED if unsupported command is requested
 */
sx_status_t sx_api_acl_port_bind_set(const sx_api_handle_t  handle,
                                     const sx_access_cmd_t  cmd,
                                     const sx_port_log_id_t log_port,
                                     const sx_acl_id_t      acl_id);

/**
 *  This function is used to get the ACL ID  of an ACL table or
 *  ACL group which is bound to a specific port
 *  Supported devices: SwitchX, SwitchX2, Spectrum.
 *
 * @param[in] handle - SX-API handle
 * @param[in] log_port - logical port ID
 * @param[in] acl_direction - ingress or egress ACL
 * @param[out] acl_id_p - ACL ID of an ACL or ACL group
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if port is not bound
 */
sx_status_t sx_api_acl_port_bind_get(const sx_api_handle_t    handle,
                                     const sx_port_log_id_t   log_port,
                                     const sx_acl_direction_t acl_direction,
                                     sx_acl_id_t             *acl_id_p);

/**
 *  This function is used for controlling mapping of vlans into
 *  vlan groups for ACL binding.
 *  CREATE command used for creating a new group, will return a
 *  free group ID if such exist
 *  ADD / DELETE commands are used to control mapping of
 *  SWID,VID to an existing vlan group
 *  DESTROY command is used to free a vlan group resource
 *
 *  This function is only valid when in 802.1Q mode.
 *  Supported devices: SwitchX, SwitchX2, Spectrum.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - CREATE / ADD / DELETE / DESTROY
 * @param[in] swid - SWID (used only with ADD/DELETE)
 * @param[in,out] group_id - vlan group ID
 * @param[in] vlan_list - a list of vlans to attach to this
 *       group
 * @param[in] vlan_num - number of elements in the vlan list
 *
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 * @return SX_STATUS_NO_RESOURCES if no group is available to create
 * @return SX_STATUS_CMD_UNSUPPORTED if unsupported command is requested
 */
sx_status_t sx_api_acl_vlan_group_map_set(const sx_api_handle_t handle,
                                          const sx_access_cmd_t cmd,
                                          const sx_swid_id_t    swid,
                                          const sx_vlan_id_t   *vlan_list_p,
                                          const uint32_t        vlan_cnt,
                                          sx_acl_vlan_group_t  *group_id_p);

/**
 *  This function is used for getting the current mapping of
 *  vlans into vlan groups for ACL binding.
 *  the vlan_list parameter are arrays at the size of
 *  vlan_num which is filled by this function. the actual
 *  size is then returned as output.
 *
 *  This function is only valid when in 802.1Q mode.
 *  Supported devices: SwitchX, SwitchX2, Spectrum.
 *
 * @param[in] handle - SX-API handle
 * @param[in] swid - SWID
 * @param[in] group_id - vlan group ID
 * @param[out] vlan_list - list of vlans which are members in
 *       this vlan group (in the given SWID)
 * @param[in,out] vlan_num - IN - number of elements allocated
 *       in the mapping entries arrays, OUT - number of actual
 *       elements found
 *
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 * @return SX_STATUS_CMD_UNSUPPORTED if 802.1D mode is enabled
 */
sx_status_t sx_api_acl_vlan_group_map_get(const sx_api_handle_t     handle,
                                          const sx_swid_id_t        swid,
                                          const sx_acl_vlan_group_t group_id,
                                          sx_vlan_id_t             *vlan_list_p,
                                          uint32_t                 *vlan_cnt_p);

/**
 *  This function is used to bind/unbind ACL to vlan group.
 *  Binding more than one ACL to vlan group is allowed. Binding
 *  may fail if there is no place for the ACL in HW
 *
 *  When in 802.1D mode, instead of providing a Vlan group,
 *  you should provide a bridge_id.
 *  Supported devices: SwitchX, SwitchX2, Spectrum.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - BIND / UNBIND
 * @param[in] vlan_group - Vlan Group ID to bind
 * @param[in] acl_id - ACL ID of an ACL or ACL Group
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if ACL element is not found in DB
 * @return SX_STATUS_NO_RESOURCES if no ACL is available to create
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO in case of HW failure
 * @return SX_STATUS_CMD_UNSUPPORTED if unsupported command is requested
 */
sx_status_t sx_api_acl_vlan_group_bind_set(const sx_api_handle_t     handle,
                                           const sx_access_cmd_t     cmd,
                                           const sx_acl_vlan_group_t vlan_group,
                                           const sx_acl_id_t         acl_id);

/**
 *  This function is used to get the ACL ID  of an ACL table or
 *  ACL group which is bound to a specific vlan group
 *
 *  When in 802.1D mode, instead of providing a Vlan group,
 *  you should provide a bridge_id.
 *  Supported devices: SwitchX, SwitchX2, Spectrum.
 *
 * @param[in] handle - SX-API handle
 * @param[in] vlan_group - Vlan Group ID
 * @param[in] acl_direction - ingress or egress ACL
 * @param[out] acl_id_p - ACL ID of an ACL or ACL Group
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 *  @return SX_STATUS_PARAM_NULL or SX_STATUS_PARAM_EXCEEDS_RANGE if any input
 *  parameter is invalid
 *  @return SX_STATUS_ENTRY_NOT_FOUND if vlan group is not bound
 */
sx_status_t sx_api_acl_vlan_group_bind_get(const sx_api_handle_t     handle,
                                           const sx_acl_vlan_group_t vlan_group,
                                           const sx_acl_direction_t  acl_direction,
                                           sx_acl_id_t              *acl_id_p);

/**
 *  This function returns attributes of the flexible key.
 *
 *  Supported devices: Spectrum.
 *
 * @param[in] handle                - SX-API handle
 * @param[in] key_handle            - The handle to flexible key
 * @param[out] key_width_p          - Key width
 *
 * @return SX_STATUS_SUCCESS            operation completes successfully
 * @return SX_STATUS_PARAM_ERROR        any input parameters is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND    the key handle is wrong
 */
sx_status_t sx_api_acl_flex_key_attr_get(const sx_api_handle_t    handle,
                                         const sx_acl_key_type_t  key_handle,
                                         sx_acl_flex_key_attr_t * key_attr_p);

/**
 *  The key will be composed from predefined filter blocks of 9B keys by SCP algorithm and it maximum size is bounded to 54B.
 *   Key creation is pure DB operation. The maximum number of keys is equal to the maximum number of regions.
 *
 *  Supported devices: Spectrum.
 *
 * @param[in] handle                    - SX-API handle
 * @param[in] cmd                       - The access cmd CREATE/DELETE
 * @param[in] key_list_p                - Array of basic key ID's
 * @param[in] key_cnt                   - Number of elements in basic key array
 * @param[out] key_handle_p             - The handle to created flexible key
 *
 * @return  SX_STATUS_SUCCESS       operation completes successfully
 * @return  SX_STATUS_PARAM_ERROR   any input parameters is invalid
 * @return  SX_STATUS_UNSUPPORTED   the wanted key cannot be created
 * @return  SX_STATUS_ERROR         general error
 */
sx_status_t sx_api_acl_flex_key_set(const sx_api_handle_t handle,
                                    const sx_access_cmd_t cmd,
                                    const sx_acl_key_t  * key_list_p,
                                    const uint32_t        key_count,
                                    sx_acl_key_type_t   * key_handle_p);

/**
 *  This function returns list of filters included in the flexible key.
 *  The user is responsible for a memory management of the filters list.
 *
 *  Supported devices: Spectrum.
 *
 * @param[in] handle                - SX-API handle
 * @param[in] key_handle            - The handle to flexible key
 * @param[out] key_list_p           - Array of basic key ID's
 * @param[in, out] key_count_p      - Number of elements in basic key array
 *                                    on return will contain the actual number
 *                                    of elements copied to the array.
 *
 * @return SX_STATUS_SUCCESS            operation completes successfully
 * @return SX_STATUS_PARAM_ERROR        any input parameters is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND    the key handle is wrong
 */
sx_status_t sx_api_acl_flex_key_get(const sx_api_handle_t   handle,
                                    const sx_acl_key_type_t key_handle,
                                    sx_acl_key_t           *key_list_p,
                                    uint32_t              * key_count_p);


/**
 * ACL rule is added or removed from a certain ACL region. The user is responsible for memory management -
 * it is necessary to initialize each member of rules_list_p using call to sx_lib_flex_acl_rule_init before calling this API
 * and de-initialize using call to sx_lib_flex_acl_rule_deinit after calling this API.
 * This operation configures HW if the ACL is bound to a device.
 * The configured rule is overrides the given offset with the new rule.
 * The flexible ACL allows to the user to define set of filters that are subset of the key assigned to the region.
 * Also the user can define a custom set of actions for each rule. The function should be called after bind ACL to region.
 * If an offset in offsets array crosses the boundaries of the region allocation the function will fail.
 *
 *  Supported devices: Spectrum.
 *
 * @param[in] handle                - SX-API handle
 * @param[in] cmd                   - The access command SET/DELETE
 * @param[in] region_id             - ACL region ID received on a region creation
 * @param[in] offsets_list_p        - array of rule offset into region directly associated with the appropriate item on in array of rules
 * @param[in] rules_list_p          - Array of structures describing the flexible rule content (see the next table)
 * @param[in] rules_cnt             - Number of elements in array of flexible rule descriptors
 *
 *  @return SX_STATUS_SUCCESS           The operation completed successfully
 *  @return SX_STATUS_CMD_UNSUPPORTED   The sent command is unsupported
 *  @return SX_STATUS_PARAM_ERROR       Invalid parameter
 *  @return SX_STATUS_ENTRY_NOT_FOUND   Wrong region ID
 *  @return SX_STATUS_NO_RESOURCES      No more space for rules. Cannot allocate space for all actions
 *
 */
sx_status_t sx_api_acl_flex_rules_set(const sx_api_handle_t          handle,
                                      const sx_access_cmd_t          cmd,
                                      const sx_acl_region_id_t       region_id,
                                      sx_acl_rule_offset_t          *offsets_list_p,
                                      const sx_flex_acl_flex_rule_t *rules_list_p,
                                      const uint32_t                 rules_cnt);


/**
 *
 * This function returns list of rules associated with particular region. The user is responsible for memory management -
 * it is necessary to initialize each member of rules_list_p using call to sx_lib_flex_acl_rule_init before calling this API and
 * de-initialize using call to sx_lib_flex_acl_rule_deinit after calling this API.
 *
 *  If the function is called with rules_list_p parameter set to NULL or *rules_cnt_p set to 0, it
 * will return the actual number of rules set to the region.
 *
 *  If the function is called with key_desc_list_p and action_list_p parameter of each of the rules in rules_list_p set
 * to NULL and offset_list_p array filled with zeroes - it will return the actual number of keys and actions for each valid rule
 * starting from offset 0, as well as the rule's offset in offset list for this rule.
 *
 *  If the function is called with key_desc_list_p and action_list_p parameter of each of the rules in rules_list_p set
 * to NULL, but offset_list_p array is filled with non-zero values - it will return the actual number of keys and actions for each valid rule
 * according to the offset, which is defined in the offset list. In this case the offset list should be filled with offsets of the rules,
 * which are valid.
 *
 *  If the function is called with key_desc_list_p and action_list_p parameter of each of the rules in rules_list_p set
 * to non-NULL, it is assumed that rule structures are allocated for all rules in the list. It also assumed that the offset list
 * is filled with real offsets of the rules in the same order as in the rules list.
 *
 * On Api call the key_desc_count and action_count of each sx_flex_acl_flex_rule_t should contain number of allocated
 * items, on API return these parameters will contain actual number of items. The offset list should contain offsets of valid rules only.
 *
 *
 *  Supported devices: Spectrum.
 *
 * @param[in] handle                - SX-API handle
 * @param[in] region_id             - ACL region ID received on a region creation
 * @param[in, out] offsets_list_p       - array of rule offset into region directly associated with the appropriate item on in array of rules
 * @param[out] rules_list_p         - Array of structures describing the flexible rule content (see the next table)
 * @param[in, out] rules_cnt        - Desirable number of elements in array of flexible rule descriptors. Function return
 *
 *  @return SX_STATUS_SUCCESS           The operation completed successfully
 *  @return SX_STATUS_ENTRY_NOT_FOUND   Wrong region ID
 *  @return SX_STATUS_PARAM_ERROR       Invalid parameter
 *
 */
sx_status_t sx_api_acl_flex_rules_get(const sx_api_handle_t    handle,
                                      const sx_acl_region_id_t region_id,
                                      sx_acl_rule_offset_t    *offsets_list_p,
                                      sx_flex_acl_flex_rule_t *rules_list_p,
                                      uint32_t               * rules_cnt_p);


/**
 *  This function is used to bind/unbind ACL or ACL group to RIF
 *
 *  Supported devices: Spectrum.
 *
 * @param[in] handle                - SX-API handle
 * @param[in] cmd                   - The command BIND/UNBIND
 * @param[in] rif_id                - RIF ID to bind/unbind
 * @param[in] acl_id                - ACL or ACL group ID that is going to be bound to RIF
 *
 *  @return SX_STATUS_SUCCESS           The operation completed successfully
 *  @return SX_STATUS_ENTRY_NOT_FOUND   ACL ID or RIF ID not found in DB
 *  @return SX_STATUS_PARAM_ERROR       Invalid parameter
 *  @return SX_STATUS_CMD_UNSUPPORTED   the given comand is unsupported
 *  @return SX_STATUS_ERROR             The operation cannot be complited
 */
sx_status_t sx_api_acl_rif_bind_set(const sx_api_handle_t handle,
                                    const sx_access_cmd_t cmd,
                                    const sx_rif_id_t     rif_id,
                                    const sx_acl_id_t     acl_id);

/**
 *  This function is used to  get ACL or ACL group ID that bound to RIF
 *
 * Supported devices: Spectrum.
 *
 * @param[in] handle                  - SX-API handle
 * @param[in] rif_id                  - RIF ID
 * @param[in] acl_direction           - The direction of ACL(ingress/egress)
 * @param[out] acl_id_p               - ACL or ACL group ID that is bound to RIF
 *
 *  @return SX_STATUS_SUCCESS   The operation completed successfully
 *  @return SX_STATUS_ENTRY_NOT_FOUND   ACL ID or RIF ID not found in DB
 *  @return SX_STATUS_PARAM_ERROR   Invalid parameter
 */
sx_status_t sx_api_acl_rif_bind_get(const sx_api_handle_t    handle,
                                    const sx_rif_id_t        rif_id,
                                    const sx_acl_direction_t acl_direction,
                                    sx_acl_id_t             *acl_id_p);

/**
 * On ACL module initialization the user can choose the parallel ACL search type. This function is used to support this feature.
 *  It links one ACL group to another. Their relation could be described as "one directional linked list" where the second group is
 *  next to the first one. Only the head of the list of groups is allowed to be bound to port/VLAN/RIF.
 *  The other linked groups will be bound automatically. An attempt to bind explicitly the other but the head will cause to an error.
 *
 *	Supported devices: Spectrum.
 *
 * @param[in] handle                    - SX-API handle
 * @param[in] cmd                       - The command BIND/UNBIND
 * @param[in] parent_group_id           - The first, parent ACL or ACL group ID that second one will be bound to
 * @param[in] group_id                  - The second ACL or ACL group ID that will be bound to the first one
 *
 *  @return SX_STATUS_SUCCESS           The operation completed successfully
 *  @return SX_STATUS_ENTRY_NOT_FOUND   ACL ID not found in DB
 *  @return SX_STATUS_PARAM_ERROR       Invalid parameter
 */
sx_status_t sx_api_acl_group_bind_set(sx_api_handle_t       handle,
                                      const sx_access_cmd_t cmd,
                                      sx_acl_id_t           group_id,
                                      sx_acl_id_t           next_group_id);

/**
 *  This function returns the next ACL group bound to the given one.
 *
 * Supported devices: Spectrum.
 *
 * @param[in] handle                 - SX-API handle
 * @param[in] group_id               - The first, parent ACL or ACL group ID that second one will be bound to
 * @param[out] group_id_p            - The ACL or ACL group ID that bound to the parent. In case of no one is bound
 *                                      to the parent invalid ACL ID will be returned
 *
 *  @return SX_STATUS_SUCCESS           The operation completed successfully
 *  @return SX_STATUS_ENTRY_NOT_FOUND   ACL ID not found in DB
 *  @return SX_STATUS_PARAM_ERROR       Invalid parameter
 */
sx_status_t sx_api_acl_group_bind_get(sx_api_handle_t handle,
                                      sx_acl_id_t     group_id,
                                      sx_acl_id_t   * group_id_p);

/**
 * Manipulate a port list container
 * Command CREATE creates a new container with the specified list of logical ports
 * and returns its new container ID in port_list_id_p.
 * Command SET replaces the contents of an existing container specified by
 * port_list_id_p, with the specified list of logical ports in port_list_p.
 * Command DESTROY deletes an existing container specified by port_list_id_p.
 * Notes: An port list  in use (e.g. by an acl key) cannot be destroyed or modified
 *        A container may contain at most RM_API_ACL_PORT_LIST_MAX logical ports
 *        A container may contain only Ethernet logical ports and not LAG ports
 *
 * Supported devices: Spectrum.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - CREATE/SET/DESTROY.
 * @param[in] port_list_p - Specifies or returns the container ID
 * @param[in] port_list_cnt - Specifies the list of logical ports for the container
 * @param[in/out] port_list_id_p - specifies the id of the port list created/to change
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if specified container ID does not exist.
 * @return SX_STATUS_NO_RESOURCES if there are no resources for the operation.
 * @return SX_STATUS_RESOURCE_IN_USE if group is in use and cannot be destroyed.
 */
sx_status_t sx_api_acl_port_list_set(const sx_api_handle_t     handle,
                                     const sx_access_cmd_t     cmd,
                                     sx_acl_port_list_entry_t *port_list_p,
                                     const uint32_t            port_list_cnt,
                                     sx_acl_port_list_id_t    *port_list_id_p);

/**
 * Retrieve information about a port list container specified by port_list_id.
 * Notes: *port_list_cnt should contain the maximum amount of logical ports to retrieve.
 *        If port_list_p is NULL, then port_list_p are not retrieved at all. In this case port_list_cnt
 *        will contain the actual number if ports in the port list
 *
 * Supported devices: Spectrum.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] port_list_id - specifies the id of the port list to retrieve
 * @param[out] port_list_p -	array of ports to copy into
 * @param[in,out] port_list_cnt_p - Specifies the maximum amount of logical ports to retrieve,
 *                               and returns the amount logical ports retrieved
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported.
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND if specified container does not exist, or no more containers.
 */
sx_status_t sx_api_acl_port_list_get(const sx_api_handle_t       handle,
                                     const sx_acl_port_list_id_t port_list_id,
                                     sx_acl_port_list_entry_t   *port_list_p,
                                     uint32_t                   *port_list_cnt_p);


/**
 *  This function is used to get ACL region HW size .
 *  Supported devices: Spectrum.
 *
 * @param[in] handle - SX-API handle
 * @param[in] region_id - ACL region ID
 * @param[out] region_size_p - The region actual hw size
 *
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 *  @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 * @return SX_STATUS_PARAM_NULL, SX_STATUS_PARAM_ERROR or SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter is invalid
 *
 */
sx_status_t sx_api_acl_region_hw_size_get(const sx_api_handle_t    handle,
                                          const sx_acl_region_id_t region_id,
                                          sx_acl_size_t           *region_size_p);


/**
 * This API creates and deletes the Custom Bytes Set. Currently only 4-bytes sets are supported.
 * Returned value is key Id from sx_acl_key_t space, which should be used with FLEX_ACL_KEY_CUSTOM_BYTES_BYTE
 * macro. Each custom byte is accessed as a separate ACL key.
 *
 * Supported devices: Spectrum.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - CREATE/DESTROY/EDIT.
 * @param[in] custom_bytes_set_attributes - Specifies extraction points data.
 * @param[in/out] custom_bytes_set_key_id_p - Specifies an array of the custom bytes keys id.
 *  For create a list of usable SDK key id is provided. For destory. Only the first key is used to destory the set.
 * @param[in/out] custom_bytes_set_key_id_cnt_p - Specifies how many custum bytes are expected by the user.
 *  The counter is updated with :MIN(available number of bytes in allocated set, Requested number of bytes)
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND if specified container ID does not exist.
 * @return SX_STATUS_NO_RESOURCES if there are no resources for the operation.
 * @return SX_STATUS_RESOURCE_IN_USE if group is in use and cannot be destroyed.
 */
sx_status_t sx_api_acl_custom_bytes_set(sx_api_handle_t                             handle,
                                        sx_access_cmd_t                             cmd,
                                        const sx_acl_custom_bytes_set_attributes_t *custom_bytes_set_attributes,
                                        sx_acl_key_t                               *custom_bytes_set_key_id_p,
                                        uint32_t                                   *custom_bytes_set_key_id_cnt_p);

/**
 *
 * This API returns extraction point parameters of the existing Custom Bytes Set
 *
 * Supported devices: Spectrum.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] custom_bytes_set_key_id_p - Specifies an array of the custom bytes keys id. Only first item
 *                                        in array is provided.
 * @param[out] custom_bytes_key_extraction_point_list_p - Specifies extraction points fetched data.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND if specified container does not exist, or no more containers.
 */
sx_status_t sx_api_acl_custom_bytes_get(sx_api_handle_t                       handle,
                                        sx_acl_key_t                         *custom_bytes_set_key_id_p,
                                        sx_acl_custom_bytes_set_attributes_t *custom_bytes_set_attributes_p);


#endif /* ifndef __SX_API_ACL_H__ */
