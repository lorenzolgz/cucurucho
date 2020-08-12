FROM ubuntu:18.04

LABEL description="Container for Cucurucho++"

# install build dependencies 
RUN apt -y update && apt -y install g++ cmake pkg-config cmake-data libjsoncpp-dev

COPY . /usr/local/cucurucho

WORKDIR /usr/local/cucurucho/

RUN chmod +x startserver.sh

CMD ["./startserver.sh"]
