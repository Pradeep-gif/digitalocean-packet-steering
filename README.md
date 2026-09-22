# Packet Steering Simulator

A compact C prototype for a cloud network datapath control loop. It selects an ECMP path for a flow, evaluates path health from latency and packet-loss signals, and reroutes traffic when the selected path fails the operating threshold.

## Run

make test

## Model

- Stable flow hashing keeps packets from a flow on one path.
- A path is unhealthy at 2% loss or 25 ms latency.
- The steering decision favors the lowest health score among healthy paths.
- Counters record packets, reroutes, and drops for fast diagnosis.

This is a userspace model, not an eBPF/XDP program. A production implementation would collect NIC and kernel telemetry, apply decisions through a programmable datapath, and use staged rollouts before changing live traffic.
