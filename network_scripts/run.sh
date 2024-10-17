#!/bin/bash

. ./vars.sh

if [[ -n $1 ]]; then
    sudo ip netns exec $NAMESPACE $@
    exit
else
    echo "Usage: $0 <command>"
    exit 1
fi

sudo ip netns exec $NAMESPACE $@
