#!/bin/bash
git clone https://github.com/K44N3R02/robotaksi-gazebo.git ~/robotaksi-gazebo-master
find $dir -type f -exec sed -i 's/\/ser\//\/$(whoami)\//g' {} +
