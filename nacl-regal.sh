#!/bin/bash
# Copyright (c) 2012 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

# nacl-regal.sh
#
# usage:  nacl-regal.sh
#
# this script downloads, patches, and builds ffmpeg for Native Client 
#

set -e

readonly PACKAGE_NAME=regal

NACL_GLIBC=${NACL_GLIBC:=0}

if [ ${NACL_GLIBC} == 1 ]; then
    LIBC=glibc
else
    LIBC=newlib
fi

OSNAME=linux

X86_BIN_DIR=${NACL_SDK_ROOT}/toolchain/${OSNAME}_x86_${LIBC}/bin
ARM_BIN_DIR=${NACL_SDK_ROOT}/toolchain/${OSNAME}_arm_newlib/bin

export NACL_GLIBC
export NACL_ARCH
export PATH=${PATH}:${X86_BIN_DIR}:${ARM_BIN_DIR}

echo "Building x86_64"
make -f Makefile SYSTEM=nacl-x86_64 $*
echo "Building i686"
make -f Makefile SYSTEM=nacl-i686 $*

unset NACL_GLIBC
echo "Building ARM"
make -f Makefile SYSTEM=nacl-arm $*
