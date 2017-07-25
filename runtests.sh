#!/bin/bash
./setuptests.sh

echo "Running keypair test suite"
cd keypairtest
./keypairtest
cd ..

./teardowntests.sh