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

/*
 * [[ WARNING | AUTOMATICALLY GENERATED FILE ]]
 * ------------------------------------------------------------------------
 * This file has been generated by the script:
 *     applibs/sx_api_utils/generator/sx_header_gen.py.
 *
 * You can manually modify this file ONLY for your testing needs.
 * In all other cases manual changes in this file must be removed
 * before committing. To modify content of this file in legal way
 * use applibs/include/adb/sx_bulk_counter.adb file.
 * ------------------------------------------------------------------------
 */

#ifndef __SX_BULK_COUNTER_AUTO_H__
#define __SX_BULK_COUNTER_AUTO_H__

#include "sx/sxd/kernel_user.h"
#include "resource_manager/resource_manager.h"
#include "sx/sdk/sx_port.h"

/* Enum specific MACRO */
#define SX_GENERATE_ENUM(ENUM, STR)   ENUM,
#define SX_GENERATE_STRING(ENUM, STR) STR,


/**
 * Types of port counters groups
 */
#define FOREACH_BULK_CNTR_PORT_GRP(F)                                                                        \
    F(SX_BULK_CNTR_PORT_GRP_IEEE_802_DOT_3_E = 1,             "") /**< IEEE 802.3 counters */                \
    F(SX_BULK_CNTR_PORT_GRP_RFC_2863_E = 2,                   "") /**< RFC 2863 counters */                  \
    F(SX_BULK_CNTR_PORT_GRP_RFC_2819_E = 4,                   "") /**< RFC 2819 counters */                  \
    F(SX_BULK_CNTR_PORT_GRP_RFC_3635_E = 8,                   "") /**< RFC 3635 counters */                  \
    F(SX_BULK_CNTR_PORT_GRP_PRIO_E = 16,                      "") /**< Priority counters */                  \
    F(SX_BULK_CNTR_PORT_GRP_TC_E = 32,                        "") /**< Per TC counters */                    \
    F(SX_BULK_CNTR_PORT_GRP_BUFF_E = 64,                      "") /**< Buffer counters */                    \
    F(SX_BULK_CNTR_PORT_GRP_PERF_E = 128,                     "") /**< Performance counters */               \
    F(SX_BULK_CNTR_PORT_GRP_DISCARD_E = 256,                  "") /**< Discard counters */                   \
    F(SX_BULK_CNTR_PORT_GRP_PHY_LAYER_E = 512,                "") /**< Physical layer counters */            \
    F(SX_BULK_CNTR_PORT_GRP_PHY_LAYER_STATS_E = 1024,         "") /**< Physical layer statistics counters */ \
    F(SX_BULK_CNTR_PORT_GRP_PHY_LAYER_INTERNAL_LINK_E = 2048, "") /**< Physical layer internal link counters */

typedef enum {
    FOREACH_BULK_CNTR_PORT_GRP(SX_GENERATE_ENUM)
} sx_bulk_cntr_port_grp_e;

/**
 * Bulk counter types
 */
#define FOREACH_BULK_CNTR_KEY_TYPE(F)                                                         \
    F(SX_BULK_CNTR_KEY_TYPE_PORT_E = SXD_BULK_CNTR_KEY_TYPE_PORT_E, "") /**< Port counters */ \
    F(SX_BULK_CNTR_KEY_TYPE_FLOW_E = SXD_BULK_CNTR_KEY_TYPE_FLOW_E, "") /**< Flow counters */

typedef enum {
    FOREACH_BULK_CNTR_KEY_TYPE(SX_GENERATE_ENUM)
} sx_bulk_cntr_key_type_e;


/**
 * Port counters groups bitmap
 */
typedef uint32_t sx_bulk_cntr_port_grp_bitmap_t;

typedef struct sx_bulk_cntr_buffer_key_port {
    sx_bulk_cntr_port_grp_bitmap_t grp_bitmap;                                                  /**< Counter-set bitmap of desired counters, must set at least one */
    sx_port_log_id_t               port_list[MAX_PHYPORT_NUM + MAX_LAG_NUM];                    /**< List of desired ports, must set at least one */
    uint32_t                       port_list_cnt;                                               /**< Number of ports in port_list */
    sx_port_prio_id_t              prio_id_list[SX_PORT_PRIO_ID_MAX - SX_PORT_PRIO_ID_MIN + 1]; /**< List of priority IDs - In use only if grp_bitmap has the SX_BULK_CNTR_PORT_GRP_PRIO_E flag */
    uint32_t                       prio_id_list_cnt;                                            /**< Number of priority IDs in the prio_id_list */
    sx_port_tc_id_t                tc_id_list[SX_PORT_TC_ID_MAX - SX_PORT_TC_ID_MIN + 1];       /**< List of TC IDs - In use only if grp_bitmap has the contains SX_BULK_CNTR_PORT_GRP_TC_E flag */
    uint32_t                       tc_id_list_cnt;                                              /**< Number of TC IDs in tc_id_list */
    sx_cos_priority_group_t        prio_group_list[RM_API_COS_BUFFERS_NUM];                     /**< List of priority groups - In use only if grp_bitmap contains SX_BULK_CNTR_PORT_GRP_BUFF_E flag */
    uint32_t                       prio_group_list_cnt;                                         /**< Number of priority groups in prio_group_list */
} sx_bulk_cntr_buffer_key_port_t;

typedef struct sx_bulk_cntr_buffer_key_flow {
    sx_flow_counter_id_t base_counter_id; /**< Base counter ID in the range */
    uint32_t             num_of_counters; /**< Number of counters in the range */
} sx_bulk_cntr_buffer_key_flow_t;

typedef union sx_bulk_cntr_buffer_key_u {
    sx_bulk_cntr_buffer_key_port_t port_key; /**< Port counters key */
    sx_bulk_cntr_buffer_key_flow_t flow_key; /**< Flow counters key */
} sx_bulk_cntr_buffer_key_u_t;

typedef struct sx_bulk_cntr_buffer_key {
    sx_bulk_cntr_key_type_e     type; /**< Type of counters to get */
    sx_bulk_cntr_buffer_key_u_t key;
} sx_bulk_cntr_buffer_key_t;

typedef sxd_bulk_cntr_buffer_layout_common_t sx_bulk_cntr_buffer_layout_common_t;
typedef sxd_bulk_cntr_buffer_layout_flow_t sx_bulk_cntr_buffer_layout_flow_t;

typedef struct sx_bulk_cntr_buffer {
    sx_bulk_cntr_buffer_key_t key;         /**< Bulk key which is bound to the buffer */
    unsigned long             buffer_id;   /**< Bulk-Counters buffer ID */
    uint32_t                  buffer_size; /**< Bulk-Counters buffer size */
} sx_bulk_cntr_buffer_t;

typedef struct sx_api_bulk_counter_transaction_set_params {
    sx_access_cmd_t           cmd;
    unsigned long             buffer_id;
    sx_bulk_cntr_buffer_key_t key;
} sx_api_bulk_counter_transaction_set_params_t;

#endif /* __SX_BULK_COUNTER_AUTO_H__ */
