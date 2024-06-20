#!/bin/sh

w4 bundle --windows waternet-windows.exe  --title Waternet build/cart.wasm
w4 bundle --mac waternet-mac  --title Waternet build/cart.wasm
w4 bundle --linux waternet-linux  --title Waternet build/cart.wasm
w4 bundle --html index.html  --title Waternet build/cart.wasm
cp build/cart.wasm waternet.wasm
chmod +x ./waternet-mac
chmod +x ./waternet-linux
chmod +x ./waternet-windows.exe
tar -czvf ./waternet-windows.tar.gz ./waternet-windows.exe
tar -czvf ./waternet-mac.tar.gz ./waternet-mac
tar -czvf ./waternet-linux.tar.gz ./waternet-linux
tar -czvf ./waternet-html.tar.gz ./index.html
tar -czvf ./waternet-cart.tar.gz ./waternet.wasm
rm -f ./waternet-windows.exe
rm -f ./waternet-mac
rm -f ./waternet-linux
