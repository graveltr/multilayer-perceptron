# Use an official Ubuntu image as a base
FROM ubuntu:20.04

# Set the maintainer label
LABEL maintainer="trevor.gravely@vanderbilt.edu"

# Set environment variables to avoid user interaction during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Install essential build tools, gcc, g++, cmake, git, and libcurl
RUN apt-get update && apt-get install -y \
    build-essential \
    gcc \
    g++ \
    cmake \
    git \
    libcurl4-openssl-dev \
    && rm -rf /var/lib/apt/lists/*

# Set the working directory
WORKDIR /usr/src/myapp

# Copy the current directory contents into the container
COPY . .

# Example command to compile your application (can be modified as needed)
# RUN make

# Command to keep the container running for development
CMD [ "tail", "-f", "/dev/null" ]
