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


#ifndef __SX_API_MC_CONTAINER_H__
#define __SX_API_MC_CONTAINER_H__

#include <sx/sdk/sx_api.h>

/************************************************
 *  API functions
 ***********************************************/

/**
 * Sets the log verbosity level of MC_CONTAINER MODULE.
 * Supported devices: SwitchX, SwitchX2, Spectrum.
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] verbosity_target         - set verbosity of : API / MODULE / BOTH
 * @param[in] module_verbosity_level   - MC_CONTAINER module verbosity level
 * @param[in] api_verbosity_level      - MC_CONTAINER API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_mc_container_log_verbosity_level_set(const sx_api_handle_t           handle,
                                                        const sx_log_verbosity_target_t verbosity_target,
                                                        const sx_verbosity_level_t      module_verbosity_level,
                                                        const sx_verbosity_level_t      api_verbosity_level);

/**
 * Gets the log verbosity level of MC_CONTAINER MODULE.
 * Supported devices: SwitchX, SwitchX2, Spectrum.
 *
 * @param[in]  handle                   - SX-API handle
 * @param[in]  verbosity_target         - get verbosity of : API / MODULE / BOTH
 * @param[out] module_verbosity_level_p - MC_CONTAINER module verbosity level
 * @param[out] api_verbosity_level_p    - MC_CONTAINER API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_mc_container_log_verbosity_level_get(const sx_api_handle_t           handle,
                                                        const sx_log_verbosity_target_t verbosity_target,
                                                        sx_verbosity_level_t           *module_verbosity_level_p,
                                                        sx_verbosity_level_t           *api_verbosity_level_p);

/**
 * Manipulate a multicast container
 * Command CREATE creates a new container with the specified list of next_hops_cnt
 * next hops in next_hop_list_p, and returns its new container ID in container_id_p.
 * Commands ADD and DELETE add or delete the next hops specified by next_hop_list_p
 * and next_hop_cnt to/from an existing container specified by container_id_p.
 * Command SET replaces the contents of an existing container specified by
 * container_id_p, with the specified list of next hops in next_hop_list_p.
 * Command DESTROY deletes an existing container specified by container_id_p.
 * Command DELETE_ALL deletes all existing containers.
 * Notes: A container in use (e.g. by a multicast route or ACL) cannot be destroyed
 *        A container may contain at most RM_API_ROUTER_RIFS_MAX next hops
 *
 * Supported devices: Spectrum.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - CREATE/ADD/DELETE/SET/DESTROY/DELETE_ALL.
 * @param[in,out] container_id_p - Specifies or returns the container ID
 * @param[in] next_hop_list_p - Specifies the list of next hops for the container
 * @param[in] next_hop_cnt - Specifies the amount of next hops in next_hop_list_p
 * @param[in] container_attr_p - Specifies the container attributes
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND if specified container ID does not exist.
 * @return SX_STATUS_NO_RESOURCES if there are no resources for the operation.
 * @return SX_STATUS_RESOURCE_IN_USE if group is in use and cannot be destroyed.
 */
sx_status_t sx_api_mc_container_set(const sx_api_handle_t               handle,
                                    const sx_access_cmd_t               cmd,
                                    sx_mc_container_id_t               *container_id_p,
                                    const sx_mc_next_hop_t             *next_hop_list_p,
                                    const uint32_t                      next_hop_cnt,
                                    const sx_mc_container_attributes_t* container_attr_p);

/**
 * Retrieve information about a multicast container
 * Command GET retrieves information about the container specified by container_id_p.
 * Command GETFIRST retrieves the first container, its ID, next hops and attributes.
 * Command GETNEXT retrieves the next container after container_id_p, its ID, next hops and attributes.
 * Command COUNT returns the number of existing containers, in *next_hop_cnt
 * Notes: *next_hop_cnt should contain the maximum amount of next hops to retrieve.
 *        If rpf_vif_list_p is NULL, then next hops are not retrieved at all.
 *        If *next_hop_cnt is 0, or if rpf_vif_list_p is NULL, then the amount of next hops
 *        is returned in *next_hop_cnt
 *        If container_attr is NULL, then attributes are not retrieved.
 *
 * Supported devices: Spectrum.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - GET/GETFIRST/GETNEXT/COUNT
 * @param[in] container_id - Specifies a container ID or returns a container ID
 * @param[out] next_hop_list_p - Returns the list of next hops in the container
 * @param[in,out] next_hop_cnt_p - Specifies the maximum amount of next hops to retrieve,
 *                               and returns the amount of next hops retrieved
 * @param[out] container_attr_p - Returns the container attributes
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND if specified container does not exist, or no more containers.
 */
sx_status_t sx_api_mc_container_get(const sx_api_handle_t         handle,
                                    const sx_access_cmd_t         cmd,
                                    sx_mc_container_id_t          container_id,
                                    sx_mc_next_hop_t             *next_hop_list_p,
                                    uint32_t                     *next_hop_cnt_p,
                                    sx_mc_container_attributes_t *container_attr_p);

#endif /* __SX_API_MC_CONTAINER_H__ */
