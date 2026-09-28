#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUILD_DIR="$(mktemp -d)"
SERVER_PID=""

cleanup() {
  if [[ -n "$SERVER_PID" ]]; then
    kill "$SERVER_PID" 2>/dev/null || true
    wait "$SERVER_PID" 2>/dev/null || true
  fi
  rm -rf "$BUILD_DIR"
}
trap cleanup EXIT

CFLAGS=(-std=c11 -Wall -Wextra -Wpedantic -Werror)

gcc "${CFLAGS[@]}" "$ROOT/src/c/09_programowanie_sieci/01_klient_serwer_tcp/serwer.c"   -o "$BUILD_DIR/tcp_server"
gcc "${CFLAGS[@]}" "$ROOT/src/c/09_programowanie_sieci/01_klient_serwer_tcp/klient.c"   -o "$BUILD_DIR/tcp_client"

timeout 5 "$BUILD_DIR/tcp_server" >"$BUILD_DIR/tcp_server.log" 2>&1 &
SERVER_PID=$!
sleep 0.2
TCP_OUTPUT="$(timeout 5 "$BUILD_DIR/tcp_client")"
wait "$SERVER_PID"
SERVER_PID=""
grep -q '40' <<<"$TCP_OUTPUT"

gcc "${CFLAGS[@]}" "$ROOT/src/c/09_programowanie_sieci/02_klient_serwer_udp/serwer.c"   -o "$BUILD_DIR/udp_server"
gcc "${CFLAGS[@]}" "$ROOT/src/c/09_programowanie_sieci/02_klient_serwer_udp/klient.c"   -o "$BUILD_DIR/udp_client"

timeout 5 "$BUILD_DIR/udp_server" >"$BUILD_DIR/udp_server.log" 2>&1 &
SERVER_PID=$!
sleep 0.2
UDP_OUTPUT="$(timeout 5 "$BUILD_DIR/udp_client")"
wait "$SERVER_PID"
SERVER_PID=""
grep -q '40' <<<"$UDP_OUTPUT"

gcc "${CFLAGS[@]}" "$ROOT/src/c/09_programowanie_sieci/03_serwer_http/main.c"   -o "$BUILD_DIR/http_server"

timeout 5 "$BUILD_DIR/http_server" >"$BUILD_DIR/http_server.log" 2>&1 &
SERVER_PID=$!
sleep 0.2
HTTP_OUTPUT="$(curl --fail --silent --max-time 3 http://127.0.0.1:8080/)"
wait "$SERVER_PID"
SERVER_PID=""
grep -q 'Witaj z prostego serwera C!' <<<"$HTTP_OUTPUT"

echo "TCP, UDP and HTTP smoke tests passed."
