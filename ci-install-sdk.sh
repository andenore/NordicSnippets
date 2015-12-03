#!/bin/sh
# Install SDK for Travis-CI
set -ex
SDK_INSTALL_DIR=/tmp
SDK_URL=http://developer.nordicsemi.com/nRF52_SDK/nRF52_SDK_v0.x.x
SDK_VERSION=nRF52_SDK_0.9.2_dbc28c9
# Remove old file if exists
rm -Rf /tmp/$SDK_VERSION.zip
rm -Rf /tmp/nrf52-sdk-for-travis-ci
wget $SDK_URL/$SDK_VERSION.zip --directory-prefix=/tmp
SDK_PATH=/tmp/nrf52-sdk-for-travis-ci
mkdir -p $SDK_PATH
unzip /tmp/$SDK_VERSION.zip -d  $SDK_PATH
