#!/usr/bin/env bash
source ${BASH_SOURCE%/*}/common.sh

exec_check lean --plugin ${EXAMPLE_PLUGIN} --run -j 0 "$f"
