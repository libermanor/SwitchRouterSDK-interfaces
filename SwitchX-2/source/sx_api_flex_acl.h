/*
 *  Copyright (C) 2015-2016. Mellanox Technologies, Ltd. ALL RIGHTS RESERVED.
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

#ifndef SX_API_FLEX_ACL_H_
#define SX_API_FLEX_ACL_H_


#include <sx/sdk/sx_flex_acl.h>
/************************************************
 *  API functions
 ***********************************************/

/**
 *  This function is used to create the flexible key.
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
 * If the function is called with rules_list_p parameter set to NULL, it will return the actual number of rules set to the region.
 * If the function is called with key_desc_list_p and action_list_p parameter of rules_list_p set to NULL it will return the
 * actual number of keys and/or action for the specific rule - in this case all key_desc_list_p and action_list_p pointers
 * must be NULL.
 *
 *  Supported devices: Spectrum.
 *
 * @param[in] handle                - SX-API handle
 * @param[in] region_id             - ACL region ID received on a region creation
 * @param[out] offsets_list_p       - array of rule offset into region directly associated with the appropriate item on in array of rules
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


#endif /* SX_API_FLEX_ACL_H_ */
