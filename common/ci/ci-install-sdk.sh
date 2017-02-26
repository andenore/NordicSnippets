#!/bin/sh
# Install SDK for Travis-CI
set -ex
SDK_INSTALL_DIR=/tmp
SDK_URL=http://developer.nordicsemi.com/nRF5_SDK/nRF5_SDK_v12.x.x
SDK_VERSION=nRF5_SDK_12.2.0_f012efa
# Remove old file if exists
rm -Rf /tmp/$SDK_VERSION.zip
rm -Rf /tmp/nrf52-sdk-for-travis-ci
wget $SDK_URL/$SDK_VERSION.zip --directory-prefix=/tmp
SDK_PATH=/tmp/nrf52-sdk-for-travis-ci
mkdir -p $SDK_PATH
unzip /tmp/$SDK_VERSION.zip -d  $SDK_PATH
