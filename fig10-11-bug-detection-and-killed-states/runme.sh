#!/bin/bash

ulimit -s unlimited

# clear old data

rm -rf json.h/*.pdf json.h/*.png json.h/logs
rm -rf libosip/*.pdf libosip/*.png libosip/killed_states.* libosip/logs
rm -rf libyaml/*.pdf libyaml/*.png libyaml/killed_states.* libyaml/logs
rm -rf regex/*.pdf regex/*.png regex/logs
rm -rf utf8.h/*.pdf utf8.h/*.png utf8.h/logs


cd regex
./run.sh
mv *.pdf ../fig10a-regex.pdf
mv *.png ../fig10a-regex.png
cd ..

cd utf8.h
./run.sh
mv *.pdf ../fig10b-utf8-h.pdf
mv *.png ../fig10b-utf8-h.png
cd ..

cd json.h
./run.sh
mv *.pdf ../fig10c-json-h.pdf
mv *.png ../fig10c-json-h.png
cd ..

cd libosip
./run.sh
mv *.pdf ../fig10d-libosip.pdf
mv *.png ../fig10d-libosip.png
cd ..


cd libyaml
./run.sh
mv *.pdf ../fig10e-libyaml.pdf
mv *.png ../fig10e-libyaml.png
cd ..

# Kiled States
python3 plot_killed_states.py libosip
mv libosip/killed_states.png fig11a-libosip.png
mv libosip/killed_states.pdf fig11a-libosip.pdf

python3 plot_killed_states.py libyaml
mv libyaml/killed_states.png fig11b-libyaml.png
mv libyaml/killed_states.pdf fig11b-libyaml.pdf