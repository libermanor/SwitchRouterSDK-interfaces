/*
 *  Copyright (C) 2014-2019. Mellanox Technologies, Ltd. ALL RIGHTS RESERVED.
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


#ifndef SX_LIB_HOST_IFC_H_
#define SX_LIB_HOST_IFC_H_

#include <sx/sdk/sx_api.h>

/**
 * Send a unicast control packet through a specific logical port. Routing and QOS
 * from TX header.
 * Supported devices: Spectrum, Spectrum2.
 *
 * \deprecated Prio parameter is deprecated and will be removed in the future.
 *
 * @param[in] fd              - File descriptor to send from.
 * @param[in] packet_p        - Buffer containing the packet to send.
 * @param[in] packet_size     - Size of packet.
 * @param[in] swid            - Switch ID of packet destination.
 * @param[in] egress_log_port - Logical port of packet destination.
 * @param[in] prio            - Priority of the packet.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if any input parameters is null
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_MEMORY_ERROR error handling memory
 * @return SX_STATUS_NO_RESOURCES device was not opened
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is
 * not found in DB
 */
sx_status_t sx_lib_host_ifc_unicast_ctrl_send(const sx_fd_t         * fd_p,
                                              const void            * packet_p,
                                              const uint32_t          packet_size,
                                              const sx_swid_t         swid,
                                              const sx_port_log_id_t  egress_log_port,
                                              const sx_cos_priority_t prio);

/**
 *  Send a unicast and multicast data packet. Packet forwarding is done
 *  according to the HW tables.
 *  Supported devices: Spectrum, Spectrum2.
 *
 * \deprecated Prio parameter is deprecated and will be removed in the future.
 *
 * @param[in] fd            - File descriptor to send from.
 * @param[in] packet        - buffer containing the packet to send.
 * @param[in] packet_size   - Size of packet.
 * @param[in] swid          - Switch ID of packet destination.
 * @param[in] prio          - priority of the packet.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if any input parameters is null
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_MEMORY_ERROR error handling memory
 * @return SX_STATUS_NO_RESOURCES device was not opened
 */
sx_status_t sx_lib_host_ifc_data_send(const sx_fd_t          *fd,
                                      const void             *packet,
                                      const uint32_t          packet_size,
                                      const sx_swid_t         swid,
                                      const sx_cos_priority_t prio);

/**
 *  Send a packet to a loopback interface. the packet will be treated as if it was
 *  received from the HW, and dispatched to the relevant application except for the
 *  application who sent it.
 *  Supported devices: Spectrum, Spectrum2.
 *
 * @param[in] fd                - File descriptor to send from.
 * @param[in] packet            - Buffer containing the packet to send.
 * @param[in] packet_size       - Size of packet.
 * @param[in] swid              - Switch ID of the packet.
 * @param[in] trap_id           - Trap ID of the packet.
 * @param[in] ingress_log_port  - Source logical port.
 * @param[in] is_lag            - Is the source logical port member of a lag.
 * @param[in] ingress_lag_port  - Source lag port when applicable.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if any input parameters is null
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_MEMORY_ERROR error handling memory
 * @return SX_STATUS_NO_RESOURCES device was not opened
 * @return SX_STATUS_ENTRY_NOT_FOUND if requested element is
 * not found in DB
 */
sx_status_t sx_lib_host_ifc_loopback_ctrl_send(const sx_fd_t         *fd,
                                               const void            *packet,
                                               const uint32_t         packet_size,
                                               const sx_swid_t        swid,
                                               const sx_trap_id_t     trap_id,
                                               const sx_port_log_id_t ingress_log_port,
                                               const boolean_t        is_lag,
                                               const sx_port_log_id_t ingress_lag_port);

/**
 * This API enables the user to receive Traps or Events.
 * Trap RX : relevant returned information is packet_p and packet_size_p.
 * Event RX : relevant returned information is event info.
 *       Receive info struct is relevant for both traps & events and
 *       it contains the logical port in a case the event is port related
 *       event , and the ingress port in case of a trap.
 *       Read operation is blocking.
 * Supported devices: Spectrum, Spectrum2.
 *
 * @param[in]     fd              - File descriptor to listen on.
 * @param[out]    packet          - copy received packet to this buffer.
 * @param[in,out] packet_size     - [in]: The size of packet.
 *                                  [out]: Size of received packet (in bytes).
 * @param[out]    receive_info    - Information regarding the source of the packet
 *                                  (RX logical port) and about the event for events
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if any input parameters is null
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_MEMORY_ERROR error handling memory
 * @return SX_STATUS_NO_RESOURCES device was not opened
 * @return SX_STATUS_NO_MEMORY insufficient packet size, needed size filled in
 * packet_size
 */
sx_status_t sx_lib_host_ifc_recv(const sx_fd_t     *fd,
                                 void              *packet,
                                 uint32_t          *packet_size,
                                 sx_receive_info_t *receive_info);

/**
 * This API enables the user to receive Traps or Events list.
 * Trap RX :
 *       relevant returned information is packet_p and packet_size_p
 *       fields of packet_info_list_p.
 * Event RX :
 *       relevant returned information is event info.
 *
 * Receive info struct is relevant for both traps & events and
 *       it contains the logical port in a case the event is port related
 *       event , and the ingress port in case of a trap.
 *       Read operation is blocking.
 * This API internally uses a static memory buffer (around 10MB) to temporarily
 * store and parse the packets, and a lock is used internally to protect the static
 * buffer in case the API is called from multiple threads.
 * Supported devices: Spectrum, Spectrum2.
 *
 * @param[in]     fd                      - File descriptor to listen on.
 * @param[out]    packet_info_list_p      - Contain the follow fields:
 *                    packet_p            - Packet data.
 *                    packet_size         - Packet data size (minimum 64).
 *                    receive_info        - Information regarding the
 *                                          source of the packet (RX logical port)
 *                                          and about the event for events.
 * @param[in,out] packet_info_list_size_p - [in]: Length of provide packet_info_list.
 *                                          [out]: Actual number of packets.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if any input parameters is null
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_MEMORY_ERROR error handling memory
 * @return SX_STATUS_NO_RESOURCES device was not opened
 * @return SX_STATUS_NO_MEMORY insufficient packet size, needed size filled in
 * packet_size
 */
sx_status_t sx_lib_host_ifc_recv_list(const sx_fd_t    *fd,
                                      sx_packet_info_t *packet_info_list_p,
                                      uint32_t         *packet_info_list_size_p);


#endif /* SX_LIB_HOST_IFC_H_ */
