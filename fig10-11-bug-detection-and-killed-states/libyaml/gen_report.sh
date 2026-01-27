#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: <report_dir>"
    exit 1
fi

REPORT_DIR=$1

rm -rf out.zcov
zcov scan out.zcov .
zcov genhtml out.zcov ${REPORT_DIR}
