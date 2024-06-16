FROM ubuntu:22.04

#install dependencies (and neovim for debugging)
RUN apt-get update && apt-get install -y \
    && apt-get install -y gcc g++ neovim git

RUN DEBIAN_FRONTEND="noninteractive" apt-get install -y cmake

WORKDIR /app

COPY . .

CMD ["sleep", "infinity"]