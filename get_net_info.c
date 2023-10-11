#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netlink/netlink.h>
#include <netlink/socket.h>
#include <netlink/route/link.h>
#include <netlink/route/route.h>
#include <netlink/route/nexthop.h>

// 设置网关地址
int set_gateway(char *ifname, char *gwaddr) {
    struct nl_sock *sock; // netlink socket
    struct rtnl_route *route; // route
    struct nl_addr *addr; // gateway address
    struct rtnl_nexthop *nh; // nexthop
    struct rtnl_link *link; // link
    int ifindex; // interface index
    int ret;

    sock = nl_socket_alloc(); // 分配socket
    if (!sock) {
        fprintf(stderr, "Failed to allocate netlink socket\n");
        return -1;
    }

    ret = nl_connect(sock, NETLINK_ROUTE); // 连接socket
    if (ret < 0) {
        fprintf(stderr, "Failed to connect to netlink socket: %s\n", nl_geterror(ret));
        nl_socket_free(sock);
        return -1;
    }

    ifindex = if_nametoindex(ifname); // 获取接口索引
    if (ifindex == 0) {
        fprintf(stderr, "Invalid interface name: %s\n", ifname);
        nl_socket_free(sock);
        return -1;
    }

    addr = nl_addr_build(AF_INET, gwaddr, strlen(gwaddr)); // 构建网关地址
    if (!addr) {
        fprintf(stderr, "Failed to build gateway address\n");
        nl_socket_free(sock);
        return -1;
    }

    route = rtnl_route_alloc(); // 分配route对象
    if (!route) {
        fprintf(stderr, "Failed to allocate route object\n");
        nl_socket_free(sock);
        nl_addr_put(addr);
        return -1;
    }

    // 设置地址族、路由表、路由作用域、协议、路由类型和目标地址
    rtnl_route_set_family(route, AF_INET);
    rtnl_route_set_table(route, RT_TABLE_MAIN);
    rtnl_route_set_scope(route, RT_SCOPE_UNIVERSE);
    rtnl_route_set_protocol(route, RTPROT_BOOT);
    rtnl_route_set_type(route, RTN_UNICAST);
    rtnl_route_set_dst(route, nl_addr_build(AF_INET, "0.0.0.0", 1));

    nh = rtnl_route_nh_alloc(); // 分配nexthop对象
    if (!nh) {
        fprintf(stderr, "Failed to allocate nexthop object\n");
        nl_socket_free(sock);
        nl_addr_put(addr);
        rtnl_route_put(route);
        return -1;
    }

    rtnl_route_nh_set_ifindex(nh, ifindex); // 设置接口索引
    rtnl_route_nh_set_gateway(nh, addr); // 设置网关地址
    rtnl_route_add_nexthop(route, nh); // 添加nexthop

    ret = rtnl_route_add(sock, route, NLM_F_CREATE | NLM_F_EXCL); // 添加路由
    if (ret < 0) {
        fprintf(stderr, "Failed to add route: %s\n", nl_geterror(ret));
        nl_socket_free(sock);
        nl_addr_put(addr);
        rtnl_route_put(route);
        rtnl_nexthop_put(nh);
        return -1;
    }

    printf("Gateway address %s added on interface %s\n", gwaddr, ifname);

    nl_addr_put(addr);
    rtnl_nexthop_put(nh);
    rtnl_route_put(route);
    nl_socket_free(sock);

    return 0;
}

int main() {
    set_gateway("ens3","::");
}