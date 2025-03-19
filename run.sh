#!/bin/bash

# Check if a simulation path is provided
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <path_to_simulation_file>"
    exit 1
fi

# Define the path to the models directory
MODELS_DIR="$(pwd)/harita2"

# Check if the models directory exists
if [ ! -d "$MODELS_DIR" ]; then
    echo "Models directory does not exist: $MODELS_DIR"
    exit 1
fi

# Add the models directory to the GZ_SIM_RESOURCE_PATH
export GZ_SIM_RESOURCE_PATH="$MODELS_DIR:$GZ_SIM_RESOURCE_PATH"
echo "GZ_SIM_RESOURCE_PATH=[$GZ_SIM_RESOURCE_PATH]"

# Get the simulation file path from the argument
SIMULATION_FILE="$1"

# Check if the simulation file exists
if [ ! -f "$SIMULATION_FILE" ]; then
    echo "Simulation file does not exist: $SIMULATION_FILE"
    exit 1
fi

# Run Gazebo with the specified simulation file
gz sim -v 4 "$SIMULATION_FILE" -s

