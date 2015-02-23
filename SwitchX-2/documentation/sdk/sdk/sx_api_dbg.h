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

#ifndef __SX_API_DBG_H__
#define __SX_API_DBG_H__

#include <sx/sdk/sx_api.h>


/************************************************
 *  API functions
 ***********************************************/

/**
 * This API generates debug dump of all SDK modules, SX-core and driver.
 *
 * @param[in] handle              - SX-API handle
 * @param[in] dump_file_path      - full path file name
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if the path string length is greater than 256
 * @return SX_STATUS_ERROR general error
 */
sx_status_t sx_api_dbg_generate_dump(const sx_api_handle_t handle,
                                     const char           *dump_file_path);


#endif /* __SX_API_DBG_H__ */
