#!/bin/bash

# Check if input file is provided
if [ -z "$1" ]; then
  echo "Usage: $0 input_image [output_image]"
  exit 1
fi

INPUT="$1"
OUTPUT="${2:-grayscale_${INPUT}}"

# Convert to grayscale using ImageMagick
convert "$INPUT" -colorspace Gray "$OUTPUT"

echo "Grayscale image saved as $OUTPUT"