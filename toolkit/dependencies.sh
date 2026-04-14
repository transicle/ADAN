#!/bin/bash

detect_os() {
    if [[ "$OSTYPE" == "darwin"* ]]; then
        echo "macOS"
    elif [[ "$OSTYPE" == "linux-gnu"* ]]; then
        echo "Linux"
    else
        echo "Unknown"
    fi
}

detect_linux_distro() {
    if [ -f /etc/os-release ]; then
        . /etc/os-release
        echo "$ID"
    elif [ -f /etc/distro-release ]; then
        cat /etc/distro-release | grep -oP '(?<=^ID=)[^"]+'
    else
        echo "unknown"
    fi
}

install_macos() {
    if ! command -v brew &> /dev/null; then
        /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
    fi
    brew install xmake
}

install_linux() {
    local distro=$(detect_linux_distro)
    
    case "$distro" in
        ubuntu|debian)
            apt-get update
            apt-get install -y xmake gcc g++
            ;;
        fedora|rhel|centos)
            dnf install -y xmake gcc gcc-c++
            ;;
        arch)
            pacman -Sy xmake base-devel
            ;;
        opensuse*)
            zypper install -y xmake gcc gcc-c++
            ;;
        alpine)
            apk add xmake gcc g++
            ;;
        *)
            exit 1
            ;;
    esac
}

main() {
    local os=$(detect_os)
    
    case "$os" in
        macOS)
            install_macos
            ;;
        Linux)
            install_linux
            ;;
        *)
            exit 1
            ;;
    esac
}

main
