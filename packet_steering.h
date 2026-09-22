#ifndef PACKET_STEERING_H
#define PACKET_STEERING_H

#include <stdbool.h>
#include <stdint.h>

typedef struct {
  const char *name;
  double latency_ms;
  double loss_pct;
  bool enabled;
} path_t;

typedef struct {
  uint64_t packets;
  uint64_t reroutes;
  uint64_t drops;
} telemetry_t;

bool path_healthy(const path_t *path);
int choose_path(uint32_t flow_hash, const path_t paths[], int count);
int steer_flow(uint32_t flow_hash, int current, const path_t paths[], int count, telemetry_t *telemetry);

#endif
