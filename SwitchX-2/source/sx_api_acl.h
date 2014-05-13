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

#ifndef __SX_API_ACL_H__
#define __SX_API_ACL_H__

#include <sx/sdk/sx_api.h>


/************************************************
 *  API functions
 ***********************************************/

/**
 * This function sets the log verbosity level of ACL MODULE
 * @param[in] handle                   - SX-API handle
 * @param[in] verbosity_target         - set verbosity of : API / MODULE / BOTH
 * @param[in] module_verbosity_level   - ACL module verbosity level
 * @param[in] api_verbosity_level      - ACL API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 *         SX_STATUS_PARAM_ERROR if any input parameters is invalid
 *         SX_STATUS_ERROR general error
 */
sx_status_t sx_api_acl_log_verbosity_level_set(
		const sx_api_handle_t			handle,
		const sx_log_verbosity_target_t	verbosity_target,
		const sx_verbosity_level_t		module_verbosity_level,
		const sx_verbosity_level_t		api_verbosity_level);

/**
 * This function gets the log verbosity level of ACL MODULE
 *
 * @param[in]  handle                   - SX-API handle
 * @param[in]  verbosity_target         - get verbosity of : API / MODULE / BOTH
 * @param[out] module_verbosity_level_p - ACL module verbosity level
 * @param[out] api_verbosity_level_p    - ACL API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 *         SX_STATUS_PARAM_ERROR if any input parameters is invalid
 *         SX_STATUS_ERROR general error
 */
sx_status_t sx_api_acl_log_verbosity_level_get(
		const sx_api_handle_t			handle,
		const sx_log_verbosity_target_t	verbosity_target,
			  sx_verbosity_level_t		*module_verbosity_level_p,
			  sx_verbosity_level_t		*api_verbosity_level_p);

/**
 *  This function is used to create ACL region (rules list).
 *  for creation use command CREATE and supply key_type and
 *  size. acl_region_id is returned on successful creation.
 *  for destroying an ACL region it is required that the ACL
 *  region is not bound and the acl_region_id should be
 *  provided. EDIT command is used for resizing an existing ACL
 *  region. acl_region_id and new size should be provided.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - CREATE / DESTROY
 * @param[in] key_type - key type used in this ACL
 * @param[in] action_type - type of actions to be used in this
 *       ACL block
 * @param[in] acl_size - maximal number of rules in this ACL
 * @param[in,out] region_id_p - ACL region ID as described above
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 *  @return SX_STATUS_PARAM_NULL or SX_STATUS_PARAM_EXCEEDS_RANGE if any input
 *  parameter is invalid
 *  @return SX_STATUS_ENTRY_NOT_FOUND if requested element is
 *  not found in DB
 *  @return SX_STATUS_NO_RESOURCES if no ACL is available to
 *  create
 *  @return SX_STATUS_CMD_UNSUPPORTED if unsupported command is
 *  requested
 */
sx_status_t sx_api_acl_region_set(
		const sx_api_handle_t          handle,
		const sx_access_cmd_t          cmd,
		const sx_acl_key_type_t        key_type,
		const sx_acl_action_type_t     action_type,
		const sx_acl_size_t            region_size,
			  sx_acl_region_id_t       *region_id_p);

/**
 *  This function is used to get ACL region properties .
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
 * @return SX_STATUS_PARAM_NULL or SX_STATUS_PARAM_EXCEEDS_RANGE
 *  if any input parameter is invalid
 *  @return SX_STATUS_ENTRY_NOT_FOUND if requested element is
 *                             not found in DB
 */
sx_status_t sx_api_acl_region_get(
		const sx_api_handle_t         handle,
		const sx_acl_region_id_t      region_id,
			  sx_acl_key_type_t       *key_type_p,
			  sx_acl_action_type_t    *action_type_p,
			  sx_acl_size_t           *region_size_p);

/**
 *  This function is used to create an ACL . User may create
 *  either a packet type agnostic or a packet type sensitive
 *  ACL. Packet agnostic ACL requires one ACL region while
 *  packet sensitive ACL requires an ordered list of ACL
 *  regions. Use CREATE access command for creating a new ACL,
 *  it will return an ACL id. DESTROY command may be used when
 *  the ACL is not bound to HW.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - CREATE / DESTROY
 * @param[in] acl_type - ACL type of this ACL. some types of
 *       ACLs are packet type sensitive and require several
 *       regions
 * @param[in] acl_direction - ACL direction (ingress or egress
 *       ACL)
 * @param[in] acl_region_group_p - ACL region group matching ACL type
 * @param[in,out] acl_id_p - ACL ID as described above
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 *  @return SX_STATUS_PARAM_NULL or SX_STATUS_PARAM_EXCEEDS_RANGE if any input
 *  parameter is invalid
 *  @return SX_STATUS_ENTRY_NOT_FOUND if requested element is
 *  not found in DB
 *  @return SX_STATUS_NO_RESOURCES if no ACL is available to
 *  create
 *  @return SX_STATUS_CMD_UNSUPPORTED if unsupported command is
 *  requested
 */
sx_status_t sx_api_acl_set(
		const sx_api_handle_t         handle,
		const sx_access_cmd_t         cmd,
		const sx_acl_type_t           acl_type,
		const sx_acl_direction_t      acl_direction,
		const sx_acl_region_group_t   *acl_region_group_p,
			  sx_acl_id_t             *acl_id_p);

/**
 *  This function is used to get ACL attributes . The ACL id is
 *  given and the function returns ACL attributes : type and a
 *  list of attached regions. the length of the regions list
 *  depends on the ACL type
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
sx_status_t sx_api_acl_get(
		const sx_api_handle_t         handle,
		const sx_acl_id_t             acl_id,
			  sx_acl_type_t           *acl_type_p,
			  sx_acl_direction_t      *acl_direction_p,
			  sx_acl_region_group_t   *acl_region_group_p);

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
 * @return SX_STATUS_PARAM_NULL if any input parameter is NULL
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter exceeds its range
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is not found in DB
 * @return SX_STATUS_NO_RESOURCES if no group is available to create
 * @return SX_STATUS_CMD_UNSUPPORTED if unsupported command is requested
 */
sx_status_t sx_api_acl_group_set(
		const sx_api_handle_t     handle,
		const sx_access_cmd_t     cmd,
		const sx_acl_direction_t  acl_direction,
		const sx_acl_id_t         *acl_id_list_p,
		const uint32_t            acl_id_cnt,
			  sx_acl_id_t         *group_id_p);

/**
 *
 *  This function is used to get ACL group attributes . the ACL
 *  group id is given and the function returns ACL group
 *  attributes : direction and a list of attached ACLs.
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
 * @return SX_STATUS_PARAM_NULL or SX_STATUS_PARAM_EXCEEDS_RANGE
 *  if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is
 *  not found in DB
 *
 */
sx_status_t sx_api_acl_group_get(
		const sx_api_handle_t     handle,
		const sx_acl_id_t         group_id,
			  sx_acl_direction_t  *acl_direction_p,
			  sx_acl_id_t         *acl_id_list_p,
			  uint32_t            *acl_id_cnt_p);

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
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - ADD / ADD_PORTS / DELETE_PORTS / DELETE 
 * @param[in] pbs_entry - struct for PBS attributes 
 * @param[in,out] pbs_id - Port range comparison ID
 *
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if any inpu parameter is NULL
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter 
 * exceeds its allowed range 
 * @return SX_STATUS_ENTRY_NOT_FOUND if element is not found in 
 *         DB
 * @return  SX_STATUS_NO_RESOURCES if there are no HW resources 
 *          for PBS creation
 * @return SX_STATUS_RESOURCE_IN_USE if the PBS record is in use
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO in case of HW failure
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_CMD_UNSUPPORTED if unsupported command is requested
 * @return SX_STATUS_INVALID_HANDLE: Invalid Handle
 */
sx_status_t sx_api_acl_policy_based_switching_set(
		const sx_api_handle_t             handle,
		const sx_access_cmd_t             cmd,
		const sx_swid_t                   swid,
		const sx_acl_pbs_entry_t          *pbs_entry_p,
			  sx_acl_pbs_id_t             *pbs_id_p);
                                                    
/**
 *  This function is used to get a PBS set or to count ports of
 *  a PBS set. note that for GET command the pbs_entry should be
 *  pre-allocated and pbs_entry port_num should be updated to
 *  maximal port count to get.
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
 * @return SX_STATUS_PARAM_NULL if any of the input parameters
 *         are NULL
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter 
 *         exceeds its allowed range
 * @return SX_STATUS_ENTRY_NOT_FOUND if ACL element is not found in DB
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO in case of HW failure
 * @return SX_STATUS_CMD_UNSUPPORTED if unsupported command is
 *         requested
 * @return SX_STATUS_INVALID_HANDLE: Invalid Handle
 */
sx_status_t sx_api_acl_policy_based_switching_get(
		const sx_api_handle_t             handle,
		const sx_access_cmd_t             cmd,
		const sx_swid_t                   swid,
		const sx_acl_pbs_id_t             pbs_id,
			  sx_acl_pbs_entry_t          *pbs_entry_p);

/**
 *  This function adds/edits/deletes a Layer 4 port range comparison set (up to SX_ACL_MAX_PORT_RANGES).
 *  Use this comparison set for ACL IPv4 IPv6 full key.
 *  When ADD command is used the given ranges are written into a group and its ID is returned.
 *  When EDIT command is used the given range is written into a group of range_index.
 *  When DELETE command is used the given range_index configuration is cleared.
 *  Port range comparison set cannot be deleted if it is applied to an acl rule.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - ADD / EDIT / DELETE
 * @param[in] l4_port_range - struct for Layer 4 port range comparison
 * @param[in, out] range_id - Port range comparison ID
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO: Message size error
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT: Message size error
 * @return SX_STATUS_PARAM_NULL or SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if ACL element is not found in DB
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO in case of HW failure
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_CMD_UNSUPPORTED if unsupported command is requested
 * @return SX_STATUS_INVALID_HANDLE: Invalid Handle
 */
sx_status_t sx_api_acl_l4_port_range_set(
		const sx_api_handle_t            handle,
		const sx_access_cmd_t            cmd,
		const sx_acl_port_range_entry_t  *l4_port_range_p,
			  sx_acl_port_range_id_t     *range_id_p);

/**
 *  This function is used to get a Layer 4 port range comparison set.
 *
 * @param[in] handle - SX-API handle
 * @param[in] range_id - Port range comparison ID
 * @param[out] l4_port_range - struct for Layer 4 port range comparison
 *
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_MESSAGE_SIZE_ZERO: Message size error
 * @return SX_STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT: Message size error
 * @return SX_STATUS_PARAM_NULL or SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if ACL element is not found in DB
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO in case of HW failure
 * @return SX_STATUS_INVALID_HANDLE: Invalid Handle
 */

sx_status_t sx_api_acl_l4_port_range_get(
		const sx_api_handle_t            handle,
		const sx_acl_port_range_id_t     range_id,
			  sx_acl_port_range_entry_t  *l4_port_range_p);

/**
 *  This function is used for inserting rules into an ACL
 *  region. Inserting rules is allowed before and after bind
 *  operation. Rule is inserted to an explicit offset,
 *  overriding existing rule on that offset. Rules must have the
 *  same key type as the ACL region.
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
 *  @return SX_STATUS_PARAM_NULL or SX_STATUS_PARAM_EXCEEDS_RANGE if any input
 *  parameter is invalid
 *  @return SX_STATUS_ENTRY_NOT_FOUND if ACL element is not
 *  found in DB
 *  @return SX_STATUS_NO_RESOURCES if there is no more space for
 *  rules
 *  @return SX_STATUS_SXD_RETURNED_NON_ZERO in case of HW
 *  failure
 *  @return SX_STATUS_CMD_UNSUPPORTED if unsupported command is
 *  requested
 */
sx_status_t sx_api_acl_rules_set(
		const sx_api_handle_t         handle,
		const sx_access_cmd_t         cmd,
		const sx_acl_region_id_t      region_id,
		const sx_acl_rule_t           *rules_list_p,
		const uint32_t                rules_cnt);

/**
 *  This function is used for getting rules of an ACL block.
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
 * @return SX_STATUS_PARAM_NULL or SX_STATUS_PARAM_EXCEEDS_RANGE if any input
 *  parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if ACL element is not
 *  found in DB
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO in case of HW
 *  failure requested
 */
sx_status_t sx_api_acl_rules_get(
		const sx_api_handle_t         handle,
		const sx_acl_region_id_t      region_id ,
		const sx_acl_rule_offset_t    start_offset,
			  sx_acl_rule_t           *rules_list_p,
			  uint32_t                *rules_cnt_p);

/**
 *  This function is used for getting rules of an ACL block.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - READ / READ_CLEAR
 * @param[in] region_id - ACL region ID
 * @param[in] rule_offset - ACL Rule offset within the region
 * @param[out] activity_p - ACL Rule activity
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL or SX_STATUS_PARAM_EXCEEDS_RANGE if any input
 *  parameter is invalid
 * @return SX_STATUS_ENTRY_NOT_FOUND if ACL element is not
 *  found in DB
 * @return SX_STATUS_SXD_RETURNED_NON_ZERO in case of HW
 *  failure requested
 */
sx_status_t sx_api_acl_rule_activity_get(
		const sx_api_handle_t         handle,
		const sx_access_cmd_t         cmd,
		const sx_acl_region_id_t      region_id,
		const sx_acl_rule_offset_t    rule_offset,
			  boolean_t               *activity_p);

/**
 *  This function is used for moving a block of rules within an
 *  ACL region. Moving is allowed before and after ACL bind.
 *  Moving a block does not affect search hits, but may override
 *  existing rules if such exist on the new block location.
 *  Non-valid rules within the block are moved as well.
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
 *  @return SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter
 *  is invalid
 *  @return SX_STATUS_ENTRY_NOT_FOUND if ACL element is not
 *  found in DB
 *  @return SX_STATUS_SXD_RETURNED_NON_ZERO in case of HW
 *          failure
 */
sx_status_t sx_api_acl_rule_block_move_set(
		const sx_api_handle_t         handle,
		const sx_acl_region_id_t      region_id,
		const sx_acl_rule_offset_t    block_start,
		const sx_acl_size_t           block_size,
		const sx_acl_rule_offset_t    new_block_start);

/**
 *  This function is used to bind/unbind ACL or ACL group to a
 *  port (or LAG). Binding more than one ACL to port may be
 *  achieved by using ACL groups.
 *  Binding may fail if there is no place for the ACL in HW
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - BIND / UNBIND
 * @param[in] log_port - logical port ID to bind
 * @param[in] acl_id - ACL ID given for ACL or ACL group
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 *  @return SX_STATUS_PARAM_NULL or SX_STATUS_PARAM_EXCEEDS_RANGE if any input
 *  parameter is invalid
 *  @return SX_STATUS_ENTRY_NOT_FOUND if ACL element is not
 *  found in DB
 *  @return SX_STATUS_NO_RESOURCES if no ACL is available to
 *  create
 *  @return SX_STATUS_SXD_RETURNED_NON_ZERO in case of HW
 *  failure
 *  @return SX_STATUS_CMD_UNSUPPORTED if unsupported command is
 *  requested
 */
sx_status_t sx_api_acl_port_bind_set(
		const sx_api_handle_t               handle,
		const sx_access_cmd_t               cmd,
		const sx_port_log_id_t              log_port,
		const sx_acl_id_t                   acl_id);

/**
 *  This function is used to get the ACL ID  of an ACL table or
 *  ACL group which is bound to a specific port
 *
 * @param[in] handle - SX-API handle
 * @param[in] log_port - logical port ID
 * @param[in] acl_direction - ingress or egress ACL
 * @param[out] acl_id_p - ACL ID of an ACL or ACL group
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 *  @return SX_STATUS_PARAM_NULL or SX_STATUS_PARAM_EXCEEDS_RANGE if any input
 *  parameter is invalid
 *  @return SX_STATUS_ENTRY_NOT_FOUND if port is not bound
 */
sx_status_t sx_api_acl_port_bind_get(
		const sx_api_handle_t               handle,
		const sx_port_log_id_t              log_port,
		const sx_acl_direction_t            acl_direction,
		      sx_acl_id_t                   *acl_id_p);

/**
 *  This function is used for controlling mapping of vlans into
 *  vlan groups for ACL binding.
 *  CREATE command used for creating a new group, will return a
 *  free group ID if such exist
 *  ADD / DELETE commands are used to control mapping of
 *  SWID,VID to an existing vlan group
 *  DESTROY command is used to free a vlan group resource
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
 * @return SX_STATUS_PARAM_NULL or SX_STATUS_PARAM_EXCEEDS_RANGE if any input
 *  parameter is invalid
 *  @return SX_STATUS_ENTRY_NOT_FOUND if requested element is
 *  not found in DB
 *  @return SX_STATUS_NO_RESOURCES if no group is available to
 *  create
 *  @return SX_STATUS_CMD_UNSUPPORTED if unsupported command is
 *  requested
 */
sx_status_t sx_api_acl_vlan_group_map_set(
		const sx_api_handle_t      handle,
		const sx_access_cmd_t      cmd,
		const sx_swid_id_t         swid,
		const sx_vlan_id_t         *vlan_list_p,
		const uint32_t             vlan_cnt,
			  sx_acl_vlan_group_t  *group_id_p);

/**
 *  This function is used for getting the current mapping of
 *  vlans into vlan groups for ACL binding.
 *  the vlan_list parameter are arrays at the size of
 *  vlan_num which is filled by this function. the actual
 *  size is then returned as output.
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
 * @return SX_STATUS_PARAM_NULL or SX_STATUS_PARAM_EXCEEDS_RANGE if any input
 *  parameter is invalid
 *  @return SX_STATUS_ENTRY_NOT_FOUND if requested element is
 *  not found in DB
 */
sx_status_t sx_api_acl_vlan_group_map_get(
		const sx_api_handle_t      handle,
		const sx_swid_id_t         swid,
		const sx_acl_vlan_group_t  group_id,
			  sx_vlan_id_t         *vlan_list_p,
			  uint32_t             *vlan_cnt_p);

/**
 *  This function is used to bind/unbind ACL to vlan group.
 *  Binding more than one ACL to vlan group is allowed. Binding
 *  may fail if there is no place for the ACL in HW
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - BIND / UNBIND
 * @param[in] vlan_group - logical port ID to bind
 * @param[in] acl_id - ACL ID of an ACL or ACL list
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 *  @return SX_STATUS_PARAM_EXCEEDS_RANGE if any input parameter
 *  is invalid
 *  @return SX_STATUS_ENTRY_NOT_FOUND if ACL element is not
 *  found in DB
 *  @return SX_STATUS_NO_RESOURCES if no ACL is available to
 *  create
 *  @return SX_STATUS_SXD_RETURNED_NON_ZERO in case of HW
 *  failure
 *  @return SX_STATUS_CMD_UNSUPPORTED if unsupported command is
 *  requested
 */
sx_status_t sx_api_acl_vlan_group_bind_set(
		const sx_api_handle_t             handle,
		const sx_access_cmd_t             cmd,
		const sx_acl_vlan_group_t         vlan_group,
		const sx_acl_id_t                 acl_id);

/**
 *  This function is used to get the ACL ID  of an ACL table or
 *  ACL group which is bound to a specific vlan group
 *
 * @param[in] handle - SX-API handle
 * @param[in] vlan_group - vlan_group ID
 * @param[in] acl_direction - ingress or egress ACL
 * @param[out] acl_id_p - ACL ID of an ACL or ACL list
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 *  @return SX_STATUS_PARAM_NULL or SX_STATUS_PARAM_EXCEEDS_RANGE if any input
 *  parameter is invalid
 *  @return SX_STATUS_ENTRY_NOT_FOUND if vlan group is not bound
 */
sx_status_t sx_api_acl_vlan_group_bind_get(
		const sx_api_handle_t             handle,
		const sx_acl_vlan_group_t         vlan_group,
		const sx_acl_direction_t          acl_direction,
			  sx_acl_id_t                 *acl_id_p);

#endif



