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

#ifndef __SX_API_POLICER_H__
#define __SX_API_POLICER_H__

#include <sx/sdk/sx_api.h>


/************************************************
 *  API functions
 ***********************************************/

/**
 * This function sets the log verbosity level of POLICER MODULE
 * @param[in] handle                   - SX-API handle
 * @param[in] verbosity_target         - set verbosity of : API / MODULE / BOTH
 * @param[in] module_verbosity_level   - POLICER module verbosity level
 * @param[in] api_verbosity_level      - POLICER API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 *         SX_STATUS_PARAM_ERROR if any input parameters is invalid
 *         SX_STATUS_ERROR general error
 */
sx_status_t sx_api_policer_log_verbosity_level_set(const sx_api_handle_t           handle,
                                                   const sx_log_verbosity_target_t verbosity_target,
                                                   const sx_verbosity_level_t      module_verbosity_level,
                                                   const sx_verbosity_level_t      api_verbosity_level);

/**
 * This function gets the log verbosity level of POLICER MODULE
 *
 * @param[in]  handle                   - SX-API handle
 * @param[in]  verbosity_target         - get verbosity of : API / MODULE / BOTH
 * @param[out] module_verbosity_level_p - POLICER module verbosity level
 * @param[out] api_verbosity_level_p    - POLICER API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 *         SX_STATUS_PARAM_ERROR if any input parameters is invalid
 *         SX_STATUS_ERROR general error
 */
sx_status_t sx_api_policer_log_verbosity_level_get(const sx_api_handle_t           handle,
                                                   const sx_log_verbosity_target_t verbosity_target,
                                                   sx_verbosity_level_t           *module_verbosity_level_p,
                                                   sx_verbosity_level_t           *api_verbosity_level_p);

/**
 * This function creates/destroy/edit a policer in the system.
 *
 * @param[in] handle - SX-API handle
 * @param[in] cmd - SX_ACCESS_CMD_CREATE: create a new policer and returns a policer ID in policer_id_p
 *                  SX_ACCESS_CMD_DESTROY: destroy an existing policer (according to policer_id_p)
 *                  SX_ACCESS_CMD_EDIT: edit configuration parameters of an existing policer
 * @param[in] policer_attr_p - policer attributes. Ignored when cmd is DESTROY.
 * @param[in,out] policer_id_p - policer ID
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if pid_p or policer_attrib_p pointers are NULL
 * @return SX_STATUS_INVALID_HANDLE if vpi_handle is invalid
 * @return SX_STATUS_CMD_UNSUPPORTED if cmd is SX_ACCESS_CMD_DESTROY or any other unsupported command
 * @return SX_STATUS_PARAM_ERROR if any of the input parameters is invalid
 * @return SX_STATUS_COMM_ERROR if an error occured on send or receive message to driver
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_policer_set(const sx_api_handle_t          handle,
                               const sx_access_cmd_t          cmd,
                               const sx_policer_attributes_t *policer_attr_p,
                               sx_policer_id_t               *policer_id_p);

/**
 * This function gets a policer attributes.
 *
 * @param[in] handle - SX-API handle
 * @param[in] policer_id - policer ID
 * @param[out] policer_attr_p - pointer to policer attributes
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if policer_attrib_p is NULL
 * @return SX_STATUS_INVALID_HANDLE if vpi_handle is invalid
 * @return SX_STATUS_PARAM_ERROR if any other input error
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_policer_get(const sx_api_handle_t    handle,
                               const sx_policer_id_t    policer_id,
                               sx_policer_attributes_t *policer_attr_p);

#endif /* __SX_API_POLICER_H__ */
