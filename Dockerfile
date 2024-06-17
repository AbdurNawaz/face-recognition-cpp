FROM ubuntu:22.04

ARG DEBIAN_FRONTEND=noninteractive

#install dependencies (and neovim for debugging)
RUN apt-get update && apt-get install -y \
    && apt-get install -y gcc g++ neovim git

RUN apt-get update && apt-get install -y \
    # OpenCV dependencies
    build-essential cmake libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev \
    python3-dev python3-numpy libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev libdc1394-dev \
    libcanberra-gtk-module libcanberra-gtk3-module

RUN git clone https://github.com/opencv/opencv.git && \
    cd /opencv && mkdir build && cd build && \
    cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr/local .. && \
    make -j"$(nproc)" && \
    make install && \
    rm -rf /opencv

WORKDIR /app

COPY . .

CMD ["sleep", "infinity"]