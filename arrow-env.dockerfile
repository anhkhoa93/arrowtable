# This file is to generate environment to build and run arrow-table application
# Arrow lib major release will be installed within the os (linux), this application will link with the lib by default
# Check https://arrow.apache.org/install/ for more detail or other OS distribution of arrow lib
# NOTE: Only make change or use this file if the image on the registry is changed, we only build this image once and reuse it in main Dockerfile
# Build command: docker build -f ./arrow-env.dockerfile -t arrow-env:latest .

FROM ubuntu:focal


ENV DEBIAN_FRONTEND=noninteractive 

RUN apt update
RUN apt install -y -V ca-certificates lsb-release wget
RUN wget https://apache.jfrog.io/artifactory/arrow/$(lsb_release --id --short | tr 'A-Z' 'a-z')/apache-arrow-apt-source-latest-$(lsb_release --codename --short).deb
RUN apt install -y -V ./apache-arrow-apt-source-latest-$(lsb_release --codename --short).deb
RUN apt update
RUN apt install -y -V libarrow-dev
RUN apt install -y -V libarrow-dataset-dev
RUN apt install -y -V libarrow-flight-dev
# Notes for Plasma related packages:
#   * You need to enable "non-free" component on Debian GNU/Linux
#   * You need to enable "multiverse" component on Ubuntu
#   * You can use Plasma related packages only on amd64
RUN apt install -y -V libplasma-dev
RUN apt install -y -V libgandiva-dev
RUN apt install -y -V libparquet-dev
RUN apt-get install -y -q --no-install-recommends \
      build-essential \
      cmake \
      pkg-config


# This is for unit testing
RUN apt-get -y install git
RUN git clone https://github.com/google/googletest.git -b release-1.11.0
RUN cd googletest && mkdir -p build && cd build && cmake .. && make && make install
