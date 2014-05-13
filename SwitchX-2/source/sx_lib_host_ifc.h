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


#ifndef SX_LIB_HOST_IFC_H_
#define SX_LIB_HOST_IFC_H_

#include <sx/sdk/sx_api.h>

/**
 * Send a unicast control packet through a specific logical port.Routing and QOS
 * from TX header.
 *
 * @param[in] fd            - File descriptor to send from.
 * @param[in] packet            - buffer containing the packet to send.
 * @param[in] packet_size       - size of packet.
 * @param[in] swid          - switch id of packet destination.
 * @param[in] egress_log_port       - logical port of packet destination.
 * @param[in] prio          - priority of the packet.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if any input parameters is null
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_MEMORY_ERROR error handling memory
 * @return SX_STATUS_NO_RESOURCES device was not opened
 */
sx_status_t
sx_lib_host_ifc_unicast_ctrl_send(
                               const sx_fd_t           * fd_p,
                               const void              * packet_p,
                               const uint32_t            packet_size,
                               const sx_swid_t           swid,
                               const sx_port_log_id_t    egress_log_port,
                               const sx_cos_priority_t   prio);

/**
 *This API is not supported at the current release
 *
 *  Send a unicast and multicast data packet . Packet forwarding is done
 *  according to the HW tables
 *
 * @param[in] fd            - File descriptor to send from.
 * @param[in] packet            - buffer containing the packet to send.
 * @param[in] packet_size       - size of packet.
 * @param[in] swid              - switch id of packet destination.
 * @param[in] prio          - priority of the packet.
 *
 * @return  SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if any input parameters is null
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_MEMORY_ERROR error handling memory
 * @return SX_STATUS_NO_RESOURCES device was not opened
 */
sx_status_t
sx_lib_host_ifc_date_send(
                            const sx_fd_t         *fd,
                            const void            *packet,
                            const uint32_t        packet_size,
                            const sx_swid_t       swid,
                            const sx_cos_priority_t  prio);

/**
 *  Send a packet to a loopback interface. the packet will be treated as if it was
 *  received from the HW, and dispatched to the relevant application except for the
 *  application who sent it.
 *
 * @param[in] fd            - File descriptor to send from.
 * @param[in] packet            - buffer containing the packet to send.
 * @param[in] packet_size       - size of packet.
 * @param[in] swid              - switch id of the packet.
 * @param[in] trap_id           - trap ID of the packet.
 * @param[in] ingress_log_port      - source logical port.
 * @param[in] is_lag            - is the source logical port member of a lag.
 * @param[in] ingress_lag_port      - source lag port when applicable.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_NULL if any input parameters is null
 * @return SX_STATUS_PARAM_ERROR if any input parameters is invalid
 * @return SX_STATUS_ERROR general error
 * @return SX_STATUS_MEMORY_ERROR error handling memory
 * @return SX_STATUS_NO_RESOURCES device was not opened
 */
sx_status_t
sx_lib_host_ifc_loopback_ctrl_send(
                                    const sx_fd_t           *fd,
                                    const void              *packet,
                                    const uint32_t           packet_size,
                                    const sx_swid_t          swid,
                                    const sx_trap_id_t       trap_id,
                                    const sx_port_log_id_t   ingress_log_port,
                                    const boolean_t          is_lag,
                                    const sx_port_log_id_t   ingress_lag_port);

/**
* This API enables the user to receive Traps or Events.
* Trap RX : relevant returned information is packet_p and packet_size_p.
* Event RX : relevant returned information is event info.
*       Receive info struct is relevant for both traps & events and
*       it contains the logical port in a case the event is port related
*       event , and the ingress port in case of a trap.
*       Read operation is blocking.
*
*@param[in]     fd      - File descriptor to listen on.
*@param[out]    receive_info_p  - information regarding the
*      source of the packet (RX logical port) and about the event for events
*@param[out]    packet          - copy received packet to this buffer.
*@param[in,out] packet_size     - in : the size of packet ,out: size of
*                                      received packet. (in bytes)
*
* @return SX_STATUS_SUCCESS if operation completes successfully
* @return SX_STATUS_PARAM_NULL if any input parameters is null
* @return SX_STATUS_ERROR general error
* @return SX_STATUS_MEMORY_ERROR error handling memory
* @return SX_STATUS_NO_RESOURCES device was not opened
*/
sx_status_t
sx_lib_host_ifc_recv(
                     const sx_fd_t     *fd,
                     void              *packet,
                     uint32_t          *packet_size,
                     sx_receive_info_t *receive_info);



#endif /* SX_LIB_HOST_IFC_H_ */
