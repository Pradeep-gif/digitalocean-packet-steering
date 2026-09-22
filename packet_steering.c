#include "packet_steering.h"
#include <float.h>

bool path_healthy(const path_t *path) {
  return path->enabled && path->loss_pct < 2.0 && path->latency_ms < 25.0;
}

static double health_score(const path_t *path) {
  return path->latency_ms + (path->loss_pct * 10.0);
}

int choose_path(uint32_t flow_hash, const path_t paths[], int count) {
  int first = (int)(flow_hash % (uint32_t)count);
  int selected = -1;
  double best = DBL_MAX;
  for (int offset = 0; offset < count; offset++) {
    int index = (first + offset) % count;
    if (path_healthy(&paths[index]) && health_score(&paths[index]) < best) {
      selected = index;
      best = health_score(&paths[index]);
    }
  }
  return selected;
}

int steer_flow(uint32_t flow_hash, int current, const path_t paths[], int count, telemetry_t *telemetry) {
  telemetry->packets++;
  if (current >= 0 && current < count && path_healthy(&paths[current])) return current;
  int next = choose_path(flow_hash, paths, count);
  if (next < 0) telemetry->drops++;
  else if (next != current) telemetry->reroutes++;
  return next;
}
