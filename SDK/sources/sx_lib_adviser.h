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


#ifndef __SX_LIB_ADVISER_H__
#define __SX_LIB_ADVISER_H__

#include "sx/sdk/sx_types.h"


/************************************************
 *  Type definitions
 ***********************************************/
#define SX_GENERATE_ENUM(ENUM, STR) ENUM,


#define FOREACH_SX_LIB_ADVISER_EVENT_TYPE(F)                             \
    F(SX_LIB_ADVISER_EVENT_NONE_E = 0, "N/A")                            \
    F(SX_LIB_ADVISER_PORT_ADDED_E = 1, "Port Added")                     \
    F(SX_LIB_ADVISER_PORT_DELETED_E = 2, "Port Deleted")                 \
    F(SX_LIB_ADVISER_PORT_ADDED_TO_LAG = 3, "Port Added to LAG")         \
    F(SX_LIB_ADVISER_PORT_DELETED_FROM_LAG = 4, "Port Deleted from LAG") \
    F(SX_LIB_ADVISER_EVENT_TYPE_MIN_E = SX_LIB_ADVISER_PORT_ADDED_E, "") \
    F(SX_LIB_ADVISER_EVENT_TYPE_MAX_E = SX_LIB_ADVISER_PORT_DELETED_FROM_LAG, "")

typedef enum sx_lib_adviser_event_type {
    FOREACH_SX_LIB_ADVISER_EVENT_TYPE(SX_GENERATE_ENUM)
} sx_lib_adviser_event_type_e;

#define SX_LIB_ADVISER_EVENT_TYPE_NUM (SX_LIB_ADVISER_EVENT_TYPE_MAX_E + 1)

#define SX_LIB_ADVISER_EVENT_TYPE_CHECK_RANGE(TYPE) \
    (SX_CHECK_RANGE(SX_LIB_ADVISER_EVENT_TYPE_MIN_E, (TYPE), SX_LIB_ADVISER_EVENT_TYPE_MAX_E))


typedef sx_event_port_lag_changes_t sx_lib_adviser_event_lag_changes_t;
typedef sx_event_port_added_deleted_t sx_lib_adviser_event_port_added_deleted_t;

typedef union sx_lib_adviser_event_info_items {
    sx_lib_adviser_event_lag_changes_t        lag_changes;
    sx_lib_adviser_event_port_added_deleted_t port_added_deleted;
} sx_lib_adviser_event_info_items_t;

typedef struct sx_lib_adviser_event_info {
    sx_lib_adviser_event_type_e           type;
    union sx_lib_adviser_event_info_items info;
} sx_lib_adviser_event_info_t;

typedef sx_status_t (*sx_lib_adviser_cb_t)(const sx_lib_adviser_event_info_t event_info, const void *context);

typedef struct sx_lib_adviser_event_registration_params {
    sx_lib_adviser_event_type_e event_type;
    sx_lib_adviser_cb_t         callback; /**<  A callback to be called when an event was sent */
    void                       *context; /**<  User context to be sent to the callback */
    sx_port_log_id_t           *excluded_ports_p; /**< A list of ports events will not be sent on. Can be NULL  */
    uint32_t                    excluded_ports_cnt; /**<  The number of ports in the excluded list  */
} sx_lib_adviser_event_registration_params_t;

typedef struct sx_lib_adviser_init_params {
    sx_log_cb_t          logging_cb;
    sx_verbosity_level_t verbosity_level;
} sx_lib_adviser_init_params_t;


/************************************************
 *  API functions
 ***********************************************/

/**
 * Initializes and sets the verbosity level of this module.
 * This function should be called before any use of the library.
 * The function initializes a host-ifc channel, registers for the supported events,
 * and initializes a thread that will receive the events.
 *
 * @param[in] init_params – a structure that holds the init parameters
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_lib_adviser_init(const sx_lib_adviser_init_params_t init_params);

/**
 * Deinitializes this module.
 *
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_lib_adviser_deinit(void);


/**
 * Registers a callback to an event.
 * When such event occurs, the callback function provided will be triggered.
 * In case of port related events, there is an option to exclude ports,
 * by specifying the excluded ports in the provided parameters.
 * Any number of callbacks can be registered.
 *
 * @param[in] event_register_params – relevant event parameters.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_lib_adviser_event_register(const sx_lib_adviser_event_registration_params_t event_register_params);

/**
 * Deregisters a callback from an event.
 * The event type and callback must be specified in the given struct.
 * The rest of the parameters inside the struct are ignored.
 *
 * @param[in] event_register_params – holds the event parameters.
 *                          only event_type and callback should be set.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */

sx_status_t sx_lib_adviser_event_deregister(const sx_lib_adviser_event_registration_params_t event_register_params);


#endif /* __SX_LIB_ADVISER_H__ */
