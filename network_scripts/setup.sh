#!/bin/bash

. ./vars.sh

# sudo ip tuntap add dev $TAP_NAME mode tap

sudo ip netns add $NAMESPACE
# sudo ip link set $TAP_NAME netns $NAMESPACE
# sudo ip netns exec $NAMESPACE ip link set $TAP_NAME up
# sudo ip netns exec $NAMESPACE ip addr add $FULL_IP/24 dev $TAP_NAME
# sudo ip netns exec $NAMESPACE ip route add default dev $TAP_NAME

sudo ip link add $VETH_OUT type veth peer name $VETH_IN
sudo ip link set $VETH_IN netns $NAMESPACE

sudo ip addr add 192.168.42.1/24 dev $VETH_OUT
sudo ip link set $VETH_OUT up


sudo ip netns exec $NAMESPACE ip addr add 192.168.42.2/16 dev $VETH_IN
sudo ip netns exec $NAMESPACE ip link set $VETH_IN up
sudo ip netns exec $NAMESPACE ip link set lo up
