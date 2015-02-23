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


#ifndef __SX_API_ROUTER_H__
#define __SX_API_ROUTER_H__

#include <sx/sdk/sx_api.h>

/************************************************
 *  API functions
 ***********************************************/

/**
 * This API sets the log verbosity level of ROUTER MODULE.
 *
 * @param[in] handle                   - SX-API handle
 * @param[in] verbosity_target         - set verbosity of : API / MODULE / BOTH
 * @param[in] module_verbosity_level   - ROUTER module verbosity level
 * @param[in] api_verbosity_level      - ROUTER API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_router_log_verbosity_level_set(const sx_api_handle_t           handle,
                                                  const sx_log_verbosity_target_t verbosity_target,
                                                  const sx_verbosity_level_t      module_verbosity_level,
                                                  const sx_verbosity_level_t      api_verbosity_level);

/**
 * This API gets the log verbosity level of ROUTER MODULE.
 *
 * @param[in]  handle                   - SX-API handle
 * @param[in]  verbosity_target         - get verbosity of : API / MODULE / BOTH
 * @param[out] module_verbosity_level_p - ROUTER module verbosity level
 * @param[out] api_verbosity_level_p    - ROUTER API verbosity level
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully
 * @return SX_STATUS_PARAM_ERROR if an input parameter is invalid
 * @return SX_STATUS_ERROR for a general error
 */
sx_status_t sx_api_router_log_verbosity_level_get(const sx_api_handle_t           handle,
                                                  const sx_log_verbosity_target_t verbosity_target,
                                                  sx_verbosity_level_t           *module_verbosity_level_p,
                                                  sx_verbosity_level_t           *api_verbosity_level_p);

/**
 *  This function sets the ECMP hash function configuration parameters.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] ecmp_hash_param_p - ECMP hash configuration parameters.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_NULL if parameter is NULL.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_router_ecmp_hash_params_set(const sx_api_handle_t               handle,
                                               const sx_router_ecmp_hash_params_t *ecmp_hash_params_p);

/**
 *  This function gets the ECMP hash function configuration parameters.
 *
 * @param[in] handle - SX-API handle.
 * @param[out] ecmp_hash_params_p - ECMP hash configuration parameters.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_NULL if parameter is NULL.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_router_ecmp_hash_params_get(const sx_api_handle_t         handle,
                                               sx_router_ecmp_hash_params_t *ecmp_hash_params_p);

/**
 * This function Initiates the router module in SDK.
 * uc_params->ipv4_num requires a value larger than 30.
 * mc_params->mc_routes->ipv4_num requires a value larger than
 * 30. (If mc_router is enabled).
 *
 * @param[in] handle - SX-API handle.
 * @param[in] general_params_p - general router parameters.
 * @param[in] router_resource_p- router resource parameter.
 *
 * @return SX_STATUS_SUCCESS - if operation completes
 *         successfully.
 * @return SX_STATUS_ALREADY_INITIALIZED - When router is
 *         already initialized.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE - When calling with bad
 *         parameters.
 */
sx_status_t sx_api_router_init_set(const sx_api_handle_t              handle,
                                   const sx_router_general_param_t   *general_params_p,
                                   const sx_router_resources_param_t *router_resource_p);


/**
 *
 * This api deinit's the router block in the sdk.
 *
 * @param[in] handle - SX-API handle.
 *
 * @return SX_STATUS_SUCCESS if operation completes
 *         successfully.
 * @return SX_STATUS_RESOURCE_IN_USE When router is still
 *         active.
 */
sx_status_t sx_api_router_deinit_set(const sx_api_handle_t handle);

/**
 *  This function adds/deletes a virtual router.
 *  The router ID is allocated and returned to the caller when
 *  cmd is ADD, otherwise it is given by the caller. All
 *  interfaces and routes associated with a router must be
 *  deleted before the router can be deleted as well.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - ADD/DELETE.
 * @param[in] router_attr - Router attributes.
 * @param[in,out] vrid - Virtual router ID
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_NULL if parameter is NULL.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND if router was not added.
 * @return SX_STATUS_NO_RESOURCES if there are no resources to
 *         create another router
 * @return SX_STATUS_RESOURCE_IN_USE if router has interfaces or routes.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_router_set(const sx_api_handle_t         handle,
                              const sx_access_cmd_t         cmd,
                              const sx_router_attributes_t *router_attr,
                              sx_router_id_t               *vrid);

/**
 *  This function gets a virtual router information.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] vrid - Virtual Router ID.
 * @param[out] router_attr - Router attributes.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_NULL if parameter is NULL.
 * @return SX_STATUS_ENTRY_NOT_FOUND if router was not added.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_router_get(const sx_api_handle_t   handle,
                              const sx_router_id_t    vrid,
                              sx_router_attributes_t *router_attr);

/**
 *  This function adds/modifies/deletes/delete_all a router
 *  interface. A router interface is associated with L2
 *  interface.
 *
 *  When in 802.1D mode, if ifc_p of type SX_L2_INTERFACE_TYPE_VLAN is provided,
 *  instead of providing ifc.vlan.vlan you should provide a bridge_id.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - ADD/EDIT/DELETE/DELETE ALL.
 * @param[in] vrid - Virtual Router ID.
 * @param[in] ifc_p -  Interface type and parameters .
 * @param[in] ifc_attr_p -Interface attributes.
 * @param[in,out] rif - Router Interface ID.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_NULL if parameter is NULL.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND if router interface was not added.
 * @return SX_STATUS_NO_RESOURCES if no interface is available to create.
 * @return SX_STATUS_RESOURCE_IN_USE if router interface has routes.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_router_interface_set(const sx_api_handle_t              handle,
                                        const sx_access_cmd_t              cmd,
                                        const sx_router_id_t               vrid,
                                        const sx_router_interface_param_t *ifc_p,
                                        const sx_interface_attributes_t   *ifc_attr_p,
                                        sx_router_interface_t             *rif_p);

/**
 *  This function gets a router interface information.
 *
 *  When in 802.1D mode, if ifc_p of type SX_L2_INTERFACE_TYPE_VLAN is returned,
 *  instead of receiving a vlan ID on ifc.vlan.vlan, a bridge ID is provided.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] rif - Router Interface ID.
 * @param[out] vrid_p - Virtual Router ID.
 * @param[out] ifc_p -  Interface type and parameters .
 * @param[out] ifc_attr_p -Interface attributes.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND if router interface was not added.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_router_interface_get(const sx_api_handle_t        handle,
                                        const sx_router_interface_t  rif,
                                        sx_router_id_t              *vrid_p,
                                        sx_router_interface_param_t *ifc_p,
                                        sx_interface_attributes_t   *ifc_attr_p);

/**
 *  This function sets admin state of a router interface. Admin state is set per
 *  IP protocol.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] rif - Router Interface ID.
 * @param[in] rif_state_p - Admin state for unicast  routing and
 *                                                      multicast routing .
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND if router interface was not added.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_router_interface_state_set(const sx_api_handle_t              handle,
                                              const sx_router_interface_t        rif,
                                              const sx_router_interface_state_t *rif_state_p);

/**
 *  This function gets admin state of a router interface.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] rif - Router Interface ID.
 * @param[in] rif_state_p - Admin state for unicast  routing and
 *                                                      multicast routing .
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_NULL if parameter is NULL.
 * @return SX_STATUS_ENTRY_NOT_FOUND if router interface was not added.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_router_interface_state_get(const sx_api_handle_t        handle,
                                              const sx_router_interface_t  rif,
                                              sx_router_interface_state_t *rif_state_p);

/**
 *  This function adds/deletes a MAC address from a router interface.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - ADD/DELETE/DELETE_ALL.
 * @param[in] rif - Router Interface ID.
 * @param[in] mac_addr_list_p - MAC addresses array.
 * @param[in]  mac_addr_cnt - MAC addresses array size.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_ENTRY_NOT_FOUND if router interface was not added.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_router_interface_mac_set(const sx_api_handle_t       handle,
                                            const sx_access_cmd_t       cmd,
                                            const sx_router_interface_t rif,
                                            const sx_mac_addr_t        *mac_addr_list_p,
                                            const uint32_t              mac_addr_cnt);

/**
 *  This function gets MAC address of a router interface.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] rif - Router Interface ID.
 * @param[in] mac_addr_list_p - MAC addresses array.
 * @param[in,out] mac_addr_cnt_p - MAC addresses array size.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_NULL if parameter is NULL.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND if router interface was not added.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_router_interface_mac_get(const sx_api_handle_t       handle,
                                            const sx_router_interface_t rif,
                                            sx_mac_addr_t              *mac_addr_list_p,
                                            uint32_t                  * mac_addr_cnt_p);

/**
 *  This function adds/deletes/delete_all a neighbour
 *  information. The neighbour information associate an IP
 *  address to a MAC address. The neighbour IP addresses are
 *  learned via ARP/ND discovery at the control protocols layer,
 *  the interface that the neighbours are associated with is
 *  derived from the IP interface configuration. When calling
 *  with DELETE command, neigh_data_p->rif parameter is ignored.
 *  When cmd = DELETE_ALL, all neighbors which match the
 *  ip_addr.version and the neigh_data_p->rif, will be deleted. In case rif is
 *  SX_ROUTER_INTERFACE_DONTCARE, all neighbors corresponding
 *  with the ip_addr.version will be deleted.
 *  If ip_addr.version = SX_IP_VERSION_NONE then only IPv4
 *  neighbors will be deleted.
 *
 *  In case action is not SX_ROUTER_ACTION_FORWARD/SX_ROUTER_ACTION_DROP
 *  Trap ID will be set to SX_TRAP_ID_L3_NEIGH_IP_BASE + trap priority.
 *
 *
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - ADD/DELETE/DELETE_ALL.
 * @param[in] vrid - Virtual Router ID.
 * @param[in] ip_addr - IP address.
 * @param[in] neigh_data_p - Neighbours information.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND if neighbour was not added.
 * @return SX_STATUS_NO_RESOURCES if no neighbour entry is available to create.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_router_neigh_set(const sx_api_handle_t  handle,
                                    const sx_access_cmd_t  cmd,
                                    const sx_router_id_t   vrid,
                                    const sx_ip_addr_t    *ip_addr_p,
                                    const sx_neigh_data_t *neigh_data_p);

/**
 *  This function gets the neighbors whose ip version (IPv4/6)
 *  match's the neigh_key_p.ip_addr.version. If neigh_key_p.ip_addr.version ==
 *  SX_IP_VERSION_NONE then only IPv4 neighbors will be
 *  returned. MAC address and Router Interface ID will be
 *  returned in case the neighbor exists.
 *
 * The function can receive three types of input:
 *
 *   - 1) get information for current ip address  - you
 *      should insert the ip address in the key variable.
 *      neigh_entry_cnt_p should be equal to 1. cmd should be
 *      SX_ACCESS_CMD_GET.
 *
 *   - 2) get a list of first n<=64 neighs - you should
 *      insert ip address data in the key variable.
 *      neigh_entry_cnt_p should be equal to n.  filter_p is the
 *      filter type(s) you want to filter the results by. cmd
 *      should be SX_ACCESS_CMD_GET_FIRST.
 *
 *   - 3) get a list of n<=64 MACs which comes after certain
 *      neight record (it does not have to exist) you should
 *      insert neight ip address in the key variable.
 *      neigh_entry_cnt_p should be equal to n s ,
 *      filter_p is the filter type(s) you want to filter the
 *      results by. cmd should be SX_ACCESS_CMD_GETNEXT.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - GET/GET_FIRST/ GET_NEXT.
 * @param[in] vrid - Virtual Router ID.
 * @param[in] neigh_key_p - neigh key.
 * @param[in] filter_p - neigh key_filter.
 * @param[out] neigh_entry_list_p  - found neigh entries arr
 * @param[in,out] neigh_entry_cnt_p - found neigh entries num
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND if neighbour was not added.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_router_neigh_get(const sx_api_handle_t     handle,
                                    const sx_access_cmd_t     cmd,
                                    const sx_router_id_t      vrid,
                                    const sx_ip_addr_t      * neigh_key_p,
                                    const sx_neigh_filter_t * filter_p,
                                    sx_neigh_get_entry_t     *neigh_entry_list_p,
                                    uint32_t                * neigh_entry_cnt_p);

/**
 *  This function gets and clean  neighbor activity
 *  information.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - READ / READ_CLEAR
 * @param[in] vrid - Virtual Router ID.
 * @param[in] ip_addr_p - neigh IP address.
 * @param[out] activity_p - activity .
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND if neighbor was not added.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_router_neigh_activity_get(const sx_api_handle_t handle,
                                             const sx_access_cmd_t cmd,
                                             const sx_router_id_t  vrid,
                                             const sx_ip_addr_t  * ip_addr_p,
                                             boolean_t            *activity_p);

/**
 *  This function adds/deletes an unicast route into the routing table.
 *  The route is composed of network address and next hop array which may
 *  contains more than one entry for ECMP. In case the ARP entry is not known
 *  yet, a route can be added with action other than FORWARD. Upon ARP entry
 *  resolved and configured, the route can be modified into FORWARD.
 *  In case ARP is unresolved trap priority is set to SX_TRAP_PRIORITY_LOW.
 *  Calling with SET cmd will replace all next hop entries
 *  associated with the route. (If the route does not exist, it
 *  will be created).
 *  When cmd = DELETE_ALL all routes matching vrid, and
 *  network_addr will be deleted.
 *
 *  Command SOFT_ADD is different from ADD.
 *  SOFT_ADD cmd - the function will return in the
 *  uc_route_data_p->next_hop list the actual ECMP that as been
 *  configured to HW please note that the actual ECMP may be
 *  different from the requested ECMP due to lack of HW resources.
 *
 *  In case action is not SX_ROUTER_ACTION_FORWARD/SX_ROUTER_ACTION_DROP,
 *  Trap ID will be set to SX_TRAP_ID_L3_UC_IP_BASE + trap priority.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - ADD/SET/SOFT_ADD/DELETE/DELETE_ALL
 * @param[in] vrid - Virtual Router ID.
 * @param[in] network_addr_p - IP network address.
 * @param[in,out] uc_route_data_p - route data {Next hop list,action}
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_NO_RESOURCES if no routes is available to create.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_router_uc_route_set(const sx_api_handle_t handle,
                                       const sx_access_cmd_t cmd,
                                       const sx_router_id_t  vrid,
                                       const sx_ip_prefix_t *network_addr,
                                       sx_uc_route_data_t   *uc_route_data_p);

/**
 *  This function gets a unicast route information from the routing table.
 *  The function can receive four types of input:
 *
 *   - 1) get information for current ip address  - you
 *      should insert the ip prefix  the key variable.
 *      uc_route_get_entries_cnt_p  should be equal to 1.
 *      cmd should be SX_ACCESS_CMD_GET.
 *
 *   - 2) count the number of IPv4/6 UC routes configured,
 *      according to the network_addr->version parameter.
 *      uc_route_get_entries_cnt_p  should be equal to 0.
 *      cmd should be SX_ACCESS_CMD_GET.
 *
 *   - 3) get a list of first n<=64 routes - you should
 *      insert ip prefix  data in the key variable.
 *      uc_route_get_entries_cnt_p should be equal to n.
 *      filter_p is the filter type(s) you want to filter the
 *      results by. cmd should be SX_ACCESS_CMD_GET_FIRST.
 *
 *   - 4) get a list of n<=64 routes  which comes after certain
 *      ip prefix  (it does not have to exist) you should insert
 *      ip prefix  address in the  address network_addr_p
 *      variable.
 *      uc_route_get_entries_cnt_p should be equal to n s ,
 *      filter_p is the filter type(s) you want to filter the
 *      results by. cmd should be SX_ACCESS_CMD_GETNEXT.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - GET /GET_FIRST/ GET_NEXT.
 * @param[in] vrid - Virtual Router ID.
 * @param[in] network_addr - IP network address
 * @param[in] filter_p - UC route key_filter.
 * @param[out]uc_route_get_entries_list_p- found uc route entries arr .
 * @param[out]uc_route_get_entries_cnt_p- found uc route entries num .
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND if UC route was not added.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_router_uc_route_get(const sx_api_handle_t     handle,
                                       const sx_access_cmd_t     cmd,
                                       const sx_router_id_t      vrid,
                                       const sx_ip_prefix_t     *network_addr,
                                       sx_uc_route_key_filter_t *filter_p,
                                       sx_uc_route_get_entry_t  *uc_route_get_entries_list_p,
                                       uint32_t                 *uc_route_get_entries_cnt_p);

/**
 *  This function retrieves active unicast ECMP route information from the routing table.
 *  When using oper_uc_route_entries_p->route_data.next_hop_cnt=0 only the number of next hops will be returned.
 * @param[in] handle - SX-API handle.
 * @param[in] vrid - Virtual Router ID.
 * @param[in] network_addr - IP network address.
 * @param[out] oper_uc_route_entries_p - found uc route entry.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND if ECMP UC route was not found.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_router_uc_route_operational_ecmp_get(const sx_api_handle_t    handle,
                                                        const sx_router_id_t     vrid,
                                                        const sx_ip_prefix_t    *network_addr_p,
                                                        sx_uc_route_get_entry_t *oper_uc_route_entries_p);

/**
 *  This function creates/destroys a router counter. A router counter
 *  should be bound later to a router interface.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - CREATE/DESTROY.
 * @param[in,out] counter_p - Router counter ID.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported.
 * @return SX_STATUS_PARAM_NULL if parameter is NULL.
 * @return SX_STATUS_NO_RESOURCES if no counter is available to create.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_router_counter_set(const sx_api_handle_t   handle,
                                      const sx_access_cmd_t   cmd,
                                      sx_router_counter_id_t *counter_p);

/**
 *  This function binds/unbinds a router counter to a router interface.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - BIND/UNBIND.
 * @param[in] counter - Router counter ID.
 * @param[in] rif - Router Interface ID.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND if counter was not added.
 * @return SX_STATUS_RESOURCE_IN_USE if interface is already bound.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_router_interface_counter_bind_set(const sx_api_handle_t        handle,
                                                     const sx_access_cmd_t        cmd,
                                                     const sx_router_counter_id_t counter,
                                                     const sx_router_interface_t  rif);

/**
 *  This function gets a router counter bind of a router interface.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] counter - Router counter ID.
 * @param[out] rif_p - Router Interface ID.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_ENTRY_NOT_FOUND if counter was not added.
 * @return SX_STATUS_ENTRY_NOT_BOUND if counter was not bound.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_router_interface_counter_bind_get(const sx_api_handle_t        handle,
                                                     const sx_router_counter_id_t counter,
                                                     sx_router_interface_t       *rif_p);

/**
 *  This function gets a router counter.
 *  When using cmd=READ_CLEAR, the counters will be returned and cleared.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - READ/READ_CLEAR
 * @param[in] counter - Router counter ID.
 * @param[out] counter_set_p - Router counter set values.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_NULL if parameter is NULL.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND if counter was not added.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_router_counter_get(const sx_api_handle_t        handle,
                                      const sx_access_cmd_t        cmd,
                                      const sx_router_counter_id_t counter,
                                      sx_router_counter_set_t     *counter_set_p);

/**
 *  This function clears router counter set of a router counter.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] counter - Router counter ID.
 * @param[in] all - Clear all Router counters.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_NULL if parameter is NULL.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_ENTRY_NOT_FOUND if counter was not added.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_router_counter_clear_set(const sx_api_handle_t        handle,
                                            const sx_router_counter_id_t counter,
                                            const boolean_t              all);

/**
 * This function adds/modifies/deletes a multicast route into the MC routing table.
 *
 * In case action is not SX_ROUTER_ACTION_FORWARD/SX_ROUTER_ACTION_DROP,
 * Trap ID will be set to SX_TRAP_ID_L3_MC_IP_BASE + trap priority.
 *
 * In case mc_router_attr_p->rpf_action is SX_ROUTER_RPF_ACTION_TRAP,
 * the caller should configure SX_TRAP_ID_ETH_L3_RPF trap first.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - ADD/MODIFY/DELETE/DELETE_ALL
 *                 DELETE_ALL command deletes all multicast routes associated
 *                 with vrid and source_addr.version.
 * @param[in] vrid - Virtual Router ID.
 * @param[in] mc_route_key_p - mc route enntry key {Source IP
 *       Address,group address, ingress rif}
 * @param[in] mc_router_attr_p -multicast route attribute
 *       (e.g. rpf mode,ttl ... )
 * @param[in] mc_route_data_p - Route data {action , egrees rif
 *       list}.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_NO_RESOURCES if no routes is available to create.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_router_mc_route_set(const sx_api_handle_t            handle,
                                       const sx_access_cmd_t            cmd,
                                       const sx_router_id_t             vrid,
                                       const sx_mc_route_key_t        * mc_route_key_p,
                                       const sx_mc_route_attributes_t * mc_router_attr_p,
                                       const sx_mc_route_data_t       * mc_route_data_p);

/**
 *  This function gets a multicast route from the MC routing table.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - GET
 *                 GET - Get multicast route entry from DB.
 * @param[in] vrid - Virtual Router ID.
 * @param[in] mc_route_key_p - mc route enntry key {Source IP
 *       Address,group address, ingress rif}
 *  @param[in] filter_p - MC route key_filter - Currently NULL.
 * @param[out]uc_route_get_entries_list_p- found mc route entries arr .
 * @param[out]uc_route_get_entries_cnt_p- found mc route entries num .
 *
 * @param[out] mc_router_attr_p -multicast route route attribute
 *       (e.g. rpf mode,ttl ... )
 * @param[out] mc_route_data_p - Route data {action , egrees rif
 *       list} .
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_NOT_FOUND if mc route is not found
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_router_mc_route_get(const sx_api_handle_t     handle,
                                       const sx_access_cmd_t     cmd,
                                       const sx_router_id_t      vrid,
                                       const sx_mc_route_key_t * mc_route_key_p,
                                       sx_mc_route_key_filter_t *filter_p,
                                       sx_mc_route_get_entry_t  *mc_route_get_entries_list_p,
                                       uint32_t                 *mc_route_get_entries_cnt_p);

/**
 *  This function reads and clears multicast route activity.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - READ\READ_CLEAR
 * @param[in] vrid - Virtual Router ID.
 * @param[in] mc_route_key_p - mc route enntry key {Source IP
 *       Address,group address, ingress rif}
 * @param[out] activity_p - Route activity.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_NOT_FOUND if mc route is not found
 * @return SX_STATUS_ERROR general error.
 */

sx_status_t sx_api_router_mc_route_activity_get(const sx_api_handle_t     handle,
                                                const sx_access_cmd_t     cmd,
                                                const sx_router_id_t      vrid,
                                                const sx_mc_route_key_t * mc_route_key_p,
                                                boolean_t                *activity_p);

/**
 *  This function adds/modifies/deletes an egress VLAN/PORT interfaces to multicast route.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] cmd - ADD/DELETE/DELETE_ALL
 *                 DELETE_ALL command deletes all egress router interfaces
 *                 associated with multicast group.
 * @param[in] vrid - Virtual Router ID.
 * @param[in] mc_route_key_p - mc route enntry key {Source IP
 *       Address,group address, ingress rif}
 * @param[in] egress_rif_list_p - Egress Router Interface array.
 * @param[in,out] egress_rif_cnt - Egress Router Interface array
 *       num.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_NO_RESOURCES if no routes is available to create.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_router_mc_egress_rif_set(const sx_api_handle_t        handle,
                                            const sx_access_cmd_t        cmd,
                                            const sx_router_id_t         vrid,
                                            const sx_mc_route_key_t     *mc_route_key_p,
                                            const sx_router_interface_t *egress_rif_list_p,
                                            const uint32_t               egress_rif_cnt);

/**
 *  This function get an egress VLAN/PORT interfaces from
 *  multicast route. When egress_rif_num is 0 , will return a
 *  counter of the number of egress rifs, and egress_rif_arr will
 *  remain empty. When egress_rif_arr = NULL, will return counter
 *  in egress_rif_num.
 *
 * @param[in] handle - SX-API handle.
 * @param[in] vrid - Virtual Router ID.
 * @param[in] mc_route_key_p - mc route enntry key {Source IP
 *       Address,group address, ingress rif }
 * @param[out] egress_rif_list_p - Egress Router Interface array.
 * @param[in,out] egress_rif_cnt_p - Egress Router Interface
 *       array num.
 *
 * @return SX_STATUS_SUCCESS if operation completes successfully.
 * @return SX_STATUS_CMD_UNSUPPORTED if access command isn't supported.
 * @return SX_STATUS_PARAM_EXCEEDS_RANGE if parameters exceed range.
 * @return SX_STATUS_PARAM_ERROR if any input parameter is invalid.
 * @return SX_STATUS_NO_RESOURCES if no routes is available to create.
 * @return SX_STATUS_ERROR general error.
 */
sx_status_t sx_api_router_mc_egress_rif_get(const sx_api_handle_t    handle,
                                            const sx_router_id_t     vrid,
                                            const sx_mc_route_key_t *mc_route_key_p,
                                            sx_router_interface_t   *egress_rif_list_p,
                                            uint32_t                *egress_rif_cnt);

#endif /* __SX_API_ROUTER_H__ */
