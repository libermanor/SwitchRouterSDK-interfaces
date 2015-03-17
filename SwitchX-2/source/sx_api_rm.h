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

#ifndef __SX_API_RM_H__
#define __SX_API_RM_H__

#include <sx/sdk/sx_api.h>


/***********************************************
*  API functions
***********************************************/

/**
 * 
 *  This API is not supported in the current release.
 *  
 *  This function set the lower and upper thresholds of an sdk resource.
 *
 * @param[in] cmd              -ADD/DELETE.
 * @param[in] resource        - resource type.
 * @param[in] threshold_full    - Upper threshold value given in percentage.
 * @param[in] threshold_empty       - Lower threshold value given in percentage.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if the command is not supported/ threshold are invalid
 */

sx_status_t sx_api_rm_sdk_table_thresholds_set(const sx_api_handle_t             handle,
                                               const sx_access_cmd_t             access_cmd,
                                               const rm_sdk_table_type_e         resource,
                                               const sx_notification_threshold_t threshold_full,
                                               const sx_notification_threshold_t threshold_empty);

/**
 * 
 * This API is not supported in the current release.
 *  
 *  This function get the lower and upper thresholds of an sdk resource.
 *
 * @param[in] resource        - resource type.
 * @param[out] threshold_full    - Upper threshold value given in percentage.
 * @param[out] threshold_empty       - Lower threshold value given in percentage.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if the command is not supported/ threshold are invalid
 */

sx_status_t sx_api_rm_sdk_table_thresholds_get(const sx_api_handle_t        handle,
                                               const rm_sdk_table_type_e    resource,
                                               sx_notification_threshold_t *threshold_full,
                                               sx_notification_threshold_t *threshold_empty);

/**
 *
 * This API is not supported in the current release.
 *
 *  This function set the lower and upper thresholds of an hw resource.
 *
 * @param[in] cmd              -ADD/DELETE.
 * @param[in] resource        - resource type.
 * @param[in] threshold_full    - Upper threshold value given in percentage.
 * @param[in] threshold_empty       - Lower threshold value given in percentage.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if the command is not supported/ threshold are invalid
 */


sx_status_t sx_api_rm_hw_table_thresholds_set(const sx_api_handle_t             handle,
                                              const sx_access_cmd_t             access_cmd,
                                              const rm_hw_table_type_e          resource,
                                              const sx_notification_threshold_t threshold_full,
                                              const sx_notification_threshold_t threshold_empty);

/**
 * 
 *  This API is not supported in the current release.
 *  
 *  This function get the lower and upper thresholds of an hw resource.
 *
 * @param[in] resource        - resource type.
 * @param[out] threshold_full    - Upper threshold value given in percentage.
 * @param[out] threshold_empty       - Lower threshold value given in percentage.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if the command is not supported/ threshold are invalid
 */

sx_status_t sx_api_rm_hw_table_thresholds_get(const sx_api_handle_t        handle,
                                              const rm_hw_table_type_e     resource,
                                              sx_notification_threshold_t *threshold_full,
                                              sx_notification_threshold_t *threshold_empty);

#endif /* __SX_API_RM_H__ */
