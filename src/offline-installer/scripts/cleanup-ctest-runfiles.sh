#!/bin/bash
SCRIPTPATH="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"

usage() {
    cat <<EOF
Script to be used for automated testing. It's to be used to cleanup the .run installer packages that are generated when running the ctests. This is to be used via a test in ctest called cleanup. This script will be run right before we run the install test. We need this script because the runner on github actions has limited space.

Usage:
    ./$SCRIPT_NAME [OPTIONS]
    ./$SCRIPT_NAME --delete-dir /mnt/
                   Deletes all the .run files in the dir /mnt

Options:
  
  --delete-dir <PATH_TO_DIR>            Deletes all the .run files in PATH_TO_DIR
  -h, --help               	            This help information
EOF
}


DELETE_DIR=


# Command-Line Arguments
while [[ $# -gt 0 ]]; do
    ARG="$1"
    case $ARG in
    --dir)
        DELETE_DIR="$2"
        shift
        shift
        ;;
    -h | --help)
        usage
        exit 0
        ;;
    *)
        usage
        exit 1
        ;;
    esac
done

if [[ ! -d $DELETE_DIR ]]; then
    echo "Directory $DELETE_DIR doesn't exist so nothing to delete!"
    exit 0
fi

echo "List of .run files that were deleted"
find "$DELETE_DIR" -name *.run -print -delete