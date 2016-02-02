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


#ifndef SX_LIB_FLEX_ACL_H_
#define SX_LIB_FLEX_ACL_H_

#include <sx/sdk/sx_api.h>
#include <sx/sdk/sx_flex_acl.h>


/**
 * Initialize and prepare ACL rule API structure. This API must be used before
 * call to SDK ACL rule API.
 *
 * @param[in] key_handle           - key handle from desired region
 * @param[in] num_of_actions       - desired num of actions in rule
 * @param[in, out] rule            - The pointer to rule
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_MEMORY_ERROR error handling memory
 */
sx_status_t sx_lib_flex_acl_rule_init(const sx_acl_key_type_t  key_handle,
                                      uint32_t                 num_of_actions,
                                      sx_flex_acl_flex_rule_t *rule);


/**
 * Deinitialize ACL rule API structure. This API must be used after call to
 * SDK API which uses the rule structure.
 *
 * @param[in, out] rule            - The pointer to rule
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_MEMORY_ERROR error handling memory
 */
sx_status_t sx_lib_flex_acl_rule_deinit(sx_flex_acl_flex_rule_t *rule);

#endif /* SX_LIB_FLEX_ACL_H_ */
