#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="${SCRIPT_DIR}/build"

# 解析参数：--clean 强制清空、--reuse 复用现有，无参数时交互询问（非交互默认复用）
ACTION="prompt" # prompt|clean|reuse
if [[ $# -gt 0 ]]; then
  case "${1:-}" in
    --clean)
      ACTION="clean" ;;
    --reuse)
      ACTION="reuse" ;;
    -h|--help)
      echo "用法: bash src/build.sh [--clean|--reuse]"
      echo "  --clean  清空 src/build 后重新配置与编译"
      echo "  --reuse  复用现有 src/build (若不存在则创建)"
      exit 0 ;;
    *)
      echo "未知参数: $1" >&2
      exit 2 ;;
  esac
fi

if [[ "${ACTION}" == "prompt" && -d "${BUILD_DIR}" ]]; then
  if [[ -t 0 && -t 1 ]]; then
    read -r -p "检测到已存在 build 目录，是否清空后重建? [Y/n] " ans
    case "${ans}" in
      ""|y|Y|yes|YES)
        ACTION="clean" ;;
      *)
        ACTION="reuse" ;;
    esac
  else
    ACTION="reuse"
  fi
fi

if [[ "${ACTION}" == "clean" ]]; then
  echo "执行清理: 删除 ${BUILD_DIR}"
  rm -rf "${BUILD_DIR}"
fi

mkdir -p "${BUILD_DIR}"
cd "${BUILD_DIR}"

echo "[1/2] 配置 CMake..."
if ! cmake ..; then
  echo "CMake 配置失败，请检查 src/CMakeLists.txt"
  exit 1
fi

echo "[2/2] 开始编译..."
CORES=2
if command -v getconf >/dev/null 2>&1; then
  CORES="$(getconf _NPROCESSORS_ONLN || echo 2)"
fi

if ! cmake --build . -- -j"${CORES}"; then
  echo "编译失败"
  exit 1
fi

echo "编译完成。若 CMakeLists.txt 设置了 LIBRARY_OUTPUT_DIRECTORY，则产物在: ${SCRIPT_DIR}/../lib"


