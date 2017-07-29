#!/bin/bash
echo "Running keypair test suite"
cp keypair.{h,c} keypairtest/
cd keypairtest
make
./keypairtest
make clean &>/dev/null
rm keypair.{h,c}
rm testkey*
cd ..

echo "Running transaction test suite"
cp transaction.{h,c} transactiontest/
cp keypair.{h,c} transactiontest/
cd transactiontest/
make
./transactiontest
make clean &>/dev/null
rm transaction.{h,c}
rm keypair.{h,c}
cd ..

echo "Running the list test suite"
cp list.{h,c} listtest/
cd listtest/
make
./listtest
make clean &>/dev/null
rm list.{h,c}
cd ..