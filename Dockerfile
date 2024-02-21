# Use a slim version of Debian as the base image
FROM debian:bullseye-slim

# Update the package lists and install necessary packages
# build-essential: contains essential tools for building binaries
# gdb: GNU Debugger for debugging
# valgrind: tool for memory debugging, memory leak detection, and profiling
# libncurses5-dev: developer's libraries for ncurses
# Clean up the package lists to reduce image size
RUN apt-get update && apt-get install -y \
    build-essential \
    gdb \
    valgrind \
    libncurses5-dev \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Set the working directory to /usr/src/my_htop
WORKDIR /app

# Copy the current directory contents into the container at /usr/src/my_htop
COPY . .

# Compile the application using the make command
RUN make