#!/bin/bash

. ./vars.sh

sudo ip netns delete $NAMESPACE
# sudo ip link delete $TAP_NAME
sudo ip link delete veth0
