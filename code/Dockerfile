FROM ubuntu:latest

RUN apt-get update && apt-get install -y zlib1g-dev build-essential wget libboost-all-dev libncurses-dev

#RUN rm /bin/sh && ln -s /bin/bash /bin/sh

RUN mkdir /opt/superchat

COPY * /opt/superchat/

WORKDIR /opt/superchat/

RUN wget http://www.joe.cloud/download/opensplice.tar.gz && tar xf opensplice.tar.gz && rm opensplice.tar.gz && sed -i 12s@.*@"OSPL_HOME="$OSDIR"@" $OSDIR/release.com

RUN /bin/bash -c  make 

EXPOSE 7400-7411

ENTRYPOINT ["./bin/superchat"]