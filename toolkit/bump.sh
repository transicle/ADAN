#!/bin/bash

SCRIPT_DIR="$(dirname "$0")"
README="$SCRIPT_DIR/../README.md"
VER_FILE="$SCRIPT_DIR/../version.txt"

current=$(grep -oE 'version-[0-9.]+' "$README" | head -1 | cut -d'-' -f2)

if [[ -z "$current" ]]; then
    echo "Error: Could not parse current version from README.md"
    exit 1
fi

echo "Current version: $current"
read -rp "Bump to: " new_version

if [[ -z "$new_version" ]]; then
    echo "No version provided. Aborting."
    exit 1
fi

if [[ "$OSTYPE" == "darwin"* ]]; then
    SED_INLINE=(sed -i '') # macOS format
else
    SED_INLINE=(sed -i)    # Linux format
fi

"${SED_INLINE[@]}" "s/version-${current}/version-${new_version}/g" "$README"
"${SED_INLINE[@]}" "s/version-${current}/version-${new_version}/g" "$VER_FILE"

echo "Version bumped successfully: $current -> $new_version"
