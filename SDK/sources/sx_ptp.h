/*
 *  Copyright (C) 2010-2020. Mellanox Technologies, Ltd. ALL RIGHTS RESERVED.
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
#ifndef __SX_PTP_H__
#define __SX_PTP_H__

/**
 * PTP operational modes
 */
typedef enum sx_ptp_mode {
    SX_PTP_MODE_POLLING, /**< Polling HW to get RX/TX timestamps */
    SX_PTP_MODE_EVENTS   /**< Getting notification upon RX/TX timestamps */
} sx_ptp_mode_t;

/**
 * PTP params
 */
typedef struct sx_ptp_params {
    sx_ptp_mode_t ptp_mode; /**< PTP operational mode */
} sx_ptp_params_t;

#endif /* __SX_PTP_H__ */
