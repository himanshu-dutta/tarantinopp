FROM --platform=arm64 ubuntu:latest

RUN apt update && apt upgrade -y
RUN apt install build-essential python3 wget curl nginx -y

WORKDIR /home
RUN wget https://github.com/Kitware/CMake/releases/download/v3.26.3/cmake-3.26.3-linux-aarch64.sh
RUN chmod 777 cmake-3.26.3-linux-aarch64.sh
RUN ./cmake-3.26.3-linux-aarch64.sh --prefix=/usr/local --skip-license
RUN rm cmake-3.26.3-linux-aarch64.sh

WORKDIR /app
COPY . .


RUN rm -rf build
RUN mkdir -p build
WORKDIR /app/build
RUN cmake ..

WORKDIR /app
